import argparse
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


def thread(path: str, status_code: int, function):
    global success, fail
    for _ in range(BATCH_SIZE):
        resp = function(f"http://{HOST}:{PORT}{path}")
        if resp.status_code == status_code:
            success += 1
        else:
            fail += 1


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

    for i in range(THREAD_COUNT):
        path, status_code = list(paths.items())[i % len(paths)]
        function = functions[path]

        t = threading.Thread(target=thread(path, status_code, function))

        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print(f"Results: {success}/{success+fail}")


if __name__ == "__main__":
    main()
