# Prompt for height

def main():
    height = get_height()
    blocks = height
    for i in range(1, height +1):
        for j in range(1, height +1):
            if j < blocks:
                print(' ', end='')
            elif j >= blocks:
                print('#', end='')
            if j == height:
                print('  ', end='')
        for k in range(height, 0, -1):
            if k >= blocks:
                print('#', end='')
        print()
        blocks-=1

def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n in range(1, 9):
                break
        except ValueError:
            print("That's not an integer!")
    return n

main()