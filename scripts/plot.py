import sys
import matplotlib.pyplot as plt

def main():
    data = []
    with open(sys.argv[1]) as f:
        lines = f.readlines()
        for line in lines:
            data.append(int(line))

    plt.plot(data)
    plt.plot(data, "-")
    plt.show()

if __name__ == "__main__":
    main()