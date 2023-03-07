static int cine_read_header(AVFormatContext *avctx) /* <=== */ 
{
    AVIOContext *pb = avctx->pb;
    AVStream *st;
    unsigned int version, compression, offImageHeader, offSetup, offImageOffsets, biBitCount, length, CFA;
    int vflip;
    char *description;
    uint64_t i;

    st = avformat_new_stream(avctx, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->codec->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codec->codec_id   = AV_CODEC_ID_RAWVIDEO;
    st->codec->codec_tag  = 0;

    /* CINEFILEHEADER structure */
    avio_skip(pb, 4); // Type, Headersize

    compression = avio_rl16(pb);
    version     = avio_rl16(pb);
    if (version != 1) {
        avpriv_request_sample(avctx, "uknown version %i", version);
        return AVERROR_INVALIDDATA;
    }

    avio_skip(pb, 12); // FirstMovieImage, TotalImageCount, FirstImageNumber

    st->duration    = avio_rl32(pb);
    offImageHeader  = avio_rl32(pb);
    offSetup        = avio_rl32(pb);
    offImageOffsets = avio_rl32(pb);

    avio_skip(pb, 8); // TriggerTime

    /* BITMAPINFOHEADER structure */
    avio_seek(pb, offImageHeader, SEEK_SET);
    avio_skip(pb, 4); //biSize
    st->codec->width      = avio_rl32(pb);
    st->codec->height     = avio_rl32(pb);

    if (avio_rl16(pb) != 1) // biPlanes
        return AVERROR_INVALIDDATA;

    biBitCount = avio_rl16(pb);
    if (biBitCount != 8 && biBitCount != 16 && biBitCount != 24 && biBitCount != 48)
        return AVERROR_INVALIDDATA;

    switch (avio_rl32(pb)) {
    case BMP_RGB:
        vflip = 0;
        break;
    case 0x100: /* BI_PACKED */
        st->codec->codec_tag = MKTAG('B', 'I', 'T', 0);
        vflip = 1;
        break;
    default:
        avpriv_request_sample(avctx, "unknown bitmap compression");
        return AVERROR_INVALIDDATA;
    }

    avio_skip(pb, 4); // biSizeImage

    /* parse SETUP structure */
    avio_seek(pb, offSetup, SEEK_SET);
    avio_skip(pb, 140); // FrameRatae16 .. descriptionOld
    if (avio_rl16(pb) != 0x5453)
        return AVERROR_INVALIDDATA;
    length = avio_rl16(pb);
    if (length < 0x163C) {
        avpriv_request_sample(avctx, "short SETUP header");
        return AVERROR_INVALIDDATA;
    }

    avio_skip(pb, 616); // Binning .. bFlipH
    if (!avio_rl32(pb) ^ vflip) {
        st->codec->extradata  = av_strdup("BottomUp");
        st->codec->extradata_size  = 9;
    }

    avio_skip(pb, 4); // Grid

    avpriv_set_pts_info(st, 64, 1, avio_rl32(pb));

    avio_skip(pb, 20); // Shutter .. bEnableColor

    set_metadata_int(&st->metadata, "camera_version", avio_rl32(pb));
    set_metadata_int(&st->metadata, "firmware_version", avio_rl32(pb));
    set_metadata_int(&st->metadata, "software_version", avio_rl32(pb));
    set_metadata_int(&st->metadata, "recording_timezone", avio_rl32(pb));

    CFA = avio_rl32(pb);

    set_metadata_int(&st->metadata, "brightness", avio_rl32(pb));
    set_metadata_int(&st->metadata, "contrast", avio_rl32(pb));
    set_metadata_int(&st->metadata, "gamma", avio_rl32(pb));

    avio_skip(pb, 72); // Reserved1 .. WBView

    st->codec->bits_per_coded_sample = avio_rl32(pb);

    if (compression == CC_RGB) {
        if (biBitCount == 8) {
            st->codec->pix_fmt = AV_PIX_FMT_GRAY8;
        } else if (biBitCount == 16) {
            st->codec->pix_fmt = AV_PIX_FMT_GRAY16LE;
        } else if (biBitCount == 24) {
            st->codec->pix_fmt = AV_PIX_FMT_BGR24;
        } else if (biBitCount == 48) {
            st->codec->pix_fmt = AV_PIX_FMT_BGR48LE;
        } else {
            avpriv_request_sample(avctx, "unsupported biBitCount %i", biBitCount);
            return AVERROR_INVALIDDATA;
        }
    } else if (compression == CC_UNINT) {
        switch (CFA & 0xFFFFFF) {
        case CFA_BAYER:
            if (biBitCount == 8) {
                st->codec->pix_fmt = AV_PIX_FMT_BAYER_GBRG8;
            } else if (biBitCount == 16) {
                st->codec->pix_fmt = AV_PIX_FMT_BAYER_GBRG16LE;
            } else {
                avpriv_request_sample(avctx, "unsupported biBitCount %i", biBitCount);
                return AVERROR_INVALIDDATA;
            }
            break;
        case CFA_BAYERFLIP:
            if (biBitCount == 8) {
                st->codec->pix_fmt = AV_PIX_FMT_BAYER_RGGB8;
            } else if (biBitCount == 16) {
                st->codec->pix_fmt = AV_PIX_FMT_BAYER_RGGB16LE;
            } else {
                avpriv_request_sample(avctx, "unsupported biBitCount %i", biBitCount);
                return AVERROR_INVALIDDATA;
            }
            break;
        default:
           avpriv_request_sample(avctx, "unsupported Color Field Array (CFA) %i", CFA & 0xFFFFFF);
            return AVERROR_INVALIDDATA;
        }
    } else { //CC_LEAD
        avpriv_request_sample(avctx, "unsupported compression %i", compression);
        return AVERROR_INVALIDDATA;
    }

    avio_skip(pb, 696); // Conv8Min ... ImHeightAcq

#define DESCRIPTION_SIZE 4096
    description = av_malloc(DESCRIPTION_SIZE + 1);
    if (!description)
        return AVERROR(ENOMEM);
    i = avio_get_str(pb, DESCRIPTION_SIZE, description, DESCRIPTION_SIZE + 1);
    if (i < DESCRIPTION_SIZE)
        avio_skip(pb, DESCRIPTION_SIZE - i);
    if (description[0])
        av_dict_set(&st->metadata, "description", description, AV_DICT_DONT_STRDUP_VAL);
    else
        av_free(description);

    /* parse image offsets */
    avio_seek(pb, offImageOffsets, SEEK_SET);
    
        av_add_index_entry(st, avio_rl64(pb), i, 0, 0, AVINDEX_KEYFRAME);

    return 0;
}
static av_cold int rl2_read_header(AVFormatContext *s, /* <=== */ 
                            AVFormatParameters *ap)
{
    ByteIOContext *pb = s->pb;
    AVStream *st;
    unsigned int frame_count;
    unsigned int audio_frame_counter = 0;
    unsigned int video_frame_counter = 0;
    unsigned int back_size;
    int data_size;
    unsigned short encoding_method;
    unsigned short sound_rate;
    unsigned short rate;
    unsigned short channels;
    unsigned short def_sound_size;
    unsigned int signature;
    unsigned int pts_den = 11025; /* video only case */
    unsigned int pts_num = 1103;
    unsigned int* chunk_offset = NULL;
    int* chunk_size = NULL;
    int* audio_size = NULL;
    int i;
    int ret = 0;

    url_fskip(pb,4);          /* skip FORM tag */
    back_size = get_le32(pb); /** get size of the background frame */
    signature = get_be32(pb);
    data_size = get_be32(pb);
    frame_count = get_le32(pb);

    /* disallow back_sizes and frame_counts that may lead to overflows later */
    if(back_size > INT_MAX/2  || frame_count > INT_MAX / sizeof(uint32_t))
        return AVERROR_INVALIDDATA;

    encoding_method = get_le16(pb);
    sound_rate = get_le16(pb);
    rate = get_le16(pb);
    channels = get_le16(pb);
    def_sound_size = get_le16(pb);

    /** setup video stream */
    st = av_new_stream(s, 0);
    if(!st)
         return AVERROR(ENOMEM);

    st->codec->codec_type = CODEC_TYPE_VIDEO;
    st->codec->codec_id = CODEC_ID_RL2;
    st->codec->codec_tag = 0;  /* no fourcc */
    st->codec->width = 320;
    st->codec->height = 200;

    /** allocate and fill extradata */
    st->codec->extradata_size = EXTRADATA1_SIZE;

    if(signature == RLV3_TAG && back_size > 0)
        st->codec->extradata_size += back_size;

    st->codec->extradata = av_mallocz(st->codec->extradata_size +
                                          FF_INPUT_BUFFER_PADDING_SIZE);
    if(!st->codec->extradata)
        return AVERROR(ENOMEM);

    if(get_buffer(pb,st->codec->extradata,st->codec->extradata_size) !=
                      st->codec->extradata_size)
        return AVERROR(EIO);

    /** setup audio stream if present */
    if(sound_rate){
        pts_num = def_sound_size;
        pts_den = rate;

        st = av_new_stream(s, 0);
        if (!st)
            return AVERROR(ENOMEM);
        st->codec->codec_type = CODEC_TYPE_AUDIO;
        st->codec->codec_id = CODEC_ID_PCM_U8;
        st->codec->codec_tag = 1;
        st->codec->channels = channels;
        st->codec->bits_per_sample = 8;
        st->codec->sample_rate = rate;
        st->codec->bit_rate = st->codec->channels * st->codec->sample_rate *
            st->codec->bits_per_sample;
        st->codec->block_align = st->codec->channels *
            st->codec->bits_per_sample / 8;
        av_set_pts_info(st,32,1,rate);
    }

    av_set_pts_info(s->streams[0], 32, pts_num, pts_den);

    chunk_size =   av_malloc(frame_count * sizeof(uint32_t));
    audio_size =   av_malloc(frame_count * sizeof(uint32_t));
    chunk_offset = av_malloc(frame_count * sizeof(uint32_t));

    if(!chunk_size || !audio_size || !chunk_offset){
        av_free(chunk_size);
        av_free(audio_size);
        av_free(chunk_offset);
        return AVERROR(ENOMEM);
    }

    /** read offset and size tables */
    
        chunk_size[i] = get_le32(pb);
    
        chunk_offset[i] = get_le32(pb);
    
        audio_size[i] = get_le32(pb) & 0xFFFF;

    /** build the sample index */
    for(i=0;i<frame_count;i++){
        if(chunk_size[i] < 0 || audio_size[i] > chunk_size[i]){
            ret = AVERROR_INVALIDDATA;
            break;
        }

        if(sound_rate && audio_size[i]){
            av_add_index_entry(s->streams[1], chunk_offset[i],
                audio_frame_counter,audio_size[i], 0, AVINDEX_KEYFRAME);
            audio_frame_counter += audio_size[i] / channels;
        }
        av_add_index_entry(s->streams[0], chunk_offset[i] + audio_size[i],
            video_frame_counter,chunk_size[i]-audio_size[i],0,AVINDEX_KEYFRAME);
        ++video_frame_counter;
    }


    av_free(chunk_size);
    av_free(audio_size);
    av_free(chunk_offset);

    return ret;
}
static av_cold int rl2_read_header(AVFormatContext *s, /* <=== */ 
                            AVFormatParameters *ap)
{
    ByteIOContext *pb = s->pb;
    AVStream *st;
    unsigned int frame_count;
    unsigned int audio_frame_counter = 0;
    unsigned int video_frame_counter = 0;
    unsigned int back_size;
    int data_size;
    unsigned short encoding_method;
    unsigned short sound_rate;
    unsigned short rate;
    unsigned short channels;
    unsigned short def_sound_size;
    unsigned int signature;
    unsigned int pts_den = 11025; /* video only case */
    unsigned int pts_num = 1103;
    unsigned int* chunk_offset = NULL;
    int* chunk_size = NULL;
    int* audio_size = NULL;
    int i;
    int ret = 0;

    url_fskip(pb,4);          /* skip FORM tag */
    back_size = get_le32(pb); /** get size of the background frame */
    signature = get_be32(pb);
    data_size = get_be32(pb);
    frame_count = get_le32(pb);

    /* disallow back_sizes and frame_counts that may lead to overflows later */
    if(back_size > INT_MAX/2  || frame_count > INT_MAX / sizeof(uint32_t))
        return AVERROR_INVALIDDATA;

    encoding_method = get_le16(pb);
    sound_rate = get_le16(pb);
    rate = get_le16(pb);
    channels = get_le16(pb);
    def_sound_size = get_le16(pb);

    /** setup video stream */
    st = av_new_stream(s, 0);
    if(!st)
         return AVERROR(ENOMEM);

    st->codec->codec_type = CODEC_TYPE_VIDEO;
    st->codec->codec_id = CODEC_ID_RL2;
    st->codec->codec_tag = 0;  /* no fourcc */
    st->codec->width = 320;
    st->codec->height = 200;

    /** allocate and fill extradata */
    st->codec->extradata_size = EXTRADATA1_SIZE;

    if(signature == RLV3_TAG && back_size > 0)
        st->codec->extradata_size += back_size;

    st->codec->extradata = av_mallocz(st->codec->extradata_size +
                                          FF_INPUT_BUFFER_PADDING_SIZE);
    if(!st->codec->extradata)
        return AVERROR(ENOMEM);

    if(get_buffer(pb,st->codec->extradata,st->codec->extradata_size) !=
                      st->codec->extradata_size)
        return AVERROR(EIO);

    /** setup audio stream if present */
    if(sound_rate){
        pts_num = def_sound_size;
        pts_den = rate;

        st = av_new_stream(s, 0);
        if (!st)
            return AVERROR(ENOMEM);
        st->codec->codec_type = CODEC_TYPE_AUDIO;
        st->codec->codec_id = CODEC_ID_PCM_U8;
        st->codec->codec_tag = 1;
        st->codec->channels = channels;
        st->codec->bits_per_sample = 8;
        st->codec->sample_rate = rate;
        st->codec->bit_rate = st->codec->channels * st->codec->sample_rate *
            st->codec->bits_per_sample;
        st->codec->block_align = st->codec->channels *
            st->codec->bits_per_sample / 8;
        av_set_pts_info(st,32,1,rate);
    }

    av_set_pts_info(s->streams[0], 32, pts_num, pts_den);

    chunk_size =   av_malloc(frame_count * sizeof(uint32_t));
    audio_size =   av_malloc(frame_count * sizeof(uint32_t));
    chunk_offset = av_malloc(frame_count * sizeof(uint32_t));

    if(!chunk_size || !audio_size || !chunk_offset){
        av_free(chunk_size);
        av_free(audio_size);
        av_free(chunk_offset);
        return AVERROR(ENOMEM);
    }

    /** read offset and size tables */
    
        chunk_size[i] = get_le32(pb);
    
        chunk_offset[i] = get_le32(pb);
    
        audio_size[i] = get_le32(pb) & 0xFFFF;

    /** build the sample index */
    for(i=0;i<frame_count;i++){
        if(chunk_size[i] < 0 || audio_size[i] > chunk_size[i]){
            ret = AVERROR_INVALIDDATA;
            break;
        }

        if(sound_rate && audio_size[i]){
            av_add_index_entry(s->streams[1], chunk_offset[i],
                audio_frame_counter,audio_size[i], 0, AVINDEX_KEYFRAME);
            audio_frame_counter += audio_size[i] / channels;
        }
        av_add_index_entry(s->streams[0], chunk_offset[i] + audio_size[i],
            video_frame_counter,chunk_size[i]-audio_size[i],0,AVINDEX_KEYFRAME);
        ++video_frame_counter;
    }


    av_free(chunk_size);
    av_free(audio_size);
    av_free(chunk_offset);

    return ret;
}
static av_cold int rl2_read_header(AVFormatContext *s, /* <=== */ 
                            AVFormatParameters *ap)
{
    ByteIOContext *pb = s->pb;
    AVStream *st;
    unsigned int frame_count;
    unsigned int audio_frame_counter = 0;
    unsigned int video_frame_counter = 0;
    unsigned int back_size;
    int data_size;
    unsigned short encoding_method;
    unsigned short sound_rate;
    unsigned short rate;
    unsigned short channels;
    unsigned short def_sound_size;
    unsigned int signature;
    unsigned int pts_den = 11025; /* video only case */
    unsigned int pts_num = 1103;
    unsigned int* chunk_offset = NULL;
    int* chunk_size = NULL;
    int* audio_size = NULL;
    int i;
    int ret = 0;

    url_fskip(pb,4);          /* skip FORM tag */
    back_size = get_le32(pb); /** get size of the background frame */
    signature = get_be32(pb);
    data_size = get_be32(pb);
    frame_count = get_le32(pb);

    /* disallow back_sizes and frame_counts that may lead to overflows later */
    if(back_size > INT_MAX/2  || frame_count > INT_MAX / sizeof(uint32_t))
        return AVERROR_INVALIDDATA;

    encoding_method = get_le16(pb);
    sound_rate = get_le16(pb);
    rate = get_le16(pb);
    channels = get_le16(pb);
    def_sound_size = get_le16(pb);

    /** setup video stream */
    st = av_new_stream(s, 0);
    if(!st)
         return AVERROR(ENOMEM);

    st->codec->codec_type = CODEC_TYPE_VIDEO;
    st->codec->codec_id = CODEC_ID_RL2;
    st->codec->codec_tag = 0;  /* no fourcc */
    st->codec->width = 320;
    st->codec->height = 200;

    /** allocate and fill extradata */
    st->codec->extradata_size = EXTRADATA1_SIZE;

    if(signature == RLV3_TAG && back_size > 0)
        st->codec->extradata_size += back_size;

    st->codec->extradata = av_mallocz(st->codec->extradata_size +
                                          FF_INPUT_BUFFER_PADDING_SIZE);
    if(!st->codec->extradata)
        return AVERROR(ENOMEM);

    if(get_buffer(pb,st->codec->extradata,st->codec->extradata_size) !=
                      st->codec->extradata_size)
        return AVERROR(EIO);

    /** setup audio stream if present */
    if(sound_rate){
        pts_num = def_sound_size;
        pts_den = rate;

        st = av_new_stream(s, 0);
        if (!st)
            return AVERROR(ENOMEM);
        st->codec->codec_type = CODEC_TYPE_AUDIO;
        st->codec->codec_id = CODEC_ID_PCM_U8;
        st->codec->codec_tag = 1;
        st->codec->channels = channels;
        st->codec->bits_per_sample = 8;
        st->codec->sample_rate = rate;
        st->codec->bit_rate = st->codec->channels * st->codec->sample_rate *
            st->codec->bits_per_sample;
        st->codec->block_align = st->codec->channels *
            st->codec->bits_per_sample / 8;
        av_set_pts_info(st,32,1,rate);
    }

    av_set_pts_info(s->streams[0], 32, pts_num, pts_den);

    chunk_size =   av_malloc(frame_count * sizeof(uint32_t));
    audio_size =   av_malloc(frame_count * sizeof(uint32_t));
    chunk_offset = av_malloc(frame_count * sizeof(uint32_t));

    if(!chunk_size || !audio_size || !chunk_offset){
        av_free(chunk_size);
        av_free(audio_size);
        av_free(chunk_offset);
        return AVERROR(ENOMEM);
    }

    /** read offset and size tables */
    
        chunk_size[i] = get_le32(pb);
    
        chunk_offset[i] = get_le32(pb);
    
        audio_size[i] = get_le32(pb) & 0xFFFF;

    /** build the sample index */
    for(i=0;i<frame_count;i++){
        if(chunk_size[i] < 0 || audio_size[i] > chunk_size[i]){
            ret = AVERROR_INVALIDDATA;
            break;
        }

        if(sound_rate && audio_size[i]){
            av_add_index_entry(s->streams[1], chunk_offset[i],
                audio_frame_counter,audio_size[i], 0, AVINDEX_KEYFRAME);
            audio_frame_counter += audio_size[i] / channels;
        }
        av_add_index_entry(s->streams[0], chunk_offset[i] + audio_size[i],
            video_frame_counter,chunk_size[i]-audio_size[i],0,AVINDEX_KEYFRAME);
        ++video_frame_counter;
    }


    av_free(chunk_size);
    av_free(audio_size);
    av_free(chunk_offset);

    return ret;
}
static int ivr_read_header(AVFormatContext *s) /* <=== */ 
{
    unsigned tag, type, len, tlen, value;
    int i, j, n, count, nb_streams, ret;
    uint8_t key[256], val[256];
    AVIOContext *pb = s->pb;
    AVStream *st;
    int64_t pos, offset, temp;

    pos = avio_tell(pb);
    tag = avio_rl32(pb);
    if (tag == MKTAG('.','R','1','M')) {
        if (avio_rb16(pb) != 1)
            return AVERROR_INVALIDDATA;
        if (avio_r8(pb) != 1)
            return AVERROR_INVALIDDATA;
        len = avio_rb32(pb);
        avio_skip(pb, len);
        avio_skip(pb, 5);
        temp = avio_rb64(pb);
        while (!avio_feof(pb) && temp) {
            offset = temp;
            temp = avio_rb64(pb);
        }
        avio_skip(pb, offset - avio_tell(pb));
        if (avio_r8(pb) != 1)
            return AVERROR_INVALIDDATA;
        len = avio_rb32(pb);
        avio_skip(pb, len);
        if (avio_r8(pb) != 2)
            return AVERROR_INVALIDDATA;
        avio_skip(pb, 16);
        pos = avio_tell(pb);
        tag = avio_rl32(pb);
    }

    if (tag != MKTAG('.','R','E','C'))
        return AVERROR_INVALIDDATA;

    if (avio_r8(pb) != 0)
        return AVERROR_INVALIDDATA;
    count = avio_rb32(pb);
    for (i = 0; i < count; i++) {
        if (avio_feof(pb))
            return AVERROR_INVALIDDATA;

        type = avio_r8(pb);
        tlen = avio_rb32(pb);
        avio_get_str(pb, tlen, key, sizeof(key));
        len = avio_rb32(pb);
        if (type == 5) {
            avio_get_str(pb, len, val, sizeof(val));
            av_log(s, AV_LOG_DEBUG, "%s = '%s'\n", key, val);
        } else if (type == 4) {
            av_log(s, AV_LOG_DEBUG, "%s = '0x", key);
            
                av_log(s, AV_LOG_DEBUG, "%X", avio_r8(pb));
            av_log(s, AV_LOG_DEBUG, "'\n");
        } else if (len == 4 && type == 3 && !strncmp(key, "StreamCount", tlen)) {
            nb_streams = value = avio_rb32(pb);
        } else if (len == 4 && type == 3) {
            value = avio_rb32(pb);
            av_log(s, AV_LOG_DEBUG, "%s = %d\n", key, value);
        } else {
            av_log(s, AV_LOG_DEBUG, "Skipping unsupported key: %s\n", key);
            avio_skip(pb, len);
        }
    }

    for (n = 0; n < nb_streams; n++) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);
        st->priv_data = ff_rm_alloc_rmstream();
        if (!st->priv_data)
            return AVERROR(ENOMEM);

        if (avio_r8(pb) != 1)
            return AVERROR_INVALIDDATA;

        count = avio_rb32(pb);
        for (i = 0; i < count; i++) {
            if (avio_feof(pb))
                return AVERROR_INVALIDDATA;

            type = avio_r8(pb);
            tlen  = avio_rb32(pb);
            avio_get_str(pb, tlen, key, sizeof(key));
            len  = avio_rb32(pb);
            if (type == 5) {
                avio_get_str(pb, len, val, sizeof(val));
                av_log(s, AV_LOG_DEBUG, "%s = '%s'\n", key, val);
            } else if (type == 4 && !strncmp(key, "OpaqueData", tlen)) {
                ret = ffio_ensure_seekback(pb, 4);
                if (ret < 0)
                    return ret;
                if (avio_rb32(pb) == MKBETAG('M', 'L', 'T', 'I')) {
                    ret = rm_read_multi(s, pb, st, NULL);
                } else {
                    avio_seek(pb, -4, SEEK_CUR);
                    ret = ff_rm_read_mdpr_codecdata(s, pb, st, st->priv_data, len, NULL);
                }

                if (ret < 0)
                    return ret;
            } else if (type == 4) {
                int j;

                av_log(s, AV_LOG_DEBUG, "%s = '0x", key);
                
                    av_log(s, AV_LOG_DEBUG, "%X", avio_r8(pb));
                av_log(s, AV_LOG_DEBUG, "'\n");
            } else if (len == 4 && type == 3 && !strncmp(key, "Duration", tlen)) {
                st->duration = avio_rb32(pb);
            } else if (len == 4 && type == 3) {
                value = avio_rb32(pb);
                av_log(s, AV_LOG_DEBUG, "%s = %d\n", key, value);
            } else {
                av_log(s, AV_LOG_DEBUG, "Skipping unsupported key: %s\n", key);
                avio_skip(pb, len);
            }
        }
    }

    if (avio_r8(pb) != 6)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 12);
    avio_skip(pb, avio_rb64(pb) + pos - avio_tell(s->pb));
    if (avio_r8(pb) != 8)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, 8);

    return 0;
}
static void gmc_mmx(uint8_t *dst, uint8_t *src, /* <=== */ 
                    int stride, int h, int ox, int oy,
                    int dxx, int dxy, int dyx, int dyy,
                    int shift, int r, int width, int height)
{
    const int w    = 8;
    const int ix   = ox  >> (16 + shift);
    const int iy   = oy  >> (16 + shift);
    const int oxs  = ox  >> 4;
    const int oys  = oy  >> 4;
    const int dxxs = dxx >> 4;
    const int dxys = dxy >> 4;
    const int dyxs = dyx >> 4;
    const int dyys = dyy >> 4;
    const uint16_t r4[4]   = { r, r, r, r };
    const uint16_t dxy4[4] = { dxys, dxys, dxys, dxys };
    const uint16_t dyy4[4] = { dyys, dyys, dyys, dyys };
    const uint64_t shift2  = 2 * shift;
#define MAX_STRIDE 4096U
#define MAX_H 8U
    uint8_t edge_buf[(MAX_H + 1) * MAX_STRIDE];
    int x, y;

    const int dxw = (dxx - (1 << (16 + shift))) * (w - 1);
    const int dyh = (dyy - (1 << (16 + shift))) * (h - 1);
    const int dxh = dxy * (h - 1);
    const int dyw = dyx * (w - 1);
    int need_emu  =  (unsigned) ix >= width  - w ||
                     

    if ( // non-constant fullpel offset (3% of blocks)
        ((ox ^ (ox + dxw)) | (ox ^ (ox + dxh)) | (ox ^ (ox + dxw + dxh)) |
         (oy ^ (oy + dyw)) | (oy ^ (oy + dyh)) | (oy ^ (oy + dyw + dyh))) >> (16 + shift) ||
        // uses more than 16 bits of subpel mv (only at huge resolution)
        (dxx | dxy | dyx | dyy) & 15 ||
        (need_emu && (h > MAX_H || stride > MAX_STRIDE))) {
        // FIXME could still use mmx for some of the rows
        ff_gmc_c(dst, src, stride, h, ox, oy, dxx, dxy, dyx, dyy,
                 shift, r, width, height);
        return;
    }

    src += ix + iy * stride;
    if (need_emu) {
        ff_emulated_edge_mc_8(edge_buf, src, stride, stride, w + 1, h + 1, ix, iy, width, height);
        src = edge_buf;
    }

    __asm__ volatile (
        "movd         %0, %%mm6         \n\t"
        "pxor      %%mm7, %%mm7         \n\t"
        "punpcklwd %%mm6, %%mm6         \n\t"
        "punpcklwd %%mm6, %%mm6         \n\t"
        :: "r" (1 << shift));

    for (x = 0; x < w; x += 4) {
        uint16_t dx4[4] = { oxs - dxys + dxxs * (x + 0),
                            oxs - dxys + dxxs * (x + 1),
                            oxs - dxys + dxxs * (x + 2),
                            oxs - dxys + dxxs * (x + 3) };
        uint16_t dy4[4] = { oys - dyys + dyxs * (x + 0),
                            oys - dyys + dyxs * (x + 1),
                            oys - dyys + dyxs * (x + 2),
                            oys - dyys + dyxs * (x + 3) };

        for (y = 0; y < h; y++) {
            __asm__ volatile (
                "movq      %0, %%mm4    \n\t"
                "movq      %1, %%mm5    \n\t"
                "paddw     %2, %%mm4    \n\t"
                "paddw     %3, %%mm5    \n\t"
                "movq   %%mm4, %0       \n\t"
                "movq   %%mm5, %1       \n\t"
                "psrlw    $12, %%mm4    \n\t"
                "psrlw    $12, %%mm5    \n\t"
                : "+m" (*dx4), "+m" (*dy4)
                : "m" (*dxy4), "m" (*dyy4));

            __asm__ volatile (
                "movq      %%mm6, %%mm2 \n\t"
                "movq      %%mm6, %%mm1 \n\t"
                "psubw     %%mm4, %%mm2 \n\t"
                "psubw     %%mm5, %%mm1 \n\t"
                "movq      %%mm2, %%mm0 \n\t"
                "movq      %%mm4, %%mm3 \n\t"
                "pmullw    %%mm1, %%mm0 \n\t" // (s - dx) * (s - dy)
                "pmullw    %%mm5, %%mm3 \n\t" // dx * dy
                "pmullw    %%mm5, %%mm2 \n\t" // (s - dx) * dy
                "pmullw    %%mm4, %%mm1 \n\t" // dx * (s - dy)

                "movd         %4, %%mm5 \n\t"
                "movd         %3, %%mm4 \n\t"
                "punpcklbw %%mm7, %%mm5 \n\t"
                "punpcklbw %%mm7, %%mm4 \n\t"
                "pmullw    %%mm5, %%mm3 \n\t" // src[1, 1] * dx * dy
                "pmullw    %%mm4, %%mm2 \n\t" // src[0, 1] * (s - dx) * dy

                "movd         %2, %%mm5 \n\t"
                "movd         %1, %%mm4 \n\t"
                "punpcklbw %%mm7, %%mm5 \n\t"
                "punpcklbw %%mm7, %%mm4 \n\t"
                "pmullw    %%mm5, %%mm1 \n\t" // src[1, 0] * dx * (s - dy)
                "pmullw    %%mm4, %%mm0 \n\t" // src[0, 0] * (s - dx) * (s - dy)
                "paddw        %5, %%mm1 \n\t"
                "paddw     %%mm3, %%mm2 \n\t"
                "paddw     %%mm1, %%mm0 \n\t"
                "paddw     %%mm2, %%mm0 \n\t"

                "psrlw        %6, %%mm0 \n\t"
                "packuswb  %%mm0, %%mm0 \n\t"
                "movd      %%mm0, %0    \n\t"

                : "=m" (dst[x + y * stride])
                : "m" (src[0]), "m" (src[1]),
                  "m" (src[stride]), "m" (src[stride + 1]),
                  "m" (*r4), "m" (shift2));
            src += stride;
        }
        src += 4 - h * stride;
    }
}
static void gmc_mmx(uint8_t *dst, uint8_t *src, /* <=== */ 
                    int stride, int h, int ox, int oy,
                    int dxx, int dxy, int dyx, int dyy,
                    int shift, int r, int width, int height)
{
    const int w    = 8;
    const int ix   = ox  >> (16 + shift);
    const int iy   = oy  >> (16 + shift);
    const int oxs  = ox  >> 4;
    const int oys  = oy  >> 4;
    const int dxxs = dxx >> 4;
    const int dxys = dxy >> 4;
    const int dyxs = dyx >> 4;
    const int dyys = dyy >> 4;
    const uint16_t r4[4]   = { r, r, r, r };
    const uint16_t dxy4[4] = { dxys, dxys, dxys, dxys };
    const uint16_t dyy4[4] = { dyys, dyys, dyys, dyys };
    const uint64_t shift2  = 2 * shift;
#define MAX_STRIDE 4096U
#define MAX_H 8U
    uint8_t edge_buf[(MAX_H + 1) * MAX_STRIDE];
    int x, y;

    const int dxw = (dxx - (1 << (16 + shift))) * (w - 1);
    const int dyh = (dyy - (1 << (16 + shift))) * (h - 1);
    const int dxh = dxy * (h - 1);
    const int dyw = dyx * (w - 1);
    
                     (unsigned) iy >= height - h;

    if ( // non-constant fullpel offset (3% of blocks)
        ((ox ^ (ox + dxw)) | (ox ^ (ox + dxh)) | (ox ^ (ox + dxw + dxh)) |
         (oy ^ (oy + dyw)) | (oy ^ (oy + dyh)) | (oy ^ (oy + dyw + dyh))) >> (16 + shift) ||
        // uses more than 16 bits of subpel mv (only at huge resolution)
        (dxx | dxy | dyx | dyy) & 15 ||
        (need_emu && (h > MAX_H || stride > MAX_STRIDE))) {
        // FIXME could still use mmx for some of the rows
        ff_gmc_c(dst, src, stride, h, ox, oy, dxx, dxy, dyx, dyy,
                 shift, r, width, height);
        return;
    }

    src += ix + iy * stride;
    if (need_emu) {
        ff_emulated_edge_mc_8(edge_buf, src, stride, stride, w + 1, h + 1, ix, iy, width, height);
        src = edge_buf;
    }

    __asm__ volatile (
        "movd         %0, %%mm6         \n\t"
        "pxor      %%mm7, %%mm7         \n\t"
        "punpcklwd %%mm6, %%mm6         \n\t"
        "punpcklwd %%mm6, %%mm6         \n\t"
        :: "r" (1 << shift));

    for (x = 0; x < w; x += 4) {
        uint16_t dx4[4] = { oxs - dxys + dxxs * (x + 0),
                            oxs - dxys + dxxs * (x + 1),
                            oxs - dxys + dxxs * (x + 2),
                            oxs - dxys + dxxs * (x + 3) };
        uint16_t dy4[4] = { oys - dyys + dyxs * (x + 0),
                            oys - dyys + dyxs * (x + 1),
                            oys - dyys + dyxs * (x + 2),
                            oys - dyys + dyxs * (x + 3) };

        for (y = 0; y < h; y++) {
            __asm__ volatile (
                "movq      %0, %%mm4    \n\t"
                "movq      %1, %%mm5    \n\t"
                "paddw     %2, %%mm4    \n\t"
                "paddw     %3, %%mm5    \n\t"
                "movq   %%mm4, %0       \n\t"
                "movq   %%mm5, %1       \n\t"
                "psrlw    $12, %%mm4    \n\t"
                "psrlw    $12, %%mm5    \n\t"
                : "+m" (*dx4), "+m" (*dy4)
                : "m" (*dxy4), "m" (*dyy4));

            __asm__ volatile (
                "movq      %%mm6, %%mm2 \n\t"
                "movq      %%mm6, %%mm1 \n\t"
                "psubw     %%mm4, %%mm2 \n\t"
                "psubw     %%mm5, %%mm1 \n\t"
                "movq      %%mm2, %%mm0 \n\t"
                "movq      %%mm4, %%mm3 \n\t"
                "pmullw    %%mm1, %%mm0 \n\t" // (s - dx) * (s - dy)
                "pmullw    %%mm5, %%mm3 \n\t" // dx * dy
                "pmullw    %%mm5, %%mm2 \n\t" // (s - dx) * dy
                "pmullw    %%mm4, %%mm1 \n\t" // dx * (s - dy)

                "movd         %4, %%mm5 \n\t"
                "movd         %3, %%mm4 \n\t"
                "punpcklbw %%mm7, %%mm5 \n\t"
                "punpcklbw %%mm7, %%mm4 \n\t"
                "pmullw    %%mm5, %%mm3 \n\t" // src[1, 1] * dx * dy
                "pmullw    %%mm4, %%mm2 \n\t" // src[0, 1] * (s - dx) * dy

                "movd         %2, %%mm5 \n\t"
                "movd         %1, %%mm4 \n\t"
                "punpcklbw %%mm7, %%mm5 \n\t"
                "punpcklbw %%mm7, %%mm4 \n\t"
                "pmullw    %%mm5, %%mm1 \n\t" // src[1, 0] * dx * (s - dy)
                "pmullw    %%mm4, %%mm0 \n\t" // src[0, 0] * (s - dx) * (s - dy)
                "paddw        %5, %%mm1 \n\t"
                "paddw     %%mm3, %%mm2 \n\t"
                "paddw     %%mm1, %%mm0 \n\t"
                "paddw     %%mm2, %%mm0 \n\t"

                "psrlw        %6, %%mm0 \n\t"
                "packuswb  %%mm0, %%mm0 \n\t"
                "movd      %%mm0, %0    \n\t"

                : "=m" (dst[x + y * stride])
                : "m" (src[0]), "m" (src[1]),
                  "m" (src[stride]), "m" (src[stride + 1]),
                  "m" (*r4), "m" (shift2));
            src += stride;
        }
        src += 4 - h * stride;
    }
}
static av_cold int vc2_encode_init(AVCodecContext *avctx) /* <=== */ 
{
    Plane *p;
    SubBand *b;
    int i, j, level, o, shift;
    int64_t bits_per_frame, min_bits_per_frame;
    VC2EncContext *s = avctx->priv_data;

    s->picture_number = 0;

    /* Total allowed quantization range */
    s->q_ceil    = MAX_QUANT_INDEX;

    s->ver.major = 2;
    s->ver.minor = 0;
    s->profile   = 3;
    s->level     = 3;

    s->base_vf   = -1;
    s->strict_compliance = 1;

    s->q_avg = 0;

    /* Mark unknown as progressive */
    s->interlaced = !((avctx->field_order == AV_FIELD_UNKNOWN) ||
                      (avctx->field_order == AV_FIELD_PROGRESSIVE));

    if (avctx->pix_fmt == AV_PIX_FMT_YUV422P10) {
        if (avctx->width == 1280 && avctx->height == 720) {
            s->level = 3;
            if (avctx->time_base.num == 1001 && avctx->time_base.den == 60000)
                s->base_vf = 9;
            if (avctx->time_base.num == 1 && avctx->time_base.den == 50)
                s->base_vf = 10;
        } else if (avctx->width == 1920 && avctx->height == 1080) {
            s->level = 3;
            if (s->interlaced) {
                if (avctx->time_base.num == 1001 && avctx->time_base.den == 30000)
                    s->base_vf = 11;
                if (avctx->time_base.num == 1 && avctx->time_base.den == 50)
                    s->base_vf = 12;
            } else {
                if (avctx->time_base.num == 1001 && avctx->time_base.den == 60000)
                    s->base_vf = 13;
                if (avctx->time_base.num == 1 && avctx->time_base.den == 50)
                    s->base_vf = 14;
                if (avctx->time_base.num == 1001 && avctx->time_base.den == 24000)
                    s->base_vf = 21;
            }
        } else if (avctx->width == 3840 && avctx->height == 2160) {
            s->level = 6;
            if (avctx->time_base.num == 1001 && avctx->time_base.den == 60000)
                s->base_vf = 17;
            if (avctx->time_base.num == 1 && avctx->time_base.den == 50)
                s->base_vf = 18;
        }
    }

    if (s->interlaced && s->base_vf <= 0) {
        av_log(avctx, AV_LOG_ERROR, "Interlacing not supported with non standard formats!\n");
        return AVERROR_UNKNOWN;
    }

    if (s->interlaced)
        av_log(avctx, AV_LOG_WARNING, "Interlacing enabled!\n");

    if ((s->slice_width  & (s->slice_width  - 1)) ||
        (s->slice_height & (s->slice_height - 1))) {
        av_log(avctx, AV_LOG_ERROR, "Slice size is not a power of two!\n");
        return AVERROR_UNKNOWN;
    }

    if ((s->slice_width > avctx->width) ||
        (s->slice_height > avctx->height)) {
        av_log(avctx, AV_LOG_ERROR, "Slice size is bigger than the image!\n");
        return AVERROR_UNKNOWN;
    }

    if (s->base_vf <= 0) {
        if (avctx->strict_std_compliance <= FF_COMPLIANCE_UNOFFICIAL) {
            s->strict_compliance = s->base_vf = 0;
            av_log(avctx, AV_LOG_WARNING, "Disabling strict compliance\n");
        } else {
            av_log(avctx, AV_LOG_WARNING, "Given format does not strictly comply with "
                   "the specifications, please add a -strict -1 flag to use it\n");
            return AVERROR_UNKNOWN;
        }
    } else {
        av_log(avctx, AV_LOG_INFO, "Selected base video format = %i\n", s->base_vf);
    }

    avcodec_get_chroma_sub_sample(avctx->pix_fmt, &s->chroma_x_shift, &s->chroma_y_shift);

    /* Planes initialization */
    for (i = 0; i < 3; i++) {
        int w, h;
        p = &s->plane[i];
        p->width      = avctx->width  >> (i ? s->chroma_x_shift : 0);
        p->height     = avctx->height >> (i ? s->chroma_y_shift : 0);
        if (s->interlaced)
            p->height >>= 1;
        p->dwt_width  = w = FFALIGN(p->width,  (1 << s->wavelet_depth));
        p->dwt_height = h = FFALIGN(p->height, (1 << s->wavelet_depth));
        p->coef_stride = FFALIGN(p->dwt_width, 32);
        p->coef_buf = av_malloc(p->coef_stride*p->dwt_height*sizeof(dwtcoef));
        if (!p->coef_buf)
            goto alloc_fail;
        for (level = s->wavelet_depth-1; level >= 0; level--) {
            w = w >> 1;
            h = h >> 1;
            for (o = 0; o < 4; o++) {
                b = &p->band[level][o];
                b->width  = w;
                b->height = h;
                b->stride = p->coef_stride;
                shift = (o > 1)*b->height*b->stride + (o & 1)*b->width;
                b->buf = p->coef_buf + shift;
            }
        }

        /* DWT init */
        if (ff_vc2enc_init_transforms(&s->transform_args[i].t,
                                      s->plane[i].coef_stride,
                                      
            goto alloc_fail;
    }

    /* Slices */
    s->num_x = s->plane[0].dwt_width/s->slice_width;
    s->num_y = s->plane[0].dwt_height/s->slice_height;

    s->slice_args = av_malloc(s->num_x*s->num_y*sizeof(SliceArgs));
    if (!s->slice_args)
        goto alloc_fail;

    /* Lookup tables */
    s->coef_lut_len = av_malloc(COEF_LUT_TAB*s->q_ceil*sizeof(*s->coef_lut_len));
    if (!s->coef_lut_len)
        goto alloc_fail;

    s->coef_lut_val = av_malloc(COEF_LUT_TAB*s->q_ceil*sizeof(*s->coef_lut_val));
    if (!s->coef_lut_val)
        goto alloc_fail;

    for (i = 0; i < s->q_ceil; i++) {
        for (j = 0; j < COEF_LUT_TAB; j++) {
            uint8_t  *len_lut = &s->coef_lut_len[i*COEF_LUT_TAB];
            uint32_t *val_lut = &s->coef_lut_val[i*COEF_LUT_TAB];
            get_vc2_ue_uint(QUANT(j, ff_dirac_qscale_tab[i]),
                            &len_lut[j], &val_lut[j]);
        }
    }

    bits_per_frame = av_rescale(avctx->bit_rate, avctx->time_base.num,
                                 avctx->time_base.den);
    min_bits_per_frame = minimum_frame_bits(s) + 8*sizeof(LIBAVCODEC_IDENT) + 8*40 + 8*20000;
    if (bits_per_frame < min_bits_per_frame) {
        avctx->bit_rate = av_rescale(min_bits_per_frame, avctx->time_base.den,
                                     avctx->time_base.num);
        av_log(avctx, AV_LOG_WARNING,
               "Bitrate too low, clipping to minimum = %li Mbps!\n",
               avctx->bit_rate/1000000);
    }

    return 0;

alloc_fail:
    vc2_encode_end(avctx);
    av_log(avctx, AV_LOG_ERROR, "Unable to allocate memory!\n");
    return AVERROR(ENOMEM);
}
av_cold int ff_vc2enc_init_transforms(VC2TransformContext *s, int p_width, int p_height) /* <=== */ 
{
    s->vc2_subband_dwt[VC2_TRANSFORM_9_7]    = vc2_subband_dwt_97;
    s->vc2_subband_dwt[VC2_TRANSFORM_5_3]    = vc2_subband_dwt_53;

    
    if (!s->buffer)
        return 1;

    return 0;
}
av_cold int ff_vc2enc_init_transforms(VC2TransformContext *s, int p_width, int p_height) /* <=== */ 
{
    s->vc2_subband_dwt[VC2_TRANSFORM_9_7]    = vc2_subband_dwt_97;
    s->vc2_subband_dwt[VC2_TRANSFORM_5_3]    = vc2_subband_dwt_53;

    
    if (!s->buffer)
        return 1;

    return 0;
}
av_cold void ff_vc2enc_free_transforms(VC2TransformContext *s) /* <=== */ 
{
    
}
av_cold void ff_vc2enc_free_transforms(VC2TransformContext *s) /* <=== */ 
{
    
}
static int mxf_read_primer_pack(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset) /* <=== */ 
{
    MXFContext *mxf = arg;
    int item_num = avio_rb32(pb);
    int item_len = avio_rb32(pb);

    if (item_len != 18) {
        av_log_ask_for_sample(pb, "unsupported primer pack item length %d\n",
                              item_len);
        return AVERROR_PATCHWELCOME;
    }
    
        av_log(mxf->fc, AV_LOG_ERROR, "item_num %d is too large\n", item_num);
        return AVERROR_INVALIDDATA;
    }
    mxf->local_tags = av_calloc(item_num, item_len);
    if (!mxf->local_tags)
        return AVERROR(ENOMEM);
    mxf->local_tags_count = item_num;
    avio_read(pb, mxf->local_tags, item_num*item_len);
    return 0;
}
static int mxf_read_primer_pack(void *arg, AVIOContext *pb, int tag, int size, UID uid) /* <=== */ 
{
    MXFContext *mxf = arg;
    int item_num = avio_rb32(pb);
    int item_len = avio_rb32(pb);

    if (item_len != 18) {
        av_log(mxf->fc, AV_LOG_ERROR, "unsupported primer pack item length\n");
        return -1;
    }
    if (item_num > UINT_MAX / item_len)
        return -1;
    mxf->local_tags_count = item_num;
    mxf->local_tags = av_malloc(item_num*item_len);
    if (!mxf->local_tags)
        return -1;
    avio_read(pb, mxf->local_tags, item_num*item_len);
    return 0;
}
int ff_mpeg_er_init(MpegEncContext *s) /* <=== */ 
{
    ERContext *er = &s->er;
    int mb_array_size = s->mb_height * s->mb_stride;
    int i;

    er->avctx       = s->avctx;

    er->mb_index2xy = s->mb_index2xy;
    er->mb_num      = s->mb_num;
    er->mb_width    = s->mb_width;
    er->mb_height   = s->mb_height;
    er->mb_stride   = s->mb_stride;
    er->b8_stride   = s->b8_stride;

    
    er->error_status_table = av_mallocz(mb_array_size);
    if (!er->er_temp_buffer || !er->error_status_table)
        goto fail;

    er->mbskip_table  = s->mbskip_table;
    er->mbintra_table = s->mbintra_table;

    for (i = 0; i < FF_ARRAY_ELEMS(s->dc_val); i++)
        er->dc_val[i] = s->dc_val[i];

    er->decode_mb = mpeg_er_decode_mb;
    er->opaque    = s;

    return 0;
fail:
    av_freep(&er->er_temp_buffer);
    av_freep(&er->error_status_table);
    return AVERROR(ENOMEM);
}
int ff_mpeg_er_init(MpegEncContext *s) /* <=== */ 
{
    ERContext *er = &s->er;
    int mb_array_size = s->mb_height * s->mb_stride;
    int i;

    er->avctx       = s->avctx;

    er->mb_index2xy = s->mb_index2xy;
    er->mb_num      = s->mb_num;
    er->mb_width    = s->mb_width;
    er->mb_height   = s->mb_height;
    er->mb_stride   = s->mb_stride;
    er->b8_stride   = s->b8_stride;

    
    er->error_status_table = av_mallocz(mb_array_size);
    if (!er->er_temp_buffer || !er->error_status_table)
        goto fail;

    er->mbskip_table  = s->mbskip_table;
    er->mbintra_table = s->mbintra_table;

    for (i = 0; i < FF_ARRAY_ELEMS(s->dc_val); i++)
        er->dc_val[i] = s->dc_val[i];

    er->decode_mb = mpeg_er_decode_mb;
    er->opaque    = s;

    return 0;
fail:
    av_freep(&er->er_temp_buffer);
    av_freep(&er->error_status_table);
    return AVERROR(ENOMEM);
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x = 0, prev_y = 0, prev_ref = 0;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy] && 0) {
                        if (s->avctx->codec_id == AV_CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress(s->last_pic.tf,
                                                     mb_y, 0);
                        }
                        if (!s->last_pic.motion_val[0] ||
                            !s->last_pic.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_pic.motion_val[0][mot_index][0];
                        prev_y   = s->last_pic.motion_val[0][mot_index][1];
                        prev_ref = s->last_pic.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                        prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                        prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:

                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x = 0, prev_y = 0, prev_ref = 0;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    
                    int ref[8];
                    int pred_count;
                    int j;
                    int best_score;
                    int best_pred;
                    int mot_index;
                    int prev_x, prev_y, prev_ref;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2];
                    
                    int pred_count;
                    int j;
                    int best_score;
                    int best_pred;
                    int mot_index;
                    int prev_x, prev_y, prev_ref;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2];
                    int ref[8];
                    
                    int j;
                    int best_score;
                    int best_pred;
                    int mot_index;
                    int prev_x, prev_y, prev_ref;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(MpegEncContext *s){ /* <=== */ 
    UINT8 fixed[s->mb_num];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_width = s->mb_width;
    const int mb_height= s->mb_height;
    int i, depth, num_avail;
   
    num_avail=0;
    for(i=0; i<s->mb_num; i++){
        int f=0;
        int error= s->error_status_table[i];

        if(s->mb_type[i]&MB_TYPE_INTRA) f=MV_FROZEN; //intra //FIXME check
        if(!(error&MV_ERROR)) f=MV_FROZEN;           //inter with undamaged MV
        
        fixed[i]= f;
        if(f==MV_FROZEN)
            num_avail++;
    }
    
    if((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) || num_avail <= mb_width/2){
        int mb_x, mb_y;
        i= -1;
        for(mb_y=0; mb_y<s->mb_height; mb_y++){
            for(mb_x=0; mb_x<s->mb_width; mb_x++){
                i++;
                
                if(s->mb_type[i]&MB_TYPE_INTRA) continue;
                if(!(s->error_status_table[i]&MV_ERROR)) continue;

                s->mv_dir = MV_DIR_FORWARD;
                s->mb_intra=0;
                s->mv_type = MV_TYPE_16X16;
                s->mb_skiped=0;

                clear_blocks(s->block[0]);

                s->mb_x= mb_x;
                s->mb_y= mb_y;
                s->mv[0][0][0]= 0;
                s->mv[0][0][1]= 0;
                MPV_decode_mb(s, s->block);
            }
        }
        return;
    }
    
    for(depth=0;; depth++){
        int changed, pass, none_left;

        none_left=1;
        changed=1;
        for(pass=0; (changed || pass<2) && pass<10; pass++){
            int i,mb_x, mb_y;
int score_sum=0;
 
            changed=0;
            i= -1;
            for(mb_y=0; mb_y<s->mb_height; mb_y++){
                for(mb_x=0; mb_x<s->mb_width; mb_x++){
                    int mv_predictor[8][2]={{0}};
                    int pred_count=0;
                    
                    int best_score=256*256*256*64;
                    int best_pred=0;
                    const int mot_stride= mb_width*2+2;
                    const int mot_index= mb_x*2 + 1 + (mb_y*2+1)*mot_stride;
                    int prev_x= s->motion_val[mot_index][0];
                    int prev_y= s->motion_val[mot_index][1];

                    i++;
                    if((mb_x^mb_y^pass)&1) continue;
                    
                    if(fixed[i]==MV_FROZEN) continue;
                    
                    j=0;
                    if(mb_x>0           && fixed[i-1       ]==MV_FROZEN) j=1;
                    if(mb_x+1<mb_width  && fixed[i+1       ]==MV_FROZEN) j=1;
                    if(mb_y>0           && fixed[i-mb_width]==MV_FROZEN) j=1;
                    if(mb_y+1<mb_height && fixed[i+mb_width]==MV_FROZEN) j=1;
                    if(j==0) continue;

                    j=0;
                    if(mb_x>0           && fixed[i-1       ]==MV_CHANGED) j=1;
                    if(mb_x+1<mb_width  && fixed[i+1       ]==MV_CHANGED) j=1;
                    if(mb_y>0           && fixed[i-mb_width]==MV_CHANGED) j=1;
                    if(mb_y+1<mb_height && fixed[i+mb_width]==MV_CHANGED) j=1;
                    if(j==0 && pass>1) continue;
                    
                    none_left=0;
                    
                    if(mb_x>0 && fixed[i-1]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index - 2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index - 2][1];
                        pred_count++;
                    }
                    if(mb_x+1<mb_width && fixed[i+1]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index + 2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index + 2][1];
                        pred_count++;
                    }
                    if(mb_y>0 && fixed[i-mb_width]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index - mot_stride*2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index - mot_stride*2][1];
                        pred_count++;
                    }
                    if(mb_y+1<mb_height && fixed[i+mb_width]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index + mot_stride*2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index + mot_stride*2][1];
                        pred_count++;
                    }
                    if(pred_count==0) continue;
                    
                    if(pred_count>1){
                        int sum_x=0, sum_y=0;
                        int max_x, max_y, min_x, min_y;

                        for(j=0; j<pred_count; j++){
                            sum_x+= mv_predictor[j][0];
                            sum_y+= mv_predictor[j][1];
                        }
                    
                        /* mean */
                        mv_predictor[pred_count][0] = sum_x/j;
                        mv_predictor[pred_count][1] = sum_y/j;
                    
                        /* median */
                        if(pred_count>=3){
                            min_y= min_x= 99999;
                            max_y= max_x=-99999;
                        }else{
                            min_x=min_y=max_x=max_y=0;
                        }
                        for(j=0; j<pred_count; j++){
                            max_x= MAX(max_x, mv_predictor[j][0]);
                            max_y= MAX(max_y, mv_predictor[j][1]);
                            min_x= MIN(min_x, mv_predictor[j][0]);
                            min_y= MIN(min_y, mv_predictor[j][1]);
                        }
                        mv_predictor[pred_count+1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count+1][1] = sum_y - max_y - min_y;
                        
                        if(pred_count==4){
                            mv_predictor[pred_count+1][0] /= 2;
                            mv_predictor[pred_count+1][1] /= 2;
                        }
                        pred_count+=2;
                    }
                    
                    /* zero MV */
                    pred_count++;

                    /* last MV */
                    mv_predictor[pred_count][0]= s->motion_val[mot_index][0];
                    mv_predictor[pred_count][1]= s->motion_val[mot_index][1];
                    pred_count++;                    
                    
                    s->mv_dir = MV_DIR_FORWARD;
                    s->mb_intra=0;
                    s->mv_type = MV_TYPE_16X16;
                    s->mb_skiped=0;

                    clear_blocks(s->block[0]);

                    s->mb_x= mb_x;
                    s->mb_y= mb_y;
                    for(j=0; j<pred_count; j++){
                        int score=0;
                        UINT8 *src= s->current_picture[0] + mb_x*16 + mb_y*16*s->linesize;

                        s->motion_val[mot_index][0]= s->mv[0][0][0]= mv_predictor[j][0];
                        s->motion_val[mot_index][1]= s->mv[0][0][1]= mv_predictor[j][1];
                        MPV_decode_mb(s, s->block);
                        
                        if(mb_x>0 && fixed[i-1]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k*s->linesize-1 ]-src[k*s->linesize   ]);
                        }
                        if(mb_x+1<mb_width && fixed[i+1]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k*s->linesize+15]-src[k*s->linesize+16]);
                        }
                        if(mb_y>0 && fixed[i-mb_width]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k-s->linesize   ]-src[k               ]);
                        }
                        if(mb_y+1<mb_height && fixed[i+mb_width]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k+s->linesize*15]-src[k+s->linesize*16]);
                        }
                        
                        if(score <= best_score){ // <= will favor the last MV
                            best_score= score;
                            best_pred= j;
                        }
                    }
score_sum+= best_score;
//FIXME no need to set s->motion_val[mot_index][0] explicit
                    s->motion_val[mot_index][0]= s->mv[0][0][0]= mv_predictor[best_pred][0];
                    s->motion_val[mot_index][1]= s->mv[0][0][1]= mv_predictor[best_pred][1];

                    MPV_decode_mb(s, s->block);

                    
                    if(s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y){
                        fixed[i]=MV_CHANGED;
                        changed++;
                    }else
                        fixed[i]=MV_UNCHANGED;
                }
            }

//            printf(".%d/%d", changed, score_sum); fflush(stdout);
        }
        
        if(none_left) 
            return;
            
        for(i=0; i<s->mb_num; i++){
            if(fixed[i])
                fixed[i]=MV_FROZEN;
        }
//        printf(":"); fflush(stdout);
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2];
                    int ref[8];
                    int pred_count;
                    int j;
                    
                    int best_pred;
                    int mot_index;
                    int prev_x, prev_y, prev_ref;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2];
                    int ref[8];
                    int pred_count;
                    int j;
                    int best_score;
                    
                    int mot_index;
                    int prev_x, prev_y, prev_ref;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2];
                    int ref[8];
                    int pred_count;
                    int j;
                    int best_score;
                    int best_pred;
                    
                    int prev_x, prev_y, prev_ref;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2];
                    int ref[8];
                    int pred_count;
                    int j;
                    int best_score;
                    int best_pred;
                    int mot_index;
                    

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;
                    pred_count = 0;
                    mot_index  = (mb_x + mb_y * mot_stride) * mot_step;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    mv_predictor[pred_count][0] =
                    mv_predictor[pred_count][1] =
                             ref[pred_count]    = 0;
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    best_pred = 0;
                    best_score = 256 * 256 * 256 * 64;
                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        

                    if (fixed[mb_xy] == MV_FROZEN)
                        
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;
#define MV_FROZEN    4
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x = 0, prev_y = 0, prev_ref = 0;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        

                    if (fixed[mb_xy] == MV_FROZEN)
                        
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(ERContext *s) /* <=== */ 
{
    uint8_t *fixed = s->er_temp_buffer;

#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    if (s->last_pic.f && s->last_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->last_pic.f->height+15)>>4);
    if (s->next_pic.f && s->next_pic.f->data[0])
        mb_height = FFMIN(mb_height, (s->next_pic.f->height+15)>>4);

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    if (s->last_pic.motion_val[0])
        ff_thread_await_progress(s->last_pic.tf, mb_height-1, 0);
    for (i = 0; i < mb_width * mb_height; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
        else if(s->last_pic.f->data[0] && s->last_pic.motion_val[0]){
            const int mb_y= mb_xy / s->mb_stride;
            const int mb_x= mb_xy % s->mb_stride;
            const int mot_index= (mb_x + mb_y*mot_stride) * mot_step;
            s->cur_pic.motion_val[0][mot_index][0]= s->last_pic.motion_val[0][mot_index][0];
            s->cur_pic.motion_val[0][mot_index][1]= s->last_pic.motion_val[0][mot_index][1];
            s->cur_pic.ref_index[0][4*mb_xy]      = s->last_pic.ref_index[0][4*mb_xy];
        }
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;
                int mv_dir = (s->last_pic.f && s->last_pic.f->data[0]) ? MV_DIR_FORWARD : MV_DIR_BACKWARD;

                if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                s->decode_mb(s->opaque, 0, mv_dir, MV_TYPE_16X16, &s->mv,
                             mb_x, mb_y, 0, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < mb_height; mb_y++) {
                for (mb_x = (mb_y ^ pass) & 1; mb_x < s->mb_width; mb_x+=2) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x = 0, prev_y = 0, prev_ref = 0;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    av_assert1(!IS_INTRA(s->cur_pic.mb_type[mb_xy]));
                    av_assert1(s->last_pic.f && s->last_pic.f->data[0]);

                    j = 0;
                    if (mb_x > 0)
                        j |= fixed[mb_xy - 1];
                    if (mb_x + 1 < mb_width)
                        j |= fixed[mb_xy + 1];
                    if (mb_y > 0)
                        j |= fixed[mb_xy - mb_stride];
                    if (mb_y + 1 < mb_height)
                        j |= fixed[mb_xy + mb_stride];

                    if (!(j & MV_FROZEN))
                        continue;

                    if (!(j & MV_CHANGED) && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->cur_pic.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->cur_pic.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    prev_x   = s->cur_pic.motion_val[0][mot_index][0];
                    prev_y   = s->cur_pic.motion_val[0][mot_index][1];
                    prev_ref = s->cur_pic.ref_index[0][4 * mb_xy];

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

                    for (j = 0; j < pred_count; j++) {
                        int *linesize = s->cur_pic.f->linesize;
                        int score = 0;
                        uint8_t *src = s->cur_pic.f->data[0] +
                                       mb_x * 16 + mb_y * 16 * linesize[0];

                        s->cur_pic.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->cur_pic.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        s->decode_mb(s->opaque, ref[j], MV_DIR_FORWARD,
                                     MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] - 1] -
                                               src[k * linesize[0]]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * linesize[0] + 15] -
                                               src[k * linesize[0] + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - linesize[0]] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + linesize[0] * 15] -
                                               src[k + linesize[0] * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->cur_pic.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    s->decode_mb(s->opaque, ref[best_pred], MV_DIR_FORWARD,
                                 MV_TYPE_16X16, &s->mv, mb_x, mb_y, 0, 0);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }
        }

        if (none_left)
            return;

        for (i = 0; i < mb_width * mb_height; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            s->mb_x = 0;
            s->mb_y = mb_y;
            ff_init_block_index(s);
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                ff_update_block_index(s);

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                s->mb_x = 0;
                s->mb_y = mb_y;
                ff_init_block_index(s);
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    ff_update_block_index(s);

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress(&s->last_picture_ptr->f,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s) /* <=== */ 
{
    uint8_t fixed[s->mb_stride * s->mb_height];
#define MV_FROZEN    3
#define MV_CHANGED   2
#define MV_UNCHANGED 1
    const int mb_stride = s->mb_stride;
    const int mb_width  = s->mb_width;
    const int mb_height = s->mb_height;
    int i, depth, num_avail;
    int mb_x, mb_y, mot_step, mot_stride;

    set_mv_strides(s, &mot_step, &mot_stride);

    num_avail = 0;
    for (i = 0; i < s->mb_num; i++) {
        const int mb_xy = s->mb_index2xy[i];
        int f = 0;
        int error = s->error_status_table[mb_xy];

        if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
            f = MV_FROZEN; // intra // FIXME check
        if (!(error & ER_MV_ERROR))
            f = MV_FROZEN; // inter with undamaged MV

        fixed[mb_xy] = f;
        if (f == MV_FROZEN)
            num_avail++;
    }

    if ((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) ||
        num_avail <= mb_width / 2) {
        for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
            for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                const int mb_xy = mb_x + mb_y * s->mb_stride;

                if (IS_INTRA(s->current_picture.f.mb_type[mb_xy]))
                    continue;
                if (!(s->error_status_table[mb_xy] & ER_MV_ERROR))
                    continue;

                s->mv_dir     = s->last_picture.f.data[0] ? MV_DIR_FORWARD
                                                          : MV_DIR_BACKWARD;
                s->mb_intra   = 0;
                s->mv_type    = MV_TYPE_16X16;
                s->mb_skipped = 0;

                s->dsp.clear_blocks(s->block[0]);

                s->mb_x        = mb_x;
                s->mb_y        = mb_y;
                s->mv[0][0][0] = 0;
                s->mv[0][0][1] = 0;
                decode_mb(s, 0);
            }
        }
        return;
    }

    for (depth = 0; ; depth++) {
        int changed, pass, none_left;

        none_left = 1;
        changed   = 1;
        for (pass = 0; (changed || pass < 2) && pass < 10; pass++) {
            int mb_x, mb_y;
            int score_sum = 0;

            changed = 0;
            for (mb_y = 0; mb_y < s->mb_height; mb_y++) {
                for (mb_x = 0; mb_x < s->mb_width; mb_x++) {
                    const int mb_xy        = mb_x + mb_y * s->mb_stride;
                    int mv_predictor[8][2] = { { 0 } };
                    int ref[8]             = { 0 };
                    int pred_count         = 0;
                    int j;
                    int best_score         = 256 * 256 * 256 * 64;
                    int best_pred          = 0;
                    const int mot_index    = (mb_x + mb_y * mot_stride) * mot_step;
                    int prev_x, prev_y, prev_ref;

                    if ((mb_x ^ mb_y ^ pass) & 1)
                        continue;

                    if (fixed[mb_xy] == MV_FROZEN)
                        continue;
                    assert(!IS_INTRA(s->current_picture.f.mb_type[mb_xy]));
                    assert(s->last_picture_ptr && s->last_picture_ptr->f.data[0]);

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1]         == MV_FROZEN)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_FROZEN)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_FROZEN)
                        j = 1;
                    if (j == 0)
                        continue;

                    j = 0;
                    if (mb_x > 0             && fixed[mb_xy - 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_x + 1 < mb_width  && fixed[mb_xy + 1        ] == MV_CHANGED)
                        j = 1;
                    if (mb_y > 0             && fixed[mb_xy - mb_stride] == MV_CHANGED)
                        j = 1;
                    if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride] == MV_CHANGED)
                        j = 1;
                    if (j == 0 && pass > 1)
                        continue;

                    none_left = 0;

                    if (mb_x > 0 && fixed[mb_xy - 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - 1)];
                        pred_count++;
                    }
                    if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + 1)];
                        pred_count++;
                    }
                    
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index - mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy - s->mb_stride)];
                        pred_count++;
                    }
                    if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
                        mv_predictor[pred_count][0] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][0];
                        mv_predictor[pred_count][1] =
                            s->current_picture.f.motion_val[0][mot_index + mot_stride * mot_step][1];
                        ref[pred_count] =
                            s->current_picture.f.ref_index[0][4 * (mb_xy + s->mb_stride)];
                        pred_count++;
                    }
                    if (pred_count == 0)
                        continue;

                    if (pred_count > 1) {
                        int sum_x = 0, sum_y = 0, sum_r = 0;
                        int max_x, max_y, min_x, min_y, max_r, min_r;

                        for (j = 0; j < pred_count; j++) {
                            sum_x += mv_predictor[j][0];
                            sum_y += mv_predictor[j][1];
                            sum_r += ref[j];
                            if (j && ref[j] != ref[j - 1])
                                goto skip_mean_and_median;
                        }

                        /* mean */
                        mv_predictor[pred_count][0] = sum_x / j;
                        mv_predictor[pred_count][1] = sum_y / j;
                                 ref[pred_count]    = sum_r / j;

                        /* median */
                        if (pred_count >= 3) {
                            min_y = min_x = min_r =  99999;
                            max_y = max_x = max_r = -99999;
                        } else {
                            min_x = min_y = max_x = max_y = min_r = max_r = 0;
                        }
                        for (j = 0; j < pred_count; j++) {
                            max_x = FFMAX(max_x, mv_predictor[j][0]);
                            max_y = FFMAX(max_y, mv_predictor[j][1]);
                            max_r = FFMAX(max_r, ref[j]);
                            min_x = FFMIN(min_x, mv_predictor[j][0]);
                            min_y = FFMIN(min_y, mv_predictor[j][1]);
                            min_r = FFMIN(min_r, ref[j]);
                        }
                        mv_predictor[pred_count + 1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count + 1][1] = sum_y - max_y - min_y;
                                 ref[pred_count + 1]    = sum_r - max_r - min_r;

                        if (pred_count == 4) {
                            mv_predictor[pred_count + 1][0] /= 2;
                            mv_predictor[pred_count + 1][1] /= 2;
                                     ref[pred_count + 1]    /= 2;
                        }
                        pred_count += 2;
                    }

skip_mean_and_median:
                    /* zero MV */
                    pred_count++;

                    if (!fixed[mb_xy]) {
                        if (s->avctx->codec_id == CODEC_ID_H264) {
                            // FIXME
                        } else {
                            ff_thread_await_progress((AVFrame *) s->last_picture_ptr,
                                                     mb_y, 0);
                        }
                        if (!s->last_picture.f.motion_val[0] ||
                            !s->last_picture.f.ref_index[0])
                            goto skip_last_mv;
                        prev_x   = s->last_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->last_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->last_picture.f.ref_index[0][4 * mb_xy];
                    } else {
                        prev_x   = s->current_picture.f.motion_val[0][mot_index][0];
                        prev_y   = s->current_picture.f.motion_val[0][mot_index][1];
                        prev_ref = s->current_picture.f.ref_index[0][4 * mb_xy];
                    }

                    /* last MV */
                    mv_predictor[pred_count][0] = prev_x;
                    mv_predictor[pred_count][1] = prev_y;
                             ref[pred_count]    = prev_ref;
                    pred_count++;

skip_last_mv:
                    s->mv_dir     = MV_DIR_FORWARD;
                    s->mb_intra   = 0;
                    s->mv_type    = MV_TYPE_16X16;
                    s->mb_skipped = 0;

                    s->dsp.clear_blocks(s->block[0]);

                    s->mb_x = mb_x;
                    s->mb_y = mb_y;

                    for (j = 0; j < pred_count; j++) {
                        int score = 0;
                        uint8_t *src = s->current_picture.f.data[0] +
                                       mb_x * 16 + mb_y * 16 * s->linesize;

                        s->current_picture.f.motion_val[0][mot_index][0] =
                            s->mv[0][0][0] = mv_predictor[j][0];
                        s->current_picture.f.motion_val[0][mot_index][1] =
                            s->mv[0][0][1] = mv_predictor[j][1];

                        // predictor intra or otherwise not available
                        if (ref[j] < 0)
                            continue;

                        decode_mb(s, ref[j]);

                        if (mb_x > 0 && fixed[mb_xy - 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize - 1] -
                                               src[k * s->linesize]);
                        }
                        if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k * s->linesize + 15] -
                                               src[k * s->linesize + 16]);
                        }
                        
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k - s->linesize] - src[k]);
                        }
                        if (mb_y + 1 < mb_height && fixed[mb_xy + mb_stride]) {
                            int k;
                            for (k = 0; k < 16; k++)
                                score += FFABS(src[k + s->linesize * 15] -
                                               src[k + s->linesize * 16]);
                        }

                        if (score <= best_score) { // <= will favor the last MV
                            best_score = score;
                            best_pred  = j;
                        }
                    }
                    score_sum += best_score;
                    s->mv[0][0][0] = mv_predictor[best_pred][0];
                    s->mv[0][0][1] = mv_predictor[best_pred][1];

                    for (i = 0; i < mot_step; i++)
                        for (j = 0; j < mot_step; j++) {
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][0] = s->mv[0][0][0];
                            s->current_picture.f.motion_val[0][mot_index + i + j * mot_stride][1] = s->mv[0][0][1];
                        }

                    decode_mb(s, ref[best_pred]);


                    if (s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y) {
                        fixed[mb_xy] = MV_CHANGED;
                        changed++;
                    } else
                        fixed[mb_xy] = MV_UNCHANGED;
                }
            }

            // printf(".%d/%d", changed, score_sum); fflush(stdout);
        }

        if (none_left)
            return;

        for (i = 0; i < s->mb_num; i++) {
            int mb_xy = s->mb_index2xy[i];
            if (fixed[mb_xy])
                fixed[mb_xy] = MV_FROZEN;
        }
        // printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s){ /* <=== */ 
    UINT8 fixed[s->mb_num];
#define MV_FROZEN    3

#define MV_UNCHANGED 1
    const int mb_width = s->mb_width;
    const int mb_height= s->mb_height;
    int i, depth, num_avail;
   
    num_avail=0;
    for(i=0; i<s->mb_num; i++){
        int f=0;
        int error= s->error_status_table[i];

        if(s->mb_type[i]&MB_TYPE_INTRA) f=MV_FROZEN; //intra //FIXME check
        if(!(error&MV_ERROR)) f=MV_FROZEN;           //inter with undamaged MV
        
        fixed[i]= f;
        if(f==MV_FROZEN)
            num_avail++;
    }
    
    if((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) || num_avail <= mb_width/2){
        int mb_x, mb_y;
        i= -1;
        for(mb_y=0; mb_y<s->mb_height; mb_y++){
            for(mb_x=0; mb_x<s->mb_width; mb_x++){
                i++;
                
                if(s->mb_type[i]&MB_TYPE_INTRA) continue;
                if(!(s->error_status_table[i]&MV_ERROR)) continue;

                s->mv_dir = MV_DIR_FORWARD;
                s->mb_intra=0;
                s->mv_type = MV_TYPE_16X16;
                s->mb_skiped=0;

                clear_blocks(s->block[0]);

                s->mb_x= mb_x;
                s->mb_y= mb_y;
                s->mv[0][0][0]= 0;
                s->mv[0][0][1]= 0;
                MPV_decode_mb(s, s->block);
            }
        }
        return;
    }
    
    for(depth=0;; depth++){
        int changed, pass, none_left;

        none_left=1;
        changed=1;
        for(pass=0; (changed || pass<2) && pass<10; pass++){
            int i,mb_x, mb_y;
int score_sum=0;
 
            changed=0;
            i= -1;
            for(mb_y=0; mb_y<s->mb_height; mb_y++){
                for(mb_x=0; mb_x<s->mb_width; mb_x++){
                    int mv_predictor[8][2]={{0}};
                    int pred_count=0;
                    int j;
                    int best_score=256*256*256*64;
                    int best_pred=0;
                    const int mot_stride= mb_width*2+2;
                    const int mot_index= mb_x*2 + 1 + (mb_y*2+1)*mot_stride;
                    int prev_x= s->motion_val[mot_index][0];
                    int prev_y= s->motion_val[mot_index][1];

                    i++;
                    if((mb_x^mb_y^pass)&1) continue;
                    
                    if(fixed[i]==MV_FROZEN) continue;
                    
                    j=0;
                    if(mb_x>0           && fixed[i-1       ]==MV_FROZEN) j=1;
                    if(mb_x+1<mb_width  && fixed[i+1       ]==MV_FROZEN) j=1;
                    if(mb_y>0           && fixed[i-mb_width]==MV_FROZEN) j=1;
                    if(mb_y+1<mb_height && fixed[i+mb_width]==MV_FROZEN) j=1;
                    if(j==0) continue;

                    j=0;
                    if(mb_x>0           && fixed[i-1       ]==MV_CHANGED) j=1;
                    if(mb_x+1<mb_width  && fixed[i+1       ]==MV_CHANGED) j=1;
                    if(mb_y>0           && fixed[i-mb_width]==MV_CHANGED) j=1;
                    if(mb_y+1<mb_height && fixed[i+mb_width]==MV_CHANGED) j=1;
                    if(j==0 && pass>1) continue;
                    
                    none_left=0;
                    
                    if(mb_x>0 && fixed[i-1]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index - 2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index - 2][1];
                        pred_count++;
                    }
                    if(mb_x+1<mb_width && fixed[i+1]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index + 2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index + 2][1];
                        pred_count++;
                    }
                    if(mb_y>0 && fixed[i-mb_width]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index - mot_stride*2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index - mot_stride*2][1];
                        pred_count++;
                    }
                    if(mb_y+1<mb_height && fixed[i+mb_width]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index + mot_stride*2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index + mot_stride*2][1];
                        pred_count++;
                    }
                    if(pred_count==0) continue;
                    
                    if(pred_count>1){
                        int sum_x=0, sum_y=0;
                        int max_x, max_y, min_x, min_y;

                        for(j=0; j<pred_count; j++){
                            sum_x+= mv_predictor[j][0];
                            sum_y+= mv_predictor[j][1];
                        }
                    
                        /* mean */
                        mv_predictor[pred_count][0] = sum_x/j;
                        mv_predictor[pred_count][1] = sum_y/j;
                    
                        /* median */
                        if(pred_count>=3){
                            min_y= min_x= 99999;
                            max_y= max_x=-99999;
                        }else{
                            min_x=min_y=max_x=max_y=0;
                        }
                        for(j=0; j<pred_count; j++){
                            max_x= MAX(max_x, mv_predictor[j][0]);
                            max_y= MAX(max_y, mv_predictor[j][1]);
                            min_x= MIN(min_x, mv_predictor[j][0]);
                            min_y= MIN(min_y, mv_predictor[j][1]);
                        }
                        mv_predictor[pred_count+1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count+1][1] = sum_y - max_y - min_y;
                        
                        if(pred_count==4){
                            mv_predictor[pred_count+1][0] /= 2;
                            mv_predictor[pred_count+1][1] /= 2;
                        }
                        pred_count+=2;
                    }
                    
                    /* zero MV */
                    pred_count++;

                    /* last MV */
                    mv_predictor[pred_count][0]= s->motion_val[mot_index][0];
                    mv_predictor[pred_count][1]= s->motion_val[mot_index][1];
                    pred_count++;                    
                    
                    s->mv_dir = MV_DIR_FORWARD;
                    s->mb_intra=0;
                    s->mv_type = MV_TYPE_16X16;
                    s->mb_skiped=0;

                    clear_blocks(s->block[0]);

                    s->mb_x= mb_x;
                    s->mb_y= mb_y;
                    for(j=0; j<pred_count; j++){
                        int score=0;
                        UINT8 *src= s->current_picture[0] + mb_x*16 + mb_y*16*s->linesize;

                        s->motion_val[mot_index][0]= s->mv[0][0][0]= mv_predictor[j][0];
                        s->motion_val[mot_index][1]= s->mv[0][0][1]= mv_predictor[j][1];
                        MPV_decode_mb(s, s->block);
                        
                        if(mb_x>0 && fixed[i-1]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k*s->linesize-1 ]-src[k*s->linesize   ]);
                        }
                        if(mb_x+1<mb_width && fixed[i+1]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k*s->linesize+15]-src[k*s->linesize+16]);
                        }
                        if(mb_y>0 && fixed[i-mb_width]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k-s->linesize   ]-src[k               ]);
                        }
                        if(mb_y+1<mb_height && fixed[i+mb_width]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k+s->linesize*15]-src[k+s->linesize*16]);
                        }
                        
                        if(score <= best_score){ // <= will favor the last MV
                            best_score= score;
                            best_pred= j;
                        }
                    }
score_sum+= best_score;
//FIXME no need to set s->motion_val[mot_index][0] explicit
                    s->motion_val[mot_index][0]= s->mv[0][0][0]= mv_predictor[best_pred][0];
                    s->motion_val[mot_index][1]= s->mv[0][0][1]= mv_predictor[best_pred][1];

                    MPV_decode_mb(s, s->block);

                    
                    if(s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y){
                        fixed[i]=MV_CHANGED;
                        changed++;
                    }else
                        fixed[i]=MV_UNCHANGED;
                }
            }

//            printf(".%d/%d", changed, score_sum); fflush(stdout);
        }
        
        if(none_left) 
            return;
            
        for(i=0; i<s->mb_num; i++){
            if(fixed[i])
                fixed[i]=MV_FROZEN;
        }
//        printf(":"); fflush(stdout);
    }
}
static void guess_mv(MpegEncContext *s){ /* <=== */ 
    UINT8 fixed[s->mb_num];
#define MV_FROZEN    3
#define MV_CHANGED   2

    const int mb_width = s->mb_width;
    const int mb_height= s->mb_height;
    int i, depth, num_avail;
   
    num_avail=0;
    for(i=0; i<s->mb_num; i++){
        int f=0;
        int error= s->error_status_table[i];

        if(s->mb_type[i]&MB_TYPE_INTRA) f=MV_FROZEN; //intra //FIXME check
        if(!(error&MV_ERROR)) f=MV_FROZEN;           //inter with undamaged MV
        
        fixed[i]= f;
        if(f==MV_FROZEN)
            num_avail++;
    }
    
    if((!(s->avctx->error_concealment&FF_EC_GUESS_MVS)) || num_avail <= mb_width/2){
        int mb_x, mb_y;
        i= -1;
        for(mb_y=0; mb_y<s->mb_height; mb_y++){
            for(mb_x=0; mb_x<s->mb_width; mb_x++){
                i++;
                
                if(s->mb_type[i]&MB_TYPE_INTRA) continue;
                if(!(s->error_status_table[i]&MV_ERROR)) continue;

                s->mv_dir = MV_DIR_FORWARD;
                s->mb_intra=0;
                s->mv_type = MV_TYPE_16X16;
                s->mb_skiped=0;

                clear_blocks(s->block[0]);

                s->mb_x= mb_x;
                s->mb_y= mb_y;
                s->mv[0][0][0]= 0;
                s->mv[0][0][1]= 0;
                MPV_decode_mb(s, s->block);
            }
        }
        return;
    }
    
    for(depth=0;; depth++){
        int changed, pass, none_left;

        none_left=1;
        changed=1;
        for(pass=0; (changed || pass<2) && pass<10; pass++){
            int i,mb_x, mb_y;
int score_sum=0;
 
            changed=0;
            i= -1;
            for(mb_y=0; mb_y<s->mb_height; mb_y++){
                for(mb_x=0; mb_x<s->mb_width; mb_x++){
                    int mv_predictor[8][2]={{0}};
                    int pred_count=0;
                    int j;
                    int best_score=256*256*256*64;
                    int best_pred=0;
                    const int mot_stride= mb_width*2+2;
                    const int mot_index= mb_x*2 + 1 + (mb_y*2+1)*mot_stride;
                    int prev_x= s->motion_val[mot_index][0];
                    int prev_y= s->motion_val[mot_index][1];

                    i++;
                    if((mb_x^mb_y^pass)&1) continue;
                    
                    if(fixed[i]==MV_FROZEN) continue;
                    
                    j=0;
                    if(mb_x>0           && fixed[i-1       ]==MV_FROZEN) j=1;
                    if(mb_x+1<mb_width  && fixed[i+1       ]==MV_FROZEN) j=1;
                    if(mb_y>0           && fixed[i-mb_width]==MV_FROZEN) j=1;
                    if(mb_y+1<mb_height && fixed[i+mb_width]==MV_FROZEN) j=1;
                    if(j==0) continue;

                    j=0;
                    if(mb_x>0           && fixed[i-1       ]==MV_CHANGED) j=1;
                    if(mb_x+1<mb_width  && fixed[i+1       ]==MV_CHANGED) j=1;
                    if(mb_y>0           && fixed[i-mb_width]==MV_CHANGED) j=1;
                    if(mb_y+1<mb_height && fixed[i+mb_width]==MV_CHANGED) j=1;
                    if(j==0 && pass>1) continue;
                    
                    none_left=0;
                    
                    if(mb_x>0 && fixed[i-1]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index - 2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index - 2][1];
                        pred_count++;
                    }
                    if(mb_x+1<mb_width && fixed[i+1]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index + 2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index + 2][1];
                        pred_count++;
                    }
                    if(mb_y>0 && fixed[i-mb_width]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index - mot_stride*2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index - mot_stride*2][1];
                        pred_count++;
                    }
                    if(mb_y+1<mb_height && fixed[i+mb_width]){
                        mv_predictor[pred_count][0]= s->motion_val[mot_index + mot_stride*2][0];
                        mv_predictor[pred_count][1]= s->motion_val[mot_index + mot_stride*2][1];
                        pred_count++;
                    }
                    if(pred_count==0) continue;
                    
                    if(pred_count>1){
                        int sum_x=0, sum_y=0;
                        int max_x, max_y, min_x, min_y;

                        for(j=0; j<pred_count; j++){
                            sum_x+= mv_predictor[j][0];
                            sum_y+= mv_predictor[j][1];
                        }
                    
                        /* mean */
                        mv_predictor[pred_count][0] = sum_x/j;
                        mv_predictor[pred_count][1] = sum_y/j;
                    
                        /* median */
                        if(pred_count>=3){
                            min_y= min_x= 99999;
                            max_y= max_x=-99999;
                        }else{
                            min_x=min_y=max_x=max_y=0;
                        }
                        for(j=0; j<pred_count; j++){
                            max_x= MAX(max_x, mv_predictor[j][0]);
                            max_y= MAX(max_y, mv_predictor[j][1]);
                            min_x= MIN(min_x, mv_predictor[j][0]);
                            min_y= MIN(min_y, mv_predictor[j][1]);
                        }
                        mv_predictor[pred_count+1][0] = sum_x - max_x - min_x;
                        mv_predictor[pred_count+1][1] = sum_y - max_y - min_y;
                        
                        if(pred_count==4){
                            mv_predictor[pred_count+1][0] /= 2;
                            mv_predictor[pred_count+1][1] /= 2;
                        }
                        pred_count+=2;
                    }
                    
                    /* zero MV */
                    pred_count++;

                    /* last MV */
                    mv_predictor[pred_count][0]= s->motion_val[mot_index][0];
                    mv_predictor[pred_count][1]= s->motion_val[mot_index][1];
                    pred_count++;                    
                    
                    s->mv_dir = MV_DIR_FORWARD;
                    s->mb_intra=0;
                    s->mv_type = MV_TYPE_16X16;
                    s->mb_skiped=0;

                    clear_blocks(s->block[0]);

                    s->mb_x= mb_x;
                    s->mb_y= mb_y;
                    for(j=0; j<pred_count; j++){
                        int score=0;
                        UINT8 *src= s->current_picture[0] + mb_x*16 + mb_y*16*s->linesize;

                        s->motion_val[mot_index][0]= s->mv[0][0][0]= mv_predictor[j][0];
                        s->motion_val[mot_index][1]= s->mv[0][0][1]= mv_predictor[j][1];
                        MPV_decode_mb(s, s->block);
                        
                        if(mb_x>0 && fixed[i-1]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k*s->linesize-1 ]-src[k*s->linesize   ]);
                        }
                        if(mb_x+1<mb_width && fixed[i+1]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k*s->linesize+15]-src[k*s->linesize+16]);
                        }
                        if(mb_y>0 && fixed[i-mb_width]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k-s->linesize   ]-src[k               ]);
                        }
                        if(mb_y+1<mb_height && fixed[i+mb_width]){
                            int k;
                            for(k=0; k<16; k++)
                                score += ABS(src[k+s->linesize*15]-src[k+s->linesize*16]);
                        }
                        
                        if(score <= best_score){ // <= will favor the last MV
                            best_score= score;
                            best_pred= j;
                        }
                    }
score_sum+= best_score;
//FIXME no need to set s->motion_val[mot_index][0] explicit
                    s->motion_val[mot_index][0]= s->mv[0][0][0]= mv_predictor[best_pred][0];
                    s->motion_val[mot_index][1]= s->mv[0][0][1]= mv_predictor[best_pred][1];

                    MPV_decode_mb(s, s->block);

                    
                    if(s->mv[0][0][0] != prev_x || s->mv[0][0][1] != prev_y){
                        fixed[i]=MV_CHANGED;
                        changed++;
                    }else
                        fixed[i]=MV_UNCHANGED;
                }
            }

//            printf(".%d/%d", changed, score_sum); fflush(stdout);
        }
        
        if(none_left) 
            return;
            
        for(i=0; i<s->mb_num; i++){
            if(fixed[i])
                fixed[i]=MV_FROZEN;
        }
//        printf(":"); fflush(stdout);
    }
}
static int read_high_coeffs(AVCodecContext *avctx, uint8_t *src, int16_t *dst, int size, /* <=== */ 
                            int c, int a, int d,
                            int width, ptrdiff_t stride)
{
    PixletContext *ctx = avctx->priv_data;
    GetBitContext *b = &ctx->gbit;
    unsigned cnt1, shbits, rlen, nbits, length, i = 0, j = 0, k;
    int ret, escape, pfx, value, yflag, xflag, flag = 0;
    int64_t state = 3, tmp;

    if ((ret = init_get_bits8(b, src, bytestream2_get_bytes_left(&ctx->gb))) < 0)
      return ret;

    
        nbits = 33 - ff_clz((a >= 0) + (a ^ (a >> 31)) - (a >> 31) - 1);
        if (nbits > 16)
            return AVERROR_INVALIDDATA;
    } else {
        nbits = 1;
    }

    length = 25 - nbits;

    while (i < size) {
        if (state >> 8 != -3) {
            value = ff_clz((state >> 8) + 3) ^ 0x1F;
        } else {
            value = -1;
        }

        cnt1 = get_unary(b, 0, length);

        if (cnt1 >= length) {
            cnt1 = get_bits(b, nbits);
        } else {
            pfx = 14 + ((((uint64_t)(value - 14)) >> 32) & (value - 14));
            cnt1 *= (1 << pfx) - 1;
            shbits = show_bits(b, pfx);
            if (shbits <= 1) {
                skip_bits(b, pfx - 1);
            } else {
                skip_bits(b, pfx);
                cnt1 += shbits - 1;
            }
        }

        xflag = flag + cnt1;
        yflag = xflag;

        if (flag + cnt1 == 0) {
            value = 0;
        } else {
            xflag &= 1u;
            tmp = c * ((yflag + 1) >> 1) + (c >> 1);
            value = xflag + (tmp ^ -xflag);
        }

        i++;
        dst[j++] = value;
        if (j == width) {
            j = 0;
            dst += stride;
        }
        state += d * yflag - (d * state >> 8);

        flag = 0;

        if (state * 4 > 0xFF || i >= size)
            continue;

        pfx = ((state + 8) >> 5) + (state ? ff_clz(state): 32) - 24;
        escape = av_mod_uintp2(16383, pfx);
        cnt1 = get_unary(b, 0, 8);
        if (cnt1 < 8) {
            value = show_bits(b, pfx);
            if (value > 1) {
                skip_bits(b, pfx);
                rlen = value + escape * cnt1 - 1;
            } else {
                skip_bits(b, pfx - 1);
                rlen = escape * cnt1;
            }
        } else {
            if (get_bits1(b))
                value = get_bits(b, 16);
            else
                value = get_bits(b, 8);

            rlen = value + 8 * escape;
        }

        if (rlen > 0xFFFF || i + rlen > size)
            return AVERROR_INVALIDDATA;
        i += rlen;

        for (k = 0; k < rlen; k++) {
            dst[j++] = 0;
            if (j == width) {
                j = 0;
                dst += stride;
            }
        }

        state = 0;
        flag = rlen < 0xFFFF ? 1 : 0;
    }

    align_get_bits(b);
    return get_bits_count(b) >> 3;
}
static int read_high_coeffs(AVCodecContext *avctx, uint8_t *src, int16_t *dst, int size, /* <=== */ 
                            int c, int a, int d,
                            int width, ptrdiff_t stride)
{
    PixletContext *ctx = avctx->priv_data;
    GetBitContext *b = &ctx->gbit;
    unsigned cnt1, shbits, rlen, nbits, length, i = 0, j = 0, k;
    int ret, escape, pfx, value, yflag, xflag, flag = 0;
    int64_t state = 3, tmp;

    if ((ret = init_get_bits8(b, src, bytestream2_get_bytes_left(&ctx->gb))) < 0)
      return ret;

    if ((a >= 0) + (a ^ (a >> 31)) - (a >> 31) != 1) {
        
        if (nbits > 16)
            return AVERROR_INVALIDDATA;
    } else {
        nbits = 1;
    }

    length = 25 - nbits;

    while (i < size) {
        if (state >> 8 != -3) {
            value = ff_clz((state >> 8) + 3) ^ 0x1F;
        } else {
            value = -1;
        }

        cnt1 = get_unary(b, 0, length);

        if (cnt1 >= length) {
            cnt1 = get_bits(b, nbits);
        } else {
            pfx = 14 + ((((uint64_t)(value - 14)) >> 32) & (value - 14));
            cnt1 *= (1 << pfx) - 1;
            shbits = show_bits(b, pfx);
            if (shbits <= 1) {
                skip_bits(b, pfx - 1);
            } else {
                skip_bits(b, pfx);
                cnt1 += shbits - 1;
            }
        }

        xflag = flag + cnt1;
        yflag = xflag;

        if (flag + cnt1 == 0) {
            value = 0;
        } else {
            xflag &= 1u;
            tmp = c * ((yflag + 1) >> 1) + (c >> 1);
            value = xflag + (tmp ^ -xflag);
        }

        i++;
        dst[j++] = value;
        if (j == width) {
            j = 0;
            dst += stride;
        }
        state += d * yflag - (d * state >> 8);

        flag = 0;

        if (state * 4 > 0xFF || i >= size)
            continue;

        pfx = ((state + 8) >> 5) + (state ? ff_clz(state): 32) - 24;
        escape = av_mod_uintp2(16383, pfx);
        cnt1 = get_unary(b, 0, 8);
        if (cnt1 < 8) {
            value = show_bits(b, pfx);
            if (value > 1) {
                skip_bits(b, pfx);
                rlen = value + escape * cnt1 - 1;
            } else {
                skip_bits(b, pfx - 1);
                rlen = escape * cnt1;
            }
        } else {
            if (get_bits1(b))
                value = get_bits(b, 16);
            else
                value = get_bits(b, 8);

            rlen = value + 8 * escape;
        }

        if (rlen > 0xFFFF || i + rlen > size)
            return AVERROR_INVALIDDATA;
        i += rlen;

        for (k = 0; k < rlen; k++) {
            dst[j++] = 0;
            if (j == width) {
                j = 0;
                dst += stride;
            }
        }

        state = 0;
        flag = rlen < 0xFFFF ? 1 : 0;
    }

    align_get_bits(b);
    return get_bits_count(b) >> 3;
}
static void scale_coefs ( /* <=== */ 
    int32_t *dst,
    const int32_t *src,
    int dynrng,
    int len)
{
    int i, shift, round;
    int16_t mul;
    int temp, temp1, temp2, temp3, temp4, temp5, temp6, temp7;

    mul = (dynrng & 0x1f) + 0x20;
    
    if (shift > 0 ) {
      round = 1 << (shift-1);
      for (i=0; i<len; i+=8) {

          temp = src[i] * mul;
          temp1 = src[i+1] * mul;
          temp = temp + round;
          temp2 = src[i+2] * mul;

          temp1 = temp1 + round;
          dst[i] = temp >> shift;
          temp3 = src[i+3] * mul;
          temp2 = temp2 + round;

          dst[i+1] = temp1 >> shift;
          temp4 = src[i + 4] * mul;
          temp3 = temp3 + round;
          dst[i+2] = temp2 >> shift;

          temp5 = src[i+5] * mul;
          temp4 = temp4 + round;
          dst[i+3] = temp3 >> shift;
          temp6 = src[i+6] * mul;

          dst[i+4] = temp4 >> shift;
          temp5 = temp5 + round;
          temp7 = src[i+7] * mul;
          temp6 = temp6 + round;

          dst[i+5] = temp5 >> shift;
          temp7 = temp7 + round;
          dst[i+6] = temp6 >> shift;
          dst[i+7] = temp7 >> shift;

      }
    } else {
      shift = -shift;
      for (i=0; i<len; i+=8) {

          temp = src[i] * mul;
          temp1 = src[i+1] * mul;
          temp2 = src[i+2] * mul;

          dst[i] = temp << shift;
          temp3 = src[i+3] * mul;

          dst[i+1] = temp1 << shift;
          temp4 = src[i + 4] * mul;
          dst[i+2] = temp2 << shift;

          temp5 = src[i+5] * mul;
          dst[i+3] = temp3 << shift;
          temp6 = src[i+6] * mul;

          dst[i+4] = temp4 << shift;
          temp7 = src[i+7] * mul;

          dst[i+5] = temp5 << shift;
          dst[i+6] = temp6 << shift;
          dst[i+7] = temp7 << shift;

      }
    }
}
static int wavpack_decode_block(AVCodecContext *avctx, int block_no, /* <=== */ 
                                AVFrame *frame, const uint8_t *buf, int buf_size)
{
    WavpackContext *wc = avctx->priv_data;
    WavpackFrameContext *s;
    GetByteContext gb;
    void *samples_l, *samples_r;
    int ret;
    int got_terms   = 0, got_weights = 0, got_samples = 0,
        got_entropy = 0, got_bs      = 0, got_float   = 0, got_hybrid = 0;
    int i, j, id, size, ssize, weights, t;
    int bpp, chan = 0, chmask = 0, orig_bpp, sample_rate = 0;
    int multiblock;

    if (block_no >= wc->fdec_num && wv_alloc_frame_context(wc) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error creating frame decode context\n");
        return AVERROR_INVALIDDATA;
    }

    s = wc->fdec[block_no];
    if (!s) {
        av_log(avctx, AV_LOG_ERROR, "Context for block %d is not present\n",
               block_no);
        return AVERROR_INVALIDDATA;
    }

    memset(s->decorr, 0, MAX_TERMS * sizeof(Decorr));
    memset(s->ch, 0, sizeof(s->ch));
    s->extra_bits     = 0;
    s->and            = s->or = s->shift = 0;
    s->got_extra_bits = 0;

    bytestream2_init(&gb, buf, buf_size);

    s->samples = bytestream2_get_le32(&gb);
    if (s->samples != wc->samples) {
        av_log(avctx, AV_LOG_ERROR, "Mismatching number of samples in "
               "a sequence: %d and %d\n", wc->samples, s->samples);
        return AVERROR_INVALIDDATA;
    }
    s->frame_flags = bytestream2_get_le32(&gb);
    bpp            = av_get_bytes_per_sample(avctx->sample_fmt);
    orig_bpp       = ((s->frame_flags & 0x03) + 1) << 3;
    multiblock     = (s->frame_flags & WV_SINGLE_BLOCK) != WV_SINGLE_BLOCK;

    s->stereo         = !(s->frame_flags & WV_MONO);
    s->stereo_in      =  (s->frame_flags & WV_FALSE_STEREO) ? 0 : s->stereo;
    s->joint          =   s->frame_flags & WV_JOINT_STEREO;
    s->hybrid         =   s->frame_flags & WV_HYBRID_MODE;
    s->hybrid_bitrate =   s->frame_flags & WV_HYBRID_BITRATE;
    s->post_shift     = bpp * 8 - orig_bpp + ((s->frame_flags >> 13) & 0x1f);
    s->hybrid_maxclip =  ((1LL << (orig_bpp - 1)) - 1);
    s->hybrid_minclip = ((-1LL << (orig_bpp - 1)));
    s->CRC            = bytestream2_get_le32(&gb);

    // parse metadata blocks
    while (bytestream2_get_bytes_left(&gb)) {
        id   = bytestream2_get_byte(&gb);
        size = bytestream2_get_byte(&gb);
        if (id & WP_IDF_LONG) {
            size |= (bytestream2_get_byte(&gb)) << 8;
            size |= (bytestream2_get_byte(&gb)) << 16;
        }
        size <<= 1; // size is specified in words
        ssize  = size;
        if (id & WP_IDF_ODD)
            size--;
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Got incorrect block %02X with size %i\n", id, size);
            break;
        }
        if (bytestream2_get_bytes_left(&gb) < ssize) {
            av_log(avctx, AV_LOG_ERROR,
                   "Block size %i is out of bounds\n", size);
            break;
        }
        switch (id & WP_IDF_MASK) {
        case WP_ID_DECTERMS:
            if (size > MAX_TERMS) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation terms\n");
                s->terms = 0;
                bytestream2_skip(&gb, ssize);
                continue;
            }
            s->terms = size;
            for (i = 0; i < s->terms; i++) {
                uint8_t val = bytestream2_get_byte(&gb);
                s->decorr[s->terms - i - 1].value = (val & 0x1F) - 5;
                s->decorr[s->terms - i - 1].delta =  val >> 5;
            }
            got_terms = 1;
            break;
        case WP_ID_DECWEIGHTS:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            weights = size >> s->stereo_in;
            if (weights > MAX_TERMS || weights > s->terms) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation weights\n");
                bytestream2_skip(&gb, ssize);
                continue;
            }
            for (i = 0; i < weights; i++) {
                t = (int8_t)bytestream2_get_byte(&gb);
                s->decorr[s->terms - i - 1].weightA = t << 3;
                if (s->decorr[s->terms - i - 1].weightA > 0)
                    s->decorr[s->terms - i - 1].weightA +=
                        (s->decorr[s->terms - i - 1].weightA + 64) >> 7;
                if (s->stereo_in) {
                    t = (int8_t)bytestream2_get_byte(&gb);
                    s->decorr[s->terms - i - 1].weightB = t << 3;
                    if (s->decorr[s->terms - i - 1].weightB > 0)
                        s->decorr[s->terms - i - 1].weightB +=
                            (s->decorr[s->terms - i - 1].weightB + 64) >> 7;
                }
            }
            got_weights = 1;
            break;
        case WP_ID_DECSAMPLES:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            t = 0;
            for (i = s->terms - 1; (i >= 0) && (t < size); i--) {
                if (s->decorr[i].value > 8) {
                    s->decorr[i].samplesA[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    s->decorr[i].samplesA[1] =
                        wp_exp2(bytestream2_get_le16(&gb));

                    if (s->stereo_in) {
                        s->decorr[i].samplesB[0] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        s->decorr[i].samplesB[1] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        t                       += 4;
                    }
                    t += 4;
                } else if (s->decorr[i].value < 0) {
                    s->decorr[i].samplesA[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    s->decorr[i].samplesB[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    t                       += 4;
                } else {
                    for (j = 0; j < s->decorr[i].value; j++) {
                        s->decorr[i].samplesA[j] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        if (s->stereo_in) {
                            s->decorr[i].samplesB[j] =
                                wp_exp2(bytestream2_get_le16(&gb));
                        }
                    }
                    t += s->decorr[i].value * 2 * (s->stereo_in + 1);
                }
            }
            got_samples = 1;
            break;
        case WP_ID_ENTROPY:
            if (size != 6 * (s->stereo_in + 1)) {
                av_log(avctx, AV_LOG_ERROR,
                       "Entropy vars size should be %i, got %i",
                       6 * (s->stereo_in + 1), size);
                bytestream2_skip(&gb, ssize);
                continue;
            }
            for (j = 0; j <= s->stereo_in; j++)
                for (i = 0; i < 3; i++) {
                    s->ch[j].median[i] = wp_exp2(bytestream2_get_le16(&gb));
                }
            got_entropy = 1;
            break;
        case WP_ID_HYBRID:
            if (s->hybrid_bitrate) {
                for (i = 0; i <= s->stereo_in; i++) {
                    s->ch[i].slow_level = wp_exp2(bytestream2_get_le16(&gb));
                    size               -= 2;
                }
            }
            for (i = 0; i < (s->stereo_in + 1); i++) {
                s->ch[i].bitrate_acc = bytestream2_get_le16(&gb) << 16;
                size                -= 2;
            }
            if (size > 0) {
                for (i = 0; i < (s->stereo_in + 1); i++) {
                    s->ch[i].bitrate_delta =
                        wp_exp2((int16_t)bytestream2_get_le16(&gb));
                }
            } else {
                for (i = 0; i < (s->stereo_in + 1); i++)
                    s->ch[i].bitrate_delta = 0;
            }
            got_hybrid = 1;
            break;
        case WP_ID_INT32INFO: {
            uint8_t val[4];
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, size = %i\n",
                       size);
                bytestream2_skip(&gb, ssize - 4);
                continue;
            }
            bytestream2_get_buffer(&gb, val, 4);
            if (val[0]) {
                s->extra_bits = val[0];
            } else if (val[1]) {
                s->shift = val[1];
            } else if (val[2]) {
                s->and   = s->or = 1;
                s->shift = val[2];
            } else if (val[3]) {
                s->and   = 1;
                s->shift = val[3];
            }
            /* original WavPack decoder forces 32-bit lossy sound to be treated
             * as 24-bit one in order to have proper clipping */
            if (s->hybrid && bpp == 4 && s->post_shift < 8 && s->shift > 8) {
                s->post_shift      += 8;
                s->shift           -= 8;
                s->hybrid_maxclip >>= 8;
                s->hybrid_minclip >>= 8;
            }
            break;
        }
        case WP_ID_FLOATINFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid FLOATINFO, size = %i\n", size);
                bytestream2_skip(&gb, ssize);
                continue;
            }
            s->float_flag    = bytestream2_get_byte(&gb);
            s->float_shift   = bytestream2_get_byte(&gb);
            s->float_max_exp = bytestream2_get_byte(&gb);
            got_float        = 1;
            bytestream2_skip(&gb, 1);
            break;
        case WP_ID_DATA:
            s->sc.offset = bytestream2_tell(&gb);
            s->sc.size   = size * 8;
            init_get_bits(&s->gb, gb.buffer, size * 8);
            s->data_size = size * 8;
            bytestream2_skip(&gb, size);
            got_bs       = 1;
            break;
        case WP_ID_EXTRABITS:
            if (size <= 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid EXTRABITS, size = %i\n",
                       size);
                bytestream2_skip(&gb, size);
                continue;
            }
            s->extra_sc.offset = bytestream2_tell(&gb);
            s->extra_sc.size   = size * 8;
            init_get_bits(&s->gb_extra_bits, gb.buffer, size * 8);
            s->crc_extra_bits  = get_bits_long(&s->gb_extra_bits, 32);
            bytestream2_skip(&gb, size);
            s->got_extra_bits  = 1;
            break;
        case WP_ID_CHANINFO:
            if (size <= 1) {
                av_log(avctx, AV_LOG_ERROR,
                       "Insufficient channel information\n");
                return AVERROR_INVALIDDATA;
            }
            chan = bytestream2_get_byte(&gb);
            switch (size - 2) {
            case 0:
                chmask = bytestream2_get_byte(&gb);
                break;
            case 1:
                chmask = bytestream2_get_le16(&gb);
                break;
            case 2:
                chmask = bytestream2_get_le24(&gb);
                break;
            case 3:
                chmask = bytestream2_get_le32(&gb);;
                break;
            case 5:
                bytestream2_skip(&gb, 1);
                chan  |= (bytestream2_get_byte(&gb) & 0xF) << 8;
                chmask = bytestream2_get_le16(&gb);
                break;
            default:
                av_log(avctx, AV_LOG_ERROR, "Invalid channel info size %d\n",
                       size);
                chan   = avctx->channels;
                chmask = avctx->channel_layout;
            }
            break;
        case WP_ID_SAMPLE_RATE:
            if (size != 3) {
                av_log(avctx, AV_LOG_ERROR, "Invalid custom sample rate.\n");
                return AVERROR_INVALIDDATA;
            }
            sample_rate = bytestream2_get_le24(&gb);
            break;
        default:
            bytestream2_skip(&gb, size);
        }
        if (id & WP_IDF_ODD)
            bytestream2_skip(&gb, 1);
    }

    if (!got_terms) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation terms\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_weights) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation weights\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_samples) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation samples\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_entropy) {
        av_log(avctx, AV_LOG_ERROR, "No block with entropy info\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->hybrid && !got_hybrid) {
        av_log(avctx, AV_LOG_ERROR, "Hybrid config not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_bs) {
        av_log(avctx, AV_LOG_ERROR, "Packed samples not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_float && avctx->sample_fmt == AV_SAMPLE_FMT_FLTP) {
        av_log(avctx, AV_LOG_ERROR, "Float information not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->got_extra_bits && avctx->sample_fmt != AV_SAMPLE_FMT_FLTP) {
        const int size   = get_bits_left(&s->gb_extra_bits);
        const int wanted = s->samples * s->extra_bits << s->stereo_in;
        if (size < wanted) {
            av_log(avctx, AV_LOG_ERROR, "Too small EXTRABITS\n");
            s->got_extra_bits = 0;
        }
    }

    if (!wc->ch_offset) {
        int sr = (s->frame_flags >> 23) & 0xf;
        if (sr == 0xf) {
            if (!sample_rate) {
                av_log(avctx, AV_LOG_ERROR, "Custom sample rate missing.\n");
                return AVERROR_INVALIDDATA;
            }
            avctx->sample_rate = sample_rate;
        } else
            avctx->sample_rate = wv_rates[sr];

        if (multiblock) {
            if (chan)
                avctx->channels = chan;
            if (chmask)
                avctx->channel_layout = chmask;
        } else {
            avctx->channels       = s->stereo ? 2 : 1;
            avctx->channel_layout = s->stereo ? AV_CH_LAYOUT_STEREO :
                                                AV_CH_LAYOUT_MONO;
        }

        /* get output buffer */
        frame->nb_samples = s->samples;
        if ((ret = ff_get_buffer(avctx, frame, 0)) < 0) {
            av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
            return ret;
        }
    }

    if (wc->ch_offset + s->stereo >= avctx->channels) {
        av_log(avctx, AV_LOG_WARNING, "Too many channels coded in a packet.\n");
        
    }

    samples_l = frame->extended_data[wc->ch_offset];
    if (s->stereo)
        samples_r = frame->extended_data[wc->ch_offset + 1];

    wc->ch_offset += 1 + s->stereo;

    if (s->stereo_in) {
        ret = wv_unpack_stereo(s, &s->gb, samples_l, samples_r, avctx->sample_fmt);
        if (ret < 0)
            return ret;
    } else {
        ret = wv_unpack_mono(s, &s->gb, samples_l, avctx->sample_fmt);
        if (ret < 0)
            return ret;

        if (s->stereo)
            memcpy(samples_r, samples_l, bpp * s->samples);
    }

    return 0;
}
static int wavpack_decode_block(AVCodecContext *avctx, int block_no, /* <=== */ 
                                void *data, int *got_frame_ptr,
                                const uint8_t *buf, int buf_size)
{
    WavpackContext *wc = avctx->priv_data;
    WavpackFrameContext *s;
    void *samples = data;
    int samplecount;
    int got_terms   = 0, got_weights = 0, got_samples = 0,
        got_entropy = 0, got_bs      = 0, got_float   = 0, got_hybrid = 0;
    const uint8_t *orig_buf = buf;
    const uint8_t *buf_end  = buf + buf_size;
    int i, j, id, size, ssize, weights, t;
    int bpp, chan, chmask, orig_bpp;

    if (buf_size == 0) {
        *got_frame_ptr = 0;
        return 0;
    }

    if (block_no >= wc->fdec_num && wv_alloc_frame_context(wc) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error creating frame decode context\n");
        return -1;
    }

    s = wc->fdec[block_no];
    if (!s) {
        av_log(avctx, AV_LOG_ERROR, "Context for block %d is not present\n",
               block_no);
        return -1;
    }

    memset(s->decorr, 0, MAX_TERMS * sizeof(Decorr));
    memset(s->ch, 0, sizeof(s->ch));
    s->extra_bits     = 0;
    s->and            = s->or = s->shift = 0;
    s->got_extra_bits = 0;

    if (!wc->mkv_mode) {
        s->samples = AV_RL32(buf);
        buf       += 4;
        if (!s->samples) {
            *got_frame_ptr = 0;
            return 0;
        }
    } else {
        s->samples = wc->samples;
    }
    s->frame_flags = AV_RL32(buf);
    buf           += 4;
    bpp            = av_get_bytes_per_sample(avctx->sample_fmt);
    samples        = (uint8_t *)samples + bpp * wc->ch_offset;
    orig_bpp       = ((s->frame_flags & 0x03) + 1) << 3;

    s->stereo         = !(s->frame_flags & WV_MONO);
    s->stereo_in      =  (s->frame_flags & WV_FALSE_STEREO) ? 0 : s->stereo;
    s->joint          =   s->frame_flags & WV_JOINT_STEREO;
    s->hybrid         =   s->frame_flags & WV_HYBRID_MODE;
    s->hybrid_bitrate =   s->frame_flags & WV_HYBRID_BITRATE;
    s->post_shift     = bpp * 8 - orig_bpp + ((s->frame_flags >> 13) & 0x1f);
    s->hybrid_maxclip =  ((1LL << (orig_bpp - 1)) - 1);
    s->hybrid_minclip = ((-1LL << (orig_bpp - 1)));
    s->CRC            = AV_RL32(buf);
    buf              += 4;
    if (wc->mkv_mode)
        buf += 4;  // skip block size;

    wc->ch_offset += 1 + s->stereo;

    // parse metadata blocks
    while (buf < buf_end) {
        id   = *buf++;
        size = *buf++;
        if (id & WP_IDF_LONG) {
            size |= (*buf++) << 8;
            size |= (*buf++) << 16;
        }
        size <<= 1; // size is specified in words
        ssize  = size;
        if (id & WP_IDF_ODD)
            size--;
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Got incorrect block %02X with size %i\n", id, size);
            break;
        }
        if (buf + ssize > buf_end) {
            av_log(avctx, AV_LOG_ERROR,
                   "Block size %i is out of bounds\n", size);
            break;
        }
        if (id & WP_IDF_IGNORE) {
            buf += ssize;
            continue;
        }
        switch (id & WP_IDF_MASK) {
        case WP_ID_DECTERMS:
            if (size > MAX_TERMS) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation terms\n");
                s->terms = 0;
                buf     += ssize;
                continue;
            }
            s->terms = size;
            for (i = 0; i < s->terms; i++) {
                s->decorr[s->terms - i - 1].value = (*buf & 0x1F) - 5;
                s->decorr[s->terms - i - 1].delta = *buf >> 5;
                buf++;
            }
            got_terms = 1;
            break;
        case WP_ID_DECWEIGHTS:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            weights = size >> s->stereo_in;
            if (weights > MAX_TERMS || weights > s->terms) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation weights\n");
                buf += ssize;
                continue;
            }
            for (i = 0; i < weights; i++) {
                t                                   = (int8_t)(*buf++);
                s->decorr[s->terms - i - 1].weightA = t << 3;
                if (s->decorr[s->terms - i - 1].weightA > 0)
                    s->decorr[s->terms - i - 1].weightA +=
                        (s->decorr[s->terms - i - 1].weightA + 64) >> 7;
                if (s->stereo_in) {
                    t                                   = (int8_t)(*buf++);
                    s->decorr[s->terms - i - 1].weightB = t << 3;
                    if (s->decorr[s->terms - i - 1].weightB > 0)
                        s->decorr[s->terms - i - 1].weightB +=
                            (s->decorr[s->terms - i - 1].weightB + 64) >> 7;
                }
            }
            got_weights = 1;
            break;
        case WP_ID_DECSAMPLES:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            t = 0;
            for (i = s->terms - 1; (i >= 0) && (t < size); i--) {
                if (s->decorr[i].value > 8) {
                    s->decorr[i].samplesA[0] = wp_exp2(AV_RL16(buf));
                    buf                     += 2;
                    s->decorr[i].samplesA[1] = wp_exp2(AV_RL16(buf));
                    buf                     += 2;
                    if (s->stereo_in) {
                        s->decorr[i].samplesB[0] = wp_exp2(AV_RL16(buf));
                        buf                     += 2;
                        s->decorr[i].samplesB[1] = wp_exp2(AV_RL16(buf));
                        buf                     += 2;
                        t                       += 4;
                    }
                    t += 4;
                } else if (s->decorr[i].value < 0) {
                    s->decorr[i].samplesA[0] = wp_exp2(AV_RL16(buf));
                    buf                     += 2;
                    s->decorr[i].samplesB[0] = wp_exp2(AV_RL16(buf));
                    buf                     += 2;
                    t                       += 4;
                } else {
                    for (j = 0; j < s->decorr[i].value; j++) {
                        s->decorr[i].samplesA[j] = wp_exp2(AV_RL16(buf));
                        buf                     += 2;
                        if (s->stereo_in) {
                            s->decorr[i].samplesB[j] = wp_exp2(AV_RL16(buf));
                            buf                     += 2;
                        }
                    }
                    t += s->decorr[i].value * 2 * (s->stereo_in + 1);
                }
            }
            got_samples = 1;
            break;
        case WP_ID_ENTROPY:
            if (size != 6 * (s->stereo_in + 1)) {
                av_log(avctx, AV_LOG_ERROR,
                       "Entropy vars size should be %i, got %i",
                       6 * (s->stereo_in + 1), size);
                buf += ssize;
                continue;
            }
            for (j = 0; j <= s->stereo_in; j++)
                for (i = 0; i < 3; i++) {
                    s->ch[j].median[i] = wp_exp2(AV_RL16(buf));
                    buf               += 2;
                }
            got_entropy = 1;
            break;
        case WP_ID_HYBRID:
            if (s->hybrid_bitrate) {
                for (i = 0; i <= s->stereo_in; i++) {
                    s->ch[i].slow_level = wp_exp2(AV_RL16(buf));
                    buf                += 2;
                    size               -= 2;
                }
            }
            for (i = 0; i < (s->stereo_in + 1); i++) {
                s->ch[i].bitrate_acc = AV_RL16(buf) << 16;
                buf                 += 2;
                size                -= 2;
            }
            if (size > 0) {
                for (i = 0; i < (s->stereo_in + 1); i++) {
                    s->ch[i].bitrate_delta = wp_exp2((int16_t)AV_RL16(buf));
                    buf                   += 2;
                }
            } else {
                for (i = 0; i < (s->stereo_in + 1); i++)
                    s->ch[i].bitrate_delta = 0;
            }
            got_hybrid = 1;
            break;
        case WP_ID_INT32INFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, size = %i, sent_bits = %i\n",
                       size, *buf);
                buf += ssize;
                continue;
            }
            if (buf[0])
                s->extra_bits = buf[0];
            else if (buf[1])
                s->shift = buf[1];
            else if (buf[2]) {
                s->and   = s->or = 1;
                s->shift = buf[2];
            } else if (buf[3]) {
                s->and   = 1;
                s->shift = buf[3];
            }
            /* original WavPack decoder forces 32-bit lossy sound to be treated
             * as 24-bit one in order to have proper clipping */
            if (s->hybrid && bpp == 4 && s->post_shift < 8 && s->shift > 8) {
                s->post_shift      += 8;
                s->shift           -= 8;
                s->hybrid_maxclip >>= 8;
                s->hybrid_minclip >>= 8;
            }
            buf += 4;
            break;
        case WP_ID_FLOATINFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid FLOATINFO, size = %i\n", size);
                buf += ssize;
                continue;
            }
            s->float_flag    = buf[0];
            s->float_shift   = buf[1];
            s->float_max_exp = buf[2];
            buf             += 4;
            got_float        = 1;
            break;
        case WP_ID_DATA:
            s->sc.offset = buf - orig_buf;
            s->sc.size   = size * 8;
            init_get_bits(&s->gb, buf, size * 8);
            s->data_size = size * 8;
            buf         += size;
            got_bs       = 1;
            break;
        case WP_ID_EXTRABITS:
            if (size <= 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid EXTRABITS, size = %i\n",
                       size);
                buf += size;
                continue;
            }
            s->extra_sc.offset = buf - orig_buf;
            s->extra_sc.size   = size * 8;
            init_get_bits(&s->gb_extra_bits, buf, size * 8);
            s->crc_extra_bits  = get_bits_long(&s->gb_extra_bits, 32);
            buf               += size;
            s->got_extra_bits  = 1;
            break;
        case WP_ID_CHANINFO:
            if (size <= 1) {
                av_log(avctx, AV_LOG_ERROR,
                       "Insufficient channel information\n");
                return -1;
            }
            chan = *buf++;
            switch (size - 2) {
            case 0:
                chmask = *buf;
                break;
            case 1:
                chmask = AV_RL16(buf);
                break;
            case 2:
                chmask = AV_RL24(buf);
                break;
            case 3:
                chmask = AV_RL32(buf);
                break;
            case 5:
                chan  |= (buf[1] & 0xF) << 8;
                chmask = AV_RL24(buf + 2);
                break;
            default:
                av_log(avctx, AV_LOG_ERROR, "Invalid channel info size %d\n",
                       size);
                chan   = avctx->channels;
                chmask = avctx->channel_layout;
            }
            if (chan != avctx->channels) {
                av_log(avctx, AV_LOG_ERROR,
                       "Block reports total %d channels, "
                       "decoder believes it's %d channels\n",
                       chan, avctx->channels);
                return -1;
            }
            if (!avctx->channel_layout)
                avctx->channel_layout = chmask;
            buf += size - 1;
            break;
        default:
            buf += size;
        }
        if (id & WP_IDF_ODD)
            buf++;
    }

    if (!got_terms) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation terms\n");
        return -1;
    }
    if (!got_weights) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation weights\n");
        return -1;
    }
    if (!got_samples) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation samples\n");
        return -1;
    }
    if (!got_entropy) {
        av_log(avctx, AV_LOG_ERROR, "No block with entropy info\n");
        return -1;
    }
    if (s->hybrid && !got_hybrid) {
        av_log(avctx, AV_LOG_ERROR, "Hybrid config not found\n");
        return -1;
    }
    if (!got_bs) {
        av_log(avctx, AV_LOG_ERROR, "Packed samples not found\n");
        return -1;
    }
    if (!got_float && avctx->sample_fmt == AV_SAMPLE_FMT_FLT) {
        av_log(avctx, AV_LOG_ERROR, "Float information not found\n");
        return -1;
    }
    if (s->got_extra_bits && avctx->sample_fmt != AV_SAMPLE_FMT_FLT) {
        const int size   = get_bits_left(&s->gb_extra_bits);
        const int wanted = s->samples * s->extra_bits << s->stereo_in;
        if (size < wanted) {
            av_log(avctx, AV_LOG_ERROR, "Too small EXTRABITS\n");
            s->got_extra_bits = 0;
        }
    }

    if (s->stereo_in) {
        if (avctx->sample_fmt == AV_SAMPLE_FMT_S16)
            samplecount = wv_unpack_stereo(s, &s->gb, samples, AV_SAMPLE_FMT_S16);
        else if (avctx->sample_fmt == AV_SAMPLE_FMT_S32)
            samplecount = wv_unpack_stereo(s, &s->gb, samples, AV_SAMPLE_FMT_S32);
        else
            samplecount = wv_unpack_stereo(s, &s->gb, samples, AV_SAMPLE_FMT_FLT);

        if (samplecount < 0)
            return -1;

        samplecount >>= 1;
    } else {
        const int channel_stride = avctx->channels;

        if (avctx->sample_fmt == AV_SAMPLE_FMT_S16)
            samplecount = wv_unpack_mono(s, &s->gb, samples, AV_SAMPLE_FMT_S16);
        else if (avctx->sample_fmt == AV_SAMPLE_FMT_S32)
            samplecount = wv_unpack_mono(s, &s->gb, samples, AV_SAMPLE_FMT_S32);
        else
            samplecount = wv_unpack_mono(s, &s->gb, samples, AV_SAMPLE_FMT_FLT);

        if (samplecount < 0)
            return -1;

        if (s->stereo && avctx->sample_fmt == AV_SAMPLE_FMT_S16) {
            int16_t *dst = (int16_t *)samples + 1;
            int16_t *src = (int16_t *)samples;
            int cnt      = samplecount;
            while (cnt--) {
                *dst = *src;
                src += channel_stride;
                dst += channel_stride;
            }
        } else if (s->stereo && avctx->sample_fmt == AV_SAMPLE_FMT_S32) {
            int32_t *dst = (int32_t *)samples + 1;
            int32_t *src = (int32_t *)samples;
            int cnt      = samplecount;
            while (cnt--) {
                *dst = *src;
                src += channel_stride;
                dst += channel_stride;
            }
        } else if (s->stereo) {
            float *dst = (float *)samples + 1;
            float *src = (float *)samples;
            int cnt    = samplecount;
            while (cnt--) {
                *dst = *src;
                src += channel_stride;
                dst += channel_stride;
            }
        }
    }

    *got_frame_ptr = 1;

    return samplecount * bpp;
}
static int wavpack_decode_block(AVCodecContext *avctx, int block_no, /* <=== */ 
                                AVFrame *frame, const uint8_t *buf, int buf_size)
{
    WavpackContext *wc = avctx->priv_data;
    ThreadFrame tframe = { .f = frame };
    WavpackFrameContext *s;
    GetByteContext gb;
    void *samples_l = NULL, *samples_r = NULL;
    int ret;
    int got_terms   = 0, got_weights = 0, got_samples = 0,
        got_entropy = 0, got_bs      = 0, got_float   = 0, got_hybrid = 0;
    int i, j, id, size, ssize, weights, t;
    int bpp, chan = 0, chmask = 0, orig_bpp, sample_rate = 0;
    int multiblock;

    if (block_no >= wc->fdec_num && wv_alloc_frame_context(wc) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error creating frame decode context\n");
        return AVERROR_INVALIDDATA;
    }

    s = wc->fdec[block_no];
    if (!s) {
        av_log(avctx, AV_LOG_ERROR, "Context for block %d is not present\n",
               block_no);
        return AVERROR_INVALIDDATA;
    }

    memset(s->decorr, 0, MAX_TERMS * sizeof(Decorr));
    memset(s->ch, 0, sizeof(s->ch));
    s->extra_bits     = 0;
    s->and            = s->or = s->shift = 0;
    s->got_extra_bits = 0;

    bytestream2_init(&gb, buf, buf_size);

    s->samples = bytestream2_get_le32(&gb);
    if (s->samples != wc->samples) {
        av_log(avctx, AV_LOG_ERROR, "Mismatching number of samples in "
               "a sequence: %d and %d\n", wc->samples, s->samples);
        return AVERROR_INVALIDDATA;
    }
    s->frame_flags = bytestream2_get_le32(&gb);
    bpp            = av_get_bytes_per_sample(avctx->sample_fmt);
    orig_bpp       = ((s->frame_flags & 0x03) + 1) << 3;
    multiblock     = (s->frame_flags & WV_SINGLE_BLOCK) != WV_SINGLE_BLOCK;

    s->stereo         = !(s->frame_flags & WV_MONO);
    s->stereo_in      =  (s->frame_flags & WV_FALSE_STEREO) ? 0 : s->stereo;
    s->joint          =   s->frame_flags & WV_JOINT_STEREO;
    s->hybrid         =   s->frame_flags & WV_HYBRID_MODE;
    s->hybrid_bitrate =   s->frame_flags & WV_HYBRID_BITRATE;
    s->post_shift     = bpp * 8 - orig_bpp + ((s->frame_flags >> 13) & 0x1f);
    if (s->post_shift < 0 || s->post_shift > 31) {
        return AVERROR_INVALIDDATA;
    }
    s->hybrid_maxclip =  ((1LL << (orig_bpp - 1)) - 1);
    s->hybrid_minclip = ((-1UL << (orig_bpp - 1)));
    s->CRC            = bytestream2_get_le32(&gb);

    // parse metadata blocks
    while (bytestream2_get_bytes_left(&gb)) {
        id   = bytestream2_get_byte(&gb);
        size = bytestream2_get_byte(&gb);
        if (id & WP_IDF_LONG) {
            size |= (bytestream2_get_byte(&gb)) << 8;
            size |= (bytestream2_get_byte(&gb)) << 16;
        }
        size <<= 1; // size is specified in words
        ssize  = size;
        if (id & WP_IDF_ODD)
            size--;
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Got incorrect block %02X with size %i\n", id, size);
            break;
        }
        if (bytestream2_get_bytes_left(&gb) < ssize) {
            av_log(avctx, AV_LOG_ERROR,
                   "Block size %i is out of bounds\n", size);
            break;
        }
        switch (id & WP_IDF_MASK) {
        case WP_ID_DECTERMS:
            if (size > MAX_TERMS) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation terms\n");
                s->terms = 0;
                bytestream2_skip(&gb, ssize);
                continue;
            }
            s->terms = size;
            for (i = 0; i < s->terms; i++) {
                uint8_t val = bytestream2_get_byte(&gb);
                s->decorr[s->terms - i - 1].value = (val & 0x1F) - 5;
                s->decorr[s->terms - i - 1].delta =  val >> 5;
            }
            got_terms = 1;
            break;
        case WP_ID_DECWEIGHTS:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            weights = size >> s->stereo_in;
            if (weights > MAX_TERMS || weights > s->terms) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation weights\n");
                bytestream2_skip(&gb, ssize);
                continue;
            }
            for (i = 0; i < weights; i++) {
                t = (int8_t)bytestream2_get_byte(&gb);
                s->decorr[s->terms - i - 1].weightA = t * (1 << 3);
                if (s->decorr[s->terms - i - 1].weightA > 0)
                    s->decorr[s->terms - i - 1].weightA +=
                        (s->decorr[s->terms - i - 1].weightA + 64) >> 7;
                if (s->stereo_in) {
                    t = (int8_t)bytestream2_get_byte(&gb);
                    s->decorr[s->terms - i - 1].weightB = t * (1 << 3);
                    if (s->decorr[s->terms - i - 1].weightB > 0)
                        s->decorr[s->terms - i - 1].weightB +=
                            (s->decorr[s->terms - i - 1].weightB + 64) >> 7;
                }
            }
            got_weights = 1;
            break;
        case WP_ID_DECSAMPLES:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            t = 0;
            for (i = s->terms - 1; (i >= 0) && (t < size); i--) {
                if (s->decorr[i].value > 8) {
                    s->decorr[i].samplesA[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    s->decorr[i].samplesA[1] =
                        wp_exp2(bytestream2_get_le16(&gb));

                    if (s->stereo_in) {
                        s->decorr[i].samplesB[0] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        s->decorr[i].samplesB[1] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        t                       += 4;
                    }
                    t += 4;
                } else if (s->decorr[i].value < 0) {
                    s->decorr[i].samplesA[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    s->decorr[i].samplesB[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    t                       += 4;
                } else {
                    for (j = 0; j < s->decorr[i].value; j++) {
                        s->decorr[i].samplesA[j] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        if (s->stereo_in) {
                            s->decorr[i].samplesB[j] =
                                wp_exp2(bytestream2_get_le16(&gb));
                        }
                    }
                    t += s->decorr[i].value * 2 * (s->stereo_in + 1);
                }
            }
            got_samples = 1;
            break;
        case WP_ID_ENTROPY:
            if (size != 6 * (s->stereo_in + 1)) {
                av_log(avctx, AV_LOG_ERROR,
                       "Entropy vars size should be %i, got %i.\n",
                       6 * (s->stereo_in + 1), size);
                bytestream2_skip(&gb, ssize);
                continue;
            }
            for (j = 0; j <= s->stereo_in; j++)
                for (i = 0; i < 3; i++) {
                    s->ch[j].median[i] = wp_exp2(bytestream2_get_le16(&gb));
                }
            got_entropy = 1;
            break;
        case WP_ID_HYBRID:
            if (s->hybrid_bitrate) {
                for (i = 0; i <= s->stereo_in; i++) {
                    s->ch[i].slow_level = wp_exp2(bytestream2_get_le16(&gb));
                    size               -= 2;
                }
            }
            for (i = 0; i < (s->stereo_in + 1); i++) {
                s->ch[i].bitrate_acc = bytestream2_get_le16(&gb) << 16;
                size                -= 2;
            }
            if (size > 0) {
                for (i = 0; i < (s->stereo_in + 1); i++) {
                    s->ch[i].bitrate_delta =
                        wp_exp2((int16_t)bytestream2_get_le16(&gb));
                }
            } else {
                for (i = 0; i < (s->stereo_in + 1); i++)
                    s->ch[i].bitrate_delta = 0;
            }
            got_hybrid = 1;
            break;
        case WP_ID_INT32INFO: {
            uint8_t val[4];
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, size = %i\n",
                       size);
                bytestream2_skip(&gb, ssize - 4);
                continue;
            }
            bytestream2_get_buffer(&gb, val, 4);
            if (val[0] > 31) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, extra_bits = %d (> 32)\n", val[0]);
                continue;
            } else if (val[0]) {
                s->extra_bits = val[0];
            } else if (val[1]) {
                s->shift = val[1];
            } else if (val[2]) {
                s->and   = s->or = 1;
                s->shift = val[2];
            } else if (val[3]) {
                s->and   = 1;
                s->shift = val[3];
            }
            if (s->shift > 31) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, shift = %d (> 31)\n", s->shift);
                s->and = s->or = s->shift = 0;
                continue;
            }
            /* original WavPack decoder forces 32-bit lossy sound to be treated
             * as 24-bit one in order to have proper clipping */
            if (s->hybrid && bpp == 4 && s->post_shift < 8 && s->shift > 8) {
                s->post_shift      += 8;
                s->shift           -= 8;
                s->hybrid_maxclip >>= 8;
                s->hybrid_minclip >>= 8;
            }
            break;
        }
        case WP_ID_FLOATINFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid FLOATINFO, size = %i\n", size);
                bytestream2_skip(&gb, ssize);
                continue;
            }
            s->float_flag    = bytestream2_get_byte(&gb);
            s->float_shift   = bytestream2_get_byte(&gb);
            s->float_max_exp = bytestream2_get_byte(&gb);
            got_float        = 1;
            bytestream2_skip(&gb, 1);
            break;
        case WP_ID_DATA:
            s->sc.offset = bytestream2_tell(&gb);
            s->sc.size   = size * 8;
            if ((ret = init_get_bits8(&s->gb, gb.buffer, size)) < 0)
                return ret;
            s->data_size = size * 8;
            bytestream2_skip(&gb, size);
            got_bs       = 1;
            break;
        case WP_ID_EXTRABITS:
            if (size <= 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid EXTRABITS, size = %i\n",
                       size);
                bytestream2_skip(&gb, size);
                continue;
            }
            s->extra_sc.offset = bytestream2_tell(&gb);
            s->extra_sc.size   = size * 8;
            if ((ret = init_get_bits8(&s->gb_extra_bits, gb.buffer, size)) < 0)
                return ret;
            s->crc_extra_bits  = get_bits_long(&s->gb_extra_bits, 32);
            bytestream2_skip(&gb, size);
            s->got_extra_bits  = 1;
            break;
        case WP_ID_CHANINFO:
            if (size <= 1) {
                av_log(avctx, AV_LOG_ERROR,
                       "Insufficient channel information\n");
                return AVERROR_INVALIDDATA;
            }
            chan = bytestream2_get_byte(&gb);
            switch (size - 2) {
            case 0:
                chmask = bytestream2_get_byte(&gb);
                break;
            case 1:
                chmask = bytestream2_get_le16(&gb);
                break;
            case 2:
                chmask = bytestream2_get_le24(&gb);
                break;
            case 3:
                chmask = bytestream2_get_le32(&gb);
                break;
            case 5:
                size = bytestream2_get_byte(&gb);
                if (avctx->channels != size)
                    av_log(avctx, AV_LOG_WARNING, "%i channels signalled"
                           " instead of %i.\n", size, avctx->channels);
                chan  |= (bytestream2_get_byte(&gb) & 0xF) << 8;
                chmask = bytestream2_get_le16(&gb);
                break;
            default:
                av_log(avctx, AV_LOG_ERROR, "Invalid channel info size %d\n",
                       size);
                chan   = avctx->channels;
                chmask = avctx->channel_layout;
            }
            break;
        case WP_ID_SAMPLE_RATE:
            if (size != 3) {
                av_log(avctx, AV_LOG_ERROR, "Invalid custom sample rate.\n");
                return AVERROR_INVALIDDATA;
            }
            sample_rate = bytestream2_get_le24(&gb);
            break;
        default:
            bytestream2_skip(&gb, size);
        }
        if (id & WP_IDF_ODD)
            bytestream2_skip(&gb, 1);
    }

    if (!got_terms) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation terms\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_weights) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation weights\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_samples) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation samples\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_entropy) {
        av_log(avctx, AV_LOG_ERROR, "No block with entropy info\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->hybrid && !got_hybrid) {
        av_log(avctx, AV_LOG_ERROR, "Hybrid config not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_bs) {
        av_log(avctx, AV_LOG_ERROR, "Packed samples not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_float && avctx->sample_fmt == AV_SAMPLE_FMT_FLTP) {
        av_log(avctx, AV_LOG_ERROR, "Float information not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->got_extra_bits && avctx->sample_fmt != AV_SAMPLE_FMT_FLTP) {
        const int size   = get_bits_left(&s->gb_extra_bits);
        const int wanted = s->samples * s->extra_bits << s->stereo_in;
        if (size < wanted) {
            av_log(avctx, AV_LOG_ERROR, "Too small EXTRABITS\n");
            s->got_extra_bits = 0;
        }
    }

    if (!wc->ch_offset) {
        int sr = (s->frame_flags >> 23) & 0xf;
        if (sr == 0xf) {
            if (!sample_rate) {
                av_log(avctx, AV_LOG_ERROR, "Custom sample rate missing.\n");
                return AVERROR_INVALIDDATA;
            }
            avctx->sample_rate = sample_rate;
        } else
            avctx->sample_rate = wv_rates[sr];

        if (multiblock) {
            if (chan)
                avctx->channels = chan;
            if (chmask)
                avctx->channel_layout = chmask;
        } else {
            avctx->channels       = s->stereo ? 2 : 1;
            avctx->channel_layout = s->stereo ? AV_CH_LAYOUT_STEREO :
                                                AV_CH_LAYOUT_MONO;
        }

        /* get output buffer */
        frame->nb_samples = s->samples + 1;
        if ((ret = ff_thread_get_buffer(avctx, &tframe, 0)) < 0)
            return ret;
        frame->nb_samples = s->samples;
    }

    if (wc->ch_offset + s->stereo >= avctx->channels) {
        av_log(avctx, AV_LOG_WARNING, "Too many channels coded in a packet.\n");
        return ((avctx->err_recognition & AV_EF_EXPLODE) || !wc->ch_offset) ? AVERROR_INVALIDDATA : 0;
    }

    samples_l = frame->extended_data[wc->ch_offset];
    if (s->stereo)
        samples_r = frame->extended_data[wc->ch_offset + 1];

    wc->ch_offset += 1 + s->stereo;

    if (s->stereo_in) {
        ret = wv_unpack_stereo(s, &s->gb, samples_l, samples_r, avctx->sample_fmt);
        if (ret < 0)
            return ret;
    } else {
        ret = wv_unpack_mono(s, &s->gb, samples_l, avctx->sample_fmt);
        if (ret < 0)
            return ret;

        if (s->stereo)
            memcpy(samples_r, samples_l, bpp * s->samples);
    }

    return 0;
}
static int wavpack_decode_block(AVCodecContext *avctx, int block_no, /* <=== */ 
                                AVFrame *frame, const uint8_t *buf, int buf_size)
{
    WavpackContext *wc = avctx->priv_data;
    ThreadFrame tframe = { .f = frame };
    WavpackFrameContext *s;
    GetByteContext gb;
    void *samples_l = NULL, *samples_r = NULL;
    int ret;
    int got_terms   = 0, got_weights = 0, got_samples = 0,
        got_entropy = 0, got_bs      = 0, got_float   = 0, got_hybrid = 0;
    int i, j, id, size, ssize, weights, t;
    int bpp, chan = 0, chmask = 0, orig_bpp, sample_rate = 0;
    int multiblock;

    if (block_no >= wc->fdec_num && wv_alloc_frame_context(wc) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error creating frame decode context\n");
        return AVERROR_INVALIDDATA;
    }

    s = wc->fdec[block_no];
    if (!s) {
        av_log(avctx, AV_LOG_ERROR, "Context for block %d is not present\n",
               block_no);
        return AVERROR_INVALIDDATA;
    }

    memset(s->decorr, 0, MAX_TERMS * sizeof(Decorr));
    memset(s->ch, 0, sizeof(s->ch));
    s->extra_bits     = 0;
    s->and            = s->or = s->shift = 0;
    s->got_extra_bits = 0;

    bytestream2_init(&gb, buf, buf_size);

    s->samples = bytestream2_get_le32(&gb);
    if (s->samples != wc->samples) {
        av_log(avctx, AV_LOG_ERROR, "Mismatching number of samples in "
               "a sequence: %d and %d\n", wc->samples, s->samples);
        return AVERROR_INVALIDDATA;
    }
    s->frame_flags = bytestream2_get_le32(&gb);
    bpp            = av_get_bytes_per_sample(avctx->sample_fmt);
    orig_bpp       = ((s->frame_flags & 0x03) + 1) << 3;
    multiblock     = (s->frame_flags & WV_SINGLE_BLOCK) != WV_SINGLE_BLOCK;

    s->stereo         = !(s->frame_flags & WV_MONO);
    s->stereo_in      =  (s->frame_flags & WV_FALSE_STEREO) ? 0 : s->stereo;
    s->joint          =   s->frame_flags & WV_JOINT_STEREO;
    s->hybrid         =   s->frame_flags & WV_HYBRID_MODE;
    s->hybrid_bitrate =   s->frame_flags & WV_HYBRID_BITRATE;
    s->post_shift     = bpp * 8 - orig_bpp + ((s->frame_flags >> 13) & 0x1f);
    if (s->post_shift < 0 || s->post_shift > 31) {
        return AVERROR_INVALIDDATA;
    }
    s->hybrid_maxclip =  ((1LL << (orig_bpp - 1)) - 1);
    s->hybrid_minclip = ((-1UL << (orig_bpp - 1)));
    s->CRC            = bytestream2_get_le32(&gb);

    // parse metadata blocks
    while (bytestream2_get_bytes_left(&gb)) {
        id   = bytestream2_get_byte(&gb);
        size = bytestream2_get_byte(&gb);
        if (id & WP_IDF_LONG) {
            size |= (bytestream2_get_byte(&gb)) << 8;
            size |= (bytestream2_get_byte(&gb)) << 16;
        }
        size <<= 1; // size is specified in words
        ssize  = size;
        if (id & WP_IDF_ODD)
            size--;
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR,
                   "Got incorrect block %02X with size %i\n", id, size);
            break;
        }
        if (bytestream2_get_bytes_left(&gb) < ssize) {
            av_log(avctx, AV_LOG_ERROR,
                   "Block size %i is out of bounds\n", size);
            break;
        }
        switch (id & WP_IDF_MASK) {
        case WP_ID_DECTERMS:
            if (size > MAX_TERMS) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation terms\n");
                s->terms = 0;
                bytestream2_skip(&gb, ssize);
                continue;
            }
            s->terms = size;
            for (i = 0; i < s->terms; i++) {
                uint8_t val = bytestream2_get_byte(&gb);
                s->decorr[s->terms - i - 1].value = (val & 0x1F) - 5;
                s->decorr[s->terms - i - 1].delta =  val >> 5;
            }
            got_terms = 1;
            break;
        case WP_ID_DECWEIGHTS:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            weights = size >> s->stereo_in;
            if (weights > MAX_TERMS || weights > s->terms) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation weights\n");
                bytestream2_skip(&gb, ssize);
                continue;
            }
            for (i = 0; i < weights; i++) {
                t = (int8_t)bytestream2_get_byte(&gb);
                s->decorr[s->terms - i - 1].weightA = t * (1 << 3);
                if (s->decorr[s->terms - i - 1].weightA > 0)
                    s->decorr[s->terms - i - 1].weightA +=
                        (s->decorr[s->terms - i - 1].weightA + 64) >> 7;
                if (s->stereo_in) {
                    t = (int8_t)bytestream2_get_byte(&gb);
                    s->decorr[s->terms - i - 1].weightB = t * (1 << 3);
                    if (s->decorr[s->terms - i - 1].weightB > 0)
                        s->decorr[s->terms - i - 1].weightB +=
                            (s->decorr[s->terms - i - 1].weightB + 64) >> 7;
                }
            }
            got_weights = 1;
            break;
        case WP_ID_DECSAMPLES:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            t = 0;
            for (i = s->terms - 1; (i >= 0) && (t < size); i--) {
                if (s->decorr[i].value > 8) {
                    s->decorr[i].samplesA[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    s->decorr[i].samplesA[1] =
                        wp_exp2(bytestream2_get_le16(&gb));

                    if (s->stereo_in) {
                        s->decorr[i].samplesB[0] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        s->decorr[i].samplesB[1] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        t                       += 4;
                    }
                    t += 4;
                } else if (s->decorr[i].value < 0) {
                    s->decorr[i].samplesA[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    s->decorr[i].samplesB[0] =
                        wp_exp2(bytestream2_get_le16(&gb));
                    t                       += 4;
                } else {
                    for (j = 0; j < s->decorr[i].value; j++) {
                        s->decorr[i].samplesA[j] =
                            wp_exp2(bytestream2_get_le16(&gb));
                        if (s->stereo_in) {
                            s->decorr[i].samplesB[j] =
                                wp_exp2(bytestream2_get_le16(&gb));
                        }
                    }
                    t += s->decorr[i].value * 2 * (s->stereo_in + 1);
                }
            }
            got_samples = 1;
            break;
        case WP_ID_ENTROPY:
            if (size != 6 * (s->stereo_in + 1)) {
                av_log(avctx, AV_LOG_ERROR,
                       "Entropy vars size should be %i, got %i.\n",
                       6 * (s->stereo_in + 1), size);
                bytestream2_skip(&gb, ssize);
                continue;
            }
            for (j = 0; j <= s->stereo_in; j++)
                for (i = 0; i < 3; i++) {
                    s->ch[j].median[i] = wp_exp2(bytestream2_get_le16(&gb));
                }
            got_entropy = 1;
            break;
        case WP_ID_HYBRID:
            if (s->hybrid_bitrate) {
                for (i = 0; i <= s->stereo_in; i++) {
                    s->ch[i].slow_level = wp_exp2(bytestream2_get_le16(&gb));
                    size               -= 2;
                }
            }
            for (i = 0; i < (s->stereo_in + 1); i++) {
                s->ch[i].bitrate_acc = bytestream2_get_le16(&gb) << 16;
                size                -= 2;
            }
            if (size > 0) {
                for (i = 0; i < (s->stereo_in + 1); i++) {
                    s->ch[i].bitrate_delta =
                        wp_exp2((int16_t)bytestream2_get_le16(&gb));
                }
            } else {
                for (i = 0; i < (s->stereo_in + 1); i++)
                    s->ch[i].bitrate_delta = 0;
            }
            got_hybrid = 1;
            break;
        case WP_ID_INT32INFO: {
            uint8_t val[4];
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, size = %i\n",
                       size);
                bytestream2_skip(&gb, ssize - 4);
                continue;
            }
            bytestream2_get_buffer(&gb, val, 4);
            if (val[0] > 31) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, extra_bits = %d (> 32)\n", val[0]);
                continue;
            } else if (val[0]) {
                s->extra_bits = val[0];
            } else if (val[1]) {
                s->shift = val[1];
            } else if (val[2]) {
                s->and   = s->or = 1;
                s->shift = val[2];
            } else if (val[3]) {
                s->and   = 1;
                s->shift = val[3];
            }
            if (s->shift > 31) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid INT32INFO, shift = %d (> 31)\n", s->shift);
                s->and = s->or = s->shift = 0;
                continue;
            }
            /* original WavPack decoder forces 32-bit lossy sound to be treated
             * as 24-bit one in order to have proper clipping */
            if (s->hybrid && bpp == 4 && s->post_shift < 8 && s->shift > 8) {
                s->post_shift      += 8;
                s->shift           -= 8;
                s->hybrid_maxclip >>= 8;
                s->hybrid_minclip >>= 8;
            }
            break;
        }
        case WP_ID_FLOATINFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR,
                       "Invalid FLOATINFO, size = %i\n", size);
                bytestream2_skip(&gb, ssize);
                continue;
            }
            s->float_flag    = bytestream2_get_byte(&gb);
            s->float_shift   = bytestream2_get_byte(&gb);
            s->float_max_exp = bytestream2_get_byte(&gb);
            got_float        = 1;
            bytestream2_skip(&gb, 1);
            break;
        case WP_ID_DATA:
            s->sc.offset = bytestream2_tell(&gb);
            s->sc.size   = size * 8;
            if ((ret = init_get_bits8(&s->gb, gb.buffer, size)) < 0)
                return ret;
            s->data_size = size * 8;
            bytestream2_skip(&gb, size);
            got_bs       = 1;
            break;
        case WP_ID_EXTRABITS:
            if (size <= 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid EXTRABITS, size = %i\n",
                       size);
                bytestream2_skip(&gb, size);
                continue;
            }
            s->extra_sc.offset = bytestream2_tell(&gb);
            s->extra_sc.size   = size * 8;
            if ((ret = init_get_bits8(&s->gb_extra_bits, gb.buffer, size)) < 0)
                return ret;
            s->crc_extra_bits  = get_bits_long(&s->gb_extra_bits, 32);
            bytestream2_skip(&gb, size);
            s->got_extra_bits  = 1;
            break;
        case WP_ID_CHANINFO:
            if (size <= 1) {
                av_log(avctx, AV_LOG_ERROR,
                       "Insufficient channel information\n");
                return AVERROR_INVALIDDATA;
            }
            chan = bytestream2_get_byte(&gb);
            switch (size - 2) {
            case 0:
                chmask = bytestream2_get_byte(&gb);
                break;
            case 1:
                chmask = bytestream2_get_le16(&gb);
                break;
            case 2:
                chmask = bytestream2_get_le24(&gb);
                break;
            case 3:
                chmask = bytestream2_get_le32(&gb);
                break;
            case 5:
                size = bytestream2_get_byte(&gb);
                if (avctx->channels != size)
                    av_log(avctx, AV_LOG_WARNING, "%i channels signalled"
                           " instead of %i.\n", size, avctx->channels);
                chan  |= (bytestream2_get_byte(&gb) & 0xF) << 8;
                chmask = bytestream2_get_le16(&gb);
                break;
            default:
                av_log(avctx, AV_LOG_ERROR, "Invalid channel info size %d\n",
                       size);
                chan   = avctx->channels;
                chmask = avctx->channel_layout;
            }
            break;
        case WP_ID_SAMPLE_RATE:
            if (size != 3) {
                av_log(avctx, AV_LOG_ERROR, "Invalid custom sample rate.\n");
                return AVERROR_INVALIDDATA;
            }
            sample_rate = bytestream2_get_le24(&gb);
            break;
        default:
            bytestream2_skip(&gb, size);
        }
        if (id & WP_IDF_ODD)
            bytestream2_skip(&gb, 1);
    }

    if (!got_terms) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation terms\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_weights) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation weights\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_samples) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation samples\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_entropy) {
        av_log(avctx, AV_LOG_ERROR, "No block with entropy info\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->hybrid && !got_hybrid) {
        av_log(avctx, AV_LOG_ERROR, "Hybrid config not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_bs) {
        av_log(avctx, AV_LOG_ERROR, "Packed samples not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (!got_float && avctx->sample_fmt == AV_SAMPLE_FMT_FLTP) {
        av_log(avctx, AV_LOG_ERROR, "Float information not found\n");
        return AVERROR_INVALIDDATA;
    }
    if (s->got_extra_bits && avctx->sample_fmt != AV_SAMPLE_FMT_FLTP) {
        const int size   = get_bits_left(&s->gb_extra_bits);
        const int wanted = s->samples * s->extra_bits << s->stereo_in;
        if (size < wanted) {
            av_log(avctx, AV_LOG_ERROR, "Too small EXTRABITS\n");
            s->got_extra_bits = 0;
        }
    }

    if (!wc->ch_offset) {
        int sr = (s->frame_flags >> 23) & 0xf;
        if (sr == 0xf) {
            if (!sample_rate) {
                av_log(avctx, AV_LOG_ERROR, "Custom sample rate missing.\n");
                return AVERROR_INVALIDDATA;
            }
            avctx->sample_rate = sample_rate;
        } else
            avctx->sample_rate = wv_rates[sr];

        if (multiblock) {
            if (chan)
                avctx->channels = chan;
            if (chmask)
                avctx->channel_layout = chmask;
        } else {
            avctx->channels       = s->stereo ? 2 : 1;
            avctx->channel_layout = s->stereo ? AV_CH_LAYOUT_STEREO :
                                                AV_CH_LAYOUT_MONO;
        }

        /* get output buffer */
        frame->nb_samples = s->samples + 1;
        if ((ret = ff_thread_get_buffer(avctx, &tframe, 0)) < 0)
            return ret;
        frame->nb_samples = s->samples;
    }

    if (wc->ch_offset + s->stereo >= avctx->channels) {
        av_log(avctx, AV_LOG_WARNING, "Too many channels coded in a packet.\n");
        return ((avctx->err_recognition & AV_EF_EXPLODE) || !wc->ch_offset) ? AVERROR_INVALIDDATA : 0;
    }

    samples_l = frame->extended_data[wc->ch_offset];
    if (s->stereo)
        samples_r = frame->extended_data[wc->ch_offset + 1];

    wc->ch_offset += 1 + s->stereo;

    if (s->stereo_in) {
        ret = wv_unpack_stereo(s, &s->gb, samples_l, samples_r, avctx->sample_fmt);
        if (ret < 0)
            return ret;
    } else {
        ret = wv_unpack_mono(s, &s->gb, samples_l, avctx->sample_fmt);
        if (ret < 0)
            return ret;

        if (s->stereo)
            memcpy(samples_r, samples_l, bpp * s->samples);
    }

    return 0;
}
static int wavpack_decode_block(AVCodecContext *avctx, int block_no, /* <=== */ 
                                void *data, int *got_frame_ptr,
                                const uint8_t *buf, int buf_size)
{
    WavpackContext *wc = avctx->priv_data;
    WavpackFrameContext *s;
    void *samples = data;
    int samplecount;
    int got_terms   = 0, got_weights = 0, got_samples = 0,
        got_entropy = 0, got_bs      = 0, got_float   = 0; got_hybrid = 0;
    const uint8_t *orig_buf = buf;
    const uint8_t *buf_end  = buf + buf_size;
    int i, j, id, size, ssize, weights, t;
    int bpp, chan, chmask;

    if (buf_size == 0) {
        *got_frame_ptr = 0;
        return 0;
    }

    if (block_no >= wc->fdec_num && wv_alloc_frame_context(wc) < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error creating frame decode context\n");
        return -1;
    }

    s = wc->fdec[block_no];
    if (!s) {
        av_log(avctx, AV_LOG_ERROR, "Context for block %d is not present\n", block_no);
        return -1;
    }

    memset(s->decorr, 0, MAX_TERMS * sizeof(Decorr));
    memset(s->ch, 0, sizeof(s->ch));
    s->extra_bits = 0;
    s->and = s->or = s->shift = 0;
    s->got_extra_bits = 0;

    if (!wc->mkv_mode) {
        s->samples = AV_RL32(buf); buf += 4;
        if (!s->samples) {
            *got_frame_ptr = 0;
            return 0;
        }
    } else {
        s->samples = wc->samples;
    }
    s->frame_flags = AV_RL32(buf); buf += 4;
    bpp = av_get_bytes_per_sample(avctx->sample_fmt);
    samples = (uint8_t*)samples + bpp * wc->ch_offset;

    s->stereo         = !(s->frame_flags & WV_MONO);
    s->stereo_in      =  (s->frame_flags & WV_FALSE_STEREO) ? 0 : s->stereo;
    s->joint          =   s->frame_flags & WV_JOINT_STEREO;
    s->hybrid         =   s->frame_flags & WV_HYBRID_MODE;
    s->hybrid_bitrate =   s->frame_flags & WV_HYBRID_BITRATE;
    s->hybrid_maxclip = (1LL << ((((s->frame_flags & 0x03) + 1) << 3) - 1)) - 1;
    s->post_shift     = 8 * (bpp - 1 - (s->frame_flags & 0x03)) +
                        ((s->frame_flags >> 13) & 0x1f);
    s->CRC            = AV_RL32(buf); buf += 4;
    if (wc->mkv_mode)
        buf += 4; //skip block size;

    wc->ch_offset += 1 + s->stereo;

    // parse metadata blocks
    while (buf < buf_end) {
        id   = *buf++;
        size = *buf++;
        if (id & WP_IDF_LONG) {
            size |= (*buf++) << 8;
            size |= (*buf++) << 16;
        }
        size <<= 1; // size is specified in words
        ssize = size;
        if (id & WP_IDF_ODD)
            size--;
        if (size < 0) {
            av_log(avctx, AV_LOG_ERROR, "Got incorrect block %02X with size %i\n", id, size);
            break;
        }
        if (buf + ssize > buf_end) {
            av_log(avctx, AV_LOG_ERROR, "Block size %i is out of bounds\n", size);
            break;
        }
        if (id & WP_IDF_IGNORE) {
            buf += ssize;
            continue;
        }
        switch (id & WP_IDF_MASK) {
        case WP_ID_DECTERMS:
            if (size > MAX_TERMS) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation terms\n");
                s->terms = 0;
                buf += ssize;
                continue;
            }
            s->terms = size;
            for (i = 0; i < s->terms; i++) {
                s->decorr[s->terms - i - 1].value = (*buf & 0x1F) - 5;
                s->decorr[s->terms - i - 1].delta = *buf >> 5;
                buf++;
            }
            got_terms = 1;
            break;
        case WP_ID_DECWEIGHTS:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            weights = size >> s->stereo_in;
            if (weights > MAX_TERMS || weights > s->terms) {
                av_log(avctx, AV_LOG_ERROR, "Too many decorrelation weights\n");
                buf += ssize;
                continue;
            }
            for (i = 0; i < weights; i++) {
                t = (int8_t)(*buf++);
                s->decorr[s->terms - i - 1].weightA = t << 3;
                if (s->decorr[s->terms - i - 1].weightA > 0)
                    s->decorr[s->terms - i - 1].weightA +=
                            (s->decorr[s->terms - i - 1].weightA + 64) >> 7;
                if (s->stereo_in) {
                    t = (int8_t)(*buf++);
                    s->decorr[s->terms - i - 1].weightB = t << 3;
                    if (s->decorr[s->terms - i - 1].weightB > 0)
                        s->decorr[s->terms - i - 1].weightB +=
                                (s->decorr[s->terms - i - 1].weightB + 64) >> 7;
                }
            }
            got_weights = 1;
            break;
        case WP_ID_DECSAMPLES:
            if (!got_terms) {
                av_log(avctx, AV_LOG_ERROR, "No decorrelation terms met\n");
                continue;
            }
            t = 0;
            for i = s->terms - 1; (i >= 0) && (t < size); i--) {
                if (s->decorr[i].value > 8) {
                    s->decorr[i].samplesA[0] = wp_exp2(AV_RL16(buf)); buf += 2;
                    s->decorr[i].samplesA[1] = wp_exp2(AV_RL16(buf)); buf += 2;
                    if (s->stereo_in) {
                        s->decorr[i].samplesB[0] = wp_exp2(AV_RL16(buf)); buf += 2;
                        s->decorr[i].samplesB[1] = wp_exp2(AV_RL16(buf)); buf += 2;
                        t += 4;
                    }
                    t += 4;
                } else if (s->decorr[i].value < 0) {
                    s->decorr[i].samplesA[0] = wp_exp2(AV_RL16(buf)); buf += 2;
                    s->decorr[i].samplesB[0] = wp_exp2(AV_RL16(buf)); buf += 2;
                    t += 4;
                } else {
                    for (j = 0; j < s->decorr[i].value; j++) {
                        s->decorr[i].samplesA[j] = wp_exp2(AV_RL16(buf)); buf += 2;
                        if (s->stereo_in)
                            s->decorr[i].samplesB[j] = wp_exp2(AV_RL16(buf)); buf += 2;
                    }
                    t += s->decorr[i].value * 2 * (s->stereo_in + 1);
                }
            }
            got_samples = 1;
            break;
        case WP_ID_ENTROPY:
            if (size != 6 * (s->stereo_in + 1)) {
                av_log(avctx, AV_LOG_ERROR, "Entropy vars size should be %i, "
                       "got %i", 6 * (s->stereo_in + 1), size);
                buf += ssize;
                continue;
            }
            for (j = 0; j <= s->stereo_in; j++) {
                for (i = 0; i < 3; i++) {
                    s->ch[j].median[i] = wp_exp2(AV_RL16(buf));
                    buf += 2;
                }
            }
            got_entropy = 1;
            break;
        case WP_ID_HYBRID:
            if (s->hybrid_bitrate) {
                for (i = 0; i <= s->stereo_in; i++) {
                    s->ch[i].slow_level = wp_exp2(AV_RL16(buf));
                    buf += 2;
                    size -= 2;
                }
            }
            for (i = 0; i < (s->stereo_in + 1); i++) {
                s->ch[i].bitrate_acc = AV_RL16(buf) << 16;
                buf += 2;
                size -= 2;
            }
            if (size > 0) {
                for (i = 0; i < (s->stereo_in + 1); i++) {
                    s->ch[i].bitrate_delta = wp_exp2((int16_t)AV_RL16(buf));
                    buf += 2;
                }
            } else {
                for (i = 0; i < (s->stereo_in + 1); i++)
                    s->ch[i].bitrate_delta = 0;
            }
            got_hybrid = 1;
            break;
        case WP_ID_INT32INFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid INT32INFO, size = %i, sent_bits = %i\n", size, *buf);
                buf += ssize;
                continue;
            }
            if (buf[0])
                s->extra_bits = buf[0];
            else if (buf[1])
                s->shift = buf[1];
            else if (buf[2]){
                s->and = s->or = 1;
                s->shift = buf[2];
            } else if(buf[3]) {
                s->and   = 1;
                s->shift = buf[3];
            }
            buf += 4;
            break;
        case WP_ID_FLOATINFO:
            if (size != 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid FLOATINFO, size = %i\n", size);
                buf += ssize;
                continue;
            }
            s->float_flag    = buf[0];
            s->float_shift   = buf[1];
            s->float_max_exp = buf[2];
            buf += 4;
            got_float = 1;
            break;
        case WP_ID_DATA:
            s->sc.offset = buf - orig_buf;
            s->sc.size   = size * 8;
            init_get_bits(&s->gb, buf, size * 8);
            s->data_size = size * 8;
            buf += size;
            got_bs = 1;
            break;
        case WP_ID_EXTRABITS:
            if (size <= 4) {
                av_log(avctx, AV_LOG_ERROR, "Invalid EXTRABITS, size = %i\n",
                       size);
                buf += size;
                continue;
            }
            s->extra_sc.offset = buf - orig_buf;
            s->extra_sc.size   = size * 8;
            init_get_bits(&s->gb_extra_bits, buf, size * 8);
            s->crc_extra_bits = get_bits_long(&s->gb_extra_bits, 32);
            buf += size;
            s->got_extra_bits = 1;
            break;
        case WP_ID_CHANINFO:
            if (size <= 1) {
                av_log(avctx, AV_LOG_ERROR, "Insufficient channel information\n");
                return -1;
            }
            chan = *buf++;
            switch (size - 2) {
            case 0: chmask = *buf;         break;
            case 1: chmask = AV_RL16(buf); break;
            case 2: chmask = AV_RL24(buf); break;
            case 3: chmask = AV_RL32(buf); break;
            case 5:
                chan |= (buf[1] & 0xF) << 8;
                chmask = AV_RL24(buf + 2);
                break;
            default:
                av_log(avctx, AV_LOG_ERROR, "Invalid channel info size %d\n",
                       size);
                chan   = avctx->channels;
                chmask = avctx->channel_layout;
            }
            if (chan != avctx->channels) {
                av_log(avctx, AV_LOG_ERROR, "Block reports total %d channels, "
                       "decoder believes it's %d channels\n", chan,
                       avctx->channels);
                return -1;
            }
            if (!avctx->channel_layout)
                avctx->channel_layout = chmask;
            buf += size - 1;
            break;
        default:
            buf += size;
        }
        if (id & WP_IDF_ODD)
            buf++;
    }

    if (!got_terms) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation terms\n");
        return -1;
    }
    if (!got_weights) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation weights\n");
        return -1;
    }
    if (!got_samples) {
        av_log(avctx, AV_LOG_ERROR, "No block with decorrelation samples\n");
        return -1;
    }
    if (!got_entropy) {
        av_log(avctx, AV_LOG_ERROR, "No block with entropy info\n");
        return -1;
    }
    if (s->hybrid && !got_hybrid) {
        av_log(avctx, AV_LOG_ERROR, "Hybrid config not found\n");
        return -1;
    }
    if (!got_bs) {
        av_log(avctx, AV_LOG_ERROR, "Packed samples not found\n");
        return -1;
    }
    if (!got_float && avctx->sample_fmt == AV_SAMPLE_FMT_FLT) {
        av_log(avctx, AV_LOG_ERROR, "Float information not found\n");
        return -1;
    }
    if (s->got_extra_bits && avctx->sample_fmt != AV_SAMPLE_FMT_FLT) {
        const int size   = get_bits_left(&s->gb_extra_bits);
        const int wanted = s->samples * s->extra_bits << s->stereo_in;
        if (size < wanted) {
            av_log(avctx, AV_LOG_ERROR, "Too small EXTRABITS\n");
            s->got_extra_bits = 0;
        }
    }

    if (s->stereo_in) {
        if (avctx->sample_fmt == AV_SAMPLE_FMT_S16)
            samplecount = wv_unpack_stereo(s, &s->gb, samples, AV_SAMPLE_FMT_S16);
        else if (avctx->sample_fmt == AV_SAMPLE_FMT_S32)
            samplecount = wv_unpack_stereo(s, &s->gb, samples, AV_SAMPLE_FMT_S32);
        else
            samplecount = wv_unpack_stereo(s, &s->gb, samples, AV_SAMPLE_FMT_FLT);

        if (samplecount < 0)
            return -1;

        samplecount >>= 1;
    } else {
        const int channel_stride = avctx->channels;

        if (avctx->sample_fmt == AV_SAMPLE_FMT_S16)
            samplecount = wv_unpack_mono(s, &s->gb, samples, AV_SAMPLE_FMT_S16);
        else if (avctx->sample_fmt == AV_SAMPLE_FMT_S32)
            samplecount = wv_unpack_mono(s, &s->gb, samples, AV_SAMPLE_FMT_S32);
        else
            samplecount = wv_unpack_mono(s, &s->gb, samples, AV_SAMPLE_FMT_FLT);

        if (samplecount < 0)
            return -1;

        if (s->stereo && avctx->sample_fmt == AV_SAMPLE_FMT_S16) {
            int16_t *dst = (int16_t*)samples + 1;
            int16_t *src = (int16_t*)samples;
            int cnt = samplecount;
            while (cnt--) {
                *dst = *src;
                src += channel_stride;
                dst += channel_stride;
            }
        } else if (s->stereo && avctx->sample_fmt == AV_SAMPLE_FMT_S32) {
            int32_t *dst = (int32_t*)samples + 1;
            int32_t *src = (int32_t*)samples;
            int cnt = samplecount;
            while (cnt--) {
                *dst = *src;
                src += channel_stride;
                dst += channel_stride;
            }
        } else if (s->stereo) {
            float *dst = (float*)samples + 1;
            float *src = (float*)samples;
            int cnt = samplecount;
            while (cnt--) {
                *dst = *src;
                src += channel_stride;
                dst += channel_stride;
            }
        }
    }

    *got_frame_ptr = 1;

    return samplecount * bpp;
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        if (av_image_check_size(FFMAX(left + w, ctx->width),
                                FFMAX(top  + h, ctx->height), 0, ctx->avctx) < 0)
            return AVERROR_INVALIDDATA;
        avcodec_set_dimensions(ctx->avctx, FFMAX(left + w, ctx->width),
                                           FFMAX(top  + h, ctx->height));
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        ctx->avctx->width  = FFMAX(left + w, ctx->width);
        
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        ctx->avctx->width  = FFMAX(left + w, ctx->width);
        
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        if (av_image_check_size(FFMAX(left + w, ctx->width),
                                FFMAX(top  + h, ctx->height), 0, ctx->avctx) < 0)
            return AVERROR_INVALIDDATA;
        avcodec_set_dimensions(ctx->avctx, FFMAX(left + w, ctx->width),
                                           FFMAX(top  + h, ctx->height));
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        if (av_image_check_size(FFMAX(left + w, ctx->width),
                                FFMAX(top  + h, ctx->height), 0, ctx->avctx) < 0)
            return AVERROR_INVALIDDATA;
        avcodec_set_dimensions(ctx->avctx, FFMAX(left + w, ctx->width),
                                           FFMAX(top  + h, ctx->height));
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        
        ctx->avctx->height = FFMAX(top + h, ctx->height);
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        
        ctx->avctx->height = FFMAX(top + h, ctx->height);
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int process_frame_obj(SANMVideoContext *ctx) /* <=== */ 
{
    uint16_t codec, top, left, w, h;

    codec = bytestream2_get_le16u(&ctx->gb);
    left  = bytestream2_get_le16u(&ctx->gb);
    top   = bytestream2_get_le16u(&ctx->gb);
    w     = bytestream2_get_le16u(&ctx->gb);
    h     = bytestream2_get_le16u(&ctx->gb);

    if (ctx->width < left + w || ctx->height < top + h) {
        if (av_image_check_size(FFMAX(left + w, ctx->width),
                                FFMAX(top  + h, ctx->height), 0, ctx->avctx) < 0)
            return AVERROR_INVALIDDATA;
        avcodec_set_dimensions(ctx->avctx, FFMAX(left + w, ctx->width),
                                           FFMAX(top  + h, ctx->height));
        init_sizes(ctx, left + w, top + h);
        if (init_buffers(ctx)) {
            av_log(ctx->avctx, AV_LOG_ERROR, "error resizing buffers\n");
            return AVERROR(ENOMEM);
        }
    }
    bytestream2_skip(&ctx->gb, 4);

    av_dlog(ctx->avctx, "subcodec %d\n", codec);
    switch (codec) {
    case 1:
    case 3:
        return old_codec1(ctx, top, left, w, h);
        break;
    case 37:
        return old_codec37(ctx, top, left, w, h);
        break;
    case 47:
        return old_codec47(ctx, top, left, w, h);
        break;
    default:
        av_log_ask_for_sample(ctx->avctx, "unknown subcodec %d\n", codec);
        return AVERROR_PATCHWELCOME;
    }
}
static int decode_frame(AVCodecContext * avctx, void *data, int *data_size, uint8_t * buf, /* <=== */ 
                        int buf_size)
{
    KmvcContext *const ctx = (KmvcContext *) avctx->priv_data;
    uint8_t *out, *src;
    int i;
    int header;
    int blocksize;

    if (ctx->pic.data[0])
        avctx->release_buffer(avctx, &ctx->pic);

    ctx->pic.reference = 1;
    ctx->pic.buffer_hints = FF_BUFFER_HINTS_VALID;
    if (avctx->get_buffer(avctx, &ctx->pic) < 0) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return -1;
    }

    header = *buf++;

    /* blocksize 127 is really palette change event */
    if (buf[0] == 127) {
        buf += 3;
        for (i = 0; i < 127; i++) {
            ctx->pal[i + (header & 0x81)] = (buf[0] << 16) | (buf[1] << 8) | buf[2];
            buf += 4;
        }
        buf -= 127 * 4 + 3;
    }

    if (header & KMVC_KEYFRAME) {
        ctx->pic.key_frame = 1;
        ctx->pic.pict_type = FF_I_TYPE;
    } else {
        ctx->pic.key_frame = 0;
        ctx->pic.pict_type = FF_P_TYPE;
    }

    /* if palette has been changed, copy it from palctrl */
    if (ctx->avctx->palctrl && ctx->avctx->palctrl->palette_changed) {
        memcpy(ctx->pal, ctx->avctx->palctrl->palette, AVPALETTE_SIZE);
        ctx->setpal = 1;
        ctx->avctx->palctrl->palette_changed = 0;
    }

    if (header & KMVC_PALETTE) {
        ctx->pic.palette_has_changed = 1;
        // palette starts from index 1 and has 127 entries
        for (i = 1; i <= ctx->palsize; i++) {
            ctx->pal[i] = (buf[0] << 16) | (buf[1] << 8) | buf[2];
            buf += 3;
        }
    }

    if (ctx->setpal) {
        ctx->setpal = 0;
        ctx->pic.palette_has_changed = 1;
    }

    /* make the palette available on the way out */
    memcpy(ctx->pic.data[1], ctx->pal, 1024);

    blocksize = *buf++;

    if (blocksize != 8 && blocksize != 127) {
        av_log(avctx, AV_LOG_ERROR, "Block size = %i\n", blocksize);
        return -1;
    }
    memset(ctx->cur, 0, 320 * 200);
    switch (header & KMVC_METHOD) {
    case 0:
    case 1: // used in palette changed event
        memcpy(ctx->cur, ctx->prev, 320 * 200);
        break;
    case 3:
        kmvc_decode_intra_8x8(ctx, buf, avctx->width, avctx->height);
        break;
    case 4:
        kmvc_decode_inter_8x8(ctx, buf, avctx->width, avctx->height);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown compression method %i\n", header & KMVC_METHOD);
        return -1;
    }

    out = ctx->pic.data[0];
    src = ctx->cur;
    for (i = 0; i < avctx->height; i++) {
        memcpy(out, src, avctx->width);
        src += 320;
        out += ctx->pic.linesize[0];
    }

    /* flip buffers */
    if (ctx->cur == ctx->frm0) {
        ctx->cur = ctx->frm1;
        ctx->prev = ctx->frm0;
    } else {
        ctx->cur = ctx->frm0;
        ctx->prev = ctx->frm1;
    }

    *data_size = sizeof(AVFrame);
    *(AVFrame *) data = ctx->pic;

    /* always report that the buffer was completely consumed */
    return buf_size;
}
static int decode_frame(AVCodecContext *avctx, void *data, int *data_size, AVPacket *avpkt) /* <=== */ 
{
    const uint8_t *buf = avpkt->data;
    const uint8_t *buf_end = buf + avpkt->size;
    KgvContext * const c = avctx->priv_data;
    int offsets[7];
    uint16_t *out, *prev;
    int outcnt = 0, maxcnt;
    int w, h, i;

    if (avpkt->size < 2)
        return -1;

    w = (buf[0] + 1) * 8;
    h = (buf[1] + 1) * 8;
    buf += 2;

    if (avcodec_check_dimensions(avctx, w, h))
        return -1;

    if (w != avctx->width || h != avctx->height)
        avcodec_set_dimensions(avctx, w, h);

    maxcnt = w * h;

    out = av_realloc(c->cur, w * h * 2);
    if (!out)
        return -1;
    c->cur = out;

    prev = av_realloc(c->prev, w * h * 2);
    if (!prev)
        return -1;
    c->prev = prev;

    
        offsets[i] = -1;

    while (outcnt < maxcnt && buf_end - 2 > buf) {
        int code = AV_RL16(buf);
        buf += 2;

        if (!(code & 0x8000)) {
            out[outcnt++] = code; // rgb555 pixel coded directly
        } else {
            int count;
            uint16_t *inp;

            if ((code & 0x6000) == 0x6000) {
                // copy from previous frame
                int oidx = (code >> 10) & 7;
                int start;

                count = (code & 0x3FF) + 3;

                if (offsets[oidx] < 0) {
                    if (buf_end - 3 < buf)
                        break;
                    offsets[oidx] = AV_RL24(buf);
                    buf += 3;
                }

                start = (outcnt + offsets[oidx]) % maxcnt;

                if (maxcnt - start < count)
                    break;

                inp = prev + start;
            } else {
                // copy from earlier in this frame
                int offset = (code & 0x1FFF) + 1;

                if (!(code & 0x6000)) {
                    count = 2;
                } else if ((code & 0x6000) == 0x2000) {
                    count = 3;
                } else {
                    if (buf_end - 1 < buf)
                        break;
                    count = 4 + *buf++;
                }

                if (outcnt < offset)
                    break;

                inp = out + outcnt - offset;
            }

            if (maxcnt - outcnt < count)
                break;

            for (i = 0; i < count; i++)
                out[outcnt++] = inp[i];
        }
    }

    if (outcnt - maxcnt)
        av_log(avctx, AV_LOG_DEBUG, "frame finished with %d diff\n", outcnt - maxcnt);

    c->pic.data[0]     = (uint8_t *)c->cur;
    c->pic.linesize[0] = w * 2;

    *data_size = sizeof(AVFrame);
    *(AVFrame*)data = c->pic;

    FFSWAP(uint16_t *, c->cur, c->prev);

    return avpkt->size;
}
static int decode_frame(AVCodecContext *avctx, void *data, /* <=== */ 
                        int *got_frame, AVPacket *avpkt)
{
    EXRContext *s = avctx->priv_data;
    ThreadFrame frame = { .f = data };
    AVFrame *picture = data;
    uint8_t *ptr;

    int y, ret;
    int out_line_size;
    int nb_blocks;/* nb scanline or nb tile */

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    if ((ret = decode_header(s)) < 0)
        return ret;

    switch (s->pixel_type) {
    case EXR_FLOAT:
    case EXR_HALF:
        if (s->channel_offsets[3] >= 0) {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_RGBA64;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_YA16;
            }
        } else {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_RGB48;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            }
        }
        break;
    case EXR_UINT:
        avpriv_request_sample(avctx, "32-bit unsigned int");
        return AVERROR_PATCHWELCOME;
    default:
        av_log(avctx, AV_LOG_ERROR, "Missing channel list.\n");
        return AVERROR_INVALIDDATA;
    }

    if (s->apply_trc_type != AVCOL_TRC_UNSPECIFIED)
        avctx->color_trc = s->apply_trc_type;

    switch (s->compression) {
    case EXR_RAW:
    case EXR_RLE:
    case EXR_ZIP1:
        s->scan_lines_per_block = 1;
        break;
    case EXR_PXR24:
    case EXR_ZIP16:
        s->scan_lines_per_block = 16;
        break;
    case EXR_PIZ:
    case EXR_B44:
    case EXR_B44A:
        s->scan_lines_per_block = 32;
        break;
    default:
        avpriv_report_missing_feature(avctx, "Compression %d", s->compression);
        return AVERROR_PATCHWELCOME;
    }

    /* Verify the xmin, xmax, ymin, ymax and xdelta before setting
     * the actual image size. */
    if (s->xmin > s->xmax                  ||
        s->ymin > s->ymax                  ||
        s->xdelta != s->xmax - s->xmin + 1 ||
        s->xmax >= s->w                    ||
        s->ymax >= s->h) {
        av_log(avctx, AV_LOG_ERROR, "Wrong or missing size information.\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_set_dimensions(avctx, s->w, s->h)) < 0)
        return ret;

    s->desc          = av_pix_fmt_desc_get(avctx->pix_fmt);
    if (!s->desc)
        return AVERROR_INVALIDDATA;
    out_line_size    = avctx->width * 2 * s->desc->nb_components;

    if (s->is_tile) {
        nb_blocks = ((s->xdelta + s->tile_attr.xSize - 1) / s->tile_attr.xSize) *
        ((s->ydelta + s->tile_attr.ySize - 1) / s->tile_attr.ySize);
    } else { /* scanline */
        nb_blocks = (s->ydelta + s->scan_lines_per_block - 1) /
        s->scan_lines_per_block;
    }

    if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
        return ret;

    if (bytestream2_get_bytes_left(&s->gb) < nb_blocks * 8)
        return AVERROR_INVALIDDATA;

    // save pointer we are going to use in decode_block
    s->buf      = avpkt->data;
    s->buf_size = avpkt->size;
    ptr         = picture->data[0];

    // Zero out the start if ymin is not 0
    for (y = 0; y < s->ymin; y++) {
        memset(ptr, 0, out_line_size);
        ptr += picture->linesize[0];
    }

    s->picture = picture;

    avctx->execute2(avctx, decode_block, s->thread_data, NULL, nb_blocks);

    // Zero out the end if ymax+1 is not h
    for (y = s->ymax + 1; y < avctx->height; y++) {
        memset(ptr, 0, out_line_size);
        ptr += picture->linesize[0];
    }

    picture->pict_type = AV_PICTURE_TYPE_I;
    *got_frame = 1;

    return avpkt->size;
}
static int decode_frame(AVCodecContext *avctx, /* <=== */ 
                        void *data, int *data_size, AVPacket *avpkt)
{
    TiffContext *const s = avctx->priv_data;
    AVFrame *picture = data;
    AVFrame *const p = &s->picture;
    unsigned off;
    int id, le, ret;
    int i, j, entries;
    int stride;
    unsigned soff, ssize;
    uint8_t *dst;
    GetByteContext stripsizes;
    GetByteContext stripdata;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    //parse image header
    if (avpkt->size < 8)
        return AVERROR_INVALIDDATA;
    id = bytestream2_get_le16u(&s->gb);
    if (id == 0x4949)
        le = 1;
    else if (id == 0x4D4D)
        le = 0;
    else {
        av_log(avctx, AV_LOG_ERROR, "TIFF header not found\n");
        return -1;
    }
    s->le = le;
    s->invert = 0;
    s->compr = TIFF_RAW;
    s->fill_order = 0;
    free_geotags(s);
    /* free existing metadata */
    av_dict_free(&s->picture.metadata);

    // As TIFF 6.0 specification puts it "An arbitrary but carefully chosen number
    // that further identifies the file as a TIFF file"
    if (tget_short(&s->gb, le) != 42) {
        av_log(avctx, AV_LOG_ERROR,
               "The answer to life, universe and everything is not correct!\n");
        return -1;
    }
    // Reset these offsets so we can tell if they were set this frame
    s->stripsizesoff = s->strippos = 0;
    /* parse image file directory */
    off = tget_long(&s->gb, le);
    if (off >= UINT_MAX - 14 || avpkt->size < off + 14) {
        av_log(avctx, AV_LOG_ERROR, "IFD offset is greater than image size\n");
        return AVERROR_INVALIDDATA;
    }
    bytestream2_seek(&s->gb, off, SEEK_SET);
    entries = tget_short(&s->gb, le);
    if (bytestream2_get_bytes_left(&s->gb) < entries * 12)
        return AVERROR_INVALIDDATA;
    for (i = 0; i < entries; i++) {
        if (tiff_decode_tag(s) < 0)
            return -1;
    }

    for (i = 0; i<s->geotag_count; i++) {
        const char *keyname = get_geokey_name(s->geotags[i].key);
        if (!keyname) {
            av_log(avctx, AV_LOG_WARNING, "Unknown or unsupported GeoTIFF key %d\n", s->geotags[i].key);
            continue;
        }
        if (get_geokey_type(s->geotags[i].key) != s->geotags[i].type) {
            av_log(avctx, AV_LOG_WARNING, "Type of GeoTIFF key %d is wrong\n", s->geotags[i].key);
            continue;
        }
        ret = av_dict_set(&s->picture.metadata, keyname, s->geotags[i].val, 0);
        if (ret<0) {
            av_log(avctx, AV_LOG_ERROR, "Writing metadata with key '%s' failed\n", keyname);
            return ret;
        }
    }

    if (!s->strippos && !s->stripoff) {
        av_log(avctx, AV_LOG_ERROR, "Image data is missing\n");
        return -1;
    }
    /* now we have the data and may start decoding */
    if ((ret = init_image(s)) < 0)
        return ret;

    if (s->strips == 1 && !s->stripsize) {
        av_log(avctx, AV_LOG_WARNING, "Image data size missing\n");
        s->stripsize = avpkt->size - s->stripoff;
    }
    stride = p->linesize[0];
    dst = p->data[0];

    if (s->stripsizesoff) {
        if (s->stripsizesoff >= avpkt->size)
            return AVERROR_INVALIDDATA;
        bytestream2_init(&stripsizes, avpkt->data + s->stripsizesoff, avpkt->size - s->stripsizesoff);
    }
    if (s->strippos) {
        if (s->strippos >= avpkt->size)
            return AVERROR_INVALIDDATA;
        bytestream2_init(&stripdata, avpkt->data + s->strippos, avpkt->size - s->strippos);
    }

    for (i = 0; i < s->height; i += s->rps) {
        if (s->stripsizesoff)
            ssize = tget(&stripsizes, s->sstype, s->le);
        else
            ssize = s->stripsize;

        if (s->strippos)
            soff = tget(&stripdata, s->sot, s->le);
        else
            soff = s->stripoff;

        if (soff > avpkt->size || ssize > avpkt->size - soff) {
            av_log(avctx, AV_LOG_ERROR, "Invalid strip size/offset\n");
            return -1;
        }
        if (tiff_unpack_strip(s, dst, stride, avpkt->data + soff, ssize,
                              FFMIN(s->rps, s->height - i)) < 0)
            break;
        dst += s->rps * stride;
    }
    if (s->predictor == 2) {
        dst = p->data[0];
        soff = s->bpp >> 3;
        ssize = s->width * soff;
        if (s->avctx->pix_fmt == PIX_FMT_RGB48LE ||
            s->avctx->pix_fmt == PIX_FMT_RGBA64LE) {
            for (i = 0; i < s->height; i++) {
                for (j = soff; j < ssize; j += 2)
                    AV_WL16(dst + j, AV_RL16(dst + j) + AV_RL16(dst + j - soff));
                dst += stride;
            }
        } else if (s->avctx->pix_fmt == PIX_FMT_RGB48BE ||
                   s->avctx->pix_fmt == PIX_FMT_RGBA64BE) {
            for (i = 0; i < s->height; i++) {
                for (j = soff; j < ssize; j += 2)
                    AV_WB16(dst + j, AV_RB16(dst + j) + AV_RB16(dst + j - soff));
                dst += stride;
            }
        } else {
            for (i = 0; i < s->height; i++) {
                for (j = soff; j < ssize; j++)
                    dst[j] += dst[j - soff];
                dst += stride;
            }
        }
    }

    if (s->invert) {
        dst = s->picture.data[0];
        for (i = 0; i < s->height; i++) {
            for (j = 0; j < s->picture.linesize[0]; j++)
                dst[j] = (s->avctx->pix_fmt == PIX_FMT_PAL8 ? (1<<s->bpp) - 1 : 255) - dst[j];
            dst += s->picture.linesize[0];
        }
    }
    *picture   = s->picture;
    *data_size = sizeof(AVPicture);

    return avpkt->size;
}
static int decode_frame(AVCodecContext * avctx, void *data, int *data_size, uint8_t * buf, /* <=== */ 
                        int buf_size)
{
    KmvcContext *const ctx = (KmvcContext *) avctx->priv_data;
    uint8_t *out, *src;
    int i;
    int header;
    int blocksize;

    if (ctx->pic.data[0])
        avctx->release_buffer(avctx, &ctx->pic);

    ctx->pic.reference = 1;
    ctx->pic.buffer_hints = FF_BUFFER_HINTS_VALID;
    if (avctx->get_buffer(avctx, &ctx->pic) < 0) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return -1;
    }

    header = *buf++;

    /* blocksize 127 is really palette change event */
    if (buf[0] == 127) {
        buf += 3;
        for (i = 0; i < 127; i++) {
            ctx->pal[i + (header & 0x81)] = (buf[0] << 16) | (buf[1] << 8) | buf[2];
            buf += 4;
        }
        buf -= 127 * 4 + 3;
    }

    if (header & KMVC_KEYFRAME) {
        ctx->pic.key_frame = 1;
        ctx->pic.pict_type = FF_I_TYPE;
    } else {
        ctx->pic.key_frame = 0;
        ctx->pic.pict_type = FF_P_TYPE;
    }

    /* if palette has been changed, copy it from palctrl */
    if (ctx->avctx->palctrl && ctx->avctx->palctrl->palette_changed) {
        memcpy(ctx->pal, ctx->avctx->palctrl->palette, AVPALETTE_SIZE);
        ctx->setpal = 1;
        ctx->avctx->palctrl->palette_changed = 0;
    }

    if (header & KMVC_PALETTE) {
        ctx->pic.palette_has_changed = 1;
        // palette starts from index 1 and has 127 entries
        for (i = 1; i <= ctx->palsize; i++) {
            ctx->pal[i] = (buf[0] << 16) | (buf[1] << 8) | buf[2];
            buf += 3;
        }
    }

    if (ctx->setpal) {
        ctx->setpal = 0;
        ctx->pic.palette_has_changed = 1;
    }

    /* make the palette available on the way out */
    memcpy(ctx->pic.data[1], ctx->pal, 1024);

    blocksize = *buf++;

    if (blocksize != 8 && blocksize != 127) {
        av_log(avctx, AV_LOG_ERROR, "Block size = %i\n", blocksize);
        return -1;
    }
    memset(ctx->cur, 0, 320 * 200);
    switch (header & KMVC_METHOD) {
    case 0:
    case 1: // used in palette changed event
        memcpy(ctx->cur, ctx->prev, 320 * 200);
        break;
    case 3:
        kmvc_decode_intra_8x8(ctx, buf, avctx->width, avctx->height);
        break;
    case 4:
        kmvc_decode_inter_8x8(ctx, buf, avctx->width, avctx->height);
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Unknown compression method %i\n", header & KMVC_METHOD);
        return -1;
    }

    out = ctx->pic.data[0];
    src = ctx->cur;
    for (i = 0; i < avctx->height; i++) {
        memcpy(out, src, avctx->width);
        src += 320;
        out += ctx->pic.linesize[0];
    }

    /* flip buffers */
    if (ctx->cur == ctx->frm0) {
        ctx->cur = ctx->frm1;
        ctx->prev = ctx->frm0;
    } else {
        ctx->cur = ctx->frm0;
        ctx->prev = ctx->frm1;
    }

    *data_size = sizeof(AVFrame);
    *(AVFrame *) data = ctx->pic;

    /* always report that the buffer was completely consumed */
    return buf_size;
}
static int decode_frame(AVCodecContext *avctx, void *data, int *data_size, AVPacket *avpkt) /* <=== */ 
{
    const uint8_t *buf = avpkt->data;
    const uint8_t *buf_end = buf + avpkt->size;
    KgvContext * const c = avctx->priv_data;
    
    uint16_t *out, *prev;
    int outcnt = 0, maxcnt;
    int w, h, i;

    if (avpkt->size < 2)
        return -1;

    w = (buf[0] + 1) * 8;
    h = (buf[1] + 1) * 8;
    buf += 2;

    if (avcodec_check_dimensions(avctx, w, h))
        return -1;

    if (w != avctx->width || h != avctx->height)
        avcodec_set_dimensions(avctx, w, h);

    maxcnt = w * h;

    out = av_realloc(c->cur, w * h * 2);
    if (!out)
        return -1;
    c->cur = out;

    prev = av_realloc(c->prev, w * h * 2);
    if (!prev)
        return -1;
    c->prev = prev;

    for (i = 0; i < 7; i++)
        offsets[i] = -1;

    while (outcnt < maxcnt && buf_end - 2 > buf) {
        int code = AV_RL16(buf);
        buf += 2;

        if (!(code & 0x8000)) {
            out[outcnt++] = code; // rgb555 pixel coded directly
        } else {
            int count;
            uint16_t *inp;

            if ((code & 0x6000) == 0x6000) {
                // copy from previous frame
                int oidx = (code >> 10) & 7;
                int start;

                count = (code & 0x3FF) + 3;

                if (offsets[oidx] < 0) {
                    if (buf_end - 3 < buf)
                        break;
                    offsets[oidx] = AV_RL24(buf);
                    buf += 3;
                }

                start = (outcnt + offsets[oidx]) % maxcnt;

                if (maxcnt - start < count)
                    break;

                inp = prev + start;
            } else {
                // copy from earlier in this frame
                int offset = (code & 0x1FFF) + 1;

                if (!(code & 0x6000)) {
                    count = 2;
                } else if ((code & 0x6000) == 0x2000) {
                    count = 3;
                } else {
                    if (buf_end - 1 < buf)
                        break;
                    count = 4 + *buf++;
                }

                if (outcnt < offset)
                    break;

                inp = out + outcnt - offset;
            }

            if (maxcnt - outcnt < count)
                break;

            for (i = 0; i < count; i++)
                out[outcnt++] = inp[i];
        }
    }

    if (outcnt - maxcnt)
        av_log(avctx, AV_LOG_DEBUG, "frame finished with %d diff\n", outcnt - maxcnt);

    c->pic.data[0]     = (uint8_t *)c->cur;
    c->pic.linesize[0] = w * 2;

    *data_size = sizeof(AVFrame);
    *(AVFrame*)data = c->pic;

    FFSWAP(uint16_t *, c->cur, c->prev);

    return avpkt->size;
}
static int decode_frame(AVCodecContext *avctx, void *data, /* <=== */ 
                        int *got_frame, AVPacket *avpkt)
{
    EXRContext *s = avctx->priv_data;
    ThreadFrame frame = { .f = data };
    AVFrame *picture = data;
    uint8_t *ptr;

    int y, ret;
    int out_line_size;
    int nb_blocks;/* nb scanline or nb tile */

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    if ((ret = decode_header(s)) < 0)
        return ret;

    switch (s->pixel_type) {
    case EXR_FLOAT:
    case EXR_HALF:
        if (s->channel_offsets[3] >= 0) {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_RGBA64;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_YA16;
            }
        } else {
            if (!s->is_luma) {
                avctx->pix_fmt = AV_PIX_FMT_RGB48;
            } else {
                avctx->pix_fmt = AV_PIX_FMT_GRAY16;
            }
        }
        break;
    case EXR_UINT:
        avpriv_request_sample(avctx, "32-bit unsigned int");
        return AVERROR_PATCHWELCOME;
    default:
        av_log(avctx, AV_LOG_ERROR, "Missing channel list.\n");
        return AVERROR_INVALIDDATA;
    }

    if (s->apply_trc_type != AVCOL_TRC_UNSPECIFIED)
        avctx->color_trc = s->apply_trc_type;

    switch (s->compression) {
    case EXR_RAW:
    case EXR_RLE:
    case EXR_ZIP1:
        s->scan_lines_per_block = 1;
        break;
    case EXR_PXR24:
    case EXR_ZIP16:
        s->scan_lines_per_block = 16;
        break;
    case EXR_PIZ:
    case EXR_B44:
    case EXR_B44A:
        s->scan_lines_per_block = 32;
        break;
    default:
        avpriv_report_missing_feature(avctx, "Compression %d", s->compression);
        return AVERROR_PATCHWELCOME;
    }

    /* Verify the xmin, xmax, ymin, ymax and xdelta before setting
     * the actual image size. */
    if (s->xmin > s->xmax                  ||
        s->ymin > s->ymax                  ||
        s->xdelta != s->xmax - s->xmin + 1 ||
        s->xmax >= s->w                    ||
        s->ymax >= s->h) {
        av_log(avctx, AV_LOG_ERROR, "Wrong or missing size information.\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_set_dimensions(avctx, s->w, s->h)) < 0)
        return ret;

    s->desc          = av_pix_fmt_desc_get(avctx->pix_fmt);
    if (!s->desc)
        return AVERROR_INVALIDDATA;
    out_line_size    = avctx->width * 2 * s->desc->nb_components;

    if (s->is_tile) {
        nb_blocks = ((s->xdelta + s->tile_attr.xSize - 1) / s->tile_attr.xSize) *
        ((s->ydelta + s->tile_attr.ySize - 1) / s->tile_attr.ySize);
    } else { /* scanline */
        nb_blocks = (s->ydelta + s->scan_lines_per_block - 1) /
        s->scan_lines_per_block;
    }

    if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0)
        return ret;

    if (bytestream2_get_bytes_left(&s->gb) < nb_blocks * 8)
        return AVERROR_INVALIDDATA;

    // save pointer we are going to use in decode_block
    s->buf      = avpkt->data;
    s->buf_size = avpkt->size;
    ptr         = picture->data[0];

    // Zero out the start if ymin is not 0
    for (y = 0; y < s->ymin; y++) {
        memset(ptr, 0, out_line_size);
        ptr += picture->linesize[0];
    }

    s->picture = picture;

    avctx->execute2(avctx, decode_block, s->thread_data, NULL, nb_blocks);

    // Zero out the end if ymax+1 is not h
    for (y = s->ymax + 1; y < avctx->height; y++) {
        memset(ptr, 0, out_line_size);
        ptr += picture->linesize[0];
    }

    picture->pict_type = AV_PICTURE_TYPE_I;
    *got_frame = 1;

    return avpkt->size;
}
static int decode_frame(AVCodecContext *avctx, /* <=== */ 
                        void *data, int *data_size, AVPacket *avpkt)
{
    TiffContext *const s = avctx->priv_data;
    AVFrame *picture = data;
    AVFrame *const p = &s->picture;
    unsigned off;
    int id, le, ret;
    int i, j, entries;
    int stride;
    unsigned soff, ssize;
    uint8_t *dst;
    GetByteContext stripsizes;
    GetByteContext stripdata;

    bytestream2_init(&s->gb, avpkt->data, avpkt->size);

    //parse image header
    if (avpkt->size < 8)
        return AVERROR_INVALIDDATA;
    id = bytestream2_get_le16u(&s->gb);
    if (id == 0x4949)
        le = 1;
    else if (id == 0x4D4D)
        le = 0;
    else {
        av_log(avctx, AV_LOG_ERROR, "TIFF header not found\n");
        return -1;
    }
    s->le = le;
    s->invert = 0;
    s->compr = TIFF_RAW;
    s->fill_order = 0;
    free_geotags(s);
    /* free existing metadata */
    av_dict_free(&s->picture.metadata);

    // As TIFF 6.0 specification puts it "An arbitrary but carefully chosen number
    // that further identifies the file as a TIFF file"
    if (tget_short(&s->gb, le) != 42) {
        av_log(avctx, AV_LOG_ERROR,
               "The answer to life, universe and everything is not correct!\n");
        return -1;
    }
    // Reset these offsets so we can tell if they were set this frame
    s->stripsizesoff = s->strippos = 0;
    /* parse image file directory */
    off = tget_long(&s->gb, le);
    if (off >= UINT_MAX - 14 || avpkt->size < off + 14) {
        av_log(avctx, AV_LOG_ERROR, "IFD offset is greater than image size\n");
        return AVERROR_INVALIDDATA;
    }
    bytestream2_seek(&s->gb, off, SEEK_SET);
    entries = tget_short(&s->gb, le);
    if (bytestream2_get_bytes_left(&s->gb) < entries * 12)
        return AVERROR_INVALIDDATA;
    for (i = 0; i < entries; i++) {
        if (tiff_decode_tag(s) < 0)
            return -1;
    }

    for (i = 0; i<s->geotag_count; i++) {
        const char *keyname = get_geokey_name(s->geotags[i].key);
        if (!keyname) {
            av_log(avctx, AV_LOG_WARNING, "Unknown or unsupported GeoTIFF key %d\n", s->geotags[i].key);
            continue;
        }
        if (get_geokey_type(s->geotags[i].key) != s->geotags[i].type) {
            av_log(avctx, AV_LOG_WARNING, "Type of GeoTIFF key %d is wrong\n", s->geotags[i].key);
            continue;
        }
        ret = av_dict_set(&s->picture.metadata, keyname, s->geotags[i].val, 0);
        if (ret<0) {
            av_log(avctx, AV_LOG_ERROR, "Writing metadata with key '%s' failed\n", keyname);
            return ret;
        }
    }

    if (!s->strippos && !s->stripoff) {
        av_log(avctx, AV_LOG_ERROR, "Image data is missing\n");
        return -1;
    }
    /* now we have the data and may start decoding */
    if ((ret = init_image(s)) < 0)
        return ret;

    if (s->strips == 1 && !s->stripsize) {
        av_log(avctx, AV_LOG_WARNING, "Image data size missing\n");
        s->stripsize = avpkt->size - s->stripoff;
    }
    stride = p->linesize[0];
    dst = p->data[0];

    if (s->stripsizesoff) {
        if (s->stripsizesoff >= avpkt->size)
            return AVERROR_INVALIDDATA;
        bytestream2_init(&stripsizes, avpkt->data + s->stripsizesoff, avpkt->size - s->stripsizesoff);
    }
    if (s->strippos) {
        if (s->strippos >= avpkt->size)
            return AVERROR_INVALIDDATA;
        bytestream2_init(&stripdata, avpkt->data + s->strippos, avpkt->size - s->strippos);
    }

    for (i = 0; i < s->height; i += s->rps) {
        if (s->stripsizesoff)
            ssize = tget(&stripsizes, s->sstype, s->le);
        else
            ssize = s->stripsize;

        if (s->strippos)
            soff = tget(&stripdata, s->sot, s->le);
        else
            soff = s->stripoff;

        if (soff > avpkt->size || ssize > avpkt->size - soff) {
            av_log(avctx, AV_LOG_ERROR, "Invalid strip size/offset\n");
            return -1;
        }
        if (tiff_unpack_strip(s, dst, stride, avpkt->data + soff, ssize,
                              FFMIN(s->rps, s->height - i)) < 0)
            break;
        dst += s->rps * stride;
    }
    if (s->predictor == 2) {
        dst = p->data[0];
        soff = s->bpp >> 3;
        ssize = s->width * soff;
        if (s->avctx->pix_fmt == PIX_FMT_RGB48LE ||
            s->avctx->pix_fmt == PIX_FMT_RGBA64LE) {
            for (i = 0; i < s->height; i++) {
                for (j = soff; j < ssize; j += 2)
                    AV_WL16(dst + j, AV_RL16(dst + j) + AV_RL16(dst + j - soff));
                dst += stride;
            }
        } else if (s->avctx->pix_fmt == PIX_FMT_RGB48BE ||
                   s->avctx->pix_fmt == PIX_FMT_RGBA64BE) {
            for (i = 0; i < s->height; i++) {
                for (j = soff; j < ssize; j += 2)
                    AV_WB16(dst + j, AV_RB16(dst + j) + AV_RB16(dst + j - soff));
                dst += stride;
            }
        } else {
            for (i = 0; i < s->height; i++) {
                for (j = soff; j < ssize; j++)
                    dst[j] += dst[j - soff];
                dst += stride;
            }
        }
    }

    if (s->invert) {
        dst = s->picture.data[0];
        for (i = 0; i < s->height; i++) {
            for (j = 0; j < s->picture.linesize[0]; j++)
                dst[j] = (s->avctx->pix_fmt == PIX_FMT_PAL8 ? (1<<s->bpp) - 1 : 255) - dst[j];
            dst += s->picture.linesize[0];
        }
    }
    *picture   = s->picture;
    *data_size = sizeof(AVPicture);

    return avpkt->size;
}
static int dirac_decode_data_unit(AVCodecContext *avctx, const uint8_t *buf, int size) /* <=== */ 
{
    DiracContext *s = avctx->priv_data;
    DiracFrame *pic = NULL;
    int i, parse_code = buf[4];

    if (size < DATA_UNIT_HEADER_SIZE)
        return -1;

    init_get_bits(&s->gb, &buf[13], 8*(size - DATA_UNIT_HEADER_SIZE));

    if (parse_code == pc_seq_header) {
        if (s->seen_sequence_header)
            return 0;

        /* [DIRAC_STD] 10. Sequence header */
        if (avpriv_dirac_parse_sequence_header(avctx, &s->gb, &s->source))
            return -1;

        avcodec_get_chroma_sub_sample(avctx->pix_fmt, &s->chroma_x_shift, &s->chroma_y_shift);

        if (alloc_sequence_buffers(s))
            return -1;

        s->seen_sequence_header = 1;
    } else if (parse_code == pc_eos) { /* [DIRAC_STD] End of Sequence */
        free_sequence_buffers(s);
        s->seen_sequence_header = 0;
    } else if (parse_code == pc_aux_data) {
        if (buf[13] == 1) {     /* encoder implementation/version */
            int ver[3];
            /* versions older than 1.0.8 don't store quant delta for
               subbands with only one codeblock */
            if (sscanf(buf+14, "Schroedinger %d.%d.%d", ver, ver+1, ver+2) == 3)
                if (ver[0] == 1 && ver[1] == 0 && ver[2] <= 7)
                    s->old_delta_quant = 1;
        }
    } else if (parse_code & 0x8) {  /* picture data unit */
        if (!s->seen_sequence_header) {
            av_log(avctx, AV_LOG_DEBUG, "Dropping frame without sequence header\n");
            return -1;
        }

        /* find an unused frame */
        for (i = 0; i < MAX_FRAMES; i++)
            if (s->all_frames[i].avframe.data[0] == NULL)
                pic = &s->all_frames[i];
        if (!pic) {
            av_log(avctx, AV_LOG_ERROR, "framelist full\n");
            return -1;
        }

        avcodec_get_frame_defaults(&pic->avframe);

        /* [DIRAC_STD] Defined in 9.6.1 ... */
        
        s->is_arith    = (parse_code & 0x48) == 0x08;          /* [DIRAC_STD] using_ac()      */
        s->low_delay   = (parse_code & 0x88) == 0x88;          /* [DIRAC_STD] is_low_delay()  */
        pic->avframe.reference = (parse_code & 0x0C) == 0x0C;  /* [DIRAC_STD]  is_reference() */
        pic->avframe.key_frame = s->num_refs == 0;             /* [DIRAC_STD] is_intra()      */
        pic->avframe.pict_type = s->num_refs + 1;              /* Definition of AVPictureType in avutil.h */

        if (avctx->get_buffer(avctx, &pic->avframe) < 0) {
            av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
            return -1;
        }
        s->current_picture = pic;
        s->plane[0].stride = pic->avframe.linesize[0];
        s->plane[1].stride = pic->avframe.linesize[1];
        s->plane[2].stride = pic->avframe.linesize[2];

        /* [DIRAC_STD] 11.1 Picture parse. picture_parse() */
        if (dirac_decode_picture_header(s))
            return -1;

        /* [DIRAC_STD] 13.0 Transform data syntax. transform_data() */
        if (dirac_decode_frame_internal(s))
            return -1;
    }
    return 0;
}
static int dirac_decode_data_unit(AVCodecContext *avctx, const uint8_t *buf, int size) /* <=== */ 
{
    DiracContext *s = avctx->priv_data;
    DiracFrame *pic = NULL;
    int i, parse_code = buf[4];

    if (size < DATA_UNIT_HEADER_SIZE)
        return -1;

    init_get_bits(&s->gb, &buf[13], 8*(size - DATA_UNIT_HEADER_SIZE));

    if (parse_code == pc_seq_header) {
        if (s->seen_sequence_header)
            return 0;

        //[DIRAC_STD] 10. Sequence header
        if (avpriv_dirac_parse_sequence_header(avctx, &s->gb, &s->source))
            return -1;

        avcodec_get_chroma_sub_sample(avctx->pix_fmt, &s->chroma_x_shift, &s->chroma_y_shift);

        if (alloc_sequence_buffers(s))
            return -1;

        s->seen_sequence_header = 1;
    } else if (parse_code == pc_eos) { //[DIRAC_STD] End of Sequence
        free_sequence_buffers(s);
        s->seen_sequence_header = 0;
    } else if (parse_code == pc_aux_data) {
        if (buf[13] == 1) {     // encoder implementation/version
            int ver[3];
            // versions older than 1.0.8 don't store quant delta for
            // subbands with only one codeblock
            if (sscanf(buf+14, "Schroedinger %d.%d.%d", ver, ver+1, ver+2) == 3)
                if (ver[0] == 1 && ver[1] == 0 && ver[2] <= 7)
                    s->old_delta_quant = 1;
        }
    } else if (parse_code & 0x8) {  // picture data unit
        if (!s->seen_sequence_header) {
            av_log(avctx, AV_LOG_DEBUG, "Dropping frame without sequence header\n");
            return -1;
        }

        // find an unused frame
        for (i = 0; i < MAX_FRAMES; i++)
            if (s->all_frames[i].avframe.data[0] == NULL)
                pic = &s->all_frames[i];
        if (!pic) {
            av_log(avctx, AV_LOG_ERROR, "framelist full\n");
            return -1;
        }

        avcodec_get_frame_defaults(&pic->avframe);

        //[DIRAC_STD] Defined in 9.6.1 ...
        s->num_refs    =  parse_code & 0x03; //[DIRAC_STD] num_refs()
        s->is_arith    = (parse_code & 0x48) == 0x08; //[DIRAC_STD] using_ac()
        s->low_delay   = (parse_code & 0x88) == 0x88; //[DIRAC_STD] is_low_delay()
        pic->avframe.reference = (parse_code & 0x0C) == 0x0C; //[DIRAC_STD]  is_reference()
        pic->avframe.key_frame = s->num_refs == 0; //[DIRAC_STD] is_intra()
        pic->avframe.pict_type = s->num_refs + 1; //Definition of AVPictureType in avutil.h

        if (avctx->get_buffer(avctx, &pic->avframe) < 0) {
            av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
            return -1;
        }
        s->current_picture = pic;
        s->plane[0].stride = pic->avframe.linesize[0];
        s->plane[1].stride = pic->avframe.linesize[1];
        s->plane[2].stride = pic->avframe.linesize[2];

        //[DIRAC_STD] 11.1 Picture parse. picture_parse()
        if (dirac_decode_picture_header(s))
            return -1;

        //[DIRAC_STD] 13.0 Transform data syntax. transform_data()
        if (dirac_decode_frame_internal(s))
            return -1;
    }
    return 0;
}
static uint8_t *advance_line(uint8_t *start, uint8_t *line, /* <=== */ 
                             int stride, int *y, int h, int interleave)
{
    *y += interleave;

    if (*y < h) {
        return line + interleave * stride;
    } else {
        *y = (*y + 1) & (interleave - 1);
        
            return start + *y * stride;
        } else {
            return NULL;
        }
    }
}
static void RENAME(vertical_compose53iL0)(uint8_t *_b0, uint8_t *_b1, uint8_t *_b2, /* <=== */ 
                                          int width)
{
    int i;
    TYPE *b0 = (TYPE *)_b0;
    TYPE *b1 = (TYPE *)_b1;
    TYPE *b2 = (TYPE *)_b2;
    for (i = 0; i < width; i++)
        b1[i] -= (b0[i] + b2[i] + 2) >> 2;
}
static void RENAME(vertical_compose53iL0)(uint8_t *_b0, uint8_t *_b1, uint8_t *_b2, /* <=== */ 
                                          int width)
{
    int i;
    TYPE *b0 = (TYPE *)_b0;
    TYPE *b1 = (TYPE *)_b1;
    TYPE *b2 = (TYPE *)_b2;
    for (i = 0; i < width; i++)
        b1[i] -= (b0[i] + b2[i] + 2) >> 2;
}
static void RENAME(vertical_compose53iL0)(uint8_t *_b0, uint8_t *_b1, uint8_t *_b2, /* <=== */ 
                                          int width)
{
    int i;
    TYPE *b0 = (TYPE *)_b0;
    TYPE *b1 = (TYPE *)_b1;
    TYPE *b2 = (TYPE *)_b2;
    for (i = 0; i < width; i++)
        
}
static void decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            cb+= get_symbol(&s->c, &s->block_state[64], 1);
            
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        decode_q_branch(s, level+1, 2*x+0, 2*y+0);
        decode_q_branch(s, level+1, 2*x+1, 2*y+0);
        decode_q_branch(s, level+1, 2*x+0, 2*y+1);
        decode_q_branch(s, level+1, 2*x+1, 2*y+1);
    }
}
static int decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;
    int res;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return 0;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            if (s->nb_planes > 2) {
                cb+= get_symbol(&s->c, &s->block_state[64], 1);
                
            }
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            if (ref >= s->ref_frames) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid ref\n");
                return AVERROR_INVALIDDATA;
            }
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        if ((res = decode_q_branch(s, level+1, 2*x+0, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+0, 2*y+1)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+1)) < 0)
            return res;
    }
    return 0;
}
static int decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;
    int res;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return 0;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            cb+= get_symbol(&s->c, &s->block_state[64], 1);
            
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            if (ref >= s->ref_frames) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid ref\n");
                return AVERROR_INVALIDDATA;
            }
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        if ((res = decode_q_branch(s, level+1, 2*x+0, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+0, 2*y+1)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+1)) < 0)
            return res;
    }
    return 0;
}
static void decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            cb+= get_symbol(&s->c, &s->block_state[64], 1);
            
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        decode_q_branch(s, level+1, 2*x+0, 2*y+0);
        decode_q_branch(s, level+1, 2*x+1, 2*y+0);
        decode_q_branch(s, level+1, 2*x+0, 2*y+1);
        decode_q_branch(s, level+1, 2*x+1, 2*y+1);
    }
}
static void decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            
            cb+= get_symbol(&s->c, &s->block_state[64], 1);
            cr+= get_symbol(&s->c, &s->block_state[96], 1);
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        decode_q_branch(s, level+1, 2*x+0, 2*y+0);
        decode_q_branch(s, level+1, 2*x+1, 2*y+0);
        decode_q_branch(s, level+1, 2*x+0, 2*y+1);
        decode_q_branch(s, level+1, 2*x+1, 2*y+1);
    }
}
static void decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            
            cr+= get_symbol(&s->c, &s->block_state[96], 1);
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        decode_q_branch(s, level+1, 2*x+0, 2*y+0);
        decode_q_branch(s, level+1, 2*x+1, 2*y+0);
        decode_q_branch(s, level+1, 2*x+0, 2*y+1);
        decode_q_branch(s, level+1, 2*x+1, 2*y+1);
    }
}
static int decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;
    int res;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return 0;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            if (s->nb_planes > 2) {
                
                cr+= get_symbol(&s->c, &s->block_state[96], 1);
            }
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            if (ref >= s->ref_frames) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid ref\n");
                return AVERROR_INVALIDDATA;
            }
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        if ((res = decode_q_branch(s, level+1, 2*x+0, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+0, 2*y+1)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+1)) < 0)
            return res;
    }
    return 0;
}
static int decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;
    int res;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return 0;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            
            cr+= get_symbol(&s->c, &s->block_state[96], 1);
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            if (ref >= s->ref_frames) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid ref\n");
                return AVERROR_INVALIDDATA;
            }
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        if ((res = decode_q_branch(s, level+1, 2*x+0, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+0, 2*y+1)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+1)) < 0)
            return res;
    }
    return 0;
}
static void decode_q_branch(SnowContext *s, int level, int x, int y){ /* <=== */ 
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        int ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;

        if(type){
            pred_mv(s, &mx, &my, 0, left, top, tr);
            l += get_symbol(&s->c, &s->block_state[32], 1);
            
            cr+= get_symbol(&s->c, &s->block_state[96], 1);
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        decode_q_branch(s, level+1, 2*x+0, 2*y+0);
        decode_q_branch(s, level+1, 2*x+1, 2*y+0);
        decode_q_branch(s, level+1, 2*x+0, 2*y+1);
        decode_q_branch(s, level+1, 2*x+1, 2*y+1);
    }
}
void ff_add_png_paeth_prediction(uint8_t *dst, uint8_t *src, uint8_t *top, /* <=== */ 
                                 int w, int bpp)
{
    int i;
    for (i = 0; i < w; i++) {
        int a, b, c, p, pa, pb, pc;

        a = dst[i - bpp];
        b = top[i];
        c = top[i - bpp];

        p  = b - c;
        pc = a - c;

        pa = abs(p);
        pb = abs(pc);
        pc = abs(p + pc);

        if (pa <= pb && pa <= pc)
            p = a;
        else if (pb <= pc)
            p = b;
        else
            p = c;
        dst[i] = p + src[i];
    }
}
void ff_add_png_paeth_prediction(uint8_t *dst, uint8_t *src, uint8_t *top, int w, int bpp) /* <=== */ 
{
    int i;
    for(i = 0; i < w; i++) {
        int a, b, c, p, pa, pb, pc;

        a = dst[i - bpp];
        b = top[i];
        c = top[i - bpp];

        p = b - c;
        pc = a - c;

        pa = abs(p);
        pb = abs(pc);
        pc = abs(p + pc);

        if (pa <= pb && pa <= pc)
            p = a;
        else if (pb <= pc)
            p = b;
        else
            p = c;
        dst[i] = p + src[i];
    }
}
