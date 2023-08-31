import subprocess

def main():
    subprocess.run([
        "cmake",
        "--preset",
        "default"
    ], shell=True)

    subprocess.run([
        "cmake",
        "--build",
        "--preset",
        "default"
    ], shell=True)

if __name__ == "__main__":
    main()