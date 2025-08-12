import re
import sys

def main():
    print(count(input("Text: ")))


def count(s):

    # Get the string of text from the user
    matches = re.findall(r"\b[\.\?\,]?um[\.\?\,]?\b", s, flags=re.IGNORECASE)
    # Search for the word "um" in that string
    length = len(matches)
    # return the count of the times "um" was in the string
    return length

if __name__ == "__main__":
    main()
