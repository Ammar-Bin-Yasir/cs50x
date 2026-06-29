# Calculates the reading level for a particular text given (Grade 1-16+)
import cs50
import re


def main():
    # Prompt user for text
    Text = input("Text: ")

    # Count the number of Letters
    L = letters(Text)
    # Count the number of Words
    W = words(Text)
    # Count the number of Sentences
    S = sentences(Text)
    # Compute the Coleman-Liau Index
    index = CL_index(L, W, S)
    # Print the Grade level
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def letters(text):
    letters = 0

    for char in text:
        if char.isalpha():
            letters += 1

    return letters


def words(text):
    words = 0

    word_list = text.split()

    words = len(word_list)

    return words


def sentences(text):

    sentences = re.findall(r'[.!?]', text)

    return len(sentences)


def CL_index(letters, words, sentences):

    L = letters / words * 100

    S = sentences / words * 100

    return round(0.0588 * L - 0.296 * S - 15.8)


main()
