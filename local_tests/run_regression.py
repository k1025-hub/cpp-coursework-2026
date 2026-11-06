#!/usr/bin/env python3
"""Compile and run local boundary tests without changing the coursework files.

Examples:
    python3 local_tests/run_regression.py
    python3 local_tests/run_regression.py --sanitize
    python3 local_tests/run_regression.py --only q2 q4

Uses Python 3.9+ and a C++17 compiler; no third-party Python packages required.
The teacher's public checker remains a separate command: python3 tools/check.py .
"""

import argparse
import os
from pathlib import Path
import shutil
import subprocess
import tempfile


def run_phase(command, cwd, timeout):
    try:
        completed = subprocess.run(
            command, cwd=cwd, stdin=subprocess.DEVNULL,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, errors="replace", timeout=timeout,
        )
    except subprocess.TimeoutExpired:
        return False, "Timed out after {} seconds".format(timeout)
    except OSError as error:
        return False, str(error)
    return completed.returncode == 0, completed.stdout.strip()


def main():
    tests_dir = Path(__file__).resolve().parent
    repo = tests_dir.parent
    sources = sorted(tests_dir.glob("*_boundaries.cpp"))
    tests = {source.stem[:-len("_boundaries")]: source for source in sources}
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default=os.environ.get("CXX", "c++"),
                        help="C++17 compiler executable (default: CXX or c++)")
    parser.add_argument("--sanitize", action="store_true",
                        help="Enable AddressSanitizer and UndefinedBehaviorSanitizer")
    parser.add_argument("--only", nargs="+", choices=sorted(tests),
                        help="Run selected test groups instead of all discovered groups")
    args = parser.parse_args()
    compiler = shutil.which(args.compiler)
    if compiler is None:
        parser.error("C++ compiler not found: " + args.compiler)
    if not tests:
        parser.error("No *_boundaries.cpp tests found in " + str(tests_dir))
    names = sorted(set(args.only)) if args.only else list(tests)
    passed = 0
    with tempfile.TemporaryDirectory(prefix="aim-cpp-regression-") as temporary:
        for name in names:
            binary = Path(temporary) / (name + ".exe")
            command = [compiler, "-std=c++17", "-Wall", "-Wextra", "-pedantic"]
            if args.sanitize:
                command += ["-fsanitize=address,undefined", "-fno-omit-frame-pointer"]
            command += [str(tests[name]), "-o", str(binary)]
            compiled, output = run_phase(command, repo, timeout=45)
            if not compiled:
                print("[FAIL] {}: compilation\n{}".format(name, output), flush=True)
                continue
            succeeded, output = run_phase([str(binary)], repo, timeout=10)
            print("[{}] {}{}".format(
                "PASS" if succeeded else "FAIL", name,
                ": " + output if output else "",
            ), flush=True)
            passed += int(succeeded)
    print("Local regression: {}/{} groups passed".format(passed, len(names)))
    return 0 if passed == len(names) else 1


if __name__ == "__main__":
    raise SystemExit(main())
