import logging
from fastapi import HTTPException
import logging
from enum import Enum

Color = Enum(
    'Color', 'BLACK RED GREEN YELLOW BLUE MAGENTA CYAN WHITE', start=30
)


class CustomFormatter(logging.Formatter):
    grey = '\033[1m'
    yellow = "\x1b[33;20m"
    red = "\x1b[31;20m"
    bold_red = "\x1b[31;1m"
    reset = "\x1b[0m"
    # format = "%(asctime)s - %(name)-14s - %(levelname)-8s - %(message)s (%(filename)s:%(lineno)d)"
    format = "%(asctime)s - %(name)-14s - %(levelname)-8s - %(message)s"

    FORMATS = {
        logging.DEBUG: grey + format + reset,
        logging.INFO: grey + format + reset,
        logging.WARNING: yellow + format + reset,
        logging.ERROR: red + format + reset,
        logging.CRITICAL: bold_red + format + reset
    }

    def format(self, record):
        log_fmt = self.FORMATS.get(record.levelno)
        formatter = logging.Formatter(log_fmt)
        return formatter.format(record)


class LogHTTPException(HTTPException):
    def __init__(self, status_code: int, msg: str):
        logging.error(f"Returning {status_code}: {msg}")
        super(LogHTTPException, self).__init__(status_code, msg)


def pretty_log(msg, level: int = logging.INFO) -> None:
    for line in msg.split("\n"):
        logging.log(level, line)


def setup_logging() -> None:
    # create console handler with a higher log level
    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)
    ch.setFormatter(CustomFormatter())

    # Redirect all logging
    for logger_name in ["root", "uvicorn.access"]:
        logger = logging.getLogger(logger_name)
        logger.setLevel(logging.INFO)
        logger.addHandler(ch)


if __name__ == "__main__":
    setup_logging()
    logging.debug("debug message")
    logging.info("info message")
    logging.warning("warning message")
    logging.error("error message")
    logging.critical("critical message")
