import matplotlib.pyplot as plt

def main():
    data = []
    with open('out/a.out.txt') as f:
        lines = f.readlines()
        for line in lines:
            data.append(line)

    plt.plot(data)
    plt.plot(data, "g*")
    plt.show()

if __name__ == "__main__":
    main()