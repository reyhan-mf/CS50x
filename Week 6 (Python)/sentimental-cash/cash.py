# TODO
from cs50 import *


def get_cents():
    while True:
        cents = get_float("Changed owed: ")
        if cents > 0:
            break
    return int(cents * 100)


def calculate_quarters(cents):
    x = 0
    if cents >= 25:
        for i in range(25, cents + 1, 25):
            x += 1
    return x


def calculate_dimes(cents):
    x = 0
    if cents >= 10:
        for i in range(10, cents + 1, 10):
            x += 1
    return x


def calculate_nickels(cents):
    x = 0
    if cents >= 5:
        for i in range(5, cents + 1, 5):
            x += 1
    return x


def calculate_pennies(cents):
    x = 0
    if cents >= 1:
        for i in range(1, cents + 1, 1):
            x += 1
    return x


def main():
    cents = get_cents()

    quarters = int(calculate_quarters(cents))
    cents -= quarters * 25

    dimes = int(calculate_dimes(cents))
    cents -= dimes * 10

    nickels = int(calculate_nickels(cents))
    cents -= nickels * 5

    pennies = int(calculate_pennies(cents))
    cents -= pennies * 1

    coins = quarters + dimes + nickels + pennies

    print(coins)


main()
