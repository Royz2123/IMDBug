for (i = 0; i < st->duration; i++)
for(i=0; i < frame_count;i++)
for(i=0; i < frame_count;i++)
for(i=0; i < frame_count;i++)
for (j = 0; j < len; j++)
(unsigned) iy >= height - h;
int need_emu  =  (unsigned) ix >= width  - w ||
s->plane[i].dwt_height))
s->buffer = av_malloc(2*p_width*p_height*sizeof(dwtcoef));
av_freep(&s->buffer);
if (item_num > 65536) {
er->er_temp_buffer     = av_malloc(s->mb_height * s->mb_stride);
if (mb_y + 1<mb_height && fixed[mb_xy + mb_stride]) {
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
int prev_x, prev_y, prev_ref;
if (fixed[mb_xy] == MV_FROZEN)
continue;
if (!(j & MV_FROZEN))
continue;
#define MV_FROZEN    4
if (mb_x > 0 && fixed[mb_xy - 1]) {
if (mb_x + 1 < mb_width && fixed[mb_xy + 1]) {
uint8_t *fixed = s->er_temp_buffer;
if (mb_y > 0 && fixed[mb_xy - mb_stride]) {
#define MV_CHANGED   2
#define MV_UNCHANGED 1
if ((a >= 0) + (a ^ (a >> 31)) - (a >> 31) != 1) {
nbits = 33 - ff_clz((a >= 0) + (a ^ (a >> 31)) - (a >> 31) - 1);
shift = 4 - ((dynrng << 23) >> 28);
return (avctx->err_recognition & AV_EF_EXPLODE) ? AVERROR_INVALIDDATA : 0;
ctx->avctx->height = FFMAX(top + h, ctx->height);
ctx->avctx->width  = FFMAX(left + w, ctx->width);
for (i = 0; i < 7; i++)
int offsets[7];
s->num_refs    =  parse_code & 0x03;                   /* [DIRAC_STD] num_refs()      */
if (*y) {
b1[i] -= (int)(b0[i] + (unsigned)b2[i] + 2) >> 2;
cr+= get_symbol(&s->c, &s->block_state[96], 1);
l += get_symbol(&s->c, &s->block_state[32], 1);
cb+= get_symbol(&s->c, &s->block_state[64], 1);
for(; i < size; i+=bpp) {\
else {\
for (; i < size; i += bpp) {\
int j;\
for (j = 0; j < bpp; j++)\
dst[i+j] = op(dst[i+j-bpp], src[i+j], last[i+j]);\
}\
}
if (k == CABAC_MAX_BIN)
coef[start] -= AAC_MUL26(coef[start - i * inc], lpc[i - 1]);
int prob, prob2, helper, val;
v += s->adsp.scalarproduct_int16(&s->residues[i], s->filter,
avctx->height = height > 0 ? height : -height;
*coeffs = *coeffs << -shift;
const int t0 =  27246 * blk[3 * step] + 18405 * blk[5 * step];
const int t1 =  27246 * blk[5 * step] - 18405 * blk[3 * step];
const int t2 =   6393 * blk[7 * step] + 32139 * blk[1 * step];
const int t3 =   6393 * blk[1 * step] - 32139 * blk[7 * step];
const unsigned t4 = 5793U * (t2 + t0 + 0x800 >> 12);
const unsigned t5 = 5793U * (t3 + t1 + 0x800 >> 12);
v = (av_clip_intp2(v >> 10, 13) << dshift) - *p1;
run_vlc[i].table = run_vlc_tables[i];
run_vlc[i].table_allocated = run_vlc_tables_size;
init_vlc(&run_vlc[i],
run_before= get_vlc2(gb, (run_vlc-1)[zeros_left].table, RUN_VLC_BITS, 1); \
run_before= get_vlc2(gb, (run_vlc-1)[zeros_left].table, RUN_VLC_BITS, 1); \
return;
dst[i] -= mul15(src[i], coeff);
return buf + (i << k);
CLOSE_READER(re, gb);
return buf + 1;
} else
if (gb->size_in_bits <= re_index)
return -1;
CLOSE_READER(re, gb);
for (i = 0; samplesref->data[i]; i++)
else if (avctx->codec_descriptor->props & AV_CODEC_PROP_TEXT_SUB)
sub->format = 1;
return AVERROR_INVALIDDATA;
if (avctx->codec_descriptor->props & AV_CODEC_PROP_BITMAP_SUB)
sub->format = 0;
case 0:  smp = 4;                              break;
case 1:  smp = 2;                              break;
dctx->remaining = avpriv_dnxhd_get_frame_size(cid);
if (dctx->remaining <= 0) {
dctx->remaining = ff_dnxhd_get_hr_frame_size(cid, dctx->w, dctx->h);
if (dctx->remaining <= 0)
return dctx->remaining;
if (value[strlen(value) - 1] == ',') {
print_str("color_primaries", av_color_primaries_name(frame->color_primaries));
else
print_str_opt("color_primaries", av_color_primaries_name(frame->color_primaries));
if (frame->color_primaries != AVCOL_PRI_UNSPECIFIED)
print_str("color_primaries", av_color_primaries_name(par->color_primaries));
else
print_str_opt("color_primaries", av_color_primaries_name(par->color_primaries));
if (par->color_primaries != AVCOL_PRI_UNSPECIFIED)
for(i=0;i<table_entries_used;i++)
int i, shift, round;
unsigned mul;
unsigned mask  = ((1 << bits_per_plane) - 1) << shift;
av_frame_set_metadata(p, metadata);
if (decode_text_chunk(s, length, 1, &metadata) < 0)
if (decode_text_chunk(s, length, 0, &metadata) < 0)
&band->blk_vlc, avctx))
band->blk_vlc.tab = ctx->blk_vlc.tab;
if (offset > s->nb_blocks)
s->frame.nb_samples = out / s->channels;
s->frame = av_frame_alloc();
if (!s->frame)
return AVERROR(ENOMEM);
b1[i] = refl[i] << 4;
if (avc == NULL) {
if (count >= INT_MAX / sizeof(int16_t))
if (count >= INT_MAX / sizeof(int64_t))
p[2 * i] -= (p[2 * i - 1] + p[2 * i + 1] + 2) >> 2;
p[1] >>= 1;
p[2 * i + 1] += (p[2 * i] + p[2 * i + 2]) >> 1;
t0  =  (s3 * 19266 + s5 * 12873) >> 15;
t1  =  (s5 * 19266 - s3 * 12873) >> 15;
t2  = ((s7 * 4520  + s1 * 22725) >> 15) - t0;
t3  = ((s1 * 4520  - s7 * 22725) >> 15) - t1;
tA  = (s2 * 8867 - s6 * 21407) >> 14;
tB  = (s6 * 8867 + s2 * 21407) >> 14;
coeffs[1] += *coeffs;
h->qp = (h->qp + get_se_golomb(gb)) & 63; //qp_delta
s->frame.nb_samples = s->samples;
for (i = 1; i <= lpc_order; i++)
int buf_size = alac->max_samples_per_frame * sizeof(int32_t);
int bit;
int S)
A = 2 * s->decorr[i].samplesA[0] - s->decorr[i].samplesA[1];
B = 2 * s->decorr[i].samplesB[0] - s->decorr[i].samplesB[1];
A = (3 * s->decorr[i].samplesA[0] - s->decorr[i].samplesA[1]) >> 1;
B = (3 * s->decorr[i].samplesB[0] - s->decorr[i].samplesB[1]) >> 1;
L += (R -= (L >> 1));
if((unsigned)htaps > HTAPS_MAX || htaps==0)
avctx->height = bytestream2_get_be32u(&gb);
avctx->width  = bytestream2_get_be32u(&gb);
const int qscale = (215 - 2*quant)*5;
goto done;
goto done;
done:
if ((ret = ff_reget_buffer(avctx, s->frame)) < 0)
return ret;
goto done;
if (av_image_check_size(cfg->pic_width, cfg->pic_height, 0, NULL) < 0 ||
int tb = av_clip_int8(poc - poc0);
s->codeblock_mode = svq3_get_ue_golomb(gb);
if (s->codeblock_mode > 1) {
av_log(s->avctx, AV_LOG_ERROR, "unknown codeblock mode\n");
return -1;
}
s->wavelet_idx = svq3_get_ue_golomb(gb);
if (s->wavelet_idx > 6)
return -1;
s->wavelet_depth = svq3_get_ue_golomb(gb);
if (s->wavelet_depth > MAX_DWT_LEVELS) {
av_log(s->avctx, AV_LOG_ERROR, "too many dwt decompositions\n");
return -1;
}
s->codeblock[i].width  = svq3_get_ue_golomb(gb);
s->codeblock[i].height = svq3_get_ue_golomb(gb);
if (total_size > in->size - idx_size) {
int total_size = 0;
if (s > 0) {
L2 = L + ((s->decorr[i].weightA * s->decorr[i].samplesA[0] + 512) >> 10);
R2 = R + ((s->decorr[i].weightB * L2 + 512) >> 10);
R2 = R + ((s->decorr[i].weightB * s->decorr[i].samplesB[0] + 512) >> 10);
L2 = L + ((int)(s->decorr[i].weightA * A + 512U) >> 10);
R2 = R + ((int)(s->decorr[i].weightB * B + 512U) >> 10);
L2 = L + ((s->decorr[i].weightA * R2 + 512) >> 10);
if (bits > MIN_CACHE_BITS)                                  \
if (len >= INT_MAX / 4 - 1 || len < 0 || skip > buf_size) {
skip = len * 4 + 4;
if ((clut == &default_clut && ctx->compute_clut == -1) || ctx->compute_clut == 1)
compute_default_clut(rect, rect->w, rect->h);
AV_WN32(rect->data[1] + 4*list_inv[i], RGBA(v/2,v,v/2,v));
S  *= 1 << s->float_shift;
result <<= quant_step_size;
s->spatial_decomposition_type+= get_symbol(&s->c, s->header_state, 1);
s->mv_scale       += get_symbol(&s->c, s->header_state, 1);
s->qbias          += get_symbol(&s->c, s->header_state, 1);
s->block_max_depth+= get_symbol(&s->c, s->header_state, 1);
s->qlog           += get_symbol(&s->c, s->header_state, 1);
*ptr= pred + (dc << point_transform);
memset(l->tokens[j], 0, sizeof(**l->tokens) * l->tok_lens[j]);
dest[group * 128 + k] += tmp << shift;
for (y = 0; y < cell->height; is_first_row = 0, y += 1 + v_zoom) {
for (x = 0; x < cell->width; x += 1 + h_zoom) {
return 0;
int ret;
ChannelParams *cp = &s->channel_params[ch];
cp->sign_huff_offset = calculate_sign_huff(m, substr, ch);
if (get_bits1(gbp))
return ret;
cp->sign_huff_offset = calculate_sign_huff(m, substr, ch);
avctx->height = line;
av_log(avctx, AV_LOG_VERBOSE,
"Not enough slice data available, "
"cropping the frame by %d pixels\n",
avctx->height - line);
if ((ret = allocate_buffers(s)) < 0)
return ret;
if ((ret = init_offset(s)) < 0)
return ret;
vec[i] = vec[i] << bits;
mx = (unsigned)(mx + 3 + 0x6000) / 6 + dx - 0x1000;
my = (unsigned)(my + 3 + 0x6000) / 6 + dy - 0x1000;
fx  = (unsigned)(mx + 0x3000) / 3 - 0x1000;
fy  = (unsigned)(my + 0x3000) / 3 - 0x1000;
mx  = (unsigned)(mx + 1 + 0x3000) / 3 + dx - 0x1000;
my  = (unsigned)(my + 1 + 0x3000) / 3 + dy - 0x1000;
if (s->channel_mode == AC3_CHMODE_DUALMONO)
if(s->block_max_depth > 1 || s->block_max_depth < 0){
c->tile_width * (uint64_t)c->tile_height >= INT_MAX / 4
i0 = *src0 + (((i_ict_params[0] * *src2) + (1 << 15)) >> 16);
i2 = *src0 + (((i_ict_params[3] * *src1) + (1 << 15)) >> 16);
S = T + ((s->decorr[i].weightA * A + 512) >> 10);
sar = av_mul_q(sar, (AVRational){new_h * old_w, new_w * old_h});
push_output_configuration(ac);
block[stride*0 + xStride*0]= ((a+c)*qmul) >> 7;
block[stride*0 + xStride*1]= ((e+b)*qmul) >> 7;
block[stride*1 + xStride*0]= ((a-c)*qmul) >> 7;
block[stride*1 + xStride*1]= ((e-b)*qmul) >> 7;
add -= (mid - base);
return (a * b + (1 << 14)) >> 15;
int td = av_clip_int8(poc1 - poc0);
buf += (i << k);
return av_append_packet(s->pb, pkt, fsize - ADTS_HEADER_SIZE);
s->sprite_offset[0][1] = (sprite_ref[0][1] << (alpha + rho)) +
s->sprite_offset[0][0] = (sprite_ref[0][0] << (alpha + rho)) +
dst[0] = (idx & 3) * (1 + (((int)sign >> 31) << 1));
dst[3] = (idx >> 6 & 3) * (1 + (((int)sign >> 31) << 1));
dst[1] = (idx >> 2 & 3) * (1 + (((int)sign >> 31) << 1));
dst[2] = (idx >> 4 & 3) * (1 + (((int)sign >> 31) << 1));
dst[1] = (idx >> 4 & 15) * (1 - ((sign & 1) << 1));
dst += s->rps * stride;
const int tA = 181 * (t9 + (t1 - t3)) + 0x80 >> 8;                  \
const int tB = 181 * (t9 - (t1 - t3)) + 0x80 >> 8;                  \
samples[i] = decoded[i] + 0x80;
if (res_bits >= RSIZE_BITS)
res_bits = res = 0;
return ret;
if ((ret = ff_reget_buffer(avctx, c->pic)) < 0)
} else {
}
c->pic->key_frame = frame_type & 0x20 ? 1 : 0;
c->pic->pict_type = frame_type & 0x20 ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;
return ret;
*got_frame = 1;
if ((ret = av_frame_ref(data, c->pic)) < 0)
coeff = vlcdec_lookup[num_bits][value];
if (!prec->cblk[cblkno].data)
if (s > 0) {
FFMIN(s->num_coeff_partitions, avctx->thread_count) > 1;
if(bits<=8){
if(bits<=8){
if (s->studio_profile)
else
ret = av_int2sf(u, 15 - nz);
uint64_t accu = 0, round;
int i, nz;
av_assert2(FFABS(x[i + 0][0]) >> 29 == 0);
accu += (int64_t)x[i + 0][0] * x[i + 0][0];
av_assert2(FFABS(x[i + 0][1]) >> 29 == 0);
accu += (int64_t)x[i + 0][1] * x[i + 0][1];
av_assert2(FFABS(x[i + 1][0]) >> 29 == 0);
accu += (int64_t)x[i + 1][0] * x[i + 1][0];
av_assert2(FFABS(x[i + 1][1]) >> 29 == 0);
accu += (int64_t)x[i + 1][1] * x[i + 1][1];
if (u == 0) {
nz = 1;
} else {
nz = -1;
nz++;
nz = 32 - nz;
}
c = (FFABS(c)*qf + qs) >> 2;                                                   \
int t;
return av_clipf((1.0 - FFMAX(0.0, tilt)) * (1.25 - 0.25 * wsp), 0.1, 1.0);
tilt = ctx->celpm_ctx.dot_productf(synth, synth + 1, AMRWB_SFR_SIZE - 1) /
ctx->celpm_ctx.dot_productf(synth, synth, AMRWB_SFR_SIZE);
if (ret < 0)
memcpy(diffFrame->data[0], s->last_frame->data[0],
s->last_frame->linesize[0] * s->last_frame->height);
memcpy(diffFrame->data[0], s->prev_frame->data[0],
s->prev_frame->linesize[0] * s->prev_frame->height);
memcpy(s->prev_frame->data[0], s->last_frame->data[0],
s->last_frame->linesize[0] * s->last_frame->height);
rt->protocols = ffurl_get_protocols(NULL, NULL);
sap->protocols = ffurl_get_protocols(NULL, NULL);
rt->protocols = ffurl_get_protocols(NULL, NULL);
rt->protocols = ffurl_get_protocols(NULL, NULL);
rt->protocols = ffurl_get_protocols(NULL, NULL);
c->protocols = ffurl_get_protocols(NULL, NULL);
sap->protocols = ffurl_get_protocols(NULL, NULL);
return prev ? NULL : &ffurl_context_class;
AVIOInternal *internal = s->opaque;
return prev ? NULL : internal->h;
protocols = ffurl_get_protocols(NULL, NULL);
return avio_open2(pb, url, flags, &s->interrupt_callback, options);
ff_lzw_encode_init(s->lzw, s->buf, 2 * width * height,
rt->protocols = ffurl_get_protocols(NULL, NULL);
sap->protocols = ffurl_get_protocols(NULL, NULL);
rt->protocols = ffurl_get_protocols(NULL, NULL);
rt->protocols = ffurl_get_protocols(NULL, NULL);
rt->protocols = ffurl_get_protocols(NULL, NULL);
c->protocols = ffurl_get_protocols(NULL, NULL);
sap->protocols = ffurl_get_protocols(NULL, NULL);
return prev ? NULL : &ffurl_context_class;
AVIOInternal *internal = s->opaque;
return prev ? NULL : internal->h;
protocols = ffurl_get_protocols(NULL, NULL);
return avio_open2(pb, url, flags, &s->interrupt_callback, options);
copy(srcPtr, srcStride[0], dstY, dstU, dstV, dstStride[0], c->srcW, c->input_rgb2yuv_table);
if (quant_idx > DIRAC_MAX_QUANT_INDEX) {
if (buf_size < 17) {
add = mid - base - 1;
return (a + b - 1) / b;
plane[k] = av_clip_int16(samples[k] * (1 << shift));
plane[k] = clip23(samples[k] * (1 << shift)) * (1 << 8);
if (startcode == VISUAL_OBJ_STARTCODE) {
uint32_t startcode;
startcode = get_bits_long(gb, 32);
}
/* StudioVisualObject() */
} else if (startcode == VISUAL_OBJ_STARTCODE) {
mpeg4_decode_visual_object(s, gb);
}
llabs(s->sprite_delta[i][1] * (w+16LL)) >= INT_MAX
s->decode_mb_row_no_filter(avctx, tdata, jobnr, threadnr);
const int b5 = (a3>>2) - a5;
const int b7 =  a7 - (a1>>2);
const int b1 = (a7>>2) + a1;
const int b3 =  a3 + (a5>>2);
int linesize = (avctx->width * avctx->bits_per_coded_sample + 7) / 8;
if (!last_pic_droppable && h0->cur_pic_ptr->tf.owner == h0->avctx) {
if (!last_pic_droppable && last_pic_structure != PICT_FRAME) {
if (!last_pic_droppable && last_pic_structure != PICT_FRAME) {
}
if (s->ti.bps != avctx->bits_per_raw_sample) {
avctx->bits_per_raw_sample = s->ti.bps;
if ((ret = set_bps_params(avctx)) < 0)
return ret;
r = cdt[p1] << 10;
if (avctx->codec_tag == MKTAG('R', 'G', 'B', '8'))
else if (avctx->codec_tag == MKTAG('R', 'G', 'B', 'N'))
while (strlen(language) >= 3) {
for (p = lang->value; next && *len_ptr < 255 / 4 * 4; p = next + 1) {
return AVERROR_INVALIDDATA;
return AVERROR_INVALIDDATA;
if (tns->present && !er_syntax)
if (decode_tns(ac, tns, gb, ics) < 0)
return AVERROR_INVALIDDATA;
&pulse, ics, sce->band_type) < 0)
return AVERROR_PATCHWELCOME;
if (decode_ics_info(ac, ics, gb) < 0)
return AVERROR_INVALIDDATA;
if (tns->present && er_syntax)
if (decode_tns(ac, tns, gb, ics) < 0)
return AVERROR_INVALIDDATA;
return ret;
if (decode_spectrum_and_dequant(ac, out, gb, sce->sf, pulse_present,
return ret;
return AVERROR_INVALIDDATA;
if (pl.len) {
for(i=0; i<=w-sizeof(long); i+=sizeof(long)){
for(i=0; i<=w-sizeof(long); i+=sizeof(long)){
int pixel_ptr = 0;
ADVANCE_BLOCK();
ADVANCE_BLOCK();
ADVANCE_BLOCK();
if((width * height)/2048*7 > bytestream2_get_bytes_left(&gb))
if (sscanf(in+tag_close+1, "%127[^>]>%n", buffer, &len) >= 1 && len > 0) {
if ((!tag_close && sptr < FF_ARRAY_ELEMS(stack)) ||
avctx->width  = width;
avctx->height = height > 0 ? height : -(unsigned)height;
level |= SHOW_SBITS(re, &s->gb, 6)<<5;
for (i = sb_start; i < sb_end && get_bits_left(gb) > 0; i++) {
return -(((int64_t)(-a)) >> b);
int t    = dst[out - pitch] + (table[c * 2] - 128);
R2 = R + ((int)(s->decorr[i].weightB * (unsigned)L2 + 512) >> 10);
line[x]=  (( i*qmul + qadd)>>(QEXPSHIFT));
line[x]= -((-i*qmul + qadd)>>(QEXPSHIFT)); //FIXME try different bias
if (val > 31)
const int scaled_x = cx * ASS_DEFAULT_PLAYRESX / 720;
const int scaled_y = cy * ASS_DEFAULT_PLAYRESY / 480;
const int scaled_x = x1 * ASS_DEFAULT_PLAYRESX / 720;
const int scaled_y = y1 * ASS_DEFAULT_PLAYRESY / 480;
ur->rem_rung_list = av_realloc(ur->rem_rung_list,
if (!ur->rem_rung_list) {
av_free(ur->rem_rung_list);
ctx->err = AVERROR(ENOMEM);
av_free(rung->rem_rung_list);
if (tsmb_size == 0) {
return AVERROR_INVALIDDATA;
}
for (i = 0; i <= w - sizeof(long); i += sizeof(long)) {
if (!s->cdx[i] || !s->cdy[i]) {
if (v < 0) {
"nonzerobits %d invalid\n", v);
c->tile_stride = FFALIGN(c->tile_width * 3, 16);
s->width =           get_bits(&s->gb,14);
s->height =          get_bits(&s->gb,14);
if (result) {
sum = RSHIFT(s->sprite_offset[0][n] << s->quarter_sample, a);
motion_y <<= (3 - s->sprite_warping_accuracy);
motion_x <<= (3 - s->sprite_warping_accuracy);
motion_x <<= (3 - s->sprite_warping_accuracy);
motion_y <<= (3 - s->sprite_warping_accuracy);
if (s->framep[VP56_FRAME_GOLDEN]->data[0] &&
ff_get_buffer(avctx, s->cur_decode_frame, 0);
ff_get_buffer(avctx, s->prev_decode_frame, 0);
av_frame_free(&s->last_frame);
av_frame_free(&s->second_last_frame);
av_frame_free(&s->cur_decode_frame);
av_frame_free(&s->prev_decode_frame);
return AVERROR(ENOMEM);
dst[x  ] = av_clip_uintp2(src[x  ] + (1 << (PX - 1)), PX);                                  \
dst[x+1] = av_clip_uintp2(src[x+1] + (1 << (PX - 1)), PX);                                  \
dst[x+2] = av_clip_uintp2(src[x+2] + (1 << (PX - 1)), PX);                                  \
dst[x+3] = av_clip_uintp2(src[x+3] + (1 << (PX - 1)), PX);                                  \
if (shift < 0) {
*((uint32_t*)(src[0] + x*4 + stride[0]*y)) = b + (g<<8) + (r<<16) + (a<<24);
if (left < 0)
left -= c->packed_stream_size[i][j];
if (left < 0)
left -= c->control_stream_size[i][j];
b += ff_subtitles_next_line(b);
s->planes = desc_in->nb_components;
bytestream2_get_bytes_left(&gb) < slice_end) {
l += 1 << av_log2(h >> 21);
cabac_init_decoder(s);
else
cabac_init_decoder(s);
cabac_init_decoder(s);
else
s->spx_band_sizes);
&s->num_cpl_bands, s->cpl_band_sizes);
int *num_bands, uint8_t *band_sizes)
uint8_t coded_band_struct[22];
const uint8_t *band_struct;
coded_band_struct[subbnd] = get_bits1(gbc);
band_struct = coded_band_struct;
} else if (!blk) {
band_struct = &default_band_struct[start_subband+1];
} else {
/* no change in band structure */
return;
mask & (pred + (dc * (1 << point_transform)));
dst[i] += src[i] * coeff + (1 << 2) >> 3;
AV_INPUT_BUFFER_PADDING_SIZE);
av_free(src2);
uint8_t *src2 = av_malloc((unsigned)size +
const int sign = FFSIGN(coeff);
return (x << 1) ^ (x >> 7);
dc = (dc * 10923 + 32768) >> 16;
dc = (dc * 10923 + 32768) >> 16;
pattern = A + (B << 4) + (C << 8);
t <<= 2;
dst[i] += (int)(src[i] * (SUINT)coeff + (1 << 2)) >> 3;
buf[j + k] -= clip23(norm16(err));
dst[n] += clip23((mul16(src[n], scale_inv) + round) >> shift);
if (mux_slot_length_bytes * 8 > get_bits_left(gb)) {
int scale = get_unary(gb, 1, 9);
int x = get_bits_long(gb, code.init);
if (c->video_size < aligned_width * avctx->height * c->bpp / 8)
if (ref == s->ref)
(1 << output_shift[mat_ch]);
bytestream_get_buffer(&buf, cdg_data, buf_size - CDG_HEADER_SIZE);
int mx      = m * ((A[0][0] * x + A[0][1]*y) + (1<<ez) * b[0]);
int my      = m * ((A[1][0] * x + A[1][1]*y) + (1<<ez) * b[1]);
if (!*ptrptr && !(nmemb && size))
if (dest_end - pd < i || bytestream2_get_bytes_left(&gb) < 2)
for (i = 0; i < l; i++) {
*pd++ = bytestream2_get_byteu(&gb);
*pd++ = bytestream2_get_byteu(&gb);
bytestream2_skip(&gb, 2);
int i, l;
int a1    = coeffs[1];
int a2    = a1 + *coeffs;
int a1 = *coeffs++;
int a4  = a3 + a1;
int a5  = a4 + a2;
int a3  = coeffs[2];
int a1    = coeffs[1];
int a2    = a1 + *coeffs;
int a3    = *coeffs + a1;
int a4    = a3 + a2;
br[1] = br[0] << 1;
br[0] <<= 1;
tmp -= error_buf[i] * filter_buf[i];
s->decorr[s->terms - i - 1].weightB = t << 3;
s->decorr[s->terms - i - 1].weightA = t << 3;
err = aacDecoder_DecodeFrame(s->handle, (INT_PCM *) s->decoder_buffer, s->decoder_buffer_size, 0);
ctx->deltas[stream_id][i] = v - (1 << mb);
for (i = 0; i < 4 && out->data[i]; i++) {
for (plane = 0; plane < 4 && frame->data[plane]; plane++) {
for (plane = 0; plane < 4 && frame->data[plane]; plane++) {
for (plane = 1; plane < 4 && frame->data[plane]; plane++)
for (plane = 0; plane < 4 && in->data[plane]; plane++) {
for (p = 0; p < 4 && in->data[p]; p++) {
for (plane = 0; in->data[plane] && plane < 4; plane++)
for (plane = 0; in->data[plane] && plane < 4; plane++)
for (plane = 0; plane < 4 && frame->data[plane]; plane++) {
for (plane = 0; plane < 4 && in->data[plane]; plane++) {
for (plane = 0; inpic->data[plane] && plane < 4; plane++) {
for (plane = 0; plane < 4 && in->data[plane]; plane++) {
for (plane = 0; plane < 4 && src->data[plane]; plane++)
for (plane = 0; plane < 4 && in->data[plane]; plane++) {
if (src_end - src < zsize)
s1 = (181 * (a1 - a5 + a7 - a3) + 128) >> 8; // 1, 3, 5, 7
s2 = (181 * (a1 - a5 - a7 + a3) + 128) >> 8;
if (avpkt->size < 3LL * avctx->height * avctx->width / 2) {
c->framebuf_stride = FFALIGN(c->width * 3, 16);
aligned_height     = FFALIGN(c->height,    16);
if(!new_buffer)
if(!new_buffer)
line = picture->data[plane] + y * picture->linesize[plane];
dst = linel + (x * pixelsize + compno*!planar);
dst = line + x * pixelsize + compno*!planar;
linel = (uint16_t *)picture->data[plane] + y * (picture->linesize[plane] >> 1);
Jpeg2000Prec *prec = band->prec + precno;
av_freep(&prec->zerobits);
av_freep(&prec->cblkincl);
av_freep(&prec->cblk);
else
c->nreslevels2decode = c->nreslevels - s->reduction_factor;
if (c->nreslevels < s->reduction_factor)
c->nreslevels2decode = 1;
MVF(PU(x0 + ((x) << hshift)), PU(y0 + ((y) << vshift)))
if (s->version != 0)
pps->beta_offset = get_se_golomb(gb) * 2;
pps->tc_offset = get_se_golomb(gb) * 2;
if (pps->beta_offset/2 < -6 || pps->beta_offset/2 > 6) {
pps->beta_offset/2);
if (pps->tc_offset/2 < -6 || pps->tc_offset/2 > 6) {
pps->tc_offset/2);
if (!(s->bpc == 10 || s->bpc == 12)) {
s->bpc = data;
buf[k] += buf[k - 1];
while (buf->len > 0 && buf->str[buf->len - 1] == ' ')
buf->str[--buf->len] = 0;
s->avctx->width  = ff_jpeg2000_ceildivpow2(s->width  - s->image_offset_x,
s->reduction_factor);
s->avctx->height = ff_jpeg2000_ceildivpow2(s->height - s->image_offset_y,
s->reduction_factor);
block[0] = get_sbits(gb, 9) << 6;
block[0] = get_sbits(gb, 9) << 6;
cur_qtzd_reconst = av_clip_int16((band->s_predictor + cur_diff) << 1);
(sg[1] << 7) + (band->pole_mem[1] * 127 >> 7), -12288, 12288);
ACCUM(0, cur_diff << 1, 0);
ACCUM(0, cur_diff << 1, 1);
f->chroma_planes  = get_rac(c, state);
f->chroma_h_shift = get_symbol(c, state, 0);
f->chroma_v_shift = get_symbol(c, state, 0);
f->transparency   = get_rac(c, state);
if (s->slice_height == 0 || s->mb_x != 0 ||
block[ff_zigzag_direct[pos]] = (ff_hq_ac_syms[val] * q[pos]) >> 12;
if((unsigned)fourxm->track_count >= UINT_MAX / sizeof(AudioTrack)){
ret= -1;
goto fail;
}
av_freep(&prec->cblk);
cblk->zero      = 0;
ff_mqc_initenc(&t1->mqc, cblk->data);
bytestream_put_buffer(&s->buf, cblk->data,   cblk->passes[cblk->ninclpasses-1].rate
|| sizeof(cblk->data) < cblk->length + cblk->lengthinc[cwsno] + 4
if (ret > sizeof(cblk->data)) {
sizeof(cblk->data));
return 0;
return 0;
uint16_t *y, *u, *v, aligned_width = FFALIGN(avctx->width, 4);
v += s->residues[i + j + 3] * s->filter[j + 3] +
s->residues[i + j + 2] * s->filter[j + 2] +
s->residues[i + j + 1] * s->filter[j + 1] +
s->residues[i + j    ] * s->filter[j    ];
int val;
if (val[0] > 32) {
((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
uint_fast8_t *classifs = vr->classifs;
avctx->flags &= ~CODEC_FLAG_EMU_EDGE;
MatroskaTrack *tracks = matroska->tracks.elem;
if (a.size == 1) { /* 64 bit extended size */
static int cinepak_decode (CinepakContext *s)
const uint8_t  *eod = (s->data + s->size);
if (buf_size <= 8) {
if (s->codec_id == AV_CODEC_ID_JV) {
strcpy(filename, sic->filename);
SET_DIAG_MV(/ 2, << 1, sl->left_mb_xy[i >= 36], ((i >> 2)) & 3);
if (state * 4 > 0xFF || i >= size)
if (state * 4 > 0xFF || i >= size)
int y0 = Y[m][0];
int y1 = Y[m][1];
f->slice_count < MAX_SLICES && 3 < p - c->bytestream_start;
(s->color_type == PNG_COLOR_TYPE_RGB && length != 6))
if (sps->mb_height >= INT_MAX / 2) {
decoded[j] += sum >> qlevel;
if (!var_size)
return AVERROR_PATCHWELCOME;
return AVERROR_PATCHWELCOME;
return AVERROR_PATCHWELCOME;
return AVERROR_INVALIDDATA;
return AVERROR_INVALIDDATA;
return AVERROR_INVALIDDATA;
if (!var_size)
if (!var_size)
if (!var_size)
if (!var_size)
return AVERROR_INVALIDDATA;
if (!var_size)
h->qp = (h->qp + get_se_golomb(&h->gb)) & 63;
c->pro         = 1;
} else if (avctx->extradata_size == 8) {
} else if (avctx->extradata_size >= 16) {
for (y = 0; y < avctx->height; y++) {
for(y = 0; y < avctx->height; y++ ) {
bp1[j] = ((bp2[j] - ((refl[i+1] * bp2[i-j]) >> 12)) * b) >> 12;
v[      i] = AAC_SRA_R((src0[i] - src1[63 - i]), 5);
v[127 - i] = AAC_SRA_R((src0[i] + src1[63 - i]), 5);
int16_t *quant_matrix = s->quant_matrixes[s->quant_sindex[0]];
int16_t *quant_matrix, int Al)
int dc_index, int ac_index, int16_t *quant_matrix)
int ac_index, int16_t *quant_matrix,
base = GET_MED(0) + GET_MED(1) + GET_MED(2) * (t - 2);
memset(cblk->lengthinc, 0, sizeof(cblk->lengthinc));
dest[group * 128 + k] += tmp * (1 << shift);
in += len - 1;
} else
av_bprint_chars(dst, *in, 1);
if ((an != 1 && (len = 0, sscanf(in, "{\\%*[^}]}%n", &len) >= 0 && len > 0)) ||
(len = 0, sscanf(in, "{%*1[CcFfoPSsYy]:%*[^}]}%n", &len) >= 0 && len > 0)) {
if (h->cur.f->pict_type != AV_PICTURE_TYPE_B) {
decode_mb_i(h, 0);
return 0;
bytestream2_skip(&gb, len + (len & 1));
if (len < 0 || bytestream2_get_bytes_left(&gb) < 18) {
if (count > UINT_MAX / sizeof(*c->meta_keys)) {
if (c->chunk_size == 0) // end of stream
re_signal = c->se + dq;
while (avio_tell(s->pb) < tag_end) {
while (avio_tell(s->pb) < end) {
dst[i + 0*stride] = cm[ dst[i + 0*stride] + ((b0 + b4) >> 7)];
dst[i + 1*stride] = cm[ dst[i + 1*stride] + ((b1 + b5) >> 7)];
dst[i + 2*stride] = cm[ dst[i + 2*stride] + ((b2 + b6) >> 7)];
dst[i + 3*stride] = cm[ dst[i + 3*stride] + ((b3 + b7) >> 7)];
dst[i + 4*stride] = cm[ dst[i + 4*stride] + ((b3 - b7) >> 7)];
dst[i + 5*stride] = cm[ dst[i + 5*stride] + ((b2 - b6) >> 7)];
dst[i + 6*stride] = cm[ dst[i + 6*stride] + ((b1 - b5) >> 7)];
dst[i + 7*stride] = cm[ dst[i + 7*stride] + ((b0 - b4) >> 7)];
const uint8_t *cm = ff_crop_tab + MAX_NEG_CROP;
av_assert0(fabs(av_q2d(st2->time_base) - ast2->scale / (double)ast2->rate) < av_q2d(st2->time_base) * 0.00000001);
/* check if the caller has overridden the codec id */
#if FF_API_LAVF_AVCTX
pps->log2_parallel_merge_level       = get_ue_golomb_long(gb) + 2;
if (pps->log2_parallel_merge_level > sps->log2_ctb_size) {
pps->log2_parallel_merge_level - 2);
if (FFABS(L) + FFABS(R) > (1<<19)) {
decoded[i] <<= s->sample_shift[chan];
if (freq >> (5 - group) > s->nsubbands * 4 - 5) {
b1[j] = ((refl[i] * b2[i-j-1]) >> 12) + b2[j];
priv->extra_headers_left  = 1 + extra_headers;
av_free(os->private);
} else if (s->bit_depth == 1) {
if (s->context_initialized &&
(   s->width != s->avctx->coded_width || s->height != s->avctx->coded_height
|| s->avctx->bits_per_raw_sample != h->sps.bit_depth_luma
|| h->cur_chroma_format_idc != h->sps.chroma_format_idc
av_log_missing_feature(s->avctx,
"Width/height/bit depth/chroma idc changing with threads is", 0);
return -1;   // width / height changed during parallelized decoding
}
decoded[i] *= 1 << s->sample_shift[chan];
samples[i] *= 1 << 8;
output[j] <<= 2;
if (uncompress(c->decomp_buf, &dlen, &buf[2], buf_size - 2) != Z_OK)
if (av_lzo1x_decode(c->decomp_buf, &outlen, &buf[2], &inlen))
for (i = 0; i < s->cdlms_ttl[c]; i++)
decode_cdlms(s);
av_dlog(s->avctx, "do_arith_coding == 1");
abort();
int i, j, rawpcm_tile, padding_zeroes;
cumulative_target = 1 << scale_factor;
buffer[i] <<= s->bitshift;
lpc32[k]         = -p[k + 1] - p[k] - q[k + 1] + q[k];
lpc32[order-k-1] = -p[k + 1] - p[k] + q[k + 1] - q[k];
state += (int64_t)d * yflag - (d * state >> 8);
uint32_t data_size, line, col = 0;
uint32_t tileX, tileY, tileLevelX, tileLevelY;
if (pal) {
av_buffer_unref(&context->palette);
if (!context->palette) {
av_buffer_unref(&frame->buf[0]);
return AVERROR(ENOMEM);
}
if (avpkt->size - vid_size) {
memcpy(context->palette->data, pal, avpkt->size - vid_size);
if (ret < 0)
return AVERROR(EINVAL);
init_get_bits8(&gb, nal->data + 1, (nal->size - 1));
AVIndexEntry *e = &st->index_entries[st->nb_index_entries++];
if (s->cdef[0] < 0) {
for (x = 0; x < s->ncomponents; x++)
s->cdef[x] = x + 1;
if ((s->ncomponents & 1) == 0)
s->cdef[s->ncomponents-1] = 0;
s0 = ((d << COEFF_BITS) * scale + c->coeff[0] * s1 + c->coeff[1] * s2) >> COEFF_BITS;
tmp = pps->init_qp + get_se_golomb(&sl->gb);
m->sample_buffer[i][maxchan+1] = ((int8_t)(seed >> 15)) << s->noise_shift;
m->sample_buffer[i][maxchan+2] = ((int8_t) seed_shr7)   << s->noise_shift;
fcoeff[i] = get_sbits(gbp, coeff_bits) << coeff_shift;
int32_t sample = sample_buffer[i][mat_ch]
<< output_shift[mat_ch];
im = RSCALE(-input[n2+2*i] - input[ n-1-2*i]);
re = RSCALE(-input[2*i+n3] - input[n3-1-2*i]);
im = RSCALE(-input[n4+2*i] + input[n4-1-2*i]);
re = RSCALE( input[2*i]    - input[n2-1-2*i]);
const int qmul = svq3_dequant_coeff[qp];
output[stride *  0 + offset] = (z0 + z3) * qmul + 0x80000 >> 20;
output[stride *  2 + offset] = (z1 + z2) * qmul + 0x80000 >> 20;
output[stride *  8 + offset] = (z1 - z2) * qmul + 0x80000 >> 20;
output[stride * 10 + offset] = (z0 - z3) * qmul + 0x80000 >> 20;
parse_mb_skip(w);
value <<= bits_per_plane;
mask  <<= bits_per_plane;
if (m->avctx->codec_id == AV_CODEC_ID_MLP && s->noise_type) {
int min_channel, max_channel, max_matrix_channel;
if (max_channel > MAX_MATRIX_CHANNEL_MLP && !s->noise_type) {
s->noise_type = get_bits1(gbp);
b[2*x  ] = (tmp[x] + 1)>>1;
b[2*x+1] = (COMPOSE_DD97iH0(tmp[x-1], tmp[x], b[x+w2], tmp[x+1], tmp[x+2]) + 1)>>1;
b[2*x  ] = (tmp[x] + 1)>>1;
b[2*x+1] = (COMPOSE_DD97iH0(tmp[x-1], tmp[x], b[x+w2], tmp[x+1], tmp[x+2]) + 1)>>1;
if (sps->temporal_layer[i].max_dec_pic_buffering > HEVC_MAX_DPB_SIZE) {
int32_t *p1 = &tfilter[0];
int32_t *p2 = &tfilter[i - 1];
x     = *p1 + (s->predictors[i] * *p2 + 256 >> 9);
*p2  += s->predictors[i] * *p1 + 256 >> 9;
m->style_entries = AV_RB16(tsmb);
if (m->tracksize + m->size_var + 2 + m->style_entries * 12 > avpkt->size)
sl->qscale += dquant;
(frame->data[1][3+i*4]<<24)
uint32_t pixel = colors[code & 3] | (alpha << 24);
return AVERROR_PATCHWELCOME;
return AVERROR_PATCHWELCOME;
if (llabs(s->sprite_offset[i][0] + s->sprite_delta[i][0] * (int64_t)w) >= INT_MAX ||
llabs(s->sprite_offset[i][0] + s->sprite_delta[i][1] * (int64_t)h) >= INT_MAX ||
llabs(s->sprite_offset[i][0] + s->sprite_delta[i][0] * (int64_t)w + s->sprite_delta[i][1] * (int64_t)h) >= INT_MAX) {
t1 = (s1) << 1; t5 = (s5) << 1;\
sp2 = src[ 8] << shift;
sp3 = src[16] << shift;
sp4 = src[24] << shift;
sp1 = src[ 0] << shift;
if (!avctx->width || !avctx->height)
const unsigned int a2 =  block[i+0*8] - block[i+4*8];
const unsigned int a4 = (block[i+2*8]>>1) - block[i+6*8];
const unsigned int a6 = (block[i+6*8]>>1) + block[i+2*8];
const unsigned int a0 =  block[i+0*8] + block[i+4*8];
gdv->pal[i] = 0xFF << 24 | r << 18 | g << 10 | b << 2;
int den = h->scale_den[FFMAX(src->ref, 0)];
if ((code & 0xF) > 4) {
return (p_ener - f_ener) / (p_ener + f_ener);
} else if (encoding == 1 && (c->bpp == 6 || c->bpp == 8)) {
if (shift < 31)
*coef += (pv.mant + (1 << (shift - 1))) >> shift;
parse_palette(avctx, &gbc, (uint32_t *)p->data[1], colors);
const int z0= temp[2*0+i] + temp[2*2+i];
const int z1= temp[2*0+i] - temp[2*2+i];
const int z2= temp[2*1+i] - temp[2*3+i];
const int z3= temp[2*1+i] + temp[2*3+i];
block[stride*0+offset]= ((z0 + z3)*qmul + 128) >> 8;
block[stride*1+offset]= ((z1 + z2)*qmul + 128) >> 8;
block[stride*2+offset]= ((z1 - z2)*qmul + 128) >> 8;
block[stride*3+offset]= ((z0 - z3)*qmul + 128) >> 8;
av_log(s->avctx, AV_LOG_ERROR,
"sprite_brightness_change not supported\n");
if (ctx->vol_sprite_usage == STATIC_SPRITE)
av_log(s->avctx, AV_LOG_ERROR, "static sprite not supported\n");
if (s->pict_type == AV_PICTURE_TYPE_S &&
(ctx->vol_sprite_usage == STATIC_SPRITE ||
ctx->vol_sprite_usage == GMC_SPRITE)) {
if (mpeg4_decode_sprite_trajectory(ctx, gb) < 0)
return AVERROR_INVALIDDATA;
if (ctx->sprite_brightness_change)
unsigned short shift = (b[ 2] >> 2);
p[2 * i]     += (I_LFTG_BETA  * (p[2 * i - 1] + p[2 * i + 1]) + (1 << 15)) >> 16;
p[2 * i]     -= (I_LFTG_DELTA * (p[2 * i - 1] + p[2 * i + 1]) + (1 << 15)) >> 16;
p[2 * i + 1] += (I_LFTG_ALPHA * (p[2 * i]     + p[2 * i + 2]) + (1 << 15)) >> 16;
p[2 * i + 1] -= (I_LFTG_GAMMA * (p[2 * i]     + p[2 * i + 2]) + (1 << 15)) >> 16;
ret = ff_set_dimensions(avctx, dsh->width, dsh->height);
val = FFMIN(val, 32767);
uint32_t diff = (*(ptr[0]++) << 24) |
int nd, st;
next_coef = (next_coef + scaling_list_delta_coef + 256) % 256;
*payload_len += bytestream2_get_byte(&gb);
*payload_len += bytestream2_get_byte(&gb);
*payload_len = 0;
int field_poc[2];
val = val * quant_matrix[0] + s->last_dc[component];
if (nlsf[i] < nlsf[i - 1] + min_delta[i])
nlsf[i] = nlsf[i - 1] + min_delta[i];
s->time    = (s->last_time_base + time_incr) * s->avctx->framerate.num + time_increment;
s->time = s->time_base * s->avctx->framerate.num + time_increment;
int *dest = target->ret;
((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
row[1] = (a1 + b1) >> (ROW_SHIFT + extra_shift);
row[6] = (a1 - b1) >> (ROW_SHIFT + extra_shift);
row[2] = (a2 + b2) >> (ROW_SHIFT + extra_shift);
row[5] = (a2 - b2) >> (ROW_SHIFT + extra_shift);
row[3] = (a3 + b3) >> (ROW_SHIFT + extra_shift);
row[4] = (a3 - b3) >> (ROW_SHIFT + extra_shift);
row[0] = (a0 + b0) >> (ROW_SHIFT + extra_shift);
row[7] = (a0 - b0) >> (ROW_SHIFT + extra_shift);
*lag_frac = (pitch_index - (*lag_int << 1) + 256 - 376) << 1;
samples[i] <<= 8;
if (!s->have_undamaged_frame) {
for (x = 0; x < avctx->width * 4; x++) {
*data_32++ = sample * 256;
sample[1][x] = av_mod_uintp2(RENAME(predict)(sample[1] + x, sample[0] + x) + diff, bits);
c->bytestream_end = c->bytestream + 2;
return ret;
return AVERROR_INVALIDDATA;
if (s->frames[VP56_FRAME_CURRENT]->key_frame)
ff_set_dimensions(s->avctx, 0, 0);
return ret;
s->matrix_coeff[mat][ch] = coeff_val << (14 - frac_bits);
memcpy((SHORTFLOAT *)frame->data[ch], s->output_buffer[map],
data[i] <<= I_PRESHIFT;
bits[*pos] = (~pfx) & ((1U << FFMAX(pl, 1)) - 1);
((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
if (x < avctx->width) {
break;
dst[i] += AAC_MADD28(src[i][0], src[i][0], src[i][1], src[i][1]);
if (av_image_check_size(s->width, s->height, 0, s->avctx)) {
t8  = (t6 * 11585) >> 14;
t9  = (t7 * 11585) >> 14;
const int t6 = ((blk[0 * step] + blk[4 * step]) << dshift) + bias;  \
const int t7 = ((blk[0 * step] - blk[4 * step]) << dshift) + bias;  \
if (val[0] > 31) {
"Invalid INT32INFO, extra_bits = %d (> 32)\n", val[0]);
if (s->avctx->active_thread_type&FF_THREAD_FRAME) {
av_log(avctx, AV_LOG_ERROR, "midstream reconfiguration with multithreading is unsupported, try -threads 1\n");
return AVERROR_PATCHWELCOME;
}
dst[x] = av_clip_pixel(( (src[x] << (14 - BIT_DEPTH)) * wx1 + src2[x] * wx0 + ((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
int mask  = ((1 << bits_per_plane) - 1) << shift;
mant <<= (23 - (mbits - 1));
b = ff_eac3_gaq_remap_2_4_b[hebap-8][log_gain-1] << 8;
s->pre_mantissa[ch][bin][blk] = ff_eac3_mantissa_vq[hebap][v][blk] << 8;
cblk->passes[passno-1].rate = ff_mqc_flush_to(&t1->mqc, cblk->passes[passno-1].flushed, &cblk->passes[passno-1].flushed_len);
const int z0= temp[4*0+i] + temp[4*2+i];
const int z1= temp[4*0+i] - temp[4*2+i];
const int z2= temp[4*1+i] - temp[4*3+i];
const int z3= temp[4*1+i] + temp[4*3+i];
output[stride* 0+offset]= ((((z0 + z3)*qmul + 128 ) >> 8));
output[stride* 1+offset]= ((((z1 + z2)*qmul + 128 ) >> 8));
output[stride* 4+offset]= ((((z1 - z2)*qmul + 128 ) >> 8));
output[stride* 5+offset]= ((((z0 - z3)*qmul + 128 ) >> 8));
*data_32++ = sample << 8;
pps->init_qp                              = get_se_golomb(gb) + 26 + qp_bd_offset;
pps->init_qs                              = get_se_golomb(gb) + 26 + qp_bd_offset;
f1[i + 1] = f1[i - 1] + MULL2(f1[i], lpc[2 * i]);
f2[i + 1] = f2[i - 1] + MULL2(f2[i], lpc[2 * i + 1]);
skip_bytes(&lc->cc, 0);
return ret;
cabac_reinit(s->HEVClc);
int ret = cabac_init_decoder(s);
if (ret < 0)
return ret;
cabac_reinit(s->HEVClc);
int ret = cabac_init_decoder(s);
if (ret < 0)
int16_t mul;
diff = -diff;
const int z0=  block[i + 4*0]     +  block[i + 4*2];
const int z1=  block[i + 4*0]     -  block[i + 4*2];
const int z2= (block[i + 4*1]>>1) -  block[i + 4*3];
const int z3=  block[i + 4*1]     + (block[i + 4*3]>>1);
const int z0=  block[0 + 4*i]     +  block[2 + 4*i];
const int z1=  block[0 + 4*i]     -  block[2 + 4*i];
const int z2= (block[1 + 4*i]>>1) -  block[3 + 4*i];
const int z3=  block[1 + 4*i]     + (block[3 + 4*i]>>1);
dst[i + 0*stride]= av_clip_pixel(dst[i + 0*stride] + ((z0 + z3) >> 6));
dst[i + 1*stride]= av_clip_pixel(dst[i + 1*stride] + ((z1 + z2) >> 6));
dst[i + 2*stride]= av_clip_pixel(dst[i + 2*stride] + ((z1 - z2) >> 6));
dst[i + 3*stride]= av_clip_pixel(dst[i + 3*stride] + ((z0 - z3) >> 6));
*rgba++ = (*alpha++ << 24) | (r << 16) | (g << 8) | b;
if (sps->bit_depth_luma > 14U || sps->bit_depth_chroma > 14U) {
}
else {
matroska->prev_pkt = NULL;
if (c->end >= c->buffer && c->bits >= 0) {
if (c->end >= c->buffer && c->bits >= 0) {
(pic->linesize[0] < 0 && output + p2 * (depth >> 3) < output_end)) {
(pic->linesize[0] < 0 && output + p1 * (depth >> 3) < output_end))
output_end = pic->data[0] +  avctx->height      * pic->linesize[0];
if ((pic->linesize[0] > 0 && output + p1 * (depth >> 3) > output_end) ||
if ((pic->linesize[0] > 0 && output + p2 * (depth >> 3) > output_end) ||
dst[n] += (src[n] + round) >> shift;
A =  2 * s->decorr[i].samplesA[0] - s->decorr[i].samplesA[1];
A = (3 * s->decorr[i].samplesA[0] - s->decorr[i].samplesA[1]) >> 1;
const int a0 =  block[i+0*8] + block[i+4*8];
const int a2 =  block[i+0*8] - block[i+4*8];
const int a4 = (block[i+2*8]>>1) - block[i+6*8];
const int a6 = (block[i+6*8]>>1) + block[i+2*8];
const int b0 = a0 + a6;
const int b2 = a2 + a4;
const int b4 = a2 - a4;
const int b6 = a0 - a6;
const int a1 = -block[i+3*8] + block[i+5*8] - block[i+7*8] - (block[i+7*8]>>1);
const int a3 =  block[i+1*8] + block[i+7*8] - block[i+3*8] - (block[i+3*8]>>1);
const int a5 = -block[i+1*8] + block[i+7*8] + block[i+5*8] + (block[i+5*8]>>1);
const int a7 =  block[i+3*8] + block[i+5*8] + block[i+1*8] + (block[i+1*8]>>1);
tmp = (tmp + 4096) >> 13;
return AVERROR_INVALIDDATA;
return AVERROR_PATCHWELCOME;
if (!ics->num_swb || !ics->swb_offset)
return AVERROR_BUG;
i1 = *src0 - (((i_ict_params[1] * *src1) + (1 << 15)) >> 16)
i2 = *src0 + (2 * *src1) + (((-14942 * *src1) + (1 << 15)) >> 16);
mant <<= 6;
i <<= 1;
che->ch[0].ret[j] = (int32_t)av_clip64((int64_t)che->ch[0].ret[j]<<7, INT32_MIN, INT32_MAX-0x8000)+0x8000;
che->ch[1].ret[j] = (int32_t)av_clip64((int64_t)che->ch[1].ret[j]<<7, INT32_MIN, INT32_MAX-0x8000)+0x8000;
if (ret < 0)
const int rr = (dc + 0x80000);
S = -S;
if (S >= 0x1000000) {
v = (av_clip_intp2(v >> filter_quant, 13) * (1 << dshift)) - *decoded;
if ((err = ff_h264_queue_decode_slice(h, nal)))
output[j] <<= 2;
tfilter[0] = s->predictors[0] << 6;
tfilter[i] = s->predictors[i] << 6;
v = (av_clip_intp2(v >> filter_quant, 13) << dshift) - *decoded;
s->predictors[2] = get_sbits(gb, size) << (10 - size);
s->predictors[3] = get_sbits(gb, size) << (10 - size);
s->predictors[i] = get_sbits(gb, x) << (10 - size);
*samples++ = av_clip_int16(ractx->curr_sblock[j + 10] << 2);
ROUNDED_DIV(((h - h2) * (r * sprite_ref[0][1] - 16 * vop_ref[0][1]) +
h2 * (r * sprite_ref[2][1] - 16 * vop_ref[2][1])), h);
(r * sprite_ref[0][0] - 16 * vop_ref[0][0]) +
w2 * (r * sprite_ref[1][0] - 16 * vop_ref[1][0])), w);
(r * sprite_ref[0][1] - 16 * vop_ref[0][1]) +
w2 * (r * sprite_ref[1][1] - 16 * vop_ref[1][1])), w);
ROUNDED_DIV(((h - h2) * (r * sprite_ref[0][0] - 16 * vop_ref[0][0]) +
h2 * (r * sprite_ref[2][0] - 16 * vop_ref[2][0])), h);
scale = AAC_RENAME(cce_scale)[get_bits(gb, 2)];
l[k] + start + 1, r[k] + start + 1,
((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
const SUINT z0=  block[i + 4*0]     +  block[i + 4*2];
const SUINT z1=  block[i + 4*0]     -  block[i + 4*2];
const SUINT z2= (block[i + 4*1]>>1) -  block[i + 4*3];
const SUINT z3=  block[i + 4*1]     + (block[i + 4*3]>>1);
if (decoded_size > height * stride - left - top * stride) {
decoded_size = height * stride - left - top * stride;
decoded_size = height * stride - left - top * stride;
if (decoded_size > height * stride - left - top * stride) {
if (ctx->hybrid && !channel)
update_error_limit(ctx);
int l = snprintf(ap, 5 + strlen(sep), "%d%s", sp[i], sep);
ap = av_malloc((5 + strlen(sep)) * count);
ap = av_malloc(component_len * count);
int component_len;
component_len = 15 + strlen(sep);
return (lo + (lo * (1 << 16))) * 2;
pixel = colors[code & 3] | (alpha << 24);
const unsigned a4 = (block[2+i*8]>>1) - block[6+i*8];
const unsigned a6 = (block[6+i*8]>>1) + block[2+i*8];
const unsigned a0 =  block[0+i*8] + block[4+i*8];
const unsigned a2 =  block[0+i*8] - block[4+i*8];
sum += coeffs[j] * s->decoded[channel][i - j - 1];
int32_t sum = (s->version < 2) ? 0 : s->blocksize / 2;
s->sprite_offset[0][1] = sprite_offset[0][1];
s->sprite_delta[i][0] - a * (1LL<<16),
s->sprite_delta[i][1] - a * (1LL<<16)
if (llabs(sprite_offset[0][i] + s->sprite_delta[i][0] * (w+16LL)) >= INT_MAX ||
llabs(sprite_offset[0][i] + s->sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
llabs(sprite_offset[0][i] + s->sprite_delta[i][0] * (w+16LL) + s->sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
s->sprite_delta[0][0]  = a;
s->sprite_delta[0][1]  =
s->sprite_delta[1][0]  = 0;
s->sprite_delta[1][1]  = a;
s->sprite_offset[0][0] = sprite_offset[0][0];
s->sprite_delta[0][0]  = a;
s->sprite_delta[0][1]  =
s->sprite_delta[1][0]  = 0;
s->sprite_delta[1][1]  = a;
s->sprite_offset[1][1] = sprite_offset[1][1];
s->sprite_offset[1][0] = sprite_offset[1][0];
s->sprite_delta[0][0] = (-r * sprite_ref[0][0] + virtual_ref[0][0]);
s->sprite_delta[0][1] = (+r * sprite_ref[0][1] - virtual_ref[0][1]);
s->sprite_delta[1][0] = (-r * sprite_ref[0][1] + virtual_ref[0][1]);
s->sprite_delta[1][1] = (-r * sprite_ref[0][0] + virtual_ref[0][0]);
llabs(s->sprite_delta[i][0] * (w+16LL)) >= INT_MAX ||
llabs(s->sprite_delta[i][1] * (w+16LL)) >= INT_MAX ||
s->sprite_delta[0][0] = (-r * sprite_ref[0][0] + virtual_ref[0][0]) * h3;
s->sprite_delta[0][1] = (-r * sprite_ref[0][0] + virtual_ref[1][0]) * w3;
s->sprite_delta[1][0] = (-r * sprite_ref[0][1] + virtual_ref[0][1]) * h3;
s->sprite_delta[1][1] = (-r * sprite_ref[0][1] + virtual_ref[1][1]) * w3;
if (s->sprite_delta[0][0] == a << ctx->sprite_shift[0] &&
s->sprite_delta[0][1] == 0 &&
s->sprite_delta[1][0] == 0 &&
s->sprite_delta[1][1] == a << ctx->sprite_shift[0]) {
s->sprite_delta[0][0] = a;
s->sprite_delta[0][1] = 0;
s->sprite_delta[1][0] = 0;
s->sprite_delta[1][1] = a;
FFABS(s->sprite_delta[0][i]) >= INT_MAX >> shift_y  ||
FFABS(s->sprite_delta[1][i]) >= INT_MAX >> shift_y
s->sprite_delta[0][i]  *= 1 << shift_y;
s->sprite_delta[1][i]  *= 1 << shift_y;
if (val >= end)
if (shift_c < 0 || shift_y < 0) {
avpriv_request_sample(s->avctx, "Too large sprite shift");
*got_frame = 1;
l->preamble      = CONVERT_TO_RESIDUE(res >> (RSIZE_BITS - off), off);
l->sign = ((l->preamble >> (RSIZE_BITS - l->preamble_bits)) & 1) ? -1 : +1;
} else if (s > 0) {
round = 1 << (s-1);
*lag_frac = (pitch_index - (*lag_int << 1)) << 1;
*lag_frac = (pitch_index - (*lag_int << 1) + 68) << 1;
if (shift < 0) {
block[0] = a->last_dc[component] << 3;
if (wanted_stream_spec[type] && st_index[type] == -1)
int ct, d;
if (ofs + len > frame_width)
if (ofs + len + 1 > frame_width)
if (ofs + len + 1 > frame_width)
len = rle_unpack(pb, &dp[ofs], len, frame_width - ofs);
else
if (s->size >= 0) {
meth = *pb++;
lz_unpack(pb, s->unpack_buffer, s->unpack_buffer_size);
if (frame_x || frame_y || (frame_width != s->avctx->width) ||
(frame_height != s->avctx->height)) {
s += 4;
if (chainlen == speclen)
while (dataleft > 0) {
tag = *s++;
if (d + 8 > d_end)
if (d + 1 > d_end)
s += 4;
if (pd + l > dest_end)
if (pd + i > dest_end)
int src_len, int dest_len)
} while (i < src_len);
if (src_len & 1)
src_len >>= 1;
no_residue[i] = floor->decode(vc, &floor->data, ch_floor_ptr);
floor_setup->data.t1.list[1].x = (1 << rangebits);
read_huffman_tree(avctx, gb);
read_huffman_tree(avctx, gb);
read_huffman_tree(avctx, gb);
read_huffman_tree(avctx, gb);
theora_decode_tables(avctx, &gb);
s->filesize = -1;
int64_t off = s->off;
s->filesize         = -1;
"Range: bytes=%"PRId64"-", s->off);
s->off = strtoll(p, NULL, 10);
s->filesize = strtoll(slash + 1, NULL, 10);
target_end >= 0 && s->off < target_end) {
"Stream ends prematurely at %"PRId64", should be %"PRId64"\n",
int64_t target_end = s->end_off ? s->end_off : s->filesize;
if ((!s->willclose || s->chunksize < 0) &&
target_end >= 0 && s->off >= target_end)
if (!len && (!s->willclose || s->chunksize < 0) &&
int remaining = s->icy_metaint - s->icy_data_read;
if (remaining < 0)
av_log(h, AV_LOG_INFO, "Will reconnect at %"PRId64" error=%s.\n", s->off, av_err2str(read_ret));
if (s->chunksize >= 0) {
av_log(h, AV_LOG_ERROR, "Failed to reconnect at %"PRId64".\n", target);
s->chunksize = strtoll(line, NULL, 16);
av_log(NULL, AV_LOG_TRACE, "Chunked encoding data size: %"PRId64"'\n",
int64_t target = h->is_streamed ? 0 : s->off;
int64_t old_off = s->off;
else if ((s->filesize == -1 && whence == SEEK_END))
} else if (!av_strcasecmp(tag, "Content-Length") && s->filesize == -1) {
s->filesize = strtoll(p, NULL, 10);
s->filesize  = -1;
s->icy_metaint = strtoll(p, NULL, 10);
s->chunksize = -1;
if (s->width != avctx->width && s->height != avctx->height) {
av_bprint_get_buffer(bp, 1, &buf, &buf_size);
if (!buf_size) {
zstream.avail_out = buf_size;
if (atom.size < sizeof(uuid) || atom.size == INT64_MAX)
if (state * 4ULL > 0xFF || i >= size)
if(avctx->slice_count) return avctx->slice_offset[n];
else                   return AV_RL32(buf + n*8 - 4) == 1 ? AV_RL32(buf + n*8) :  AV_RB32(buf + n*8);
if(offset < 0 || offset > buf_size){
}
break;
if (size < 0 || size > buf_size - offset) {
if (get_slice_offset(avctx, slices_hdr, i+1) < 0 ||
get_slice_offset(avctx, slices_hdr, i+1) > buf_size) {
if(get_slice_offset(avctx, slices_hdr, 0) < 0 ||
get_slice_offset(avctx, slices_hdr, 0) > buf_size){
if(i+2 < slice_count)
size = get_slice_offset(avctx, slices_hdr, i+2) - offset;
init_get_bits(&s->gb, buf+get_slice_offset(avctx, slices_hdr, 0), (buf_size-get_slice_offset(avctx, slices_hdr, 0))*8);
size = buf_size - offset;
else
av_log(avctx, AV_LOG_ERROR, "Slice size is invalid\n");
int offset = get_slice_offset(avctx, slices_hdr, i);
init_get_bits(&s->gb, buf+get_slice_offset(avctx, slices_hdr, i+1), (buf_size-get_slice_offset(avctx, slices_hdr, i+1))*8);
if(i+1 == slice_count)
size = buf_size - offset;
else
size = get_slice_offset(avctx, slices_hdr, i+1) - offset;
dc       = 13 * 13 * (dc == 1 ? 1538 * block[0]
(int8_t)pwt->chroma_weight[i][list][j][1] != pwt->chroma_weight[i][list][j][1])
int i, e, a;
L2 = L + ((int)(s->decorr[i].weightA * (unsigned)s->decorr[i].samplesA[0] + 512) >> 10);
L2 = L + ((int)(s->decorr[i].weightA * (unsigned)R2 + 512) >> 10);
L2 = L + ((int)(s->decorr[i].weightA * (unsigned)A + 512) >> 10);
R2 = R + ((int)(s->decorr[i].weightB * (unsigned)B + 512) >> 10);
R2 = R + ((int)(s->decorr[i].weightB * (unsigned)s->decorr[i].samplesB[0] + 512) >> 10);
S = T + ((int)(s->decorr[i].weightA * (unsigned)A + 512) >> 10);
s->offset[channel][s->nmean - 1] = s->bitshift == 32 ? 0 : (sum / s->blocksize) << s->bitshift;
ch_data->bs_num_env);
ch_data->bs_num_env = 2;
ch_data->bs_num_env = 2;
ch_data->bs_num_env);
ch_data->bs_num_env                 = num_rel_lead + num_rel_trail + 1;
if (ch_data->bs_num_env > 5) {
switch (ch_data->bs_frame_class = get_bits(gb, 2)) {
ch_data->bs_num_env                 = 1 << get_bits(gb, 2);
num_rel_lead                        = ch_data->bs_num_env - 1;
if (ch_data->bs_num_env == 1)
ch_data->bs_amp_res = 0;
if (ch_data->bs_num_env > 4) {
sqrtf(fixed_mean_energy);
s->frame->nb_samples = MPA_FRAME_SIZE;
if (frame_end - frame < 2)
return allocate_frame_buffers(ctx, avctx);
ctx->width     = avctx->width;
ctx->height    = avctx->height;
ctx->width  = width;
ctx->height = height;
if ((res = allocate_frame_buffers(ctx, avctx)) < 0)
int p, luma_width, luma_height, chroma_width, chroma_height;
luma_width  = ctx->width;
luma_height = ctx->height;
AVCodecContext *avctx)
s->width =           get_bits(&s->gb,14);
s->height =          get_bits(&s->gb,14);
if (ptr + cpp > end)
const uint8_t *end, *ptr = avpkt->data;
size *= 94;
end = avpkt->data + avpkt->size;
while (memcmp(ptr, "/* XPM */", 9) && ptr < end - 9)
if (ptr >= end) {
if (ptr + cpp > end)
if (pixdepth == 1) {
} else if (pixdepth == 8) {
if (frame_end - frame < width + 3)
if (s->has_alpha)
avctx->pix_fmt = AV_PIX_FMT_YUVA420P;
av_fast_malloc(&s->decoded_buffer, &s->decoded_size,
2 * FFALIGN(blockstodecode, 8) * sizeof(*s->decoded_buffer));
if (!nblocks || nblocks > INT_MAX) {
int ff_amf_tag_size(const uint8_t *data, const uint8_t *data_end)
if (ctx->mb_height > 68 ||
(ctx->mb_height << frame->interlaced_frame) > (ctx->height + 15) >> 4) {
if (!av_strstart(proto_name, "http", NULL) && !av_strstart(proto_name, "file", NULL))
if (!encoding && c->palette_size && c->bpp <= 8) {
uint8_t *output_samples_u8 = data;
for(i=0; i<s->height; i++)
memset(s->last_picture_ptr->f.data[0] + s->last_picture_ptr->f.linesize[0]*i, 16, s->width);
if (s->buf_end - s->buf < n)
if (s->buf_end - s->buf < n)
s->decoded[chan] = tmp_ptr;
s->decoded[chan][i] = 0;
s->decoded[chan] += s->nwrap;
tmp_ptr = av_realloc(s->decoded[chan], sizeof(int32_t)*(s->blocksize + s->nwrap));
s->decoded[i] -= s->nwrap;
av_freep(&s->decoded[i]);
if (!pcm)
break;
pcm  = ppcm[ipcm++];
/* next stereo channel (50Mbps and 100Mbps only) */
pcm = ppcm[ipcm++];
copy_fields(s, s1, golden_frame, current_frame);
if (!pcm)
break;
pcm  = ppcm[ipcm++];
/* next stereo channel (50Mbps and 100Mbps only) */
pcm = ppcm[ipcm++];
avctx->width   = width;
avctx->height  = height;
int code, i, j, level, val, run;
s1 = (181 * (a1 - a5 + a7 - a3) + 128) >> 8;
s2 = (181 * (a1 - a5 - a7 + a3) + 128) >> 8;
if (depth & 0x80)
else if (depth & 0x40)
int i, a1, b1, c1, d1;
tmp[i * 4 + 0] = (a1 + d1) >> 14;
tmp[i * 4 + 3] = (a1 - d1) >> 14;
tmp[i * 4 + 1] = (b1 + c1) >> 14;
tmp[i * 4 + 2] = (b1 - c1) >> 14;
((a1 + d1 + 0x20000) >> 18));
((a1 - d1 + 0x20000) >> 18));
((b1 + c1 + 0x20000) >> 18));
((b1 - c1 + 0x20000) >> 18));
mant <<= 24 - bits;
sum += filter_coeffs[i-1] * out[n-i];
((ox0 + ox1 + 1) << log2Wd)) >> (log2Wd + 1));
llabs(s->sprite_offset[0][i] + s->sprite_delta[i][0] * (w+16LL) + s->sprite_delta[i][1] * (h+16LL)) >= INT_MAX) {
unsigned len = get_symbol(c, state, 0) + 1;
*coef += (unsigned)(pv.mant << -shift);
coeff <<= 4;
if (get_bits_left(gb) < t - 1)
register int t= ( (v>>1)*qmul + qadd)>>QEXPSHIFT;
mvP->x += get_se_golomb(&h->gb);
mvP->y += get_se_golomb(&h->gb);
unsigned delta = -((int16_t)segments * width);
AVFrameSideData *av_frame_new_side_data(AVFrame *frame,
enum AVFrameSideDataType type,
int size)
for (i = 0; i < height; i++)
max[1] = 31;
avctx->sample_aspect_ratio = av_d2q(1.0 / ff_mpeg1_aspect[s->aspect_ratio_info], 255);
while (avio_tell(s->pb) < end) {
if (*(b - 1) == 0xff && avio_tell(s->pb) < end - 1) {
s->sprite_offset[0][0] =
s->sprite_offset[0][1] =
s->sprite_offset[1][0] =
s->sprite_offset[1][1] = 0;
if (llabs(s->sprite_offset[0][i] + s->sprite_delta[i][0] * (w+16LL)) >= INT_MAX ||
llabs(s->sprite_offset[0][i] + s->sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
llabs(s->sprite_offset[0][i] + s->sprite_delta[i][0] * (w+16LL) + s->sprite_delta[i][1] * (h+16LL)) >= INT_MAX ||
s->sprite_offset[0][0] = sprite_ref[0][0] - a * vop_ref[0][0];
s->sprite_offset[0][1] = sprite_ref[0][1] - a * vop_ref[0][1];
s->sprite_offset[1][0] = ((sprite_ref[0][0] >> 1) | (sprite_ref[0][0] & 1)) -
llabs(s->sprite_offset[0][i] + sd[1] * (h+16LL)) >= INT_MAX ||
s->sprite_offset[1][1] = ((sprite_ref[0][1] >> 1) | (sprite_ref[0][1] & 1)) -
s->sprite_offset[0][0] = (sprite_ref[0][0] * (1 << alpha + rho)) +
s->sprite_offset[0][1] = (sprite_ref[0][1] * (1 << alpha + rho)) +
s->sprite_offset[1][0] = ((-r * sprite_ref[0][0] + virtual_ref[0][0]) *
s->sprite_offset[1][1] = ((-r * sprite_ref[0][1] + virtual_ref[0][1]) *
s->sprite_offset[0][0] = (sprite_ref[0][0] * (1<<(alpha + beta + rho - min_ab))) +
(-r * sprite_ref[0][0] + virtual_ref[0][0]) *
h3 * (-vop_ref[0][0]) +
(-r * sprite_ref[0][0] + virtual_ref[1][0]) *
w3 * (-vop_ref[0][1]) +
(1 << (alpha + beta + rho - min_ab - 1));
s->sprite_offset[0][1] = (sprite_ref[0][1] * (1 << (alpha + beta + rho - min_ab))) +
(-r * sprite_ref[0][1] + virtual_ref[0][1]) *
h3 * (-vop_ref[0][0]) +
(-r * sprite_ref[0][1] + virtual_ref[1][1]) *
w3 * (-vop_ref[0][1]) +
(1 << (alpha + beta + rho - min_ab - 1));
s->sprite_offset[1][0] = (-r * sprite_ref[0][0] + virtual_ref[0][0]) *
h3 * (-2 * vop_ref[0][0] + 1) +
(-r * sprite_ref[0][0] + virtual_ref[1][0]) *
w3 * (-2 * vop_ref[0][1] + 1) + 2 * w2 * h3 *
r * sprite_ref[0][0] - 16 * w2 * h3 +
(1 << (alpha + beta + rho - min_ab + 1));
s->sprite_offset[1][1] = (-r * sprite_ref[0][1] + virtual_ref[0][1]) *
h3 * (-2 * vop_ref[0][0] + 1) +
(-r * sprite_ref[0][1] + virtual_ref[1][1]) *
w3 * (-2 * vop_ref[0][1] + 1) + 2 * w2 * h3 *
r * sprite_ref[0][1] - 16 * w2 * h3 +
(1 << (alpha + beta + rho - min_ab + 1));
s->sprite_offset[0][0] >>= ctx->sprite_shift[0];
s->sprite_offset[0][1] >>= ctx->sprite_shift[0];
s->sprite_offset[1][0] >>= ctx->sprite_shift[1];
s->sprite_offset[1][1] >>= ctx->sprite_shift[1];
llabs(s->sprite_offset[0][i] + sd[0] * (w+16LL)) >= INT_MAX ||
FFABS(s->sprite_offset[0][0]) >= INT_MAX >> shift_y  ||
FFABS(s->sprite_offset[1][0]) >= INT_MAX >> shift_c  ||
FFABS(s->sprite_offset[0][1]) >= INT_MAX >> shift_y  ||
FFABS(s->sprite_offset[1][1]) >= INT_MAX >> shift_c
llabs(s->sprite_offset[0][i] + sd[0] * (w+16LL) + sd[1] * (h+16LL)) >= INT_MAX
s->sprite_offset[0][i] *= 1 << shift_y;
s->sprite_offset[1][i] *= 1 << shift_c;
read_const_block_data(ctx, bd);
if (avctx->internal->skip_samples) {
for (ch = 0; ch <= s->max_matrix_channel; ch++)
return AVERROR_INVALIDDATA;
if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
return ret;
if (pal && pal_size == AVPALETTE_SIZE)
memcpy(gdv->pal, pal, AVPALETTE_SIZE);
while (!(x = get_byte(c)))
cx = (clr & 0xFFFFFF) >> 16;
cx = (clr & 0xFFFFFF) >> 16;
fp->state[i] = state_bits ? get_sbits(gbp, state_bits) << state_shift : 0;
ff_vp56_init_range_decoder(&s->c, buf, buf_size);
int ret = ff_set_dimensions(s->avctx, 16 * cols, 16 * rows);
ff_vp56_init_range_decoder(&s->cc, buf, buf_size);
ff_vp56_init_range_decoder(c, buf+6, buf_size-6);
ff_vp56_init_range_decoder(c, buf+1, buf_size-1);
ff_vp56_init_range_decoder(c, buf, part1_size);
ff_vp56_init_range_decoder(&s->coeff_partition[0], buf, buf_size);
ff_vp56_init_range_decoder(c, buf, header_size);
ff_vp56_init_range_decoder(&s->coeff_partition[i], buf, buf_size);
return 0;
ff_vp56_init_range_decoder(&s->coeff_partition[i], buf, size);
ff_vp56_init_range_decoder(&s->c, data2, size2);
if (wasted) {
return ret;
for (i = 0; i < num_coeff; i++)
block[ff_zigzag_direct[i]] = get_se_golomb(gb) *
s->plane[s->channel_num].band[0][0].width  = data;
s->plane[s->channel_num].band[0][0].stride = data;
s->plane[s->channel_num].band[s->level][s->subband_num].height = data;
s->plane[s->channel_num].band[0][0].height = data;
s->plane[s->channel_num].band[s->level][s->subband_num].width  = data;
s->plane[s->channel_num].band[s->level][s->subband_num].stride = FFALIGN(data, 8);
s->plane[s->channel_num].band[s->level][s->subband_num].stride = FFALIGN(data, 8);
s->plane[s->channel_num].band[s->level][s->subband_num].height = data;
s->plane[s->channel_num].band[s->level][s->subband_num].width  = data;
total_zeros_vlc[i].table = total_zeros_vlc_tables[i];
total_zeros_vlc[i].table_allocated = total_zeros_vlc_tables_size;
init_vlc(&total_zeros_vlc[i],
chroma_dc_total_zeros_vlc[i].table = chroma_dc_total_zeros_vlc_tables[i];
chroma_dc_total_zeros_vlc[i].table_allocated = chroma_dc_total_zeros_vlc_tables_size;
init_vlc(&chroma_dc_total_zeros_vlc[i],
chroma422_dc_total_zeros_vlc[i].table = chroma422_dc_total_zeros_vlc_tables[i];
chroma422_dc_total_zeros_vlc[i].table_allocated = chroma422_dc_total_zeros_vlc_tables_size;
init_vlc(&chroma422_dc_total_zeros_vlc[i],
zeros_left = get_vlc2(gb, (chroma422_dc_total_zeros_vlc-1)[total_coeff].table,
zeros_left= get_vlc2(gb, (total_zeros_vlc-1)[ total_coeff ].table, TOTAL_ZEROS_VLC_BITS, 1);
zeros_left = get_vlc2(gb, (chroma_dc_total_zeros_vlc-1)[total_coeff].table,
bits[*pos] = (~pfx) & ((1 << FFMAX(pl, 1)) - 1);
} else if (!tagname[1] && strspn(tagname, "bisu") == 1) {
if (s->flipped) {
if (prev_palette_plane == palette_plane && FFABS(curframe_index - prevframe_index) < pixel_count) {
htaps= get_symbol(&s->c, s->header_state, 0)*2 + 2;
if((unsigned)htaps >= HTAPS_MAX || htaps==0)
if (!FIELD_PICTURE && h->current_slice)
init_vlc(&s->vlc[i], VLC_BITS, 256, s->len[i], 1, 1,
s->bits[i], 4, 4, 0);
s->bits[i], 4, 4, 0);
init_vlc(&s->vlc[i], VLC_BITS, 256, s->len[i], 1, 1,
return ((x+1)*21845 + 10922) >> 16;
const uint32_t *src_pb = src_py + t * linesize;
return av_clip(re_signal << 2, -0xffff, 0xffff);
if (sl->redundant_pic_count > 0)
channels = av_get_channel_layout_nb_channels(frame->channel_layout);
for (n = nb_samples >> (1 - st); n > 0; n--) {
int expected = highpass_height * highpass_stride;
if (highpass_height > highpass_a_height || highpass_width > highpass_a_width || a_expected < expected) {
dst[i + stride * 0] = av_clip_uint8(dst[i + stride * 0] + ((z0 + z3) * qmul + rr >> 20));
dst[i + stride * 1] = av_clip_uint8(dst[i + stride * 1] + ((z1 + z2) * qmul + rr >> 20));
dst[i + stride * 2] = av_clip_uint8(dst[i + stride * 2] + ((z1 - z2) * qmul + rr >> 20));
dst[i + stride * 3] = av_clip_uint8(dst[i + stride * 3] + ((z0 - z3) * qmul + rr >> 20));
(frame->data[1][3+i*4]<<24)
const int tA = (blk[0 * step] - blk[4 * step] << 15) + rnd;
const int tB = (blk[0 * step] + blk[4 * step] << 15) + rnd;
if (w < 0 || h < 0)
return;
if (y < 0) {
return AVERROR_INVALIDDATA;
(-r * sprite_ref[0][0] + virtual_ref[0][0]) *
(-vop_ref[0][0]) +
(r * sprite_ref[0][1] - virtual_ref[0][1]) *
(-vop_ref[0][1]) + (1 << (alpha + rho - 1));
sprite_offset[0][1]    = (sprite_ref[0][1] * (1 << alpha + rho)) +
(-r * sprite_ref[0][1] + virtual_ref[0][1]) *
(-vop_ref[0][0]) +
(-r * sprite_ref[0][0] + virtual_ref[0][0]) *
(-vop_ref[0][1]) + (1 << (alpha + rho - 1));
sprite_offset[1][0]    = ((-r * sprite_ref[0][0] + virtual_ref[0][0]) *
(-2 * vop_ref[0][0] + 1) +
(r * sprite_ref[0][1] - virtual_ref[0][1]) *
(-2 * vop_ref[0][1] + 1) + 2 * w2 * r *
sprite_ref[0][0] - 16 * w2 + (1 << (alpha + rho + 1)));
sprite_offset[1][1]    = ((-r * sprite_ref[0][1] + virtual_ref[0][1]) *
(-2 * vop_ref[0][0] + 1) +
(-r * sprite_ref[0][0] + virtual_ref[0][0]) *
(-2 * vop_ref[0][1] + 1) + 2 * w2 * r *
sprite_ref[0][1] - 16 * w2 + (1 << (alpha + rho + 1)));
sprite_offset[0][0]    = (sprite_ref[0][0] * (1 << alpha + rho)) +
int v = get_sr_golomb_flac(&s->gb, tmp, INT_MAX, 0);
int v = get_sr_golomb_flac(&s->gb, tmp, INT_MAX, 0);
const int b7 =  a7 - (a1>>2);
dst[i + 0*stride] = av_clip_pixel( dst[i + 0*stride] + ((b0 + b7) >> 6) );
dst[i + 1*stride] = av_clip_pixel( dst[i + 1*stride] + ((b2 + b5) >> 6) );
dst[i + 2*stride] = av_clip_pixel( dst[i + 2*stride] + ((b4 + b3) >> 6) );
dst[i + 3*stride] = av_clip_pixel( dst[i + 3*stride] + ((b6 + b1) >> 6) );
dst[i + 4*stride] = av_clip_pixel( dst[i + 4*stride] + ((b6 - b1) >> 6) );
dst[i + 5*stride] = av_clip_pixel( dst[i + 5*stride] + ((b4 - b3) >> 6) );
dst[i + 6*stride] = av_clip_pixel( dst[i + 6*stride] + ((b2 - b5) >> 6) );
dst[i + 7*stride] = av_clip_pixel( dst[i + 7*stride] + ((b0 - b7) >> 6) );
const int a0 =  block[0+i*8] + block[4+i*8];
const int a2 =  block[0+i*8] - block[4+i*8];
const int a4 = (block[2+i*8]>>1) - block[6+i*8];
const int a6 = (block[6+i*8]>>1) + block[2+i*8];
const int b0 = a0 + a6;
const int b2 = a2 + a4;
const int b4 = a2 - a4;
const int b6 = a0 - a6;
const int a1 = -block[3+i*8] + block[5+i*8] - block[7+i*8] - (block[7+i*8]>>1);
const int a3 =  block[1+i*8] + block[7+i*8] - block[3+i*8] - (block[3+i*8]>>1);
const int a5 = -block[1+i*8] + block[7+i*8] + block[5+i*8] + (block[5+i*8]>>1);
const int a7 =  block[3+i*8] + block[5+i*8] + block[1+i*8] + (block[1+i*8]>>1);
const int b1 = (a7>>2) + a1;
const int b3 =  a3 + (a5>>2);
const int b5 = (a3>>2) - a5;
int my_col            = (mv_col[1] << y_shift) / 2;
if (shift_c < 0 || shift_y < 0 ||
FFABS(sprite_offset[0][0]) >= INT_MAX >> shift_y  ||
FFABS(sprite_offset[1][0]) >= INT_MAX >> shift_c  ||
FFABS(sprite_offset[0][1]) >= INT_MAX >> shift_y  ||
FFABS(sprite_offset[1][1]) >= INT_MAX >> shift_c
) {
avpriv_request_sample(s->avctx, "Too large sprite shift or offset");
goto overflow;
dst[i] = vector[i] << bits >> 3;
int temp1     = cos_tab[index] << 16;
((offset << 8) + 0x80) << 1;
f1[1] = ((lpc[2 * i]     << 16 >> i) + f1[1]) >> 1;
f2[1] = ((lpc[2 * i + 1] << 16 >> i) + f2[1]) >> 1;
f1[1] = (lpc[0] << 14) + (lpc[2] << 14);
lpc[i] = av_clipl_int32(((ff1 + ff2) << 3) + (1 << 15)) >> 16;
lpc[LPC_ORDER - i - 1] = av_clipl_int32(((ff1 - ff2) << 3) +
f2[1] = (lpc[1] << 14) + (lpc[3] << 14);
*ptr16= pred + (dc << point_transform);
unsigned idx = val - 0x17 + get_bits1(&gb) * byte;
L2 = L + ((s->decorr[i].weightA * A + 512) >> 10);
R2 = R + ((s->decorr[i].weightB * B + 512) >> 10);
block->u.mv[i][0] += dirac_get_arith_int(arith + 4 + 2 * i, CTX_MV_F1, CTX_MV_DATA);
block->u.mv[i][1] += dirac_get_arith_int(arith + 5 + 2 * i, CTX_MV_F1, CTX_MV_DATA);
int alpha = 0;
s->hybrid_minclip = ((-1LL << (orig_bpp - 1)));
if (prefix == CABAC_MAX_BIN) {
avctx->width  = s->width;
avctx->height = s->height;
return base_value + ((v - 7) << w->shift);
width <<= 1;
const int t8 =  17734 * blk[2 * step] - 42813 * blk[6 * step];
const int t9 =  17734 * blk[6 * step] + 42814 * blk[2 * step];
const int tA = (blk[0 * step] - blk[4 * step]) * 32768 + rnd;
const int tB = (blk[0 * step] + blk[4 * step]) * 32768 + rnd;
blk[0 * step] = (  t4       + t9 + tB) >> shift;
blk[1 * step] = (  t6 + t7  + t8 + tA) >> shift;
blk[2 * step] = (  t6 - t7  - t8 + tA) >> shift;
blk[3 * step] = (  t5       - t9 + tB) >> shift;
blk[4 * step] = ( -t5       - t9 + tB) >> shift;
blk[5 * step] = (-(t6 - t7) - t8 + tA) >> shift;
blk[6 * step] = (-(t6 + t7) + t8 + tA) >> shift;
blk[7 * step] = ( -t4       + t9 + tB) >> shift;
const int t4 = 5793 * (t2 + t0 + 0x800 >> 12);
const int t5 = 5793 * (t3 + t1 + 0x800 >> 12);
const int t6 = t2 - t0;
const int t7 = t3 - t1;
int den = h->direct_den[col_mv->ref];
b1[i] -= (b0[i] + b2[i] + 2) >> 2;
S  <<= s->float_shift;
w, h, dx, dy, c->width, c->height);
return AVERROR_INVALIDDATA;
}
if ((dx + w > c->width) || (dy + h > c->height)) {
av_log(avctx, AV_LOG_ERROR,
"Incorrect frame size: %ix%i+%ix%i of %ix%i\n",
w, h, dx, dy, c->width, c->height);
return AVERROR_INVALIDDATA;
}
if ((dx + w > c->width) || (dy + h > c->height)) {
av_log(avctx, AV_LOG_ERROR,
"Incorrect frame size: %ix%i+%ix%i of %ix%i\n",
round = 1 << (nz-1);
int nz, mant, expo, round;
round = 1 << (nz-1);
i = (int)((accu + round) >> nz);
i >>= 1;
ret = av_int2sf(i, 15 - nz);
int64_t accu = 0;
int i, nz, round;
i = (int)(accu >> 32);
if (i == 0) {
nz = 0;
while (FFABS(i) < 0x40000000) {
i <<= 1;
round = 1 << (s-1);
che->ch[1].ret[j] = (int32_t)av_clipl_int32((int64_t)che->ch[1].ret[j]<<7)+0x8000;
che->ch[0].ret[j] = (int32_t)av_clipl_int32((int64_t)che->ch[0].ret[j]<<7)+0x8000;
if (buf_size * 8LL < a->mb_height2 * a->mb_width2 * 13LL)
int mid = (base * 2 + add + 1) >> 1;
mid = (base * 2 + add + 1) >> 1;
return AVERROR_INVALIDDATA;
s->num_primitive_matrices = 0;
return AVERROR_INVALIDDATA;
return AVERROR_INVALIDDATA;
FFSWAP(uint8_t, ((uint8_t *)line)[x], ((uint8_t *)line)[w - x - 1]);
}
if (flags & TGA_RIGHTTOLEFT) { // right-to-left, needs horizontal flip
int x;
for (y = 0; y < h; y++) {
void *line = &p->data[0][y * p->linesize[0]];
for (x = 0; x < w >> 1; x++) {
switch (bpp) {
case 32:
FFSWAP(uint32_t, ((uint32_t *)line)[x], ((uint32_t *)line)[w - x - 1]);
break;
case 24:
FFSWAP(uint8_t, ((uint8_t *)line)[3 * x    ], ((uint8_t *)line)[3 * w - 3 * x - 3]);
FFSWAP(uint8_t, ((uint8_t *)line)[3 * x + 1], ((uint8_t *)line)[3 * w - 3 * x - 2]);
FFSWAP(uint8_t, ((uint8_t *)line)[3 * x + 2], ((uint8_t *)line)[3 * w - 3 * x - 1]);
break;
case 16:
FFSWAP(uint16_t, ((uint16_t *)line)[x], ((uint16_t *)line)[w - x - 1]);
break;
case 8:
line = av_malloc(img->frame->linesize[0]);
*o++ = (ff_reverse[buf[2] & 0xf0] << 28) |
*o++ = (ff_reverse[buf[2]]        << 24) |
*o++ = (ff_reverse[buf[5] & 0xf0] << 28) |
*o++ = (ff_reverse[buf[6] & 0xf0] << 28) |
level = (level * qscale * quant_matrix[j]) >> 3;
level = (level * qscale * quant_matrix[j]) >> 3;
state += (int64_t)d * yflag - ((int64_t)(d * (uint64_t)state) >> 8);
par[ 3] = (int)(((int64_t)((par[ 4]>>1) + par[ 5]) * 1431655765 + \
par[ 0] = (int)(((int64_t)(par[ 0] + (par[ 1]>>1)) * 1431655765 + \
par[ 1] = (int)(((int64_t)((par[ 1]>>1) + par[ 2]) * 1431655765 + \
par[ 2] = (int)(((int64_t)(par[ 3] + (par[ 4]>>1)) * 1431655765 + \
#   define MULLx(x, y, s) MULL(x,y,s)
#   define SHR(a,b)       ((a)>>(b))
INTFLOAT t0, t1, t2, t3, s0, s1, s2, s3;
INTFLOAT tmp[18], *tmp1, *in1;
pwt->luma_weight[16 + 2 * i][list][0] = pwt->luma_weight[16 + 2 * i + 1][list][0] = pwt->luma_weight[i][list][0];
pwt->luma_weight[16 + 2 * i][list][1] = pwt->luma_weight[16 + 2 * i + 1][list][1] = pwt->luma_weight[i][list][1];
for (j = 0; j < 2; j++) {
pwt->chroma_weight[16 + 2 * i][list][j][0] = pwt->chroma_weight[16 + 2 * i + 1][list][j][0] = pwt->chroma_weight[i][list][j][0];
pwt->chroma_weight[16 + 2 * i][list][j][1] = pwt->chroma_weight[16 + 2 * i + 1][list][j][1] = pwt->chroma_weight[i][list][j][1];
H264PredWeightTable *pwt, void *logctx)
v[i] = (ff_gain_val_tab[n][i] * m[i]) >> ff_gain_exp_tab[n];
return i << shift;
*la <<= l;
if ((ret = ff_reget_buffer(avctx, c->pic)) < 0) {
return ret;
}
*got_frame      = 1;
if ((ret = av_frame_ref(data, c->pic)) < 0)
return ret;
*coef += pv.mant << -shift;
*coef += (pv.mant + (1 << (shift - 1))) >> shift;
if (R<0 || G<0 || B<0) {
if (ret < 0)
m[0] = (ff_irms(&ractx->adsp, ractx->buffer_a) * gval) >> 12;
FF_ALLOC_OR_GOTO(c, c->lumPixBuf,  c->vLumBufSize * 3 * sizeof(int16_t *), fail);
FF_ALLOC_OR_GOTO(c, c->chrUPixBuf, c->vChrBufSize * 3 * sizeof(int16_t *), fail);
FF_ALLOC_OR_GOTO(c, c->chrVPixBuf, c->vChrBufSize * 3 * sizeof(int16_t *), fail);
line[w - 1] =
line[w - 2] = line[(w - 1) / 3];
((uint16_t*)line)[w - 1] =
((uint16_t*)line)[w - 2] = ((uint16_t*)line)[(w - 1) / 3];
tile->coord[1][1] = FFMIN((tiley + 1) * s->tile_height + s->tile_offset_y, s->height);
tile->coord[0][0] = FFMAX(tilex       * s->tile_width  + s->tile_offset_x, s->image_offset_x);
tile->coord[0][1] = FFMIN((tilex + 1) * s->tile_width  + s->tile_offset_x, s->width);
tile->coord[1][0] = FFMAX(tiley       * s->tile_height + s->tile_offset_y, s->image_offset_y);
s->rgb         = 1;
s->pegasus_rct = 0;
s->rgb         = 1;
s->pegasus_rct = 1;
if ((ret = ff_alloc_packet2(avctx, pkt, pkt_size)) < 0)
encode_slice(avctx, pic, &pb, sizes, x, y, q, mbs_per_slice);
pkt_size = ctx->frame_size_upper_bound + FF_MIN_BUFFER_SIZE;
*ptr16= pred + (dc << point_transform);
*ptr = pred + (dc << point_transform);
lpc[    j] = f + AAC_MUL26(r, b);
lpc[i-1-j] = b + AAC_MUL26(r, f);
data[i] *= 1 << I_PRESHIFT;
block[0] = dc << (3 - s->intra_dc_precision);
dst[2] += src[2];
dst[3] += src[3];
dst[0] += src[0];
dst[1] += src[1];
dst[6] += src[6];
dst[7] += src[7];
dst[0] += src[0];
dst[1] += src[1];
dst[2] += src[2];
dst[3] += src[3];
dst[4] += src[4];
dst[5] += src[5];
int quant = b->quant;
b->quant = quant;
quant += dirac_get_arith_int(c, CTX_DELTA_Q_F, CTX_DELTA_Q_DATA);
quant += dirac_get_se_golomb(gb);
if (quant < 0) {
buf_out[i] = p->filter_out[i + p->order];
if (half_vert)
if ((ret = setup_classifs(vc, vr, do_not_decode, ch_used, partition_count)) < 0)
p += vr->ptns_to_read;
if (i < vr->ptns_to_read)
if (i < vr->ptns_to_read)
int partition_count)
s->bits = get_bits(&s->gb, 8);
s->bits = 9;
if (s->bits == 9 && !s->pegasus_rct)
if (s->ls && !(s->bits <= 8 || nb_components == 1)) {
int len, nb_components, i, width, height, pix_fmt_id, ret;
unsigned int     x, y;
if (y1 >= height) {
y1 = pass ? 2 : 4;
ptr = ptr1 + linesize * y1;
pass++;
}
if (y1 >= height) {
y1 = 1;
ptr = ptr1 + linesize;
pass++;
}
s->bppcount = count;
if (count > 4) {
s->bpp, count);
if ((unsigned)elems + 1 > INT_MAX / sizeof(*pkt->side_data))
if (shift < 30) {
if (shift < 30) {
if (s->size < 10)
return AVERROR_INVALIDDATA;
if (stream_ptr_after_chunk - bytestream2_tell(&g2) > 0)
msb[n] = msb[n] * (1 << shift) + (lsb[n] << adj);
msb[n] = msb[n] * (1 << shift);
row_ptr -= stream_byte * row_dec;
if (row_ptr + pixel_ptr + stream_byte > frame_size) {
pic->data[0][row_ptr + pixel_ptr] = stream_byte & 0x0F;
int row_dec = pic->linesize[0];
int row_ptr = (avctx->height - 1) * row_dec;
int frame_size = row_dec * avctx->height;
while (row_ptr >= 0) {
pic->data[0][row_ptr + pixel_ptr] = stream_byte >> 4;
"MS RLE: bytestream overrun, %d rows left\n",
row_ptr);
pic->data[0][row_ptr + pixel_ptr] = stream_byte >> 4;
row_ptr -= row_dec;
pic->data[0][row_ptr + pixel_ptr] = stream_byte & 0x0F;
if (row_ptr + pixel_ptr + stream_byte > frame_size ||
if (s->nb_components > 1)
else if (s->palette_index && s->bits <= 8)
while (!(x = get_byte(c)))
if (av_packet_get_side_data(avpkt, AV_PKT_DATA_PARAM_CHANGE, NULL)) {
av_frame_unref(s->last_frame);
av_frame_unref(s->second_last_frame);
}
sign = (idx << 27) >> 31;
sign = (idx << 27) >> 31;
if (   chroma_planes != f->chroma_planes
f->avctx->bits_per_raw_sample = get_symbol(c, state, 0);
f->colorspace = get_symbol(c, state, 0); //YUV cs type
if (f->version > 0)
int chroma_planes, chroma_h_shift, chroma_v_shift, transparency;
int i, log2_max_num_subframes, num_possible_block_sizes;
3, s->decode_flags);
s->samples_per_frame = 1 << ff_wma_get_frame_len_bits(avctx->sample_rate,
p0 += (tmp0 + tmp1) << 2;
p0 += (tmp0 + tmp1) << 3;
p1 += (tmp0 + tmp1 + b1_1 + b1_2) << 2;
p2 +=  tmp2 << 2;
p3 += (tmp2 + b1_3) << 1;
p2 += (tmp0 + b2_4 + b2_5) << 2;
p3 += (tmp1 + b2_4 - b2_5*6 + b2_6) << 1;
p0 += tmp0 << 3;
p1 += tmp1 << 2;
p0 =  tmp0 << 4;
p1 =  tmp1 << 3;
p2 = (tmp0 + tmp2) << 3;
p3 = (tmp1 + tmp2 + b0_2) << 2;
p2 += (b3_7 + b3_8) << 1;
p1 += (tmp0 - tmp1*6 + tmp2) << 1;
dest[group * 128 + k] += (tmp + round) >> shift;
if (data_size <= 0 || data_size > buf_size)
if (line_offset > buf_size - 8)
if (data_size <= 0 || data_size > buf_size)
if (line_offset > buf_size - 20)
sce->coeffs[i] += predFreq[i];
if (bytestream2_get_bytes_left(&s->gb) < s->geotag_count * sizeof(int16_t) * 4) {
i0 = *src0 + *src2 + (((26345 * *src2) + (1 << 15)) >> 16);
- (((i_ict_params[2] * *src2) + (1 << 15)) >> 16);
line[x] <<= FRAC_BITS;
dest[i] += tmp << shift;
int prob, prob2, helper, val;
if (next)
next = (last + get_se_golomb(gb)) & 0xff;
block->u.dc[i] += dirac_get_arith_int(arith+1+i, CTX_DC_F1, CTX_DC_DATA);
v = bytestream2_get_byte(&s->gb);
S <<= s->extra_bits;
my = s->next_pic->motion_val[0][b_xy][1] << 1;
mx = s->next_pic->motion_val[0][b_xy][0] << 1;
mant = (mant + 0x40)>>7;
decode_line(s, w, sample, plane_index, 8);
decode_line(s, w, sample, plane_index, s->avctx->bits_per_raw_sample);
return;
int v, count, segments;
int i, e, a;
return (val * mul + 0x2000) >> 14;
for (i = 0; i < count; i++)
if (s->rps <= 0) {
if (len[i] == 0)
if (len[i] == 0)
if (len[i] == 0)
if (len[i] == 0)
if (len[i] == 0)
ff_bgmc_decode(gb, sb_length, current_res,
current_res += sb_length;
av_assert0(TPsot < FF_ARRAY_ELEMS(s->tile[Isot].tile_part));
sp1 = src[0] << shift;
sp2 = src[4] << shift;
s->channel[c].num_vec_coeffs = get_bits(&s->gb, num_bits) << 2;
dst[i] = out * ssign;
prefetch_motion(h, sl, 0, PIXEL_SHIFT, CHROMA_IDC);
if (get_bits_left(gb) < t2 - 1)
h->recovery_frame_cnt = get_ue_golomb_long(gb);
ret = decode_recovery_point(&h->recovery_point, gb);
if (prefix_code > 39) {
if (FFABS(L) + (unsigned)FFABS(R) > (1<<19)) {
value=AcquireString(q);
if (code < 0)
if (ctx->idat == NULL)
*pixels;
/*
Persistent pixel cache.
*/
pixels=(unsigned char *)  GetImagePixelCachePixels(image,&length);
if (pixels == (unsigned char *) NULL)
if (file == -1)
ThrowWriterException(FileOpenError,"UnableToOpenFile");
file=open_utf8(cache_filename,O_WRONLY | O_CREAT | O_BINARY,S_MODE);
if (file == -1)
count=0;
for (i=0; i < (MagickOffsetType) length; i+=count)
offset=0;
count=write(file,pixels+i,(size_t) MagickMin(length-i,(size_t)
SSIZE_MAX));
#else
count=pwrite(file,pixels+i,(size_t) MagickMin(length-i,(size_t)
SSIZE_MAX),(off_t) i);
#endif 
if (count <= 0)
count=0;
if (errno != EINTR)
break;
close(file);
if (i < (MagickOffsetType) length)
}
MagickSizeType
#if !defined(MAGICKCORE_HAVE_PWRITE)
{
int
file;
offset,
length;
register MagickOffsetType
i;
ssize_t
count;
unsigned char
DestroyBlob(p);
pixel=QuantumRange*gamma*(Dca*Sa+Da*(2.0*Sca-Sa)*(pow((Dca/Da),0.5)-
(Dca/Da))+Sca*(1.0-Da)+Dca*(1.0-Sa));
if ((IsNaN(Da) == MagickFalse) && (IsNaN(Sca) == MagickFalse))
pixel=QuantumRange*gamma*(Dca*Sa*Sa/Sca+Dca*(1.0-Sa)+Sca*(1.0-Da));
pixel=QuantumRange*gamma*(Dca*(Sa+(2.0*Sca-Sa)*(1.0-(Dca/Da)))+
pixel=QuantumRange*gamma*(Dca*Sa+Da*(2.0*Sca-Sa)*(4.0*(Dca/Da)*
(4.0*(Dca/Da)+1.0)*((Dca/Da)-1.0)+7.0*(Dca/Da))+Sca*(1.0-Da)+
while (offset <= (ssize_t) length)
histogram_image->blob=(BlobInfo *) DetachBlob(histogram_image->blob);
image->blob=(BlobInfo *) DetachBlob(image->blob);
assert(data != (const void *) NULL);
points_extent=points_extent*BezierQuantum;
break;
(void) SignatureImage(image,exception);
draw_info->direction == RightToLeftDirection ? image->columns-
return((Image *) NULL);
ThrowReaderException(FileOpenError,"UnableToOpenFile");
return((Image *) NULL);
coordinates+=(20*BezierQuantum)+360;
coordinates=(double) (BezierQuantum*primitive_info[j].coordinates);
if (((MagickSizeType) (i+coordinates)) >= number_points)
coordinates*=5;
coordinates=1;
coordinates=2.0*(ceil(MagickPI*radius))+6*BezierQuantum+360.0;
coordinates*=5;
coordinates+=2*((size_t) ceil((double) MagickPI*radius))+6*
BezierQuantum+360;
read_info=DestroyImageInfo(read_info);
ThrowPointExpectedException(token,exception);
tag=(ReadBlobLSBShort(image) << 16) | ReadBlobLSBShort(image);
tag=(ReadBlobLSBShort(image) << 16) | ReadBlobLSBShort(image);
default: ThrowReaderException(CoderError, "MultidimensionalMatricesAreNotSupported");
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
for (j=0; j < current_layer; j++)
int j;
ThrowBinaryException(CorruptImageError,"NotEnoughPixelData",
image->filename);
layer_info[j].image=DestroyImage(layer_info[j].image);
clone_info=CloneImageInfo(image_info);
ThrowReaderException(CorruptImageError,"CorruptImage");
if (HeapOverflowSanityCheck(number_pixels,viff_info.number_data_bands) != MagickFalse)
if ((bytes_per_pixel*max_packets) > GetBlobSize(image))
pixels=(unsigned char *) AcquireQuantumMemory(MagickMax(number_pixels,
max_packets),bytes_per_pixel*sizeof(*pixels));
if (image->colors > GetBlobSize(image))
if (viff_info.map_rows >
image->colormap[i].red=ScaleCharToQuantum((unsigned char) value);
image->colormap[i].green=
image->colormap[i].blue=ScaleCharToQuantum((unsigned char) value);
image->colormap[i % image->colors].green=
image->colormap[i % image->colors].blue=
/*
Initialize image structure.
*/
image->alpha_trait=viff_info.number_data_bands == 4 ? BlendPixelTrait :
UndefinedPixelTrait;
image->storage_class=(viff_info.number_data_bands < 3 ? PseudoClass :
DirectClass);
image->columns=viff_info.rows;
image->rows=viff_info.columns;
if (comment_info.comment == (char *) NULL)  \
(void) CopyMagickString(write_info->magick,"EPS2",MagickPathExtent);
(void) CopyMagickString(write_info->magick,"EPS3",MagickPathExtent);
val += (unsigned char)(data[0]) << 24;
val += (unsigned char)(data[1]) << 16;
val += (unsigned char)(data[2]) << 8;
val += (unsigned char)(data[3]);
val  = (unsigned char)(db->data[db->pos+0]) << 24;
val += (unsigned char)(db->data[db->pos+1]) << 16;
val += (unsigned char)(db->data[db->pos+2]) << 8;
val += (unsigned char)(db->data[db->pos+3]);
val  = (unsigned char)(db->data[db->pos+0]) << 8;
val += (unsigned char)(db->data[db->pos+1]);
val = (unsigned char)(db->data[db->pos]);
sizeof(*graphic_context[n]->dash_pattern));
primitive_info[j+1].point,degrees);
coordinates=GetEllipseCoordinates(primitive_info[j].point,
(void) memset(graphic_context[n]->dash_pattern,0,(2UL*x+2UL)*
blob_info->eof=MagickFalse;
(void) CheckPrimitiveExtent(&mvg_info,number_points);
DrawError,"TooManyBezierCoordinates","`%s'",token);
(void) CheckPrimitiveExtent(&mvg_info,4096);
(void) CheckPrimitiveExtent(&mvg_info,number_points);
return(MagickFalse);
primitive_info=ResizeQuantumMemory(primitive_info,extent,
sizeof(*primitive_info));
if (CheckPrimitiveExtent(mvg_info,control_points+1) != MagickFalse)
primitive_info=(*mvg_info->primitive_info)+mvg_info->offset;
if (CheckPrimitiveExtent(mvg_info,extent) != MagickFalse)
primitive_info=(*mvg_info->primitive_info)+mvg_info->offset;
if (((size_t) (mvg_info->offset+4096) > *mvg_info->extent) &&
if (((size_t) (mvg_info->offset+4096) > *mvg_info->extent) &&
(CheckPrimitiveExtent(mvg_info,4096) != MagickFalse))
q=(*mvg_info->primitive_info)+mvg_info->offset;
if (((size_t) (mvg_info->offset+4096) > *mvg_info->extent) &&
(CheckPrimitiveExtent(mvg_info,4096) != MagickFalse))
q=(*mvg_info->primitive_info)+mvg_info->offset;
(CheckPrimitiveExtent(mvg_info,4096) != MagickFalse))
(CheckPrimitiveExtent(mvg_info,4096) != MagickFalse))
sweep=fabs(StringToDouble(token,&next_token)) < DrawEpsilon ?
MagickFalse : MagickTrue;
if (token == next_token)
ThrowPointExpectedException(token,exception);
q=(*mvg_info->primitive_info)+mvg_info->offset;
if (((size_t) (mvg_info->offset+4096) > *mvg_info->extent) &&
(CheckPrimitiveExtent(mvg_info,4096) != MagickFalse))
q=(*mvg_info->primitive_info)+mvg_info->offset;
q=(*mvg_info->primitive_info)+mvg_info->offset;
if (((size_t) (mvg_info->offset+4096) > *mvg_info->extent) &&
profile=BlobToStringInfo((const unsigned char *) NULL,cin.file.user_length);
entry->flags^=CoderBlobSupportFlag;
continue;
status=MagickFalse;
if (status == MagickFalse)
continue;
(void) ThrowMagickException(exception,GetMagickModule(),DrawError,
"TooManyBezierCoordinates","`%s'",token);
image=DestroyImage(image);
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
if ((MagickSizeType) length > GetBlobSize(image))
angle.y=DegreesToRadians(degrees.y);
if (image_info->depth > 100)
bits_per_pixel=image_info->depth-100;
if (bits_per_pixel < 16)
(void) TransformImageColorspace(image,image->colorspace,exception);
*quantum_info;
sixel_buffer=(char *) AcquireQuantumMemory((size_t) length,
parameters.cp_comment=ConstantString(property);
while (num_pad_bytes--) ReadBlobByte( image );
ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
MATLAB_KO: ThrowReaderException(CorruptImageError,"ImproperImageHeader");
scale=QuantumRange/(fits_info.max_data-fits_info.min_data);
break;
break;
count=FormatLocaleString(header,MagickPathExtent,"#%s\n",property);
return(MagickEpsilon);
return(erf(alpha));
return(exp(alpha));
return(2.7182818284590452354);
return(floor(alpha));
return(QuantumRange);
return(gamma);
return((double) gcd);
subexpression[MagickPathExtent];
return(0.0);
return(hypot(alpha,*beta));
return(floor(alpha));
return((double) !!IsNaN(alpha));
return(j0(alpha));
return(j1(alpha));
return(fmod(alpha,*beta));
return(log(alpha));
return(log10(alpha))/log10(2.0);
return(log10(alpha));
return(0.0);
return(QuantumRange);
return(0.0);
return(alpha > *beta ? alpha : *beta);
return(alpha < *beta ? alpha : *beta);
return(gamma);
return((double) (alpha < MagickEpsilon));
return(fabs(alpha-(*beta)) < MagickEpsilon ? 1.0 : 0.0);
return(fabs(alpha-(*beta)) >= MagickEpsilon ? 1.0 : 0.0);
return(MagickPHI);
return(MagickPI);
return(pow(alpha,*beta));
return(*beta);
return(QuantumScale);
return(*beta);
return(alpha);
return(floor(alpha+0.5));
return(sinh(alpha));
return(sin(alpha));
return(sqrt(alpha));
return((1.0/(1.0+exp(-alpha))));
return(tanh(alpha));
return(tan(alpha));
return(ceil(alpha));
return((double) (~(size_t) (gamma+0.5)));
return(fabs(alpha));
return(acosh(alpha));
return(*beta);
return(acos(alpha));
return(asinh(alpha));
return(asin(alpha));
return(atan2(alpha,*beta));
return(atanh(alpha));
return(atan(alpha));
return(ceil(alpha));
return(0.0);
return(1.0);
return(alpha);
return(cosh(alpha));
return(cos(alpha));
return(floor(alpha));
return((alpha/(*beta*(alpha-1.0)+1.0)));
if (maximum_length > MaxBezierCoordinates)
*mvg_info->extent=extent;
if (primitive_info[i].text != (char *) NULL)
primitive_info[i].text=(char *) RelinquishMagickMemory(
primitive_info[i].text);
xcfdata=(XCFPixelInfo *) AcquireQuantumMemory(data_length,sizeof(*xcfdata));
return((image->columns+7)/8);
TIFFScanlineSize(tiff),(ssize_t) (image->columns*samples_per_pixel*
pow(2.0,ceil(log(bits_per_sample)/log(2.0)))*sizeof(uint32))));
if ((size_t) (p-comment+1) >= extent)
extent<<=1;
comment=(char *) ResizeQuantumMemory(comment,extent+MagickPathExtent,
sizeof(*comment));
if (comment == (char *) NULL)
break;
p=comment+strlen(comment);
if (comment == (char *) NULL)
if (c != EOF)
char
*comment;
(void) SetImageProperty(image,"comment",comment,exception);
comment=DestroyString(comment);
size_t
extent;
comment=AcquireString(GetImageProperty(image,"comment",exception));
p=comment+strlen(comment);
extent=strlen(comment)+MagickPathExtent;
c=PNMComment(image,exception);
c=PNMComment(image,exception);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
pixel=ScaleAnyToQuantum(PNMInteger(image,10,exception),max_value);
ThrowReaderException(CorruptImageError,"NegativeOrZeroImageSize");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
pixel=ScaleAnyToQuantum(PNMInteger(image,10,exception),max_value);
ThrowReaderException(CorruptImageError,"UnableToReadImageData");
image->columns=(size_t) PNMInteger(image,10,exception);
image->rows=(size_t) PNMInteger(image,10,exception);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
max_value=(QuantumAny) PNMInteger(image,10,exception);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
SetPixelGray(image,PNMInteger(image,2,exception) == 0 ?
QuantumRange : 0,q);
c=PNMComment(image,exception);
pixel=ScaleAnyToQuantum(PNMInteger(image,10,exception),max_value);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
intensity=ScaleAnyToQuantum(PNMInteger(image,10,exception),
max_value);
size_t offset;
if (i >= strlen(name))
if (i >= strlen(name))
(void) QueryColorCompliance(colorname,AllCompliance,color,exception);
else
scale=(double) (QuantumRange/100.0);
if ((flags & RhoValue) != 0)
color->red=(double) ClampToQuantum((MagickRealType) (scale*
geometry_info.rho));
color->green=(double) ClampToQuantum((MagickRealType) (scale*
geometry_info.sigma));
color->blue=(double) ClampToQuantum((MagickRealType) (scale*
geometry_info.xi));
color->alpha=(double) OpaqueAlpha;
if ((flags & PsiValue) != 0)
{
if (color->colorspace == CMYKColorspace)
color->black=(double) ClampToQuantum((MagickRealType) (
scale*geometry_info.psi));
else
if (color->alpha_trait != UndefinedPixelTrait)
geometry_info.psi);
}
if (((flags & ChiValue) != 0) &&
if (color->colorspace == LabColorspace)
if ((flags & SigmaValue) != 0)
color->green=(MagickRealType) ClampToQuantum((MagickRealType)
(scale*geometry_info.sigma+(QuantumRange+1)/2.0));
if ((flags & XiValue) != 0)
color->blue=(MagickRealType) ClampToQuantum((MagickRealType)
(scale*geometry_info.xi+(QuantumRange+1)/2.0));
if (LocaleCompare(colorspace,"gray") == 0)
{
color->green=color->red;
color->blue=color->red;
if (((flags & SigmaValue) != 0) &&
(color->alpha_trait != UndefinedPixelTrait))
geometry_info.sigma);
if ((icc_color == MagickFalse) &&
(color->colorspace == LinearGRAYColorspace))
{
color->colorspace=GRAYColorspace;
color->depth=8;
}
}
if ((LocaleCompare(colorspace,"HCL") == 0) ||
(LocaleCompare(colorspace,"HSB") == 0) ||
(LocaleCompare(colorspace,"HSL") == 0) ||
(LocaleCompare(colorspace,"HWB") == 0))
{
if (LocaleCompare(colorspace,"HCL") == 0)
color->colorspace=HCLColorspace;
if (LocaleCompare(colorspace,"HSB") == 0)
color->colorspace=HSBColorspace;
else
if (LocaleCompare(colorspace,"HSL") == 0)
color->colorspace=HSLColorspace;
else
if (LocaleCompare(colorspace,"HWB") == 0)
color->colorspace=HWBColorspace;
scale=1.0/255.0;
if ((flags & PercentValue) != 0)
scale=1.0/100.0;
geometry_info.sigma*=scale;
geometry_info.xi*=scale;
if (LocaleCompare(colorspace,"HCL") == 0)
ConvertHCLToRGB(fmod(fmod(geometry_info.rho,360.0)+360.0,
if (LocaleCompare(colorspace,"HSB") == 0)
ConvertHSBToRGB(fmod(fmod(geometry_info.rho,360.0)+360.0,
else
if (LocaleCompare(colorspace,"HSL") == 0)
ConvertHSLToRGB(fmod(fmod(geometry_info.rho,360.0)+360.0,
else
ConvertHWBToRGB(fmod(fmod(geometry_info.rho,360.0)+360.0,
color->colorspace=sRGBColorspace;
}
(void) QueryColorCompliance(token,AllCompliance,&stop_color,
(void) QueryColorCompliance(token,AllCompliance,
(void) QueryColorCompliance(token,AllCompliance,
gradient->angle))))/gradient->radii.x;
gradient->angle))))/gradient->radii.y;
q+=GetPixelChannels(image);
}
{
sixel_pixels[y*image->columns+x]= ((ssize_t) GetPixelIndex(image,q));
size;
size=count*quantum;
if ((count == 0) || (quantum != (size/count)))
{
errno=ENOMEM;
return((void *) NULL);
}
return(AcquireMagickMemory(size));
return((MemoryInfo *) NULL);
memory_info->blob=AcquireMagickMemory(length);
RelinquishMagickResource(DiskResource,length);
if (AcquireMagickResource(MemoryResource,length) != MagickFalse)
memory_info->blob=AcquireAlignedMemory(1,length);
memory_info->blob=MapBlob(file,IOMode,0,length);
if (AcquireMagickResource(DiskResource,length) != MagickFalse)
RelinquishMagickResource(MemoryResource,length);
if (AcquireMagickResource(MapResource,length) != MagickFalse)
RelinquishMagickResource(MapResource,length);
if ((lseek(file,length-1,SEEK_SET) == (length-1)) &&
pixel_info_length=image->columns*image->rows*MagickMax(number_planes,4);
if ((number_pixels*number_planes) != (size_t) (number_pixels*number_planes))
bmp_info.image_size=(unsigned int) (bytes_per_line*image->rows);
iris_info.bytes_per_pixel,MAGICKCORE_QUANTUM_DEPTH);
pixels=(unsigned char *) AcquireQuantumMemory(image->columns,4*
CheckNumberCompactPixels;
if ((size_t) (p-sixel_buffer+MagickPathExtent) < length)
MagickPathExtent,sizeof(*sixel_buffer));
ThrowDCMException(CorruptImageError,"ImproperImageHeader");
image_ratio=(double) former_width/former_height;
step=MagickPI/(4*(MagickPI/delta/2+0.5));
step=MagickPI/(4*(MagickPI/delta/2+0.5));
sans=NULL;
*sans;
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
device->platform_name=AcquireQuantumMemory(length,
temp=(char*) AcquireMagickMemory(strlen(path)+1);
log=(char*)AcquireMagickMemory(log_size);
pow(2.0,ceil(log(bits_per_sample)/log(2.0))))));
chunk[i]=(unsigned char) ReadBlobByte(image);
if (image->alpha_trait != UndefinedPixelTrait)
number_planes++;
number_pixels=(MagickSizeType) image->columns*image->rows;
while (EOFBlob(image) != EOF)
"baseProfile=\"full\" width=\"%g\" height=\"%g\">\n",bounds.x2-bounds.x1,
bounds.y2-bounds.y1);
(void) CloseBlob(images);
max_packets=(size_t) (number_pixels*viff_info.number_data_bands);
max_packets=((image->columns+7UL) >> 3UL)*image->rows;
if (length > compress_extent)
bzip_info.avail_in=(unsigned int) ReadBlob(image,length,
(unsigned char *) bzip_info.next_in);
lzma_info.avail_in=(unsigned int) ReadBlob(image,length,
(unsigned char *) lzma_info.next_in);
if (length > compress_extent)
zip_info.avail_in=(unsigned int) ReadBlob(image,length,
zip_info.next_in);
if (length > compress_extent)
options=DestroyString(options);
ThrowReaderException(CorruptImageError,
"InsufficientImageDataInFile");
}
image->colormap[i].green=ScaleShortToQuantum(pixel);
AcquireString(keyword+8));
profile=BlobToStringInfo((const void *) NULL,length);
if (profile == (StringInfo *) NULL)
{
options=DestroyString(options);
profiles=DestroyLinkedList(profiles,
RelinquishMagickMemory);
ThrowReaderException(ResourceLimitError,
"MemoryAllocationFailed");
}
if (EOFBlob(image) == MagickFalse)
(void) SetImageProfile(image,keyword+8,profile,
exception);
profile=DestroyStringInfo(profile);
if (LocaleCompare(keyword,"profile") == 0)
break;
profile=GetImageProfile(image,name);
if (profile != (StringInfo *) NULL)
image->colormap[i].green=ScaleCharToQuantum(pixel);
if ((packet_size*image->colors) > GetBlobSize(image))
p=GetStringInfoDatum(profile);
image->colormap[i].red=ScaleShortToQuantum(pixel);
count=ReadBlob(image,GetStringInfoLength(profile),p);
image->colormap[i].blue=ScaleShortToQuantum(pixel);
image->colormap[i].red=ScaleLongToQuantum(pixel);
image->colormap[i].green=ScaleLongToQuantum(pixel);
image->colormap[i].blue=ScaleLongToQuantum(pixel);
image->colormap[i].blue=ScaleCharToQuantum(pixel);
const StringInfo
register unsigned char
*p;
image->colormap[i].red=ScaleCharToQuantum(pixel);
Read image profiles.
if ((LocaleNCompare(keyword,"profile:",8) == 0) ||
(LocaleNCompare(keyword,"profile-",8) == 0))
size_t
length;
StringInfo
*profile;
length=StringToLong(options);
if ((MagickSizeType) length > GetBlobSize(image))
{
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,
RelinquishMagickMemory);
pixel=ScaleQuantumToShort(image->colormap[i].blue);
(void) WriteBlobByte(image,value[i]);
pixel=(unsigned char) ScaleQuantumToChar(image->colormap[i].red);
pixel=(unsigned char) ScaleQuantumToChar(
image->colormap[i].green);
pixel=(unsigned char) ScaleQuantumToChar(image->colormap[i].blue);
pixel=ScaleQuantumToLong(image->colormap[i].red);
pixel=ScaleQuantumToLong(image->colormap[i].green);
pixel=ScaleQuantumToLong(image->colormap[i].blue);
Generic profile.
pixel=ScaleQuantumToShort(image->colormap[i].green);
pixel=ScaleQuantumToShort(image->colormap[i].red);
(void) FormatLocaleString(buffer,MagickPathExtent,
"profile:%s=%.20g\n",name,(double)
GetStringInfoLength(profile));
Write image profiles.
if ((LocaleNCompare(keyword,"profile:",8) == 0) ||
(LocaleNCompare(keyword,"profile-",8) == 0))
size_t
length;
StringInfo
*profile;
length=(size_t) StringToLong(options);
if ((MagickSizeType) length > GetBlobSize(image))
{
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,
RelinquishMagickMemory);
options=DestroyString(options);
ThrowReaderException(CorruptImageError,
"InsufficientImageDataInFile");
}
profile=GetImageProfile(image,name);
AcquireString(keyword+8));
profile=BlobToStringInfo((const void *) NULL,length);
if (profile == (StringInfo *) NULL)
{
options=DestroyString(options);
profiles=DestroyLinkedList(profiles,
RelinquishMagickMemory);
ThrowReaderException(ResourceLimitError,
"MemoryAllocationFailed");
}
if (EOFBlob(image) == MagickFalse)
(void) SetImageProfile(image,keyword+8,profile,
exception);
profile=DestroyStringInfo(profile);
if (LocaleCompare(keyword,"profile") == 0) 
break;
if (profile != (StringInfo *) NULL)
register unsigned char
*p;
p=GetStringInfoDatum(profile);
count=ReadBlob(image,GetStringInfoLength(profile),p);
(void) count;
const StringInfo
if (image->profiles != (void *) NULL)
Generic profile.
Write image profiles.
name=GetNextImageProfile(image);
while (name != (const char *) NULL)
"profile:%s=%.20g\n",name,(double)
GetStringInfoLength(profile));
image->columns=image->rows=1;
image->columns=image->rows=1;
SetImageColorspace(image,GRAYColorspace,exception);
msl_info.group_info=(MSLGroupInfo *) RelinquishMagickMemory(
msl_info.group_info);
*image=(*msl_info.image);
MagickBooleanType
status;
status=ProcessMSLScript(image_info,&msl_image,exception);
if (msl_image != (Image *) NULL)
msl_image=DestroyImage(msl_image);
return(status);
return((Image *) NULL);
"MemoryAllocationFailed");
MagickFalse)
ThrowWriterException(ResourceLimitError,
alpha=1.0/alpha;
if ((image != image2) && (image2 != (Image *) NULL))
image2=DestroyImage(image2);
return (image);
if (image==NULL)
else
ThrowBinaryException(ResourceLimitError,"MemoryAllocationFailed",
image->filename);
size_t
length;
(void) ReadBlobByte(image);
if (TIFFGetField(tiff,TIFFTAG_DOCUMENTNAME,&text) == 1)
if (TIFFGetField(tiff,TIFFTAG_MAKE,&text) == 1)
if (TIFFGetField(tiff,TIFFTAG_MODEL,&text) == 1)
if (TIFFGetField(tiff,TIFFTAG_PAGENAME,&text) == 1)
if (TIFFGetField(tiff,37706,&length,&tietz) == 1)
if (TIFFGetField(tiff,TIFFTAG_ARTIST,&text) == 1)
if (TIFFGetField(tiff,TIFFTAG_DATETIME,&text) == 1)
(void) ReadBlobString(image,scale);
quantum_scale=StringToDouble(scale,(char **) NULL);
bits_per_pixel,
comment[length-1]='\0';
(void) SetImageProperty(image,"comment",comment,exception);
count=ReadBlob(image,tga_info.id_length,(unsigned char *) comment);
comment[tga_info.id_length]='\0';
(void) SetImageProperty(image,"comment",comment,exception);
comment=DestroyString(comment);
if( UnpackWPG2Raster(image,bpp,exception) < 0)
goto DecompressionFailed;
if(!image_info->ping)
for (p+=strspn(p,whitelist); p != q; p+=strspn(p,whitelist))
*p='_';
break;
}
case 'F':
{
const char
*q;
register char
*p;
static char
whitelist[] =
"^-ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
"+&@#/%?=~_|!:,.;()";
/*
Magick filename (sanitized) - filename given incl. coder & read mods.
*/
WarnNoImageReturn("\"%%%c\"",letter);
(void) CopyMagickString(value,image->magick_filename,MagickPathExtent);
p=value;
q=value+strlen(value);
sanitize_command=SanitizeDelegateCommand(command);
static char *SanitizeDelegateCommand(const char *command)
{
char
*sanitize_command;
const char
*q;
register char
*p;
static char
whitelist[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_- "
".@&;<>()|/\\\'\":%=~`";
sanitize_command=AcquireString(command);
p=sanitize_command;
q=sanitize_command+strlen(sanitize_command);
for (p+=strspn(p,whitelist); p != q; p+=strspn(p,whitelist))
*p='_';
return(sanitize_command);
}
image->blob->file_info.file=(FILE *) popen_utf8(filename+1, fileMode);
fileMode[MagickPathExtent];
TIFFScanlineSize(tiff),(ssize_t) (image->columns*samples_per_pixel*
pow(2.0,ceil(log(bits_per_sample)/log(2.0)))*sizeof(uint32))));
*q=0.0;
cache_info->number_threads);
cache_info->nexus_info=DestroyPixelCacheNexus(cache_info->nexus_info,
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxReturn(FxGetSymbol(fx_info,channel,x,y,expression,exception));
if ((command_info->mnemonic == (const char *) NULL) &&
if ((id == 0x000003ed) && (cnt < (ssize_t) (length-12)))
if( UnpackWPG2Raster(image,bpp,exception) < 0)
goto DecompressionFailed;
(void) FormatLocaleFile(stderr,
"\nUnsupported WPG token XOR, please report!");
(2UL*(number_vertices+1UL)+1UL),sizeof(*dash_polygon));
pixel.red=((aggregate.red+total_weight/2.0)/total_weight);
pixel.green=((aggregate.green+total_weight/2.0)/total_weight);
pixel.blue=((aggregate.blue+total_weight/2.0)/total_weight);
pixel.black=((aggregate.black+total_weight/2.0)/total_weight);
pixel.alpha=((aggregate.alpha+total_weight/2.0)/total_weight);
MagickError(ResourceLimitError,"too many exceptions",
"exception processing is suspended");
if (i < MaxExceptions)
{
if ((p->severity >= WarningException) && (p->severity < ErrorException))
MagickWarning(p->severity,p->reason,p->description);
if ((p->severity >= ErrorException) &&
(p->severity < FatalErrorException))
MagickError(p->severity,p->reason,p->description);
}
else
if (i == MaxExceptions)
&extent,exception);
(unsigned int) pixmap.bits_per_pixel,&extent,exception);
ThrowPICTException(ResourceLimitError,"MemoryAllocationFailed");
(void) ThrowMagickException(exception,GetMagickModule(),
CorruptImageError,"UnableToUncompressImage","`%s'",image->filename);
(void) ThrowMagickException(exception,GetMagickModule(),
size_t bytes_per_line,const unsigned int bits_per_pixel,size_t *extent,
ExceptionInfo *exception)
//(void) ThrowMagickException(exception,GetMagickModule(),
//  CorruptImageError,"UnableToUncompressImage","`%s'",image->filename);
(void) ThrowMagickException(exception,GetMagickModule(),
CorruptImageError,"UnableToUncompressImage","`%s'",
image->filename);
ResourceLimitError,"ListLengthExceedsLimit","`%s'",image->filename);
length=GetImageListLength(image);
if (AcquireMagickResource(ListLengthResource,length) == MagickFalse)
{
(void) ThrowMagickException(exception,GetMagickModule(),
length;
return((Cache) NULL);
}
MagickSizeType
*x=(ssize_t) ceil(StringToDouble(p,&p)-0.5);
*width=(size_t) floor(StringToDouble(p,&p)+0.5);
*y=(ssize_t) ceil(StringToDouble(p,&p)-0.5);
*height=(size_t) floor(StringToDouble(p,&p)+0.5);
else
if (image->depth <= 16)
extent=2*image->columns;
else
extent=4*image->columns;
quantum_info=AcquireQuantumInfo(image_info,image);
extent=3*(image->depth <= 8 ? 1 : 2)*image->columns;
if (image->depth <= 8)
extent=image->columns;
if ((total_length <= maximum_length) && ((n & 0x01) == 0) && (j > 1))
length=scale*(draw_info->dash_pattern[n]+0.5);
angle.y=DegreesToRadians(y);
(void) memset(&info,0,sizeof(info));
(void) SetImageProfile(image,"icc",profile,exception);
for (i=GetStringInfoLength(profile)-1; c != EOF; i++)
SetStringInfoLength(profile,i+1);
if (length > GetBlobSize(image))
SetStringInfoLength(profile,i);
(void) SetImageProfile(image,"xmp",profile,exception);
(void) SetImageProfile(image,"8bim",profile,exception);
*page_geometry;
page_geometry=GetPageGeometry(option);
flags=ParseMetaGeometry(page_geometry,&page.x,&page.y,&page.width,
&page.height);
page_geometry=DestroyString(page_geometry);
*/
ResetLinkedListIterator(profiles);
name=(const char *) GetNextValueInLinkedList(profiles);
while (name != (const char *) NULL)
{
profile=GetImageProfile(image,name);
if (profile != (StringInfo *) NULL)
{
register unsigned char
*p;
p=GetStringInfoDatum(profile);
count=ReadBlob(image,GetStringInfoLength(profile),p);
(void) count;
}
name=(const char *) GetNextValueInLinkedList(profiles);
}
profiles=DestroyLinkedList(profiles,RelinquishMagickMemory);
}
profiles=(LinkedListInfo *) NULL;
if (LocaleNCompare(ICCProfile,command,strlen(ICCProfile)) == 0)
{
unsigned char
*datum;
/*
Read ICC profile.
*/
for (i=0; (c=ProfileInteger(image,hex_digits)) != EOF; i++)
{
if (i >= (ssize_t) GetStringInfoLength(profile))
datum[i]=(unsigned char) c;
}
if (profiles == (LinkedListInfo *) NULL)
profiles=NewLinkedList(0);
(void) AppendValueToLinkedList(profiles,AcquireString("icc"));
profile=DestroyStringInfo(profile);
continue;
}
if (LocaleNCompare(PhotoshopProfile,command,strlen(PhotoshopProfile)) == 0)
{
unsigned char
*q;
/*
Read Photoshop profile.
*/
count=(ssize_t) sscanf(command,PhotoshopProfile " %lu",&extent);
if (count != 1)
continue;
length=extent;
if ((MagickSizeType) length > GetBlobSize(image))
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
profile=BlobToStringInfo((const void *) NULL,length);
if (profile != (StringInfo *) NULL)
{
q=GetStringInfoDatum(profile);
for (i=0; i < (ssize_t) length; i++)
*q++=(unsigned char) ProfileInteger(image,hex_digits);
if (profiles == (LinkedListInfo *) NULL)
profiles=NewLinkedList(0);
(void) AppendValueToLinkedList(profiles,AcquireString("8bim"));
profile=DestroyStringInfo(profile);
}
continue;
}
if (LocaleNCompare(BeginXMPPacket,command,strlen(BeginXMPPacket)) == 0)
{
/*
Read XMP profile.
*/
p=command;
profile=StringToStringInfo(command);
for (i=(ssize_t) GetStringInfoLength(profile)-1; c != EOF; i++)
{
SetStringInfoLength(profile,(size_t) i+1);
c=ReadBlobByte(image);
if (c == EOF)
continue;
GetStringInfoDatum(profile)[i]=(unsigned char) c;
*p++=(char) c;
if ((strchr("\n\r%",c) == (char *) NULL) &&
((size_t) (p-command) < (MagickPathExtent-1)))
continue;
*p='\0';
p=command;
if (LocaleNCompare(EndXMPPacket,command,strlen(EndXMPPacket)) == 0)
break;
}
SetStringInfoLength(profile,(size_t) i);
if (EOFBlob(image) == MagickFalse)
{
if (profiles == (LinkedListInfo *) NULL)
profiles=NewLinkedList(0);
(void) AppendValueToLinkedList(profiles,AcquireString("xmp"));
}
profile=DestroyStringInfo(profile);
continue;
}
priority=i;
{
char
*page_geometry;
page_geometry=GetPageGeometry(option);
flags=ParseMetaGeometry(page_geometry,&page.x,&page.y,&page.width,
&page.height);
if (flags == NoValue)
{
(void) ThrowMagickException(exception,GetMagickModule(),OptionError,
"InvalidGeometry","`%s'",option);
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,RelinquishMagickMemory);
image=DestroyImage(image);
return((Image *) NULL);
}
page.width=(size_t) ceil((double) (page.width*image->resolution.x/delta.x)
-0.5);
page.height=(size_t) ceil((double) (page.height*image->resolution.y/
delta.y) -0.5);
page_geometry=DestroyString(page_geometry);
fitPage=MagickTrue;
}
(void) CloseBlob(image);
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,RelinquishMagickMemory);
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,RelinquishMagickMemory);
LinkedListInfo
*profiles;
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,RelinquishMagickMemory);
if (profiles != (LinkedListInfo *) NULL)
{
const char
*name;
const StringInfo
*profile;
/*
Read image profiles.
if ((fabs(stop.x) < DrawEpsilon) && (fabs(stop.y) < DrawEpsilon))
Magic2 = lum + sat - ((lum * sat) + (HLSMAX / 2)) / HLSMAX;
Magic2 = (lum * (HLSMAX + sat) + (HLSMAX / 2)) / HLSMAX;
offset=SeekBlob(image,-((MagickOffsetType)
bzip_info.avail_in),SEEK_CUR);
if ((count > 3) && (*(p+4) == 0))
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
TellBlob(image)+8,   /* skip PS header in the wpg */
(ssize_t) Rec.RecordLength-8,exception);
TellBlob(image)+i,    /*skip PS header in the wpg2*/
if(Rec2.RecordLength > (unsigned int) i)
if(Rec.RecordLength>0x3C)
image=ExtractPostscript(image,image_info,
TellBlob(image)+0x3C,   /* skip PS l2 header in the wpg */
(ssize_t) Rec.RecordLength-0x3C,exception);
(ssize_t) (Rec2.RecordLength-i-2),exception);
image=ExtractPostscript(image,image_info,
if(Rec.RecordLength > 8)
image=ExtractPostscript(image,image_info,
pixel=QuantumRange*gamma*(Sa*Da-Sa*Da*MagickMin(1.0,(1.0-Dca/Da)*Sa/
Sca)+Sca*(1.0-Da)+Dca*(1.0-Sa));
if ((image->alpha_trait != UndefinedPixelTrait) && \
n = n * 10 + (*p - '0');
(2UL*(number_vertices+2UL)+1UL),sizeof(*dash_polygon));
image->alpha_trait=tile_image->alpha_trait;
SetImageAlphaChannel(image,TransparentAlphaChannel,exception);
jng_image=DestroyImage(jng_image);
q=ParseXPMColor(p+width,MagickTrue);
(void) ((ReadBlobLSBShort(image) << 16) | ReadBlobLSBShort(image));
ThrowWriterException(DelegateError,"UnableToEncodeImageFile");
if ((fabs(stop.x) < DrawEpsilon) && (fabs(stop.y) < DrawEpsilon))
if ((fabs(stop.x) < DrawEpsilon) && (fabs(stop.y) < DrawEpsilon))
if ((LocaleNCompare(token,"url(",4) == 0) && (strlen(token) > 4))
ThrowReaderException(TypeError,"UnableToGetTypeMetrics");
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
number_points=6553;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
status=MagickFalse;
sun_pixels=(unsigned char *) AcquireQuantumMemory(pixels_length,
p=PushLongPixel(quantum_info->endian,p,&pixel);
*q++=(uint32_t) (image->alpha_trait != UndefinedPixelTrait ?
tiff_pixels=(unsigned char *) AcquireMagickMemory(TIFFScanlineSize(tiff)+
sizeof(uint32));
ThrowBinaryException(ResourceLimitError,"InvalidLength",
image->filename);
image->filename);
ThrowBinaryException(CorruptImageError,"UnexpectedEndOfFile",
ResourceLimitError,"MemoryAllocationFailed","`%s'",
image->filename);
compact_pixels=AcquireCompactPixels(image,exception);
quantum_info=AcquireQuantumInfo(image_info,image);
ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
mng_info=MngInfoFreeStruct(mng_info);
goto MATLAB_KO;    /* unsupported endian */
if (strncmp(MATLAB_HDR.identific, "MATLAB", 6))
length=GetImageListLength(image);
if (AcquireMagickResource(ListLengthResource,length) == MagickFalse)
ThrowBinaryException(ImageError,"ListLengthExceedsLimit",image->filename);
(2UL*(number_vertices+3UL)+3UL),sizeof(*dash_polygon));
if (depth > MagickMaxRecursionDepth)
comment=DestroyString(comment);
p+=GetPixelChannels(image);
(void) SetImageType(image,PaletteType,exception);
i=(ssize_t) image->columns % 4;
depth=0;
*alpha=FxEvaluateSubexpression(fx_info,channel,x,y,fx_info->expression,&depth,
size_t
depth;
&depth,&beta,exception);
&depth,&beta,exception);
&depth,&beta,exception);
depth=0;
depth,
FxResult(0.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult((alpha/(*beta*(alpha-1.0)+1.0)));
FxResult(MagickEpsilon);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(erf(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(exp(alpha));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(2.7182818284590452354);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(floor(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
const char *expression,size_t *depth,double *beta,ExceptionInfo *exception)
FxResult(gamma);
#define FxResult(x) \
{ \
subexpression=DestroyString(subexpression); \
return(x); \
}
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
*subexpression;
FxResult((double) gcd);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(alpha > *beta ? alpha : *beta);
FxResult(floor(alpha));
subexpression=AcquireString((const char *) NULL);
if (*depth > MagickMaxRecursionDepth)
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(0.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(0.0);
FxResult(0.0);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(floor(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,depth,
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(*beta);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
beta,exception);
FxResult(*beta == 0.0 ? 1.0 : 0.0);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
*beta=pow(alpha,FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,
beta,exception));
FxResult(*beta);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha*(*beta));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+2,depth,
beta,exception);
FxResult(j0(alpha));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult((double) !!IsNaN(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+2,depth,
FxResult(0.0);
FxResult(j1(alpha));
FxResult(alpha/(*beta));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(1.0);
FxResult(gamma);
FxResult(0.0);
FxResult(fmod(alpha,*beta));
beta,exception);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha+(*beta));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+2,depth,
beta,exception);
FxResult(log(alpha));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha-(*beta));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+6,depth,
beta,exception);
FxResult(log10(alpha)/log10(2.0));
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(log10(alpha));
FxResult(0.0);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(*beta);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(QuantumRange);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(0.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(*beta);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha < *beta ? 1.0 : 0.0);
beta,exception);
FxResult(alpha < *beta ? alpha : *beta);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha <= *beta ? 1.0 : 0.0);
beta,exception);
FxResult(gamma);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha > *beta ? 1.0 : 0.0);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha >= *beta ? 1.0 : 0.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
FxResult(fabs(alpha-(*beta)) < MagickEpsilon ? 1.0 : 0.0);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(fabs(alpha-(*beta)) >= MagickEpsilon ? 1.0 : 0.0);
FxResult(1.0);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(*beta);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(MagickPI);
FxResult(*beta);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(pow(alpha,*beta));
FxResult((double) (alpha < MagickEpsilon));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(*beta);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth,beta,
FxResult(*beta);
FxResult(QuantumRange);
FxResult(QuantumScale);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(*beta);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth,beta,
FxResult(*beta);
FxResult(alpha);
beta,exception);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(floor(alpha+0.5));
FxResult(0.0);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,p,depth,beta,
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,q,depth,beta,
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(gamma);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
FxResult(alpha < 0.0 ? -1.0 : 1.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(1.0);
FxResult(gamma);
FxResult(0.0);
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
beta,exception);
FxResult(sinh(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
FxResult(*beta);
beta,exception);
FxResult(sin(alpha));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(alpha);
beta,exception);
FxResult(sqrt(alpha));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
*beta=FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,beta,
FxResult(*beta);
beta,exception);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
gamma=alpha*FxEvaluateSubexpression(fx_info,channel,x,y,++p,depth,
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(gamma);
FxResult(alpha);
(*depth)++;
if (*depth >= FxMaxParenthesisDepth)
beta,exception);
FxResult(tanh(alpha));
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,subexpression,depth,
beta,exception);
(*depth)--;
FxResult(gamma);
FxResult(0.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+6,depth,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,expression+1,depth,beta,
FxResult(1.0*gamma);
FxResult(ceil(alpha));
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,expression+1,depth,beta,
FxResult(-1.0*gamma);
FxResult((1.0/(1.0+exp(-alpha))));
FxResult(MagickPHI);
gamma=FxEvaluateSubexpression(fx_info,channel,x,y,expression+1,depth,beta,
FxResult((double) (~(size_t) (gamma+0.5)));
FxResult(tan(alpha));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(fabs(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(acosh(alpha));
depth,beta,exception);
FxResult(*beta);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(acos(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(1.0);
FxResult(gamma*gamma);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(asinh(alpha));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(asin(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(((ssize_t) alpha) & 0x01 ? -1.0 : 1.0);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(atan2(alpha,*beta));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(atanh(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(atan(alpha));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(ceil(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(0.0);
FxResult(1.0);
FxResult(alpha);
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+4,depth,
beta,exception);
FxResult(cosh(alpha));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
FxResult(cos(alpha));
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
FxResult(hypot(alpha,*beta));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+5,depth,
beta,exception);
FxResult(FxGetSymbol(fx_info,channel,x,y,expression,exception));
alpha=FxEvaluateSubexpression(fx_info,channel,x,y,expression+3,depth,
beta,exception);
info.scale=(Quantum *) AcquireQuantumMemory(length,sizeof(*info.scale));
if (map_length >= 32)
while (hue < 0.0)
hue+=1.0;
while (hue > 1.0)
hue-=1.0;
while (hue >= 1.0)
while (hue > 1.0)
hue-=1.0;
while (hue < 0.0)
hue+=1.0;
while (hue < 0.0)
hue+=1.0;
while (hue >= 1.0)
hue-=1.0;
while (hue > 1.0)
hue-=1.0;
while (hue < 0.0)
hue+=1.0;
while (hue > 1.0)
hue-=1.0;
while (hue < 0.0)
hue+=1.0;
while (hue < 0.0)
hue+=1.0;
while (hue >= 1.0)
hue-=1.0;
while (hue >= 1.0)
while (hue < 0.0)
hue+=1.0;
while (hue >= 1.0)
hue-=1.0;
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
DestroyJNG(NULL,&color_image,&color_image_info,NULL,NULL);
exception);
CatchException(exception);
MagickPathExtent);
graphic_context[n]->fill_pattern=ReadImage(pattern_info,
exception);
CatchException(exception);
MagickPathExtent);
graphic_context[n]->stroke_pattern=ReadImage(pattern_info,
if (profile != (StringInfo *) NULL)
{ 
(void) SetImageProfile(image,GetStringInfoName(profile),profile,
exception);
profile=DestroyStringInfo(profile);
}
return((Image *) NULL);
return((Image *) NULL);
return((Image *) NULL);
{
image=DestroyImageList(image);
return((Image *) NULL);
}
if ((image->columns == 0) || (image->rows == 0)) 
return(image->previous == (Image *) NULL ? (Image *) NULL : image);
return((Image *) NULL);
return((Image *) NULL);
return((Image *) NULL);
{
image=DestroyImageList(image);
return((Image *) NULL);
}
return(image);
if ((image->columns == 0) || (image->rows == 0)) 
return(image->previous == (Image *) NULL ? (Image *) NULL : image);
colorspace[MagickPathExtent+1];
ReadPixmap(pixmap);
ReadPixmap(pixmap);
ThrowReaderException(CorruptImageError,
ThrowReaderException(ResourceLimitError,
"MemoryAllocationFailed");
lastrow=(unsigned char *) NULL;
(void) CopyMagickMemory(lastrow,one_row,bytes_per_row);
lastrow=(unsigned char *) AcquireQuantumMemory(bytes_per_row,
sizeof(*lastrow));
/* TODO check whether memory really was acquired? */
(void) WriteBlobByte(image,(unsigned char) ((31*transpix.red)/QuantumRange));
ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
*lastrow,
(void) WriteBlobByte(image,(unsigned char) ((63*transpix.green)/QuantumRange));
(void) WriteBlobByte(image,(unsigned char) ((31*transpix.blue)/QuantumRange));
if ((y == 0) || (lastrow[x + bit] != one_row[x + bit]))
if (lastrow != (unsigned char *) NULL) 
lastrow=(unsigned char *) RelinquishMagickMemory(lastrow);
*q++=(unsigned char) (ScaleQuantumToShort(image->colormap[i].green) & 0xff);;
q=colormap;
unsigned char
*colormap;
packet_size=(size_t) (3UL*depth/8UL);
size_t
packet_size;
if ((colors*image->depth/8) > GetBlobSize(image))
size_t
packet_size;
unsigned char
*colormap;
packet_size=(size_t) (3UL*image->depth/8UL);
(void) ResetMagickMemory(imbuf + (size_t) imsx * y + posision_x, color_index, repeat_count);
(void) CopyMagickString(extent_xml,p,extent*
sizeof(*extent_xml));
p[extent]='\0';
extent_xml=(char *) AcquireQuantumMemory(extent+1,
p=(char *) ResizeQuantumMemory(p,extent+1,sizeof(*p));
pixel.red=(double) GetPixelRed(image,p)+color_vector.red*(1.0-(4.0*
(weight*weight)));
pixel.green=(double) GetPixelGreen(image,p)+color_vector.green*(1.0-(4.0*
(weight*weight)));
pixel.blue=(double) GetPixelBlue(image,p)+color_vector.blue*(1.0-(4.0*
(weight*weight)));
pixel.black=(double) GetPixelBlack(image,p)+color_vector.black*(1.0-(4.0*
(weight*weight)));
pixel.alpha=GetPixelAlpha(image,p);
ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
scanlines=(MagickOffsetType *) RelinquishMagickMemory(scanlines);
(image->number_meta_channels > MaxPixelChannels) ||
(void) CopyMagickString(subexpression,expression+6,MagickPathExtent);
Frames = ReadBlobXXXLong(image2);
if (Frames == 0)
{
if (clone_info != (ImageInfo *) NULL)
clone_info=DestroyImageInfo(clone_info);
if ((image != image2) && (image2 != (Image *) NULL))
image2=DestroyImage(image2);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
}
extent=MagickMax(image->columns,image->rows)*quantum;
for (x=0; x < (ssize_t) number_pixels; x+=4)
if (SeekBlob(image,offset,SEEK_SET) != offset)
ThrowReaderException(CorruptImageError,"NotEnoughPixelData");
/* read in the layer */
layer_ok=ReadOneLayer(image_info,image,&doc_info,
&layer_info[current_layer],current_layer,exception);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
colorname=AcquireString(name+i+1);
return(DestroyImageList(image));
if (ret < 0)
(Rec2.RecordLength-2-2) / 3)
while (*sp == '\0' || *sp == ' ' || *sp == '\n')
while (*sp != '\n')
sp++;
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
color_image=DestroyImage(color_image);
color_image=DestroyImage(color_image);
color_image=DestroyImage(color_image);
alpha_image_info=DestroyImageInfo(alpha_image_info);
points_extent=coordinates;
points_extent+=2*ceil((double) MagickPI*radius)+6*BezierQuantum+360;
(void) ThrowMagickException(exception,GetMagickModule(),DrawError,
"TooManyBezierCoordinates","`%s'",token);
MagickSizeType
coordinates;
coordinates=TracePath(&mvg_info,token,exception);
if (coordinates == 0)
coordinates=primitive_info[j].coordinates;
coordinates=(BezierQuantum*primitive_info[j].coordinates);
coordinates=(MagickSizeType) (2*(ceil(MagickPI*radius))+6*
BezierQuantum+360);
(void) SetImageBackgroundColor(image,exception);
(void) SetImageBackgroundColor(image,exception);
if (layer_info[i].channels < 1)
{
layer_info=DestroyLayerInfo(layer_info,number_layers);
ThrowBinaryException(CorruptImageError,"MissingImageChannel",
image->filename);
}
(void) FormatLocaleString(read_info->filename,MagickPathExtent,"%s.%s",
*read_info->magick='\0';
number_points=65536;
path_info=(PathInfo *) AcquireQuantumMemory((size_t) (2UL*i+4UL),
angle;
pixels=(unsigned char *) AcquireQuantumMemory(packets+256UL,image->rows*
if ((p > (datum+length-count)) || (count > (ssize_t) length))
compact_pixels=(unsigned char *) AcquireQuantumMemory((2*channels*
for (x=0; x < (ssize_t) number_pixels; x+=2)
ldblk,sizeof(*BImgBuff));
if ((id == 0x000003ed) && (PSDQuantum(count) < (ssize_t) (length-12)))
static MagickBooleanType WritePSDImage(const ImageInfo *image_info,Image *image,
ExceptionInfo *exception)
continue;
status=MagickFalse;
if (status == MagickFalse)
continue;
return(MagickFalse);
clip_mask=CloneImage(image,image->columns,image->rows,MagickTrue,exception);
if (clip_mask == (Image *) NULL)
return((Image *) NULL);
return((Image *) NULL);
composite_mask=CloneImage(image,image->columns,image->rows,MagickTrue,
exception);
if (composite_mask == (Image *) NULL)
(void) CopyMagickMemory(q,q+PSDQuantum(count)+12,length-
(PSDQuantum(count)+12)-(q-datum));
SetStringInfoLength(bim_profile,length-(PSDQuantum(count)+12));
number_points=8192+6*BezierQuantum+360;
image=DestroyImage(image);
kernel=(float *) AcquireQuantumMemory(MagickMax(image->rows,image->columns),
if (map_length >= 32)
if (map_length >= 64)
draw_info->direction == RightToLeftDirection ? image->columns-
property=InterpretImageProperties((ImageInfo *) image_info,image,
property=InterpretImageProperties((ImageInfo *) image_info,image,option+8,
property=InterpretImageProperties((ImageInfo *) image_info,image,option,
if (property == (char *) NULL)
(void) SetImageProperty(image,"caption",property,exception);
caption=ConstantString(GetImageProperty(image,"caption",exception));
width=draw_info->pointsize*strlen(caption);
property=InterpretImageProperties((ImageInfo *) image_info,image,
if (property == (char *) NULL)
(void) SetImageProperty(image,"label",property,exception);
label=GetImageProperty(image,"label",exception);
width=draw_info->pointsize*strlen(label);
(void) bits_per_sample;
ConformPixelInfo(distort_image,&distort_image->matte_color,&invalid,
exception);
angle.y=DegreesToRadians(degrees.y);
rotate_image=RotateImage(image,90.0,exception);
if (rotate_image != (Image *) NULL)
*rotate_image;
image=rotate_image;
image=DestroyImage(image);
#define FxMaxSubexpressionDepth  600
memory_info->blob=MapBlob(file,IOMode,0,length);
if (memory_info->blob != NULL)
memory_info->type=MapVirtualMemory;
(void) AcquireMagickResource(MapResource,length);
(void) RelinquishUniqueFileResource(memory_info->filename);
row_bytes=(unsigned short) (image->columns | 0x8000);
row_bytes=(unsigned short) ((4*image->columns) | 0x8000);
row_bytes,
memory_info->blob=MapBlob(file,IOMode,0,length);
if (memory_info->blob != NULL)
memory_info->type=MapVirtualMemory;
(void) AcquireMagickResource(MapResource,length);
(void) RelinquishUniqueFileResource(memory_info->filename);
(void) sscanf(value,"%d +X %d",&height,&width);
image->columns=(size_t) width;
(void) sscanf(value,"%g %g %g %g %g %g %g %g",
&chromaticity[0],&chromaticity[1],&chromaticity[2],
&chromaticity[3],&chromaticity[4],&chromaticity[5],
&white_point[0],&white_point[1]);
image->chromaticity.red_primary.x=chromaticity[0];
image->chromaticity.red_primary.y=chromaticity[1];
image->chromaticity.green_primary.x=chromaticity[2];
image->chromaticity.green_primary.y=chromaticity[3];
image->chromaticity.blue_primary.x=chromaticity[4];
image->chromaticity.blue_primary.y=chromaticity[5];
image->chromaticity.white_point.x=white_point[0],
image->chromaticity.white_point.y=white_point[1];
while ((c != '\n') && (c != '\0'))
image->rows=(size_t) height;
q[i]=ClampToQuantum(pixel);
static inline Quantum ClampPixel(const MagickRealType value)
{
#if !defined(MAGICKCORE_HDRI_SUPPORT)
return((Quantum) value);
#else
if (value < 0.0f)
return(0.0);
if (value >= (MagickRealType) QuantumRange)
return((Quantum) QuantumRange);
return(value);
#endif
}
status=SetImageProgress(image,SaveImageTag,(MagickOffsetType) y,
image->rows);
length,
if (length != 0)
i%=length;
return(DestroyImageList(image));
if (*(draw_info->primitive+1) != '-')
number_points=6613;
return((Image *) NULL);
return((Image *) NULL);
if (bpp == 1)
TIFFGetProfiles(tiff,image,exception);
image=DestroyImage(image);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"UnexpectedEndOfFile");
ThrowReaderException(CorruptImageError,"UnexpectedEndOfFile");
ThrowReaderException(CorruptImageError,"UnexpectedEndOfFile");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
colorspace[MagickPathExtent];
if (jpeg == MagickFalse)
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
if(z!=3) ThrowReaderException(CoderError, "MultidimensionalMatricesAreNotSupported");
ThrowReaderException(CoderError, "MultidimensionalMatricesAreNotSupported");
(sample_traits == UndefinedPixelTrait))
pcx_info.bytes_per_line=(unsigned short) (((size_t) image->columns*
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
image->alpha_trait=BlendPixelTrait;
if (l != 0)
(void) DestroyXMLTreeAttributes(attributes);
(void) SetImageBackgroundColor(image,exception);
if ((image_info->ping != MagickFalse) && (image_info->number_scenes != 0))
if (image->scene >= (image_info->scene+image_info->number_scenes-1))
break;
status=SetImageExtent(image,image->columns,image->rows,exception);
if (status == MagickFalse)
ThrowPCXException(exception->severity,exception->reason);
if (options == (const char *) NULL)
p=(char *) ResizeQuantumMemory(p,extent,sizeof(*p));
{
}
image_count++;
if (image_count != 0)
count+=EncodeImage(image,scanline,bytes_per_line & 0x7FFF,
packed_scanline);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,
ThrowReaderException(CorruptImageError,"NotEnoughPixelData");
ThrowReaderException(CorruptImageError,
"NotEnoughPixelData");
"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,
"NotEnoughPixelData");
ThrowReaderException(ResourceLimitError,
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
"MemoryAllocationFailed");
return(DestroyImageList(image));
return((Image *) NULL);
return((Image *) NULL);
return((Image *) NULL);
return((Image *) NULL);
return((Image *) NULL);
return((Image *) NULL);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,
SeekBlob(image,stream_info->offsets[0]+stream_info->segments[0],
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,
ThrowReaderException(CorruptImageError,
SEEK_SET);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
SeekBlob(image,stream_info->offsets[0]+stream_info->segments[1],
SEEK_SET);
ReadDCMPixels(image,&info,stream_info,MagickFalse,exception);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
image_info->filename);
assert(exception != (ExceptionInfo *) NULL);
logging=LogMagickEvent(CoderEvent,GetMagickModule(),"Enter ReadMNGImage()");
image=AcquireImage(image_info,exception);
mng_info=(MngInfo *) NULL;
status=OpenBlob(image_info,image,ReadBinaryBlobMode,exception);
mng_info=MngInfoFreeStruct(mng_info);
if (status == MagickFalse)
return((Image *) NULL);
first_mng_object=MagickFalse;
skipping_loop=(-1);
/* Allocate a MngInfo structure.  */
mng_info=MngInfoFreeStruct(mng_info);
mng_info=(MngInfo *) AcquireMagickMemory(sizeof(MngInfo));
if (mng_info == (MngInfo *) NULL)
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
/* Initialize members of the MngInfo structure.  */
static Image *ReadMNGImage(const ImageInfo *image_info,
mng_info->image=image;
mng_info=MngInfoFreeStruct(mng_info);
mng_info=MngInfoFreeStruct(mng_info);
image=GetFirstImageInList(image);
MngInfo
*mng_info;
mng_info=MngInfoFreeStruct(mng_info);
mng_info=MngInfoFreeStruct(mng_info);
mng_info=MngInfoFreeStruct(mng_info);
MngInfoFreeStruct(mng_info);
(void) ResetMagickMemory(mng_info,0,sizeof(MngInfo));
mng_info=MngInfoFreeStruct(mng_info);
/* Open image file.  */
mng_info=MngInfoFreeStruct(mng_info);
assert(image_info != (const ImageInfo *) NULL);
(void) LogMagickEvent(TraceEvent,GetMagickModule(),"%s",
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
{ \
ThrowReaderException(severity,tag); \
}
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
p=PushLongPixel(quantum_info->endian,p,&pixel);
geometry_info->rho*=PerceptibleReciprocal(geometry_info->sigma);
if (j >= 256)
if (image->depth > (8*sizeof(MagickSizeType)))
(void) SetImageArtifact(image,name,clip_path);
(void) ParseAtom(image, db, ctx, exception);
(void) ParseAtom(image, db, ctx, exception);
if (id >= (ssize_t) ctx->idsCount) {
image->resolution.x=geometry_info.rho;
image->resolution.y=geometry_info.sigma;
image->resolution.y=image->resolution.x;
channel_mask=SetPixelChannelMask(image,(ChannelType) (1 << channel));
ResetMagickMemory(sun_pixels,0,pixels_length*sizeof(*sun_pixels));
(double) (spotcolor++));
(void) FormatLocaleString(property,MagickPathExtent,"ps:SpotColor-%.20g",
for (depth=1; (GetQuantumRange(depth)+1) < max_value; depth++) ;
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
ThrowReaderException(CorruptImageError,"CorruptImage");
ThrowReaderException(CorruptImageError,"CorruptImage");
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
memcpy(stream,header,12);
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
}
stream=(unsigned char*) RelinquishMagickMemory(stream);
switch (webp_status)
case VP8_STATUS_OUT_OF_MEMORY:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
break;
}
case VP8_STATUS_INVALID_PARAM:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"invalid parameter");
break;
}
case VP8_STATUS_BITSTREAM_ERROR:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"CorruptImage");
break;
}
case VP8_STATUS_UNSUPPORTED_FEATURE:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CoderError,"DataEncodingSchemeIsNotSupported");
break;
}
case VP8_STATUS_SUSPENDED:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"decoder suspended");
break;
}
case VP8_STATUS_USER_ABORT:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"user abort");
break;
}
case VP8_STATUS_NOT_ENOUGH_DATA:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
break;
}
default:
{
stream=(unsigned char*) RelinquishMagickMemory(stream);
ThrowReaderException(CorruptImageError,"CorruptImage");
}
(image->compression == UndefinedCompression) || (image->columns == 0) ||
(image->rows == 0))
if (coordinates > 2097152)
if (id > (ssize_t) ctx->idsCount) {
}
if (id > (ssize_t) ctx->idsCount) {
}
if (id > (ssize_t) ctx->idsCount) {
}
if (DBGetSize(db) < (8*count))
if (assoc_count > MAX_ASSOCS_COUNT) {
if (ignore_depth == 0)
DeleteImageFromList(&image->previous);
image = rotated_image;
samples_per_pixel*pow(2.0,ceil(log(bits_per_sample)/log(2.0))),
if (step < 0.0000001)
step=0.0000001;
if (step < 0.0000001)
step=0.0000001;
angle=degrees-(360.0*floor(degrees/360.0));
angle=degrees-(360.0*floor(degrees/360.0));
(2UL*(number_vertices+6UL)+6UL),sizeof(*dash_polygon));
if ((image_info->number_scenes != 0) && (image_info->scene != 0))
image->rows=height;
/*
status=SetImageExtent(image,image->columns,image->rows,exception);
if (status == MagickFalse)
return(DestroyImageList(image));
Initialize image structure.
*/
image->columns=width;
entry->flags|=CoderDecoderSeekableStreamFlag;
(void) ReadBlobByte(image);
ThrowDCMException(CorruptImageError,"ImproperImageHeader");
return((size_t) floor((angle.y-angle.x)/step+0.5)+2);
(void) SetImageProperty((Image *) image,"icc:manufacturer",info,
exception);
(void) SetImageProperty((Image *) image,"icc:model",info,exception);
(void) SetImageProperty((Image *) image,"icc:copyright",info,exception);
(void) SetImageProperty((Image *) image,"icc:description",info,
exception);
ThrowRLEException(CorruptImageError,"UnexpectedEndOfFile");
(primitive_info[j+2].point.x > 360.0) ||
(primitive_info[j+2].point.y < -360.0) ||
TraceBezier(primitive_info+j,primitive_info[j].coordinates);
PointInfo
offset,
degrees;
alpha=primitive_info[j+1].point.x-primitive_info[j].point.x;
beta=primitive_info[j+1].point.y-primitive_info[j].point.y;
radius=hypot((double) alpha,(double) beta);
offset.x=(double) radius;
offset.y=(double) radius;
degrees.x=0.0;
degrees.y=360.0;
case ArcPrimitive:
{
PointInfo
center,
radii;
if ((primitive_info[j+2].point.x < -360.0) ||
(primitive_info[j+2].point.x > 360.0) ||
(primitive_info[j+2].point.y < -360.0) ||
(primitive_info[j+2].point.y > 360.0))
ThrowPointExpectedException(token,exception);
center.x=0.5*(primitive_info[j+1].point.x+primitive_info[j].point.x);
center.y=0.5*(primitive_info[j+1].point.y+primitive_info[j].point.y);
radii.x=fabs(center.x-primitive_info[j].point.x);
if (number_points != (MagickSizeType) ((size_t) number_points))
ThrowBinaryException(ResourceLimitError,"MemoryAllocationFailed",
image->filename);
(size_t) number_points+4096,sizeof(*primitive_info));
if (primitive_info == (PrimitiveInfo *) NULL)
ThrowBinaryException(ResourceLimitError,"MemoryAllocationFailed",
image->filename);
(primitive_info[j+2].point.y > 360.0))
ThrowPointExpectedException(token,exception);
number_points;
radii.y=fabs(center.y-primitive_info[j].point.y);
(size_t) number_points+4096,sizeof(*primitive_info));
if ((primitive_info == (PrimitiveInfo *) NULL) ||
(number_points != (MagickSizeType) ((size_t) number_points)))
break;
}
primitive_info[j+1].point,primitive_info[j+2].point);
coordinates,
case EllipsePrimitive:
coordinates=TracePath(primitive_info+j,token,exception);
{
if ((primitive_info[j+2].point.x < -360.0) ||
step=MagickPI/8.0;
if ((delta >= 0.0) && (delta < (MagickPI/8.0)))
step=MagickPI/(4.0*(MagickPI*PerceptibleReciprocal(delta)/2.0));
angle.x=DegreesToRadians(arc.x);
y=arc.y;
while (y < arc.x)
y+=360.0;
angle.y=DegreesToRadians(y);
return((size_t) floor((angle.y-angle.x)/step+0.5)+3);
}
static size_t ReckonEllipseCoordinates(const PointInfo radii,
const PointInfo arc)
{
double
delta,
step,
y;
PointInfo
angle;
/*
Ellipses are just short segmented polys.
*/
if ((fabs(radii.x) < DrawEpsilon) || (fabs(radii.y) < DrawEpsilon))
return(0);
delta=2.0*PerceptibleReciprocal(MagickMax(radii.x,radii.y));
if ((offset.x < DrawEpsilon) || (offset.y < DrawEpsilon))
primitive_info->coordinates=0;
p=primitive_info;
static size_t ReckonRoundRectangleCoordinates(const PointInfo start,
const PointInfo end,PointInfo arc)
{
PointInfo
degrees,
offset;
size_t
coordinates;
offset.x=fabs(end.x-start.x);
offset.y=fabs(end.y-start.y);
if ((offset.x < DrawEpsilon) || (offset.y < DrawEpsilon))
return(0);
coordinates=0;
if (arc.x > (0.5*offset.x))
arc.x=0.5*offset.x;
if (arc.y > (0.5*offset.y))
arc.y=0.5*offset.y;
degrees.x=270.0;
degrees.y=360.0;
coordinates+=ReckonEllipseCoordinates(arc,degrees);
degrees.x=0.0;
degrees.y=90.0;
coordinates+=ReckonEllipseCoordinates(arc,degrees);
degrees.x=90.0;
degrees.y=180.0;
coordinates+=ReckonEllipseCoordinates(arc,degrees);
degrees.x=180.0;
degrees.y=270.0;
coordinates+=ReckonEllipseCoordinates(arc,degrees);
return(coordinates+1);
}
TraceEllipse(primitive_info,center,radius,degrees);
TraceArcPath(q,point,end,arc,angle,large_arc,sweep);
if (code < 0)
if (code < 0)
if (number_bins > MagickEpsilon)
if (maximum_length > MaxBezierCoordinates)
break;
ResourceLimitError,"MemoryAllocationFailed","`%s'",token);
if (stream_info->offsets == (ssize_t *) NULL) \
if ((count > (ssize_t) length) || (count < 0))
ThrowReaderException(CoderError,"UnsupportedCellTypeInTheMatrix");
size_t one;
if (LocaleNCompare(filename,"fd:",3) == 0)
(x+1)*sizeof(*clone_info->dash_pattern));
(2UL*x+2UL)*sizeof(*graphic_context[n]->dash_pattern));
AcquireQuantumMemory((size_t) (2UL*x+2UL),
(void) ImportQuantumPixels(image,(CacheView *) NULL,quantum_info,
(void) ImportQuantumPixels(image,(CacheView *) NULL,quantum_info,
(void) ImportQuantumPixels(image,(CacheView *) NULL,quantum_info,
(void) ImportQuantumPixels(image,(CacheView *) NULL,quantum_info,
JPEGSetImageSamplingFactor(&jpeg_info,image,exception);
(void) FormatLocaleString(value,MagickPathExtent,"%.20g",(double)
(void) SetImageProperty(image,"jpeg:colorspace",value,exception);
&y_offset,&red,&green,&blue);
long
count=(ssize_t) sscanf(text,"%ld,%ld: (%lf%*[%,]",&x_offset,
"%ld,%ld: (%lf%*[%,]%lf%*[%,]%lf%*[%,]%lf%*[%,]%lf%*[%,]",
"%ld,%ld: (%lf%*[%,]%lf%*[%,]%lf%*[%,]%lf%*[%,]",&x_offset,
break;       
x_offset=(-1);
y_offset=(-1);
"%ld,%ld: (%lf%*[%,]%lf%*[%,]%lf%*[%,]%lf%*[%,]",
count=(ssize_t) sscanf(text,"%ld,%ld: (%lf%*[%,]%lf%*[%,]",
count=(ssize_t) sscanf(text,
"%ld,%ld: (%lf%*[%,]%lf%*[%,]%lf%*[%,]",&x_offset,
clone_info->clip_mask=(char *) NULL;
(void) DeleteImageArtifact(image,filename);
if ((fabs(maximum_length) < DrawEpsilon) ||
(maximum_length > MaxBezierCoordinates))
#if WEBP_DECODER_ABI_VERSION >= 0x0100
picture.progress_hook=WebPEncodeProgress;
#endif
primitive_info->text=(char *) RelinquishMagickMemory(
primitive_info->text);
if (primitive_info->text != (char *) NULL)
primitive_info=(PrimitiveInfo *) RelinquishMagickMemory(primitive_info);
primitive_info[j].text=AcquireString(token);
while (*p && ((p-chunk) < (ssize_t) length))
image->colormap=(PixelInfo *) AcquireQuantumMemory(image->colors+1,
sizeof(*image->colormap));
if (image->colormap == (PixelInfo *) NULL)
if (dpx.image.number_elements > MaxNumberImageElements)
number_points=8192;
break;
}
if (profiles != (LinkedListInfo *) NULL)
profiles=DestroyLinkedList(profiles,DestroyGIFProfile);
if (profiles != (LinkedListInfo *) NULL)
{
StringInfo
*profile;
/*
Set image profiles.
*/
ResetLinkedListIterator(profiles);
profile=(StringInfo *) GetNextValueInLinkedList(profiles);
while (profile != (StringInfo *) NULL)
{
(void) SetImageProfile(image,GetStringInfoName(profile),profile,
exception);
profile=(StringInfo *) GetNextValueInLinkedList(profiles);
}
if (TIFFGetField(tiff,exif_info[i].tag,&long8y,&sans,&sans) == 1)
&sans,&sans);
if (TIFFGetField(tiff,exif_info[i].tag,&doubley,&sans,&sans) == 1)
if ((TIFFGetField(tiff,exif_info[i].tag,&ascii,&sans,&sans) == 1) &&
if (TIFFGetField(tiff,exif_info[i].tag,&floaty,&sans,&sans) == 1)
if (TIFFGetField(tiff,exif_info[i].tag,&longy,&sans,&sans) == 1)
if (TIFFGetField(tiff,exif_info[i].tag,&shorty,&sans,&sans) == 1)
(void) memset(string_info->datum,0,length+MagickPathExtent);
if ((unsigned int) ((group << 16) | element) == 0xFFFEE0DD)
magic_info=GetMagicInfo(magick,2*MagickPathExtent,exception);
(void) ReadBlob(image, 2*MagickPathExtent, magick);
i=(ssize_t) (j+TracePath(primitive_info+j,token,exception));
{
(void) ThrowMagickException(exception,GetMagickModule(),DrawError,
"attribute not recognized","`%c'",attribute);
primitive_info->coordinates=0;
return(0);
}
if(MATLAB_HDR.DataType!=miMATRIX) continue;  /* skip another objects. */
pixel=(Quantum) ScaleCharToQuantum((unsigned char) ReadBlobByte(image));
wmf_api_destroy(API);
wmf_api_destroy(API);
wmf_api_destroy(API);
wmf_api_destroy(API);
if (API)
wmf_api_destroy(API);
heif_image_release(heif_image);
if ((info.scale != (Quantum *) NULL) &&
if ((info.scale != (Quantum *) NULL) &&
if ((info.scale != (Quantum *) NULL) &&
if ((info.scale != (Quantum *) NULL) &&
image=DestroyImageList(image);
return((Image *) NULL);
}
count=ReadBlob(image,length-16,png+16);
if (count == (ssize_t) length-16)
(void) CopyMagickString(read_info->magick,"PNG",MagickPathExtent);
{
if (count < 0) return -1;
return(-1);
return(-1);
if (c == EOF) return -1;
/*
We read it, but don't use it...
*/
{
if (image->debug != MagickFalse)
(void) LogMagickEvent(CoderEvent,GetMagickModule(),
"        source(%x), dest(%x)",(unsigned int)
blend_source,(unsigned int) blend_dest);
}
points_extent=2*ceil((double) MagickPI*radius)+6*BezierQuantum+360;
layer_info->mask.image=mask;
/*
Write pyramid-encoded TIFF image.
*/
write_info=CloneImageInfo(image_info);
write_info->adjoin=MagickTrue;
(void) CopyMagickString(write_info->magick,"TIFF",MagickPathExtent);
(void) CopyMagickString(images->magick,"TIFF",MagickPathExtent);
images=DestroyImageList(images);
write_info=DestroyImageInfo(write_info);
if (sixel_decode((unsigned char *) sixel_buffer,&sixel_pixels,&image->columns,&image->rows,&sixel_palette,&image->colors) == MagickFalse)
p=(const unsigned char *) ReadBlobStream(image,1,buffer,&count);
string[i]='\0';
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
value=ReadDCMByte(stream_info,image) | (unsigned short)
ThrowReaderException(CorruptImageError,
"InsufficientImageDataInFile");
length=MagickPathExtent;
textlist[i]=(char *) AcquireQuantumMemory((size_t) (q-p)+
MagickPathExtent,sizeof(**textlist));
graymap=(int *) AcquireQuantumMemory((size_t) colors,
redmap=(int *) AcquireQuantumMemory((size_t) colors,
bluemap=(int *) AcquireQuantumMemory((size_t) colors,
greenmap=(int *) AcquireQuantumMemory((size_t) colors,
(void) FormatLocaleString(color_image_info->filename,MagickPathExtent,"%s",
color_image->filename);
ThrowReaderException(CorruptImageError,"CorruptImage");
ThrowReaderException(CorruptImageError,"CorruptImage");
ThrowReaderException(CorruptImageError,
"InsufficientImageDataInFile");
return(DestroyImageList(image));
ThrowReaderException(ResourceLimitError,
alpha_image=DestroyImage(alpha_image);
return(DestroyImageList(image));
"MemoryAllocationFailed");
if (ReadDDSInfo(image, &dds_info) != MagickTrue) {
}
(void) WriteBlob(color_image,length,chunk);
chunk=(unsigned char *) RelinquishMagickMemory(chunk);
if (!DecodeImage(image, pixels, packets * image -> rows))
ThrowReaderException( CorruptImageError, "RLEDecoderError" );
"UnrecognizedImageCompressionType" );
if (LocaleCompare(name,colorname) == 0)
return(MagickFalse);
status=QueryColorCompliance(colorname,AllCompliance,color,exception);
if (c == EOF)
rows_per_strip=image->columns*image->rows;
if (TIFFGetField(tiff,TIFFTAG_ROWSPERSTRIP,&rows_per_strip) == 1)
if ((count == 0) || (LocaleNCompare(type,"8BIM",4) != 0))
ReversePSDString(image,type,count);
if ((count != 0) && ((LocaleNCompare(type,"Lr16",4) == 0) ||
angle=degrees-360.0*(ssize_t) (degrees/360.0);
q=pixels+y*width*GetPixelChannels(image);;
if (*component != '\0')
number_points=16384;
if (loop_iters == 0)
ThrowWriterException(ResourceLimitError,"MemoryAllocationFailed");
clone_image=DestroyImage(clone_image);
length=MagickPathExtent;
if (sun_info.maplength > GetBlobSize(image))
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
if (length >= DBGetSize(db))
ThrowAndReturn("insufficient data");
(void) SetImageProfile(image,"xmp",profile,exception);
(void) fputc(c,file);
GetExceptionMessage(errno));
if (output == (FILE *) NULL) {
return(MagickFalse);
}
for (i=2; i < (ssize_t) (argc-1); i++) {
#if 0
fprintf(stderr, "DEBUG: Concatenate Image: \"%s\"\n", argv[i]);
#endif
pixel_info_length=image->columns*image->rows*number_planes_filled;
number_planes_filled*sizeof(*pixels));
size_t
(void) DecodeImage(sun_data,sun_info.length,sun_pixels,bytes_per_line*
height);
weight=StringToUnsignedLong(token);
GetNextToken(q,&q,extent,keyword);
(void) ReadBlob(image,ldblk,BImgBuff);
bbuf=ReadBlobByte(image);
InsertByte(bbuf);
coordinates+=(6*BezierQuantum)+360;
if (strspn(t,"AaCcQqSsTt") != 0)
if (info.scale != (Quantum *) NULL)
info.scale=(Quantum *) RelinquishMagickMemory(info.scale);
FT_Done_Glyph(glyph.image);
for (coordinates=0; angle.x < angle.y; angle.x+=step)
coordinates++;
return(coordinates+1);
coordinates;
if (step < EllipseEpsilon)
step=EllipseEpsilon;
if (step < EllipseEpsilon)
step=EllipseEpsilon;
value=(unsigned short) ((((unsigned char *) buffer)[0] << 8) |
((unsigned char *) buffer)[1]);
quantum.unsigned_value=(value & 0xffff);
value=(unsigned short) ((buffer[1] << 8) | buffer[0]);
quantum.unsigned_value=(value & 0xffff);
value=(unsigned int) ((buffer[3] << 24) | (buffer[2] << 16) |
(buffer[1] << 8 ) | (buffer[0]));
value=(unsigned int) ((buffer[0] << 24) | (buffer[1] << 16) |
(buffer[2] << 8) | buffer[3]);
if ((LocaleCompare(id,"MagickCache") != 0) ||
if ((LocaleCompare(id,"ImageMagick") != 0) ||
if (((flags & XiNegative) != 0) && (geometry_info->xi == 0.0))
value=(unsigned short) ((((unsigned char *) buffer)[0] << 8) |
((unsigned char *) buffer)[1]);
quantum.unsigned_value=(value & 0xffff);
value=(unsigned short) ((buffer[1] << 8) | buffer[0]);
quantum.unsigned_value=(value & 0xffff);
value=(unsigned int) ((buffer[3] << 24) | (buffer[2] << 16) |
(buffer[1] << 8 ) | (buffer[0]));
quantum.unsigned_value=(value & 0xffffffff);
value=(unsigned int) ((buffer[0] << 24) | (buffer[1] << 16) |
(buffer[2] << 8) | buffer[3]);
quantum.unsigned_value=(value & 0xffffffff);
quantum.unsigned_value=(value & 0xffff);
value=(unsigned int) ((buffer[0] << 24) | (buffer[1] << 16) |
(buffer[2] << 8) | buffer[3]);
return((unsigned int) (value & 0xffffffff));
value=(unsigned int) ((buffer[3] << 24) | (buffer[2] << 16) |
(buffer[1] << 8 ) | (buffer[0]));
return((unsigned int) (value & 0xffffffff));
value=(unsigned short) ((buffer[1] << 8) | buffer[0]);
return((unsigned short) (value & 0xffff));
value=(unsigned short) ((((unsigned char *) buffer)[0] << 8) |
((unsigned char *) buffer)[1]);
return((unsigned short) (value & 0xffff));
quantum.unsigned_value=(value & 0xffffffff);
for ( ; ; draw_info->pointsize*=2.0)
return(value);
return(0);
image->colormap[1].red=(Quantum) 0;
image->colormap[1].green=(Quantum) 0;
image->colormap[1].blue=(Quantum) 0;
value=XBMInteger(image,hex_digits);
*p++=(unsigned char) value;
value,
*p++=(unsigned char) (value >> 8);
value=XBMInteger(image,hex_digits);
*p++=(unsigned char) value;
image->colormap[0].red=QuantumRange;
image->colormap[0].green=QuantumRange;
image->colormap[0].blue=QuantumRange;
return(DestroyImageList(image));
break;
if (cmsGetProfileInfoASCII(icc_profile,cmsInfoDescription,"en","US",
info,MagickPathExtent) != 0)
if (cmsGetProfileInfoASCII(icc_profile,cmsInfoManufacturer,"en","US",
info,MagickPathExtent) != 0)
if (cmsGetProfileInfoASCII(icc_profile,cmsInfoModel,"en","US",info,
MagickPathExtent) != 0)
if (cmsGetProfileInfoASCII(icc_profile,cmsInfoCopyright,"en","US",
info,MagickPathExtent) != 0)
while (GetUTFCode(pattern) == '*')
pattern+=GetUTFOctets(pattern);
image->columns=(size_t) MagickAbsoluteValue(dib_info.width);
image->rows=(size_t) MagickAbsoluteValue(dib_info.height);
subexpression[MagickPathExtent],
gamma=alpha-floor((alpha/(*beta)))*(*beta);
SetImageColorspace(image,GRAYColorspace,exception);
pixel_info_length=image->columns*image->rows*number_planes_filled;
pixel_info=AcquireVirtualMemory(pixel_info_length,sizeof(*pixels));
return(DestroyImageList(image));
else if (exception->exceptions != (void *) NULL)
ClearLinkedList((LinkedListInfo *) exception->exceptions,
DestroyExceptionElement);
if (GetNumberOfElementsInLinkedList(exceptions) > MagickMaxRecursionDepth)
if (GetNumberOfElementsInLinkedList(exceptions) == MagickMaxRecursionDepth)
(void) ThrowMagickException(exception,GetMagickModule(),CorruptImageError,
"InvalidColormapIndex","`%s'",image->filename);
if (c == EOF) return -1;
return 0;
if (c == EOF) return -1;
if (c == EOF) return -1;
return 0;
if (c0 == EOF) return -1;
if (taglen < 0) return -1;
if (c == EOF) return -1;
Ascii85Encode(tile_image,ScaleQuantumToChar(ClampToQuantum(
{
(void) WriteBlob(color_image,length,chunk);
chunk=(unsigned char *) RelinquishMagickMemory(chunk);
}
(void) ReadBlobByte(image);
for ( ; length != 0; length--)
RelinquishMagickMemory(WMF_MAGICK_GetFontData(API)->ps_name);
if (ddata->draw_info != (DrawInfo *) NULL)
{
DestroyDrawInfo(ddata->draw_info);
ddata->draw_info=(DrawInfo *)NULL;
}
colormap_index=(ssize_t *) AcquireQuantumMemory(image->colors,
colormap_index=(ssize_t *) AcquireQuantumMemory(MaxColormapSize,
ThrowReaderException(ResourceLimitError,
quantum_info=DestroyQuantumInfo(quantum_info);
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
quantum_info=DestroyQuantumInfo(quantum_info);
"ImageDepthNotSupported");
ThrowReaderException(CorruptImageError,
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
{
quantum_info=DestroyQuantumInfo(quantum_info);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
}
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
ThrowReaderException(CorruptImageError,
"UnableToReadImageData");
ThrowReaderException(CorruptImageError,"InsufficientImageDataInFile");
{
quantum_info=DestroyQuantumInfo(quantum_info);
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
}
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
quantum_info=DestroyQuantumInfo(quantum_info);
ThrowReaderException(CorruptImageError,
ThrowReaderException(ResourceLimitError,"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"UnableToReadImageData");
ThrowReaderException(CorruptImageError,
ThrowReaderException(ResourceLimitError,
"MemoryAllocationFailed");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
ThrowReaderException(CorruptImageError,"ImproperImageHeader");
quantum_info=DestroyQuantumInfo(quantum_info);
quantum_info=DestroyQuantumInfo(quantum_info);
ThrowReaderException(CorruptImageError,
ThrowReaderException(CorruptImageError,"UnableToReadImageData");
if ((p+length) < q)
while (p < q)
{
for (i=0; i < (ssize_t) length; i++)
if (p[i] != target[i])
break;
if (i == (ssize_t) length)
return((unsigned char *) p);
p++;
}
(jp2_image->comps[i].data == NULL))
length=length*BezierQuantum;
length,
if ((i+length) >= number_points)
length*=5;
length+=2*((size_t) ceil((double) MagickPI*radius))+6*BezierQuantum+360;
if (step < 0.00001)
step=0.00001;
length=(MagickSizeType) ReadBlobByte(image);
break;
rows_per_strip)*sizeof(uint32)));
memcpy(prop->data, propDb.data, prop->size);
image->columns ? (double) image->columns-1 : bounds.x1;
image->rows ? (double) image->rows-1 : bounds.y1;
image->columns ? (double) image->columns-1 : bounds.x2;
image->rows ? (double) image->rows-1 : bounds.y2;
return(MagickEpsilon);
return(erf(alpha));
return(exp(alpha));
return(2.7182818284590452354);
return(floor(alpha));
return(gamma);
#define FxMaxSubexpressionDepth  200
return((double) gcd);
subexpression[MagickPathExtent];
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(alpha < *beta ? alpha : *beta);
return(0.0);
return(hypot(alpha,*beta));
return(0.0);
return(0.0);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(floor(alpha));
return(*beta);
return((double) !!IsNaN(alpha));
return(*beta == 0.0 ? 1.0 : 0.0);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(*beta);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(alpha*(*beta));
return(j0(alpha));
return(j1(alpha));
return(0.0);
return(alpha/(*beta));
return(1.0);
return(gamma);
return(0.0);
return(fmod(alpha,*beta));
return(alpha+(*beta));
return(log(alpha));
return(alpha-(*beta));
return(log10(alpha)/log10(2.0));
return(log10(alpha));
return(0.0);
return(*beta);
return(QuantumRange);
return(0.0);
return(alpha > *beta ? alpha : *beta);
return(*beta);
return(alpha < *beta ? 1.0 : 0.0);
return(alpha <= *beta ? 1.0 : 0.0);
return(gamma);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(alpha > *beta ? 1.0 : 0.0);
return(alpha >= *beta ? 1.0 : 0.0);
return((double) (alpha < MagickEpsilon));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(fabs(alpha-(*beta)) < MagickEpsilon ? 1.0 : 0.0);
return(fabs(alpha-(*beta)) >= MagickEpsilon ? 1.0 : 0.0);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(*beta);
return(MagickPHI);
return(MagickPI);
return(*beta);
return(pow(alpha,*beta));
return(sin(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(*beta);
return(QuantumRange);
return(*beta);
return(QuantumScale);
return(*beta);
return(1.0);
return(*beta);
return(floor(alpha+0.5));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(0.0);
return(sqrt(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(gamma);
return(alpha < 0.0 ? -1.0 : 1.0);
return(1.0);
return(gamma);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(0.0);
return(sinh(alpha));
return(*beta);
return(alpha);
return((1.0/(1.0+exp(-alpha))));
return(*beta);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(gamma);
return(tanh(alpha));
return(tan(alpha));
return(gamma);
return(0.0);
return(1.0*gamma);
return(ceil(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(-1.0*gamma);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return((double) (~(size_t) (gamma+0.5)));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(fabs(alpha));
return(acosh(alpha));
return(*beta);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(acos(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(1.0);
return(gamma*gamma);
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(asinh(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(alpha);
return(asin(alpha));
return(((ssize_t) alpha) & 0x01 ? -1.0 : 1.0);
return(atan2(alpha,*beta));
return(atanh(alpha));
return(atan(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(ceil(alpha));
return(0.0);
return(1.0);
return(alpha);
return(cosh(alpha));
return(cos(alpha));
return(FxGetSymbol(fx_info,channel,x,y,expression,exception));
return(floor(alpha));
return(alpha);
return(0.0);
return((alpha/(*beta*(alpha-1.0)+1.0)));
(void) SetImageProfile(image,keyword+8,profile,exception);
(void) SetImageProfile(image,keyword+8,profile,exception);
status=ReadPSDChannelRLE(image,psd_info,i,sizes+(i*image->rows),
status=ReadPSDChannelRaw(image,psd_info->channels,i,exception);
if (num_images < 1)
PrimitiveInfo
*primitive_info;
primitive_info=AcquireQuantumMemory(extent,sizeof(*primitive_info));
if (primitive_info == (PrimitiveInfo *) NULL)
{
(void) ThrowMagickException(mvg_info->exception,GetMagickModule(),
ResourceLimitError,"MemoryAllocationFailed","`%s'","");
return(MagickFalse);
}
(void) memcpy(primitive_info,*mvg_info->primitive_info,*mvg_info->extent);
(void) RelinquishMagickMemory(*mvg_info->primitive_info);
*mvg_info->primitive_info=primitive_info;
return(MagickTrue);
*/
{
for (i=0; primitive_info[i].primitive != UndefinedPrimitive; i++)
if (primitive_info[i].text != (char *) NULL)
primitive_info[i].text=(char *) RelinquishMagickMemory(
primitive_info[i].text);
primitive_info=(PrimitiveInfo *) RelinquishMagickMemory(primitive_info);
}
affine.tx+=cursor;
DrawInfo
*clone_info;
TypeMetric
metrics;
cursor=0.0;
/*
Compute text cursor offset.
cursor,
clone_info=CloneDrawInfo((ImageInfo *) NULL,graphic_context[n]);
if (clone_info->density != (char *) NULL)
clone_info->density=DestroyString(clone_info->density);
clone_info->render=MagickFalse;
clone_info->text=AcquireString(token);
(void) ConcatenateString(&clone_info->text," ");
status&=GetTypeMetrics(image,clone_info,&metrics,exception);
clone_info=DestroyDrawInfo(clone_info);
cursor+=metrics.width;
flags=0;
if (i < strlen(name))
flags=ParseGeometry(name+i+1,&geometry_info);
image=pwp_image;
status=OpenBlob(image_info,pwp_image,ReadBinaryBlobMode,exception);
return((Image *) NULL);
continue;
if (n < 0)
if ((fabs(stop.x) < DrawEpsilon) || (fabs(stop.y) < DrawEpsilon))
if ((fabs(stop.x) < DrawEpsilon) || (fabs(stop.y) < DrawEpsilon))
if(UnpackWPGRaster(image,bpp,exception) < 0)
/* The raster cannot be unpacked */
{
DecompressionFailed:
ThrowReaderException(CoderError,"UnableToDecompressImage");
}
pixel=QuantumRange*gamma*(Sa*(Da+Sa*(Dca-Da)/(2.0*Sca))+Sca*
(1.0-Da)+Dca*(1.0-Sa));
pixel=QuantumRange*gamma*(Dca*Sa*Sa/(2.0*(Sa-Sca))+Sca*(1.0-Da)+Dca*
(1.0-Sa));
if (image->depth > 32)
region_info->height=(size_t) floor((image->rows*image_ratio/
image_ratio=image->columns/(double) image->rows;
region_info->width=(size_t) floor((image->columns*geometry_ratio/
image_ratio)+0.5);
image_ratio=former_width/(double) former_height;
*width=(size_t) floor((former_width*geometry_ratio/image_ratio)+0.5);
*height=(size_t) floor((former_height*image_ratio/geometry_ratio)+
0.5);
filelist[0]=ConstantString(image_info->filename);
if (filelist == (char **) NULL)
(void) SetImageAlpha(image,OpaqueAlphaChannel,exception);
if ((code < 0) || (code == Z_NEED_DICT))
if ((count == 0) || (LocaleNCompare(psd_info.signature,"8BPS",4) != 0) ||
*width=(unsigned long) (former_width/(distance/sqrt(area)));
*height=(unsigned long) (former_height/(distance/sqrt(area)));
info=(unsigned char *) RelinquishMagickMemory(info);
if (magick == MagickFalse)
(void) SetImageProfile(meta_image,name,profile,exception);
number_extensionss++;
DestroyImageProfiles(meta_image);
int
number_extensionss=0;
profile=DestroyStringInfo(profile);
{
mng_info=MngInfoFreeStruct(mng_info);
ThrowReaderException(CorruptImageError,"CorruptImage");
}
gamma=alpha*FxEvaluateSubexpression(fx_info,channel,x,y,p,depth,beta,
goto DecompressionFailed;
if (!image->ping)
if( UnpackWPG2Raster(image,bpp,exception) < 0)
(void) fputc(c,file);
ret = (*l2tp_nl_cmd_ops[cfg.pw_type]->session_create)(net, tunnel_id,
session_id, peer_session_id, &cfg);
ret = -EPROTONOSUPPORT;
if (l2tp_nl_cmd_ops[cfg.pw_type]->session_create)
struct l2tp_tunnel *tunnel;
tunnel = l2tp_tunnel_find(net, tunnel_id);
if (!tunnel) {
rc = -ENODEV;
goto out;
}
int ret = 0;
if (!(hdr.flags & VFIO_IRQ_SET_DATA_NONE)) {
size_t size;
int max = vfio_pci_get_irq_count(vdev, hdr.index);
if (hdr.flags & VFIO_IRQ_SET_DATA_BOOL)
size = sizeof(uint8_t);
else if (hdr.flags & VFIO_IRQ_SET_DATA_EVENTFD)
size = sizeof(int32_t);
else
return -EINVAL;
if (hdr.argsz - minsz < hdr.count * size ||
hdr.start >= max || hdr.start + hdr.count > max)
if (!ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
if (!ext4_test_bit(EXT4_B2C(sbi, offset), bh->b_data))
if (newIndex < 256)
} else if (newIndex > 250)
newIndex = 250;
maxFilenameLen = 250 - localExtIndex;
len = udf_translate_to_linux(dname, filename->u_name, filename->u_len,
if (udf_build_ustr_exact(unifilename, sname, flen))
flen = udf_get_filename(dir->i_sb, nameptr, fname, lfi);
flen = udf_get_filename(dir->i_sb, nameptr, fname, lfi);
p += udf_get_filename(sb, pc->componentIdent, p,
pc->lengthComponentIdent);
udf_pc_to_char(inode->i_sb, symlink, inode->i_size, p);
dev->priv_flags		&= ~IFF_XMIT_DST_RELEASE;
dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
else
bond_dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
if (type == ARPHRD_ETHER)
else
elen += sizeof(struct pathComponent) + pc->lengthComponentIdent;
if (pc->lengthComponentIdent > 0)
err = scm_send(sock, msg, siocb->scm);
err = scm_send(sock, msg, siocb->scm);
err = scm_send(sock, msg, siocb->scm);
memcpy(info, &laddr->a, addrlen);
memcpy(&info->sctpi_p_address, &prim->ipaddr,
sizeof(struct sockaddr_storage));
}
out:
kfree(mbuf);
return err;
}
video_usercopy(struct file *file, unsigned int cmd, unsigned long arg,
v4l2_kioctl func)
{
char	sbuf[128];
void    *mbuf = NULL;
void	*parg = NULL;
long	err  = -EINVAL;
int     is_ext_ctrl;
size_t  ctrls_size = 0;
void __user *user_ptr = NULL;
is_ext_ctrl = (cmd == VIDIOC_S_EXT_CTRLS || cmd == VIDIOC_G_EXT_CTRLS ||
cmd == VIDIOC_TRY_EXT_CTRLS);
/*  Copy arguments into temp kernel buffer  */
switch (_IOC_DIR(cmd)) {
case _IOC_NONE:
parg = NULL;
break;
case _IOC_READ:
case _IOC_WRITE:
case (_IOC_WRITE | _IOC_READ):
if (_IOC_SIZE(cmd) <= sizeof(sbuf)) {
parg = sbuf;
} else {
/* too big to allocate from stack */
mbuf = kmalloc(_IOC_SIZE(cmd), GFP_KERNEL);
if (NULL == mbuf)
return -ENOMEM;
parg = mbuf;
}
err = -EFAULT;
if (_IOC_DIR(cmd) & _IOC_WRITE)
if (copy_from_user(parg, (void __user *)arg, _IOC_SIZE(cmd)))
goto out;
break;
}
if (is_ext_ctrl) {
struct v4l2_ext_controls *p = parg;
/* In case of an error, tell the caller that it wasn't
a specific control that caused it. */
p->error_idx = p->count;
user_ptr = (void __user *)p->controls;
if (p->count) {
ctrls_size = sizeof(struct v4l2_ext_control) * p->count;
/* Note: v4l2_ext_controls fits in sbuf[] so mbuf is still NULL. */
mbuf = kmalloc(ctrls_size, GFP_KERNEL);
err = -ENOMEM;
if (NULL == mbuf)
goto out_ext_ctrl;
err = -EFAULT;
if (copy_from_user(mbuf, user_ptr, ctrls_size))
goto out_ext_ctrl;
p->controls = mbuf;
}
}
/* call driver */
err = func(file, cmd, parg);
if (err == -ENOIOCTLCMD)
err = -EINVAL;
if (is_ext_ctrl) {
struct v4l2_ext_controls *p = parg;
p->controls = (void *)user_ptr;
if (p->count && err == 0 && copy_to_user(user_ptr, mbuf, ctrls_size))
err = -EFAULT;
goto out_ext_ctrl;
}
if (err < 0)
goto out;
out_ext_ctrl:
/*  Copy results into user buffer  */
switch (_IOC_DIR(cmd)) {
case _IOC_READ:
case (_IOC_WRITE | _IOC_READ):
if (copy_to_user((void __user *)arg, parg, _IOC_SIZE(cmd)))
err = -EFAULT;
break;
unsigned int cmd, unsigned long arg)
err = __video_do_ioctl(file, cmd, parg);
long video_ioctl2(struct file *file,
if (!IS_ERR(task))
return;
if ((algt->type & CRYPTO_ALG_INTERNAL))
*type |= CRYPTO_ALG_INTERNAL;
if ((algt->mask & CRYPTO_ALG_INTERNAL))
*mask |= CRYPTO_ALG_INTERNAL;
continue;
if (!tid->sched)
put_io_context(ioc);
((flags & MAP_FIXED) &&
addr < 0xe0000000 && addr + len > 0x20000000)))
if ((flags & MAP_FIXED) && addr > STACK_TOP32 - len)
if ((flags & MAP_FIXED) && invalid_64bit_range(addr, len))
flags |= NTLMSSP_NEGOTIATE_KEY_XCH;
}
NTLMSSP_NEGOTIATE_NTLM | NTLMSSP_NEGOTIATE_EXTENDED_SEC;
if (ses->server->sign) {
if (!ses->server->session_estab ||
ses->ntlmssp->sesskey_per_smbsess)
keygen_exit:
if (!ses->server->sign) {
kfree(ses->auth_key.response);
ses->auth_key.response = NULL;
}
if (ses->server->sign && ses->server->ops->generate_signingkey) {
kfree(ses->auth_key.response);
ses->auth_key.response = NULL;
goto keygen_exit;
struct sock *sk = tun->sk;
int mask_type;
(unsigned long long)le32_to_cpu(ex->ee_block),
ext4_ext_get_actual_len(ex));
struct inode *inode,
struct ext4_ext_path *path)
ret = ext4_convert_unwritten_extents_endio(handle, inode,
err = ext4_ext_zeroout(inode, &orig_ex);
bh_lock_sock(asoc->base.sk);
if (sock_owned_by_user(asoc->base.sk)) {
bh_unlock_sock(asoc->base.sk);
struct net *net = sock_net(asoc->base.sk);
asoc->base.sk->sk_err = -error;
bh_lock_sock(asoc->base.sk);
if (sock_owned_by_user(asoc->base.sk)) {
bh_unlock_sock(asoc->base.sk);
struct net *net = sock_net(asoc->base.sk);
struct net *net = sock_net(asoc->base.sk);
asoc->base.sk->sk_err = -error;
bh_lock_sock(asoc->base.sk);
if (sock_owned_by_user(asoc->base.sk)) {
bh_unlock_sock(asoc->base.sk);
len = ipv6_getsockopt_sticky(sk, np->opt->hopopt,
if (!hdr)
.match_data.cmp		= type->match,
return ERR_PTR(-ENOKEY);
if (!ctx.match_data.cmp)
.match_data.cmp		= type->match,
if (!index_key.type->match || !index_key.type->instantiate ||
dns_resolver_match(const struct key *key,
const struct key_match_data *match_data)
return strcmp(key->description, match_data->raw_data) == 0;
}
int user_match(const struct key *key, const struct key_match_data *match_data)
{
if (copy_to_user(uoss, &oss, sizeof(oss)))
error = 0;
if (uoss) {
oss.ss_sp = (void __user *) current->sas_ss_sp;
oss.ss_size = current->sas_ss_size;
oss.ss_flags = sas_ss_flags(sp);
}
if (*ppos >= HPEE_MAX_LENGTH)
if (!ie1)
/*
* We don't check the error code - if userspace has
* not set up a proper pointer then tough luck.
*/
put_user(0, tidptr);
sys_futex(tidptr, FUTEX_WAKE, 1, NULL, NULL, 0);
if (tsk->clear_child_tid
&& !(tsk->flags & PF_SIGNALED)
&& atomic_read(&mm->mm_users) > 1) {
u32 __user * tidptr = tsk->clear_child_tid;
if (serial->port[0] == usbcons_info.port) {
ret = process_one_ticket(ac, secret, &p, end,
dbuf, ticket_buf);
ret = process_one_ticket(ac, secret, &p, end,
dbuf, ticket_buf);
TEMP_TICKET_BUF_LEN);
void **p, void *end,
tp = ticket_buf;
void *dbuf, void *ticket_buf)
dlen = ceph_x_decrypt(&old_key, p, end, ticket_buf,
TEMP_TICKET_BUF_LEN);
dlen = ceph_x_decrypt(secret, p, end, dbuf,
return ret;
if (chg < 0)
return chg;
if (hugepage_subpool_get_pages(spool, chg))
return -ENOSPC;
kref_put(&reservations->refs, resv_map_release);
int ret = proc_dointvec(table, write, buffer, lenp, ppos);
level = user_mode(regs) ? KERN_DEBUG : KERN_CRIT;
if (user_mode(regs))
printk(level);
print_symbol(" IAOQ[0]: %s\n", regs->iaoq[0]);
printk(level);
print_symbol(" IAOQ[1]: %s\n", regs->iaoq[1]);
printk(level);
print_symbol(" RP(r2): %s\n", regs->gr[2]);
parisc_show_stack(current, NULL, regs);
int i;
printk("%s [<" RFMT ">] ", (i&0x3)==1 ? KERN_CRIT : "", info->ip);
#ifdef CONFIG_KALLSYMS
print_symbol("%s\n", info->ip);
#else
if ((i & 0x03) == 0)
printk("\n");
#endif
printk("\n");
if (namelen > 32)
spec.flags |= SMALL;
if (spec.field_width == -1) {
spec.field_width = default_width;
spec.flags |= ZEROPAD;
}
spec.base = 16;
return number(buf, end, (unsigned long) ptr, spec);
rv = access_remote_vm(mm, arg_end - 1, &c, 1, 0);
nr_read = access_remote_vm(mm, p, page, _count, 0);
nr_read = access_remote_vm(mm, p, page, _count, 0);
ret = encrypt_authorizer(au);
au->buf->vec.iov_len = p - au->buf->vec.iov_base;
WARN_ON(p > end);
msg_b->struct_v = 1;
mb_cache_destroy(cache);
ext4_xattr_put_super(struct super_block *sb)
{
mb_cache_shrink(sb->s_bdev);
}
/*
struct mb_cache_entry *ce = NULL;
struct mb_cache *ext4_mb_cache = EXT4_GET_MB_CACHE(inode);
ce = mb_cache_entry_get(ext4_mb_cache, bh->b_bdev, bh->b_blocknr);
if (ce)
mb_cache_entry_free(ce);
if (ce)
mb_cache_entry_release(ce);
struct mb_cache *ext4_mb_cache = EXT4_GET_MB_CACHE(inode);
}
mb_cache_entry_release(ce);
if (ce) {
mb_cache_entry_free(ce);
ce = NULL;
}
mb_cache_entry_release(ce);
struct mb_cache_entry *ce = NULL;
struct mb_cache *ext4_mb_cache = EXT4_GET_MB_CACHE(inode);
ce = mb_cache_entry_get(ext4_mb_cache, bs->bh->b_bdev,
bs->bh->b_blocknr);
if (ce) {
mb_cache_entry_release(ce);
ce = NULL;
return mb_cache_create(name, HASH_BUCKET_BITS);
ce = mb_cache_entry_find_next(ce, inode->i_sb->s_bdev, hash);
struct mb_cache_entry **pce)
struct mb_cache_entry *ce;
struct mb_cache *ext4_mb_cache = EXT4_GET_MB_CACHE(inode);
again:
ce = mb_cache_entry_find_first(ext4_mb_cache, inode->i_sb->s_bdev,
hash);
if (IS_ERR(ce)) {
if (PTR_ERR(ce) == -EAGAIN)
goto again;
break;
}
struct mb_cache *ext4_mb_cache = EXT4_GET_MB_CACHE(inode);
struct mb_cache_entry *ce;
ce = mb_cache_entry_alloc(ext4_mb_cache, GFP_NOFS);
if (!ce) {
ea_bdebug(bh, "out of memory");
return;
}
error = mb_cache_entry_insert(ce, bh->b_bdev, bh->b_blocknr, hash);
mb_cache_entry_free(ce);
if (error == -EBUSY) {
error = 0;
}
} else {
mb_cache_entry_release(ce);
}
struct audit_chunk *chunk;
chunk = find_chunk(p);
get_inotify_watch(&chunk->watch);
spin_unlock(&hash_lock);
untag_chunk(chunk, p);
put_inotify_watch(&chunk->watch);
spin_lock(&hash_lock);
* chunk is refcounted by embedded inotify_watch.
call_rcu(&chunk->head, __free_chunk);
void audit_put_chunk(struct audit_chunk *chunk)
free_chunk(chunk);
get_inotify_watch(&p->watch);
chunk = find_chunk(node);
get_inotify_watch(&chunk->watch);
spin_unlock(&hash_lock);
untag_chunk(chunk, node);
put_inotify_watch(&chunk->watch);
spin_lock(&hash_lock);
struct audit_chunk *chunk;
struct audit_chunk *chunk = container_of(rcu, struct audit_chunk, head);
return;
return;
return;
* audit_inotify_unregister(). */
list_add(&parent->ilist, &inotify_list);
get_inotify_watch(&parent->wdata);
/* the put matching the get in audit_do_del_rule() */
put_inotify_watch(&p->wdata);
get_inotify_watch(watch);
mutex_unlock(&ih->mutex);
put_inotify_watch(watch);
mutex_unlock(&ih->mutex);
if (cb->nlh->nlmsg_len > 4 + NLMSG_SPACE(sizeof(*r))) {
struct rtattr *bc = (struct rtattr *)(r + 1);
if (!inet_diag_bc_run(RTA_DATA(bc), RTA_PAYLOAD(bc), &entry))
if (flags & __GFP_ZERO)
memset(ptr, 0, size);
if (flags & __GFP_ZERO)
memset(addr, 0, size);
vcpu->arch.apic->vapic_addr = vapic_addr;
if (vapic_addr)
else
data = *(u32 *)(vapic + offset_in_page(vcpu->arch.apic->vapic_addr));
kunmap_atomic(vapic);
vapic = kmap_atomic(vcpu->arch.apic->vapic_page);
void *vapic;
static int vapic_enter(struct kvm_vcpu *vcpu)
{
struct kvm_lapic *apic = vcpu->arch.apic;
struct page *page;
if (!apic || !apic->vapic_addr)
return 0;
page = gfn_to_page(vcpu->kvm, apic->vapic_addr >> PAGE_SHIFT);
if (is_error_page(page))
return -EFAULT;
vcpu->arch.apic->vapic_page = page;
return 0;
}
struct kvm_lapic *apic = vcpu->arch.apic;
int idx;
if (!apic || !apic->vapic_addr)
return;
idx = srcu_read_lock(&vcpu->kvm->srcu);
kvm_release_page_dirty(apic->vapic_page);
mark_page_dirty(vcpu->kvm, apic->vapic_addr >> PAGE_SHIFT);
srcu_read_unlock(&vcpu->kvm->srcu, idx);
}
static void vapic_exit(struct kvm_vcpu *vcpu)
{
r = 0;
kvm_lapic_set_vapic_addr(vcpu, va.vapic_addr);
vapic_exit(vcpu);
r = vapic_enter(vcpu);
if (r) {
srcu_read_unlock(&kvm->srcu, vcpu->srcu_idx);
return r;
}
void *shared_kaddr;
struct pvclock_vcpu_time_info *guest_hv_clock;
memcpy(shared_kaddr + vcpu->time_offset, &vcpu->hv_clock,
sizeof(vcpu->hv_clock));
kunmap_atomic(shared_kaddr);
pvclock_flags = (guest_hv_clock->flags & PVCLOCK_GUEST_STOPPED);
shared_kaddr = kmap_atomic(vcpu->time_page);
if (!vcpu->time_page)
mark_page_dirty(v->kvm, vcpu->time >> PAGE_SHIFT);
guest_hv_clock = shared_kaddr + vcpu->time_offset;
/* ...but clean it before doing the actual write */
vcpu->arch.time_offset = data & ~(PAGE_MASK | 1);
if (vcpu->arch.time_offset &
(sizeof(struct pvclock_vcpu_time_info) - 1))
vcpu->arch.time_page =
gfn_to_page(vcpu->kvm, data >> PAGE_SHIFT);
if (is_error_page(vcpu->arch.time_page))
vcpu->arch.time_page = NULL;
if (!vcpu->arch.time_page)
list_for_each(tmp, &server->smb_ses_list) {
ses = list_entry(tmp, struct cifsSesInfo, smb_ses_list);
if (strncmp(ses->userName, username, MAX_USERNAME_SIZE))
vma->vm_flags = vm_flags | mm->def_flags;
area->vm_flags |= VM_RESERVED;
vma->vm_flags |= (VM_IO | VM_RESERVED | VM_PFNMAP);
area->vm_flags |= VM_RESERVED;
#ifndef VIA_NDEBUG
{
unsigned long max_bufs = chan->frag_number;
if (rd && wr) max_bufs *= 2;
/* via_dsp_mmap() should ensure this */
assert (pgoff < max_bufs);
}
#endif
vmcs_writel(HOST_CR4, read_cr4());  /* 22.2.3, 22.2.5 */
struct arm_pmu *armpmu = to_arm_pmu(event->pmu);
if ((inode->i_mode & (S_ISGID | S_IXGRP)) == S_ISGID)
struct user_struct *user = group->inotify_data.user;
atomic_dec(&user->inotify_devs);
group->inotify_data.user = user;
group = inotify_new_group(user, inotify_max_queued_events);
if (IS_ERR(group)) {
ret = PTR_ERR(group);
atomic_inc(&user->inotify_devs);
if (ret >= 0)
return ret;
fsnotify_put_group(group);
atomic_dec(&user->inotify_devs);
if (ret == -EEXIST)
BUG_ON(ret == -EEXIST);
kfree(it);
goto err1;
goto err1;
return NULL;
err1:
kfree (v);
struct sg_proc_deviter * it = (struct sg_proc_deviter *) v;
return sprintf(buf, "%s\n", pdev->driver_override);
if (syscall_nr < 0)
if (syscall_nr < 0)
if (syscall_nr < 0)
if (ccid->ccid_ops->ccid_hc_rx_getsockopt != NULL)
if (ccid->ccid_ops->ccid_hc_tx_getsockopt != NULL)
fentry = &filter[pc];
A = fentry->k;
A += fentry->k;
X = fentry->k;
A = mem[fentry->k];
A -= fentry->k;
X = mem[fentry->k];
A *= fentry->k;
return fentry->k;
A /= fentry->k;
mem[fentry->k] = X;
A &= fentry->k;
mem[fentry->k] = A;
A |= fentry->k;
A <<= fentry->k;
A >>= fentry->k;
pc += fentry->k;
pc += (A > fentry->k) ? fentry->jt : fentry->jf;
pc += (A >= fentry->k) ? fentry->jt : fentry->jf;
pc += (A == fentry->k) ? fentry->jt : fentry->jf;
pc += (A & fentry->k) ? fentry->jt : fentry->jf;
k = fentry->k;
k = fentry->k;
k = fentry->k;
struct sock_filter *fentry;	/* We walk down these */
k = X + fentry->k;
k = X + fentry->k;
k = X + fentry->k;
ptr = load_pointer(skb, fentry->k, 1, &tmp);
!strncmp(of_get_property(root, "model", NULL),
"IBM,LongTrail", 13)) {
if ((root = of_find_node_by_path("/")) &&
if (!strncmp(model, "IBM,LongTrail", 13)) {
vma->vm_ops = &uio_physical_vm_ops;
idev->info->mem[mi].addr >> PAGE_SHIFT,
if (io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
start = fbdev->fb_phys & PAGE_MASK;
len = PAGE_ALIGN((start & ~PAGE_MASK) + fbdev->fb_len);
off = vma->vm_pgoff << PAGE_SHIFT;
if ((vma->vm_end - vma->vm_start + off) > len) {
return -EINVAL;
}
off += start;
vma->vm_pgoff = off >> PAGE_SHIFT;
return io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
vma->vm_end - vma->vm_start,
vma->vm_page_prot);
unsigned int len;
unsigned long start=0, off;
if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT)) {
return -EINVAL;
}
start = fbdev->fb_phys & PAGE_MASK;
len = PAGE_ALIGN((start & ~PAGE_MASK) + fbdev->fb_len);
vcpu->run->internal.suberror = KVM_INTERNAL_ERROR_EMULATION;
vcpu->run->internal.ndata = 0;
return EMULATE_FAIL;
vcpu->run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
else if (sk->sk_no_check_tx) {   /* UDP csum disabled */
if ((((length + (skb ? skb->len : headersize)) > mtu) ||
(sk->sk_type == SOCK_DGRAM) && !udp_get_no_check6_tx(sk)) {
memcpy(lp->StationName, extra, wrqu->data.length);
memcpy((void *)lp->StationName, (void *)&pLtv->u.u8[2], (size_t)pLtv->u.u16[0]);
out:
return NULL;
v.val = test_bit(SOCK_PASSCRED, &sock->flags) ? 1 : 0;
v.val = test_bit(SOCK_PASSSEC, &sock->flags) ? 1 : 0;
about it this is right. Otherwise apps have to
play 'guess the biggest size' games. RCVBUF/SNDBUF
are treated in BSD as hints */
if (val > sysctl_wmem_max)
val = sysctl_wmem_max;
if ((val * 2) < SOCK_MIN_SNDBUF)
sk->sk_sndbuf = SOCK_MIN_SNDBUF;
else
sk->sk_sndbuf = val * 2;
/*
*	Wake up sending tasks if we
*	upped the value.
*/
about it this is right. Otherwise apps have to
play 'guess the biggest size' games. RCVBUF/SNDBUF
are treated in BSD as hints */
if (val > sysctl_rmem_max)
val = sysctl_rmem_max;
if ((val * 2) < SOCK_MIN_RCVBUF)
sk->sk_rcvbuf = SOCK_MIN_RCVBUF;
else
sk->sk_rcvbuf = val * 2;
if (p[1] > X25_MAX_DTE_FACIL_LEN)
if (p[1] > X25_MAX_DTE_FACIL_LEN)
break;
break;
state->pos = 0;
state->rand = rand;
return (state->list[state->pos++] + state->rand) % state->count;
char data[8];
return -EIO;
return -EIO;
return snprintf(buf, PAGE_SIZE, "%s\n", macro_mode);
return -EIO;
return -EIO;
return brightness;
char data[8];
char build[ATUSB_BUILD_SIZE + 1];
unsigned char buffer[3];
if (optname == IPT_SO_SET_REPLACE)
/* SO_SET_REPLACE seems to be the same in all levels */
do_replace(void __user *user, unsigned int len)
struct ipt_replace tmp;
struct ipt_table *t;
struct xt_table_info *newinfo, *oldinfo;
struct xt_counters *counters;
void *loc_cpu_entry, *loc_cpu_old_entry;
counters = vmalloc(tmp.num_counters * sizeof(struct xt_counters));
if (!counters) {
ret = -ENOMEM;
}
ret = translate_table(tmp.name, tmp.valid_hooks,
newinfo, loc_cpu_entry, tmp.size, tmp.num_entries,
tmp.hook_entry, tmp.underflow);
if (ret != 0)
goto free_newinfo_counters;
duprintf("ip_tables: Translated table\n");
t = try_then_request_module(xt_find_table_lock(AF_INET, tmp.name),
"iptable_%s", tmp.name);
if (!t || IS_ERR(t)) {
ret = t ? PTR_ERR(t) : -ENOENT;
goto free_newinfo_counters_untrans;
}
/* You lied! */
if (tmp.valid_hooks != t->valid_hooks) {
duprintf("Valid hook crap: %08X vs %08X\n",
tmp.valid_hooks, t->valid_hooks);
ret = -EINVAL;
goto put_module;
}
void *loc_cpu_entry;
paddc = vmalloc_node(len, numa_node_id());
/* Choose the copy that is on our node */
IPT_ENTRY_ITERATE(loc_cpu_entry,
struct xt_table_info *newinfo, *oldinfo;
struct xt_counters *counters;
const struct xt_counters addme[],
unsigned int *i)
add_counter_to_entry(struct ipt_entry *e,
struct ipt_getinfo info;
struct xt_table_info *private = t->private;
info.valid_hooks = t->valid_hooks;
memcpy(info.hook_entry, private->hook_entry,
sizeof(info.hook_entry));
memcpy(info.underflow, private->underflow,
sizeof(info.underflow));
info.num_entries = private->number;
info.size = private->size;
memcpy(info.name, name, sizeof(info.name));
if (copy_to_user(user, &info, *len) != 0)
ret = -EFAULT;
else
ret = 0;
xt_table_unlock(t);
module_put(t->me);
} else
ret = t ? PTR_ERR(t) : -ENOENT;
}
break;
case IPT_SO_GET_ENTRIES: {
struct ipt_get_entries get;
if (*len < sizeof(get)) {
duprintf("get_entries: %u < %u\n", *len, sizeof(get));
ret = -EINVAL;
} else if (copy_from_user(&get, user, sizeof(get)) != 0) {
ret = -EFAULT;
} else if (*len != sizeof(struct ipt_get_entries) + get.size) {
duprintf("get_entries: %u != %u\n", *len,
sizeof(struct ipt_get_entries) + get.size);
ret = -EINVAL;
} else
ret = get_entries(&get, user);
}
case IPT_SO_GET_INFO: {
char name[IPT_TABLE_MAXNAMELEN];
struct ipt_table *t;
if (*len != sizeof(struct ipt_getinfo)) {
duprintf("length %u != %u\n", *len,
sizeof(struct ipt_getinfo));
ret = -EINVAL;
break;
}
if (copy_from_user(name, user, sizeof(name)) != 0) {
ret = -EFAULT;
break;
}
name[IPT_TABLE_MAXNAMELEN-1] = '\0';
t = try_then_request_module(xt_find_table_lock(AF_INET, name),
"iptable_%s", name);
if (t && !IS_ERR(t)) {
void *loc_cpu_entry;
if (!oldinfo)
goto put_module;
/* Update module usage count based on number of rules */
duprintf("do_replace: oldnum=%u, initnum=%u, newnum=%u\n",
oldinfo->number, oldinfo->initial_entries, newinfo->number);
if ((oldinfo->number > oldinfo->initial_entries) || 
(newinfo->number <= oldinfo->initial_entries)) 
module_put(t->me);
if ((oldinfo->number > oldinfo->initial_entries) &&
(newinfo->number <= oldinfo->initial_entries))
module_put(t->me);
/* Get the old counters. */
get_counters(oldinfo, counters);
/* Decrease module usage counts and free resource */
if (copy_to_user(tmp.counters, counters,
ret = -EFAULT;
vfree(counters);
return ret;
put_module:
module_put(t->me);
free_newinfo_counters_untrans:
free_newinfo_counters:
vfree(counters);
free_newinfo:
/* We're lazy, and add to the first CPU; overflow works its fey magic
* and everything is OK. */
ret = do_add_counters(user, len);
copy_entries_to_user(unsigned int total_size,
struct ipt_table *table,
void __user *userptr)
(*i)++;
return 0;
return -ENOMEM;
if (skb->len < nlh->nlmsg_len)
IP_NF_ASSERT(cid);
ntohs(*cid), ntohs(new_callid));
(char *)&new_callid,
cid = &pptpReq->icreq.callID;
(void *)cid - ((void *)ctlh - sizeof(struct pptp_pkt_hdr)),
sizeof(new_callid), 
cid = &pptpReq->clrreq.callID;
sizeof(new_callid)) == 0)
u_int16_t msg, *cid = NULL, new_callid;
cid = &pptpReq->ocreq.callID;
pcid = &pptpReq->wanerr.peersCallID;
rv = ip_nat_mangle_tcp_packet(pskb, ct, ctinfo, 
pcid = &pptpReq->disc.callID;
pcid = &pptpReq->setlink.peersCallID;
(void *)pcid - ((void *)ctlh - sizeof(struct pptp_pkt_hdr)),
IP_NF_ASSERT(cid);
ntohs(*cid), ntohs(new_cid));
rv = ip_nat_mangle_tcp_packet(pskb, ct, ctinfo, 
(void *)cid - ((void *)ctlh - sizeof(struct pptp_pkt_hdr)), 
sizeof(new_cid),
u_int16_t msg, new_cid = 0, new_pcid, *pcid = NULL, *cid = NULL;
(char *)&new_cid, 
pcid = &pptpReq->ocack.peersCallID;	
cid = &pptpReq->ocack.callID;
pcid = &pptpReq->iccon.peersCallID;
IP_NF_ASSERT(pcid);
ntohs(*pcid), ntohs(new_pcid));
timr->it_interval);
overrun = timr->it_overrun_last;
timr->it_overrun = -1;
timr->it_overrun += (int)kc->timer_forward(timr, now);
timr->it_interval);
struct sk_buff *skb,
struct hns_nic_ring_data *ring_data)
int hns_nic_net_xmit_hw(struct net_device *ndev,
int bytes_returned, name_len;
return to_o2nm_cluster(node->nd_item.ci_parent->ci_parent);
delete_port(dp);
kfree(dp);
snd_seq_oss_writeq_delete(dp->writeq);
snd_seq_oss_readq_delete(dp->readq);
}
static int iov_fault_in_pages_write(struct iovec *iov, unsigned long len)
{
while (!iov->iov_len)
iov++;
while (len > 0) {
unsigned long this_len;
this_len = min_t(unsigned long, len, iov->iov_len);
if (fault_in_pages_writeable(iov->iov_base, this_len))
break;
len -= this_len;
iov++;
}
return len;
pipe_iov_copy_to_user(struct iovec *iov, const void *from, unsigned long len,
int atomic)
{
unsigned long copy;
while (len > 0) {
while (!iov->iov_len)
iov++;
copy = min_t(unsigned long, len, iov->iov_len);
if (atomic) {
if (__copy_to_user_inatomic(iov->iov_base, from, copy))
return -EFAULT;
} else {
if (copy_to_user(iov->iov_base, from, copy))
return -EFAULT;
}
from += copy;
len -= copy;
iov->iov_base += copy;
iov->iov_len -= copy;
}
return 0;
}
/*
* Attempt to pre-fault in the user memory, so we can use atomic copies.
* Returns the number of bytes not faulted in.
*/
GFP_KERNEL);
if (!os2name)
return -ENOMEM;
strcpy(os2name, name + XATTR_OS2_PREFIX_LEN);
name = os2name;
namelen -= XATTR_OS2_PREFIX_LEN;
}
kfree(os2name);
char *os2name = NULL;
if (strncmp(name, XATTR_OS2_PREFIX, XATTR_OS2_PREFIX_LEN) == 0) {
os2name = kmalloc(namelen - XATTR_OS2_PREFIX_LEN + 1,
return true;
/*
* Check for "system."
*/
if ((ea->namelen >= XATTR_SYSTEM_PREFIX_LEN) &&
!strncmp(ea->name, XATTR_SYSTEM_PREFIX, XATTR_SYSTEM_PREFIX_LEN))
return false;
/*
* Check for "user."
*/
if ((ea->namelen >= XATTR_USER_PREFIX_LEN) &&
!strncmp(ea->name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN))
return false;
/*
* Check for "security."
*/
if ((ea->namelen >= XATTR_SECURITY_PREFIX_LEN) &&
!strncmp(ea->name, XATTR_SECURITY_PREFIX,
XATTR_SECURITY_PREFIX_LEN))
return false;
/*
* Check for "trusted."
*/
if ((ea->namelen >= XATTR_TRUSTED_PREFIX_LEN) &&
!strncmp(ea->name, XATTR_TRUSTED_PREFIX, XATTR_TRUSTED_PREFIX_LEN))
return false;
/*
* Add any other valid namespace prefixes here
*/
/*
* We assume it's OS/2's flat namespace
*/
strncmp(name, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN) &&
strncmp(name, XATTR_OS2_PREFIX, XATTR_OS2_PREFIX_LEN))
* destination queue.  Using a helper function skips the a call to
return skb->queue_mapping;
dma_async_memcpy_buf_to_buf(struct dma_chan *chan, void *dest,
void *src, size_t len)
{
return dma_async_memcpy_pg_to_pg(chan, virt_to_page(dest),
(unsigned long) dest & ~PAGE_MASK,
virt_to_page(src),
(unsigned long) src & ~PAGE_MASK, len);
}
{
return dma_async_memcpy_pg_to_pg(chan, page, offset,
virt_to_page(kdata),
(unsigned long) kdata & ~PAGE_MASK, len);
}
dma_async_memcpy_buf_to_pg(struct dma_chan *chan, struct page *page,
unsigned int offset, void *kdata, size_t len)
dma_async_memcpy_pg_to_pg(struct dma_chan *chan, struct page *dest_pg,
unsigned int dest_off, struct page *src_pg, unsigned int src_off,
size_t len)
{
struct dma_device *dev = chan->device;
struct dma_async_tx_descriptor *tx;
struct dmaengine_unmap_data *unmap;
dma_cookie_t cookie;
unsigned long flags;
unmap = dmaengine_get_unmap_data(dev->dev, 2, GFP_NOWAIT);
if (!unmap)
return -ENOMEM;
unmap->to_cnt = 1;
unmap->from_cnt = 1;
unmap->addr[0] = dma_map_page(dev->dev, src_pg, src_off, len,
DMA_TO_DEVICE);
unmap->addr[1] = dma_map_page(dev->dev, dest_pg, dest_off, len,
DMA_FROM_DEVICE);
unmap->len = len;
flags = DMA_CTRL_ACK;
tx = dev->device_prep_dma_memcpy(chan, unmap->addr[1], unmap->addr[0],
len, flags);
if (!tx) {
dmaengine_unmap_put(unmap);
return -ENOMEM;
}
dma_set_unmap(tx, unmap);
cookie = tx->tx_submit(tx);
dmaengine_unmap_put(unmap);
preempt_disable();
__this_cpu_add(chan->local->bytes_transferred, len);
__this_cpu_inc(chan->local->memcpy_count);
preempt_enable();
return cookie;
}
if (err) {
if (skb)
available = TCP_SKB_CB(skb)->seq + skb->len - (*seq);
if ((available < target) &&
(len > sysctl_tcp_dma_copybreak) && !(flags & MSG_PEEK) &&
!sysctl_tcp_low_latency &&
net_dma_find_channel()) {
preempt_enable();
tp->ucopy.pinned_list =
dma_pin_iovec_pages(msg->msg_iov, len);
} else {
preempt_enable();
}
}
#endif
#ifdef CONFIG_NET_DMA
if (tp->ucopy.dma_chan) {
if (tp->rcv_wnd == 0 &&
!skb_queue_empty(&sk->sk_async_wait_queue)) {
tcp_service_net_dma(sk, true);
tcp_cleanup_rbuf(sk, copied);
} else
dma_async_issue_pending(tp->ucopy.dma_chan);
}
#endif
copied = -EFAULT;
sk_eat_skb(sk, skb, copied_early);
}
if (!(flags & MSG_PEEK)) {
#ifdef CONFIG_NET_DMA
tcp_service_net_dma(sk, false);  /* Don't block */
tp->ucopy.wakeup = 0;
#endif
}
} else
if (!(flags & MSG_PEEK)) {
msg->msg_iov, used);
break;
#ifdef CONFIG_NET_DMA
tcp_service_net_dma(sk, true);  /* Wait for queue to drain */
tp->ucopy.dma_chan = NULL;
if (tp->ucopy.pinned_list) {
dma_unpin_iovec_pages(tp->ucopy.pinned_list);
tp->ucopy.pinned_list = NULL;
}
#endif
copied_early = false;
#endif
bool copied_early = false;
sk_eat_skb(sk, skb, copied_early);
if (!copied)
}
/* Exception. Bailout! */
#ifdef CONFIG_NET_DMA
if (!tp->ucopy.dma_chan && tp->ucopy.pinned_list)
tp->ucopy.dma_chan = net_dma_find_channel();
if (tp->ucopy.dma_chan) {
tp->ucopy.dma_cookie = dma_skb_copy_datagram_iovec(
tp->ucopy.dma_chan, skb, offset,
msg->msg_iov, used,
tp->ucopy.pinned_list);
if (tp->ucopy.dma_cookie < 0) {
copied_early = false;
pr_alert("%s: dma_cookie < 0\n",
__func__);
{
/* Exception. Bailout! */
if (!copied)
copied = -EFAULT;
break;
}
err = skb_copy_datagram_iovec(skb, offset,
dma_async_issue_pending(tp->ucopy.dma_chan);
if ((offset + used) == skb->len)
copied_early = true;
#ifdef CONFIG_NET_DMA
tp->ucopy.dma_chan = NULL;
preempt_disable();
skb = skb_peek_tail(&sk->sk_receive_queue);
{
int available = 0;
static void tcp_service_net_dma(struct sock *sk, bool wait)
{
dma_cookie_t done, used;
dma_cookie_t last_issued;
struct tcp_sock *tp = tcp_sk(sk);
if (!tp->ucopy.dma_chan)
return;
last_issued = tp->ucopy.dma_cookie;
dma_async_issue_pending(tp->ucopy.dma_chan);
do {
if (dma_async_is_tx_complete(tp->ucopy.dma_chan,
last_issued, &done,
&used) == DMA_COMPLETE) {
/* Safe to free early-copied skbs now */
__skb_queue_purge(&sk->sk_async_wait_queue);
break;
} else {
struct sk_buff *skb;
while ((skb = skb_peek(&sk->sk_async_wait_queue)) &&
(dma_async_is_complete(skb->dma_cookie, done,
used) == DMA_COMPLETE)) {
__skb_dequeue(&sk->sk_async_wait_queue);
kfree_skb(skb);
}
}
} while (wait);
}
#endif
sk_eat_skb(sk, skb, false);
sk_eat_skb(sk, skb, false);
sk_eat_skb(sk, skb, false);
#ifdef CONFIG_NET_DMA
__skb_queue_purge(&sk->sk_async_wait_queue);
#endif
ioat_set_tcp_copy_break(262144);
net_dmaengine_get();
net_dmaengine_put();
ioat_set_tcp_copy_break(2048);
#ifdef CONFIG_NET_DMA
struct tcp_sock *tp = tcp_sk(sk);
if (!tp->ucopy.dma_chan && tp->ucopy.pinned_list)
tp->ucopy.dma_chan = net_dma_find_channel();
if (tp->ucopy.dma_chan)
else
#endif
{
if (!tcp_prequeue(sk, skb))
ret = tcp_v4_do_rcv(sk, skb);
}
#ifdef CONFIG_NET_DMA
/* Cleans up our sk_async_wait_queue */
__skb_queue_purge(&sk->sk_async_wait_queue);
#endif
spin_lock_irqsave(&sk->sk_receive_queue.lock, cpu_flags);
sk_eat_skb(sk, skb, false);
sk_eat_skb(sk, skb, false);
*seq = 0;
spin_unlock_irqrestore(&sk->sk_receive_queue.lock, cpu_flags);
static inline void net_dmaengine_put(void)
{
}
#endif
}
static inline void net_dmaengine_get(void)
{
ioat_set_tcp_copy_break(4096);
#ifdef CONFIG_NET_DMA
struct tcp_sock *tp = tcp_sk(sk);
if (!tp->ucopy.dma_chan && tp->ucopy.pinned_list)
tp->ucopy.dma_chan = net_dma_find_channel();
if (tp->ucopy.dma_chan)
else
#endif
{
if (!tcp_prequeue(sk, skb))
ret = tcp_v6_do_rcv(sk, skb);
}
static inline void ioat_set_tcp_copy_break(unsigned long copybreak)
sysctl_tcp_dma_copybreak = copybreak;
#ifdef CONFIG_NET_DMA
skb_queue_head_init(&sk->sk_async_wait_queue);
#endif
#endif
#ifdef CONFIG_NET_DMA
tp->ucopy.dma_chan = NULL;
tp->ucopy.wakeup = 0;
tp->ucopy.pinned_list = NULL;
tp->ucopy.dma_cookie = 0;
#endif
if (space < rqstp->rq_reserved) {
struct svc_xprt *xprt = rqstp->rq_xprt;
rqstp->rq_xprt = serv->sv_bc_xprt;
if (test_bit(XPT_TEMP, &rqstp->rq_xprt->xpt_flags))
if (versp->vs_need_cong_ctrl &&
rqstp->rq_xprt->xpt_ops->xpo_prep_reply_hdr(rqstp);
static void svc_tcp_prep_reply_hdr(struct svc_rqst *rqstp)
task_lock(task);
if (task->mm != mm)
goto out;
if (task->mm != current->mm &&
__ptrace_may_access(task, PTRACE_MODE_READ) < 0)
goto out;
task_unlock(task);
out:
task_unlock(task);
up_read(&mm->mmap_sem);
mmput(mm);
return NULL;
return sock->ops->sendpage(sock, page, offset, size, flags);
build_protos(tls_prots, &tcp_prot);
static void build_protos(struct proto *prot, struct proto *base)
{
prot[TLS_BASE_TX] = *base;
prot[TLS_BASE_TX].setsockopt	= tls_setsockopt;
prot[TLS_BASE_TX].getsockopt	= tls_getsockopt;
prot[TLS_BASE_TX].close		= tls_sk_proto_close;
prot[TLS_SW_TX] = prot[TLS_BASE_TX];
prot[TLS_SW_TX].sendmsg		= tls_sw_sendmsg;
prot[TLS_SW_TX].sendpage	= tls_sw_sendpage;
}
fput(kiocb->ki_filp);
out_fput:
if (unlikely(ret))
fput(file);
ret = -EBADF;
goto out_fput;
ret = -EINVAL;
goto out_fput;
goto out_fput;
if (unlikely(!req->ki_filp))
goto out_fput;
fput(req->ki_filp);
goto out_fput;
req->ki_filp = fget(iocb->aio_fildes);
out_fput:
return -EBADF;
return ret;
struct file *file = iocb->poll.file;
fput(file);
fput(req->file);
}
req->file = fget(iocb->aio_fildes);
if (unlikely(!req->file))
return -EBADF;
if (unlikely(apt.error)) {
req->file = fget(iocb->aio_fildes);
if (unlikely(!req->file))
return -EBADF;
if (unlikely(!req->file->f_op->fsync)) {
fput(req->file);
}
fput(req->file);
fput(req->file);
/*
* Use IP's RNG. It suits our purpose perfectly: it re-keys itself
* every second, from the entropy pool (and thus creates a limited
* drain on it), and uses halfMD4Transform within the second. We
* also mix it with jiffies and the PID:
*/
return secure_ip_id((__force __be32)(current->pid + jiffies));
status = pci_enable_msi(dev);
return 0;
"   j     3f\n"
"   jz    5f\n"
"   jnh   3f\n"
"   j     5f\n"
"3:\n"
"   jnh   6f\n"
"   j     6f\n"
"5:"SLR"  %0,%0\n"
"6: \n"
EX_TABLE(0b,3b) EX_TABLE(2b,3b) EX_TABLE(4b,6b)
"   jnh   3f\n"
"   j     3f\n"
"3:\n"
"   jz    4f\n"
"   jnh   5f\n"
"   j     5f\n"
"4:"SLR"  %0,%0\n"
"5: \n"
EX_TABLE(0b,2b) EX_TABLE(3b,5b)
#ifdef TIF_32BIT
if (test_thread_flag(TIF_32BIT))
# define IS_IA32	test_thread_flag(TIF_IA32)
NET_INC_STATS_BH(twsk_net(tw), LINUX_MIB_TIMEWAITRECYCLED);
NET_INC_STATS_BH(twsk_net(tw), LINUX_MIB_TIMEWAITRECYCLED);
for(;; result += UDP_HTABLE_SIZE) {
if (probe_kernel_read(opcodes, rip - PROLOGUE_SIZE, OPCODE_BUFSIZE)) {
show_opcodes((u8 *)regs->ip, loglvl);
if (syscall_nr < 0)
if (syscall_nr < 0)
if (syscall_nr < 0)
if (error < 0)
goto out_undo;
}
struct pernet_operations *ops;
if (ops->init) {
error = ops->init(net);
static void unregister_pernet_operations(struct pernet_operations *ops)
static void unregister_pernet_operations(struct pernet_operations *ops)
void unregister_pernet_gen_subsys(int id, struct pernet_operations *ops)
{
mutex_lock(&net_mutex);
unregister_pernet_operations(ops);
ida_remove(&net_generic_ids, id);
mutex_unlock(&net_mutex);
}
struct pernet_operations *ops;
if (upg/* && pg != upg*/) {
if (!ptep)
goto out;
goto unlock;
goto unlock;
inode = iget(dir->i_sb, ino);
inode = iget(child->d_inode->i_sb, ino);
ino > le32_to_cpu(EXT3_SB(sb)->s_es->s_inodes_count)) {
ext3_error(sb, "ext3_get_inode_block",
"bad inode number: %lu", ino);
if ((ino != EXT3_ROOT_INO && ino != EXT3_JOURNAL_INO &&
ino != EXT3_RESIZE_INO && ino < EXT3_FIRST_INO(sb)) ||
static struct vhost_vsock *vhost_vsock_get(u32 guest_cid)
{
struct vhost_vsock *vsock;
spin_lock_bh(&vhost_vsock_lock);
vsock = __vhost_vsock_get(guest_cid);
spin_unlock_bh(&vhost_vsock_lock);
return vsock;
}
list_for_each_entry(vsock, &vhost_vsock_list, list) {
list_del(&vsock->list);
return -ENODEV;
return 0;
RTL_W16(RxMaxSize, 16383);
rtl_set_rx_max_size(ioaddr);
rtl_set_rx_max_size(ioaddr);
rtl_set_rx_max_size(ioaddr);
timeo = unix_wait_for_peer(other, timeo);
err = sock_intr_errno(timeo);
if (signal_pending(current))
goto out_free;
goto restart;
if (sock_flag(other, SOCK_DEAD)) {
if (unix_peer(other) != sk && unix_recvq_full(other)) {
if (!timeo) {
err = -EAGAIN;
goto out_unlock;
unix_state_lock(sk);
if (CPUCLOCK_WHICH(which_clock) == CPUCLOCK_SCHED) {
tp->tv_sec = div_long_long_rem(cpu.sched,
NSEC_PER_SEC, &tp->tv_nsec);
} else {
}
/*
* (long)X = ((long long)divs) / (long)div
* (long)rem = ((long long)divs) % (long)div
*
* Warning, this will do an exception if X overflows.
*/
#define div_long_long_rem(a, b, c) div_ll_X_l_rem(a, b, c)
static inline long div_ll_X_l_rem(long long divs, long div, long *rem)
{
long dum2;
asm("divl %2":"=a"(dum2), "=d"(*rem)
: "rm"(div), "A"(divs));
return dum2;
}
u64 nsec = (u64)jiffies * TICK_NSEC;
value->tv_sec = div_long_long_rem(nsec, NSEC_PER_SEC, &value->tv_nsec);
if (unlikely(nsec < 0))
set_normalized_timespec(&ts, ts.tv_sec, ts.tv_nsec);
ts.tv_sec = div_long_long_rem_signed(nsec, NSEC_PER_SEC, &ts.tv_nsec);
u64 nsec = (u64)jiffies * TICK_NSEC;
long tv_usec;
value->tv_sec = div_long_long_rem(nsec, NSEC_PER_SEC, &tv_usec);
tv_usec /= NSEC_PER_USEC;
value->tv_usec = tv_usec;
time_offset = div_long_long_rem_signed(time_offset,
long mtemp, save_adjust, rem;
&rem);
NTP_INTERVAL_FREQ,
sgi_clock_offset.tv_sec = tp->tv_sec - div_long_long_rem(nsec, NSEC_PER_SEC, &rem);
u64 rem;
when = timespec_to_ns(new_setting->it_value);
period = timespec_to_ns(new_setting->it_interval);
now = timespec_to_ns(n);
tp->tv_sec = div_long_long_rem(nsec, NSEC_PER_SEC, &tp->tv_nsec)
+ sgi_clock_offset.tv_sec;
return;
ns_to_timespec(cur_setting->it_interval, timr->it.mmtimer.incr * sgi_clock_period);
ns_to_timespec(cur_setting->it_value, (timr->it.mmtimer.expires - rtc_time())* sgi_clock_period);
unsigned long remainder;
l->min_time,
div_long_long_rem(l->sum_time, l->count, &remainder),
l->max_time);
long rem;
value->tv_sec = div_long_long_rem(nsec, NSEC_PER_SEC, &rem);
dput(upper);
if (upper->d_parent == upperdir) {
/* Don't let d_delete() think it can reset d_inode */
dget(upper);
struct dentry *upper = ovl_dentry_upper(dentry);
/* racing with another thread binding seems ok here */
skb_pull(chunk->skb,
chunk->chunk_end - chunk->skb->data);
/* Verify that we have at least chunk headers
* worth of buffer left.
*/
if (skb_headlen(chunk->skb) < sizeof(sctp_chunkhdr_t)) {
sctp_chunk_free(chunk);
chunk = queue->in_progress = NULL;
}
if (chunk->chunk_end < skb_tail_pointer(chunk->skb)) {
/* RFC 2960, Section 6.10  Bundling
*
* Partial chunks MUST NOT be placed in an SCTP packet.
* If the receiver detects a partial chunk, it MUST drop
* the chunk.
*
* Since the end of the chunk is past the end of our buffer
* (which contains the whole packet, we can freely discard
* the whole packet.
*/
sctp_chunk_free(chunk);
chunk = queue->in_progress = NULL;
return NULL;
request->ssids[i].ssid_len = nla_len(attr);
if (list->head != list->tail)
kfree(list->hid_debug_buf);
if (!(list->hid_debug_buf = kzalloc(HID_DEBUG_BUFSIZE, GFP_KERNEL))) {
err = -ENOMEM;
buf[i];
list->tail = (list->tail + i) % HID_DEBUG_BUFSIZE;
}
unsigned i;
list_for_each_entry(list, &hdev->debug_list, node) {
for (i = 0; buf[i]; i++)
list->hid_debug_buf[(list->tail + i) % HID_DEBUG_BUFSIZE] =
signal_wake_up(t, t->jobctl & JOBCTL_LISTENING);
signal_wake_up(child, task_is_traced(child));
signal_wake_up(child, child->jobctl & JOBCTL_LISTENING);
signal_wake_up(child, true);
signal_wake_up(task, 1);
int copy_len;
int required_size = urb->transfer_buffer_length;
void oz_hcd_get_desc_cnf(void *hport, u8 req_id, int status, const u8 *desc,
int length, int offset, int total_size)
vhost_dev_init(dev, vqs, VHOST_NET_VQ_MAX);
vq->log = kmalloc_array(UIO_MAXIOV, sizeof(*vq->log),
vq->heads = kmalloc_array(UIO_MAXIOV, sizeof(*vq->heads),
struct vhost_virtqueue **vqs, int nvqs)
vhost_dev_init(&vsock->dev, vqs, ARRAY_SIZE(vsock->vqs));
return (pmd_flags(pte) & (_PAGE_PSE | _PAGE_PRESENT)) ==
int n;
if (!body->unit_size)
n = (len - sizeof(struct oz_multiple_fixed)+1)
int n;
if (!body->unit_size)
n = (len - sizeof(struct oz_multiple_fixed)+1)
int ret, prot_bytes;
goto err_cpus;
putname(nd->last.name);
putname(nd->last.name);
putname(nd->last.name);
pfm_smpl_buffer_alloc(struct task_struct *task, pfm_context_t *ctx, unsigned long rsize, void **user_vaddr)
ret = pfm_setup_buffer_fmt(current, ctx, ctx_flags, 0, req);
*outlen = utf8s_to_utf16s(name, len, (wchar_t *)outname);
int utf8s_to_utf16s(const u8 *s, int len, wchar_t *pwcs)
return 0;
a->act_cookie = kzalloc(sizeof(*a->act_cookie), GFP_KERNEL);
if (!a->act_cookie)
return -ENOMEM;
a->act_cookie->data = nla_memdup(tb[TCA_ACT_COOKIE], GFP_KERNEL);
if (!a->act_cookie->data) {
kfree(a->act_cookie);
return -ENOMEM;
a->act_cookie->len = nla_len(tb[TCA_ACT_COOKIE]);
int cklen = nla_len(tb[TCA_ACT_COOKIE]);
if (cklen > TC_COOKIE_MAX_SIZE) {
err = -EINVAL;
tcf_hash_release(a, bind);
goto err_mod;
}
if (nla_memdup_cookie(a, tb) < 0) {
err = -ENOMEM;
tcf_hash_release(a, bind);
goto err_mod;
if (tb[TCA_ACT_COOKIE]) {
pSMBr = (CLOSE_RSP *)pSMB;  /* BB removeme BB */
rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
(struct smb_hdr *) pSMBr, &bytes_returned, 0);
cifs_small_buf_release(pSMB);
CLOSE_RSP *pSMBr = NULL; /* BB removeme BB */
int bytes_returned;
(struct smb_hdr *) pSMBr, &bytes_returned, 1);
cifs_small_buf_release(pSMB);
cFYI(1, ("In CIFSSMBLock - timeout %d numLock %d", waitFlag, numLock));
timeout = -1; /* no response expected */
rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
timeout = 3;  /* blocking operation, no timeout */
(struct smb_hdr *) pSMBr, &bytes_returned, timeout);
struct smb_com_transaction2_sfi_rsp *pSMBr = NULL;
rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
(struct smb_hdr *) pSMBr, &bytes_returned, 0);
int bytes_returned = 0;
if (pSMB)
cifs_small_buf_release(pSMB);
pSMBr = (struct smb_com_transaction2_sfi_rsp *)pSMB;
0 /* not long op */, 0 /* do not log STATUS codes */ );
rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
(struct smb_hdr *) pSMBr, &bytes_returned, timeout);
timeout = 3;  /* blocking operation, no timeout */
(struct smb_hdr *) pSMBr, &bytes_returned, 1);
(struct smb_hdr *) pSMBr, &bytes_returned, -1);
cifs_small_buf_release(pSMB);
smb_buffer_response = (struct smb_hdr *)pSMB; /* BB removeme BB */
int length;
struct smb_hdr *smb_buffer_response;
rc = SendReceive(xid, ses, (struct smb_hdr *) pSMB,
smb_buffer_response, &length, 0);
&resp_buf_type, 0 /* not long op */, 1 /* log err */ );
CLOSE_RSP *pSMBr = NULL;
int bytes_returned;
pSMBr = (CLOSE_RSP *)pSMB; /* BB removeme BB */
rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
(struct smb_hdr *) pSMBr, &bytes_returned, 0);
cifs_small_buf_release(pSMB);
struct smb_com_transaction2_sfi_rsp *pSMBr = NULL;
int bytes_returned = 0;
pSMBr = (struct smb_com_transaction2_sfi_rsp *)pSMB;
rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
(struct smb_hdr *) pSMBr, &bytes_returned, 0);
cifs_small_buf_release(pSMB);
long_op, 0 /* do not log STATUS code */ );
} else {
smb_buffer_response = smb_buffer; /* BB removeme BB */
rc = SendReceive(xid, tcon->ses, smb_buffer, smb_buffer_response,
&length, 0);
if (smb_buffer)
cifs_small_buf_release(smb_buffer);
struct smb_hdr *smb_buffer_response; /* BB removeme BB */
int length;
long_op = 1;
long_op = 2; /* writes past end of file can take a long time */
long_op = FALSE; /* subsequent writes fast -
long_op = 2; /* writes past end of file can take a long time */
1);
long_op = 1;
long_op = FALSE; /* subsequent writes fast -
1);
midQ->resp_buf = NULL;  /* mark it so will not be freed
by DeleteMidQEntry */
/* wait for 15 seconds or until woken up due to response arriving or
due to last connection to this server being unmounted */
if (long_op == -1)
goto out;
else if (long_op == 2) /* writes past end of file can take loong time */
else if (long_op == 1)
else
timeout = 15 * HZ;
timeout = 15 * HZ;
else
rc = map_smb_to_linux_error(midQ->resp_buf, logError);
if (long_op == -1)
else if (long_op == 2) /* writes past end of file can take loong time */
else if (long_op == 1)
if (long_op < 3)
if (long_op == -1) {
&bytes_returned, 0);
rc = wait_for_free_request(ses, 3);
midQ->resp_buf = NULL;  /* mark it so will not be freed
by DeleteMidQEntry */
const int long_op, const int logError)
if (long_op == -1)
goto out;
else if (long_op == 2) /* writes past end of file can take loong time */
else if (long_op == 1)
else
timeout = 15 * HZ;
rc = map_smb_to_linux_error(midQ->resp_buf, logError);
0 /* not long op */, 1 /* log NT STATUS if any */ );
&bytes_returned, 1);
rc = SendReceive(xid, ses, smb_buffer, smb_buffer_response, &length, 0);
&bytes_returned, 1);
&bytes_returned, 1);
if (!range_is_allowed(p >> PAGE_SHIFT, count))
/*
* On ia64 if a page has been mapped somewhere as uncached, then
* it must also be accessed uncached by the kernel or data
* corruption may occur.
*/
ptr = xlate_dev_mem_ptr(p);
if (!ptr)
return -EFAULT;
remaining = copy_to_user(buf, ptr, sz);
unxlate_dev_mem_ptr(p, ptr);
*
* On x86, access has to be given to the first megabyte of ram because that area
* contains BIOS code and data regions used by X and dosemu and similar apps.
* Access has to be given to non-kernel-ram areas as well, these contain the PCI
* mmio resources as well as potential bios/acpi data regions.
if (pagenr < 256)
return 1;
if (iomem_is_exclusive(pagenr << PAGE_SHIFT))
if (!page_is_ram(pagenr))
return 1;
return 0;
}
if (oc->chosen && oc->chosen != (void *)-1UL) {
/*
* Give the killed process a good chance to exit before trying
* to allocate memory again.
*/
schedule_timeout_killable(1);
return (struct desc_struct *)(gdt_desc.address + desc_base);
if (ldt && sel < ldt->nr_entries)
desc = &ldt->entries[sel];
return desc;
static struct desc_struct *get_desc(unsigned short sel)
return NULL;
return get_desc_base(desc);
desc = get_desc(sel);
if (!desc)
struct desc_struct *desc;
if (desc->g)
limit = get_desc_limit(desc);
desc = get_desc(sel);
if (!desc)
struct desc_struct *desc;
case 0 ... sizeof(struct user_regs_struct): 
case 0 ... sizeof(struct user_regs_struct):
static void register_proc_table(ctl_table * table, struct proc_dir_entry *root)
register_proc_table(table->child, de);
register_proc_table(root_table, proc_sys_root);
return error;
tmp = tmp->next;
} while (tmp != &root_table_header.ctl_entry);
int error = parse_table(name, nlen, oldval, oldlenp, 
return -ENOTDIR;
list_del(&header->ctl_entry);
register_proc_table(table, proc_sys_root);
struct proc_dir_entry *de;
ssize_t error;
de = PDE(file->f_dentry->d_inode);
if (!de || !de->data)
return -ENOTDIR;
table = (struct ctl_table *) de->data;
if (!table || !table->proc_handler)
return -ENOTDIR;
op = (write ? 002 : 004);
if (ctl_perm(table, op))
return -EPERM;
res = count;
error = (*table->proc_handler) (table, write, file, buf, &res, ppos);
if (error)
return error;
return res;
static struct mm_struct *__check_mem_permission(struct task_struct *task)
{
struct mm_struct *mm;
mm = get_task_mm(task);
if (!mm)
return ERR_PTR(-EINVAL);
/*
* A task can always look at itself, in case it chooses
* to use system calls instead of load instructions.
*/
if (task == current)
return mm;
/*
* If current is actively ptrace'ing, and would also be
* permitted to freshly attach with ptrace now, permit it.
*/
if (task_is_stopped_or_traced(task)) {
int match;
rcu_read_lock();
match = (ptrace_parent(task) == current);
rcu_read_unlock();
if (match && ptrace_may_access(task, PTRACE_MODE_ATTACH))
return mm;
}
/*
* No one else is allowed.
*/
mmput(mm);
return ERR_PTR(-EPERM);
}
/*
* If current may access user memory in @task return a reference to the
* corresponding mm, otherwise ERR_PTR.
*/
return mm;
}
static struct mm_struct *check_mem_permission(struct task_struct *task)
{
struct mm_struct *mm;
int err;
/*
* Avoid racing if task exec's as we might get a new mm but validate
* against old credentials.
*/
err = mutex_lock_killable(&task->signal->cred_guard_mutex);
if (err)
return ERR_PTR(err);
mm = __check_mem_permission(task);
mutex_unlock(&task->signal->cred_guard_mutex);
copied = -ESRCH;
if (!task)
goto out_no_task;
copied = -ENOMEM;
out_no_task:
goto out_task;
out_mm:
mm = check_mem_permission(task);
copied = PTR_ERR(mm);
if (IS_ERR(mm))
goto out_free;
put_task_struct(task);
copied = -EIO;
if (file->private_data != (void *)((long)current->self_exec_id))
goto out_mm;
out_task:
mmput(mm);
struct task_struct *task = get_proc_task(file->f_path.dentry->d_inode);
out_free:
struct mm_struct *mm;
struct mm_struct *mm_for_maps(struct task_struct *task)
!ptrace_may_access(task, PTRACE_MODE_READ)) {
file->private_data = (void*)((long)current->self_exec_id);
struct nfs_open_context *nfs_find_open_context(struct inode *inode, struct rpc_cred *cred, int mode)
encode_share_access(xdr, arg->open_flags);
BUG();
static void encode_share_access(struct xdr_stream *xdr, int open_flags)
encode_share_access(xdr, arg->open_flags);
state = nfs4_do_open(dir, &path, openflags, NULL, cred);
nfs4_intent_set_file(nd, &path, state);
nfs4_close_sync(&path, state, openflags);
calldata->arg.open_flags = 0;
update_open_stateflags(state, open_flags);
__update_open_stateid(state, open_stateid, NULL, open_flags);
static int update_open_stateid(struct nfs4_state *state, nfs4_stateid *open_stateid, nfs4_stateid *delegation, int open_flags)
open_flags &= (FMODE_READ|FMODE_WRITE);
(deleg_cur->type & open_flags) != open_flags)
__update_open_stateid(state, open_stateid, &deleg_cur->stateid, open_flags);
nfs_set_open_stateid_locked(state, open_stateid, open_flags);
calldata->arg.open_flags = FMODE_READ;
calldata->arg.open_flags = FMODE_WRITE;
state = nfs4_do_open(dir, &path, flags, sattr, cred);
status = nfs4_intent_set_file(nd, &path, state);
nfs4_close_sync(&path, state, flags);
int delegation_type = 0;
nfs4_state_set_mode_locked(state, state->state | open_flags);
static void update_open_stateflags(struct nfs4_state *state, mode_t open_flags)
int delegation_type = 0;
if (can_open_cached(data->state, data->o_arg.open_flags & (FMODE_READ|FMODE_WRITE|O_EXCL)))
if (calldata->arg.open_flags == 0)
switch (mode & (FMODE_READ|FMODE_WRITE|O_EXCL)) {
nfs4_close_state(&opendata->path, newstate, openflags);
static int nfs4_open_recover_helper(struct nfs4_opendata *opendata, mode_t openflags, struct nfs4_state **res)
opendata = nfs4_opendata_alloc(&ctx->path, state->owner, 0, NULL);
nfs4_intent_set_file(nd, &path, state);
state = nfs4_do_open(dir, &path, nd->intent.open.flags, &attr, cred);
int open_mode = opendata->o_arg.open_flags & (FMODE_READ|FMODE_WRITE|O_EXCL);
if (can_open_cached(state, open_mode)) {
if (can_open_cached(state, open_mode)) {
update_open_stateflags(state, open_mode);
!can_open_delegated(delegation, open_mode)) {
if (update_open_stateid(state, NULL, &stateid, open_mode))
update_open_stateflags(state, open_flags);
static void __update_open_stateid(struct nfs4_state *state, nfs4_stateid *open_stateid, const nfs4_stateid *deleg_stateid, int open_flags)
nfs_set_open_stateid_locked(state, open_stateid, open_flags);
p->o_arg.open_flags = flags,
struct nfs4_state_owner *sp, int flags,
static void nfs_readdata_free(struct nfs_read_data *p)
struct nfs_read_data *rdata = data;
nfs_writedata_release(data);
nfs_readdata_release(calldata);
data->args.context = get_nfs_open_context(ctx);
data->args.context = get_nfs_open_context(ctx);
data->args.context = get_nfs_open_context(dreq->ctx);
nfs_commitdata_release(calldata);
static void nfs_writedata_free(struct nfs_write_data *p)
struct nfs_write_data *wdata = data;
: : "D" (fx), "m" (*fx), "a" (lmask), "d" (hmask)
: "memory");
: : "D" (fx), "m" (*fx), "a" (lmask), "d" (hmask)
: "0" (0)
asm volatile(xstate_fault
: : "D" (fx), "m" (*fx), "a" (lmask), "d" (hmask)
: "memory");
: : "D" (fx), "m" (*fx), "a" (lmask), "d" (hmask)
: "0" (0)
asm volatile(xstate_fault
: : "D" (fx), "m" (*fx), "a" (lmask), "d" (hmask)
asm volatile(xstate_fault
: : "D" (fx), "m" (*fx), "a" (lmask), "d" (hmask)
: "0" (0)
: "memory");
if (!iov[i].iov_len)
return -EINVAL;
if (opt && opt->is_strictroute && rt->rt_dst != rt->rt_gateway)
(opt && opt->srr) ? opt->faddr : ireq->rmt_addr,
struct ip_options *opt = inet_rsk(req)->opt;
int opt_size = sizeof(struct ip_options) + opt->optlen;
if (ireq->opt != NULL && ip_options_echo(ireq->opt, skb)) {
.daddr = (param->replyopts.srr ?
param->replyopts.faddr : iph->saddr),
if (ip_options_echo(&icmp_param->replyopts, skb))
if (ipc.opt->srr)
daddr = icmp_param->replyopts.faddr;
if (icmp_param->replyopts.optlen) {
ipc.opt = &icmp_param->replyopts;
if (ip_options_echo(&icmp_param.replyopts, skb_in))
ipc.opt = &icmp_param.replyopts;
room -= sizeof(struct iphdr) + icmp_param.replyopts.optlen;
struct ip_options *opt;
if (opt == NULL || opt->cipso == 0)
struct ip_options *opt = *opt_ptr;
opt = sk_inet->opt;
if (opt == NULL || opt->cipso == 0)
hdr_delta = cipso_v4_delopt(&sk_inet->opt);
struct ip_options *opt;
if (sk_inet->opt)
sk_conn->icsk_ext_hdr_len -= sk_inet->opt->optlen;
sk_conn->icsk_ext_hdr_len += opt->optlen;
opt = xchg(&sk_inet->opt, opt);
kfree(opt);
struct ip_options *opt = NULL;
memcpy(opt->__data, buf, buf_len);
opt->optlen = opt_len;
opt->optlen = opt_len;
opt->cipso = sizeof(struct iphdr);
struct ip_options *opt = NULL;
kfree(opt);
memcpy(opt->__data, buf, buf_len);
struct ip_options *opt;
opt = inet_sk(sk)->opt;
if (opt == NULL || opt->cipso == 0)
return -ENOMSG;
return cipso_v4_getattr(opt->__data + opt->cipso - sizeof(struct iphdr),
secattr);
newinet->opt = NULL;
sizeof(struct ip_options)+
inet->opt->optlen);
struct ip_options * opt = (struct ip_options *)optbuf;
if (inet->opt)
memcpy(optbuf, inet->opt,
if (inet->opt)
icsk->icsk_ext_hdr_len -= inet->opt->optlen;
icsk->icsk_ext_hdr_len += opt->optlen;
opt = xchg(&inet->opt, opt);
kfree(opt);
struct ip_options *opt = NULL;
if (ip_options_echo(dopt, skb)) {
struct ip_options *opt = &(IPCB(skb)->opt);
struct ip_options *dopt = NULL;
int opt_size = optlength(opt);
nexthop = inet->opt->faddr;
if (inet->opt)
inet_csk(sk)->icsk_ext_hdr_len = inet->opt->optlen;
if (inet->opt && inet->opt->srr) {
if (!inet->opt || !inet->opt->srr)
inet_csk(newsk)->icsk_ext_hdr_len = newinet->opt->optlen;
newinet->opt	      = ireq->opt;
if (newinet->opt)
kfree(inet->opt);
daddr = inet->opt->faddr;
if (inet->opt && inet->opt->srr)
if (inet->opt && inet->opt->srr)
daddr = inet->opt->faddr;
struct ip_options *opt = inet->opt;
daddr = opt->faddr;
if (opt && opt->srr)
daddr = ipc.opt->faddr;
if (!ipc.opt)
ipc.opt = inet->opt;
if (ipc.opt->srr) {
memcpy(opt->__data, data, optlen);
struct ip_options *opt = ip_options_get_alloc(optlen);
if (optlen && copy_from_user(opt->__data, data, optlen)) {
struct ip_options *opt = ip_options_get_alloc(optlen);
return kzalloc(sizeof(struct ip_options) + ((optlen + 3) & ~3),
opt->__data[optlen++] = IPOPT_END;
opt->optlen = optlen;
if (optlen && ip_options_compile(net, opt, NULL)) {
struct ip_options *sopt;
if (sopt->optlen == 0) {
dopt->optlen = 0;
}
ip_options_build(skb, opt, daddr, rt, 0);
iph->ihl += opt->optlen>>2;
if (opt && opt->optlen) {
skb_push(skb, sizeof(struct iphdr) + (opt ? opt->optlen : 0));
__be32 saddr, __be32 daddr, struct ip_options *opt)
if (ipc.opt->srr)
daddr = replyopts.opt.faddr;
struct {
struct ip_options	opt;
char			data[40];
} replyopts;
if (ip_options_echo(&replyopts.opt, skb))
if (replyopts.opt.optlen) {
if (opt && opt->is_strictroute && rt->rt_dst != rt->rt_gateway)
skb_push(skb, sizeof(struct iphdr) + (opt ? opt->optlen : 0));
if(opt && opt->srr)
daddr = opt->faddr;
if (opt && opt->optlen) {
iph->ihl += opt->optlen >> 2;
ip_options_build(skb, opt, inet->inet_daddr, rt, 0);
struct ip_options *opt = inet->opt;
memcpy(cork->opt, opt, sizeof(struct ip_options) + opt->optlen);
struct ip_options *opt;
if (!ipc.opt)
ipc.opt = inet->opt;
(ipc.opt && ipc.opt->is_strictroute)) {
if (ipc.opt && ipc.opt->srr) {
faddr = ipc.opt->faddr;
newinet->opt	   = ireq->opt;
nexthop = inet->opt->faddr;
if (inet->opt == NULL || !inet->opt->srr)
if (inet->opt != NULL)
if (inet->opt != NULL && inet->opt->srr) {
inet_csk(sk)->icsk_ext_hdr_len = inet->opt->optlen;
.rpc_cred = clp->cl_cb_conn.cb_cred
static struct rpc_cred *lookup_cb_cred(struct nfs4_cb_conn *cb)
return 0;
if (clp->cl_cb_conn.cb_cred) {
put_rpccred(clp->cl_cb_conn.cb_cred);
clp->cl_cb_conn.cb_cred = NULL;
}
strlcpy(uaddr->sa_data, dev->name, 15);
strlcpy(uaddr->sa_data, dev->name, 15);
if ((e->rule.mask[word] & bit) == bit &&
word = AUDIT_WORD(ctx->major);
bit  = AUDIT_BIT(ctx->major);
int word, bit;
io->io_cleanup = mem_cleanup;
return cap_vm_enough_memory(current->mm, pages);
static inline int security_vm_enough_memory_mm(struct mm_struct *mm, long pages)
static void reiserfs_put_super(struct super_block *s)
if (pt[6] & AX25_HBIT)
else
if ((tmp & ~mask) != PSW32_USER_BITS)
int fscrypt_get_crypt_info(struct inode *inode)
crypt_info->ci_keyring_key = keyring_key;
return 0;
down_read(&keyring_key->sem);
up_read(&keyring_key->sem);
up_read(&keyring_key->sem);
up_read(&keyring_key->sem);
if (res)
goto out;
key_put(ci->ci_keyring_key);
ret = fscrypt_get_crypt_info(dir);
dir_has_key = (ci != NULL);
struct fscrypt_info *ci;
ci = d_inode(dir)->i_crypt_info;
if (ci && ci->ci_keyring_key &&
(ci->ci_keyring_key->flags & ((1 << KEY_FLAG_INVALIDATED) |
(1 << KEY_FLAG_REVOKED) |
(1 << KEY_FLAG_DEAD))))
ci = NULL;
rc = cifs_posix_open(full_path, &newinode, nd->path.mnt,
mode, oflags, &oplock, &fileHandle, xid);
oflags = FMODE_READ;
cifs_sb->mnt_file_mode /* ignored */,
oflags, &oplock, &netfid, xid);
oflags, &oplock, &netfid, xid);
cifs_sb->mnt_file_mode /* ignored */,
tty_kref_put(tty);
/* Put the ref obtained in hvc_open() */
tty_kref_get(tty);
copylen = vnet_hdr.hdr_len;
int copylen;
pgprot_t prot = __get_dma_pgprot(attrs, pgprot_kernel);
insert_vm_struct(mm, vma);
out:
return retval;
char * name;
int i, ch, retval;
char tcomm[sizeof(current->comm)];
return 0;
regs->cs = __USER32_CS;
/*
* The early SET_PERSONALITY here is so that the lookup
* for the interpreter happens in the namespace of the 
* to-be-execed image.  SET_PERSONALITY can select an
* alternate root.
*
* However, SET_PERSONALITY is NOT allowed to switch
* this task into the new images's memory mapping
* policy - that is, TASK_SIZE must still evaluate to
* that which is appropriate to the execing application.
* This is because exit_mmap() needs to have TASK_SIZE
* evaluate to the size of the old image.
*
* So if (say) a 64-bit application is execing a 32-bit
* application it is the architecture's responsibility
* to defer changing the value of TASK_SIZE until the
* switch really is going to happen - do this in
* flush_thread().	- akpm
*/
SET_PERSONALITY(loc->elf_ex);
} else {
/* Executables without an interpreter also need a personality  */
SET_PERSONALITY(loc->elf_ex);
arch_pick_mmap_layout(current->mm);
write_lock_irq(&tasklist_lock);
write_lock_irq(&tasklist_lock);
write_lock_irq(&tasklist_lock);
write_lock_irq(&tasklist_lock);
O_CREAT | 2 | O_NOFOLLOW | O_LARGEFILE, 0600);
if (unlikely(len > ring->rx_buffersize)) {
if(put_user(0, ((char __user *) oldval) + len))
return -EFAULT;
l = strlen(table->data);
sizeof(u_int32_t)*ip_pkt_list_tot*ip_list_tot);
hold = vmalloc(sizeof(u_int32_t)*ip_pkt_list_tot*ip_list_tot);
memset(r_list[location].last_pkts,0,ip_pkt_list_tot*sizeof(u_int32_t));
memset(r_list[location].last_pkts,0,ip_pkt_list_tot*sizeof(u_int32_t));
memset(curr_table->table[count].last_pkts,0,ip_pkt_list_tot*sizeof(u_int32_t));
sig_none = (timr->it_sigev_notify & ~SIGEV_THREAD_ID) == SIGEV_NONE;
sigev_none = (timr->it_sigev_notify & ~SIGEV_THREAD_ID) == SIGEV_NONE;
if (hmacs->shmac_num_idents == 0 ||
hmacs->shmac_num_idents > SCTP_AUTH_NUM_HMACS) {
if (type_page) {
buf[rc] = '\0';
if (!ext4_valid_inum(sb, inode->i_ino))
ino == EXT4_USR_QUOTA_INO ||
ino == EXT4_GRP_QUOTA_INO ||
ino == EXT4_BOOT_LOADER_INO ||
(u32 *)open->op_verf.data, &open->op_truncate);
status = do_open_permission(rqstp, current_fh, open, MAY_NOP);
int *truncp)
if (mode > MPOL_MAX)
mntput(ns->proc_mnt);
if(dltmp.cardno < 0 || dltmp.cardno >= MAX_BOARDS)
if(len > sizeof(moxaBuff))
unsigned int random_variable = 0;
random_variable = get_random_int() & STACK_RND_MASK;
newbuf = krealloc(runtime->buffer, params->buffer_size,
GFP_KERNEL);
char *newbuf;
static int command_read(struct pci_dev *dev, int offset, u16 *value, void *data)
do {
if (!qdisc_restart(dev))
} while (!netif_queue_stopped(dev));
mm->context.user_psize = MMU_PAGE_4K;
mm->context.sllp = SLB_VSID_USER |
mmu_psize_defs[MMU_PAGE_4K].sllp;
}
(pte_val(*ptep) & _PAGE_NO_CACHE)) {
mm->context.user_psize = MMU_PAGE_4K;
mm->context.sllp = SLB_VSID_USER |
mmu_psize_defs[MMU_PAGE_4K].sllp;
get_paca()->context = mm->context;
slb_flush_and_rebolt();
#ifdef CONFIG_SPE_BASE
spu_flush_all_slbs(mm);
#endif
OUT_RING(MI_BATCH_BUFFER_START | (2 << 6));
OUT_RING(batch->start | MI_BATCH_NON_SECURE);
dev_priv->use_mi_batchbuffer_start = param.value;
} d_partitions[8];
for (i = 0 ; i < le16_to_cpu(label->d_npartitions); i++, partition++) {
if (sig == SIGCHLD &&
out:
pipe_buf_get(pipe, ibuf);
if (rem < len) {
pipe_unlock(pipe);
goto out;
}
buf->ops->get(pipe, buf);
pipe_buf_get(ipipe, ibuf);
pipe_buf_get(ipipe, ibuf);
indx, data, size, 1000);
indx, &data, 1, 1000);
indx, data, size, 100);
static int set_registers(pegasus_t *pegasus, __u16 indx, __u16 size, void *data)
static u_int16_t port, *portptr;
static u_int16_t port, *portptr;
/* deal with overflows */
if (unlikely(mm->vmacache_seqnum == 0))
vmacache_flush_all(mm);
* Flush vma caches for threads that share a given mm.
*
* The operation is safe because the caller holds the mmap_sem
* exclusively and other threads accessing the vma cache will
* have mmap_sem held at least for read, so no extra locking
* is required to maintain the vma cache.
*/
void vmacache_flush_all(struct mm_struct *mm)
{
struct task_struct *g, *p;
count_vm_vmacache_event(VMACACHE_FULL_FLUSHES);
/*
* Single threaded tasks need not iterate the entire
* list of process. We can avoid the flushing as well
* since the mm's seqnum was increased and don't have
* to worry about other threads' seqnum. Current's
* flush will occur upon the next lookup.
*/
if (atomic_read(&mm->mm_users) == 1)
return;
rcu_read_lock();
for_each_process_thread(g, p) {
/*
* Only flush the vmacache pointers as the
* mm seqnum is already set and curr's will
* be set upon invalidation when the next
* lookup is done.
*/
if (mm == p->mm)
vmacache_flush(p);
}
rcu_read_unlock();
}
/*
kfree(hx);
hx = kmalloc(sizeof(*hx), GFP_KERNEL);
if (!hx)
kfree(hx);
* User space process size. 47bits.
#define TASK_SIZE	(0x800000000000UL)
atomic_inc(&((struct bpf_prog *)raw)->aux->refcnt);
bpf_map_inc(raw, true);
atomic_inc(&map->refcnt);
bpf_map_inc(map, true);
atomic_inc(&prog->aux->refcnt);
rc = hex2bin(dst, src, j);
if (rc < 0)
pr_debug("CHAP string contains non hex digit symbols\n");
dst[j] = '\0';
return j;
}
static int chap_string_to_hex(unsigned char *dst, unsigned char *src, int len)
{
int j = DIV_ROUND_UP(len, 2), rc;
vmcs_write16(HOST_FS_SELECTOR, kvm_read_fs());    /* 22.2.4 */
vmcs_write16(HOST_GS_SELECTOR, kvm_read_gs());    /* 22.2.4 */
vmx->host_state.gs_sel = kvm_read_gs();
vmx->host_state.fs_sel = kvm_read_fs();
kvm_load_fs(vmx->host_state.fs_sel);
kvm_load_gs(vmx->host_state.gs_sel);
struct net_device *dev)
unsigned int max_frame = dev->mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;
rtl8169_set_rxbufsize(tp, dev);
if (optname == IPV6_RTHDR && opt->srcrt) {
/* Assignment of RIP may only fail in 64-bit mode */
if (ctxt->mode == X86EMUL_MODE_PROT64)
ops->get_segment(ctxt, &old_sel, &old_desc, NULL,
VCPU_SREG_CS);
if (rc != X86EMUL_CONTINUE) {
WARN_ON(ctxt->mode != X86EMUL_MODE_PROT64);
/* assigning eip failed; restore the old cs */
ops->set_segment(ctxt, old_sel, &old_desc, 0, VCPU_SREG_CS);
return rc;
}
unsigned short sel, old_sel;
struct desc_struct old_desc, new_desc;
const struct x86_emulate_ops *ops = ctxt->ops;
p->state == BR_STATE_FORWARDING)
if (p->state == BR_STATE_LEARNING ||
int err = inet_sk_rebuild_header(sk);
int crtc, ret = 0;
case -EISDIR:
if (IS_GETLK(cmd))
return nfs4_proc_getlk(state, F_GETLK, request);
if (request->fl_type == F_UNLCK)
return nfs4_proc_unlck(state, cmd, request);
if (addr->srose_ndigis > ROSE_MAX_DIGIS)
static int m88rs2000_frontend_attach(struct dvb_usb_adapter *d)
return dvb_usb_generic_rw(d, obuf, 2, NULL, 0, 0);
if (dvb_usb_generic_rw(d, obuf, 3, ibuf, 1, 0) < 0)
u8 obuf[3] = { 0xe, 0x80, 0 };
u8 ibuf[] = { 0 };
if (dvb_usb_generic_rw(d, obuf, 1, ibuf, 1, 0) < 0)
if (dvb_usb_generic_rw(d, obuf, 3, ibuf, 1, 0) < 0)
obuf[0] = 0xe;
obuf[1] = 0x02;
obuf[2] = 1;
if (dvb_usb_generic_rw(d, obuf, 3, ibuf, 1, 0) < 0)
obuf[0] = 0x51;
obuf[0] = 0xe;
obuf[1] = 0x83;
obuf[2] = 0;
if (dvb_usb_generic_rw(d, obuf, 3, ibuf, 1, 0) < 0)
obuf[0] = 0xe;
obuf[1] = 0x83;
obuf[2] = 1;
tsk->self_exec_id != tsk->parent_exec_id) &&
!capable(CAP_KILL))
if ((!fifo->skbuff->data[fifo->skbuff->len - 1])
&& (fifo->skbuff->len > 3)) {
req_event = kvm_check_request(KVM_REQ_EVENT, vcpu);
if (req_event)
kvm_make_request(KVM_REQ_EVENT, vcpu);
if (req_event || req_int_win) {
inject_pending_event(vcpu);
bool req_event;
/* enable NMI/IRQ window open exits if needed */
if (vcpu->arch.nmi_pending)
kvm_x86_ops->enable_nmi_window(vcpu);
else if (kvm_cpu_has_interrupt(vcpu) || req_int_win)
kvm_x86_ops->enable_irq_window(vcpu);
if (kvm_lapic_enabled(vcpu)) {
update_cr8_intercept(vcpu);
kvm_lapic_sync_to_vapic(vcpu);
}
}
kthread_stop(rc->uwbd.task);
p->ule_next_hdr += ext_len;
if (! p->ule_bridged) {
p->ule_sndu_type = ntohs( *(unsigned short *)p->ule_next_hdr );
p->ule_next_hdr += 2;
} else {
p->ule_sndu_type = ntohs( *(unsigned short *)(p->ule_next_hdr + ((p->ule_dbit ? 2 : 3) * ETH_ALEN)) );
/* This assures the extension handling loop will terminate. */
ext_len = hlen << 2;
p->ule_sndu_type = ntohs( *(unsigned short *)p->ule_next_hdr );
p->ule_next_hdr += 2;
static int (*ule_optional_ext_handlers[255])( struct dvb_net_priv *p ) = { NULL, };
if (l == -1) return -1;	/* Stop extension header processing and discard SNDU. */
TS_PACKET, DMX_TS_PES_OTHER,
timeout);
struct timespec timeout = { 0, 30000000 }; // 30 msec
ret = priv->tsfeed->set(priv->tsfeed, priv->pid,
/* BRIDGE SNDU handling sucks in draft-ietf-ipdvb-ule-03.txt.
* This has to be the last extension header, otherwise it won't work.
* Blame the authors!
goto sndu_done;
}
if (! priv->ule_bridged) {
skb_push( priv->ule_skb, ETH_ALEN + 2 );
ethh = (struct ethhdr *)priv->ule_skb->data;
memcpy( ethh->h_dest, ethh->h_source, ETH_ALEN );
memset( ethh->h_source, 0, ETH_ALEN );
ethh->h_proto = htons( priv->ule_sndu_type );
} else {
/* Skip the Receiver destination MAC address. */
skb_pull( priv->ule_skb, ETH_ALEN );
}
} else {
if (! priv->ule_bridged) {
skb_push( priv->ule_skb, ETH_HLEN );
/* Check continuity counter. */
memcpy( ethh->h_dest, dev->dev_addr, ETH_ALEN );
memset( ethh->h_source, 0, ETH_ALEN );
ethh->h_proto = htons( priv->ule_sndu_type );
} else {
/* skb is in correct state; nothing to do. */
"exptected %#x.\n", priv->ts_count, ts[3] & 0x0F, priv->tscc);
((struct dvb_net_priv *) dev->priv)->stats.rx_errors++;
((struct dvb_net_priv *) dev->priv)->stats.rx_frame_errors++;
((struct dvb_net_priv *) dev->priv)->stats.rx_packets++;
((struct dvb_net_priv *) dev->priv)->stats.rx_bytes += priv->ule_skb->len;
ts += TS_SZ;
priv->ts_count++;
if (*from_where > 181) {
ts += TS_SZ;
priv->ts_count++;
((struct dvb_net_priv *) dev->priv)->stats.rx_errors++;
((struct dvb_net_priv *) dev->priv)->stats.rx_length_errors++;
ethh = (struct ethhdr *)priv->ule_skb->data;
((struct dvb_net_priv *) dev->priv)->stats.rx_errors++;
((struct dvb_net_priv *) dev->priv)->stats.rx_crc_errors++;
((struct dvb_net_priv *) dev->priv)->stats.rx_errors++;
((struct dvb_net_priv *) dev->priv)->stats.rx_frame_errors++;
if (priv->ule_sndu_len > 32763) {
/* CRC32 was OK. Remove it from skb. */
priv->ule_skb->tail -= 4;
priv->ule_skb->len -= 4;
/* Filter on receiver's destination MAC address, if present. */
if (!priv->ule_dbit) {
/* The destination MAC address is the next data in the skb. */
if (memcmp( priv->ule_skb->data, dev->dev_addr, ETH_ALEN )) {
/* MAC addresses don't match.  Drop SNDU. */
// printk( KERN_WARNING "Dropping SNDU, MAC address.\n" );
dev_kfree_skb( priv->ule_skb );
if (olen == sizeof(rfc))
memcpy(&rfc, (void *)val, olen);
if (olen == sizeof(efs)) {
remote_efs = 1;
memcpy(&efs, (void *) val, olen);
}
if (!ext4_handle_valid(handle))
if (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
if (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
if (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
if (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
req->base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
ahash_def_finup_finish2(req, err);
ahash_op_unaligned_finish(areq, err);
ahash_op_unaligned_finish(areq, err);
ahash_op_unaligned_finish(req, err);
struct ahash_request_priv *priv = req->priv;
if (!err)
memcpy(priv->result, req->result,
crypto_ahash_digestsize(crypto_ahash_reqtfm(req)));
ahash_restore_req(req);
}
static void ahash_def_finup_done2(struct crypto_async_request *req, int err)
{
struct ahash_request *areq = req->data;
ahash_def_finup_finish2(areq, err);
tgt_net = get_target_net(skb, netnsid);
net = get_net_ns_by_id(sock_net(skb->sk), netnsid);
if (!netlink_ns_capable(skb, net->user_ns, CAP_NET_ADMIN)) {
ah.pad = 0;
if (chan && __rfcomm_get_listen_sock_by_addr(chan, &sa->rc_bdaddr)) {
bacpy(&rfcomm_pi(sk)->src, &sa->rc_bdaddr);
rfcomm_pi(sk)->channel = chan;
struct sockaddr_rc *sa = (struct sockaddr_rc *) addr;
int chan = sa->rc_channel;
int err = 0;
BT_DBG("sk %p %pMR", sk, &sa->rc_bdaddr);
if (addr_len)
*addr_len = sizeof(*sin);
if (addr_len)
*addr_len = sizeof(struct sockaddr_in6);
if (addr_len)
*addr_len = sizeof(*sin);
*/
if (addr_len)
*addr_len = sizeof(*sin);
/*
*	Check any passed addresses
memcpy(msg->msg_name, &sa, sizeof(struct sockaddr_pn));
if (msg->msg_name != NULL)
if (addr_len)
*addr_len = sizeof(sa);
struct sockaddr_in *sin;
struct sockaddr_in6 *sin6;
sin = (struct sockaddr_in *) msg->msg_name;
if (addr_len) {
if (family == AF_INET)
*addr_len = sizeof(*sin);
else if (family == AF_INET6 && addr_len)
*addr_len = sizeof(*sin6);
}
sin6 = (struct sockaddr_in6 *) msg->msg_name;
if (addr_len)
*addr_len=sizeof(*sin6);
while (readw(chip->DSPQ + JQS_wTail) != readw(chip->DSPQ + JQS_wHead)) {
u16 wTmp;
snd_msnd_eval_dsp_msg(chip,
readw(pwDSPQData + 2 * readw(chip->DSPQ + JQS_wHead)));
wTmp = readw(chip->DSPQ + JQS_wHead) + 1;
if (wTmp > readw(chip->DSPQ + JQS_wSize))
writew(0, chip->DSPQ + JQS_wHead);
else
writew(wTmp, chip->DSPQ + JQS_wHead);
schedule();
while (!kthread_should_stop()) {
if (try_to_freeze())
continue;
flush_signals(current);
}
if (!df) {
__ip_select_ident(iph, &rt->u.dst, 0);
} else {
iph->id = htons(inet->id++);
atalk_route_packet(skb, dev, ddp, len_hops, origlen);
return NET_RX_SUCCESS;
if (!dev)
return -ENODEV;
netif_rx(skb);  /* Send the SKB up to a higher place. */
return 0;
if (aarp_send_ddp(dev, skb, &usat->sat_addr, NULL) == -1)
kfree_skb(skb2);
/* else queued/sent above in the aarp queue */
if (aarp_send_ddp(dev, skb2,
&usat->sat_addr, NULL) == -1)
kfree_skb(skb);
/* else queued/sent above in the aarp queue */
static void atalk_route_packet(struct sk_buff *skb, struct net_device *dev,
struct ddpehdr *ddp, __u16 len_hops,
int origlen)
if (!nskb)
goto out;
if (skb && aarp_send_ddp(rt->dev, skb, &ta, NULL) == -1)
goto free_it;
out:
return;
if(aarp_send_ddp(rt->dev, skb, &rt->at, NULL) < 0)
dev_kfree_skb(skb);
char __user *optval, int optlen)
int optname, char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
int optname, char __user *optval, int optlen)
char __user *optval, int optlen)
int optname, char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int len)
char *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
int optname, char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen);
char __user *optval, int optlen)
char __user *optval, int optlen)
int optname, char __user *optval, int optlen)
char __user *optval, int optlen)
int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
int len)
int val, char __user *opt, int len)
char __user *optval, int optlen)
void __user *optval,int optlen)
char __user *optval, int optlen)
int optname, char __user *optval, int optlen)
char __user *optval, int optlen,
int (*setsockopt)(struct sock *,int,int,char __user *,int))
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
void __user *optval,int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
int lvl, int opt, char __user *ov, int ol)
char __user *optval, int optlen)
void __user *optval,int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
int optlen)
char __user *optval,
int optlen)
char __user *optval, int optlen)
int optlen)
int optlen)
int optlen)
int optlen)
int optlen)
int optlen)
char __user *optval,
char __user *optval, int optlen)
int optlen)
int optlen)
int optlen)
char __user *optval, int optlen)
int optlen)
char __user *optval,
int optlen)
char __user *optval, int optlen)
char __user *optval,
int optlen)
int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen)
char __user *optval, int optlen,
return 0;
/* There is not enough support do UPD LSO,
* so follow normal path
*/
kfree_skb(skb);
return err;
}
err = skb_append_datato_frags(sk,skb, getfrag, from,
(length - transhdrlen));
if (!err) {
struct frag_hdr fhdr;
ret = copy_to_user(param, ptr, sizeof(*ptr));
if (sctp_wspace(asoc) <= 0) {
*state = HT_AGG_STATE_OPERATIONAL;
static int ___ieee80211_stop_tx_ba_session(struct sta_info *sta, u16 tid,
enum ieee80211_back_parties initiator)
#ifdef CONFIG_MAC80211_HT_DEBUG
printk(KERN_DEBUG "Tx BA session stop requested for %pM tid %u\n",
*state = HT_AGG_STATE_OPERATIONAL;
#endif /* CONFIG_MAC80211_HT_DEBUG */
sta->sta.addr, tid);
struct ieee80211_local *local = sdata->local;
WLAN_BACK_RECIPIENT);
sta->ampdu_mlme.tid_state_tx[tid] =
HT_AGG_STATE_OPERATIONAL;
ieee80211_stop_tx_ba_session(&local->hw, sta->sta.addr, tid,
trace_kvm_mmio(KVM_TRACE_MMIO_WRITE, bytes, gpa, *(u64 *)val);
vcpu->mmio_fragments[0].gpa, *(u64 *)val);
trace_kvm_mmio(KVM_TRACE_MMIO_READ, n, addr, *(u64 *)v);
if (copy_from_user(description, _description, dlen + 1) != 0)
if (copy_from_user(description, _description, dlen + 1) != 0)
if (copy_from_user(name, _name, nlen + 1) != 0)
struct net *net = dev_net(skb_dst(skb)->dev);
if (!iph)
TYPE_SCTP_FUNC(sctp_sf_tabort_8_4_8), \
TYPE_SCTP_FUNC(sctp_sf_tabort_8_4_8), \
TYPE_SCTP_FUNC(sctp_sf_tabort_8_4_8), \
TYPE_SCTP_FUNC(sctp_sf_tabort_8_4_8), \
TYPE_SCTP_FUNC(sctp_sf_tabort_8_4_8), \
TYPE_SCTP_FUNC(sctp_sf_tabort_8_4_8), \
return sctp_sf_ootb(ep, asoc, type, arg, commands);
return sctp_sf_abort_violation(asoc, arg, commands, err_str,
return sctp_sf_abort_violation(asoc, arg, commands, err_str,
/* Break out if chunk length is less then minimal. */
break;
ch_end = ((__u8 *)ch) + WORD_ROUND(ntohs(ch->length));
if (ch_end > skb_tail_pointer(skb))
break;
return sctp_sf_abort_violation(asoc, arg, commands, err_str,
commands);
return SCTP_DISPOSITION_VIOLATION;
/* Make sure that the INIT-ACK chunk has a valid length */
if (!sctp_chunk_length_valid(chunk, sizeof(sctp_initack_chunk_t)))
return sctp_sf_violation_chunklen(ep, asoc, type, arg,
return sctp_sf_abort_violation(asoc, arg, commands, err_str,
if (!sctp_vtag_verify_either(chunk, asoc))
return sctp_sf_pdiscard(ep, asoc, type, arg, commands);
return SCTP_DISPOSITION_VIOLATION;
__futex_atomic_op1(LOCK_PREFIX "xaddl %0, %2", ret, oldval,
}
if (addr_len)
if (addr_len)
*addr_len = sizeof(struct sockaddr_in6);
if (addr_len)
*addr_len = sizeof(*sin);
*/
if (addr_len)
*addr_len = sizeof(*sin);
/*
*	Check any passed addresses
struct sockaddr_in *sin;
struct sockaddr_in6 *sin6;
sin = (struct sockaddr_in *) msg->msg_name;
if (addr_len) {
if (family == AF_INET)
*addr_len = sizeof(*sin);
else if (family == AF_INET6 && addr_len)
*addr_len = sizeof(*sin6);
}
sin6 = (struct sockaddr_in6 *) msg->msg_name;
if (addr_len)
*addr_len=sizeof(*sin6);
csum = csum_sub(csum,
csum_partial(skb_transport_header(skb) + tlen,
offset, 0));
if (offset != 0)
list_del(&f->list);
dev_remove_pack(&f->prot_hook);
fanout_release_data(f);
kfree(f);
if (po->rollover)
kfree_rcu(po->rollover, rcu);
f = po->fanout;
if (!f)
return;
po->fanout = NULL;
if (atomic_dec_and_test(&f->sk_ref)) {
mutex_unlock(&fanout_mutex);
if (err) {
return -EINVAL;
kfree(po->rollover);
return -EALREADY;
po->rollover = kzalloc(sizeof(*po->rollover), GFP_KERNEL);
if (!po->rollover)
return -ENOMEM;
atomic_long_set(&po->rollover->num, 0);
atomic_long_set(&po->rollover->num_huge, 0);
atomic_long_set(&po->rollover->num_failed, 0);
mutex_lock(&fanout_mutex);
/*
* We really can take anything the user throws at us
* but let's pick a nice big number to tell the tty
* layer that we have lots of free space
*/
return 2048;
return 0;
/* 
* We can't really account for how much data we
* have sent out, but hasn't made it through to the
* device, so just tell the tty layer that everything
* is flushed.
*/
enum ctx_state prev_state;
prev_state = exception_enter();
X86_TRAP_SS, SIGBUS) != NOTIFY_STOP) {
preempt_conditional_sti(regs);
do_trap(X86_TRAP_SS, SIGBUS, "stack segment", regs, error_code, NULL);
preempt_conditional_cli(regs);
}
exception_exit(prev_state);
if (off >= src->i_size || off + len > src->i_size)
if (!(file->f_mode & FMODE_WRITE))
return 0;
po->tp_version = val;
if (po->rx_ring.pg_vec || po->tx_ring.pg_vec)
return -EBUSY;
lock_sock(sk);
release_sock(sk);
*errp = sctp_make_op_error_space(asoc, chunk, payload_len);
if (*errp) {
sctp_init_cause(*errp, SCTP_ERROR_PROTO_VIOLATION,
sizeof(error) + sizeof(sctp_paramhdr_t));
sctp_addto_chunk(*errp, sizeof(error), error);
sctp_addto_param(*errp, sizeof(sctp_paramhdr_t), param);
}
static const char error[] = "The following parameter had invalid length:";
size_t		payload_len = WORD_ROUND(sizeof(error)) +
sizeof(sctp_paramhdr_t);
return sctp_sf_violation_paramlen(ep, asoc, type,
(void *)&err_param, commands);
return sctp_sf_violation_paramlen(ep, asoc, type,
(void *)&err_param, commands);
return sctp_sf_violation_paramlen(ep, asoc, type,
(void *)&err_param, commands);
return sctp_sf_violation_paramlen(ep, asoc, type,
if (desc->checkmode) {
INIT_WORK(&chunk->map_extend_work, pcpu_map_extend_workfn);
chunk->map_used + PCPU_ATOMIC_MAP_MARGIN_LOW &&
pcpu_async_enabled)
schedule_work(&chunk->map_extend_work);
if (new_alloc)
pcpu_extend_area_map(chunk, new_alloc);
}
static void pcpu_map_extend_workfn(struct work_struct *work)
{
struct pcpu_chunk *chunk = container_of(work, struct pcpu_chunk,
map_extend_work);
int new_alloc;
spin_lock_irq(&pcpu_lock);
new_alloc = pcpu_need_to_extend(chunk, false);
spin_unlock_irq(&pcpu_lock);
old_name = fsnotify_oldname_init(old_dentry->d_name.name);
const unsigned char *old_name;
fsnotify_oldname_free(old_name);
fsnotify_move(old_dir, new_dir, old_name, is_dir,
old_name = fsnotify_oldname_init(old_dentry->d_name.name);
const char *old_name;
fsnotify_oldname_free(old_name);
fsnotify_oldname_free(old_name);
fsnotify_move(d_inode(old_dir), d_inode(new_dir), old_name,
#if defined(CONFIG_FSNOTIFY)	/* notify helpers */
/*
* fsnotify_oldname_init - save off the old filename before we change it
*/
static inline const unsigned char *fsnotify_oldname_init(const unsigned char *name)
{
return kstrdup(name, GFP_KERNEL);
}
/*
* fsnotify_oldname_free - free the name we got from fsnotify_oldname_init
*/
static inline void fsnotify_oldname_free(const unsigned char *old_name)
{
}
#endif	/*  CONFIG_FSNOTIFY */
#if defined(CONFIG_FSNOTIFY)	/* notify helpers */
/*
* fsnotify_oldname_init - save off the old filename before we change it
*/
static inline void fsnotify_oldname_free(const unsigned char *old_name)
{
kfree(old_name);
}
#else	/* CONFIG_FSNOTIFY */
kenter("%%%d,%s,'%s',%zu",
key->serial, key->description, data, datalen);
static inline bool cfs_rq_is_decayed(struct cfs_rq *cfs_rq)
{
if (cfs_rq->load.weight)
return false;
if (cfs_rq->avg.load_sum)
return false;
if (cfs_rq->avg.util_sum)
return false;
if (cfs_rq->avg.runnable_load_sum)
return false;
return true;
}
for_each_leaf_cfs_rq_safe(rq, cfs_rq, pos) {
list_del_leaf_cfs_rq(cfs_rq);
/*
* There can be a lot of idle CPU cgroups.  Don't let fully
* decayed cfs_rqs linger on the list.
*/
if (cfs_rq_is_decayed(cfs_rq))
struct cfs_rq *cfs_rq, *pos;
if (cifs_sb->tcon->ses->capabilities & CAP_UNIX)
else {
(oplock & CIFS_CREATE_ACTION))
else {
tsk->signal->flags |= SIGNAL_STOP_DEQUEUED;
buf_to_pages(buf, buflen, arg.acl_pages, &arg.acl_pgbase);
int ret;
if (vmx_set_msr(vcpu, &msr) != 0) {
static bool gc_in_progress = false;
return retval;
}
/* Calculate the size (in bytes) occupied by the data of an iovec.  */
static inline size_t get_user_iov_size(struct iovec *iov, int iovlen)
{
size_t retval = 0;
for (; iovlen > 0; --iovlen) {
retval += iov->iov_len;
iov++;
}
payoff = payload;
for (; iovlen > 0; --iovlen) {
if (copy_from_user(payoff, iov->iov_base,iov->iov_len))
goto err_copy;
payoff += iov->iov_len;
iov++;
}
const struct sctp_chunk *chunk,
const struct msghdr *msg)
void *payload = NULL, *payoff;
size_t paylen = 0;
struct iovec *iov = NULL;
int iovlen = 0;
if (msg) {
iov = msg->msg_iov;
iovlen = msg->msg_iovlen;
paylen = get_user_iov_size(iov, iovlen);
}
retval = sctp_make_abort(asoc, chunk, sizeof(sctp_errhdr_t) + paylen);
payload = kmalloc(paylen, GFP_ATOMIC);
sctp_primitive_ABORT(asoc, msg);
struct msghdr *msg = arg;
struct sctp_chunk *abort;
/* Generate ABORT chunk to send the peer */
abort = sctp_make_abort_user(asoc, NULL, msg);
if (!abort)
retval = SCTP_DISPOSITION_NOMEM;
else
sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(abort));
struct msghdr *msg = arg;
struct sctp_chunk *abort;
/* Generate ABORT chunk to send the peer.  */
abort = sctp_make_abort_user(asoc, NULL, msg);
if (!abort)
retval = SCTP_DISPOSITION_NOMEM;
else
sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(abort));
final_p = fl6_update_dst(&fl6, np->opt, &final);
err = ip6_xmit(sk, skb, &fl6, np->opt, np->tclass);
icsk->icsk_ext_hdr_len = (np->opt->opt_flen +
np->opt->opt_nflen);
final_p = fl6_update_dst(&fl6, np->opt, &final);
if (np->opt != NULL)
len = ipv6_getsockopt_sticky(sk, np->opt,
optname, optval, len);
opt = xchg(&np->opt, NULL);
if (opt)
sock_kfree_s(sk, opt, opt->tot_len);
if (opt)
sock_kfree_s(sk, opt, opt->tot_len);
opt = ipv6_renew_options(sk, np->opt, optname,
if (opt)
sock_kfree_s(sk, opt, opt->tot_len);
opt = xchg(&inet6_sk(sk)->opt, opt);
final_p = fl6_update_dst(&fl6, np->opt, &final);
if (np->opt)
icsk->icsk_ext_hdr_len = (np->opt->opt_flen +
np->opt->opt_nflen);
final_p = fl6_update_dst(&fl6, np->opt, &final);
err = ip6_xmit(sk, skb, fl6, np->opt, np->tclass);
if (newnp->opt)
inet_csk(newsk)->icsk_ext_hdr_len = (newnp->opt->opt_nflen +
newnp->opt->opt_flen);
if (np->opt)
newnp->opt = ipv6_dup_options(newsk, np->opt);
if (opt)
sock_kfree_s(sk, opt, opt->tot_len);
opt = xchg(&np->opt, NULL);
final_p = fl6_update_dst(&fl6, np->opt, &final);
if (!opt)
opt = np->opt;
final_p = fl6_update_dst(fl6, np->opt, &final);
final_p = fl6_update_dst(fl6, np->opt, &final);
res = ip6_xmit(sk, skb, &fl6, np->opt, np->tclass);
if (!opt)
opt = np->opt;
if (opt == NULL)
opt = np->opt;
static void buf_to_pages(const void *buf, size_t buflen,
struct page **pages, unsigned int *pgbase)
{
const void *p = buf;
*pgbase = offset_in_page(buf);
p -= *pgbase;
while (p < buf + buflen) {
*(pages++) = virt_to_page(p);
p += PAGE_CACHE_SIZE;
}
}
memcpy(buf, resp_buf, res.acl_len);
ret = res.acl_len;
if (localpage)
__free_page(localpage);
struct page *pages[NFS4ACL_MAXPAGES];
struct page *localpage = NULL;
int ret;
if (buflen < PAGE_SIZE) {
/* As long as we're doing a round trip to the server anyway,
* let's be prepared for a page of acl data. */
localpage = alloc_page(GFP_KERNEL);
resp_buf = page_address(localpage);
if (localpage == NULL)
return -ENOMEM;
args.acl_pages[0] = localpage;
args.acl_pgbase = 0;
args.acl_len = PAGE_SIZE;
} else {
resp_buf = buf;
buf_to_pages(buf, buflen, args.acl_pages, &args.acl_pgbase);
ret = nfs4_call_sync(NFS_SERVER(inode)->client, NFS_SERVER(inode), &msg, &args.seq_args, &res.seq_res, 0);
if (res.acl_len > args.acl_len)
nfs4_write_cached_acl(inode, NULL, res.acl_len);
nfs4_write_cached_acl(inode, resp_buf, res.acl_len);
if (res.acl_len > buflen)
if (localpage)
size_t *acl_len)
*acl_len = attrlen;
__be32 *savep;
*acl_len = 0;
dprintk("NFS: server cheating in getattr"
" acl reply: attrlen %u > recvd %u\n",
if (iblock >= ee_block && iblock < ee_block + ee_len) {
#define in_range(b, first, len)	((b) >= (first) && (b) <= (first) + (len) - 1)
if (noblock)
return -EAGAIN;
/* starting over for a new packet */
if (noblock)
return -EAGAIN;
/* starting over for a new packet */
if (noblock)
return -EAGAIN;
/* starting over for a new packet */
if (io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
start = fbdev->fb_phys & PAGE_MASK;
len = PAGE_ALIGN((start & ~PAGE_MASK) + fbdev->fb_len);
off = vma->vm_pgoff << PAGE_SHIFT;
if ((vma->vm_end - vma->vm_start + off) > len) {
return -EINVAL;
}
off += start;
vma->vm_pgoff = off >> PAGE_SHIFT;
return io_remap_pfn_range(vma, vma->vm_start, off >> PAGE_SHIFT,
vma->vm_end - vma->vm_start,
vma->vm_page_prot);
unsigned int len;
unsigned long start=0, off;
if (vma->vm_pgoff > (~0UL >> PAGE_SHIFT)) {
return -EINVAL;
}
start = fbdev->fb_phys & PAGE_MASK;
len = PAGE_ALIGN((start & ~PAGE_MASK) + fbdev->fb_len);
int fasync_helper(int fd, struct file * filp, int on, struct fasync_struct **fapp)
if (clp->cl_nfsversion == 3) {
if (server->namelen == 0 || server->namelen > NFS3_MAXNAMLEN)
server->namelen = NFS3_MAXNAMLEN;
if (!(data->flags & NFS_MOUNT_NORDIRPLUS))
server->caps |= NFS_CAP_READDIRPLUS;
} else {
if (server->namelen == 0 || server->namelen > NFS2_MAXNAMLEN)
server->namelen = NFS2_MAXNAMLEN;
}
chip->data_buffer = kmalloc(TPM_BUFSIZE * sizeof(u8), GFP_KERNEL);
insn->code, insn->dst_reg, insn->imm);
static void print_bpf_insn(struct bpf_insn *insn)
verbose("(%02x) r%d = 0x%x\n",
} else if (BPF_MODE(insn->code) == BPF_IMM) {
print_bpf_insn(insn);
remote_efs = 1;
if (olen == sizeof(efs))
unsigned int nr_pages;
nr_pages = ((uaddr & ~PAGE_MASK) + count + ~PAGE_MASK) >> PAGE_SHIFT;
spin_lock_irqsave(&dev->lock, flags);
spin_unlock_irqrestore(&dev->lock, flags);
unsigned long flags;
spin_lock_init(&dev->lock);
spin_lock_irqsave(&dev->lock, flags);
spin_unlock_irqrestore(&dev->lock, flags);
spin_unlock_irqrestore(&dev->lock, flags);
unsigned long flags;
spin_unlock_irqrestore(&dev->lock, flags);
unsigned long flags;
spin_lock_irqsave(&dev->lock, flags);
snprintf(rcomp.type, CRYPTO_MAX_ALG_NAME, "%s", "compression");
memcpy(&ualg->cru_name, &alg->cra_name, sizeof(ualg->cru_name));
memcpy(&ualg->cru_driver_name, &alg->cra_driver_name,
sizeof(ualg->cru_driver_name));
memcpy(&ualg->cru_module_name, module_name(alg->cra_module),
CRYPTO_MAX_ALG_NAME);
snprintf(rl.type, CRYPTO_MAX_ALG_NAME, "%s", "larval");
snprintf(rpcomp.type, CRYPTO_MAX_ALG_NAME, "%s", "pcomp");
alg->cra_blkcipher.geniv ?: "<default>");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "blkcipher");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
snprintf(rhash.type, CRYPTO_MAX_ALG_NAME, "%s", "shash");
snprintf(rhash.type, CRYPTO_MAX_ALG_NAME, "%s", "ahash");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
alg->cra_ablkcipher.geniv ?: "<default>");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "ablkcipher");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "givcipher");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
alg->cra_ablkcipher.geniv ?: "<built-in>");
snprintf(raead.type, CRYPTO_MAX_ALG_NAME, "%s", "nivaead");
snprintf(raead.geniv, CRYPTO_MAX_ALG_NAME, "%s", aead->geniv);
snprintf(raead.type, CRYPTO_MAX_ALG_NAME, "%s", "aead");
snprintf(raead.geniv, CRYPTO_MAX_ALG_NAME, "%s",
aead->geniv ?: "<built-in>");
snprintf(rrng.type, CRYPTO_MAX_ALG_NAME, "%s", "rng");
unregister_pernet_subsys(&sctp_net_ops);
/* Initialize the control inode/socket for handling OOTB packets.  */
if ((status = sctp_ctl_sock_init(net))) {
pr_err("Failed to initialize the SCTP control sock\n");
static int __net_init sctp_net_init(struct net *net)
}
err_ctl_sock_init:
sctp_dbg_objcnt_exit(net);
sctp_proc_exit(net);
goto err_ctl_sock_init;
if ((sch->type == SCTP_CID_COOKIE_ACK 
&& count !=0 ) {
/* Cookie Ack/Echo chunks not the first OR 
Init / Init Ack / Shutdown compl chunks not the only chunks */
&& count !=0 ) {
/* Cookie Ack/Echo chunks not the first OR 
Init / Init Ack / Shutdown compl chunks not the only chunks */
if ((sch->type == SCTP_CID_COOKIE_ACK 
if (!prev || expand_stack(prev, addr))
BUG_ON(t->tgid != p->tgid);
static unsigned char mincore_page(struct address_space *mapping, pgoff_t pgoff)
{
unsigned char present = 0;
struct page *page;
/*
* When tmpfs swaps out a page from a file, any process mapping that
* file will not get a swp_entry_t in its pte, but rather it is like
* any other file mapping (ie. marked !present and faulted in with
* tmpfs's .fault). So swapped out tmpfs mappings are tested here.
*/
#ifdef CONFIG_SWAP
if (shmem_mapping(mapping)) {
page = find_get_entry(mapping, pgoff);
/*
* shmem/tmpfs may return swap: account for swapcache
* page too.
*/
if (xa_is_value(page)) {
swp_entry_t swp = radix_to_swp_entry(page);
page = find_get_page(swap_address_space(swp),
swp_offset(swp));
}
} else
page = find_get_page(mapping, pgoff);
#else
page = find_get_page(mapping, pgoff);
#endif
if (page) {
present = PageUptodate(page);
put_page(page);
}
return present;
}
walk->private += __mincore_unmapped_range(addr, end,
walk->vma, walk->private);
#endif
}
__mincore_unmapped_range(addr, end, vma, vec);
__mincore_unmapped_range(addr, addr + PAGE_SIZE,
vma, vec);
if (non_swap_entry(entry)) {
/*
* migration or hwpoison entries are always
* uptodate
*/
*vec = 1;
} else {
#ifdef CONFIG_SWAP
*vec = mincore_page(swap_address_space(entry),
swp_offset(entry));
#else
WARN_ON(1);
*vec = 1;
*dptr++ = 0xAA;
case FAC_NATIONAL:		/* National */
len = rose_parse_national(p + 1, facilities, facilities_len - 1);
if (len < 0)
return 0;
facilities_len -= len + 1;
p += len + 1;
break;
case FAC_CCITT:		/* CCITT */
len = rose_parse_ccitt(p + 1, facilities, facilities_len - 1);
if (len < 0)
return 0;
facilities_len -= len + 1;
p += len + 1;
break;
default:
printk(KERN_DEBUG "ROSE: rose_parse_facilities - unknown facilities family %02X\n", *p);
facilities_len--;
p++;
break;
}
} else
break;	/* Error in facilities format */
return 1;
if (facilities_len == 0)
while (facilities_len > 0) {
if (*p == 0x00) {
facilities_len--;
p++;
switch (*p) {
int len, res = 0;
src_addr  = (rose_address *)(skb->data + 9);
dest_addr = (rose_address *)(skb->data + 4);
len  = (((skb->data[3] >> 4) & 0x0F) + 1) >> 1;
len += (((skb->data[3] >> 0) & 0x0F) + 1) >> 1;
if (!rose_parse_facilities(skb->data + len + 4, &facilities)) {
if (!rose_parse_facilities(skb->data + len + 4, &facilities)) {
int n, len;
len  = (((skb->data[3] >> 4) & 0x0F) + 1) >> 1;
len += (((skb->data[3] >> 0) & 0x0F) + 1) >> 1;
if (priv->suspend)
net_get_random_once(&ip6_idents_hashrnd, sizeof(ip6_idents_hashrnd));
id = __ipv6_select_ident(net, ip6_idents_hashrnd, daddr, saddr);
static u32 ip6_idents_hashrnd __read_mostly;
hash = __ipv6_addr_jhash(dst, hashrnd);
hash = __ipv6_addr_jhash(src, hash);
static u32 __ipv6_select_ident(struct net *net, u32 hashrnd,
hash ^= net_hash_mix(net);
net_get_random_once(&ip6_proxy_idents_hashrnd,
sizeof(ip6_proxy_idents_hashrnd));
id = __ipv6_select_ident(net, ip6_proxy_idents_hashrnd,
static u32 ip6_proxy_idents_hashrnd __read_mostly;
&addrs[1], &addrs[0]);
return __br_mdb_ip_get(mdb, &br_dst, __br_ip4_hash(mdb, dst));
if (!mdb || br->multicast_disabled)
{
return __br_mdb_ip_get(mdb, dst, br_ip_hash(mdb, dst));
}
static struct net_bridge_mdb_entry *br_mdb_ip_get(
struct net_bridge_mdb_htable *mdb, struct br_ip *dst)
return __br_mdb_ip_get(mdb, &br_dst, __br_ip6_hash(mdb, dst));
dio = kmalloc(sizeof(*dio), GFP_KERNEL);
size = sprintf(buffer, "%lu\n", rbu_data.packetsize);
size = sprintf(buffer, "%s\n", image_type);
memset(uaddr, 0, *uaddrlen);
int rc = 0;
for (i = 0; i < DRM_VMW_MAX_SURFACE_FACES; ++i)
if (!(dev->flags & IFF_UP))
return NET_RX_DROP;
if (skb->len > (dev->mtu + dev->hard_header_len))
*	NET_RX_DROP     (packet was dropped)
if (po->fanout)
return -EINVAL;
|| !tb[CTA_PROTO_ICMP_CODE-1])
pipe->bufs = kzalloc(sizeof(struct pipe_buffer) * PIPE_DEF_BUFFERS, GFP_KERNEL);
pipe->buffers = PIPE_DEF_BUFFERS;
BUG_ON(tcp_skb_pcount(skb) < pcount);
if (mss_now < 48)
mss_now = 48;
else if (!skb_shift(skb, next_skb, next_skb_size))
swhash->online = true;
/*
* We can race with cpu hotplug code. Do not
* WARN if the cpu just got unplugged.
*/
WARN_ON_ONCE(swhash->online);
}
if (!head) {
swhash->online = false;
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
dvb_detach(&state->dib7000p_ops);
skb->data + CAPI_MSG_BASELEN + 6,
skb->data[CAPI_MSG_BASELEN + 5]);
skb->data + CAPI_MSG_BASELEN + 17,
skb->data[CAPI_MSG_BASELEN + 16]);
skb->data + CAPI_MSG_BASELEN + 15,
skb->data[CAPI_MSG_BASELEN + 14]);
int err;
skb = skb_recv_datagram(sk, 0, 0, &err);
down(&child->mm->context.sem);
desc = child->mm->context.ldt + (seg & ~7);
base = (desc[0] >> 16) | ((desc[1] & 0xff) << 16) | (desc[1] & 0xff000000);
/* 16-bit code segment? */
if (!((desc[1] >> 22) & 1))
addr &= 0xffff;
addr += base;
touch_pmd(vma, addr, pmd);
touch_pmd(vma, addr, pmd);
pud_t *pud)
/*
* We should set the dirty bit only for FOLL_WRITE but for now
* the dirty bit in the pud is meaningless.  And if the dirty
* bit will become meaningful and we'll only set it with
* FOLL_WRITE, an atomic set_bit will be required on the pud to
* set the young bit, instead of the current set_pud_at.
*/
_pud = pud_mkyoung(pud_mkdirty(*pud));
pud, _pud,  1))
touch_pud(vma, addr, pud);
boot_cpu_data.x86 == 6) {
switch (boot_cpu_data.x86_model) {
case INTEL_FAM6_SKYLAKE_MOBILE:
case INTEL_FAM6_SKYLAKE_DESKTOP:
case INTEL_FAM6_SKYLAKE_X:
case INTEL_FAM6_KABYLAKE_MOBILE:
case INTEL_FAM6_KABYLAKE_DESKTOP:
return true;
}
}
return false;
}
static bool __init is_skylake_era(void)
{
if (boot_cpu_data.x86_vendor == X86_VENDOR_INTEL &&
char *driver_override, *old = dev->driver_override, *cp;
static int srpt_rx_mgmt_fn_tag(struct srpt_send_ioctx *ioctx, u64 tag)
{
struct srpt_device *sdev;
struct srpt_rdma_ch *ch;
struct srpt_send_ioctx *target;
int ret, i;
ret = -EINVAL;
ch = ioctx->ch;
BUG_ON(!ch);
BUG_ON(!ch->sport);
sdev = ch->sport->sdev;
BUG_ON(!sdev);
spin_lock_irq(&sdev->spinlock);
for (i = 0; i < ch->rq_size; ++i) {
target = ch->ioctx_ring[i];
if (target->cmd.se_lun == ioctx->cmd.se_lun &&
target->cmd.tag == tag &&
srpt_get_cmd_state(target) != SRPT_STATE_DONE) {
ret = 0;
/* now let the target core abort &target->cmd; */
break;
}
}
spin_unlock_irq(&sdev->spinlock);
return ret;
}
if (!unconditional(&e->ip))
return memcmp(ip, &uncond, sizeof(uncond)) == 0;
if (s->target_offset == sizeof(struct ipt_entry) &&
t->verdict < 0 &&
unconditional(&s->ip)) {
t->verdict < 0 && unconditional(&e->arp)) ||
visited) {
if ((e->target_offset == sizeof(struct arpt_entry) &&
if (!unconditional(&e->arp))
return memcmp(arp, &uncond, sizeof(uncond)) == 0;
if ((e->target_offset == sizeof(struct ip6t_entry) &&
t->verdict < 0 &&
unconditional(&e->ipv6)) || visited) {
if (!unconditional(&e->ipv6))
return memcmp(ipv6, &uncond, sizeof(uncond)) == 0;
t->verdict < 0 &&
unconditional(&s->ipv6)) {
if (s->target_offset == sizeof(struct ip6t_entry) &&
msg->msg_namelen = sizeof(*sax);
if (!err) {
if (sat) {
sat->sat_family      = AF_APPLETALK;
struct sockaddr_at *sat = (struct sockaddr_at *)msg->msg_name;
sat->sat_addr.s_node = ddp->deh_snode;
sat->sat_addr.s_net  = ddp->deh_snet;
}
msg->msg_namelen = sizeof(*sat);
sat->sat_port        = ddp->deh_sport;
msg->msg_namelen = sizeof(*sipx);
#define arch_mmap_check	sparc_mmap_check
#define arch_mmap_check	sparc64_mmap_check
kvm_pit_load_count(kvm, 0, ps->channels[0].count, 0);
static void rd_release_device_space(struct rd_dev *rd_dev)
kfree(sg_table);
" %u pages in %u tables\n", rd_dev->rd_host->rd_host_id,
rd_dev->rd_dev_id, rd_dev->rd_page_count,
rd_dev->sg_table_count);
static int rd_build_device_space(struct rd_dev *rd_dev)
struct ext4_extent *ex, newex, orig_ex;
struct ext4_extent *ex1 = NULL;
struct ext4_extent *ex2 = NULL;
struct ext4_extent *ex3 = NULL;
struct ext4_extent_header *eh;
ext4_fsblk_t newblock;
int ret = 0;
int may_zeroout;
eh = path[depth].p_hdr;
newblock = map->m_lblk - ee_block + ext4_ext_pblock(ex);
ex2 = ex;
orig_ex.ee_block = ex->ee_block;
orig_ex.ee_len   = cpu_to_le16(ee_len);
ext4_ext_store_pblock(&orig_ex, ext4_ext_pblock(ex));
may_zeroout = ee_block + ee_len <= eof_block;
err = ext4_ext_get_access(handle, inode, path + depth);
if (err)
goto out;
if (ee_len <= 2*EXT4_EXT_ZERO_LEN && may_zeroout) {
err =  ext4_ext_zeroout(inode, &orig_ex);
goto fix_extent_len;
/* update the extent length and mark as initialized */
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = orig_ex.ee_len;
ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
ext4_ext_dirty(handle, inode, path + depth);
/* zeroed the full extent */
return allocated;
}
/* ex1: ee_block to map->m_lblk - 1 : uninitialized */
if (map->m_lblk > ee_block) {
ex1 = ex;
ex1->ee_len = cpu_to_le16(map->m_lblk - ee_block);
ext4_ext_mark_uninitialized(ex1);
ex2 = &newex;
}
/*
* for sanity, update the length of the ex2 extent before
* we insert ex3, if ex1 is NULL. This is to avoid temporary
* overlap of blocks.
*/
if (!ex1 && allocated > map->m_len)
ex2->ee_len = cpu_to_le16(map->m_len);
/* ex3: to ee_block + ee_len : uninitialised */
if (allocated > map->m_len) {
unsigned int newdepth;
/* If extent has less than EXT4_EXT_ZERO_LEN zerout directly */
if (allocated <= EXT4_EXT_ZERO_LEN && may_zeroout) {
/*
* map->m_lblk == ee_block is handled by the zerouout
* at the beginning.
* Mark first half uninitialized.
* Mark second half initialized and zero out the
* initialized extent
*/
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = cpu_to_le16(ee_len - allocated);
ext4_ext_mark_uninitialized(ex);
ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
ext4_ext_dirty(handle, inode, path + depth);
ex3 = &newex;
ex3->ee_block = cpu_to_le32(map->m_lblk);
ext4_ext_store_pblock(ex3, newblock);
ex3->ee_len = cpu_to_le16(allocated);
err = ext4_ext_insert_extent(handle, inode, path,
ex3, 0);
if (err == -ENOSPC) {
err =  ext4_ext_zeroout(inode, &orig_ex);
if (err)
goto fix_extent_len;
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = orig_ex.ee_len;
ext4_ext_store_pblock(ex,
ext4_ext_pblock(&orig_ex));
ext4_ext_dirty(handle, inode, path + depth);
/* blocks available from map->m_lblk */
return allocated;
} else if (err)
goto fix_extent_len;
/*
* We need to zero out the second half because
* an fallocate request can update file size and
* converting the second half to initialized extent
* implies that we can leak some junk data to user
* space.
*/
err =  ext4_ext_zeroout(inode, ex3);
if (err) {
/*
* We should actually mark the
* second half as uninit and return error
* Insert would have changed the extent
*/
depth = ext_depth(inode);
ext4_ext_drop_refs(path);
path = ext4_ext_find_extent(inode, map->m_lblk,
path);
if (IS_ERR(path)) {
err = PTR_ERR(path);
return err;
}
/* get the second half extent details */
ex = path[depth].p_ext;
err = ext4_ext_get_access(handle, inode,
path + depth);
if (err)
return err;
ext4_ext_mark_uninitialized(ex);
ext4_ext_dirty(handle, inode, path + depth);
return err;
}
/* zeroed the second half */
return allocated;
}
ex3 = &newex;
ex3->ee_block = cpu_to_le32(map->m_lblk + map->m_len);
ext4_ext_store_pblock(ex3, newblock + map->m_len);
ex3->ee_len = cpu_to_le16(allocated - map->m_len);
ext4_ext_mark_uninitialized(ex3);
err = ext4_ext_insert_extent(handle, inode, path, ex3, 0);
if (err == -ENOSPC && may_zeroout) {
err =  ext4_ext_zeroout(inode, &orig_ex);
if (err)
goto fix_extent_len;
/* update the extent length and mark as initialized */
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = orig_ex.ee_len;
ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
ext4_ext_dirty(handle, inode, path + depth);
/* zeroed the full extent */
/* blocks available from map->m_lblk */
return allocated;
} else if (err)
goto fix_extent_len;
/*
* The depth, and hence eh & ex might change
* as part of the insert above.
*/
newdepth = ext_depth(inode);
/*
* update the extent length after successful insert of the
* split extent
*/
ee_len -= ext4_ext_get_actual_len(ex3);
orig_ex.ee_len = cpu_to_le16(ee_len);
may_zeroout = ee_block + ee_len <= eof_block;
depth = newdepth;
ext4_ext_drop_refs(path);
path = ext4_ext_find_extent(inode, map->m_lblk, path);
if (IS_ERR(path)) {
err = PTR_ERR(path);
}
eh = path[depth].p_hdr;
ex = path[depth].p_ext;
if (ex2 != &newex)
ex2 = ex;
allocated = map->m_len;
/* If extent has less than EXT4_EXT_ZERO_LEN and we are trying
* to insert a extent in the middle zerout directly
* otherwise give the extent a chance to merge to left
*/
if (le16_to_cpu(orig_ex.ee_len) <= EXT4_EXT_ZERO_LEN &&
map->m_lblk != ee_block && may_zeroout) {
err =  ext4_ext_zeroout(inode, &orig_ex);
if (err)
goto fix_extent_len;
/* update the extent length and mark as initialized */
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = orig_ex.ee_len;
ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
ext4_ext_dirty(handle, inode, path + depth);
/* zero out the first half */
/* blocks available from map->m_lblk */
return allocated;
}
}
/*
* If there was a change of depth as part of the
* insertion of ex3 above, we need to update the length
* of the ex1 extent again here
*/
if (ex1 && ex1 != ex) {
ex1 = ex;
ex1->ee_len = cpu_to_le16(map->m_lblk - ee_block);
ext4_ext_mark_uninitialized(ex1);
ex2 = &newex;
}
/* ex2: map->m_lblk to map->m_lblk + maxblocks-1 : initialised */
ex2->ee_block = cpu_to_le32(map->m_lblk);
ext4_ext_store_pblock(ex2, newblock);
ex2->ee_len = cpu_to_le16(allocated);
if (ex2 != ex)
goto insert;
/*
* New (initialized) extent starts from the first block
* in the current extent. i.e., ex2 == ex
* We have to see if it can be merged with the extent
* on the left.
*/
if (ex2 > EXT_FIRST_EXTENT(eh)) {
/*
* To merge left, pass "ex2 - 1" to try_to_merge(),
* since it merges towards right _only_.
*/
ret = ext4_ext_try_to_merge(inode, path, ex2 - 1);
if (ret) {
err = ext4_ext_correct_indexes(handle, inode, path);
if (err)
goto out;
depth = ext_depth(inode);
ex2--;
}
* Try to Merge towards right. This might be required
* only when the whole extent is being written to.
* i.e. ex2 == ex and ex3 == NULL.
if (!ex3) {
ret = ext4_ext_try_to_merge(inode, path, ex2);
if (ret) {
err = ext4_ext_correct_indexes(handle, inode, path);
/* Mark modified extent as dirty */
err = ext4_ext_dirty(handle, inode, path + depth);
goto out;
insert:
err = ext4_ext_insert_extent(handle, inode, path, &newex, 0);
if (err == -ENOSPC && may_zeroout) {
err =  ext4_ext_zeroout(inode, &orig_ex);
if (err)
goto fix_extent_len;
/* update the extent length and mark as initialized */
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = orig_ex.ee_len;
ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
ext4_ext_dirty(handle, inode, path + depth);
/* zero out the first half */
return allocated;
} else if (err)
goto fix_extent_len;
ext4_ext_show_leaf(inode, path);
fix_extent_len:
ex->ee_block = orig_ex.ee_block;
ex->ee_len   = orig_ex.ee_len;
ext4_ext_store_pblock(ex, ext4_ext_pblock(&orig_ex));
ext4_ext_mark_uninitialized(ex);
ext4_ext_dirty(handle, inode, path + depth);
return err;
if (f2fs_sanity_check_ckpt(sbi))
pv_info.paravirt_enabled = 1;
int bytes = max_t(int, random_read_wakeup_thresh / 8,
min_t(int, nbytes, sizeof(tmp)));
if (getaddrs.addr_num <= 0) return -EINVAL;
spin_unlock_bh(&state->udp_table->hash[state->bucket].lock);
unsigned char type, void **ptr);
type, (void **)ptr)
if (header->bDescriptorType == type) {
if (header->bLength < 2) {
unsigned char type, void **ptr)
USB_DT_OTG, (void **) &desc);
skb->ip_summed = 1;
if (bprm->e_uid != current->uid)
file_permission(bprm->file, MAY_READ) ||
(bprm->interp_flags & BINPRM_FLAGS_ENFORCE_NONDUMP)) {
if (bprm->e_uid != current->euid || bprm->e_gid != current->egid || 
__mutex_trylock_slowpath);
debug_mutex_set_owner(lock, current_thread_info());
return __mutex_fastpath_trylock(&lock->count,
return __mutex_fastpath_lock_retval
mutex_acquire(&lock->dep_map, subclass, 0, ip);
mutex_remove_waiter(lock, &waiter, task_thread_info(task));
debug_mutex_set_owner(lock, task_thread_info(task));
mutex_acquire(&lock->dep_map, subclass, 0, ip);
mutex_remove_waiter(lock, &waiter, task_thread_info(task));
debug_mutex_set_owner(lock, task_thread_info(task));
debug_mutex_clear_owner(lock);
return __mutex_fastpath_lock_retval
debug_mutex_set_owner(lock, current_thread_info());
lock->owner = NULL;
void debug_mutex_set_owner(struct mutex *lock, struct thread_info *new_owner)
DEBUG_LOCKS_WARN_ON(lock->owner != current_thread_info());
static inline void debug_mutex_clear_owner(struct mutex *lock)
{
lock->owner = NULL;
}
p->parent_exec_id = p->self_exec_id;
else
if (clone_flags & (CLONE_PARENT|CLONE_THREAD))
/* Our parent execution domain becomes current domain
These must match for thread signalling to apply */
u8 smac[ETH_ALEN];
u8 alt_smac[ETH_ALEN];
u8 *psmac = smac;
u8 *palt_smac = alt_smac;
int is_iboe = ((rdma_node_get_transport(cm_id->device->node_type) ==
RDMA_TRANSPORT_IB) &&
(rdma_port_get_link_layer(cm_id->device,
ib_event->param.req_rcvd.port) ==
IB_LINK_LAYER_ETHERNET));
if (is_iboe) {
if (ib_event->param.req_rcvd.primary_path != NULL)
rdma_addr_find_smac_by_sgid(
&ib_event->param.req_rcvd.primary_path->sgid,
psmac, NULL);
else
psmac = NULL;
if (ib_event->param.req_rcvd.alternate_path != NULL)
rdma_addr_find_smac_by_sgid(
&ib_event->param.req_rcvd.alternate_path->sgid,
palt_smac, NULL);
else
palt_smac = NULL;
}
if (is_iboe)
ib_update_cm_av(cm_id, psmac, palt_smac);
unix_notinflight(scm->fp->fp[i]);
fp->f_cred->user->unix_inflight++;
void unix_inflight(struct file *fp)
fp->f_cred->user->unix_inflight--;
void unix_notinflight(struct file *fp)
if (test_thread_flag(TIF_MEMDIE) || fatal_signal_pending(current))
*
* Even if signal_pending(), we can't quit charge() loop without
* accounting. So, UNINTERRUPTIBLE is appropriate. But SIGKILL
* under OOM is always welcomed, use TASK_KILLABLE here.
schedule_timeout_uninterruptible(1);
prepare_to_wait(&memcg_oom_waitq, &owait.wait, TASK_KILLABLE);
return false;
static bool mem_cgroup_handle_oom(struct mem_cgroup *memcg, gfp_t mask,
int order)
/* Give chance to dying process */
schedule();
mem_cgroup_unmark_under_oom(memcg);
finish_wait(&memcg_oom_waitq, &owait.wait);
finish_wait(&memcg_oom_waitq, &owait.wait);
/* If oom, we never return -ENOMEM */
if (!oom) {
bool oom_check;
case CHARGE_OOM_DIE: /* Killed by OOM Killer */
css_put(&memcg->css);
goto bypass;
oom_check = false;
if (oom && !nr_oom_retries) {
oom_check = true;
nr_oom_retries = MEM_CGROUP_RECLAIM_RETRIES;
}
ret = mem_cgroup_do_charge(memcg, gfp_mask, batch, nr_pages,
oom_check);
struct zonelist *zonelist = node_zonelist(first_online_node,
GFP_KERNEL);
file_sb_list_del(file);
*/
static inline void __file_sb_list_add(struct file *file, struct super_block *sb)
{
struct list_head *list;
#ifdef CONFIG_SMP
int cpu;
cpu = smp_processor_id();
file->f_sb_list_cpu = cpu;
list = per_cpu_ptr(sb->s_files, cpu);
#else
list = &sb->s_files;
#endif
list_add(&file->f_u.fu_list, list);
}
/**
* file_sb_list_add - add a file to the sb's file list
* @file: file to add
* @sb: sb to add it to
*
* Use this function to associate a file with the superblock of the inode it
* refers to.
file_sb_list_del(file);
file_sb_list_del(file);
lg_lock_init(&files_lglock, "files_lglock");
void file_sb_list_add(struct file *file, struct super_block *sb)
{
if (likely(!(file->f_mode & FMODE_WRITE)))
return;
if (!S_ISREG(file_inode(file)->i_mode))
return;
lg_local_lock(&files_lglock);
__file_sb_list_add(file, sb);
lg_local_unlock(&files_lglock);
}
/**
* file_sb_list_del - remove a file from the sb's file list
* @file: file to remove
* @sb: sb to remove it from
*
* Use this function to remove a file from its superblock.
*/
void mark_files_ro(struct super_block *sb)
{
struct file *f;
lg_global_lock(&files_lglock);
do_file_list_for_each_entry(sb, f) {
if (!file_count(f))
continue;
if (!(f->f_mode & FMODE_WRITE))
continue;
spin_lock(&f->f_lock);
f->f_mode &= ~FMODE_WRITE;
spin_unlock(&f->f_lock);
if (file_check_writeable(f) != 0)
continue;
__mnt_drop_write(f->f_path.mnt);
file_release_write(f);
} while_file_list_for_each_entry;
lg_global_unlock(&files_lglock);
}
static inline int file_list_cpu(struct file *file)
{
#ifdef CONFIG_SMP
return file->f_sb_list_cpu;
#else
return smp_processor_id();
#endif
}
/* helper for file_sb_list_add to reduce ifdefs */
INIT_LIST_HEAD(&f->f_u.fu_list);
void file_sb_list_del(struct file *file)
{
if (!list_empty(&file->f_u.fu_list)) {
lg_local_lock_cpu(&files_lglock, file_list_cpu(file));
list_del_init(&file->f_u.fu_list);
lg_local_unlock_cpu(&files_lglock, file_list_cpu(file));
}
}
#ifdef CONFIG_SMP
/*
* These macros iterate all files on all CPUs for a given superblock.
* files_lglock must be held globally.
*/
#define do_file_list_for_each_entry(__sb, __file)		\
{								\
int i;							\
for_each_possible_cpu(i) {				\
struct list_head *list;				\
list = per_cpu_ptr((__sb)->s_files, i);		\
list_for_each_entry((__file), list, f_u.fu_list)
#define while_file_list_for_each_entry				\
}							\
}
#else
#define do_file_list_for_each_entry(__sb, __file)		\
{								\
struct list_head *list;					\
list = &(sb)->s_files;					\
list_for_each_entry((__file), list, f_u.fu_list)
#define while_file_list_for_each_entry				\
}
#endif
/**
*	mark_files_ro - mark all files read-only
*	@sb: superblock in question
*
*	All files are marked read-only.  We don't care about pending
*	delete files so this should be used in 'force' mode only.
*/
free_percpu(s->s_files);
#endif
#ifdef CONFIG_SMP
#ifdef CONFIG_SMP
s->s_files = alloc_percpu(struct list_head);
if (!s->s_files)
goto fail;
for_each_possible_cpu(i)
INIT_LIST_HEAD(per_cpu_ptr(s->s_files, i));
#else
INIT_LIST_HEAD(&s->s_files);
#endif
mark_files_ro(sb);
file_sb_list_del(f);
if (p->pid > 1 && !same_thread_group(p, current)) {
cFYI(1, ("Must sign - segFlags 0x%x", secFlags));
if (error)
if (p->flags & SIGNAL_GROUP_EXIT)
if (user_alloc && (mem->userspace_addr & (PAGE_SIZE - 1)))
ip_append_data(icmp_socket->sk, icmp_glue_bits, icmp_param,
icmp_param->data_len+icmp_param->head_len,
icmp_param->head_len,
ipc, rt, MSG_DONTWAIT);
if ((skb = skb_peek(&icmp_socket->sk->sk_write_queue)) != NULL) {
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst), IPSTATS_MIB_INHDRERRORS);
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst),
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst), IPSTATS_MIB_INTRUNCATEDPKTS);
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst), IPSTATS_MIB_INHDRERRORS);
req->ki_filp = file;
nested_vmx_ept_caps |= VMX_EPT_EXTENT_GLOBAL_BIT |
VMX_EPT_EXTENT_CONTEXT_BIT;
* Since invept is completely emulated we support both global
* and context invalidation independent of what host cpu
* supports
if (len < 0)
if (++l2cap_pi(sk)->conf_retry < L2CAP_CONF_MAX_RETRIES) {
char req[128];
/* It does not make sense to adjust L2CAP parameters
* that are currently defined in the spec. We simply
* resend config request that we sent earlier. It is
* stupid, but it helps qualification testing which
* expects at least some response from us. */
l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
l2cap_build_conf_req(sk, req), req);
goto done;
case TIOCGICOUNT:
ret = uart_get_count(state, uarg);
break;
icount.cts         = cnow.cts;
icount.dsr         = cnow.dsr;
icount.rng         = cnow.rng;
icount.dcd         = cnow.dcd;
icount.rx          = cnow.rx;
icount.tx          = cnow.tx;
icount.frame       = cnow.frame;
icount.overrun     = cnow.overrun;
icount.parity      = cnow.parity;
icount.brk         = cnow.brk;
icount.buf_overrun = cnow.buf_overrun;
return copy_to_user(icnt, &icount, sizeof(icount)) ? -EFAULT : 0;
static int uart_get_count(struct uart_state *state,
struct serial_icounter_struct __user *icnt)
case TIOCGICOUNT:
ret = uart_get_count(state, uarg);
break;
icount.cts         = cnow.cts;
icount.dsr         = cnow.dsr;
icount.rng         = cnow.rng;
icount.dcd         = cnow.dcd;
icount.rx          = cnow.rx;
icount.tx          = cnow.tx;
icount.frame       = cnow.frame;
icount.overrun     = cnow.overrun;
icount.parity      = cnow.parity;
icount.brk         = cnow.brk;
icount.buf_overrun = cnow.buf_overrun;
return copy_to_user(icnt, &icount, sizeof(icount)) ? -EFAULT : 0;
static int uart_get_count(struct uart_state *state,
struct serial_icounter_struct __user *icnt)
!inode_capable(inode, CAP_CHOWN))
!inode_capable(inode, CAP_CHOWN))
!inode_capable(inode, CAP_FSETID))
if (inode_capable(inode, CAP_FOWNER))
* Return true if current either has CAP_FOWNER to the inode, or
* owns the file.
!inode_capable(VFS_I(ip), CAP_FSETID))
if (inode_capable(inode, CAP_DAC_READ_SEARCH))
if (inode_capable(inode, CAP_DAC_READ_SEARCH))
if (inode_capable(inode, CAP_DAC_OVERRIDE))
if (inode_capable(inode, CAP_DAC_OVERRIDE))
return !inode_capable(inode, CAP_FOWNER);
struct trusted_key_payload *p = key->payload.data[0];
up_read(&oi->ip_alloc_sem);
static int ocfs2_dio_get_block(struct inode *inode, sector_t iblock,
down_read(&oi->ip_alloc_sem);
/* This is the fast path for re-write. */
ret = ocfs2_get_block(inode, iblock, bh_result, create);
if (nla->nla_len > A - skb->len)
if (__written_first_block(sbi, ri))
{
struct inode *i = file->f_path.dentry->d_inode;
return S_ISFIFO(i->i_mode) ? i->i_pipe : NULL;
}
static inline struct pipe_inode_info *get_pipe_info(struct file *file)
if (rc == 0)
acl = NULL;
umode_t mode = inode->i_mode;
rc = posix_acl_equiv_mode(acl, &mode);
if (rc < 0)
error = posix_acl_equiv_mode(acl, &inode->i_mode);
if (error < 0)
else {
inode->i_ctime = CURRENT_TIME_SEC;
mark_inode_dirty(inode);
if (error == 0)
acl = NULL;
}
ret = posix_acl_equiv_mode(acl, &new_mode);
if (ret < 0)
if (ret == 0)
acl = NULL;
rc = posix_acl_equiv_mode(acl, &inode->i_mode);
if (rc < 0)
if (rc == 0)
acl = NULL;
err = posix_acl_equiv_mode(acl, &inode->i_mode);
if (err < 0)
umode_t mode = inode->i_mode;
retval = posix_acl_equiv_mode(acl, &mode);
if (retval < 0)
else {
struct iattr iattr;
if (retval == 0) {
/*
* ACL can be represented
* by the mode bits. So don't
* update ACL.
*/
acl = NULL;
value = NULL;
size = 0;
}
/* Updte the mode bits */
iattr.ia_mode = ((mode & S_IALLUGO) |
(inode->i_mode & ~S_IALLUGO));
iattr.ia_valid = ATTR_MODE;
/* FIXME should we update ctime ?
* What is the following setxattr update the
* mode ?
v9fs_vfs_setattr_dotl(dentry, &iattr);
umode_t mode = inode->i_mode;
ret = posix_acl_equiv_mode(acl, &mode);
if (ret < 0)
return ret;
if (ret == 0)
acl = NULL;
if (nla->nla_len > A - skb->len)
if (nla->nla_len > A - skb->len)
if ((flag & CL_UNPRIVILEGED) && (mnt->mnt.mnt_flags & MNT_READONLY))
mnt->mnt.mnt_flags |= MNT_LOCK_READONLY;
nfca_poll->nfcid1_len = *data++;
nfcb_poll->sensb_res_len = *data++;
nfcf_poll->sensf_res_len = *data++;
nfcb_poll->attrib_res_len = *data++;
nfca_poll->rats_res_len = *data++;
if (count < sysex.len)
{
/*		printk(KERN_WARNING "MIDI Warning: Sysex record too short (%d<%d)\n", count, (int) sysex.len);*/
if(copy_from_user(&((char *) &sysex)[offs], &(addr)[offs], hdr_size - offs))
}
left = sysex.len;
src_offs = 0;
{
/*		  printk("MIDI Error: Invalid patch format (key) 0x%x\n", format);*/
}
{
/*		printk("MIDI Error: Patch header too short\n");*/
}
* Copy the header from user space but ignore the first bytes which have
* been transferred already.
int offs, int count, int pmgr_flag)
err = synth_devs[dev]->load_patch(dev, fmt, buf, p + 4, c, 0);
/*
* What the fuck is going on here?  We leave junk in the beginning
* of ins and then check the field pretty close to that beginning?
*/
if(copy_from_user(&((char *) &ins)[offs], addr + offs, sizeof(ins) - offs))
int offs, int count, int pmgr_flag)
spec.flags |= SMALL;
if (spec.field_width == -1) {
spec.field_width = default_width;
spec.flags |= ZEROPAD;
}
spec.base = 16;
return number(buf, end, (unsigned long) ptr, spec);
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = sizeof(*sipx);
else
msg->msg_namelen = 0;
if (sk->sk_shutdown & RCV_SHUTDOWN) {
msg->msg_namelen = 0;
}
msg->msg_namelen = 0;
msg.msg_name = (struct sockaddr *)&address;
msg.msg_namelen = sizeof(address);
msg->msg_namelen = 0;
m->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
m->msg_name = address;
if (!err) {
if (sat) {
sat->sat_family      = AF_APPLETALK;
struct sockaddr_at *sat = (struct sockaddr_at *)msg->msg_name;
sat->sat_addr.s_node = ddp->deh_snode;
sat->sat_addr.s_net  = ddp->deh_snet;
}
msg->msg_namelen = sizeof(*sat);
sat->sat_port        = ddp->deh_sport;
msg->msg_namelen = 0;
memset(srose, 0, msg->msg_namelen);
struct sockaddr_rose *srose = (struct sockaddr_rose *)msg->msg_name;
if (srose != NULL) {
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = sizeof(*sax);
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
kern_msg->msg_name = kern_address;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
if (msg->msg_namelen >= sizeof(struct sockaddr_mISDN)) {
msg->msg_namelen = sizeof(struct sockaddr_mISDN);
maddr = (struct sockaddr_mISDN *)msg->msg_name;
struct sockaddr_mISDN	*maddr;
} else {
if (msg->msg_namelen)
printk(KERN_WARNING "%s: too small namelen %d\n",
__func__, msg->msg_namelen);
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
sll = &PACKET_SKB_CB(skb)->sa.ll;
if (sock->type == SOCK_PACKET)
msg->msg_namelen = sizeof(struct sockaddr_pkt);
else
msg->msg_namelen = sll->sll_halen + offsetof(struct sockaddr_ll, sll_addr);
/*
struct sockaddr_ll *sll;
*	user program they can ask the device for its MTU anyway.
*	You lose any data beyond the buffer you gave. If it worries a
if (msg->msg_name)
/*
*	If the address length field is there to be filled in, we fill
*	it in now.
*/
msg->msg_namelen = 0;
/* will be updated in set_orig_addr() if needed */
m->msg_namelen = 0;
struct sockaddr_ax25 *sax = (struct sockaddr_ax25 *)msg->msg_name;
if (msg->msg_namelen != 0) {
goto error;
struct flowi6 *fl6 = &inet->cork.fl.u.ip6;
dst = ip6_dst_lookup_flow(sk, fl6, NULL, false);
dst = ip6_dst_lookup_flow(sk, fl6, NULL, false);
*mtu = dst_mtu(rt->dst.path);
unsigned int maxfraglen, fragheaderlen;
fragheaderlen, skb, rt);
int mtu;
*mtu = dst_mtu(rt->dst.path);
struct rt6_info *rt)
opt.refcnt = gact->tcf_refcnt - ref;
opt.bindcnt = gact->tcf_bindcnt - bind;
opt.action = gact->tcf_action;
p_opt.paction = gact->tcfg_paction;
p_opt.pval = gact->tcfg_pval;
p_opt.ptype = gact->tcfg_ptype;
opt.index = gact->tcf_index;
struct tc_nat opt;
opt.old_addr = p->old_addr;
opt.new_addr = p->new_addr;
opt.mask = p->mask;
opt.flags = p->flags;
opt.index = p->tcf_index;
opt.action = p->tcf_action;
opt.refcnt = p->tcf_refcnt - ref;
opt.bindcnt = p->tcf_bindcnt - bind;
opt.action = d->tcf_action;
struct tc_skbedit opt;
opt.index = d->tcf_index;
opt.refcnt = d->tcf_refcnt - ref;
opt.bindcnt = d->tcf_bindcnt - bind;
opt.index = d->tcf_index;
opt.refcnt = d->tcf_refcnt - ref;
opt.bindcnt = d->tcf_bindcnt - bind;
opt.action = d->tcf_action;
struct tc_defact opt;
opt.index = m->tcf_index;
opt.action = m->tcf_action;
opt.refcnt = m->tcf_refcnt - ref;
opt.bindcnt = m->tcf_bindcnt - bind;
opt.eaction = m->tcfm_eaction;
opt.ifindex = m->tcfm_ifindex;
if (iget_flags & XFS_IGET_BULKSTAT) {
if (iget_flags & XFS_IGET_BULKSTAT) {
error = xfs_iget(mp, NULL, ino, XFS_IGET_BULKSTAT,
* The XFS_IGET_BULKSTAT means that an invalid inode number is just
* fine and not an indication of a corrupted filesystem.  Because
* clients can send any kind of invalid file handle, e.g. after
* a restore on the server we have to deal with this case gracefully.
XFS_IGET_BULKSTAT, XFS_ILOCK_SHARED, &ip, bno);
XFS_IGET_BULKSTAT, XFS_ILOCK_SHARED, &ip, bno);
XFS_IGET_BULKSTAT, XFS_ILOCK_SHARED, &ip, bno);
if (flags & XFS_IGET_BULKSTAT)
if (flags & XFS_IGET_BULKSTAT) {
if ((flags & XFS_IGET_BULKSTAT) &&
if ((flags & XFS_IGET_BULKSTAT) &&
/*
* We just created this mm, if we can't find the strings
* we just copied into it something is _very_ wrong. Similar
* for strings that are too long, we should not have created
* any.
*/
if (WARN_ON_ONCE(len < 0 || len > MAX_ARG_STRLEN - 1)) {
send_sig(SIGKILL, current, 0);
return -1;
/* walk the whole argument looking for non-ascii chars */
if (len_left > MAX_EXECVE_AUDIT_LEN)
to_send = MAX_EXECVE_AUDIT_LEN;
else
to_send = len_left;
ret = copy_from_user(buf, tmp_p, to_send);
/*
* There is no reason for this copy to be short. We just
* copied them here, and the mm hasn't been exposed to user-
* space yet.
*/
if (ret) {
WARN_ON(1);
send_sig(SIGKILL, current, 0);
return -1;
}
buf[to_send] = '\0';
has_cntl = audit_string_contains_control(buf, to_send);
if (has_cntl) {
/*
* hex messages get logged as 2 bytes, so we can only
* send half as much in each message
*/
max_execve_audit_len = MAX_EXECVE_AUDIT_LEN / 2;
break;
}
len_left -= to_send;
tmp_p += to_send;
} while (len_left > 0);
len_left = len;
if (len > max_execve_audit_len)
too_long = 1;
/* rewalk the argument actually logging the message */
for (i = 0; len_left > 0; i++) {
int room_left;
if (len_left > max_execve_audit_len)
to_send = max_execve_audit_len;
else
to_send = len_left;
/* do we have space left to send this argument in this ab? */
room_left = MAX_EXECVE_AUDIT_LEN - arg_num_len - *len_sent;
if (has_cntl)
room_left -= (to_send * 2);
else
room_left -= to_send;
if (room_left < 0) {
*len_sent = 0;
audit_log_end(*ab);
*ab = audit_log_start(context, GFP_KERNEL, AUDIT_EXECVE);
if (!*ab)
return 0;
}
/*
* first record needs to say how long the original string was
* so we can be sure nothing was lost.
*/
if ((i == 0) && (too_long))
audit_log_format(*ab, " a%d_len=%zu", arg_num,
has_cntl ? 2*len : len);
/*
* normally arguments are small enough to fit and we already
* filled buf above when we checked for control characters
* so don't bother with another copy_from_user
*/
if (len >= max_execve_audit_len)
ret = copy_from_user(buf, p, to_send);
else
ret = 0;
if (ret) {
WARN_ON(1);
send_sig(SIGKILL, current, 0);
return -1;
buf[to_send] = '\0';
/* actually log it */
audit_log_format(*ab, " a%d", arg_num);
if (too_long)
audit_log_format(*ab, "[%d]", i);
audit_log_format(*ab, "=");
if (has_cntl)
audit_log_n_hex(*ab, buf, to_send);
else
audit_log_string(*ab, buf);
p += to_send;
len_left -= to_send;
*len_sent += arg_num_len;
if (has_cntl)
*len_sent += to_send * 2;
else
*len_sent += to_send;
}
/* include the null we didn't log */
return len + 1;
}
static void audit_log_execve_info(struct audit_context *context,
struct audit_buffer **ab)
{
int i, len;
size_t len_sent = 0;
const char __user *p;
char *buf;
p = (const char __user *)current->mm->arg_start;
audit_log_format(*ab, "argc=%d", context->execve.argc);
/*
* we need some kernel buffer to hold the userspace args.  Just
* allocate one big one rather than allocating one of the right size
* for every single argument inside audit_log_single_execve_arg()
* should be <8k allocation so should be pretty safe.
*/
buf = kmalloc(MAX_EXECVE_AUDIT_LEN + 1, GFP_KERNEL);
if (!buf) {
audit_panic("out of memory for argv string");
return;
}
for (i = 0; i < context->execve.argc; i++) {
len = audit_log_single_execve_arg(context, ab, i,
&len_sent, p, buf);
if (len <= 0)
break;
p += len;
}
kfree(buf);
char arg_num_len_buf[12];
const char __user *tmp_p = p;
/* how many digits are in arg_num? 5 is the length of ' a=""' */
size_t arg_num_len = snprintf(arg_num_len_buf, 12, "%d", arg_num) + 5;
size_t len, len_left, to_send;
size_t max_execve_audit_len = MAX_EXECVE_AUDIT_LEN;
unsigned int i, has_cntl = 0, too_long = 0;
int ret;
/* strnlen_user includes the null we don't want to send */
len_left = len = strnlen_user(p, MAX_ARG_STRLEN) - 1;
if (ns_capable(ns->parent, cap_setid))
Nor can they impersonate a kill(), which adds source info.  */
if (info->si_code >= 0)
Nor can they impersonate a kill(), which adds source info.  */
if (info.si_code >= 0)
perf_event_mmap(vma);
get_user(buf, &uiov32->iov_base)) {
tot_len = -EFAULT;
break;
}
"length %d, values %02X, %02X, "
"%02X, %02X\n",
p[0], p[1], p[2], p[3], p[4], p[5]);
list_del(&keyring->type_data.link);
if (!mm_init(mm, tsk))
rcu_read_lock();
if (ns_capable(__task_cred(task)->user_ns, CAP_SYS_PTRACE))
flags |= PT_PTRACE_CAP;
rcu_read_unlock();
rcu_read_lock();
if (dumpable != SUID_DUMP_USER &&
!ptrace_has_cap(__task_cred(task)->user_ns, mode)) {
rcu_read_unlock();
}
rcu_read_unlock();
int dumpable = 0;
ap->applid, capi_cmsg2str(&s_cmsg));
if (debugmode > 3)
printk(KERN_DEBUG "capidrv_signal: applid=%d %s\n",
printk(KERN_ERR "capidrv-%d: %s\n",
card->contrnr, capi_cmsg2str(cmsg));
p[0] = 0;
protocol_message_2_pars(cmsg, 1);
bufprint("%s ID=%03d #0x%04x LEN=%04d\n",
return buf;
p = buf;
printstructlen(m, len);
bufprint("%c", *m);
bufprint(">");
bufprint("<%02x", *m);
bufprint(" %02x", *m);
bufprint(">");
vsprintf(p, fmt, f);
p += strlen(p);
bufprint("%-*s\n", slen, name);
static void protocol_message_2_pars(_cmsg * cmsg, int level)
protocol_message_2_pars(cmsg, level + 1);
bufprint("%-*s = default\n", slen, NAME);
protocol_message_2_pars(&cmsg, 1);
return buf;
printk(KERN_NOTICE "kcapi: Controller %d: %s unregistered\n",
printk(KERN_DEBUG "kcapi: put [%#x] %s\n",
CAPIMSG_CONTROLLER(skb->data),
printk(KERN_DEBUG "kcapi: put [%#x] id#%d %s len=%u\n",
capi_message2str(skb->data));
printk(KERN_DEBUG "kcapi: got [0x%lx] id#%d %s len=%u\n",
(unsigned long) card->cnr,
CAPIMSG_APPID(skb->data),
printk(KERN_DEBUG "kcapi: got [0x%lx] %s\n",
(unsigned long) card->cnr,
capi_message2str(skb->data));
printk(KERN_INFO "kcapi: controller %d not active, got: %s",
card->cnr, capi_message2str(skb->data));
printk(KERN_ERR "kcapi: handle_message: applid %d state released (%s)\n",
CAPIMSG_APPID(skb->data), capi_message2str(skb->data));
printk(KERN_DEBUG "kcapi: card %d resume\n", card->cnr);
printk(KERN_INFO "kcapi: contr %d set trace=%d\n",
printk(KERN_NOTICE "kcapi: card %d down.\n", card->cnr);
printk(KERN_DEBUG "kcapi: card %d suspend\n", card->cnr);
printk(KERN_NOTICE "kcapi: Controller %d: %s attached\n",
printk(KERN_NOTICE "kcapi: card %d \"%s\" ready.\n",
dev_set_name(ddev, disk->disk_name);
error = dev_set_name(&oud->class_dev, disk->disk_name);
thread = kthread_create(nbd_thread, nbd, nbd->disk->disk_name);
/* mark that this skb passed once through the udp gro layer */
NAPI_GRO_CB(skb)->udp_mark = 1;
if (NAPI_GRO_CB(skb)->udp_mark ||
if (pt[6] & AX25_HBIT)
else
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = sizeof(*sipx);
else
msg->msg_namelen = 0;
if (sk->sk_shutdown & RCV_SHUTDOWN) {
msg->msg_namelen = 0;
}
msg->msg_namelen = 0;
msg.msg_name = (struct sockaddr *)&address;
msg.msg_namelen = sizeof(address);
msg->msg_namelen = 0;
m->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
m->msg_name = address;
if (!err) {
if (sat) {
sat->sat_family      = AF_APPLETALK;
struct sockaddr_at *sat = (struct sockaddr_at *)msg->msg_name;
sat->sat_addr.s_node = ddp->deh_snode;
sat->sat_addr.s_net  = ddp->deh_snet;
}
msg->msg_namelen = sizeof(*sat);
sat->sat_port        = ddp->deh_sport;
msg->msg_namelen = 0;
memset(srose, 0, msg->msg_namelen);
struct sockaddr_rose *srose = (struct sockaddr_rose *)msg->msg_name;
if (srose != NULL) {
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = sizeof(*sax);
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
kern_msg->msg_name = kern_address;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
if (msg->msg_namelen >= sizeof(struct sockaddr_mISDN)) {
msg->msg_namelen = sizeof(struct sockaddr_mISDN);
maddr = (struct sockaddr_mISDN *)msg->msg_name;
struct sockaddr_mISDN	*maddr;
} else {
if (msg->msg_namelen)
printk(KERN_WARNING "%s: too small namelen %d\n",
__func__, msg->msg_namelen);
msg->msg_namelen = 0;
msg->msg_namelen = 0;
msg->msg_namelen = 0;
sll = &PACKET_SKB_CB(skb)->sa.ll;
if (sock->type == SOCK_PACKET)
msg->msg_namelen = sizeof(struct sockaddr_pkt);
else
msg->msg_namelen = sll->sll_halen + offsetof(struct sockaddr_ll, sll_addr);
/*
struct sockaddr_ll *sll;
*	user program they can ask the device for its MTU anyway.
*	You lose any data beyond the buffer you gave. If it worries a
if (msg->msg_name)
/*
*	If the address length field is there to be filled in, we fill
*	it in now.
*/
msg->msg_namelen = 0;
/* will be updated in set_orig_addr() if needed */
m->msg_namelen = 0;
struct sockaddr_ax25 *sax = (struct sockaddr_ax25 *)msg->msg_name;
if (msg->msg_namelen != 0) {
BUG_ON(key != ctx->match_data);
sk_incoming_cpu_update(sk);
char *tmpptr = key + strlen(key);
*tmpptr = '=';
(u64)user_ptr);
return NULL;
}
buffer->free_in_progress = 1;
* free the buffer twice
if (buffer->free_in_progress) {
binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
"%d:%d FREE_BUFFER u%016llx user freed buffer twice\n",
alloc->pid, current->pid,
/* updating a negative key instantiates it */
clear_bit(KEY_FLAG_NEGATIVE, &key->flags);
/* updating a negative key instantiates it */
clear_bit(KEY_FLAG_NEGATIVE, &key->flags);
/* updating a negative key instantiates it */
clear_bit(KEY_FLAG_NEGATIVE, &key->flags);
set_bit(KEY_FLAG_INSTANTIATED, &key->flags);
if (!test_bit(KEY_FLAG_INSTANTIATED, &key->flags)) {
smp_wmb();
key->reject_error = -error;
if (test_bit(KEY_FLAG_INSTANTIATED, &key->flags) &&
!test_bit(KEY_FLAG_NEGATIVE, &key->flags) &&
key->type->destroy)
if (test_bit(KEY_FLAG_INSTANTIATED, &key->flags))
!test_bit(KEY_FLAG_INSTANTIATED, &key->flags))
return key->reject_error;
}
if (test_bit(KEY_FLAG_NEGATIVE, &key->flags)) {
smp_rmb();
if (key_is_instantiated(key)) {
if (key_is_instantiated(key) &&
if (key_is_instantiated(key))
if (kflags & (1 << KEY_FLAG_NEGATIVE)) {
smp_rmb();
ctx->result = ERR_PTR(key->reject_error);
unsigned long kflags = key->flags;
if (key_is_instantiated(keyring)) {
if (test_bit(KEY_FLAG_NEGATIVE, &key->flags))
showflag(key, 'N', KEY_FLAG_NEGATIVE),
showflag(key, 'I', KEY_FLAG_INSTANTIATED),
if (test_bit(KEY_FLAG_INSTANTIATED, &key->flags)) {
if (test_bit(KEY_FLAG_NEGATIVE, &key->flags)) {
ret = -ENOKEY;
goto error2;
}
static inline bool key_is_instantiated(const struct key *key)
if (key_is_instantiated(key))
if (!test_bit(KEY_FLAG_NEGATIVE, &key->flags))
if (test_bit(KEY_FLAG_NEGATIVE, &key->flags))
umount_tree(mnt, 0);
if (ret < 0)
static struct btrfs_dir_item *btrfs_match_dir_item_name(struct btrfs_root *root,
struct btrfs_path *path,
const char *name, int name_len);
/* It is not a fragmented frame */
goto ret_orig;
}
if (!(fhdr->frag_off & htons(0xFFF9))) {
pr_debug("Invalid fragment offset\n");
int retval = 0;
if (!urb)
return -ENOMEM;
inet_frag_lru_add(nf, qp);
clear_buffer_new(bh);
if (!err)
return err;
long error, i, remaining;
unsigned char * tmp;
error = -ENOMEM;
if (!vma->vm_file)
return error;
start = ((start - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
if (end > vma->vm_end)
end = vma->vm_end;
end = ((end - vma->vm_start) >> PAGE_SHIFT) + vma->vm_pgoff;
error = -EAGAIN;
tmp = (unsigned char *) __get_free_page(GFP_KERNEL);
if (!tmp)
return error;
/* (end - start) is # of pages, and also # of bytes in "vec */
remaining = (end - start),
error = 0;
for (i = 0; remaining > 0; remaining -= PAGE_SIZE, i++) {
int j = 0;
long thispiece = (remaining < PAGE_SIZE) ?
remaining : PAGE_SIZE;
while (j < thispiece)
tmp[j++] = mincore_page(vma, start++);
if (copy_to_user(vec + PAGE_SIZE * i, tmp, thispiece)) {
error = -EFAULT;
break;
}
}
free_page((unsigned long) tmp);
return error;
sb->s_maxbytes = MAX_LFS_FILESIZE;
err = xt_check_entry_offsets(e, e->target_offset, e->next_offset);
err = xt_check_entry_offsets(e, e->target_offset, e->next_offset);
ret = xt_compat_check_entry_offsets(e,
sprintf(new_port->name, "port-%d", num);
dh = skb_header_pointer(skb, dataoff, sizeof(_dh), &dh);
dh = skb_header_pointer(skb, dataoff, sizeof(_dh), &dh);
if (unlikely(!is_rx || (!is_vid && !is_tch) || !ops->vidioc_g_fmt_vid_cap))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_g_fmt_vid_cap_mplane))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_g_fmt_vid_overlay))
if (unlikely(!is_rx || is_vid || !ops->vidioc_g_fmt_vbi_cap))
break;
if (unlikely(!is_rx || is_vid || !ops->vidioc_g_fmt_sliced_vbi_cap))
break;
if (unlikely(!is_tx || !is_vid || !ops->vidioc_g_fmt_vid_out))
if (unlikely(!is_tx || !is_vid || !ops->vidioc_g_fmt_vid_out_mplane))
if (unlikely(!is_tx || !is_vid || !ops->vidioc_g_fmt_vid_out_overlay))
if (unlikely(!is_tx || is_vid || !ops->vidioc_g_fmt_vbi_out))
if (unlikely(!is_tx || is_vid || !ops->vidioc_g_fmt_sliced_vbi_out))
if (unlikely(!is_rx || !is_sdr || !ops->vidioc_g_fmt_sdr_cap))
break;
if (unlikely(!is_tx || !is_sdr || !ops->vidioc_g_fmt_sdr_out))
break;
if (unlikely(!is_rx || !is_vid || !ops->vidioc_g_fmt_meta_cap))
break;
struct video_device *vfd = video_devdata(file);
bool is_vid = vfd->vfl_type == VFL_TYPE_GRABBER;
bool is_sdr = vfd->vfl_type == VFL_TYPE_SDR;
bool is_tch = vfd->vfl_type == VFL_TYPE_TOUCH;
bool is_rx = vfd->vfl_dir != VFL_DIR_TX;
bool is_tx = vfd->vfl_dir != VFL_DIR_RX;
int ret;
if (unlikely(!is_tx || !is_vid || !ops->vidioc_s_fmt_vid_out_mplane))
if (unlikely(!is_rx || is_vid || !ops->vidioc_s_fmt_vbi_cap))
if (unlikely(!is_tx || !is_sdr || !ops->vidioc_s_fmt_sdr_out))
if (unlikely(!is_rx || (!is_vid && !is_tch) || !ops->vidioc_s_fmt_vid_cap))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_s_fmt_meta_cap))
if (is_tch)
if (unlikely(!is_rx || !is_vid || !ops->vidioc_s_fmt_vid_cap_mplane))
if (unlikely(!is_tx || !is_vid || !ops->vidioc_s_fmt_vid_out_overlay))
if (unlikely(!is_tx || !is_vid || !ops->vidioc_s_fmt_vid_out))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_s_fmt_vid_overlay))
if (unlikely(!is_tx || is_vid || !ops->vidioc_s_fmt_vbi_out))
bool is_vid = vfd->vfl_type == VFL_TYPE_GRABBER;
bool is_sdr = vfd->vfl_type == VFL_TYPE_SDR;
bool is_tch = vfd->vfl_type == VFL_TYPE_TOUCH;
bool is_rx = vfd->vfl_dir != VFL_DIR_TX;
bool is_tx = vfd->vfl_dir != VFL_DIR_RX;
int ret;
if (unlikely(!is_tx || is_vid || !ops->vidioc_s_fmt_sliced_vbi_out))
if (unlikely(!is_rx || is_vid || !ops->vidioc_s_fmt_sliced_vbi_cap))
if (unlikely(!is_rx || !is_sdr || !ops->vidioc_s_fmt_sdr_cap))
if (unlikely(!is_tx || !is_vid || !ops->vidioc_enum_fmt_vid_out))
if (unlikely(!is_tx || !is_vid || !ops->vidioc_enum_fmt_vid_out_mplane))
struct video_device *vfd = video_devdata(file);
bool is_vid = vfd->vfl_type == VFL_TYPE_GRABBER;
bool is_sdr = vfd->vfl_type == VFL_TYPE_SDR;
bool is_tch = vfd->vfl_type == VFL_TYPE_TOUCH;
bool is_rx = vfd->vfl_dir != VFL_DIR_TX;
bool is_tx = vfd->vfl_dir != VFL_DIR_RX;
int ret = -EINVAL;
if (unlikely(!is_tx || !is_sdr || !ops->vidioc_enum_fmt_sdr_out))
if (unlikely(!is_rx || (!is_vid && !is_tch) || !ops->vidioc_enum_fmt_vid_cap))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_enum_fmt_meta_cap))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_enum_fmt_vid_cap_mplane))
if (unlikely(!is_rx || !is_vid || !ops->vidioc_enum_fmt_vid_overlay))
if (unlikely(!is_rx || !is_sdr || !ops->vidioc_enum_fmt_sdr_cap))
/* Reserve space for headers. */
skb_reserve(buff, MAX_TCP_HEADER);
buff = alloc_skb_fclone(MAX_TCP_HEADER + 15, sk->sk_allocation);
if (unlikely(buff == NULL))
netdev_notifier_info_init(&info, dev);
struct net_device *dev = ((struct in_ifaddr *)ptr)->ifa_dev->dev;
if (len > MAX_RDS_RADIO_TEXT) {
if (len > MAX_RDS_PS_NAME) {
else if (vcpu->arch.apic_base & X2APIC_ENABLE) {
ecryptfs_hash_buckets = 1;
while (ecryptfs_number_of_users >> ecryptfs_hash_buckets)
ecryptfs_hash_buckets++;
for (i = 0; i < ecryptfs_hash_buckets; i++)
* ecryptfs_hash_buckets), GFP_KERNEL);
get_user(buf, &uiov32->iov_base)) {
tot_len = -EFAULT;
break;
}
err += iov[ct].iov_len;
/*
* Goal is not to verify user data, but to prevent returning
* negative value, which is interpreted as errno.
* Overflow is still possible, but it is harmless.
*/
if (err < 0)
int size, ct;
long err;
return -EMSGSIZE;
change_page_attr(virt_to_page(__va(p->phys_addr)),
if (!(sb->s_flags & MS_RDONLY)) {
bail2:
goto bail2;
kfree(sbi);
goto bail3;
bail3:
static int override_release(char __user *release, int len)
snprintf(buf, len, "2.6.%u%s", v, rest);
ret = copy_to_user(release, buf, len);
if (!sock_flag(sk, SOCK_ZAPPED))
return -EINVAL;
if (!rq->skip_clock_update) {
int cpu = cpu_of(rq);
u64 irq_time;
rq->clock = sched_clock_cpu(cpu);
irq_time = irq_time_cpu(cpu);
if (rq->clock - irq_time > rq->clock_task)
rq->clock_task = rq->clock - irq_time;
sched_irq_time_avg_update(rq, irq_time);
}
rq->skip_clock_update = 0;
clear_tsk_need_resched(prev);
goto ende;
if (sbinfo->max_blocks >= 0) {
buf->f_blocks = sbinfo->max_blocks;
buf->f_bavail = buf->f_bfree = sbinfo->free_blocks;
int hugetlb_get_quota(struct address_space *mapping, long delta)
{
int ret = 0;
struct hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(mapping->host->i_sb);
if (sbinfo->free_blocks > -1) {
spin_lock(&sbinfo->stat_lock);
if (sbinfo->free_blocks - delta >= 0)
sbinfo->free_blocks -= delta;
else
ret = -ENOMEM;
spin_unlock(&sbinfo->stat_lock);
}
return ret;
}
}
}
void hugetlb_put_quota(struct address_space *mapping, long delta)
{
struct hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(mapping->host->i_sb);
if (sbinfo->free_blocks > -1) {
spin_lock(&sbinfo->stat_lock);
sbinfo->free_blocks += delta;
spin_unlock(&sbinfo->stat_lock);
mapping = (struct address_space *) page_private(page);
hugetlb_put_quota(mapping, 1);
if (mapping)
struct address_space *mapping;
hugetlb_put_quota(inode->i_mapping, (chg - freed));
mapping = (struct address_space *)page_private(page);
hugetlb_put_quota(inode->i_mapping, chg);
set_page_private(page, (unsigned long) mapping);
struct address_space *mapping = vma->vm_file->f_mapping;
struct inode *inode = mapping->host;
* Processes that did not create the mapping will have no reserves and
* will not have accounted against quota. Check that the quota can be
* made before satisfying the allocation
* MAP_NORESERVE mappings may also need pages and quota allocated
* if no reserve mapping overlaps.
if (hugetlb_get_quota(inode->i_mapping, chg))
hugetlb_put_quota(inode->i_mapping, chg);
* and filesystem quota without using reserves
* Hand back the quota if there are not
/* There must be enough filesystem quota for the mapping */
if (hugetlb_get_quota(inode->i_mapping, chg))
hugetlb_put_quota(vma->vm_file->f_mapping, reserve);
*state = HT_AGG_STATE_OPERATIONAL;
static int ___ieee80211_stop_tx_ba_session(struct sta_info *sta, u16 tid,
enum ieee80211_back_parties initiator)
#ifdef CONFIG_MAC80211_HT_DEBUG
printk(KERN_DEBUG "Tx BA session stop requested for %pM tid %u\n",
*state = HT_AGG_STATE_OPERATIONAL;
#endif /* CONFIG_MAC80211_HT_DEBUG */
sta->sta.addr, tid);
struct ieee80211_local *local = sdata->local;
WLAN_BACK_RECIPIENT);
sta->ampdu_mlme.tid_state_tx[tid] =
HT_AGG_STATE_OPERATIONAL;
ieee80211_stop_tx_ba_session(&local->hw, sta->sta.addr, tid,
return -EFAULT;
ret = -EFAULT;
if (unlikely(err == -EFAULT)) {
if (unlikely(err == -EFAULT)) {
if (unlikely(err == -EFAULT)) {
return segmented_write(ctxt, ctxt->memop.addr.mem, &fx_state, size);
rc = segmented_read(ctxt, ctxt->memop.addr.mem, &fx_state, 512);
ret = xt_compat_check_entry_offsets(e, e->target_offset,
lock_kernel();
switch (orig) {
case 0:
if (offset < 0)
goto out;
file->f_pos = offset;
unlock_kernel();
return(file->f_pos);
case 1:
if (offset + file->f_pos < 0)
goto out;
file->f_pos += offset;
unlock_kernel();
return(file->f_pos);
case 2:
goto out;
default:
goto out;
}
out:
unlock_kernel();
return -EINVAL;
return gfs2_lookupi(dip, &qstr, 1, NULL);
if (pte && walk->hugetlb_entry)
__mark_reg_known(regs + insn->dst_reg, insn->imm);
static void coerce_reg_to_32(struct bpf_reg_state *reg)
{
/* clear high 32 bits */
reg->var_off = tnum_cast(reg->var_off, 4);
/* Update bounds */
__update_reg_bounds(reg);
}
regs[value_regno].var_off =
tnum_cast(regs[value_regno].var_off, size);
__update_reg_bounds(&regs[value_regno]);
coerce_reg_to_32(dst_reg);
coerce_reg_to_32(&src_reg);
allowed -= mm->total_vm / 32;
allowed -= current->mm->total_vm / 32;
return (flags & VM_ACCOUNT)?
0: security_vm_enough_memory(VM_ACCT(PAGE_CACHE_SIZE));
return (flags & VM_ACCOUNT)?
security_vm_enough_memory(VM_ACCT(size)): 0;
if (null_selector) /* for NULL selector skip all following checks */
&& null_selector)
goto exception;
return udp_prot.setsockopt(sk, level, optname, optval, optlen);
return sizeof(struct rds_header) + RDS_CONG_MAP_BYTES;
if (!res)
fuse_put_request(fc, req);
} else
/* Cleanup any SCTP per socket resources.  */
local_bh_disable();
local_bh_enable();
cm_dentry = debugfs_create_file("custom_method", S_IWUGO,
if (unlikely(insert_vm_struct(mm, vma))) {
kmem_cache_free(vm_area_cachep, vma);
return -ENOMEM;
}
spin_unlock_irqrestore(&process->sighand->siglock, flags);
if (!vma->anon_vma || vma->vm_ops || vma->vm_file)
VM_SHARED   | VM_MAYSHARE   |
VM_PFNMAP   | VM_IO      | VM_DONTEXPAND |
VM_RESERVED | VM_HUGETLB | VM_INSERTPAGE |
VM_MIXEDMAP | VM_SAO))
if (*vm_flags & (VM_HUGEPAGE |
VM_SHARED   | VM_MAYSHARE   |
VM_PFNMAP   | VM_IO      | VM_DONTEXPAND |
VM_RESERVED | VM_HUGETLB | VM_INSERTPAGE |
VM_MIXEDMAP | VM_SAO))
if (*vm_flags & (VM_NOHUGEPAGE |
VM_BUG_ON(is_linear_pfn_mapping(vma) || is_pfn_mapping(vma));
/* VM_PFNMAP vmas may have vm_ops null but vm_file set */
if (!vma->anon_vma || vma->vm_ops || vma->vm_file)
if (!vma->anon_vma || vma->vm_ops || vma->vm_file)
VM_BUG_ON(is_linear_pfn_mapping(vma) || is_pfn_mapping(vma));
/* VM_PFNMAP vmas may have vm_ops null but vm_file set */
if (vma->vm_file || vma->vm_ops)
VM_BUG_ON(is_linear_pfn_mapping(vma) || is_pfn_mapping(vma));
if ((drv_data->quirks & LG_RDESC_REL_ABS) && *rsize >= 50 &&
if ((drv_data->quirks & LG_RDESC) && *rsize >= 90 && rdesc[83] == 0x26 &&
if (*rsize >= 107 && rdesc[104] == 0x26 && rdesc[105] == 0x80 &&
if (*rsize >= 60 && rdesc[39] == 0x2a && rdesc[40] == 0xf5 &&
if (*rsize >= 74 &&
if (*rsize >= 30 && rdesc[29] == 0x05 && rdesc[30] == 0x09) {
if (unlikely(vcpu->arch.target < 0))
/* Make sure they initialize the vcpu with KVM_ARM_VCPU_INIT */
__wait_discard_cmd(sbi, false);
if (num > 0) {
data += VBLK_SIZE_HEAD;
size -= VBLK_SIZE_HEAD;
}
hlist_for_each_entry(dentry, &inode->i_dentry, d_alias) {
list_move(&dn->d_u.d_child, &parent->d_subdirs);
list_for_each_entry(de, &parent->d_subdirs, d_u.d_child) {
ll_d_hlist_for_each_entry(alias, p, &inode->i_dentry, d_alias) {
parent = ll_d_hlist_entry(dir->i_dentry, struct dentry, d_alias);
d_u.d_child) {
ll_d_hlist_for_each_entry(dentry, p, &dir->i_dentry, d_alias) {
list_for_each_entry(child, &alias->d_subdirs, d_u.d_child) {
hlist_for_each_entry(alias, &inode->i_dentry, d_alias) {
dentry = list_entry(p, struct dentry, d_u.d_child);
dentry = list_entry(p, struct dentry, d_u.d_child);
p = last->d_u.d_child.prev;
struct dentry *d = list_entry(node, struct dentry, d_u.d_child);
struct dentry, d_u.d_child);
struct dentry, d_u.d_child);
list_for_each_entry(dent, &parent->d_subdirs, d_u.d_child) {
d_child = &dentry->d_u.d_child;
list_for_each_entry_safe(dentry, tmp, &dir->d_subdirs, d_u.d_child) {
list_for_each_entry(child, &parent->d_subdirs, d_u.d_child) {
hlist_for_each_entry(dentry, &inode->i_dentry, d_alias) {
hlist_del_init(&sb->s_root->d_alias);
ret = list_entry(next, struct dentry, d_u.d_child);
next = p->d_u.d_child.next;
next = prev->d_u.d_child.next;
next = q->d_u.d_child.next;
q = list_entry(next, struct dentry, d_u.d_child);
list_move(&expired->d_parent->d_subdirs, &expired->d_u.d_child);
struct dentry *d = list_entry(tmp, struct dentry, d_u.d_child);
list_for_each_entry(child, &dir->d_subdirs, d_u.d_child) {
list_for_each_entry(child, &dentry->d_subdirs, d_u.d_child) {
struct list_head *p, *q = &cursor->d_u.d_child;
struct dentry *next = list_entry(p, struct dentry, d_u.d_child);
list_add_tail(&cursor->d_u.d_child, p);
next = list_entry(p, struct dentry, d_u.d_child);
list_del(&cursor->d_u.d_child);
parent = hlist_entry(inode->i_dentry.first, struct dentry, d_alias);
parent = hlist_entry(inode->i_dentry.first, struct dentry, d_alias);
hlist_for_each_entry(alias, &inode->i_dentry, d_alias) {
hlist_add_head(&dentry->d_alias, &inode->i_dentry);
BUG_ON(!hlist_unhashed(&entry->d_alias));
BUG_ON(!hlist_unhashed(&entry->d_alias));
hlist_for_each_entry(alias, &inode->i_dentry, d_alias) {
BUG_ON(!hlist_unhashed(&entry->d_alias));
WARN_ON(!hlist_unhashed(&dentry->d_alias));
alias = hlist_entry(inode->i_dentry.first, struct dentry, d_alias);
list_for_each_entry(child, &dparent->d_subdirs, d_u.d_child) {
list_add(&dentry->d_u.d_child, &parent->d_subdirs);
INIT_HLIST_NODE(&dentry->d_alias);
INIT_LIST_HEAD(&dentry->d_u.d_child);
next = child->d_u.d_child.next;
struct dentry *dentry = list_entry(tmp, struct dentry, d_u.d_child);
hlist_add_head(&tmp->d_alias, &inode->i_dentry);
hlist_del_init(&dentry->d_alias);
INIT_HLIST_NODE(&dentry->d_alias);
INIT_LIST_HEAD(&dentry->d_u.d_child);
list_del_init(&target->d_u.d_child);
list_move(&dentry->d_u.d_child, &dentry->d_parent->d_subdirs);
list_move(&target->d_u.d_child, &target->d_parent->d_subdirs);
list_move(&dentry->d_u.d_child, &dentry->d_parent->d_subdirs);
!hlist_unhashed(&dentry->d_alias) ||
hlist_for_each_entry(alias, &inode->i_dentry, d_alias) {
hlist_add_head(&dentry->d_alias, &inode->i_dentry);
hlist_for_each_entry(alias, &inode->i_dentry, d_alias) {
WARN_ON(!hlist_unhashed(&dentry->d_alias));
list_del(&dentry->d_u.d_child);
BUG_ON(!hlist_unhashed(&entry->d_alias));
hlist_for_each_entry(dentry, &inode->i_dentry, d_alias) {
ll_d_hlist_for_each_entry(dentry, p, &inode->i_dentry, d_alias) {
list_for_each_entry(dentry, &parent->d_subdirs, d_u.d_child) {
list_for_each_entry(dentry, &parent->d_subdirs, d_u.d_child) {
static inline void truncate_partial_page(struct page *page, unsigned partial)
{
zero_user_segment(page, partial, PAGE_CACHE_SIZE);
cleancache_invalidate_page(page->mapping, page);
if (page_has_private(page))
do_invalidatepage(page, partial, PAGE_CACHE_SIZE - partial);
}
* specified offsets (and zeroing out partial page
* (if lstart is not page aligned)).
* @lend: offset to which to truncate
truncate_partial_page(page, partial);
while (index <= end && pagevec_lookup(&pvec, mapping, index,
min(end - index, (pgoff_t)PAGEVEC_SIZE - 1) + 1)) {
if (index > end)
min(end - index, (pgoff_t)PAGEVEC_SIZE - 1) + 1)) {
if (partial) {
if (index == start && pvec.pages[0]->index > end) {
const pgoff_t start = (lstart + PAGE_CACHE_SIZE-1) >> PAGE_CACHE_SHIFT;
const unsigned partial = lstart & (PAGE_CACHE_SIZE - 1);
struct pagevec pvec;
pgoff_t index;
pgoff_t end;
int i;
if (index > end)
BUG_ON((lend & (PAGE_CACHE_SIZE - 1)) != (PAGE_CACHE_SIZE - 1));
end = (lend >> PAGE_CACHE_SHIFT);
return -EINVAL;
if ((p->flags & XFRM_STATE_ESN) && !rt)
if (xfrm_replay_state_esn_len(replay_esn) !=
xfrm_replay_state_esn_len(up))
strcpy(algo->alg_name, auth->alg_name);
return NF_ACCEPT;
return alt;
return usb_set_interface(udev,
intf->altsetting[0].desc.bInterfaceNumber, alt);
int alt;
if (alt < 0)
return alt->desc.bAlternateSetting;
static int uas_find_uas_alt_setting(struct usb_interface *intf)
return -ENODEV;
if (alt < 0)
r = uas_find_endpoints(&intf->altsetting[alt], eps);
int r, alt;
ia_valid &= ~ATTR_KILL_PRIV;
if (error > 0)
error = security_inode_killpriv(dentry);
if (error)
attr->ia_valid &= ~ATTR_KILL_PRIV;
unregister_pernet_device(&ipgre_net_ops);
if (!user)
return ERR_PTR(-ENOMEM);
construct_get_dest_keyring(&dest_keyring);
goto couldnt_alloc_key;
couldnt_alloc_key:
user = key_user_lookup(current_fsuid());
return -EAGAIN;
}
xfrm4_tunnel_deregister(&sit_handler, AF_INET6);
if (xfrm4_tunnel_register(&sit_handler, AF_INET6) < 0) {
printk(KERN_INFO "sit init: Can't add protocol\n");
unregister_pernet_subsys(&xfrm6_tunnel_net_ops);
xfrm6_tunnel_spi_fini();
static void xfrm6_tunnel_spi_fini(void)
{
kmem_cache_destroy(xfrm6_tunnel_spi_kmem);
}
return 0;
}
static int __init xfrm6_tunnel_spi_init(void)
{
xfrm6_tunnel_spi_kmem = kmem_cache_create("xfrm6_tunnel_spi",
sizeof(struct xfrm6_tunnel_spi),
0, SLAB_HWCACHE_ALIGN,
NULL);
if (!xfrm6_tunnel_spi_kmem)
return -ENOMEM;
xfrm4_tunnel_deregister(&ipip_handler, AF_INET);
if (xfrm4_tunnel_register(&ipip_handler, AF_INET)) {
return -EAGAIN;
err = register_pernet_device(&ipip_net_ops);
if (err)
static void sas_eh_defer_cmd(struct scsi_cmnd *cmd)
{
struct domain_device *dev = cmd_to_domain_dev(cmd);
struct sas_ha_struct *ha = dev->port->ha;
struct sas_task *task = TO_SAS_TASK(cmd);
if (!dev_is_sata(dev)) {
sas_eh_finish_cmd(cmd);
return;
}
/* report the timeout to libata */
sas_end_task(cmd, task);
list_move_tail(&cmd->eh_entry, &ha->eh_ata_q);
}
sas_eh_defer_cmd(cmd);
if (stringset == ETH_SS_STATS)
if (stringset == ETH_SS_STATS)
if (stringset == ETH_SS_STATS)
if (rt->rt_flags&RTCF_DOREDIRECT && !opt->srr && !skb_sec_path(skb))
return X86EMUL_CONTINUE;
rc = load_segment_descriptor(ctxt, sel, VCPU_SREG_CS);
ctxt->_eip = 0;
unsigned short sel;
memcpy(&ctxt->_eip, ctxt->src.valptr, ctxt->op_bytes);
return __load_segment_descriptor(ctxt, selector, seg, cpl, false);
u16 selector, int seg, u8 cpl, bool in_task_switch)
ret = __load_segment_descriptor(ctxt, tss->ds, VCPU_SREG_DS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->fs, VCPU_SREG_FS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->gs, VCPU_SREG_GS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->ldt_selector, VCPU_SREG_LDTR, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->es, VCPU_SREG_ES, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->cs, VCPU_SREG_CS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->ss, VCPU_SREG_SS, cpl, true);
if (ctxt->op_bytes == 4)
ctxt->_eip = (u32)ctxt->_eip;
rc = emulate_pop(ctxt, &ctxt->_eip, ctxt->op_bytes);
rc = load_segment_descriptor(ctxt, (u16)cs, VCPU_SREG_CS);
ret = __load_segment_descriptor(ctxt, tss->ds, VCPU_SREG_DS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->cs, VCPU_SREG_CS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->ldt, VCPU_SREG_LDTR, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->ss, VCPU_SREG_SS, cpl, true);
ret = __load_segment_descriptor(ctxt, tss->es, VCPU_SREG_ES, cpl, true);
pfn = kvm_pin_pages(slot, gfn, page_size);
kvm_unpin_pages(kvm, pfn, page_size);
* spin until we've taken care of that timer below.
*/
spin_unlock(&tsk->sighand->siglock);
BUG_ON(tsk->exit_state);
spin_lock(&tsk->sighand->siglock);
/*
* Here we take off tsk->cpu_timers[N] and tsk->signal->cpu_timers[N]
* all the timers that are firing, and put them on the firing list.
*/
check_thread_timers(tsk, &firing);
check_process_timers(tsk, &firing);
/*
* We must release these locks before taking any timer's lock.
* There is a potential race with timer deletion here, as the
* siglock now protects our private firing list.  We have set
* the firing flag in each timer, so that a deletion attempt
* that gets the timer lock before we do will give it up and
/*
* Make sure we don't try to process any timer firings
* while we are already exiting.
*/
tsk->it_virt_expires = cputime_zero;
tsk->it_prof_expires = cputime_zero;
tsk->it_sched_expires = 0;
if (p->parent == p->real_parent)
BUG();
#endif
#if !defined(CONFIG_ALTIVEC)
config->intf_assoc[iad_num] =
(struct usb_interface_assoc_descriptor
*)header;
ret = security_file_permission(file, MAY_READ);
break;
if (unlikely(ret))
if (unlikely(ret))
break;
ret = security_file_permission(file, MAY_WRITE);
if (unlikely(ret))
break;
ret = aio_setup_single_vector(kiocb);
ret = security_file_permission(file, MAY_WRITE);
ret = security_file_permission(file, MAY_READ);
if (unlikely(ret))
break;
ret = aio_setup_single_vector(kiocb);
if (unlikely(len < ETH_ZLEN)) {
if (skb_padto(skb, ETH_ZLEN))
goto err_update_stats;
len = ETH_ZLEN;
}
err_update_stats:
/* The 0th block becomes the root, move the dirents out */
fde = &root->dotdot;
de = (struct ext4_dir_entry_2 *)((char *)fde +
ext4_rec_len_from_disk(fde->rec_len));
len = ((char *) root) + blocksize - (char *) de;
dxtrace(printk(KERN_DEBUG "Creating index\n"));
"block %lu > max",
indirect_blocks + double_blocks);
static ssize_t cm_write(struct file *file, const char __user * user_buf,
size_t count, loff_t *ppos)
{
static char *buf;
static u32 max_size;
static u32 uncopied_bytes;
struct acpi_table_header table;
acpi_status status;
if (!(*ppos)) {
/* parse the table header to get the table length */
if (count <= sizeof(struct acpi_table_header))
return -EINVAL;
if (copy_from_user(&table, user_buf,
sizeof(struct acpi_table_header)))
return -EFAULT;
uncopied_bytes = max_size = table.length;
buf = kzalloc(max_size, GFP_KERNEL);
if (!buf)
return -ENOMEM;
}
if (buf == NULL)
return -EINVAL;
if ((*ppos > max_size) ||
(*ppos + count > max_size) ||
(*ppos + count < count) ||
(count > uncopied_bytes))
return -EINVAL;
if (copy_from_user(buf + (*ppos), user_buf, count)) {
kfree(buf);
buf = NULL;
return -EFAULT;
}
uncopied_bytes -= count;
*ppos += count;
if (!uncopied_bytes) {
status = acpi_install_method(buf);
kfree(buf);
buf = NULL;
if (ACPI_FAILURE(status))
return -EINVAL;
add_taint(TAINT_OVERRIDDEN_ACPI_TABLE);
}
return count;
}
acpi_custom_method_init();
__net_random_once_disable_jump(done_key);
struct static_key *done_key)
static_key_slow_inc(work->key);
if (!static_key_enabled(work->key))
ret = sys_wait4(pid, ustatus, options, (struct rusage __user *) &r);
struct inet_diag_bc_op *op = (struct inet_diag_bc_op *)bc;
if (op->yes < 4 || op->yes > len + 4)
if (op->no < 4 || op->no > len + 4)
if (op->yes < 4 || op->yes > len + 4)
if (!mp->ports && !mp->mglist &&
if (!mp->ports && !mp->mglist &&
!(iter->rt6i_flags & RTF_EXPIRES))
if (sibling->rt6i_metric == rt->rt6i_metric) {
if (rt->rt6i_flags & RTF_GATEWAY &&
!(rt->rt6i_flags & RTF_EXPIRES) &&
struct page *dma_alloc_from_contiguous(struct device *dev, int count,
pr_debug("%s(cma %p, count %d, align %d)\n", __func__, (void *)cma,
ret = 0;
key.objectid = btrfs_header_owner(leaf);
PFERR_WRITE_MASK, exception);
unsigned int bytes, struct x86_exception *exception)
return kvm_read_guest_virt_helper(addr, val, bytes, vcpu, 0, exception);
struct x86_exception *exception)
return ctxt->ops->read_std(ctxt, linear, data, size, &ctxt->exception);
return ctxt->ops->write_std(ctxt, linear, data, size, &ctxt->exception);
r = ops->read_std(ctxt, base + io_bitmap_ptr + port/8, &perm, 2, NULL);
r = ops->read_std(ctxt, base + 102, &io_bitmap_ptr, 2, NULL);
return ctxt->ops->write_std(ctxt, linear, data, size, &ctxt->exception);
return ctxt->ops->read_std(ctxt, linear, data, size, &ctxt->exception);
b->mtu = dev->mtu;
static int needs_empty_write(sector_t block, struct inode *inode)
{
int error;
struct buffer_head bh_map = { .b_state = 0, .b_blocknr = 0 };
bh_map.b_size = 1 << inode->i_blkbits;
error = gfs2_block_map(inode, block, &bh_map, 0);
if (unlikely(error))
return error;
return !buffer_mapped(&bh_map);
}
u64 start = offset >> PAGE_CACHE_SHIFT;
unsigned int start_offset = offset & ~PAGE_CACHE_MASK;
u64 end = (offset + len - 1) >> PAGE_CACHE_SHIFT;
pgoff_t curr;
struct page *page;
unsigned int end_offset = (offset + len) & ~PAGE_CACHE_MASK;
unsigned int from, to;
if (!end_offset)
end_offset = PAGE_CACHE_SIZE;
goto out;
curr = start;
offset = start << PAGE_CACHE_SHIFT;
from = start_offset;
to = PAGE_CACHE_SIZE;
while (curr <= end) {
page = grab_cache_page_write_begin(inode->i_mapping, curr,
AOP_FLAG_NOFS);
if (unlikely(!page)) {
error = -ENOMEM;
goto out;
}
if (curr == end)
to = end_offset;
error = write_empty_blocks(page, from, to, mode);
if (!error && offset + to > inode->i_size &&
!(mode & FALLOC_FL_KEEP_SIZE)) {
i_size_write(inode, offset + to);
}
unlock_page(page);
page_cache_release(page);
if (error)
curr++;
offset += PAGE_CACHE_SIZE;
from = 0;
brelse(dibh);
if (end) {
ret = __block_write_begin(page, start, end - start, gfs2_block_map);
if (unlikely(ret))
return ret;
ret = empty_write_end(page, start, end, mode);
if (unlikely(ret))
return ret;
}
return 0;
}
static int write_empty_blocks(struct page *page, unsigned from, unsigned to,
int mode)
{
struct inode *inode = page->mapping->host;
unsigned start, end, next, blksize;
sector_t block = page->index << (PAGE_CACHE_SHIFT - inode->i_blkbits);
int ret;
blksize = 1 << inode->i_blkbits;
next = end = 0;
while (next < from) {
next += blksize;
block++;
}
start = next;
do {
next += blksize;
ret = needs_empty_write(block, inode);
if (unlikely(ret < 0))
return ret;
if (ret == 0) {
if (end) {
ret = __block_write_begin(page, start, end - start,
gfs2_block_map);
if (unlikely(ret))
return ret;
ret = empty_write_end(page, start, end, mode);
if (unlikely(ret))
return ret;
end = 0;
}
start = next;
}
else
end = next;
block++;
} while (next < to);
static int empty_write_end(struct page *page, unsigned from,
unsigned to, int mode)
{
struct inode *inode = page->mapping->host;
struct gfs2_inode *ip = GFS2_I(inode);
struct buffer_head *bh;
unsigned offset, blksize = 1 << inode->i_blkbits;
pgoff_t end_index = i_size_read(inode) >> PAGE_CACHE_SHIFT;
zero_user(page, from, to-from);
mark_page_accessed(page);
if (page->index < end_index || !(mode & FALLOC_FL_KEEP_SIZE)) {
if (!gfs2_is_writeback(ip))
gfs2_page_add_databufs(ip, page, from, to);
block_commit_write(page, from, to);
return 0;
}
offset = 0;
bh = page_buffers(page);
while (offset < to) {
if (offset >= from) {
set_buffer_uptodate(bh);
mark_buffer_dirty(bh);
clear_buffer_new(bh);
write_dirty_buffer(bh, WRITE);
}
offset += blksize;
bh = bh->b_this_page;
}
offset = 0;
bh = page_buffers(page);
while (offset < to) {
if (offset >= from) {
wait_on_buffer(bh);
if (!buffer_uptodate(bh))
return -EIO;
}
offset += blksize;
bh = bh->b_this_page;
}
return 0;
}
int i, len;
p = current->mm->arg_start;
return 0;
/* We could have perhaps used atomic_t, but this and friends
below are the only places.  So it doesn't seem worthwhile.  */
inode->i_pipe->readers++;
return 0;
if (filp->f_mode & FMODE_READ)
inode->i_pipe->readers++;
if (filp->f_mode & FMODE_WRITE)
inode->i_pipe->writers++;
inode->i_pipe->writers++;
return 0;
if (error)
seq_printf(m, "tx_op: %03X %s [%d] ",
seq_printf(m, "[%d]%c ", op->nframes,
int i;
int i;
if (msg_head->nframes < 1)
int i, err;
/* we need at least one can_frame */
int datalen = head->nframes * CFSIZ;
static inline int bcm_rx_do_flush(struct bcm_op *op, int update, int index)
kfree(self->ias_obj->name);
kfree(self->ias_obj);
else umount_tree(mnt, 0);
struct usb_serial	*serial = port->serial;
struct usb_serial_port	*wport;
wport = serial->port[1];
tty_port_tty_set(&wport->port, tty);
for (idx = 0; idx < kcontrol->count; idx++, id.index++, id.numid++)
snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_TLV, &kctl->id);
for (idx = 0; idx < kcontrol->count; idx++, id.index++, id.numid++)
snd_ctl_notify(card, SNDRV_CTL_EVENT_MASK_VALUE,
&control->id);
hlist_del(&pin->m_list);
hlist_del(&pin->s_list);
for (i=fpl->count-1; i>=0; i--)
fput(fpl->fp[i]);
kfree(fpl);
if (shmflg & SHM_RND)
addr &= ~(shmlba - 1);	   /* round down */
long do_shmat(int shmid, char __user *shmaddr, int shmflg, ulong *raddr,
unsigned long shmlba)
return error;
if ((res = tipc_bearer_init()) ||
(res = tipc_cltr_init()) ||
static int net_init(void)
{
memset(&tipc_net, 0, sizeof(tipc_net));
tipc_net.zones = kcalloc(tipc_max_zones + 1, sizeof(struct _zone *), GFP_ATOMIC);
if (!tipc_net.zones) {
return -ENOMEM;
}
return 0;
}
goto exit;
if (!media_list)
if (!tipc_bearers)
return;
kfree(tipc_bearers);
kfree(media_list);
tipc_bearers = NULL;
media_list = NULL;
} else {
kfree(tipc_bearers);
kfree(media_list);
tipc_bearers = NULL;
media_list = NULL;
res = -ENOMEM;
}
write_unlock_bh(&tipc_net_lock);
return res;
}
int tipc_bearer_init(void)
{
int res;
write_lock_bh(&tipc_net_lock);
tipc_bearers = kcalloc(MAX_BEARERS, sizeof(struct bearer), GFP_ATOMIC);
media_list = kcalloc(MAX_MEDIA, sizeof(struct media), GFP_ATOMIC);
if (tipc_bearers && media_list) {
res = 0;
goto discard;
* in the interest of security over speed.
if (msg->msg_namelen >= sizeof(struct sockaddr_mISDN)) {
msg->msg_namelen = sizeof(struct sockaddr_mISDN);
maddr = (struct sockaddr_mISDN *)msg->msg_name;
struct sockaddr_mISDN	*maddr;
} else {
if (msg->msg_namelen)
printk(KERN_WARNING "%s: too small namelen %d\n",
__func__, msg->msg_namelen);
msg->msg_namelen = 0;
if (sk_filter(sk, skb))
if (sk_filter(sk, skb))
memcpy(msg->msg_name, &sa, sizeof(struct sockaddr_pn));
if (msg->msg_name != NULL)
if (addr_len)
*addr_len = sizeof(sa);
* rflags is the old, "raw" value of the flags.  The new value has
* not been saved yet.
kvm_vcpu_check_singlestep(vcpu, rflags, &r);
static struct pktcdvd_device *pkt_find_dev_from_minor(int dev_minor)
.match_data.cmp		= type->match,
return ERR_PTR(-ENOKEY);
if (!ctx.match_data.cmp)
.match_data.cmp		= type->match,
if (!index_key.type->match || !index_key.type->instantiate ||
return strcmp(key->description, match_data->raw_data) == 0;
}
int user_match(const struct key *key, const struct key_match_data *match_data)
{
EXPORT_SYMBOL_GPL(user_match);
/*
void sock_release(struct socket *sock)
sock_release(SOCKET_I(inode));
if (_payload) {
_snd_timer_stop(slave, 1, SNDRV_TIMER_EVENT_RESOLUTION);
spin_unlock_irq(&slave_active_lock);
spin_lock_irq(&slave_active_lock);
while (bytes) {
brcmf_fweh_process_skb(ifp->drvr, skb);
brcmf_fweh_process_skb(ifp->drvr, skb);
if (test_facility(156)) {
if (oldmm->context.asce_limit < mm->context.asce_limit)
crst_table_downgrade(mm, oldmm->context.asce_limit);
INIT_LIST_HEAD(&mm->context.gmap_list);
return (pgd_t *) crst_table_alloc(mm);
spin_lock_init(&mm->context.list_lock);
parse_rock_ridge_inode(de, inode);
parse_rock_ridge_inode(de, inode);
void *site;
/*
* start_site can be concurrently reset by
* timer_stats_timer_clear_start_info()
*/
site = READ_ONCE(timer->start_site);
if (likely(!site))
timer_stats_update_stats(timer, timer->start_pid, site,
timer->function, timer->start_comm,
timer->flags);
timer_stats_account_timer(timer);
timer_stats_timer_set_start_info(&dwork->timer);
static inline void timer_stats_timer_set_start_info(struct timer_list *timer)
{
}
static inline void timer_stats_timer_set_start_info(struct timer_list *timer)
{
if (likely(!timer_stats_active))
return;
__timer_stats_timer_set_start_info(timer, __builtin_return_address(0));
}
static inline void init_timer_stats(void)
{
}
timer->start_site = NULL;
}
#else
static inline void timer_stats_timer_clear_start_info(struct timer_list *timer)
{
}
#endif
static inline void timer_stats_timer_clear_start_info(struct timer_list *timer)
{
#ifdef CONFIG_TIMER_STATS
char tmp[TASK_COMM_LEN + 1];
#endif
#ifdef CONFIG_TIMER_STATS
SEQ_printf(m, ", ");
print_name_offset(m, timer->start_site);
memcpy(tmp, timer->start_comm, TASK_COMM_LEN);
tmp[TASK_COMM_LEN] = 0;
SEQ_printf(m, ", %s/%d", tmp, timer->start_pid);
#endif
timer_stats_timer_set_start_info(&dwork->timer);
fp->binder = ref->node->ptr;
fp->cookie = ref->node->cookie;
binder_inc_node(ref->node, fp->hdr.type == BINDER_TYPE_BINDER,
trace_binder_transaction_ref_to_node(t, ref);
binder_inc_ref(new_ref, fp->hdr.type == BINDER_TYPE_HANDLE,
ref->debug_id, ref->desc, ref->node->debug_id,
(u64)ref->node->ptr);
struct binder_ref *new_ref;
new_ref = binder_get_ref_for_node(target_proc, ref->node);
struct binder_ref *ref;
return -ENOMEM;
if (!new_ref)
ref = binder_get_ref(proc, fp->handle,
fp->hdr.type == BINDER_TYPE_HANDLE);
if (!ref) {
NULL);
trace_binder_transaction_ref_to_ref(t, ref, new_ref);
ref->debug_id, ref->desc, new_ref->debug_id,
new_ref->desc, ref->node->debug_id);
if (ref->node->proc == target_proc) {
fp->handle = new_ref->desc;
new_ref->desc = (node == context->binder_context_mgr_node) ? 0 : 1;
proc->pid, new_ref->debug_id, new_ref->desc,
if (desc < ref->desc) {
} else if (desc > ref->desc) {
} else if (need_strong_ref && !ref->strong) {
new_ref->debug_id = atomic_inc_return(&binder_last_id);
struct binder_ref *ref = NULL;
if (target == 0 &&
if (ctx_mgr_node) {
ref = binder_get_ref_for_node(proc,
ctx_mgr_node);
if (ref && ref->desc != target) {
binder_user_error("%d:%d tried to acquire reference to desc 0, got %d instead\n",
proc->pid, thread->pid,
ref->desc);
}
if (ref == NULL)
ref = binder_get_ref(proc, target,
cmd == BC_ACQUIRE ||
cmd == BC_RELEASE);
trace_binder_transaction_node_to_ref(t, node, ref);
ref->debug_id, ref->desc);
fp->handle = ref->desc;
ref = binder_get_ref_for_node(target_proc, node);
if (!ref)
return -ENOMEM;
struct binder_ref *ref;
binder_inc_ref(ref, fp->hdr.type == BINDER_TYPE_HANDLE, &thread->todo);
new_ref->desc = (node == context->binder_context_mgr_node) ? 0 : 1;
proc->pid, new_ref->debug_id, new_ref->desc,
struct binder_context *context = proc->context;
new_ref->debug_id = atomic_inc_return(&binder_last_id);
struct binder_ref *ref;
ref = binder_get_ref(proc, fp->handle,
hdr->type == BINDER_TYPE_HANDLE);
binder_dec_ref(ref, hdr->type == BINDER_TYPE_HANDLE);
if (write)
return -EINVAL;
else {
len = svc_print_xprts(tmpbuf, sizeof(tmpbuf));
if (!access_ok(VERIFY_WRITE, buffer, len))
return -EFAULT;
if (__copy_to_user(buffer, tmpbuf, len))
return -EFAULT;
}
*lenp -= len;
*ppos += len;
return 0;
int len;
static int ecryptfs_parse_options(struct ecryptfs_sb_info *sbi, char *options)
int len = 0;
len += snprintf(page + len, count - len,
"pages  : %li bytes (%li pages per %likB)\n",
pages * PAGE_SIZE, pages, PAGE_SIZE / 1024);
len += snprintf(page + len, count - len,
"buffer %d : ID %08x : type %s\n",
devno, mem->id, types[mem->buffer.dev.type]);
len += snprintf(page + len, count - len,
"  addr = 0x%lx, size = %d bytes\n",
(unsigned long)mem->buffer.addr, (int)mem->buffer.bytes);
return len;
return (int)count;
if (count > ARRAY_SIZE(buf) - 1)
count = ARRAY_SIZE(buf) - 1;
buf[ARRAY_SIZE(buf) - 1] = '\0';
return (int)count;
return (int)count;
return (int)count;
return (int)count;
if (IS_ERR(handle))
ion_free(client, handle);
ion_handle_put(handle);
handle = ion_handle_get_by_id(client, data.handle.handle);
static struct ion_handle *ion_handle_get_by_id(struct ion_client *client,
ion_handle_put(handle);
void ion_free(struct ion_client *client, struct ion_handle *handle)
msg->msg_namelen = 0;
if (sig == SIGCHLD &&
*flags &= ~FOLL_WRITE;
/* Some code in the 64bit emulation may not be 64bit clean.
Don't take any chances. */
if (test_tsk_thread_flag(child, TIF_IA32))
value &= 0xffffffff;
printk("minix_bmap: block<0\n");
printk("minix_bmap: block>big\n");
printk("minix_bmap: block<0\n");
printk("minix_bmap: block>big\n");
old_end, old_pmd, new_pmd,
bool need_flush = false;
&need_flush);
new_pmd, new_addr, need_rmap_locks, &need_flush);
if (need_flush)
flush_tlb_range(vma, old_end-len, old_addr);
if (new_ptl != old_ptl)
spin_unlock(new_ptl);
else
*need_flush = true;
if (pmd_present(pmd) && pmd_dirty(pmd))
pmd_t *old_pmd, pmd_t *new_pmd, bool *need_flush)
mutex_lock(&dst_ctx->mutex);
mutex_lock(&src_ctx->mutex);
mutex_unlock(&src_ctx->mutex);
struct inode *inode = mapping->host;
int err;
if( current->euid != 0 )	/* root only */
if( current->euid != 0 )	/* root only */
if( current->euid != 0 )	/* root only */
if( current->euid != 0 )	/* root only */
syscall_page = (void *)get_zeroed_page(GFP_ATOMIC);
indir = kmalloc(full_size, GFP_USER);
data = kmalloc(gstrings.len * ETH_GSTRING_LEN, GFP_USER);
return;
}
skb_copy_bits(from, 0, skb_put(to, hlen), hlen);
if (len <= skb_tailroom(to)) {
skb_copy_bits(from, 0, skb_put(to, len), len);
skb_zerocopy(skb, entskb, data_len, hlen);
skb_zerocopy(user_skb, skb, skb->len, hlen);
dev_err(&sdev->udev->dev, "get pipe, epnum %d\n", epnum);
dev_err(&sdev->udev->dev, "no such endpoint?, %d\n",
dev_err(&sdev->udev->dev, "get pipe() invalid epnum %d\n", epnum);
return ERR_PTR(-EFAULT);
return ERR_PTR(-EINVAL);
return ERR_PTR(ret);
filp = dentry_open(dentry, mqueue_mnt, oflag);
if (!IS_ERR(filp))
dget(dentry);
return filp;
struct file *filp;
if (u_attr != NULL) {
filp = (oflag & O_EXCL) ? ERR_PTR(-EEXIST) :
do_open(dentry, oflag);
} else
filp = (dentry->d_inode) ? do_open(dentry, oflag) :
ERR_PTR(-ENOENT);
dput(dentry);
out_putfd:
if (!replace && card->user_ctl_count >= MAX_USER_CONTROLS)
return -ENOMEM;
down_write(&card->controls_rwsem);
_kctl = snd_ctl_find_id(card, &info->id);
err = 0;
if (_kctl) {
if (replace)
err = snd_ctl_remove(card, _kctl);
else
err = -EBUSY;
} else {
if (replace)
err = -ENOENT;
up_write(&card->controls_rwsem);
if (err < 0)
return err;
if (BPF_CLASS(insn->code) != BPF_ALU64) {
/* 32-bit ALU ops are (32,32)->64 */
coerce_reg_to_size(dst_reg, 4);
coerce_reg_to_size(&src_reg, 4);
if (umax_val > 63) {
/* Shifts greater than 63 are undefined.  This includes
* shifts by a negative number.
if (umax_val > 63) {
/* Shifts greater than 63 are undefined.  This includes
* shifts by a negative number.
/* if we knew anything about the old value, we're not
* equal, because we can't know anything about the
* scalar value of the pointer in the new value.
return rold->umin_value == 0 &&
rold->umax_value == U64_MAX &&
rold->smin_value == S64_MIN &&
rold->smax_value == S64_MAX &&
tnum_is_unknown(rold->var_off);
struct dentry *new = d_alloc(base, name);
struct dentry * dentry = d_alloc(parent, name);
cn_del_callback(&dev->id);
err = cn_add_callback(&dev->id, "connector", &cn_callback);
if (err) {
cn_already_initialized = 0;
cn_queue_free_dev(dev->cbdev);
netlink_kernel_release(dev->nls);
return -EINVAL;
}
int err;
dev->id.idx = cn_idx;
dev->id.val = cn_val;
static int cn_ctl_msg_equals(struct cn_ctl_msg *m1, struct cn_ctl_msg *m2)
{
int i;
struct cn_notify_req *req1, *req2;
if (m1->idx_notify_num != m2->idx_notify_num)
return 0;
if (m1->val_notify_num != m2->val_notify_num)
return 0;
if (m1->len != m2->len)
return 0;
if ((m1->idx_notify_num + m1->val_notify_num) * sizeof(*req1) !=
m1->len)
return 1;
req1 = (struct cn_notify_req *)m1->data;
req2 = (struct cn_notify_req *)m2->data;
for (i = 0; i < m1->idx_notify_num; ++i) {
if (req1->first != req2->first || req1->range != req2->range)
return 0;
req1++;
req2++;
}
for (i = 0; i < m1->val_notify_num; ++i) {
if (req1->first != req2->first || req1->range != req2->range)
return 0;
req1++;
req2++;
}
return 1;
}
/*
* Main connector device's callback.
*
* Used for notification of a request's processing.
*/
cn_notify(id, 1);
return;
}
size += sizeof(*ent);
ent = kzalloc(size, GFP_KERNEL);
if (!ent)
return;
ent->msg = (struct cn_ctl_msg *)(ent + 1);
memcpy(ent->msg, ctl, size - sizeof(*ent));
mutex_lock(&notify_lock);
list_add(&ent->notify_entry, &notify_list);
mutex_unlock(&notify_lock);
}
static void cn_callback(struct cn_msg *msg, struct netlink_skb_parms *nsp)
{
struct cn_ctl_msg *ctl;
struct cn_ctl_entry *ent;
u32 size;
if (msg->len < sizeof(*ctl))
return;
ctl = (struct cn_ctl_msg *)msg->data;
size = (sizeof(*ctl) + ((ctl->idx_notify_num +
ctl->val_notify_num) *
sizeof(struct cn_notify_req)));
if (msg->len != size)
return;
if (ctl->len + sizeof(*ctl) != msg->len)
return;
/*
* Remove notification.
*/
if (ctl->group == 0) {
struct cn_ctl_entry *n;
mutex_lock(&notify_lock);
list_for_each_entry_safe(ent, n, &notify_list, notify_entry) {
if (cn_ctl_msg_equals(ent->msg, ctl)) {
list_del(&ent->notify_entry);
kfree(ent);
}
}
mutex_unlock(&notify_lock);
cn_notify(id, 0);
if (client->type == USER_CLIENT)
mutex_lock(&tu->tread_sem);
mutex_unlock(&tu->tread_sem);
}
if (get_user(xarg, p)) {
mutex_unlock(&tu->tread_sem);
}
mutex_unlock(&tu->tread_sem);
static long snd_timer_user_ioctl(struct file *file, unsigned int cmd,
mutex_lock(&tu->tread_sem);
if (tu->timeri)	{	/* too late */
mutex_unlock(&tu->tread_sem);
mutex_init(&tu->tread_sem);
return -EFAULT;
if (!access_ok(VERIFY_READ, user_data, remain))
drm_gem_object_unreference_unlocked(obj);
return -EINVAL;
return -EINVAL;
drm_gem_object_unreference_unlocked(obj);
* Half the ports are for SPEED_HIGH and half for SPEED_SUPER, thus the * 2.
*out += sprintf(*out, "%16p %s",
vdev->ud.tcp_socket,
if (!access_ok(VERIFY_READ, up, sizeof(struct video_code32)) ||
copy_from_user(kp->loadwhat, up->loadwhat, sizeof(up->loadwhat)) ||
get_user(kp->datasize, &up->datasize) ||
copy_from_user(kp->data, up->data, up->datasize))
return -EFAULT;
return 0;
__dec_zone_page_state(page, NR_FILE_PAGES);
__inc_zone_page_state(newpage, NR_FILE_PAGES);
if (!PageSwapCache(page) && PageSwapBacked(page)) {
__dec_zone_page_state(page, NR_SHMEM);
__inc_zone_page_state(newpage, NR_SHMEM);
spin_unlock_irq(&mapping->tree_lock);
enum ctx_state prev_state;
prev_state = exception_enter();
X86_TRAP_SS, SIGBUS) != NOTIFY_STOP) {
preempt_conditional_sti(regs);
do_trap(X86_TRAP_SS, SIGBUS, "stack segment", regs, error_code, NULL);
preempt_conditional_cli(regs);
}
exception_exit(prev_state);
inode_double_lock(inode, pipe->inode);
inode_double_unlock(inode, pipe->inode);
inode_double_lock(inode, pipe->inode);
if (likely(!ret))
inode_double_unlock(inode, pipe->inode);
inode_double_lock(inode, pipe->inode);
inode_double_unlock(inode, pipe->inode);
/* ipc_addid() locks msq upon success. */
id = ipc_addid(&msg_ids(ns), &msq->q_perm, ns->msg_ctlmni);
if (id < 0) {
ipc_rcu_putref(msq, msg_rcu_free);
return id;
}
if (!realinode)
return ERR_PTR(-ENOENT);
if (!(uval & FUTEX_OWNER_DIED)) {
* anyone else up:
ret = unlock_futex_pi(uaddr, uval);
if (ret == -EFAULT)
goto pi_faulted;
}
if (!(uval & FUTEX_OWNER_DIED) &&
if (!reiserfs_expose_privroot(s))
s->s_root->d_op = &xattr_lookup_poison_ops;
if (reiserfs_expose_privroot(dir->d_sb))
return 0;
lock_kernel();
void pwc_isoc_cleanup(struct pwc_device *pdev)
if (copy_to_user(buf, image_buffer_addr, count))
return -EWOULDBLOCK;
int bytes_to_read;
return -ERESTARTSYS;
if (unlikely(!(status & E1000_RXD_STAT_EOP))) {
if (crng_ready()) {
if (!crng_ready()) {
(!sk2->sk_reuse        || !sk->sk_reuse)         &&
(!sk2->sk_bound_dev_if || !sk->sk_bound_dev_if
|| sk2->sk_bound_dev_if == sk->sk_bound_dev_if) &&
(*saddr_comp)(sk, sk2)                             )
hash = hash_port_and_addr(snum, inet_sk(sk)->rcv_saddr);
if (sk2->sk_hash == hash                             &&
sk2 != sk                                        &&
inet_sk(sk2)->num == snum	                     &&
int error;
sem_unlock(sma);
sem_unlock(sma);
ipc_rcu_getref(sma);
int nsems;
spin_lock(&ipcp->lock);
spin_unlock(&ipcp->lock);
static inline struct sem_array *sem_obtain_lock(struct ipc_namespace *ns, int id)
sma = sem_lock_check(ns, semid);
if (IS_ERR(sma))
return PTR_ERR(sma);
out_unlock:
err = -ERANGE;
nsems = sma->sem_nsems;
return err;
err = -EACCES;
if (ipcperms(ns, &sma->sem_perm, S_IWUGO))
goto out_unlock;
if (err)
goto out_unlock;
err = -EINVAL;
if(semnum < 0 || semnum >= nsems)
goto out_unlock;
err = 0;
int nsems;
if (val > SEMVMX || val < 0)
goto out_unlock;
sem_unlock(sma);
ipc_lock_object(&sma->sem_perm);
ipc_lock_object(&sma->sem_perm);
sem_unlock(sma);
ipc_lock_object(&sma->sem_perm);
if (un) {
if (un->semid == -1) {
rcu_read_unlock();
goto out_unlock_free;
} else {
/*
* rcu lock can be released, "un" cannot disappear:
* - sem_lock is acquired, thus IPC_RMID is
*   impossible.
* - exit_sem is impossible, it always operates on
*   current (or a dead task).
*/
rcu_read_unlock();
}
}
int undos = 0, alter = 0, max;
sem_unlock(sma);
sma = sem_obtain_lock(ns, semid);
} else
INIT_LIST_HEAD(&tasks);
rcu_read_lock();
if (un)
rcu_read_unlock();
sem_unlock(sma);
ipc_lock_by_ptr(&sma->sem_perm);
sem_unlock(sma);
rcu_read_unlock();
if (semid == -1)
sma = sem_lock_check(tsk->nsproxy->ipc_ns, un->semid);
if (IS_ERR(sma))
sem_unlock(sma);
int semid;
int i;
sem_unlock(sma);
ipc_unlock(&(sma)->sem_perm);
ipc_rcu_getref(sma);
static inline struct sem_array *sem_lock_check(struct ipc_namespace *ns,
int id)
{
struct kern_ipc_perm *ipcp = ipc_lock_check(&sem_ids(ns), id);
if (IS_ERR(ipcp))
return ERR_CAST(ipcp);
return container_of(ipcp, struct sem_array, sem_perm);
}
}
spin_lock(&sma->sem_perm.lock);
sem_unlock(sma);
spin_lock(&sma->sem_perm.lock);
sem_unlock(sma);
ipc_rcu_getref(sma);
sem_unlock(sma);
sem_unlock(sma);
ipc_lock_by_ptr(&sma->sem_perm);
ipc_rcu_putref(sma);
ipc_unlock(&(sma)->sem_perm);
ipc_rcu_getref(sma);
ipc_unlock(&(sma)->sem_perm);
spin_lock(&(sma)->sem_perm.lock);
ipc_rcu_getref(msq);
if (--container_of(ptr, struct ipc_rcu_hdr, data)->refcount > 0)
container_of(ptr, struct ipc_rcu_hdr, data)->refcount++;
ret = hermes_enable_port(hw, 0);
ret = hermes_disable_port(hw, 0);
if (pcred->tgcred->session_keyring->uid != mycred->euid ||
name_rmt->valuelen = cpu_to_be32(args->valuelen);
valuelen = be32_to_cpu(name_rmt->valuelen);
valuelen);
args->valuelen = valuelen;
if (args->valuelen < valuelen) {
args->valuelen = valuelen;
args->valuelen = valuelen;
name_rmt->valuelen = cpu_to_be32(args->valuelen);
args->valuelen = be32_to_cpu(name_rmt->valuelen);
args->valuelen);
blkcnt = xfs_attr3_rmt_blocks(mp, args->valuelen);
valuelen = args->valuelen;
int			valuelen = args->valuelen;
if (!(task->task_state_flags & SAS_TASK_STATE_DONE))
complete(&task->slow_task->completion);
spec.flags |= SMALL;
if (spec.field_width == -1) {
spec.field_width = default_width;
spec.flags |= ZEROPAD;
}
spec.base = 16;
return number(buf, end, (unsigned long) ptr, spec);
if (!rc)
return (((addr >= VSYSCALL_START) && (addr < VSYSCALL_END)) ||
((addr >= VSYSCALL32_BASE) && (addr < VSYSCALL32_END)));
if (__map_syscall32(tsk->mm, VSYSCALL32_BASE) < 0)
return NULL;
return &gate32_vma;
}
if (test_tsk_thread_flag(tsk, TIF_IA32)) {
/* lookup code assumes the pages are present. set them up
now */
SetPageReserved(virt_to_page(syscall32_page));
int err;
down_read(&mm->mmap_sem);
err = __map_syscall32(mm, address);
up_read(&mm->mmap_sem);
return err;
/* Try and get dynamic programs out of the way of the
* default mmap base, as well as whatever program they
* might try to exec.  This is because the brk will
* follow the loader, and is not movable.  */
load_bias = ELF_ET_DYN_BASE - vaddr;
if (current->flags & PF_RANDOMIZE)
load_bias += arch_mmap_rnd();
load_bias = ELF_PAGESTART(load_bias);
if (IS_ERR(*lower_file))
goto out;
page = alloc_page(GFP_KERNEL | GFP_DMA32);
if (ipv6_dev_get_saddr(ip6_dst_idev(&rt->u.dst)->dev,
static inline int stack_guard_page_start(struct vm_area_struct *vma,
unsigned long addr)
{
return (vma->vm_flags & VM_GROWSDOWN) &&
(vma->vm_start == addr) &&
!vma_growsdown(vma->vm_prev, addr);
}
/* Is the vma a continuation of the stack vma below it? */
}
static inline int vma_growsdown(struct vm_area_struct *vma, unsigned long addr)
{
return vma && (vma->vm_end == addr) && (vma->vm_flags & VM_GROWSDOWN);
static inline int vma_growsup(struct vm_area_struct *vma, unsigned long addr)
{
return vma && (vma->vm_start == addr) && (vma->vm_flags & VM_GROWSUP);
}
if (!vmm || addr + len <= vmm->vm_start)
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
start += PAGE_SIZE;
if (stack_guard_page_end(vma, end))
end -= PAGE_SIZE;
if (stack_guard_page_start(vma, start))
(!vma || addr + len <= vma->vm_start))
return (!vma || (addr + len) <= vma->vm_start);
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
/*
* Note how expand_stack() refuses to expand the stack all the way to
* abut the next virtual mapping, *unless* that mapping itself is also
* a stack mapping. We want to leave room for a guard page, after all
* (the guard page itself is not added here, that is done by the
* actual page faulting logic)
*
* This matches the behavior of the guard page logic (see mm/memory.c:
* check_stack_guard_page()), which only allows the guard page to be
* removed under these circumstances.
*/
actual_size = size;
unsigned long new_start, actual_size;
actual_size -= PAGE_SIZE;
if (actual_size > READ_ONCE(rlim[RLIMIT_STACK].rlim_cur))
if (size && (vma->vm_flags & (VM_GROWSUP | VM_GROWSDOWN)))
highest_address = vma->vm_end;
mm->highest_vm_end = vma->vm_end;
if (find_vma_intersection(mm, oldbrk, newbrk+PAGE_SIZE))
vma = find_vma(mm, addr);
struct vm_area_struct *vma;
(!vma || addr + len <= vma->vm_start))
if (address < PAGE_ALIGN(address+4))
address = PAGE_ALIGN(address+4);
else
mm->highest_vm_end = address;
gap_start = vma->vm_prev->vm_end;
gap_end = vma->vm_start;
(!vma || addr + len <= vma->vm_start))
gap_start = vma->vm_prev ? vma->vm_prev->vm_end : 0;
vma->vm_prev->vm_end : 0;
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
gap_end = vma->vm_start;
struct vm_area_struct *vma;
(!vma || addr + len <= vma->vm_start))
vma = find_vma(mm, addr);
gap_end = vma->vm_start;
gap_start = vma->vm_prev ? vma->vm_prev->vm_end : 0;
struct vm_area_struct *next;
address &= PAGE_MASK;
next = vma->vm_next;
if (next && next->vm_start == address + PAGE_SIZE) {
if (!(next->vm_flags & VM_GROWSUP))
return -ENOMEM;
}
gap_end = vma->vm_start;
vma->vm_prev->vm_end : 0;
gap_start = vma->vm_prev ? vma->vm_prev->vm_end : 0;
mm->highest_vm_end = prev ? prev->vm_end : 0;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
struct vm_area_struct *vma;
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
unsigned long max, subtree_gap;
max = vma->vm_start;
if (vma->vm_prev)
max -= vma->vm_prev->vm_end;
(stack_guard_page_start(vma, address) ||
stack_guard_page_end(vma, address + PAGE_SIZE)))
return -ENOENT;
/* For mm_populate(), just skip the stack guard page. */
if ((*flags & FOLL_POPULATE) &&
(!vma || addr + len <= vma->vm_start))
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
struct vm_area_struct *vma;
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
/* Check if we need to add a guard page to the stack */
if (check_stack_guard_page(vma, vmf->address) < 0)
return VM_FAULT_SIGSEGV;
static inline int check_stack_guard_page(struct vm_area_struct *vma, unsigned long address)
{
address &= PAGE_MASK;
if ((vma->vm_flags & VM_GROWSDOWN) && address == vma->vm_start) {
struct vm_area_struct *prev = vma->vm_prev;
/*
* Is there a mapping abutting this one below?
*
* That's only ok if it's the same stack mapping
* that has gotten split..
*/
if (prev && prev->vm_end == address)
return prev->vm_flags & VM_GROWSDOWN ? 0 : -ENOMEM;
return expand_downwards(vma, address - PAGE_SIZE);
}
if ((vma->vm_flags & VM_GROWSUP) && address + PAGE_SIZE == vma->vm_end) {
struct vm_area_struct *next = vma->vm_next;
/* As VM_GROWSDOWN but s/below/above/ */
if (next && next->vm_start == address + PAGE_SIZE)
return next->vm_flags & VM_GROWSUP ? 0 : -ENOMEM;
return expand_upwards(vma, address + PAGE_SIZE);
}
return 0;
}
/*
err = compat_put_timespec(up, &kts);
err = compat_put_timeval(up, &ktv);
pgoff = offset >> HPAGE_SHIFT;
unsigned long pgoff;
h_vm_pgoff = vma->vm_pgoff >> (HPAGE_SHIFT - PAGE_SHIFT);
v_offset = (h_pgoff - h_vm_pgoff) << HPAGE_SHIFT;
* Is this VMA fully outside the truncation point?
if (h_vm_pgoff >= h_pgoff)
vma_prio_tree_foreach(vma, &iter, root, h_pgoff, ULONG_MAX) {
unsigned long h_vm_pgoff;
if (size > ACCESS_ONCE(rlim[RLIMIT_STACK].rlim_cur) / 4) {
put_page(page);
return NULL;
}
if ((intr_info & INTR_INFO_INTR_TYPE_MASK) == INTR_TYPE_NMI_INTR)
== (INTR_TYPE_HARD_EXCEPTION | INTR_INFO_VALID_MASK);
if ((exit_intr_info & INTR_INFO_INTR_TYPE_MASK) == INTR_TYPE_NMI_INTR &&
(exit_intr_info & INTR_INFO_VALID_MASK)) {
static inline int stack_guard_page_start(struct vm_area_struct *vma,
unsigned long addr)
{
return (vma->vm_flags & VM_GROWSDOWN) &&
(vma->vm_start == addr) &&
!vma_growsdown(vma->vm_prev, addr);
}
/* Is the vma a continuation of the stack vma below it? */
}
static inline int vma_growsdown(struct vm_area_struct *vma, unsigned long addr)
{
return vma && (vma->vm_end == addr) && (vma->vm_flags & VM_GROWSDOWN);
static inline int vma_growsup(struct vm_area_struct *vma, unsigned long addr)
{
return vma && (vma->vm_start == addr) && (vma->vm_flags & VM_GROWSUP);
}
if (!vmm || addr + len <= vmm->vm_start)
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
start += PAGE_SIZE;
if (stack_guard_page_end(vma, end))
end -= PAGE_SIZE;
if (stack_guard_page_start(vma, start))
(!vma || addr + len <= vma->vm_start))
return (!vma || (addr + len) <= vma->vm_start);
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
(!vma || addr + len <= vma->vm_start))
/*
* Note how expand_stack() refuses to expand the stack all the way to
* abut the next virtual mapping, *unless* that mapping itself is also
* a stack mapping. We want to leave room for a guard page, after all
* (the guard page itself is not added here, that is done by the
* actual page faulting logic)
*
* This matches the behavior of the guard page logic (see mm/memory.c:
* check_stack_guard_page()), which only allows the guard page to be
* removed under these circumstances.
*/
actual_size = size;
unsigned long new_start, actual_size;
actual_size -= PAGE_SIZE;
if (actual_size > READ_ONCE(rlim[RLIMIT_STACK].rlim_cur))
if (size && (vma->vm_flags & (VM_GROWSUP | VM_GROWSDOWN)))
highest_address = vma->vm_end;
mm->highest_vm_end = vma->vm_end;
if (find_vma_intersection(mm, oldbrk, newbrk+PAGE_SIZE))
vma = find_vma(mm, addr);
struct vm_area_struct *vma;
(!vma || addr + len <= vma->vm_start))
if (address < PAGE_ALIGN(address+4))
address = PAGE_ALIGN(address+4);
else
mm->highest_vm_end = address;
gap_start = vma->vm_prev->vm_end;
gap_end = vma->vm_start;
(!vma || addr + len <= vma->vm_start))
gap_start = vma->vm_prev ? vma->vm_prev->vm_end : 0;
vma->vm_prev->vm_end : 0;
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
gap_end = vma->vm_start;
struct vm_area_struct *vma;
(!vma || addr + len <= vma->vm_start))
vma = find_vma(mm, addr);
gap_end = vma->vm_start;
gap_start = vma->vm_prev ? vma->vm_prev->vm_end : 0;
struct vm_area_struct *next;
address &= PAGE_MASK;
next = vma->vm_next;
if (next && next->vm_start == address + PAGE_SIZE) {
if (!(next->vm_flags & VM_GROWSUP))
return -ENOMEM;
}
gap_end = vma->vm_start;
vma->vm_prev->vm_end : 0;
gap_start = vma->vm_prev ? vma->vm_prev->vm_end : 0;
mm->highest_vm_end = prev ? prev->vm_end : 0;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
struct vm_area_struct *vma;
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
unsigned long max, subtree_gap;
max = vma->vm_start;
if (vma->vm_prev)
max -= vma->vm_prev->vm_end;
(stack_guard_page_start(vma, address) ||
stack_guard_page_end(vma, address + PAGE_SIZE)))
return -ENOENT;
/* For mm_populate(), just skip the stack guard page. */
if ((*flags & FOLL_POPULATE) &&
(!vma || addr + len <= vma->vm_start))
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
struct vm_area_struct *vma;
struct vm_area_struct *vma;
vma = find_vma(mm, addr);
(!vma || addr + len <= vma->vm_start))
/* Check if we need to add a guard page to the stack */
if (check_stack_guard_page(vma, vmf->address) < 0)
return VM_FAULT_SIGSEGV;
static inline int check_stack_guard_page(struct vm_area_struct *vma, unsigned long address)
{
address &= PAGE_MASK;
if ((vma->vm_flags & VM_GROWSDOWN) && address == vma->vm_start) {
struct vm_area_struct *prev = vma->vm_prev;
/*
* Is there a mapping abutting this one below?
*
* That's only ok if it's the same stack mapping
* that has gotten split..
*/
if (prev && prev->vm_end == address)
return prev->vm_flags & VM_GROWSDOWN ? 0 : -ENOMEM;
return expand_downwards(vma, address - PAGE_SIZE);
}
if ((vma->vm_flags & VM_GROWSUP) && address + PAGE_SIZE == vma->vm_end) {
struct vm_area_struct *next = vma->vm_next;
/* As VM_GROWSDOWN but s/below/above/ */
if (next && next->vm_start == address + PAGE_SIZE)
return next->vm_flags & VM_GROWSUP ? 0 : -ENOMEM;
return expand_upwards(vma, address + PAGE_SIZE);
}
return 0;
}
/*
user_access_begin();
if (!access_ok(infop, sizeof(*infop)))
user_access_begin();
if (!access_ok(infop, sizeof(*infop)))
user_access_begin();
if (!access_ok(infop, sizeof(*infop)))
user_access_begin();
#define user_access_begin() do { } while (0)
user_access_begin();
if (!access_ok(umask, bitmap_size / 8))
if (!access_ok(umask, bitmap_size / 8))
user_access_begin();
return retval;
user_access_begin();
retval = do_strnlen_user(str, count, max);
user_access_end();
pte = huge_ptep_get_and_clear(mm, address, huge_pte_offset(mm, address));
#ifdef CONFIG_FUTEX
if (unlikely(tsk->robust_list))
exit_robust_list(tsk);
#ifdef CONFIG_COMPAT
if (unlikely(tsk->compat_robust_list))
compat_exit_robust_list(tsk);
#endif
#endif
tty_ldisc_halt(tty);
if (hmacs->shmac_num_idents == 0 ||
hmacs->shmac_num_idents > SCTP_AUTH_NUM_HMACS) {
return crypto_skcipher_setkey(private, key, keylen);
return crypto_alloc_skcipher(name, type, mask);
crypto_free_skcipher(private);
if (sk->sk_state & (PPPOX_BOUND | PPPOX_ZOMBIE)) {
pid = nlh->nlmsg_pid;           /*pid of sending process */
/*
* Here if the dst entry we've looked up
* has a neighbour entry that is in the INCOMPLETE
* state and the src address from the flow is
* marked as OPTIMISTIC, we release the found
* dst entry and replace it instead with the
* dst entry of the nexthop router
*/
if (!((*dst)->neighbour->nud_state & NUD_VALID)) {
struct inet6_ifaddr *ifp;
struct flowi fl_gw;
int redirect;
ifp = ipv6_get_ifaddr(net, &fl->fl6_src,
(*dst)->dev, 1);
redirect = (ifp && ifp->flags & IFA_F_OPTIMISTIC);
if (ifp)
in6_ifa_put(ifp);
if (redirect) {
/*
* We need to get the dst entry for the
* default router instead
*/
dst_release(*dst);
memcpy(&fl_gw, fl, sizeof(struct flowi));
memset(&fl_gw.fl6_dst, 0, sizeof(struct in6_addr));
*dst = ip6_route_output(net, sk, &fl_gw);
if ((err = (*dst)->error))
goto out_err_release;
}
while (bytes || unlikely(!iov->iov_len && i->count)) {
case EXIT_REASON_INVEPT:
static void ptrace_triggered(struct perf_event *bp, int nmi,
record_and_restart(event, val, regs, nmi);
if (perf_event_overflow(event, nmi, &data, regs))
struct pt_regs *regs, int nmi)
static void ptrace_hbptriggered(struct perf_event *bp, int unused,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
regs, address);
regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
if (perf_event_overflow(event, 0, data, regs))
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0,
1, 0, regs, 0);
1, 0, regs, 0);
1, 0, regs, 0);
1, 0, regs, 0);
if (perf_event_overflow(event, 0, &data, regs))
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
1, 0, regs, 0);
1, 0, regs, regs->cp0_badvaddr);
if (perf_event_overflow(event, 1, &data, &regs))
if (perf_output_begin(&handle, event, header.size * (top - at), 1, 1))
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
void ptrace_triggered(struct perf_event *bp, int nmi,
1, 0, regs, regs->dar);				\
1, 0, regs, 0);					\
perf_sw_event(PERF_COUNT_SW_CPU_MIGRATIONS, 1, 1, NULL, 0);
if (perf_event_overflow(event, 0, &data, regs))
if (perf_event_overflow(event, 0, &data, regs))
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, regs->ARM_pc);
perf_sw_event(PERF_COUNT_SW_CONTEXT_SWITCHES, 1, 1, NULL, 0);
__perf_sw_event(event_id, nr, nmi, regs, addr);
extern int perf_event_overflow(struct perf_event *event, int nmi,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, addr);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0, regs, addr);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0, regs, addr);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
if (perf_event_overflow(event, 1, &data, regs))
static void kgdb_hw_overflow_handler(struct perf_event *event, int nmi,
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
1, 0, xcp, 0);
if (perf_event_overflow(event, 1, &data, regs))
if (perf_event_overflow(event, 0, &data, regs))
if (perf_event_overflow(event, 1, &data, regs)) {
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, sfar);
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, sfar);
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, addr);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN,
1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ,
1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, address);
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, address);
if (nmi) {
event->pending_wakeup = 1;
irq_work_queue(&event->pending);
} else
perf_event_wakeup(event);
perf_event_disable(event);
if (nmi) {
event->pending_wakeup = 1;
irq_work_queue(&event->pending);
} else
perf_event_wakeup(event);
int perf_event_overflow(struct perf_event *event, int nmi,
return __perf_event_overflow(event, nmi, 1, data, regs);
event->pending_disable = 1;
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ, 1, 0,
regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN, 1, 0,
regs, address);
perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
int nmi, int sample)
handle->nmi	= nmi;
if (handle->nmi) {
handle->event->pending_wakeup = 1;
irq_work_queue(&handle->event->pending);
} else
perf_event_wakeup(handle->event);
static void sample_hbp_handler(struct perf_event *bp, int nmi,
void ptrace_triggered(struct perf_event *bp, int nmi,
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, addr);
perf_sw_event(PERF_COUNT_SW_ALIGNMENT_FAULTS, 1, 0, regs, addr);
record_and_restart(event, val, regs, nmi);
if (perf_event_overflow(event, nmi, &data, regs))
if (perf_event_overflow(event, 1, &data, regs))
perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, 0, regs, 0);
static void watchdog_overflow_callback(struct perf_event *event, int nmi,
uint32_t loc;
struct sparingTable *st;
struct sparablePartitionMap *spm =
(struct sparablePartitionMap *)gpm;
map->s_partition_type = UDF_SPARABLE_MAP15;
map->s_type_specific.s_sparing.s_packet_len =
le16_to_cpu(spm->packetLength);
for (j = 0; j < spm->numSparingTables; j++) {
struct buffer_head *bh2;
loc = le32_to_cpu(
spm->locSparingTable[j]);
bh2 = udf_read_tagged(sb, loc, loc,
&ident);
map->s_type_specific.s_sparing.
s_spar_map[j] = bh2;
if (bh2 == NULL)
continue;
st = (struct sparingTable *)bh2->b_data;
if (ident != 0 || strncmp(
st->sparingIdent.ident,
UDF_ID_SPARING,
strlen(UDF_ID_SPARING))) {
brelse(bh2);
map->s_type_specific.s_sparing.
s_spar_map[j] = NULL;
}
}
map->s_partition_func = udf_get_pblock_spar15;
int i, j, offset;
spin_lock(&unix_gc_lock);
spin_unlock(&unix_gc_lock);
if (unix_sock_count) {
for (i = scm->fp->count - 1; i >= 0; i--)
unix_inflight(scm->fp->fp[i]);
}
if (!err && uru) {
/* kernel_waitid() overwrites everything in ru */
if (COMPAT_USE_64BIT_TIME)
err = copy_to_user(uru, &ru, sizeof(ru));
else
err = put_compat_rusage(&ru, uru);
}
return -EFAULT;
if (!err) {
if (err)
}
}
SYSCALL_DEFINE1(sparc_brk, unsigned long, brk)
{
/* People could try to be nasty and use ta 0x6d in 32bit programs */
return current->mm->brk;
return current->mm->brk;
return sys_brk(brk);
static int kvm_read_guest_virt(gva_t addr, void *val, unsigned int bytes,
struct kvm_vcpu *vcpu)
return kvm_read_guest_virt(dtable.base + index*8, seg_desc, sizeof(*seg_desc), vcpu);
if (kvm_read_guest(vcpu->kvm, get_tss_base_addr(vcpu, nseg_desc),
get_tss_base_addr(vcpu, nseg_desc),
if (ret == X86EMUL_PROPAGATE_FAULT) {
kvm_inject_gp(vcpu, 0);
}
ret = kvm_write_guest_virt(q, p, bytes, vcpu);
ret = kvm_read_guest_virt(q, p, bytes, vcpu);
if (kvm_read_guest_virt(addr, val, bytes, vcpu)
struct kvm_vcpu *vcpu)
gpa_t gpa = vcpu->arch.mmu.gva_to_gpa(vcpu, addr);
if (kvm_read_guest(vcpu->kvm, get_tss_base_addr(vcpu, nseg_desc),
if (kvm_read_guest(vcpu->kvm, get_tss_base_addr(vcpu, nseg_desc),
old_tss_base = vcpu->arch.mmu.gva_to_gpa(vcpu, old_tss_base);
get_tss_base_addr(vcpu, nseg_desc),
get_tss_base_addr(vcpu, nseg_desc),
if (kvm_read_guest(vcpu->kvm, get_tss_base_addr(vcpu, nseg_desc),
get_tss_base_addr(vcpu, nseg_desc),
return vcpu->arch.mmu.gva_to_gpa(vcpu, base_addr);
kvm_read_guest_virt(rip_linear, (void *)opcodes, 4, vcpu);
return kvm_write_guest_virt(dtable.base + index*8, seg_desc, sizeof(*seg_desc), vcpu);
gpa = vcpu->arch.mmu.gva_to_gpa(vcpu, addr);
#define PFERR_RSVD_MASK (1U << 3)
gpa = vcpu->arch.mmu.gva_to_gpa(vcpu, gva);
schp->pages[k] = alloc_pages(gfp_mask, order);
/*
* Tell all users of get_user/copy_from_user etc... that the content
* is no longer stable. No barriers really needed because unmapping
* should imply barriers already and the reader would hit a page fault
* if it stumbled over a reaped memory.
*/
set_bit(MMF_UNSTABLE, &mm->flags);
for (vma = mm->mmap ; vma; vma = vma->vm_next) {
if (!can_madv_dontneed_vma(vma))
continue;
/*
* Only anonymous pages have a good chance to be dropped
* without additional steps which we cannot afford as we
* are OOM already.
*
* We do not even care about fs backed pages because all
* which are reclaimable have already been reclaimed and
* we do not want to block exit_mmap by keeping mm ref
* count elevated without a good reason.
*/
if (vma_is_anonymous(vma) || !(vma->vm_flags & VM_SHARED)) {
const unsigned long start = vma->vm_start;
const unsigned long end = vma->vm_end;
tlb_gather_mmu(&tlb, mm, start, end);
mmu_notifier_invalidate_range_start(mm, start, end);
unmap_page_range(&tlb, vma, start, end, NULL);
mmu_notifier_invalidate_range_end(mm, start, end);
tlb_finish_mmu(&tlb, start, end);
}
}
while (attempts++ < MAX_OOM_REAP_RETRIES && !__oom_reap_task_mm(tsk, mm))
/*
* Tell all users of get_user/copy_from_user etc... that the content
* is no longer stable. No barriers really needed because unmapping
* should imply barriers already and the reader would hit a page fault
* if it stumbled over a reaped memory.
*/
set_bit(MMF_UNSTABLE, &mm->flags);
for (vma = mm->mmap ; vma; vma = vma->vm_next) {
if (!can_madv_dontneed_vma(vma))
continue;
/*
* Only anonymous pages have a good chance to be dropped
* without additional steps which we cannot afford as we
* are OOM already.
*
* We do not even care about fs backed pages because all
* which are reclaimable have already been reclaimed and
* we do not want to block exit_mmap by keeping mm ref
* count elevated without a good reason.
*/
if (vma_is_anonymous(vma) || !(vma->vm_flags & VM_SHARED)) {
const unsigned long start = vma->vm_start;
const unsigned long end = vma->vm_end;
tlb_gather_mmu(&tlb, mm, start, end);
mmu_notifier_invalidate_range_start(mm, start, end);
unmap_page_range(&tlb, vma, start, end, NULL);
mmu_notifier_invalidate_range_end(mm, start, end);
tlb_finish_mmu(&tlb, start, end);
}
}
static bool __oom_reap_task_mm(struct task_struct *tsk, struct mm_struct *mm)
if (!report)
if (err)
return -EFAULT;
long err = 0;
err = compat_get_bitmap(bm, nmask, nr_bits);
err |= copy_to_user(nm, bm, alloc_size);
hid_err(hid, "No output report found\n");
hid_err(hid, "NULL field\n");
hid_err(hid, "no output report found\n");
hid_err(hid, "output report is empty\n");
hid_err(hid, "not enough values in the field\n");
struct list_head *report_list = &hid->report_enum[HID_OUTPUT_REPORT].report_list;
struct hid_report *report;
struct hid_field *field;
/* Find the report to use */
if (list_empty(report_list)) {
hid_err(hid, "No output report found\n");
return -1;
}
report = list_entry(report_list->next, struct hid_report, list);
if (!report) {
hid_err(hid, "NULL output report\n");
return -1;
}
field = report->field[0];
if (!field) {
hid_err(hid, "NULL field\n");
return -1;
}
memset(report->field[0]->value, 0, sizeof(__s32)*report->field[0]->maxusage);
* Maxusage should always be 63 (maximum fields)
* likely a better way to ensure this data is clean
hid_err(hid, "NULL field\n");
return -1;
}
struct list_head *report_list = &hid->report_enum[HID_OUTPUT_REPORT].report_list;
struct hid_report *report;
struct hid_field *field;
/* Find the report to use */
if (list_empty(report_list)) {
hid_err(hid, "No output report found\n");
return -1;
}
report = list_entry(report_list->next, struct hid_report, list);
if (!report) {
hid_err(hid, "NULL output report\n");
}
field = report->field[0];
if (!field) {
else if (sk->sk_no_check_tx) {   /* UDP csum disabled */
if ((((length + (skb ? skb->len : headersize)) > mtu) ||
(sk->sk_type == SOCK_DGRAM) && !udp_get_no_check6_tx(sk)) {
mpol_put(sbinfo->mpol);
sbinfo->mpol        = config.mpol;	/* transfers initial ref */
if (!error && fcheck(fd) != filp && flock.l_type != F_UNLCK) {
page_index << PAGE_CACHE_SHIFT,
(end - page_index + 1)
page_index << PAGE_CACHE_SHIFT,
drop_futex_key_refs(&q->key);
drop_futex_key_refs(&q->key);
goto out_put_key;
out_put_key:
put_futex_key(fshared, &q.key);
goto out_put_key;
if (!signal_pending(current)) {
put_futex_key(fshared, &q.key);
}
* race with the atomic proxy lock acquition by the requeue code.
goto out_put_key;
/* Prepare to wait on uaddr. */
/* Prepare to wait on uaddr. */
* race with the atomic proxy lock acquition by the requeue code.
/* Prepare to wait on uaddr. */
get_futex_key_refs(&q->key);
atomic_inc(&fl->users);
* We are cleaning up the signal_struct here.  We delayed
* calling exit_itimers until after flush_sigqueue, just in
* case our thread-local pending queue contained a queued
* timer signal that would have been cleared in
* exit_itimers.  When that called sigqueue_free, it would
* attempt to re-take the tasklist_lock and deadlock.  This
* can never happen if we ensure that all queues the
* timer's signal might be queued on have been flushed
* first.  The shared_pending queue, and our own pending
* queue are the only queues the timer could be on, since
* there are no other threads left in the group and timer
* signals are constrained to threads inside the group.
exit_itimers(sig);
sk->sk_backlog.limit	=	sk->sk_rcvbuf << 1;
/* Set socket backlog limit. */
sk->sk_backlog.limit = sysctl_sctp_rmem[1];
if (sk->sk_backlog.len >= max(sk->sk_backlog.limit, sk->sk_rcvbuf << 1))
mm->mmap_legacy_base = mmap_legacy_base(random_factor);
if (!skip_perm_check &&
key_permission(make_key_ref(keyring, 0),
KEY_NEED_SEARCH) < 0)
continue;
struct key *find_keyring_by_name(const char *name, bool skip_perm_check)
memset(sax, 0, sizeof(sax));
return __blkdev_driver_ioctl(fc->dev->bdev, fc->dev->mode, cmd, arg);
spin_unlock_irqrestore(&tty->ctrl_lock, flags);
struct rng_alg *alg = crypto_rng_alg(rng);
struct old_rng_alg *oalg = crypto_old_rng_alg(rng);
if (oalg->rng_make_random) {
rng->generate = generate;
rng->seed = rngapi_reset;
rng->seedsize = oalg->seedsize;
return 0;
}
rng->generate = alg->generate;
rng->seed = alg->seed;
rng->seedsize = alg->seedsize;
struct crypto_rng *rng = __crypto_rng_cast(tfm);
err = tfm->seed(tfm, seed, slen);
}
err = crypto_old_rng_alg(tfm)->rng_reset(tfm, src, slen);
kzfree(buf);
return err;
}
static int rngapi_reset(struct crypto_rng *tfm, const u8 *seed,
unsigned int slen)
{
u8 *buf = NULL;
u8 *src = (u8 *)seed;
int err;
if (slen) {
buf = kmalloc(slen, GFP_KERNEL);
if (!buf)
return -ENOMEM;
memcpy(buf, seed, slen);
src = buf;
{
return &crypto_rng_tfm(tfm)->__crt_alg->cra_rng;
}
static inline struct old_rng_alg *crypto_old_rng_alg(struct crypto_rng *tfm)
return alg->cra_rng.rng_make_random ?
alg->cra_rng.seedsize : ralg->seedsize;
}
static int generate(struct crypto_rng *tfm, const u8 *src, unsigned int slen,
u8 *dst, unsigned int dlen)
{
return crypto_old_rng_alg(tfm)->rng_make_random(tfm, dst, dlen);
return tfm->generate(tfm, src, slen, dst, dlen);
return 0;
}
*ip = new_ip;
return 1;
}
return 0;
const struct exception_table_entry *fixup;
fixup = search_exception_tables(*ip);
if (fixup) {
new_ip = ex_fixup_addr(fixup);
if (fixup->fixup - fixup->insn >= 0x7ffffff0 - 4) {
/* uaccess handling not supported during early boot */
fixup = search_exception_tables(regs->ip);
if (fixup) {
new_ip = ex_fixup_addr(fixup);
return 0;
if (fixup->fixup - fixup->insn >= 0x7ffffff0 - 4) {
/* Special hack for uaccess_err */
current_thread_info()->uaccess_err = 1;
new_ip -= 0x7ffffff0;
}
regs->ip = new_ip;
return 1;
}
int fixup_exception(struct pt_regs *regs)
if (fixup_exception(regs)) {
if (!fixup_exception(regs)) {
if (fixup_exception(regs))
if (!fixup_exception(regs)) {
int mask_type;
/* AK: could wrap */
if ((pg_start + mem->page_count) > num_entries)
if ((atomic_read(&bridge->current_memory_agp) + page_count) > bridge->max_memory_agp)
sbi->s_log_groups_per_flex = sbi->s_es->s_log_groups_per_flex;
groups_per_flex = 1 << sbi->s_log_groups_per_flex;
if (!sbi->s_es->s_log_groups_per_flex) {
if (skb_csum_unnecessary(skb))
if (udp_lib_checksum_complete(skb))
vmi_ops.write_idt_entry(dt, entry, ldt_entry[0], ldt_entry[1]);
chunksize += ntohs(auth_hmacs->length);
chunksize += ntohs(auth_chunks->length);
chunksize += sizeof(sctp_supported_ext_param_t) + num_ext;
chunksize += sizeof(sctp_supported_ext_param_t) + num_ext;
chunksize += ntohs(auth_hmacs->length);
chunksize += ntohs(auth_hmacs->length);
chunksize = sizeof(init) + addrs_len + SCTP_SAT_LEN(num_types);
chunksize += ntohs(auth_chunks->length);
chunksize += ntohs(auth_chunks->length);
chunksize += sizeof(sctp_supported_ext_param_t) + num_ext;
struct ecryptfs_crypt_stat *crypt_stat,
free_page((unsigned long)virt);
virt = (char *)get_zeroed_page(GFP_KERNEL);
rc = ecryptfs_write_headers_virt(virt, PAGE_CACHE_SIZE, &size,
crypt_stat, ecryptfs_dentry);
rc = ecryptfs_write_metadata_to_xattr(ecryptfs_dentry,
crypt_stat, virt, size);
rc = ecryptfs_write_metadata_to_contents(crypt_stat,
ecryptfs_dentry, virt);
if (vlan_tx_tag_present(skb))
vlan_hwaccel_do_receive(skb);
* already set the deliver_no_wcard flag.
* be dropped at the handler.  The vlan accel path may have
dev->dev_addr))
void vlan_hwaccel_do_receive(struct sk_buff *skb)
{
struct net_device *dev = skb->dev;
struct vlan_rx_stats     *rx_stats;
skb->dev = vlan_dev_real_dev(dev);
skb->dev = dev;
skb->priority = vlan_get_ingress_priority(dev, skb->vlan_tci);
rx_stats = this_cpu_ptr(vlan_dev_info(dev)->vlan_rx_stats);
? GRO_DROP : GRO_NORMAL;
skb_gro_reset_offset(skb);
return napi_skb_finish(vlan_gro_common(napi, grp, vlan_tci, skb), skb);
if (netpoll_rx_on(skb))
return vlan_hwaccel_receive_skb(skb, grp, vlan_tci)
struct sk_buff *skb = napi_frags_skb(napi);
if (!skb)
return GRO_DROP;
if (netpoll_rx_on(skb)) {
skb->protocol = eth_type_trans(skb, skb->dev);
return vlan_hwaccel_receive_skb(skb, grp, vlan_tci)
? GRO_DROP : GRO_NORMAL;
}
return napi_frags_finish(napi, skb,
vlan_gro_common(napi, grp, vlan_tci, skb));
if (real_dev->features & NETIF_F_HW_VLAN_RX)
if (real_dev->features & NETIF_F_HW_VLAN_RX)
pr_info("8021q: device %s has buggy VLAN hw accel\n", name);
return -EOPNOTSUPP;
}
if ((real_dev->features & NETIF_F_HW_VLAN_RX) && !ops->ndo_vlan_rx_register) {
kzalloc(length + 2, GFP_KERNEL);
if (__copy_from_user(&op, dbg, sizeof(op)))
if (copy_to_user(to, ch->chunks, len))
return -EFAULT;
u32    num_chunks;
if (len <= sizeof(struct sctp_authchunks))
if (copy_from_user(&val, p, sizeof(struct sctp_authchunks)))
if (len < num_chunks)
len = num_chunks;
__u16 param_len;
if (copy_to_user(optval, hmacs->hmac_ids, len))
param_len = ntohs(hmacs->param_hdr.length);
if (len < param_len)
if (len <= sizeof(struct sctp_authchunks))
if (copy_from_user(&val, p, sizeof(struct sctp_authchunks)))
len = num_chunks;
if (put_user(len, optlen))
if (copy_to_user(to, ch->chunks, len))
return -EFAULT;
u32    num_chunks;
offset = ipv6_skip_exthdr(skb, offset, &nexthdr,
skb->tail - skb->head - offset);
* This function parses (probably truncated) exthdr set "hdr"
* of length "len". "nexthdrp" initially points to some place,
BUG();
if (len < (int)sizeof(struct ipv6_opt_hdr))
return -1;
len -= hdrlen;
ptr = ipv6_skip_exthdr(skb, ptr, &nexthdr, len);
inner_offset = ipv6_skip_exthdr(skb, sizeof(struct ipv6hdr), &nexthdr, skb->len - sizeof(struct ipv6hdr));
spec.flags |= SMALL;
if (spec.field_width == -1) {
spec.field_width = default_width;
spec.flags |= ZEROPAD;
}
spec.base = 16;
return number(buf, end, (unsigned long) ptr, spec);
if (op->len == 0 || op->src == op->dst)
if (op->flags & AES_FLAGS_USRKEY) {
if (op->flags & AES_FLAGS_COHERENT)
if (pte_valid_ng(pte)) {
* occurred.
unsigned long vm_flags = VM_READ | VM_WRITE;
*/
if (status == -EINTR || status == -ERESTARTSYS)
do_vfs_lock(filp, fl);
} else
if (!(NFS_SERVER(inode)->flags & NFS_MOUNT_NONLM)) {
/* If we were signalled we still need to ensure that
* we clean up any state on the server. We therefore
* record the lock call as having succeeded in order to
* ensure that locks_remove_posix() cleans it out when
* the process exits.
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst), IPSTATS_MIB_INHDRERRORS);
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst),
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst), IPSTATS_MIB_INTRUNCATEDPKTS);
IP6_INC_STATS_BH(ip6_dst_idev(skb->dst), IPSTATS_MIB_INHDRERRORS);
goto out;
page_cache_release(page);
spec.flags |= SMALL;
if (spec.field_width == -1) {
spec.field_width = default_width;
spec.flags |= ZEROPAD;
}
spec.base = 16;
return number(buf, end, (unsigned long) ptr, spec);
strcpy(lp->msn, cfg->eaz);
strcpy(n->num, phone->phone);
char nr[32];
strcpy(nr, setup->phone);
memcpy(devinfo.driver_name, dev->driver->driver_name, COMEDI_NAMELEN);
memcpy(devinfo.board_name, dev->board_name, COMEDI_NAMELEN);
#if defined(CONFIG_S390)
task_show_regs(m, task);
#endif
regs->gprs[6], regs->gprs[7]);
seq_printf(m, "           " FOURLONG,
regs->gprs[8], regs->gprs[9],
regs->gprs[10], regs->gprs[11]);
seq_printf(m, "           " FOURLONG,
regs->gprs[12], regs->gprs[13],
regs->gprs[14], regs->gprs[15]);
seq_printf(m, "User ACRS: %08x %08x %08x %08x\n",
task->thread.acrs[0], task->thread.acrs[1],
task->thread.acrs[2], task->thread.acrs[3]);
seq_printf(m, "           %08x %08x %08x %08x\n",
task->thread.acrs[4], task->thread.acrs[5],
task->thread.acrs[6], task->thread.acrs[7]);
seq_printf(m, "           %08x %08x %08x %08x\n",
task->thread.acrs[8], task->thread.acrs[9],
task->thread.acrs[10], task->thread.acrs[11]);
seq_printf(m, "           %08x %08x %08x %08x\n",
task->thread.acrs[12], task->thread.acrs[13],
task->thread.acrs[14], task->thread.acrs[15]);
}
/* This is called from fs/proc/array.c */
void task_show_regs(struct seq_file *m, struct task_struct *task)
{
struct pt_regs *regs;
regs = task_pt_regs(task);
seq_printf(m, "task: %p, ksp: %p\n",
task, (void *)task->thread.ksp);
seq_printf(m, "User PSW : %p %p\n",
(void *) regs->psw.mask, (void *)regs->psw.addr);
seq_printf(m, "User GPRS: " FOURLONG,
regs->gprs[0], regs->gprs[1],
regs->gprs[2], regs->gprs[3]);
seq_printf(m, "           " FOURLONG,
regs->gprs[4], regs->gprs[5],
return rq;
return fq->flush_rq;
struct request *rq = tags->rqs[tag];
/* mq_ctx of flush rq is always cloned from the corresponding req */
struct blk_flush_queue *fq = blk_get_flush_queue(rq->q, rq->mq_ctx);
if (!is_flush_request(rq, fq, tag))
* be in flight at the same time.
rq = blk_mq_tag_to_rq(hctx->tags, off + bit);
rq = blk_mq_tag_to_rq(tags, off + bit);
sas_port_delete(phy->port);
[DISCE_DESTRUCT] = sas_destruct_devices,
[DISCE_PROBE] = sas_probe_devices,
sas_discover_event(dev->port, DISCE_DESTRUCT);
struct asd_sas_port *port = ev->port;
clear_bit(DISCE_DESTRUCT, &port->disc.pending);
struct sas_discovery_event *ev = to_sas_discovery_event(work);
sas_discover_event(dev->port, DISCE_PROBE);
struct sas_discovery_event *ev = to_sas_discovery_event(work);
struct asd_sas_port *port = ev->port;
clear_bit(DISCE_PROBE, &port->disc.pending);
sas_discover_event(dev->port, DISCE_PROBE);
follow_dotdot(nd);
if (regset->core_note_type &&
kernel_fpu_begin() work consistently. */
"fxsave %1 ; fnclex",
"m" (tsk->thread.i387.fxsave)
:"memory");
"fnsave %1 ; fwait ;" GENERIC_NOP2,
memset(&lp->MacStat, 0, sizeof(lp->MacStat));
} else {
salsa20_encrypt_bytes(ctx, walk.src.virt.addr,
walk.dst.virt.addr, nbytes);
return blkcipher_walk_done(desc, &walk, 0);
}
if (likely(walk.nbytes == nbytes))
{
{
salsa20_encrypt_bytes(ctx, walk.dst.virt.addr,
walk.src.virt.addr, nbytes);
return blkcipher_walk_done(desc, &walk, 0);
}
if (likely(walk.nbytes == nbytes))
case TIOCGICOUNT:
ret = uart_get_count(state, uarg);
break;
icount.cts         = cnow.cts;
icount.dsr         = cnow.dsr;
icount.rng         = cnow.rng;
icount.dcd         = cnow.dcd;
icount.rx          = cnow.rx;
icount.tx          = cnow.tx;
icount.frame       = cnow.frame;
icount.overrun     = cnow.overrun;
icount.parity      = cnow.parity;
icount.brk         = cnow.brk;
icount.buf_overrun = cnow.buf_overrun;
return copy_to_user(icnt, &icount, sizeof(icount)) ? -EFAULT : 0;
static int uart_get_count(struct uart_state *state,
struct serial_icounter_struct __user *icnt)
alg = &salg->base;
mb();
if (likely(port->exists && !filtered))
pinctrl_unregister(gpio_dev->pctrl);
vcc_insert_socket(sk);
if (cons >= end)
if (cons >= end)
if (cons >= end)
if (cons >= end)
if (cons >= end)
xen_netbk_idx_release(netbk, pending_idx);
make_tx_response(vif, &pending_tx_info->req, XEN_NETIF_RSP_OKAY);
xen_netbk_idx_release(netbk, pending_idx);
netbk->pending_ring[index] = pending_idx;
xenvif_put(vif);
}
xenvif_put(vif);
xen_netbk_idx_release(netbk, pending_idx);
xen_netbk_idx_release(netbk, pending_idx);
pending_ring_idx_t index;
xen_netbk_idx_release(netbk, pending_idx);
struct pending_tx_info *pending_tx_info = netbk->pending_tx_info;
struct xenvif *vif = pending_tx_info[pending_idx].vif;
struct xen_netif_tx_request *txp;
txp = &netbk->pending_tx_info[pending_idx].req;
make_tx_response(vif, txp, XEN_NETIF_RSP_ERROR);
index = pending_index(netbk->pending_prod++);
netbk->pending_ring[index] = pending_idx;
if (unlikely(err)) {
pending_ring_idx_t index;
index = pending_index(netbk->pending_prod++);
txp = &pending_tx_info[pending_idx].req;
make_tx_response(vif, txp, XEN_NETIF_RSP_ERROR);
void *kaddr;
struct gfs2_quota *qp;
s64 value;
int err = -EIO;
goto unlock;
goto unlock;
qp = kaddr + offset;
value = (s64)be64_to_cpu(qp->qu_value) + change;
qp->qu_value = cpu_to_be64(value);
qd->qd_qb.qb_value = qp->qu_value;
if (fdq) {
if (fdq->d_fieldmask & FS_DQ_BSOFT) {
qp->qu_warn = cpu_to_be64(fdq->d_blk_softlimit);
qd->qd_qb.qb_warn = qp->qu_warn;
}
if (fdq->d_fieldmask & FS_DQ_BHARD) {
qp->qu_limit = cpu_to_be64(fdq->d_blk_hardlimit);
qd->qd_qb.qb_limit = qp->qu_limit;
}
}
goto unlock;
unlock:
sctp_skb_set_owner_r(skb, newsk);
sctp_skb_set_owner_r(skb, newsk);
sctp_sock_rfree(skb);
sctp_sock_rfree(skb);
} else if (ctx->might_cancel) {
timerfd_remove_cancel(ctx);
page = alloc_page_vma(gfp | __GFP_ZERO, &pvma, 0);
unregister_key_type(&key_type_dns_resolver);
argp->end = p + (argp->pagelen>>2);
argp->end = p + (PAGE_SIZE>>2);
ret = put_user(task_thread_info(child)->tp_value,
regs->uregs[reg] = current_thread_info()->tp_value;
thread->tp_value = regs->ARM_r0;
atomic_set(&new->count, 0);
if (!atomic_add_unless(&ucounts->count, 1, INT_MAX))
(NETIF_F_SG | NETIF_F_HIGHDMA | NETIF_F_FRAGLIST)
struct task_struct *reaper = get_proc_task(filp->f_path.dentry->d_inode);
unsigned int nr = filp->f_pos - FIRST_PROCESS_ENTRY;
if (ret != -EEXIST)
goto error;
ret = 0;
}
if (ret < 0) {
* and other value on any other error
BUG_ON(new->thread_keyring);
* Install a process keyring directly to a credentials struct.
* Install a fresh thread keyring, discarding the old one.
* Returns -EEXIST if there was already a process keyring, 0 if one installed,
* Make sure a process keyring is installed for the current process.  The
* existing process keyring is not replaced.
* Returns 0 if there is a process keyring by the end of this function, some
* error otherwise.
return ret != -EEXIST ? ret : 0;
* Install a session keyring directly to a credentials struct.
* Install a fresh thread keyring, discarding the old one.
return link_pipe(ipipe, opipe, len, flags);
return -EINVAL;
* Link ipipe to the two output pipes, consuming as we go along.
if (ipipe && opipe)
rinfo = kmalloc(SZ_SG_REQ_INFO * SG_MAX_QUEUE,
GFP_KERNEL);
addr = kmap_atomic(page, KM_USER0);
if (to_user)
ret = __copy_to_user_inatomic(ptr, addr + offset, bytes);
else
ret = __copy_from_user_inatomic(addr + offset, ptr, bytes);
kunmap_atomic(addr, KM_USER0);
if (ret) {
addr = kmap(page);
if (to_user)
ret = copy_to_user(ptr, addr + offset, bytes);
else
ret = copy_from_user(addr + offset, ptr, bytes);
kunmap(page);
if (ret)
return -EFAULT;
return 0;
if (to_user)
else
dprintk(2,"vm_close %p [count=%d,vma=%08lx-%08lx]\n",map,
dprintk(2,"vm_open %p [count=%d,vma=%08lx-%08lx]\n",map,
map = q->bufs[first]->map = kmalloc(sizeof(struct videobuf_mapping),GFP_KERNEL);
ath9k_htc_set_bssid_mask(priv, vif);
for (i = 0; i < ETH_ALEN; i++)
iter_data->mask[i] &= ~(iter_data->hw_macaddr[i] ^ mac[i]);
static void ath9k_htc_set_bssid_mask(struct ath9k_htc_priv *priv,
ath9k_htc_set_bssid_mask(priv, vif);
if (!use_xsave())
if (!use_xsave())
if (use_xsave()) {
xsave_state(&tsk->thread.fpu.state->xsave, -1);
if (use_xsave()) {
struct xsave_struct *xsave = &dst->thread.fpu.state->xsave;
memset(&xsave->xsave_hdr, 0, sizeof(struct xsave_hdr_struct));
xsave_state(xsave, -1);
if (!use_xsave())
else
xrstor_state(init_xstate_buf, -1);
/* clean state in init */
current_thread_info()->status = 0;
clear_used_math();
if (use_xsave())
} else if (!use_xsave()) {
struct i387_fxsave_struct *fx = &fpu->state->fxsave;
if (use_xsave())
if (use_xsave())
clts();
* This is same as math_state_restore(). But use_xsave() is not yet
* patched to use math_state_restore().
*/
setup_xstate_init();
current->thread.fpu.state =
alloc_bootmem_align(xstate_size, __alignof__(struct xsave_struct));
init_restore_xstate();
static inline void init_restore_xstate(void)
{
init_fpu(current);
__thread_fpu_begin(current);
xrstor_state(init_xstate_buf, -1);
}
current->thread.fpu.state =
alloc_bootmem_align(xstate_size, __alignof__(struct xsave_struct));
init_restore_xstate();
setup_xstate_init();
next_func = xstate_enable_ap;
static inline void xstate_enable_ap(void)
{
xstate_enable();
init_restore_xstate();
}
/*
if (!use_xsave())
BUG_ON(use_xsave());
xsave_init();
xsave_init();
out_dio:
goto out_dio;
truncate_pagecache(inode, ioffset);
/* Now release the pages and zero block aligned part of pages*/
struct address_space *mapping = inode->i_mapping;
truncate_pagecache_range(inode, start, end - 1);
inode->i_mtime = inode->i_ctime = ext4_current_time(inode);
* Write out all dirty pages to avoid race conditions
* Then release them.
*/
if (mapping->nrpages && mapping_tagged(mapping, PAGECACHE_TAG_DIRTY)) {
ret = filemap_write_and_wait_range(mapping, offset,
offset + len - 1);
if (ret)
return ret;
}
/*
/* Now release the pages again to reduce race window */
if (last_block_offset > first_block_offset)
truncate_pagecache_range(inode, first_block_offset,
last_block_offset);
/* Wait all existing dio workers, newcomers will block on i_mutex */
ext4_inode_block_unlocked_dio(inode);
inode_dio_wait(inode);
}
}
ext4_end_io_unwritten);
return dax_mkwrite(vma, vmf, ext4_get_block_dax,
}
}
struct super_block *sb = file_inode(vma->vm_file)->i_sb;
struct iovec *iovec)
&len, &iovec, compat);
iov_iter_init(&iter, rw, iovec, nr_segs, len);
len, iovec);
ret = rw_op(req, iovec, nr_segs, req->ki_pos);
sctp_init_cause(*errp, SCTP_ERROR_UNKNOWN_PARAM,
sctp_addto_chunk(*errp,
*errp = sctp_make_op_error_space(asoc, chunk,
ntohs(chunk->chunk_hdr->length));
if (!(staterr & E1000_RXD_STAT_EOP)) {
/* !EOP means multiple descriptors were used to store a single
* packet, also make sure the frame isn't just CRC only */
if (!(status & E1000_RXD_STAT_EOP) || (length <= 4)) {
} while ((done += bsize) < nbytes);
} while ((done += bsize) < nbytes);
} while ((done += bsize) < nbytes);
void __user *base = msg->msg_iov[i].iov_base;
size_t iov_len = msg->msg_iov[i].iov_len;
struct iovec iov[msg->msg_iovlen+1];
/* Check it now since we switch to KERNEL_DS later. */
int i;
if (!access_ok(VERIFY_READ, base, iov_len)) {
/*
* XXX: that is b0rken.  We can't mix userland and kernel pointers
* in iovec, since on a lot of platforms copy_from_user() will
* *not* work with the kernel and userland ones at the same time,
* regardless of what we do with set_fs().  And we are talking about
* econet-over-ethernet here, so "it's only ARM anyway" doesn't
* apply.  Any suggestions on fixing that code?		-- AV
*/
for (i = 0; i < msg->msg_iovlen; i++) {
if (len + 15 > dev->mtu) {
mutex_unlock(&econet_mutex);
return -EMSGSIZE;
}
mutex_unlock(&econet_mutex);
return -EFAULT;
}
iov[i+1].iov_base = base;
iov[i+1].iov_len = iov_len;
size += iov_len;
&err)) == NULL) {
mutex_unlock(&econet_mutex);
return err;
}
udpmsg.msg_iovlen = msg->msg_iovlen + 1;
update_db_bp_intercept(vcpu);
update_db_bp_intercept(&svm->vcpu);
else
struct buffer_head *page_bufs;
static void ext4_free_io_end(ext4_io_end_t *io)
{
BUG_ON(!io);
iput(io->inode);
kfree(io);
}
while (!list_empty(&EXT4_I(inode)->i_completed_io_list)){
io = list_entry(EXT4_I(inode)->i_completed_io_list.next,
if (list_empty(&EXT4_I(inode)->i_completed_io_list))
if (ret >= 0) {
if (!list_empty(&io->list))
list_del_init(&io->list);
ext4_free_io_end(io);
ext4_io_end_t *io  = container_of(work, ext4_io_end_t, work);
struct inode *inode = io->inode;
int ret = 0;
static ext4_io_end_t *ext4_init_io_end (struct inode *inode)
io->error = 0;
ret = block_write_begin(file, mapping, pos, len, flags, pagep, fsdata,
ext4_get_block);
ret = ext4_convert_unwritten_extents(inode, offset, size);
if (offset + size <= i_size_read(inode))
list_add_tail(&io_end->list,
&EXT4_I(io_end->inode)->i_completed_io_list);
iocb->private = ext4_init_io_end(inode);
if (max_blocks > DIO_MAX_BLOCKS)
max_blocks = DIO_MAX_BLOCKS;
dio_credits = ext4_chunk_trans_blocks(inode, max_blocks);
handle = ext4_journal_start(inode, dio_credits);
if (IS_ERR(handle)) {
ret = PTR_ERR(handle);
goto out;
ext4_journal_stop(handle);
handle_t *handle = NULL;
if (flags == EXT4_GET_BLOCKS_PRE_IO) {
* io_end structure was created for every async
* direct IO write to the middle of the file.
* To avoid unecessary convertion for every aio dio rewrite
* to the mid of file, here we flag the IO that is really
* need the convertion.
if (flags == EXT4_GET_BLOCKS_CONVERT) {
if (flags == EXT4_GET_BLOCKS_PRE_IO) {
if (ex && (flag != EXT4_GET_BLOCKS_PRE_IO)
if (flag != EXT4_GET_BLOCKS_PRE_IO)
offset += ipv6_optlen(exthdr);
*nexthdr = &exthdr->nexthdr;
struct ipv6_opt_hdr *exthdr =
(struct ipv6_opt_hdr *)(ipv6_hdr(skb) + 1);
return offset;
while (offset + 1 <= packet_len) {
struct xfrm_policy_walk *walk = (struct xfrm_policy_walk *) &cb->args[1];
BUILD_BUG_ON(sizeof(struct xfrm_policy_walk) >
sizeof(cb->args) - sizeof(cb->args[0]));
if (!cb->args[0]) {
cb->args[0] = 1;
xfrm_policy_walk_init(walk, XFRM_POLICY_TYPE_ANY);
}
keyptr = get_keyptr();
ret = half_md4_transform(hash, keyptr->secret);
struct keydata *keyptr;
int ret;
seq += ktime_to_ns(ktime_get_real());
seq &= (1ull << 48) - 1;
return seq;
}
u64 secure_dccp_sequence_number(__be32 saddr, __be32 daddr,
__be16 sport, __be16 dport)
{
u64 seq;
__u32 hash[4];
struct keydata *keyptr = get_keyptr();
hash[0] = (__force u32)saddr;
hash[1] = (__force u32)daddr;
hash[2] = ((__force u16)sport << 16) + (__force u16)dport;
hash[3] = keyptr->secret[11];
seq = half_md4_transform(hash, keyptr->secret);
seq |= ((u64)keyptr->count) << (32 - HASH_BITS);
__u32 secure_tcp_sequence_number(__be32 saddr, __be32 daddr,
__be16 sport, __be16 dport)
{
__u32 seq;
__u32 hash[4];
struct keydata *keyptr = get_keyptr();
/*
*  Pick a unique starting offset for each TCP connection endpoints
*  (saddr, daddr, sport, dport).
*  Note that the words are placed into the starting vector, which is
*  then mixed with a partial MD4 over random data.
*/
hash[0] = (__force u32)saddr;
hash[1] = (__force u32)daddr;
hash[2] = ((__force u16)sport << 16) + (__force u16)dport;
hash[3] = keyptr->secret[11];
seq = half_md4_transform(hash, keyptr->secret) & HASH_MASK;
seq += keyptr->count;
/*
*	As close as possible to RFC 793, which
*	suggests using a 250 kHz clock.
*	Further reading shows this assumes 2 Mb/s networks.
*	For 10 Mb/s Ethernet, a 1 MHz clock is appropriate.
*	For 10 Gb/s Ethernet, a 1 GHz clock should be ok, but
*	we also need to limit the resolution so that the u32 seq
*	overlaps less than one time per MSL (2 minutes).
*	Choosing a clock of 64 ns period is OK. (period of 274 s)
*/
seq += ktime_to_ns(ktime_get_real()) >> 6;
return seq;
}
/* Generate secure starting point for ephemeral IPV4 transport port search */
{
struct keydata *keyptr = get_keyptr();
u32 hash[12];
memcpy(hash, saddr, 16);
hash[4] = (__force u32)dport;
memcpy(&hash[5], keyptr->secret, sizeof(__u32) * 7);
return twothirdsMD4Transform((const __u32 *)daddr, hash);
}
#endif
#if defined(CONFIG_IP_DCCP) || defined(CONFIG_IP_DCCP_MODULE)
/* Similar to secure_tcp_sequence_number but generate a 48 bit value
* bit's 32-47 increase every key exchange
*       0-31  hash(source, dest)
*/
u32 secure_ipv6_port_ephemeral(const __be32 *saddr, const __be32 *daddr,
__be16 dport)
__u32 secure_tcpv6_sequence_number(__be32 *saddr, __be32 *daddr,
__be16 sport, __be16 dport)
{
__u32 seq;
__u32 hash[12];
struct keydata *keyptr = get_keyptr();
/* The procedure is the same as for IPv4, but addresses are longer.
* Thus we must use twothirdsMD4Transform.
*/
memcpy(hash, saddr, 16);
hash[4] = ((__force u16)sport << 16) + (__force u16)dport;
memcpy(&hash[5], keyptr->secret, sizeof(__u32) * 7);
seq = twothirdsMD4Transform((const __u32 *)daddr, hash) & HASH_MASK;
seq += keyptr->count;
seq += ktime_to_ns(ktime_get_real());
return seq;
}
struct keydata *keyptr = &ip_keydata[1 ^ (ip_cnt & 1)];
get_random_bytes(keyptr->secret, sizeof(keyptr->secret));
keyptr->count = (ip_cnt & COUNT_MASK) << HASH_BITS;
smp_wmb();
ip_cnt++;
}
__u32 secure_ip_id(__be32 daddr)
{
struct keydata *keyptr;
__u32 hash[4];
keyptr = get_keyptr();
/*
*  Pick a unique starting offset for each IP destination.
*  The dest ip address is placed in the starting vector,
*  which is then hashed with random data.
*/
hash[0] = (__force __u32)daddr;
hash[1] = keyptr->secret[9];
hash[2] = keyptr->secret[10];
hash[3] = keyptr->secret[11];
return half_md4_transform(hash, keyptr->secret);
}
rekey_seq_generator(NULL);
static __init int seqgen_init(void)
{
static inline struct keydata *get_keyptr(void)
{
struct keydata *keyptr = &ip_keydata[ip_cnt & 1];
smp_rmb();
return keyptr;
}
u32 secure_ipv4_port_ephemeral(__be32 saddr, __be32 daddr, __be16 dport)
{
struct keydata *keyptr = get_keyptr();
u32 hash[4];
/*
*  Pick a unique starting offset for each ephemeral port search
*  (saddr, daddr, dport) and 48bits of random data.
*/
hash[0] = (__force u32)saddr;
hash[1] = (__force u32)daddr;
hash[2] = (__force u32)dport ^ keyptr->secret[10];
hash[3] = keyptr->secret[11];
return half_md4_transform(hash, keyptr->secret);
}
* in the Appendix of RFC 1185, except that
* - it uses a 1 MHz clock instead of a 250 kHz clock
* - it performs a rekey every 5 minutes, which is equivalent
* 	to a (source,dest) tulple dependent forward jump of the
* 	clock by 0..2^(HASH_BITS+1)
*
* Thus the average ISN wraparound time is 68 minutes instead of
* 4.55 hours.
*
* SMP cleanup and lock avoidance with poor man's RCU.
* 			Manfred Spraul <manfred@colorfullife.com>
*
*/
#define COUNT_BITS 8
#define COUNT_MASK ((1 << COUNT_BITS) - 1)
#define HASH_BITS 24
#define HASH_MASK ((1 << HASH_BITS) - 1)
static __u32 twothirdsMD4Transform(__u32 const buf[4], __u32 const in[12])
{
__u32 a = buf[0], b = buf[1], c = buf[2], d = buf[3];
/* Round 1 */
ROUND(F, a, b, c, d, in[ 0] + K1,  3);
ROUND(F, d, a, b, c, in[ 1] + K1,  7);
ROUND(F, c, d, a, b, in[ 2] + K1, 11);
ROUND(F, b, c, d, a, in[ 3] + K1, 19);
ROUND(F, a, b, c, d, in[ 4] + K1,  3);
ROUND(F, d, a, b, c, in[ 5] + K1,  7);
ROUND(F, c, d, a, b, in[ 6] + K1, 11);
ROUND(F, b, c, d, a, in[ 7] + K1, 19);
ROUND(F, a, b, c, d, in[ 8] + K1,  3);
ROUND(F, d, a, b, c, in[ 9] + K1,  7);
ROUND(F, c, d, a, b, in[10] + K1, 11);
ROUND(F, b, c, d, a, in[11] + K1, 19);
/* Round 2 */
ROUND(G, a, b, c, d, in[ 1] + K2,  3);
ROUND(G, d, a, b, c, in[ 3] + K2,  5);
ROUND(G, c, d, a, b, in[ 5] + K2,  9);
ROUND(G, b, c, d, a, in[ 7] + K2, 13);
ROUND(G, a, b, c, d, in[ 9] + K2,  3);
ROUND(G, d, a, b, c, in[11] + K2,  5);
ROUND(G, c, d, a, b, in[ 0] + K2,  9);
ROUND(G, b, c, d, a, in[ 2] + K2, 13);
ROUND(G, a, b, c, d, in[ 4] + K2,  3);
ROUND(G, d, a, b, c, in[ 6] + K2,  5);
ROUND(G, c, d, a, b, in[ 8] + K2,  9);
ROUND(G, b, c, d, a, in[10] + K2, 13);
/* Round 3 */
ROUND(H, a, b, c, d, in[ 3] + K3,  3);
ROUND(H, d, a, b, c, in[ 7] + K3,  9);
ROUND(H, c, d, a, b, in[11] + K3, 11);
ROUND(H, b, c, d, a, in[ 2] + K3, 15);
ROUND(H, a, b, c, d, in[ 6] + K3,  3);
ROUND(H, d, a, b, c, in[10] + K3,  9);
ROUND(H, c, d, a, b, in[ 1] + K3, 11);
ROUND(H, b, c, d, a, in[ 5] + K3, 15);
ROUND(H, a, b, c, d, in[ 9] + K3,  3);
ROUND(H, d, a, b, c, in[ 0] + K3,  9);
ROUND(H, c, d, a, b, in[ 4] + K3, 11);
ROUND(H, b, c, d, a, in[ 8] + K3, 15);
return buf[1] + b; /* "most hashed" word */
/* Alternative: return sum of all words? */
}
#endif
#undef ROUND
#undef F
#undef G
#undef H
#undef K1
#undef K2
#undef K3
/* This should not be decreased so low that ISNs wrap too fast. */
#define REKEY_INTERVAL (300 * HZ)
/*
* Bit layout of the tcp sequence numbers (before adding current time):
* bit 24-31: increased after every key exchange
* bit 0-23: hash(source,dest)
*
* The implementation is similar to the algorithm described
hash[3] = (__force __u32)daddr[3];
return half_md4_transform(hash, keyptr->secret);
}
__u32 secure_ipv6_id(const __be32 daddr[4])
{
const struct keydata *keyptr;
__u32 hash[4];
keyptr = get_keyptr();
hash[0] = (__force __u32)daddr[0];
hash[1] = (__force __u32)daddr[1];
hash[2] = (__force __u32)daddr[2];
if ((n->nlmsg_type != RTM_GETQDISC) && !capable(CAP_NET_ADMIN))
if ((n->nlmsg_type != RTM_GETTCLASS) && !capable(CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_AUDIT_WRITE))
if (!capable(CAP_AUDIT_CONTROL))
if ((req_userhdr->cmd & 0xC000) && (!capable(CAP_NET_ADMIN)))
if (!capable(CAP_NET_ADMIN))
if (kind != 2 && !ns_capable(net->user_ns, CAP_NET_ADMIN))
return rtnl_group_changelink(net,
return do_setlink(dev, ifm, tb, ifname, modified);
if (!ns_capable(net->user_ns, CAP_NET_ADMIN)) {
static int do_setlink(struct net_device *dev, struct ifinfomsg *ifm,
static int rtnl_group_changelink(struct net *net, int group,
err = do_setlink(dev, ifm, tb, NULL, 0);
if (!capable(CAP_NET_ADMIN))
if (!ns_capable(net->user_ns, CAP_NET_ADMIN)) {
if (!capable(CAP_SYS_ADMIN)) {
if ((nlh->nlmsg_type == RTM_SETDCB) && !capable(CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_SYS_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_SYS_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!ns_capable(net->user_ns, CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
if (!capable(CAP_NET_ADMIN))
may_report_filterinfo = ns_capable(net->user_ns, CAP_NET_ADMIN);
if ((n->nlmsg_type != RTM_GETACTION) && !capable(CAP_NET_ADMIN))
} else {
printk(KERN_WARNING DRV_NAME ": %s: failed to enable MSI-X: err %d!\n",
pci_name(dev), result);
}
int otherend = pdev->xdev->otherend_id;
printk(KERN_ERR "error enable msi for guest %x status %x\n",
otherend, status);
if (!grow_buffers(bdev, block, size))
if (hstart >= hend) {
progress++;
continue;
}
if (khugepaged_scan.address > hend) {
khugepaged_scan.address = hend + HPAGE_PMD_SIZE;
progress++;
continue;
}
BUG_ON(khugepaged_scan.address & ~HPAGE_PMD_MASK);
BUG_ON(khugepaged_scan.mm_slot != mm_slot);
if (!vma->anon_vma || vma->vm_ops || vma->vm_file) {
khugepaged_scan.address = vma->vm_end;
progress++;
continue;
}
if (hstart >= hend) {
progress++;
continue;
}
BUG_ON(khugepaged_thread != current);
if (khugepaged_scan.address > hend) {
khugepaged_scan.address = hend + HPAGE_PMD_SIZE;
progress++;
continue;
}
BUG_ON(khugepaged_scan.address & ~HPAGE_PMD_MASK);
BUG_ON(khugepaged_thread != current);
BUG_ON(khugepaged_scan.mm_slot != mm_slot);
if (!vma->anon_vma || vma->vm_ops || vma->vm_file) {
khugepaged_scan.address = vma->vm_end;
progress++;
continue;
}
size = PAGE_SIZE;
}
size_t size = maxnum * sizeof(struct __fdb_entry);
if (size > PAGE_SIZE) {
while (chunk_len > 0) {
asconf_param);
int	all_param_pass = 1;
/* Verify the ASCONF packet before we process it.  */
if (SCTP_ERROR_NO_ERROR != err_code)
all_param_pass = 0;
sctp_add_asconf_response(asconf_ack,
asconf_param->crr_id, err_code,
asconf_param);
if (SCTP_ERROR_RSRC_LOW == err_code)
/* Move to the next ASCONF param. */
length = ntohs(asconf_param->param_hdr.length);
asconf_param = (void *)asconf_param + length;
chunk_len -= length;
if (!sctp_verify_asconf(asoc,
(sctp_paramhdr_t *)addip_hdr->params,
(void *)asconf_ack->chunk_end,
&err_param))
if (!sctp_verify_asconf(asoc,
addr_param = (union sctp_addr_param *)hdr->params;
length = ntohs(addr_param->p.length);
if (length < sizeof(sctp_paramhdr_t))
return sctp_sf_violation_paramlen(net, ep, asoc, type, arg,
(void *)addr_param, commands);
union sctp_addr_param	*addr_param;
&err_param))
int			length;
(sctp_paramhdr_t *)((void *)addr_param + length),
(void *)chunk->chunk_end,
&err_param))
(sctp_paramhdr_t *)addip_hdr->params,
(void *)asconf_ack->chunk_end,
if (!sctp_verify_asconf(asoc,
atomic_set(&p->ip_id_count, secure_ip_id(daddr->addr.a4));
static __inline__ void ipv6_select_ident(struct frag_hdr *fhdr)
{
static u32 ipv6_fragmentation_id = 1;
static DEFINE_SPINLOCK(ip6_id_lock);
spin_lock_bh(&ip6_id_lock);
fhdr->identification = htonl(ipv6_fragmentation_id);
if (++ipv6_fragmentation_id == 0)
ipv6_fragmentation_id = 1;
spin_unlock_bh(&ip6_id_lock);
}
return atomic_add_return(more, &p->ip_id_count) - more;
transhdrlen, mtu, flags);
ipv6_select_ident(fh);
ipv6_select_ident(fh);
ipv6_select_ident(&fhdr);
int transhdrlen, int mtu,unsigned int flags)
ipv6_select_ident(fptr);
* returns allocated block in subsequent extent or EXT_MAX_BLOCK.
if (end != EXT_MAX_BLOCK) {
if (end == EXT_MAX_BLOCK) {
if (end == EXT_MAX_BLOCK) {
return EXT_MAX_BLOCK;
return EXT_MAX_BLOCK;
* returns first allocated block from next leaf or EXT_MAX_BLOCK
&& next != EXT_MAX_BLOCK) {
if (last_blk >= EXT_MAX_BLOCK)
last_blk = EXT_MAX_BLOCK-1;
while (block < last && block != EXT_MAX_BLOCK) {
err = ext4_ext_remove_space(inode, last_block, EXT_MAX_BLOCK);
len = EXT_MAX_BLOCK;
if (b2 == EXT_MAX_BLOCK)
len1 = EXT_MAX_BLOCK - b1;
(orig_start + *len > EXT_MAX_BLOCK))  {
"[ino:orig %lu, donor %lu]\n", EXT_MAX_BLOCK,
if ((orig_start > EXT_MAX_BLOCK) ||
(donor_start > EXT_MAX_BLOCK) ||
(*len > EXT_MAX_BLOCK) ||
/* 32-bit extent-start container, ee_block */
res = 1LL << 32;
res -= 1;
snprintf(rcomp.type, CRYPTO_MAX_ALG_NAME, "%s", "compression");
memcpy(&ualg->cru_name, &alg->cra_name, sizeof(ualg->cru_name));
memcpy(&ualg->cru_driver_name, &alg->cra_driver_name,
sizeof(ualg->cru_driver_name));
memcpy(&ualg->cru_module_name, module_name(alg->cra_module),
CRYPTO_MAX_ALG_NAME);
snprintf(rl.type, CRYPTO_MAX_ALG_NAME, "%s", "larval");
snprintf(rpcomp.type, CRYPTO_MAX_ALG_NAME, "%s", "pcomp");
alg->cra_blkcipher.geniv ?: "<default>");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "blkcipher");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
snprintf(rhash.type, CRYPTO_MAX_ALG_NAME, "%s", "shash");
snprintf(rhash.type, CRYPTO_MAX_ALG_NAME, "%s", "ahash");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
alg->cra_ablkcipher.geniv ?: "<default>");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "ablkcipher");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "givcipher");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
alg->cra_ablkcipher.geniv ?: "<built-in>");
snprintf(raead.type, CRYPTO_MAX_ALG_NAME, "%s", "nivaead");
snprintf(raead.geniv, CRYPTO_MAX_ALG_NAME, "%s", aead->geniv);
snprintf(raead.type, CRYPTO_MAX_ALG_NAME, "%s", "aead");
snprintf(raead.geniv, CRYPTO_MAX_ALG_NAME, "%s",
aead->geniv ?: "<built-in>");
snprintf(rrng.type, CRYPTO_MAX_ALG_NAME, "%s", "rng");
if (current->active_mm != mm)
snprintf(rcomp.type, CRYPTO_MAX_ALG_NAME, "%s", "compression");
memcpy(&ualg->cru_name, &alg->cra_name, sizeof(ualg->cru_name));
memcpy(&ualg->cru_driver_name, &alg->cra_driver_name,
sizeof(ualg->cru_driver_name));
memcpy(&ualg->cru_module_name, module_name(alg->cra_module),
CRYPTO_MAX_ALG_NAME);
snprintf(rl.type, CRYPTO_MAX_ALG_NAME, "%s", "larval");
snprintf(rpcomp.type, CRYPTO_MAX_ALG_NAME, "%s", "pcomp");
alg->cra_blkcipher.geniv ?: "<default>");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "blkcipher");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
snprintf(rhash.type, CRYPTO_MAX_ALG_NAME, "%s", "shash");
snprintf(rhash.type, CRYPTO_MAX_ALG_NAME, "%s", "ahash");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
alg->cra_ablkcipher.geniv ?: "<default>");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "ablkcipher");
snprintf(rblkcipher.type, CRYPTO_MAX_ALG_NAME, "%s", "givcipher");
snprintf(rblkcipher.geniv, CRYPTO_MAX_ALG_NAME, "%s",
alg->cra_ablkcipher.geniv ?: "<built-in>");
snprintf(raead.type, CRYPTO_MAX_ALG_NAME, "%s", "nivaead");
snprintf(raead.geniv, CRYPTO_MAX_ALG_NAME, "%s", aead->geniv);
snprintf(raead.type, CRYPTO_MAX_ALG_NAME, "%s", "aead");
snprintf(raead.geniv, CRYPTO_MAX_ALG_NAME, "%s",
aead->geniv ?: "<built-in>");
snprintf(rrng.type, CRYPTO_MAX_ALG_NAME, "%s", "rng");
goto err;
BIO *cmsbio = NULL, *tmpin = NULL;
if (dcont && (tmpin == dcont))
do_free_upto(cmsbio, dcont);
BIO_free_all(cmsbio);
cmsbio=CMS_dataInit(cms, tmpin);
if (!cmsbio)
goto err;
if (!cms_copy_content(out, cmsbio, flags))
static int cms_copy_content(BIO *out, BIO *in, unsigned int flags)
while (f != upto);
ERR_clear_error();
if (r > 0)
return 1;
ERR_clear_error();
if (r > 0)
return 1;
return 0;
int ret = 0;
ri, pkey) > 0)
break;
goto err;
ri = NULL;
}
if (ri == NULL)
{
PKCS7err(PKCS7_F_PKCS7_DATADECODE,
PKCS7_R_NO_RECIPIENT_MATCHES_KEY);
goto err;
if (pkcs7_decrypt_rinfo(&ek, &eklen, ri, pkey) <= 0)
PKCS7_R_DECRYPTED_KEY_IS_WRONG_LENGTH);
unsigned char *ek = NULL;
int eklen;
PKCS7err(PKCS7_F_PKCS7_DATADECODE,
CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO,
CMS_R_INVALID_KEY_LENGTH);
goto err;
if (enc && !ec->key)
/* Generate random key */
if (!ec->keylen)
ec->keylen = EVP_CIPHER_CTX_key_length(ctx);
ec->key = OPENSSL_malloc(ec->keylen);
if (!ec->key)
if (EVP_CIPHER_CTX_rand_key(ctx, ec->key) <= 0)
keep_key = 1;
else if (ec->keylen != (unsigned int)EVP_CIPHER_CTX_key_length(ctx))
/* We only allow the client to restart the handshake once per
* negotiation. */
if (s->s3->flags & SSL3_FLAGS_SGC_RESTART_DONE)
{
SSLerr(SSL_F_SSL3_CHECK_CLIENT_HELLO, SSL_R_MULTIPLE_SGC_RESTARTS);
return -1;
}
if (PKCS7_is_detached(p7) || (in_bio != NULL)) {
int len = OBJ_obj2txt(obj_txt, sizeof(obj_txt), obj, 0);
BIO_write(bio, obj_txt, len);
BIO_write(bio, "\n", 1);
else {
/* Skip any fractional seconds... */
if (*str == '.') {
while ((*str >= '0') && (*str <= '9'))
str++;
int i, j;
i = ctm->length;
if (*str == 'Z')
if ((i < 11) || (i > 17))
if (i < 13)
return(0);
return(0);
top = p->top;
if (ubits <= BN_BITS2 && udp[0] == 1)
break;
int i, ubits = BN_num_bits(u), vbits = BN_num_bits(v), /* v is copy
* of p */
s->method = ssl23_get_server_method(s->version);
if (s->method == NULL)
if ((peer != NULL) && (type & EVP_PKT_SIGN))
if (i)
ssl_fill_hello_random(s, 0, p, sizeof(s->s3->client_random));
if (i + len < MDC2_BLOCK) {
bn_data = OPENSSL_malloc((num / BN_DEC_NUM + 1) * sizeof(BN_ULONG));
/* Need at least keyname + iv + some encrypted data */
if (eticklen < 48)
return 2;
if (!BUF_MEM_grow_clean(b, len + want)) {
ASN1err(ASN1_F_ASN1_D2I_READ_BIO, ERR_R_MALLOC_FAILURE);
goto err;
}
i = BIO_read(in, &(b->data[len]), want);
if (i <= 0) {
ASN1err(ASN1_F_ASN1_D2I_READ_BIO,
ASN1_R_NOT_ENOUGH_DATA);
len += i;
want -= i;
BN_set_flags(k, BN_FLG_CONSTTIME);
}
if ((dsa->flags & DSA_FLAG_NO_EXP_CONSTTIME) == 0) {
alg_k=s->s3->tmp.new_cipher->algorithm_mkey;
EVP_MD_CTX_init(&md_ctx);
if (s->s3->tmp.new_cipher->algorithm_mkey & SSL_kPSK)
if (i + inl < bl) {
* attacks. */
#if 0
#else
v[1] = TLS1_VERSION_MINOR;
#endif
else if (p[9] > SSL3_VERSION_MAJOR)
* so we simply assume TLS 1.0 to avoid protocol version downgrade
*p == SSL3_MT_CLIENT_HELLO) &&
BIGNUM a,c,d,e;
int i;
BN_init(&a);
BN_init(&c);
BN_init(&d);
BN_init(&e);
BN_bntest_rand(&a,40+i*10,0,0);
a.neg=rand_neg();
BN_sqr(&c,&a,ctx);
BN_print(bp,&a);
BN_print(bp,&a);
BN_print(bp,&c);
BN_div(&d,&e,&c,&a,ctx);
BN_sub(&d,&d,&a);
if(!BN_is_zero(&d) || !BN_is_zero(&e))
{
fprintf(stderr,"Square test failed!\n");
return 0;
}
BN_free(&a);
BN_free(&c);
BN_free(&d);
BN_free(&e);
return(1);
BN_ULONG t1,t2;
BN_ULONG t1,t2;
BN_ULONG t1,t2;
BN_ULONG t1,t2;
#ifdef BN_LLONG
BN_ULLONG t,tt;
#else
BN_ULONG bl,bh;
#endif
BN_ULONG t1,t2;
#ifdef BN_LLONG
BN_ULLONG t;
#else
BN_ULONG bl,bh;
#endif
BN_ULONG t1,t2;
#ifdef BN_LLONG
BN_ULLONG t,tt;
#else
BN_ULONG bl,bh;
#endif
BN_ULONG t1,t2;
#endif
BN_ULONG t1,t2;
#ifdef BN_LLONG
BN_ULLONG t;
#else
BN_ULONG bl,bh;
if (frag != NULL) dtls1_hm_fragment_free(frag);
if (item != NULL) OPENSSL_free(item);
if ( frag != NULL) dtls1_hm_fragment_free(frag);
if ( item != NULL) OPENSSL_free(item);
if (buf && (buf_len > 0))
if ((a == NULL) || (a->data == NULL)) {
buf[0]='\0';
return(0);
}
if (buf_len > 0)
if ((data == NULL) || (ret->length < len))
data=(unsigned char *)OPENSSL_malloc(len ? (int)len : 1);
int i;
/* Sanity check OID encoding: can't have leading 0x80 in
* subidentifiers, see: X.690 8.19.2
for (i = 0, p = *pp; i < len; i++, p++)
ret->length=(int)len;
memcpy(data,p,(int)len);
pqueue_insert(s->d1->buffered_messages, item);
if (frag_len && frag_len < msg_hdr->msg_len)
pqueue_insert(s->d1->buffered_messages, item);
if (s->session->tlsext_ecpointformatlist != NULL) OPENSSL_free(s->session->tlsext_ecpointformatlist);
bn_wexpand(rr,k*2);
bn_wexpand(t,k*2);
bn_wexpand(t,k*4);
bn_wexpand(rr,k*4);
if (s->session->peer != s->session->sess_cert->peer_key->x509)
php_stream *innerstream = (php_stream *)stream->abstract;
php_stream_close((php_stream *)stream->abstract);
php_stream *innerstream = (php_stream *)stream->abstract;
if (innerstream->wrapperdata) {
php_stream_close((php_stream *)innerstream->wrapperdata);
innerstream->wrapperdata = NULL;
zend_throw_exception_ex(phar_ce_PharException, 0 TSRMLS_CC, error);
zend_throw_exception_ex(phar_ce_PharException, 0 TSRMLS_CC, error);
ctxt->options -= XML_PARSE_DTDLOAD;
tmp = emalloc(len + 1);
memcpy(tmp, s, len);
Z_TYPE_P(ent->data) = IS_STRING;
Z_STRLEN_P(ent->data) = len;
Z_STRVAL_P(ent->data) = estrndup(s, len);
efree(tmp);
xReturn = XMLRPC_CreateValueBase64(key, Z_STRVAL_P(val), Z_STRLEN_P(val));
if ((type == xmlrpc_base64 && Z_TYPE_P(value) != IS_NULL) || type == xmlrpc_datetime) {
exif_thumbnail_build(ImageInfo TSRMLS_CC);
ImageInfo->make = estrdup(value_ptr);
ImageInfo->model = estrdup(value_ptr);
unsigned char count;
static const char newstub1_1[] = "Extract_Phar::$temp)) {\nheader('HTTP/1.0 404 Not Found');\necho \"<html>\\n <head>\\n  <title>File Not Found<title>\\n </head>\\n <body>\\n  <h1>404 - File \", $pt, \" Not Found</h1>\\n </body>\\n</html>\";\nexit;\n}\n$b = pathinfo($a);\nif (!isset($b['extension'])) {\nheader('Content-Type: text/plain');\nheader('Content-Length: ' . filesize($a));\nreadfile($a);\nexit;\n}\nif (isset($mimes[$b['extension']])) {\nif ($mimes[$b['extension']] === 1) {\ninclude $a;\nexit;\n}\nif ($mimes[$b['extension']] === 2) {\nhighlight_file($a);\nexit;\n}\nheader('Content-Type: ' .$mimes[$b['extension']]);\nheader('Content-Length: ' . filesize($a));\nreadfile($a);\nexit;\n}\n}\n\nclass Extract_Phar\n{\nstatic $temp;\nstatic $origdir;\nconst GZ = 0x1000;\nconst BZ2 = 0x2000;\nconst MASK = 0x3000;\nconst START = '";
static const int newstub_len = 6665;
#line 533 "ext/standard/var_unserializer.c"
case 'O':	goto yy4;
case 'R':	goto yy6;
case 'S':	goto yy7;
case 'a':	goto yy8;
case 'b':	goto yy9;
case 'd':	goto yy10;
case 'i':	goto yy11;
case 'r':	goto yy13;
case 's':	goto yy14;
case '}':	goto yy15;
default:	goto yy2;
++YYCURSOR;
#line 909 "ext/standard/var_unserializer.re"
if (yych == ':') goto yy17;
if (yych == ';') goto yy19;
if (yych == ':') goto yy21;
if (yych == ':') goto yy22;
if (yych == ':') goto yy23;
if (yych == ':') goto yy24;
if (yych == ':') goto yy25;
if (yych == ':') goto yy26;
if (yych == ':') goto yy27;
if (yych == ':') goto yy28;
yych = *(YYMARKER = ++YYCURSOR);
if (yych == ':') goto yy29;
goto yy3;
yy15:
#line 903 "ext/standard/var_unserializer.re"
#line 646 "ext/standard/var_unserializer.c"
goto yy31;
if (yych == '+') goto yy30;
++YYCURSOR;
#line 581 "ext/standard/var_unserializer.re"
{
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_NULL(*rval);
return 1;
}
#line 665 "ext/standard/var_unserializer.c"
yy21:
if (yych <= ',') {
if (yych == '+') goto yy33;
goto yy18;
} else {
if (yych <= '-') goto yy33;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy34;
goto yy18;
yy22:
yych = *++YYCURSOR;
if (yych == '+') goto yy36;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy37;
goto yy18;
yy23:
yych = *++YYCURSOR;
if (yych == '+') goto yy39;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy40;
yy24:
yych = *++YYCURSOR;
if (yych <= '1') goto yy42;
goto yy18;
yy25:
if (yych <= '/') {
if (yych <= ',') {
if (yych == '+') goto yy43;
goto yy18;
} else {
if (yych <= '-') goto yy44;
if (yych <= '.') goto yy45;
goto yy18;
} else {
if (yych <= 'I') {
if (yych <= '9') goto yy46;
if (yych <= 'H') goto yy18;
goto yy48;
if (yych == 'N') goto yy49;
goto yy18;
yy26:
yych = *++YYCURSOR;
if (yych <= ',') {
if (yych == '+') goto yy50;
goto yy18;
} else {
if (yych <= '-') goto yy50;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy51;
goto yy18;
yy27:
yych = *++YYCURSOR;
if (yych <= ',') {
if (yych == '+') goto yy53;
goto yy18;
} else {
if (yych <= '-') goto yy53;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy54;
goto yy18;
yy28:
if (yych == '+') goto yy56;
goto yy18;
if (yych <= '-') goto yy56;
if (yych <= '9') goto yy57;
yy29:
if (yych == '+') goto yy59;
if (yych <= '9') goto yy60;
goto yy18;
yy30:
yych = *++YYCURSOR;
if (yybm[0+yych] & 128) {
goto yy31;
}
goto yy18;
yy31:
if (yybm[0+yych] & 128) {
goto yy31;
}
if (yych <= ':') goto yy62;
goto yy18;
yy33:
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy34:
if (YYLIMIT <= YYCURSOR) YYFILL(1);
yych = *YYCURSOR;
if (yych == ';') goto yy63;
yy36:
yy37:
if (yych <= '9') goto yy37;
if (yych <= ':') goto yy65;
goto yy18;
yy39:
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy40:
if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
yych = *YYCURSOR;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy40;
if (yych <= ':') goto yy66;
goto yy18;
yy42:
yych = *++YYCURSOR;
if (yych == ';') goto yy67;
goto yy18;
yy43:
yych = *++YYCURSOR;
if (yych == '.') goto yy45;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy46;
goto yy18;
yy44:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych != '.') goto yy18;
} else {
if (yych <= '9') goto yy46;
if (yych == 'I') goto yy48;
goto yy18;
yy45:
yych = *++YYCURSOR;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy69;
goto yy18;
yy46:
++YYCURSOR;
if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
yych = *YYCURSOR;
if (yych <= ':') {
if (yych <= '.') {
if (yych <= '-') goto yy18;
goto yy69;
} else {
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy46;
goto yy18;
}
} else {
if (yych <= 'E') {
if (yych <= ';') goto yy71;
if (yych <= 'D') goto yy18;
goto yy73;
} else {
if (yych == 'e') goto yy73;
goto yy18;
}
yy48:
yych = *++YYCURSOR;
if (yych == 'N') goto yy74;
goto yy18;
yy49:
yych = *++YYCURSOR;
if (yych == 'A') goto yy75;
goto yy18;
yy50:
if (yych >= ':') goto yy18;
yy51:
++YYCURSOR;
if (YYLIMIT <= YYCURSOR) YYFILL(1);
yych = *YYCURSOR;
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy51;
if (yych == ';') goto yy76;
yy53:
yy54:
if (yych <= '9') goto yy54;
if (yych <= ':') goto yy78;
goto yy18;
yy56:
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy57:
if (YYLIMIT <= YYCURSOR) YYFILL(1);
yych = *YYCURSOR;
if (yych <= '9') goto yy57;
if (yych == ';') goto yy79;
yy59:
yy60:
if (yych <= '9') goto yy60;
if (yych <= ':') goto yy81;
goto yy18;
yy62:
if (yych == '"') goto yy82;
goto yy18;
yy63:
#line 537 "ext/standard/var_unserializer.re"
long id;
*p = YYCURSOR;
if (!var_hash) return 0;
id = parse_iv(start + 2) - 1;
if (id == -1 || var_access(var_hash, id, &rval_ref) != SUCCESS) {
if (*rval != NULL) {
var_push_dtor_no_addref(var_hash, rval);
*rval = *rval_ref;
Z_ADDREF_PP(rval);
Z_SET_ISREF_PP(rval);
#line 936 "ext/standard/var_unserializer.c"
yy65:
if (yych == '"') goto yy84;
yy66:
if (yych == '{') goto yy86;
yy67:
#line 588 "ext/standard/var_unserializer.re"
{
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_BOOL(*rval, parse_iv(start + 2));
return 1;
}
#line 954 "ext/standard/var_unserializer.c"
yy69:
if (yych <= '9') goto yy69;
goto yy73;
if (yych == 'e') goto yy73;
yy71:
#line 637 "ext/standard/var_unserializer.re"
if (*((*p)++) == '}')
return 1;
#if SOMETHING_NEW_MIGHT_LEAD_TO_CRASH_ENABLE_IF_YOU_ARE_BRAVE
zval_ptr_dtor(rval);
#endif
return 0;
ent.type = ST_BOOLEAN;
SET_STACK_VARNAME;
ALLOC_ZVAL(ent.data);
INIT_PZVAL(ent.data);
Z_TYPE_P(ent.data) = IS_BOOL;
ent.type = ST_BOOLEAN;
SET_STACK_VARNAME;
ZVAL_FALSE(&ent.data);
#line 642 "ext/standard/var_unserializer.c"
#line 582 "ext/standard/var_unserializer.c"
#line 959 "ext/standard/var_unserializer.re"
#line 585 "ext/standard/var_unserializer.c"
case 'O':	goto yy13;
case 'R':	goto yy2;
case 'S':	goto yy10;
case 'a':	goto yy11;
case 'b':	goto yy6;
case 'd':	goto yy8;
case 'i':	goto yy7;
case 'r':	goto yy4;
case 's':	goto yy9;
case '}':	goto yy14;
default:	goto yy16;
yych = *(YYMARKER = ++YYCURSOR);
if (yych == ':') goto yy95;
#line 962 "ext/standard/var_unserializer.re"
#line 646 "ext/standard/var_unserializer.c"
if (yych == ':') goto yy89;
if (yych == ';') goto yy87;
if (yych == ':') goto yy83;
if (yych == ':') goto yy77;
if (yych == ':') goto yy53;
if (yych == ':') goto yy46;
if (yych == ':') goto yy39;
if (yych == ':') goto yy32;
if (yych == ':') goto yy25;
if (yych == ':') goto yy17;
#line 956 "ext/standard/var_unserializer.re"
#line 695 "ext/standard/var_unserializer.c"
yy16:
yych = *++YYCURSOR;
goto yy3;
goto yy20;
if (yych == '+') goto yy19;
if (yybm[0+yych] & 128) {
goto yy20;
yy20:
++YYCURSOR;
if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
yych = *YYCURSOR;
if (yybm[0+yych] & 128) {
goto yy20;
}
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
++YYCURSOR;
#line 804 "ext/standard/var_unserializer.re"
{
size_t len, len2, len3, maxlen;
zend_long elements;
char *str;
zend_string *class_name;
zend_class_entry *ce;
int incomplete_class = 0;
int custom_object = 0;
zval user_func;
zval retval;
zval args[1];
if (!var_hash) return 0;
if (*start == 'C') {
custom_object = 1;
}
len2 = len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len || len == 0) {
*p = start + 2;
return 0;
}
str = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR+1) != ':') {
*p = YYCURSOR+1;
return 0;
}
len3 = strspn(str, "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377\\");
if (len3 != len)
{
*p = YYCURSOR + len3 - len;
return 0;
}
class_name = zend_string_init(str, len, 0);
do {
if(!unserialize_allowed_class(class_name, classes)) {
incomplete_class = 1;
ce = PHP_IC_ENTRY;
break;
/* Try to find class directly */
BG(serialize_lock)++;
ce = zend_lookup_class(class_name);
if (ce) {
BG(serialize_lock)--;
if (EG(exception)) {
zend_string_release(class_name);
return 0;
}
break;
}
BG(serialize_lock)--;
if (EG(exception)) {
zend_string_release(class_name);
return 0;
}
/* Check for unserialize callback */
if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0')) {
incomplete_class = 1;
ce = PHP_IC_ENTRY;
break;
}
/* Call unserialize callback */
ZVAL_STRING(&user_func, PG(unserialize_callback_func));
ZVAL_STR_COPY(&args[0], class_name);
BG(serialize_lock)++;
if (call_user_function_ex(CG(function_table), NULL, &user_func, &retval, 1, args, 0, NULL) != SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
zend_string_release(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&args[0]);
return 0;
}
php_error_docref(NULL, E_WARNING, "defined (%s) but not found", Z_STRVAL(user_func));
incomplete_class = 1;
ce = PHP_IC_ENTRY;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&args[0]);
break;
}
BG(serialize_lock)--;
zval_ptr_dtor(&retval);
if (EG(exception)) {
zend_string_release(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&args[0]);
return 0;
}
/* The callback function may have defined the class */
BG(serialize_lock)++;
if ((ce = zend_lookup_class(class_name)) == NULL) {
php_error_docref(NULL, E_WARNING, "Function %s() hasn't defined the class it was called for", Z_STRVAL(user_func));
incomplete_class = 1;
ce = PHP_IC_ENTRY;
BG(serialize_lock)--;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&args[0]);
break;
} while (1);
*p = YYCURSOR;
if (custom_object) {
int ret;
ret = object_custom(UNSERIALIZE_PASSTHRU, ce);
if (ret && incomplete_class) {
php_store_class_name(rval, ZSTR_VAL(class_name), len2);
zend_string_release(class_name);
return ret;
elements = object_common1(UNSERIALIZE_PASSTHRU, ce);
if (elements < 0) {
zend_string_release(class_name);
return 0;
if (incomplete_class) {
php_store_class_name(rval, ZSTR_VAL(class_name), len2);
zend_string_release(class_name);
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 878 "ext/standard/var_unserializer.c"
yy25:
if (yych != '+') goto yy18;
if (yych <= '-') goto yy26;
if (yych <= '9') goto yy27;
yy26:
if (yych >= ':') goto yy18;
yy27:
if (yych <= '9') goto yy27;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 793 "ext/standard/var_unserializer.re"
{
zend_long elements;
if (!var_hash) return 0;
elements = object_common1(UNSERIALIZE_PASSTHRU, ZEND_STANDARD_CLASS_DEF_PTR);
if (elements < 0 || elements >= HT_MAX_SIZE) {
return 0;
}
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 914 "ext/standard/var_unserializer.c"
yy32:
yych = *++YYCURSOR;
if (yych == '+') goto yy33;
yy33:
yy34:
if (yych <= '9') goto yy34;
if (yych >= ';') goto yy18;
if (yych != '{') goto yy18;
#line 769 "ext/standard/var_unserializer.re"
{
zend_long elements = parse_iv(start + 2);
/* use iv() not uiv() in order to check data range */
*p = YYCURSOR;
if (!var_hash) return 0;
if (elements < 0 || elements >= HT_MAX_SIZE) {
return 0;
array_init_size(rval, elements);
if (elements) {
/* we can't convert from packed to hash during unserialization, because
reference to some zvals might be keept in var_hash (to support references) */
zend_hash_real_init(Z_ARRVAL_P(rval), 0);
if (!process_nested_data(UNSERIALIZE_PASSTHRU, Z_ARRVAL_P(rval), elements, 0)) {
return 0;
return finish_nested_data(UNSERIALIZE_PASSTHRU);
}
#line 959 "ext/standard/var_unserializer.c"
yy39:
if (yych == '+') goto yy40;
if (yych <= '9') goto yy41;
yy40:
yy41:
if (yych <= '9') goto yy41;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 735 "ext/standard/var_unserializer.re"
{
size_t len, maxlen;
zend_string *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
if ((str = unserialize_str(&YYCURSOR, len, maxlen)) == NULL) {
return 0;
}
if (*(YYCURSOR) != '"') {
zend_string_free(str);
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR + 1) != ';') {
efree(str);
*p = YYCURSOR + 1;
return 0;
}
YYCURSOR += 2;
*p = YYCURSOR;
ZVAL_STR(rval, str);
return 1;
}
#line 1014 "ext/standard/var_unserializer.c"
yy46:
yych = *++YYCURSOR;
if (yych == '+') goto yy47;
if (yych <= '9') goto yy48;
yy47:
yy48:
if (yych <= '9') goto yy48;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 703 "ext/standard/var_unserializer.re"
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
str = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
if (*(YYCURSOR + 1) != ';') {
*p = YYCURSOR + 1;
YYCURSOR += 2;
*p = YYCURSOR;
ZVAL_STRINGL(rval, str, len);
#line 1067 "ext/standard/var_unserializer.c"
yy53:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych <= ',') {
if (yych == '+') goto yy57;
goto yy18;
} else {
if (yych <= '-') goto yy55;
if (yych <= '.') goto yy60;
goto yy18;
}
} else {
if (yych <= 'I') {
if (yych <= '9') goto yy58;
if (yych <= 'H') goto yy18;
goto yy56;
} else {
if (yych != 'N') goto yy18;
}
}
if (yych == 'A') goto yy76;
yy55:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych == '.') goto yy60;
goto yy18;
} else {
if (yych <= '9') goto yy58;
if (yych != 'I') goto yy18;
}
yy56:
if (yych == 'N') goto yy72;
yy57:
yych = *++YYCURSOR;
if (yych == '.') goto yy60;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy58:
if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
yych = *YYCURSOR;
if (yych <= ':') {
if (yych <= '.') {
if (yych <= '-') goto yy18;
goto yy70;
} else {
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy58;
goto yy18;
}
} else {
if (yych <= 'E') {
if (yych <= ';') goto yy63;
if (yych <= 'D') goto yy18;
goto yy65;
} else {
if (yych == 'e') goto yy65;
goto yy18;
}
}
yy60:
yych = *++YYCURSOR;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy61:
if (yych <= '9') goto yy61;
goto yy65;
if (yych == 'e') goto yy65;
yy63:
#line 694 "ext/standard/var_unserializer.re"
int newsize = target->len + add_len + 1;
int incr = target->size * 2;
newsize = newsize - (newsize % incr) + incr;
exif_error_docref("exif_read_data#error_ifd" EXIFERR_CC, ImageInfo, E_WARNING, "Illegal IFD size: 2 + x%04X*12 = x%04X > x%04X", NumDirEntries, 2+NumDirEntries*12, value_len);
exif_process_IFD_in_MAKERNOTE(ImageInfo, value_ptr, byte_count, offset_base, IFDlength, displacement TSRMLS_CC);
exif_thumbnail_build(ImageInfo TSRMLS_CC);
int old_bin_num, bin_num;
old_bin_num = ZEND_MM_SRUN_BIN_NUM(info);
bin_num = ZEND_MM_SMALL_SIZE_TO_BIN(size);
if (old_bin_num == bin_num) {
dbg = zend_mm_get_debug_info(heap, ptr);
dbg->size = real_size;
dbg->filename = __zend_filename;
dbg->orig_filename = __zend_orig_filename;
dbg->lineno = __zend_lineno;
dbg->orig_lineno = __zend_orig_lineno;
return ptr;
#line 501 "ext/standard/var_unserializer.c"
case 'O':	goto yy13;
case 'R':	goto yy2;
case 'S':	goto yy10;
case 'a':	goto yy11;
case 'b':	goto yy6;
case 'd':	goto yy8;
case 'i':	goto yy7;
case 'r':	goto yy4;
case 's':	goto yy9;
case '}':	goto yy14;
default:	goto yy16;
yych = *(YYMARKER = ++YYCURSOR);
if (yych == ':') goto yy95;
#line 877 "ext/standard/var_unserializer.re"
#line 563 "ext/standard/var_unserializer.c"
if (yych == ':') goto yy89;
if (yych == ';') goto yy87;
if (yych == ':') goto yy83;
if (yych == ':') goto yy77;
if (yych == ':') goto yy53;
if (yych == ':') goto yy46;
if (yych == ':') goto yy39;
if (yych == ':') goto yy32;
if (yych == ':') goto yy25;
if (yych == ':') goto yy17;
#line 871 "ext/standard/var_unserializer.re"
#line 612 "ext/standard/var_unserializer.c"
yy16:
yych = *++YYCURSOR;
goto yy3;
goto yy20;
if (yych == '+') goto yy19;
if (yybm[0+yych] & 128) {
goto yy20;
yy20:
++YYCURSOR;
if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
yych = *YYCURSOR;
if (yybm[0+yych] & 128) {
goto yy20;
}
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
++YYCURSOR;
#line 717 "ext/standard/var_unserializer.re"
{
size_t len, len2, len3, maxlen;
long elements;
char *class_name;
zend_class_entry *ce;
zend_class_entry **pce;
int incomplete_class = 0;
int custom_object = 0;
zval *user_func;
zval *retval_ptr;
zval **args[1];
zval *arg_func_name;
if (!var_hash) return 0;
if (*start == 'C') {
custom_object = 1;
}
INIT_PZVAL(*rval);
len2 = len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len || len == 0) {
*p = start + 2;
return 0;
}
class_name = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR+1) != ':') {
*p = YYCURSOR+1;
return 0;
}
len3 = strspn(class_name, "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377\\");
if (len3 != len)
{
*p = YYCURSOR + len3 - len;
return 0;
}
class_name = estrndup(class_name, len);
do {
/* Try to find class directly */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
ce = *pce;
break;
}
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
/* Check for unserialize callback */
if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0')) {
incomplete_class = 1;
ce = PHP_IC_ENTRY;
break;
}
/* Call unserialize callback */
MAKE_STD_ZVAL(user_func);
ZVAL_STRING(user_func, PG(unserialize_callback_func), 1);
args[0] = &arg_func_name;
MAKE_STD_ZVAL(arg_func_name);
ZVAL_STRING(arg_func_name, class_name, 1);
BG(serialize_lock)++;
if (call_user_function_ex(CG(function_table), NULL, user_func, &retval_ptr, 1, args, 0, NULL TSRMLS_CC) != SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
php_error_docref(NULL TSRMLS_CC, E_WARNING, "defined (%s) but not found", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
}
BG(serialize_lock)--;
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
}
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
/* The callback function may have defined the class */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
ce = *pce;
php_error_docref(NULL TSRMLS_CC, E_WARNING, "Function %s() hasn't defined the class it was called for", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
BG(serialize_lock)--;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
} while (1);
*p = YYCURSOR;
if (custom_object) {
int ret;
ret = object_custom(UNSERIALIZE_PASSTHRU, ce);
if (ret && incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return ret;
elements = object_common1(UNSERIALIZE_PASSTHRU, ce);
if (elements < 0) {
efree(class_name);
return 0;
if (incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 797 "ext/standard/var_unserializer.c"
yy25:
if (yych != '+') goto yy18;
if (yych <= '-') goto yy26;
if (yych <= '9') goto yy27;
yy26:
if (yych >= ':') goto yy18;
yy27:
if (yych <= '9') goto yy27;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 704 "ext/standard/var_unserializer.re"
{
long elements;
if (!var_hash) return 0;
INIT_PZVAL(*rval);
elements = object_common1(UNSERIALIZE_PASSTHRU, ZEND_STANDARD_CLASS_DEF_PTR);
if (elements < 0) {
return 0;
}
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 835 "ext/standard/var_unserializer.c"
yy32:
yych = *++YYCURSOR;
if (yych == '+') goto yy33;
yy33:
yy34:
if (yych <= '9') goto yy34;
if (yych >= ';') goto yy18;
if (yych != '{') goto yy18;
#line 683 "ext/standard/var_unserializer.re"
{
long elements = parse_iv(start + 2);
/* use iv() not uiv() in order to check data range */
*p = YYCURSOR;
if (!var_hash) return 0;
if (elements < 0) {
return 0;
INIT_PZVAL(*rval);
array_init_size(*rval, elements);
if (!process_nested_data(UNSERIALIZE_PASSTHRU, Z_ARRVAL_PP(rval), elements, 0)) {
return 0;
return finish_nested_data(UNSERIALIZE_PASSTHRU);
}
#line 877 "ext/standard/var_unserializer.c"
yy39:
if (yych == '+') goto yy40;
if (yych <= '9') goto yy41;
yy40:
yy41:
if (yych <= '9') goto yy41;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 648 "ext/standard/var_unserializer.re"
{
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
if ((str = unserialize_str(&YYCURSOR, &len, maxlen)) == NULL) {
return 0;
}
if (*(YYCURSOR) != '"') {
efree(str);
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR + 1) != ';') {
efree(str);
*p = YYCURSOR + 1;
return 0;
}
YYCURSOR += 2;
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_STRINGL(*rval, str, len, 0);
return 1;
}
#line 933 "ext/standard/var_unserializer.c"
yy46:
yych = *++YYCURSOR;
if (yych == '+') goto yy47;
if (yych <= '9') goto yy48;
yy47:
yy48:
if (yych <= '9') goto yy48;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 615 "ext/standard/var_unserializer.re"
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
str = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
if (*(YYCURSOR + 1) != ';') {
*p = YYCURSOR + 1;
return 0;
YYCURSOR += 2;
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_STRINGL(*rval, str, len, 1);
#line 987 "ext/standard/var_unserializer.c"
yy53:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych <= ',') {
if (yych == '+') goto yy57;
goto yy18;
} else {
if (yych <= '-') goto yy55;
if (yych <= '.') goto yy60;
goto yy18;
}
} else {
if (yych <= 'I') {
if (yych <= '9') goto yy58;
if (yych <= 'H') goto yy18;
goto yy56;
} else {
if (yych != 'N') goto yy18;
}
}
if (yych == 'A') goto yy76;
yy55:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych == '.') goto yy60;
goto yy18;
} else {
if (yych <= '9') goto yy58;
if (yych != 'I') goto yy18;
}
yy56:
if (yych == 'N') goto yy72;
yy57:
yych = *++YYCURSOR;
if (yych == '.') goto yy60;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy58:
if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
yych = *YYCURSOR;
if (yych <= ':') {
if (yych <= '.') {
if (yych <= '-') goto yy18;
goto yy70;
} else {
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy58;
goto yy18;
}
} else {
if (yych <= 'E') {
if (yych <= ';') goto yy63;
if (yych <= 'D') goto yy18;
goto yy65;
} else {
if (yych == 'e') goto yy65;
goto yy18;
}
}
yy60:
yych = *++YYCURSOR;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy61:
if (yych <= '9') goto yy61;
goto yy65;
if (yych == 'e') goto yy65;
yy63:
#line 605 "ext/standard/var_unserializer.re"
#line 249 "ext/standard/var_unserializer.re"
zend_hash_exists(&Z_OBJCE_PP(rval)->function_table, "__wakeup", sizeof("__wakeup"))) {
INIT_PZVAL(&fname);
ZVAL_STRINGL(&fname, "__wakeup", sizeof("__wakeup") - 1, 0);
BG(serialize_lock)++;
call_user_function_ex(CG(function_table), rval, &fname, &retval_ptr, 0, 0, 1, NULL TSRMLS_CC);
BG(serialize_lock)--;
}
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
zval *retval_ptr = NULL;
zval fname;
if (EG(exception)) {
return 0;
}
/* We've got partially constructed object on our hands here. Wipe it. */
if(Z_TYPE_PP(rval) == IS_OBJECT) {
zend_hash_clean(Z_OBJPROP_PP(rval));
zend_object_store_ctor_failed(*rval TSRMLS_CC);
}
zval_ptr_dtor(&var_hash->data[i]);
PHPWRITE(" Access Denied</h1>\n </body>\n</html>", sizeof(" Access Denied</h1>\n </body>\n</html>") - 1);
PHPWRITE(entry, entry_len);
PHPWRITE(entry, entry_len);
PHPWRITE(" Not Found</h1>\n </body>\n</html>",  sizeof(" Not Found</h1>\n </body>\n</html>") - 1);
length = MIN(length, strlen(value));
if (tmp_line[tmp_line_len - 1] == '\n') {
if (tmp_line[tmp_line_len - 1] == '\r') {
(*ret)->zero = phar_get_fp_offset(phar_get_link_source(entry TSRMLS_CC) TSRMLS_CC);
if (entry.filename[entry.filename_len - 1] == '/') {
if ((greet_packet->server_capabilities & CLIENT_SSL) && (mysql_flags & CLIENT_SSL)) {
zend_bool verify = mysql_flags & CLIENT_SSL_VERIFY_SERVER_CERT? TRUE:FALSE;
DBG_INF("Switching to SSL");
if (!PACKET_WRITE(auth_packet, conn)) {
CONN_SET_STATE(conn, CONN_QUIT_SENT);
SET_CLIENT_ERROR(*conn->error_info, CR_SERVER_GONE_ERROR, UNKNOWN_SQLSTATE, mysqlnd_server_gone);
goto end;
}
if (FAIL == conn->net->m.enable_ssl(conn->net TSRMLS_CC)) {
goto end;
int		size, rcvd;
int		lines;
if (rcvd == -1) {
if (obj->stringval == NULL) {
xmlXPathFreeObject(obj);
xmlXPathFreeObject(obj);
php_error_docref(NULL TSRMLS_CC, E_WARNING, "Handler name must be a string");
output PATH whil ^%PATH^% not. escapeshellcmd will escape all %.
char newpath[MAXPATHLEN];
free(rbuf);
RETURN_STRING(ptr, 0);
*
* XXX: an unreasonable amount of precision may be specified
* resulting in overflow of num_buf. Currently we
* ignore this possibility.
*
* XXX: an unreasonable amount of precision may be specified
* resulting in overflow of num_buf. Currently we
* ignore this possibility.
strlcat(passwd, "$", 1);
if (Z_TYPE_P(obj) == IS_STRING) {
/* {{{ proto bool is_subclass_of(mixed object, string class_name)
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zs", &obj, &class_name, &class_name_len) == FAILURE) {
offset_base, IFDlength, displacement, section_index, 0, maker_note->tag_table TSRMLS_CC)) {
encoded_word = NULL;
if ((mode & PHP_ICONV_MIME_DECODE_STRICT)) {
scan_stat = 12;
} else {
scan_stat = 0;
}
if (*matchingpath == OP_RREF)
object_init_ex(&obj, pce);
/* Merge current hashtable with object's default properties */
zend_hash_merge(Z_OBJPROP(obj),
Z_ARRVAL(ent2->data),
zval_add_ref, 0);
if (incomplete_class) {
php_store_class_name(&obj, Z_STRVAL(ent1->data), Z_STRLEN(ent1->data));
/* Clean up old array entry */
zval_ptr_dtor(&ent2->data);
/* Set stack entry to point to the newly created object */
ZVAL_COPY_VALUE(&ent2->data, &obj);
ht->nTableSize = zend_hash_check_size(nSize);
ch = 0;
im->tpixels[y][x] = 0;
if (pos > CDF_SEC_SIZE(h) * sst->sst_len) {
pos, CDF_SEC_SIZE(h) * sst->sst_len));
wp->socket_mode = 0666;
number = image.ncolors;
if (nbytes < (offset + 2))
if (nbytes < (offset + 8))
if (nbytes < (offset + 4))
if (nbytes < (offset + 1)) /* should always be true */
if (nbytes < (offset + 2))
if (nbytes < (offset + m->vallen))
if (nbytes < offset)
if (nbytes < (offset + 4))
if (nbytes < offset)
if (nbytes < (offset + 2))
if (nbytes < (offset + 4))
if (nbytes < offset)
if (nbytes < (offset + 1))
if (nbytes < (offset + 4))
if (nbytes < (offset + 2))
if (nbytes < (offset + 4))
/* check size */
if (crop->width<=0 || crop->height<=0) {
return NULL;
}
if (dst == NULL) {
return NULL;
}
text, 0, 0, &printed_something, &need_separator,
int mode, int text)
BINTEST, text);
ssi->si_count = CDF_TOLE2(si->si_count);
for (i = 0; i < CDF_TOLE4(si->si_count); i++) {
if (i >= CDF_LOOP_LIMIT) {
DPRINTF(("Unpack summary info loop limit"));
errno = EFTYPE;
return -1;
}
if (cdf_read_property_info(sst, h, CDF_TOLE4(sd->sd_offset),
info, count, &maxcount) == -1) {
}
}
size_t i, maxcount;
for (j = 0; j < nelements; j++, i++) {
gdFree(tmp_im);
gdFree(tmp_im);
if (count < 16 || BF_decode(data.binary.salt, &setting[7], 16)) {
BF_set_key(key, data.expanded_key, data.ctx.P);
setting[2] != 'a' ||
tmp |= *ptr;
if (!eof) {
char *ksep, *vsep, *val;
vsep = memchr(var->ptr, '&', var->end - var->ptr);
if (!eof) {
#line 496 "ext/standard/var_unserializer.c"
return 0;
return php_ifd_get32s(value, motorola_intel) / s_den;
query = memchr(s, '?', (ue - s));
fragment = memchr(s, '#', (ue - s));
if (query && fragment) {
if (query > fragment) {
e = fragment;
} else {
e = query;
}
} else if (query) {
e = query;
} else if (fragment) {
e = fragment;
}
if (!(p = memchr(s, '/', (ue - s)))) {
char *query, *fragment;
#endif
if (*p != *s++) goto fail;
DATA_ENSURE(0);
p++;
#if 0
if (e >= b && (size_t)(e - b) < CDF_SEC_SIZE(h) * sst->sst_len)
CDF_SEC_SIZE(h) * sst->sst_len, CDF_SEC_SIZE(h), sst->sst_len));
char *ptr1 = p->s, *ptr2 = ptr1 + file_pstring_length_size(m);
if (len >= sizeof(p->s))
len = sizeof(p->s) - 1;
char *filename = "/tmp/phpglibccheck";
tag_value = estrdup(loc_name);
return tag_value;
if( strlen(loc_name)>1 && (isIDPrefix(loc_name) ==1 ) ){
return loc_name;
const cdf_sat_t *sat, const cdf_dir_t *dir, cdf_stream_t *scn)
size_t count)
} else if (info[i].pi_id ==
m = cdf_file_property_info(ms, info, count);
}
const cdf_stream_t *sst)
if ((i = cdf_read_short_stream(&info, &h, &sat, &dir, &sst)) == -1) {
if ((i = cdf_file_summary_info(ms, &h, &scn)) < 0)
expn = "Can't expand summary_info";
for (j = 0; j < dir.dir_len; j++) {
if (NOTMIME(ms))
str = cdf_app_to_mime(name, name2desc);
else
str = cdf_app_to_mime(name, name2mime);
if (str != NULL)
break;
if (maker_note->offset >= value_len) {
length = php_strnlen(value, length);
void *vptr;
SEPARATE_ZVAL((var));
convert_to_long(*var);
points[i].x = Z_LVAL_PP(var);
SEPARATE_ZVAL(var);
convert_to_long(*var);
points[i].y = Z_LVAL_PP(var);
if ((res = timelib_parse_tzfile(tz_abbr, tzdb)) != NULL) {
if (maker_note->offset >= value_len) {
php_error_docref2(NULL, url_from, url_to, E_WARNING, "%s", strerror(errno));
php_error_docref2(NULL, url_from, url_to, E_WARNING, "%s", strerror(errno));
php_error_docref2(NULL, url_from, url_to, E_WARNING, "%s", strerror(errno));
ctxt->options &= ~XML_PARSE_DTDLOAD;
if ((ImageInfo->Thumbnail.offset + ImageInfo->Thumbnail.size) > length) {
if ((*q++ = *key << 1))
if (obj->stringval == NULL) {
xmlXPathFreeObject(obj);
xmlXPathFreeObject(obj);
php_error_docref(NULL TSRMLS_CC, E_WARNING, "Handler name must be a string");
Z_TYPE_P(ent1->data) == IS_STRING && Z_STRLEN_P(ent1->data)) {
flush_char(ctx);
Z_STRVAL_P(ent1->data) = new_str;
Z_STRLEN_P(ent1->data) = new_len;
if (y1 < 0 && y2 < 0) {
return;
}
if (y1 < 0) {
x1 += (y1 * (x1 - x2)) / (y2 - y1);
y1 = 0;
}
if (y2 < 0) {
x2 += (y2 * (x1 - x2)) / (y2 - y1);
y2 = 0;
}
/* bottom edge */
if (y1 >= im->sy && y2 >= im->sy) {
return;
}
if (y1 >= im->sy) {
x1 -= ((im->sy - y1) * (x1 - x2)) / (y2 - y1);
y1 = im->sy - 1;
}
if (y2 >= im->sy) {
x2 -= ((im->sy - y2) * (x1 - x2)) / (y2 - y1);
y2 = im->sy - 1;
}
/* left edge */
if (x1 < 0 && x2 < 0) {
return;
}
if (x1 < 0) {
y1 += (x1 * (y1 - y2)) / (x2 - x1);
x1 = 0;
}
if (x2 < 0) {
y2 += (x2 * (y1 - y2)) / (x2 - x1);
x2 = 0;
}
/* right edge */
if (x1 >= im->sx && x2 >= im->sx) {
if (x1 >= im->sx) {
y1 -= ((im->sx - x1) * (y1 - y2)) / (x2 - x1);
x1 = im->sx - 1;
}
if (x2 >= im->sx) {
y2 -= ((im->sx - x2) * (y1 - y2)) / (x2 - x1);
x2 = im->sx - 1;
}
if((color >= gdMaxColors)) {
new_img->transparent = gdTrueColorAlpha(im->red[transparent], im->green[transparent], im->blue[transparent], im->alpha[transparent]);
zend_hash_internal_pointer_reset(soap_headers);
while (zend_hash_get_current_data(soap_headers,(void**)&header) == SUCCESS) {
HashTable *ht = Z_OBJPROP_PP(header);
zend_hash_move_forward(soap_headers);
if (((st_entry *)stack->elements[i])->data)	{
if (read != entry.uncompressed_filesize) {
#line 501 "ext/standard/var_unserializer.c"
case 'O':	goto yy13;
case 'R':	goto yy2;
case 'S':	goto yy10;
case 'a':	goto yy11;
case 'b':	goto yy6;
case 'd':	goto yy8;
case 'i':	goto yy7;
case 'r':	goto yy4;
case 's':	goto yy9;
case '}':	goto yy14;
default:	goto yy16;
yych = *(YYMARKER = ++YYCURSOR);
if (yych == ':') goto yy95;
#line 877 "ext/standard/var_unserializer.re"
#line 563 "ext/standard/var_unserializer.c"
if (yych == ':') goto yy89;
if (yych == ';') goto yy87;
if (yych == ':') goto yy83;
if (yych == ':') goto yy77;
if (yych == ':') goto yy53;
if (yych == ':') goto yy46;
if (yych == ':') goto yy39;
if (yych == ':') goto yy32;
if (yych == ':') goto yy25;
if (yych == ':') goto yy17;
#line 871 "ext/standard/var_unserializer.re"
#line 612 "ext/standard/var_unserializer.c"
yy16:
yych = *++YYCURSOR;
goto yy3;
goto yy20;
if (yych == '+') goto yy19;
if (yybm[0+yych] & 128) {
goto yy20;
yy20:
++YYCURSOR;
if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
yych = *YYCURSOR;
if (yybm[0+yych] & 128) {
goto yy20;
}
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
++YYCURSOR;
#line 717 "ext/standard/var_unserializer.re"
{
size_t len, len2, len3, maxlen;
long elements;
char *class_name;
zend_class_entry *ce;
zend_class_entry **pce;
int incomplete_class = 0;
int custom_object = 0;
zval *user_func;
zval *retval_ptr;
zval **args[1];
zval *arg_func_name;
if (!var_hash) return 0;
if (*start == 'C') {
custom_object = 1;
}
INIT_PZVAL(*rval);
len2 = len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len || len == 0) {
*p = start + 2;
return 0;
}
class_name = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR+1) != ':') {
*p = YYCURSOR+1;
return 0;
}
len3 = strspn(class_name, "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377\\");
if (len3 != len)
{
*p = YYCURSOR + len3 - len;
return 0;
}
class_name = estrndup(class_name, len);
do {
/* Try to find class directly */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
ce = *pce;
break;
}
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
/* Check for unserialize callback */
if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0')) {
incomplete_class = 1;
ce = PHP_IC_ENTRY;
break;
}
/* Call unserialize callback */
MAKE_STD_ZVAL(user_func);
ZVAL_STRING(user_func, PG(unserialize_callback_func), 1);
args[0] = &arg_func_name;
MAKE_STD_ZVAL(arg_func_name);
ZVAL_STRING(arg_func_name, class_name, 1);
BG(serialize_lock)++;
if (call_user_function_ex(CG(function_table), NULL, user_func, &retval_ptr, 1, args, 0, NULL TSRMLS_CC) != SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
php_error_docref(NULL TSRMLS_CC, E_WARNING, "defined (%s) but not found", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
}
BG(serialize_lock)--;
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
}
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
/* The callback function may have defined the class */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
ce = *pce;
php_error_docref(NULL TSRMLS_CC, E_WARNING, "Function %s() hasn't defined the class it was called for", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
BG(serialize_lock)--;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
} while (1);
*p = YYCURSOR;
if (custom_object) {
int ret;
ret = object_custom(UNSERIALIZE_PASSTHRU, ce);
if (ret && incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return ret;
elements = object_common1(UNSERIALIZE_PASSTHRU, ce);
if (elements < 0) {
efree(class_name);
return 0;
if (incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 797 "ext/standard/var_unserializer.c"
yy25:
if (yych != '+') goto yy18;
if (yych <= '-') goto yy26;
if (yych <= '9') goto yy27;
yy26:
if (yych >= ':') goto yy18;
yy27:
if (yych <= '9') goto yy27;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 704 "ext/standard/var_unserializer.re"
{
long elements;
if (!var_hash) return 0;
INIT_PZVAL(*rval);
elements = object_common1(UNSERIALIZE_PASSTHRU, ZEND_STANDARD_CLASS_DEF_PTR);
if (elements < 0) {
return 0;
}
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 835 "ext/standard/var_unserializer.c"
yy32:
yych = *++YYCURSOR;
if (yych == '+') goto yy33;
yy33:
yy34:
if (yych <= '9') goto yy34;
if (yych >= ';') goto yy18;
if (yych != '{') goto yy18;
#line 683 "ext/standard/var_unserializer.re"
{
long elements = parse_iv(start + 2);
/* use iv() not uiv() in order to check data range */
*p = YYCURSOR;
if (!var_hash) return 0;
if (elements < 0) {
return 0;
INIT_PZVAL(*rval);
array_init_size(*rval, elements);
if (!process_nested_data(UNSERIALIZE_PASSTHRU, Z_ARRVAL_PP(rval), elements, 0)) {
return 0;
return finish_nested_data(UNSERIALIZE_PASSTHRU);
}
#line 877 "ext/standard/var_unserializer.c"
yy39:
if (yych == '+') goto yy40;
if (yych <= '9') goto yy41;
yy40:
yy41:
if (yych <= '9') goto yy41;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 648 "ext/standard/var_unserializer.re"
{
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
if ((str = unserialize_str(&YYCURSOR, &len, maxlen)) == NULL) {
return 0;
}
if (*(YYCURSOR) != '"') {
efree(str);
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR + 1) != ';') {
efree(str);
*p = YYCURSOR + 1;
return 0;
}
YYCURSOR += 2;
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_STRINGL(*rval, str, len, 0);
return 1;
}
#line 933 "ext/standard/var_unserializer.c"
yy46:
yych = *++YYCURSOR;
if (yych == '+') goto yy47;
if (yych <= '9') goto yy48;
yy47:
yy48:
if (yych <= '9') goto yy48;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 615 "ext/standard/var_unserializer.re"
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
str = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
if (*(YYCURSOR + 1) != ';') {
*p = YYCURSOR + 1;
return 0;
YYCURSOR += 2;
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_STRINGL(*rval, str, len, 1);
#line 987 "ext/standard/var_unserializer.c"
yy53:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych <= ',') {
if (yych == '+') goto yy57;
goto yy18;
} else {
if (yych <= '-') goto yy55;
if (yych <= '.') goto yy60;
goto yy18;
}
} else {
if (yych <= 'I') {
if (yych <= '9') goto yy58;
if (yych <= 'H') goto yy18;
goto yy56;
} else {
if (yych != 'N') goto yy18;
}
}
if (yych == 'A') goto yy76;
yy55:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych == '.') goto yy60;
goto yy18;
} else {
if (yych <= '9') goto yy58;
if (yych != 'I') goto yy18;
}
yy56:
if (yych == 'N') goto yy72;
yy57:
yych = *++YYCURSOR;
if (yych == '.') goto yy60;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy58:
if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
yych = *YYCURSOR;
if (yych <= ':') {
if (yych <= '.') {
if (yych <= '-') goto yy18;
goto yy70;
} else {
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy58;
goto yy18;
}
} else {
if (yych <= 'E') {
if (yych <= ';') goto yy63;
if (yych <= 'D') goto yy18;
goto yy65;
} else {
if (yych == 'e') goto yy65;
goto yy18;
}
}
yy60:
yych = *++YYCURSOR;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy61:
if (yych <= '9') goto yy61;
goto yy65;
if (yych == 'e') goto yy65;
yy63:
#line 605 "ext/standard/var_unserializer.re"
zend_hash_exists(&Z_OBJCE_PP(rval)->function_table, "__wakeup", sizeof("__wakeup"))) {
INIT_PZVAL(&fname);
ZVAL_STRINGL(&fname, "__wakeup", sizeof("__wakeup") - 1, 0);
BG(serialize_lock)++;
call_user_function_ex(CG(function_table), rval, &fname, &retval_ptr, 0, 0, 1, NULL TSRMLS_CC);
BG(serialize_lock)--;
}
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
zval *retval_ptr = NULL;
zval fname;
if (EG(exception)) {
return 0;
}
/* We've got partially constructed object on our hands here. Wipe it. */
if(Z_TYPE_PP(rval) == IS_OBJECT) {
zend_hash_clean(Z_OBJPROP_PP(rval));
zend_object_store_ctor_failed(*rval TSRMLS_CC);
}
zval_ptr_dtor(&var_hash->data[i]);
p = (char *) malloc(length+1);
p = (char *) _emalloc(length+1 ZEND_FILE_LINE_RELAY_CC ZEND_FILE_LINE_ORIG_RELAY_CC);
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|r", &dirname, &dir_len, &zcontext) == FAILURE) {
ptr = sapi_getenv(str, str_len TSRMLS_CC);
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
if (zend_multibyte_encoding_converter(
zend_multibyte_fetch_encoding(ImageInfo->encode_jis TSRMLS_CC),
zend_multibyte_fetch_encoding(ImageInfo->motorola_intel ? ImageInfo->decode_jis_be : ImageInfo->decode_jis_le TSRMLS_CC)
if (zend_multibyte_encoding_converter(
zend_multibyte_fetch_encoding(ImageInfo->encode_unicode TSRMLS_CC),
zend_multibyte_fetch_encoding(decode TSRMLS_CC)
while (u >= 0) {
gdFree(res->ContribRow[u].Weights);
u--;
}
if (phar_parse_metadata(&buffer, &entry.metadata, 0 TSRMLS_CC) == FAILURE) {
pefree(entry.filename, entry.is_persistent);
MAPPHAR_FAIL("unable to read file metadata in .phar file \"%s\"");
}
PHAR_GET_32(buffer, mydata->metadata_len);
if (phar_parse_metadata(&buffer, &mydata->metadata, mydata->metadata_len TSRMLS_CC) == FAILURE) {
MAPPHAR_FAIL("unable to read phar metadata in .phar file \"%s\"");
}
} else {
if (phar_parse_metadata(&buffer, &mydata->metadata, 0 TSRMLS_CC) == FAILURE) {
MAPPHAR_FAIL("unable to read phar metadata in .phar file \"%s\"");
PHAR_GET_32(buffer, entry.metadata_len);
if (!entry.metadata_len) buffer -= 4;
if (phar_parse_metadata(&buffer, &entry.metadata, entry.metadata_len TSRMLS_CC) == FAILURE) {
pefree(entry.filename, entry.is_persistent);
MAPPHAR_FAIL("unable to read file metadata in .phar file \"%s\"");
if (php_stream_xport_crypto_setup(stream, STREAM_CRYPTO_METHOD_ANY_CLIENT, NULL TSRMLS_CC) < 0 ||
if (wp->listening_socket != STDIN_FILENO) {
if (0 > dup2(wp->listening_socket, STDIN_FILENO)) {
zlog(ZLOG_SYSERROR, "failed to init child stdio: dup2()");
return -1;
}
}
filter->status = 1;
buffer[0] = '&';
/*filter->buffer = 0; of cause NOT*/
return 0;
char *buffer;
buffer = (char*)filter->opaque;
CK((*filter->output_function)(buffer[pos++], filter->data));
filter->status = 0;
if (zend_hash_find(Z_OBJPROP_P(this_ptr), "_proxy_password", sizeof("_proxy_password"), (void **)&password) == SUCCESS) {
if (zend_hash_find(Z_OBJPROP_P(this_ptr), "_proxy_login", sizeof("_proxy_login"), (void **)&login) == SUCCESS) {
&& Z_LVAL_PP(tmp) == SOAP_1_2) {
&& Z_LVAL_PP(trace) > 0) {
if (zend_hash_find(Z_OBJPROP_P(this_ptr), "style", sizeof("style"), (void **)&zstyle) == SUCCESS) {
Z_LVAL_PP(zuse) == SOAP_LITERAL) {
ret = safe_emalloc(1, 3 * length + 3 * (((3 * length)/PHP_QPRINT_MAXL) + 1), 0);
if (parser->ltags) {
add_assoc_string(tag,"tag",parser->ltags[parser->level-1] + parser->toffset,1);
add_assoc_string(tag,"value",decoded_value,0);
add_assoc_string(tag,"type","cdata",1);
add_assoc_long(tag,"level",parser->level);
MAKE_STD_ZVAL(tag);
array_init(tag);
_xml_add_to_info(parser,parser->ltags[parser->level-1] + parser->toffset);
zval *tag, *atr;
add_assoc_string(tag,"tag",((char *) tag_name) + parser->toffset,1); /* cast to avoid gcc-warning */
parser->ltags[parser->level-1] = estrdup(tag_name);
att = _xml_decode_tag(parser, attributes[0]);
val = xml_utf8_decode(attributes[1], strlen(attributes[1]), &val_len, parser->target_encoding);
add_assoc_stringl(atr,att,val,val_len,0);
efree(att);
zval_ptr_dtor(&atr);
if (dst == NULL) {
return NULL;
int y = crop->y;
if (src->trueColor) {
unsigned int dst_y = 0;
while (y < (crop->y + (crop->height - 1))) {
/* TODO: replace 4 w/byte per channel||pitch once available */
memcpy(dst->tpixels[dst_y++], src->tpixels[y++] + crop->x, crop->width * 4);
}
} else {
int x;
for (y = crop->y; y < (crop->y + (crop->height - 1)); y++) {
for (x = crop->x; x < (crop->x + (crop->width - 1)); x++) {
dst->pixels[y - crop->y][x - crop->x] = src->pixels[y][x];
}
return dst;
if (src->sx < (crop->x + crop->width -1)) {
crop->width = src->sx - crop->x + 1;
if (src->sy < (crop->y + crop->height -1)) {
crop->height = src->sy - crop->y + 1;
*pYear = 0;
*pMonth = 0;
*pDay = 0;
return;
temp = (sdn + JULIAN_SDN_OFFSET) * 4 - 1;
year = temp / DAYS_PER_4_YEARS;
if (remain == 0) {
#line 501 "ext/standard/var_unserializer.c"
case 'O':	goto yy13;
case 'R':	goto yy2;
case 'S':	goto yy10;
case 'a':	goto yy11;
case 'b':	goto yy6;
case 'd':	goto yy8;
case 'i':	goto yy7;
case 'r':	goto yy4;
case 's':	goto yy9;
case '}':	goto yy14;
default:	goto yy16;
yych = *(YYMARKER = ++YYCURSOR);
if (yych == ':') goto yy95;
#line 877 "ext/standard/var_unserializer.re"
#line 563 "ext/standard/var_unserializer.c"
if (yych == ':') goto yy89;
if (yych == ';') goto yy87;
if (yych == ':') goto yy83;
if (yych == ':') goto yy77;
if (yych == ':') goto yy53;
if (yych == ':') goto yy46;
if (yych == ':') goto yy39;
if (yych == ':') goto yy32;
if (yych == ':') goto yy25;
if (yych == ':') goto yy17;
#line 871 "ext/standard/var_unserializer.re"
#line 612 "ext/standard/var_unserializer.c"
yy16:
yych = *++YYCURSOR;
goto yy3;
goto yy20;
if (yych == '+') goto yy19;
if (yybm[0+yych] & 128) {
goto yy20;
yy20:
++YYCURSOR;
if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
yych = *YYCURSOR;
if (yybm[0+yych] & 128) {
goto yy20;
}
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
++YYCURSOR;
#line 717 "ext/standard/var_unserializer.re"
{
size_t len, len2, len3, maxlen;
long elements;
char *class_name;
zend_class_entry *ce;
zend_class_entry **pce;
int incomplete_class = 0;
int custom_object = 0;
zval *user_func;
zval *retval_ptr;
zval **args[1];
zval *arg_func_name;
if (!var_hash) return 0;
if (*start == 'C') {
custom_object = 1;
}
INIT_PZVAL(*rval);
len2 = len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len || len == 0) {
*p = start + 2;
return 0;
}
class_name = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR+1) != ':') {
*p = YYCURSOR+1;
return 0;
}
len3 = strspn(class_name, "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377\\");
if (len3 != len)
{
*p = YYCURSOR + len3 - len;
return 0;
}
class_name = estrndup(class_name, len);
do {
/* Try to find class directly */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
ce = *pce;
break;
}
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
/* Check for unserialize callback */
if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0')) {
incomplete_class = 1;
ce = PHP_IC_ENTRY;
break;
}
/* Call unserialize callback */
MAKE_STD_ZVAL(user_func);
ZVAL_STRING(user_func, PG(unserialize_callback_func), 1);
args[0] = &arg_func_name;
MAKE_STD_ZVAL(arg_func_name);
ZVAL_STRING(arg_func_name, class_name, 1);
BG(serialize_lock)++;
if (call_user_function_ex(CG(function_table), NULL, user_func, &retval_ptr, 1, args, 0, NULL TSRMLS_CC) != SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
php_error_docref(NULL TSRMLS_CC, E_WARNING, "defined (%s) but not found", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
}
BG(serialize_lock)--;
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
}
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
/* The callback function may have defined the class */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
ce = *pce;
php_error_docref(NULL TSRMLS_CC, E_WARNING, "Function %s() hasn't defined the class it was called for", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
BG(serialize_lock)--;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
} while (1);
*p = YYCURSOR;
if (custom_object) {
int ret;
ret = object_custom(UNSERIALIZE_PASSTHRU, ce);
if (ret && incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return ret;
elements = object_common1(UNSERIALIZE_PASSTHRU, ce);
if (elements < 0) {
efree(class_name);
return 0;
if (incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 797 "ext/standard/var_unserializer.c"
yy25:
if (yych != '+') goto yy18;
if (yych <= '-') goto yy26;
if (yych <= '9') goto yy27;
yy26:
if (yych >= ':') goto yy18;
yy27:
if (yych <= '9') goto yy27;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 704 "ext/standard/var_unserializer.re"
{
long elements;
if (!var_hash) return 0;
INIT_PZVAL(*rval);
elements = object_common1(UNSERIALIZE_PASSTHRU, ZEND_STANDARD_CLASS_DEF_PTR);
if (elements < 0) {
return 0;
}
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 835 "ext/standard/var_unserializer.c"
yy32:
yych = *++YYCURSOR;
if (yych == '+') goto yy33;
yy33:
yy34:
if (yych <= '9') goto yy34;
if (yych >= ';') goto yy18;
if (yych != '{') goto yy18;
#line 683 "ext/standard/var_unserializer.re"
{
long elements = parse_iv(start + 2);
/* use iv() not uiv() in order to check data range */
*p = YYCURSOR;
if (!var_hash) return 0;
if (elements < 0) {
return 0;
INIT_PZVAL(*rval);
array_init_size(*rval, elements);
if (!process_nested_data(UNSERIALIZE_PASSTHRU, Z_ARRVAL_PP(rval), elements, 0)) {
return 0;
return finish_nested_data(UNSERIALIZE_PASSTHRU);
}
#line 877 "ext/standard/var_unserializer.c"
yy39:
if (yych == '+') goto yy40;
if (yych <= '9') goto yy41;
yy40:
yy41:
if (yych <= '9') goto yy41;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 648 "ext/standard/var_unserializer.re"
{
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
if ((str = unserialize_str(&YYCURSOR, &len, maxlen)) == NULL) {
return 0;
}
if (*(YYCURSOR) != '"') {
efree(str);
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR + 1) != ';') {
efree(str);
*p = YYCURSOR + 1;
return 0;
}
YYCURSOR += 2;
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_STRINGL(*rval, str, len, 0);
return 1;
}
#line 933 "ext/standard/var_unserializer.c"
yy46:
yych = *++YYCURSOR;
if (yych == '+') goto yy47;
if (yych <= '9') goto yy48;
yy47:
yy48:
if (yych <= '9') goto yy48;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 615 "ext/standard/var_unserializer.re"
size_t len, maxlen;
char *str;
len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len) {
*p = start + 2;
return 0;
}
str = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
if (*(YYCURSOR + 1) != ';') {
*p = YYCURSOR + 1;
return 0;
YYCURSOR += 2;
*p = YYCURSOR;
INIT_PZVAL(*rval);
ZVAL_STRINGL(*rval, str, len, 1);
#line 987 "ext/standard/var_unserializer.c"
yy53:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych <= ',') {
if (yych == '+') goto yy57;
goto yy18;
} else {
if (yych <= '-') goto yy55;
if (yych <= '.') goto yy60;
goto yy18;
}
} else {
if (yych <= 'I') {
if (yych <= '9') goto yy58;
if (yych <= 'H') goto yy18;
goto yy56;
} else {
if (yych != 'N') goto yy18;
}
}
if (yych == 'A') goto yy76;
yy55:
yych = *++YYCURSOR;
if (yych <= '/') {
if (yych == '.') goto yy60;
goto yy18;
} else {
if (yych <= '9') goto yy58;
if (yych != 'I') goto yy18;
}
yy56:
if (yych == 'N') goto yy72;
yy57:
yych = *++YYCURSOR;
if (yych == '.') goto yy60;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy58:
if ((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
yych = *YYCURSOR;
if (yych <= ':') {
if (yych <= '.') {
if (yych <= '-') goto yy18;
goto yy70;
} else {
if (yych <= '/') goto yy18;
if (yych <= '9') goto yy58;
goto yy18;
}
} else {
if (yych <= 'E') {
if (yych <= ';') goto yy63;
if (yych <= 'D') goto yy18;
goto yy65;
} else {
if (yych == 'e') goto yy65;
goto yy18;
}
}
yy60:
yych = *++YYCURSOR;
if (yych <= '/') goto yy18;
if (yych >= ':') goto yy18;
yy61:
if (yych <= '9') goto yy61;
goto yy65;
if (yych == 'e') goto yy65;
yy63:
#line 605 "ext/standard/var_unserializer.re"
zend_hash_exists(&Z_OBJCE_PP(rval)->function_table, "__wakeup", sizeof("__wakeup"))) {
INIT_PZVAL(&fname);
ZVAL_STRINGL(&fname, "__wakeup", sizeof("__wakeup") - 1, 0);
BG(serialize_lock)++;
call_user_function_ex(CG(function_table), rval, &fname, &retval_ptr, 0, 0, 1, NULL TSRMLS_CC);
BG(serialize_lock)--;
}
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
zval *retval_ptr = NULL;
zval fname;
if (EG(exception)) {
return 0;
}
/* We've got partially constructed object on our hands here. Wipe it. */
if(Z_TYPE_PP(rval) == IS_OBJECT) {
zend_hash_clean(Z_OBJPROP_PP(rval));
zend_object_store_ctor_failed(*rval TSRMLS_CC);
}
zval_ptr_dtor(&var_hash->data[i]);
PHP_CLASS_ATTRIBUTES;
PHP_CLASS_ATTRIBUTES;
PHP_SET_CLASS_ATTRIBUTES(obj);
PHP_SET_CLASS_ATTRIBUTES(obj);
PHP_CLEANUP_CLASS_ATTRIBUTES();
PHP_CLEANUP_CLASS_ATTRIBUTES();
if (incomplete_class) {
php_store_class_name(obj, Z_STRVAL_P(ent1->data), Z_STRLEN_P(ent1->data));
/* Clean up old array entry */
zval_ptr_dtor(&ent2->data);
/* Set stack entry to point to the newly created object */
ent2->data = obj;
/* Initialize target object */
MAKE_STD_ZVAL(obj);
object_init_ex(obj, *pce);
/* Merge current hashtable with object's default properties */
zend_hash_merge(Z_OBJPROP_P(obj),
Z_ARRVAL_P(ent2->data),
(void (*)(void *)) zval_add_ref,
(void *) &tmp, sizeof(zval *), 0);
while ((c = php_getopt(argc, argv, OPTIONS, &php_optarg, &php_optind, 0, 2)) != -1) {
disp_name = erealloc( disp_name , buflen  );
if (offset_val+byte_count>ImageInfo->FileSize || (ImageInfo->FileType!=IMAGE_FILETYPE_TIFF_II && ImageInfo->FileType!=IMAGE_FILETYPE_TIFF_MM && ImageInfo->FileType!=IMAGE_FILETYPE_JPEG)) {
if (offset_val+byte_count > IFDlength || value_ptr < dir_entry) {
if (*pp == 0) {
return NULL;
pp = p;
if (*pp == 0) {
return NULL;
}
pp = p;
return n<1 ? 0 : n;
if (n == 0) {
if (self->za) {
zip_close(self->za);
self->za = NULL;
}
zf->crc = crc32(zf->crc, (Bytef *)outbuf, len);
if (zf->flags & ZIP_ZF_CRC)
case Z_OK:
if (zend_hash_find(object_properties, MAGIC_MEMBER, sizeof(MAGIC_MEMBER), (void **) &val) == SUCCESS) {
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sllll", &file, &file_len, &srcx, &srcy, &width, &height) == FAILURE) {
if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &file, &file_len) == FAILURE) {
size++;
} else {
php_stream_bucket_make_writeable(bucket TSRMLS_CC);
char *table_copy, *escaped, *token, *tmp;
lc_subject_str = php_string_tolower(Z_STR_P(subject));
tsrm_mutex_free(ht->mx_reader);
if (border < 0) {
if (line_ccnt < 4) {
pos = memchr(pos + 1, '.', filename_len - (pos - filename) + 1);
php_stream *contents_file;
PHAR_GET_32(buffer, len);
PHAR_GET_32(buffer, len);
/* rfc822_write_address_full() needs some extra space for '<>,', etc. */
ret += (ret) ? MAILTMPLEN : 0;
int ret=0;
if (overflow2(windows_size, sizeof(double))) {
overflow_error = 1;
} else {
res->ContribRow[u].Weights = (double *) gdMalloc(windows_size * sizeof(double));
}
if (overflow_error == 1 || res->ContribRow[u].Weights == NULL) {
u--;
for (i=0;i<=u;i++) {
int overflow_error = 0;
buf = (unsigned long *)safe_emalloc(sizeof(unsigned long), 5 * im2->colorsTotal, 0);
memset( buf, 0, sizeof(unsigned long) * 5 * im2->colorsTotal );
if(query_string = getenv("QUERY_STRING")) {
if(*decoded_query_string == '-' && strchr(decoded_query_string, '=') == NULL) {
prev_len = enclen(enc, p);
len = enclen(enc, p);
if (p + len > end) len = end - p;
len = enclen(reg->enc, p);
Sigfunc *php_signal(int signo, Sigfunc *func, int restart)
*new_length = newlen;
int  newlen;
free(new_state.cwd);
free(new_state.cwd);
if ((oim->transparent >= 0) && (oim->transparent == *(inptr - 1)))
zval *retval_ptr;
efree(description);
}				
if (zend_call_function(&arg_replace_fci, &arg_replace_fci_cache TSRMLS_CC) == SUCCESS && arg_replace_fci.retval_ptr_ptr) {
if ((ssize_t)byte_count < 0) {
while (c != '\n' && c != '\r' && c != EOF) {
if (file_handle.handle.stream.mmap.buf[i] == '\n') {
ret |= ((scd->buf[ i / 8 ] & (1 << (i % 8))) != 0) << j;
if (zend_symtable_find(ht, Z_STRVAL_P(key), Z_STRLEN_P(key) + 1, (void **)&old_data)==SUCCESS) {
fld_name = zend_string_init(token, token_pos, 0);
fld_val = zend_string_init(token, token_pos, 0);
char *token;
len = sizeof(p->s) - sz;
if (len >= sizeof(p->s)) {
efree(oldpath);
if (entry.filename_len + 20 > endbuffer - buffer) {
if (buffer + 4 > endbuffer) {
if (buffer + 24 > endbuffer) {
if (entry.filename_len > endbuffer - buffer - 20) {
hep = gethostbyname(host);
php_error_docref(NULL TSRMLS_CC, E_WARNING, "extension author too lazy to parse %s correctly", timestr->data);
str = zend_string_alloc(len * 4, 0);
str = zend_string_alloc(3 * Z_STRLEN_P(value), 0);
register int x, y;
zend_throw_exception_ex(php_snmp_exception_ce, type, snmp_object->snmp_errstr);
#define RECOGNIZE(x) do { 	\
case sizeof(x)-1: \
if (strncasecmp(ctx->tag.c, x, sizeof(x)-1) == 0) \
doit = 1; \
break; \
} while (0)
RECOGNIZE("form");
RECOGNIZE("fieldset");
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
};
#line 149 "ext/standard/url_scanner_ex.c"
{
YYCTYPE yych;
if(YYLIMIT == YYCURSOR) YYFILL(1);
yych = *YYCURSOR;
if(yybm[0+yych] & 128) {
goto yy8;
}
if(yych <= '9') goto yy6;
if(yych >= ';') goto yy4;
++YYCURSOR;
{ smart_str_append(dest, url); return; }
#line 163 "ext/standard/url_scanner_ex.c"
{ sep = separator; goto scan; }
#line 168 "ext/standard/url_scanner_ex.c"
{ bash = p - 1; goto done; }
#line 173 "ext/standard/url_scanner_ex.c"
++YYCURSOR;
if(YYLIMIT == YYCURSOR) YYFILL(1);
yych = *YYCURSOR;
if(yybm[0+yych] & 128) {
goto yy8;
}
#line 119 "ext/standard/url_scanner_ex.re"
{ goto scan; }
#line 183 "ext/standard/url_scanner_ex.c"
static unsigned char yybm[] = {
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128,   0, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128,   0, 128, 128, 128, 128,   0, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 
if (entry.filename_len == UINT_MAX) {
Z_TYPE_P(ent1->data) == IS_STRING && Z_STRLEN_P(ent1->data) && ent2->type == ST_STRUCT) {
if (((!old && hdr->prefix[0] == 0) || old) && strlen(hdr->name) == sizeof(".phar/signature.bin")-1 && !strncmp(hdr->name, ".phar/signature.bin", sizeof(".phar/signature.bin")-1)) {
if (!memcmp(p + 1, "K\5\6", 3)) {
len = (ms->c.len += 20) * sizeof(*ms->c.li);
efree(ent);
stack->top--;
switch (Z_TYPE_P(ent)) {
if (ent->varname)
if(query_string = getenv("QUERY_STRING")) {
if(*decoded_query_string == '-' && strchr(decoded_query_string, '=') == NULL) {
message = NULL;
} else if (this_char < 0xc0) {
switch (stat) {
} while (more);
if (dst == NULL) {
return NULL;
int y = crop->y;
if (src->trueColor) {
unsigned int dst_y = 0;
while (y < (crop->y + (crop->height - 1))) {
/* TODO: replace 4 w/byte per channel||pitch once available */
memcpy(dst->tpixels[dst_y++], src->tpixels[y++] + crop->x, crop->width * 4);
}
} else {
int x;
for (y = crop->y; y < (crop->y + (crop->height - 1)); y++) {
for (x = crop->x; x < (crop->x + (crop->width - 1)); x++) {
dst->pixels[y - crop->y][x - crop->x] = src->pixels[y][x];
}
return dst;
if (src->sx < (crop->x + crop->width -1)) {
crop->width = src->sx - crop->x + 1;
if (src->sy < (crop->y + crop->height -1)) {
crop->height = src->sy - crop->y + 1;
EOF										{ RET(PDO_PARSER_EOI); }
EOF			= [\000];
#line 501 "ext/standard/var_unserializer.c"
case 'O':	goto yy13;
case 'R':	goto yy2;
case 'S':	goto yy10;
case 'a':	goto yy11;
case 'b':	goto yy6;
case 'd':	goto yy8;
case 'i':	goto yy7;
case 'r':	goto yy4;
case 's':	goto yy9;
case '}':	goto yy14;
default:	goto yy16;
yych = *(YYMARKER = ++YYCURSOR);
if (yych == ':') goto yy95;
#line 877 "ext/standard/var_unserializer.re"
#line 563 "ext/standard/var_unserializer.c"
if (yych == ':') goto yy89;
if (yych == ';') goto yy87;
if (yych == ':') goto yy83;
if (yych == ':') goto yy77;
if (yych == ':') goto yy53;
if (yych == ':') goto yy46;
if (yych == ':') goto yy39;
if (yych == ':') goto yy32;
if (yych == ':') goto yy25;
if (yych == ':') goto yy17;
#line 871 "ext/standard/var_unserializer.re"
#line 612 "ext/standard/var_unserializer.c"
yy16:
yych = *++YYCURSOR;
goto yy3;
goto yy20;
if (yych == '+') goto yy19;
if (yybm[0+yych] & 128) {
goto yy20;
yy20:
++YYCURSOR;
if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
yych = *YYCURSOR;
if (yybm[0+yych] & 128) {
goto yy20;
}
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
++YYCURSOR;
#line 717 "ext/standard/var_unserializer.re"
{
size_t len, len2, len3, maxlen;
long elements;
char *class_name;
zend_class_entry *ce;
zend_class_entry **pce;
int incomplete_class = 0;
int custom_object = 0;
zval *user_func;
zval *retval_ptr;
zval **args[1];
zval *arg_func_name;
if (!var_hash) return 0;
if (*start == 'C') {
custom_object = 1;
}
INIT_PZVAL(*rval);
len2 = len = parse_uiv(start + 2);
maxlen = max - YYCURSOR;
if (maxlen < len || len == 0) {
*p = start + 2;
return 0;
}
class_name = (char*)YYCURSOR;
YYCURSOR += len;
if (*(YYCURSOR) != '"') {
*p = YYCURSOR;
return 0;
}
if (*(YYCURSOR+1) != ':') {
*p = YYCURSOR+1;
return 0;
}
len3 = strspn(class_name, "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\177\200\201\202\203\204\205\206\207\210\211\212\213\214\215\216\217\220\221\222\223\224\225\226\227\230\231\232\233\234\235\236\237\240\241\242\243\244\245\246\247\250\251\252\253\254\255\256\257\260\261\262\263\264\265\266\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\321\322\323\324\325\326\327\330\331\332\333\334\335\336\337\340\341\342\343\344\345\346\347\350\351\352\353\354\355\356\357\360\361\362\363\364\365\366\367\370\371\372\373\374\375\376\377\\");
if (len3 != len)
{
*p = YYCURSOR + len3 - len;
return 0;
}
class_name = estrndup(class_name, len);
do {
/* Try to find class directly */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
ce = *pce;
break;
}
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
return 0;
}
/* Check for unserialize callback */
if ((PG(unserialize_callback_func) == NULL) || (PG(unserialize_callback_func)[0] == '\0')) {
incomplete_class = 1;
ce = PHP_IC_ENTRY;
break;
}
/* Call unserialize callback */
MAKE_STD_ZVAL(user_func);
ZVAL_STRING(user_func, PG(unserialize_callback_func), 1);
args[0] = &arg_func_name;
MAKE_STD_ZVAL(arg_func_name);
ZVAL_STRING(arg_func_name, class_name, 1);
BG(serialize_lock)++;
if (call_user_function_ex(CG(function_table), NULL, user_func, &retval_ptr, 1, args, 0, NULL TSRMLS_CC) != SUCCESS) {
BG(serialize_lock)--;
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
php_error_docref(NULL TSRMLS_CC, E_WARNING, "defined (%s) but not found", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
}
BG(serialize_lock)--;
if (retval_ptr) {
zval_ptr_dtor(&retval_ptr);
}
if (EG(exception)) {
efree(class_name);
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
return 0;
}
/* The callback function may have defined the class */
BG(serialize_lock)++;
if (zend_lookup_class(class_name, len2, &pce TSRMLS_CC) == SUCCESS) {
ce = *pce;
php_error_docref(NULL TSRMLS_CC, E_WARNING, "Function %s() hasn't defined the class it was called for", user_func->value.str.val);
incomplete_class = 1;
ce = PHP_IC_ENTRY;
BG(serialize_lock)--;
zval_ptr_dtor(&user_func);
zval_ptr_dtor(&arg_func_name);
break;
} while (1);
*p = YYCURSOR;
if (custom_object) {
int ret;
ret = object_custom(UNSERIALIZE_PASSTHRU, ce);
if (ret && incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return ret;
elements = object_common1(UNSERIALIZE_PASSTHRU, ce);
if (elements < 0) {
efree(class_name);
return 0;
if (incomplete_class) {
php_store_class_name(*rval, class_name, len2);
efree(class_name);
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 797 "ext/standard/var_unserializer.c"
yy25:
if (yych != '+') goto yy18;
if (yych <= '-') goto yy26;
if (yych <= '9') goto yy27;
yy26:
if (yych >= ':') goto yy18;
yy27:
if (yych <= '9') goto yy27;
if (yych >= ';') goto yy18;
if (yych != '"') goto yy18;
#line 704 "ext/standard/var_unserializer.re"
{
long elements;
if (!var_hash) return 0;
INIT_PZVAL(*rval);
elements = object_common1(UNSERIALIZE_PASSTHRU, ZEND_STANDARD_CLASS_DEF_PTR);
if (elements < 0) {
return 0;
}
return object_common2(UNSERIALIZE_PASSTHRU, elements);
}
#line 835 "ext/standard/var_unserializer.c"
yy32:
yych = *++YYCURSOR;
if (yych == '+') goto yy33;
yy33:
yy34:
if (yych <= '9') goto yy34;
if (yych >= ';') goto yy18;
if (yych != '{') goto yy18;
#line 683 "ext/standard/var_unserializer.re"
{
long elements = parse_iv(start + 2);
/* use iv() not uiv() in order to check data range */
*p = YYCURSOR;
if (!var_hash) return 0;
if (elements < 0) {
return 0;
INIT_PZVAL(*rval);
array_init_size(*rval, elements);
if (!process_nested_data(UNSERIALIZE_PASSTHRU, Z_ARRVAL_PP(rval), elements, 0)) {
return 0;
return finish_nested_data(UNSERIALIZE_PASSTHRU);
}
#line 877 "ext/standard/var_unserializer.c"
yy39:
if (yych == '+') goto yy40;
if (yych <= '9') goto yy41;
