# This scraper is compatible with a previous version of VDLine which had a far more expansive directory structure.
# Once the dataset was scraped and parsed, it was placed, in its entirety, within the vulnerable_sourcecode.pkl file
# This scraper is included within the project for reporting purposes only and will not compile at this time

#!/bin/python
import json
import shutil
import sys
from datetime import datetime
import logging
import requests
import os
import pandas as pd
from os.path import join as pathjoin
import src.configs as configs
# from prepare.cpg_generator import joern_parse
import subprocess
PATHS = configs.Paths()
DATA = configs.Data()
CB_PROJECTS = DATA.projects
FOUND_404_STR = 15
JOERN_PATH = PATHS.joern
TMP_DIR = PATHS.temp
RAW_DIR = PATHS.raw
PROJECT = ""
DEST = ""
DATASET = None
_commits = []
_functions = []
_line_nos = []
_lines = []
_file_paths = []
_urls = []


def produce_df():
    """
    Gathers all the information from all the projects contained in 'vulnerable_lines.json" and
    the source code obtained from the scraper in GitHub creates one dataframe for all projects
    with the source code included. (Original dataset does not include the source code).
    """
    ds_filename = f"{RAW_DIR}/all/vulnerable_lines.pkl"
    if os.path.exists(ds_filename):
        logging.warning("File ds_filename already exits. Returning.")
        return
    # ds = pd.DataFrame(columns=["project", "commit", "target", "function_name", "function"])
    ds = []
    _commit_no = 0     # How the dataframe is codified
    _rest_no = 1
    for p in CB_PROJECTS.keys():
        vuln_lines = pd.read_pickle(f"{RAW_DIR}{p}/vulnerable_lines.pkl")
        for r in vuln_lines.iterrows():
            _commit = r[_commit_no]
            _rest = r[_rest_no]    # at this point, the keys are function_name, file_path, line_no and line
            _project = p
            _name = _rest["function_name"]
            _target = _rest["line_no"]
            _line = _rest["line"]
            if type(_line) is not str:
                logging.warning(f"Record skip: {p} {_commit} {_name} {_target}")
                continue
            if _line[0] == '+' or _line[0] == '-':  # remove leading - or +
                _line = _line[1:].lstrip()
            _file = f"{RAW_DIR}{p}/functions/{_name}--{_commit}.c"
            if not os.path.exists(_file):
                logging.warning(f"File {_file} does not exits. Continue")
                continue
            with open(_file) as f:
                _function = "". join(f.readlines())   # read lines, non-ASCII char can be a problem
            this = {"project": _project, "commit": _commit, "target": _target, "function_name": _name,
                    "line": _line, "function": _function}
            ds.append(this)
        logging.info(f"Finish  reading project {p}")
    logging.info(f"Finish dataset production.")
    ds = pd.DataFrame(ds)
    ds = ds.set_index("commit")
    ds.to_pickle(ds_filename)
    logging.info(f"Wrote dataset.pkl to {RAW_DIR}")
    return


def _dict_file_path(data: dict):
    files = data['data']
    if not files:
        logging.warning("No data, skip")
        return
    for file in files.keys():
        logging.info(f"File is {file}")
        _dict_function(files[file], file)
    return


def _dict_function(data: dict, file_path):
    for function in data.keys():
        logging.info(f"Function name is {function}")
        _dict_lineno(data[function], file_path, function)
    return


def _dict_lineno(data: dict, file_path, function):
    if not data:
        logging.error("Data is none in 'lineno' function")
        return
    for line_no in data.keys():
        logging.info(f"Line number is {line_no}")
        _dict_line(data[line_no], file_path, function, line_no)
    return


def _dict_line(data: dict, file_path, function, line_no):
    line = data["line"]
    if not line:
        logging.error("Line empty")
        line = 0
    else:
        logging.info(f"The vulnerable line is:\n{line}")
    _dict_commit(data["intro"], file_path, function, line_no, line)
    return


def _dict_commit(data: dict, file_path, function, line_no, line):
    commit = data['commit']
    url_src = f"https://raw.githubusercontent.com/{PROJECT}/{commit}/{file_path}"

    _file_paths.append(file_path)
    _functions.append(function)
    _line_nos.append(line_no)
    _lines.append(line)
    _commits.append(commit[0:20])
    _urls.append(url_src)
    _request_url_write(function, commit, file_path)
    return


def _request_url_write(function, commit, file_path):
    url_src = f"https://raw.githubusercontent.com/{PROJECT}/{commit}/{file_path}"
    commits_dest = pathjoin(DEST, "commits")
    logging.info(f"URL is: {url_src}")
    to_write = pathjoin(commits_dest, f"{function}--{commit[0:20]}.c")
    if os.path.exists(to_write):
        logging.warning("File exists, skip request")
        return
    try:
        source_code = requests.get(url_src)
        if len(source_code.content) < FOUND_404_STR:
            logging.error("Found 404, file not written")
            return
        with open(to_write, 'wb') as fh:
            fh.write(source_code.content)
    except requests.exceptions.RequestException as e:
        logging.error(f"An exception was raise while getting the file {_file_paths}. Continue.")
    return


def scrape_dataset(project_to_scrape):
    """
    This functions creates the dataset by reading the Carrots blender dataset
    and requesting the data from Github. At the end, it creates a pandas DF with the information
    and a 'commit' directory with the source code data
    """
    global PROJECT, DEST, DATASET
    log_filename = "default_log.txt"  # just a temp placeholder
    for key in CB_PROJECTS.keys():
        if key in project_to_scrape:
            PROJECT = CB_PROJECTS[key]
            DEST = pathjoin(PATHS.raw, key)
            log_filename = os.path.join(DEST, "log.txt")
            commits_dest = pathjoin(DEST, "commits")
            break
    if not PROJECT:
        print("[Error] Project not found, check source parameter. Exit.")
        sys.exit(1)
    logging.basicConfig(level=logging.INFO, filename=log_filename, filemode='w+',
                        format='[%(levelname)s] - %(message)s')
    logging.info(
        f"{str(datetime.now())[0:-5]} --------------------------------------------------------------------------------")
    logging.info(f"Extracting source file from {PROJECT}")
    if not os.path.exists(DEST):
        logging.info(f"Destination dir does not exists. Creating {DEST}")
        os.mkdir(DEST)
    proj_vl = pathjoin(PATHS.raw, project_to_scrape, "vulnerable_lines.json")
    with open(proj_vl, 'r') as src:
        logging.info(f"Reading {proj_vl} file")
        ds = json.load(src)
    for key in ds.keys():
        _dict_file_path(ds[key])  # this line is the one that does the hard work
        logging.info("Next...")
    logging.info(f"SUMMARY:\n\tfiles {len(_file_paths)}, functions {len(_functions)}, commits {len(_commits)},"
                 f" line_no. {len(_line_nos)}, lines {len(_lines)}")
    DATASET = pd.DataFrame.from_dict({"function_name": _functions, "file_path": _file_paths, "commit": _commits,
                                      "line_no": _line_nos, "line": _lines})
    DATASET = DATASET.set_index('commit')
    DATASET.to_pickle(pathjoin(PATHS.raw, f"{project_to_scrape}/vulnerable_lines.pkl"))
    logging.info(f"Pickle written successfully. Exiting at time {str(datetime.now())[0:-5]}")
    return


if __name__ == '__main__':
    logging.basicConfig(filename="scrapper.log", level=logging.INFO)
    logging.critical(f"---> Start execution {__file__}")
    # scrape_dataset("data/raw/openssl")
    # PROJECT = 'php'
    # DATASET = pd.read_pickle(f"data/raw/{PROJECT}_vulnerable_lines.pkl")
    # ds = read_files(f"data/raw/{PROJECT}", f"{PROJECT}_commits_test.bin", JOERN_PATH)
    # cpg_stat = create_cpg(ds)
    # parse_source(cpg_stat, f"data/raw/{PROJECT}/functions/")
    produce_df()