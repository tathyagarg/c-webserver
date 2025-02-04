import argparse
import os
import threading

import requests

parser = argparse.ArgumentParser()
parser.add_argument("--host", type=str, default="localhost")
parser.add_argument("--port", type=int, default=8080)
parser.add_argument("--thread_count", type=int, default=100)
parser.add_argument("--batch_size", type=int, default=100)
args = parser.parse_args()

HOST: str = args.host
PORT: int = args.port

THREAD_COUNT: int = args.thread_count
BATCH_SIZE: int = args.batch_size

success = 0
fail = 0
thread_statuses = [0] * THREAD_COUNT


def display_status(size: int = os.get_terminal_size().columns - 10):
    filled = round(size * sum(thread_statuses) / (THREAD_COUNT * BATCH_SIZE))
    print(
        "[",
        "=" * filled,
        " " * (size - filled),
        "] ",
        f"{sum(thread_statuses)/(THREAD_COUNT * BATCH_SIZE)*100:0>6.2f}",
        "%",
        end="\r",
        sep="",
    )


def thread(path: str, status_code: int, function, i: int):
    global success, fail
    for _ in range(BATCH_SIZE):
        try:
            resp = function(f"http://{HOST}:{PORT}{path}")
        except requests.exceptions.ConnectionError as e:
            print()
            raise e
        if resp.status_code == status_code:
            success += 1
        else:
            fail += 1

        thread_statuses[i] += 1
        display_status()


def main():
    threads = []
    paths = {
        "/": 200,
        "/this_doesnt_exist": 404,
        "/get_ep": 405,
    }
    functions = {
        "/": requests.get,
        "/this_doesnt_exist": requests.get,
        "/get_ep": requests.post,
    }

    display_status()
    for i in range(THREAD_COUNT):
        path, status_code = list(paths.items())[i % len(paths)]
        function = functions[path]

        t = threading.Thread(target=thread(path, status_code, function, i))

        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print(f"\nSuccess: {success}, Fail: {fail}")


if __name__ == "__main__":
    main()
