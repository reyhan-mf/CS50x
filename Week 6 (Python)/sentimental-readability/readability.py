from cs50 import *
import re


def letter_len(texts):
    x = 0
    for text in texts:
        if text.isalpha():
            x += 1
    return x


def word_len(texts):
    return len(texts.split())


def sentence_len(text):
    return len(re.findall(r'[.!?]', text))


def main():
    text = get_string("Text: ")
    L = float((letter_len(text) / word_len(text)) * 100)
    S = float((sentence_len(text) / word_len(text)) * 100)

    result = round((0.0588 * L - 0.296 * S - 15.8))

    if result < 2:
        print("Before Grade 1")
    elif result >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(result)}")


main()
