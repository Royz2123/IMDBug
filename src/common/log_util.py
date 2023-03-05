import logging

from fastapi import HTTPException

TITLE_LEVEL = logging.INFO + 1


class LogHTTPException(HTTPException):
    def __init__(self, status_code: int, msg: str):
        logging.error(f"{msg}, returning {status_code}")
        super(LogHTTPException, self).__init__(status_code, msg)


class CustomFormatter(logging.Formatter):
    grey = '\x1b[38;20m'
    white = '\x1b[20m'
    white_underline = '\x1b[21m'
    yellow = "\x1b[33;20m"
    red = "\x1b[31;20m"
    bold_red = "\x1b[31;1m"
    reset = "\x1b[0m"
    format = "%(asctime)s - %(name)-14s - %(levelname)-8s - %(message)s"

    FORMATS = {
        logging.DEBUG: white + format + reset,
        logging.INFO: white + format + reset,
        TITLE_LEVEL: white_underline + format + reset,
        logging.WARNING: yellow + format + reset,
        logging.ERROR: red + format + reset,
        logging.CRITICAL: bold_red + format + reset
    }

    def __init__(self):
        # Current solution for removing double logs, should fix
        self.prev_record = None
        super(CustomFormatter, self).__init__()

    def format(self, record):
        if record == self.prev_record:
            return ""
        log_fmt = self.FORMATS.get(record.levelno)
        formatter = logging.Formatter(log_fmt)
        self.prev_record = record
        return formatter.format(record)


def pretty_log(msg, level: int = logging.INFO) -> None:
    for line in msg.split("\n"):
        logging.log(level, line)


def setup_logging() -> None:
    logging.addLevelName(TITLE_LEVEL, "TITLE")

    # create console handler with a higher log level
    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)
    ch.setFormatter(CustomFormatter())

    # Redirect all logging
    for logger_name in ["uvicron", "uvicorn.access", None]:
        logger = logging.getLogger(logger_name)
        logger.handlers.clear()
        logger.setLevel(logging.DEBUG)
        if logger_name != "uvicorn":
            logger.addHandler(ch)


if __name__ == "__main__":
    setup_logging()
    logging.debug("debug message")
    logging.info("info message")
    logging.warning("warning message")
    logging.error("error message")
    logging.critical("critical message")
