from cs50 import *


def letter_len(texts):
    x = 0
    for text in texts:
        if text.isalpha():
            x += 1
    return x


def word_len(texts):
    return len(texts.split())


def sentence_len(text):
    word = 0
    punctuation_seen = False
    for char in text:
        if char in ['?', '.', '!']:
            if not punctuation_seen:
                word += 1
                punctuation_seen = True
        else:
            punctuation_seen = False
    return word


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
