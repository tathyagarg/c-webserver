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


def thread():
    global success, fail
    for _ in range(BATCH_SIZE):
        resp = requests.get(f"http://{HOST}:{PORT}")
        if resp.status_code == 200:
            success += 1
        else:
            fail += 1


def main():
    threads = []
    for _ in range(THREAD_COUNT):
        t = threading.Thread(target=thread)

        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    print(f"Results: {success}/{success+fail}")


if __name__ == "__main__":
    main()
