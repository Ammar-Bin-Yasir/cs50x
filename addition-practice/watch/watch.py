import re
import sys


def main():
    print(parse(input("HTML: ")))


def parse(s):
    # From the iframe tag, find the src attribute and extract the unique url
    link = re.search(r'src="https?://(?:www\.)?youtube.com/embed/([^"]+)"', s)

    # shotren the src link to required length
    if link:
        return "https://youtu.be/" + link.group(1)
    else:
    # return the shortened link
        return None

if __name__ == "__main__":
    main()
