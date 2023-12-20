import subprocess
import sys

def main():
    subprocess.run([
        "cmake",
        "--preset",
        sys.argv[1]
    ], shell=True)

    subprocess.run([
        "cmake",
        "--build",
        f"build-{sys.argv[1]}"
    ], shell=True)

if __name__ == "__main__":
    main()