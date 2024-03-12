from cs50 import *
while True:
    n = get_int("Height: ")
    if n > 0 and n <= 8:
        break

for i in range(n):

    for k in range (n, i + 1, -1):
        print(" ", end="")

    for j in range(i + 1):
        print("#", end="")

    for l in range (i + 1):
        if l == 0:
            print("  #", end="")
        else:
            print("#", end="")
    print()






