import re
import sys

def main():
    print(convert(input("Hours: ")))


def convert(s):
    # get input in 12 hours format (in 4 different ways)
    time = re.search(r"^([1-9]|1[0-2])\:?([0-5][0-9])? (AM|PM) to ([1-9]|1[0-2])\:?([0-5][0-9])? (AM|PM)$", s)
    if time is None:
        raise ValueError("Invalid input format")
    else:
        # Evaluate other exceptions
        if time.group(1) == "12" and time.group(2) is not None and time.group(2) == "60":
            raise ValueError("Invalid input format")
        elif time.group(4) == "12" and time.group(5) is not None and time.group(5) == "60":
            raise ValueError("Invalid input format")
        elif (time.group(3) == "AM" and time.group(6) == "AM") or (time.group(3) == "PM" and time.group(6) == "PM"):
            raise ValueError("Invalid input format")
    # Convert that input to 24 hour format respectively ( ##:## to ##:## )
    minutes1 = time.group(2) if time.group(2) is not None else "00"
    minutes2 = time.group(5) if time.group(5) is not None else "00"
    if time.group(3) == "AM":
        hours1 = "00" if time.group(1) == "12" else time.group(1).zfill(2)
    else:
        hours1 = time.group(1) if time.group(1) == "12" else str(int(time.group(1)) + 12).zfill(2)

    if time.group(6) == "AM":
        hours2 = "00" if time.group(4) == "12" else time.group(4).zfill(2)
    else:
        hours2 = time.group(4) if time.group(4) == "12" else str(int(time.group(4)) + 12).zfill(2)
    # return the converted string
    return f"{hours1}:{minutes1} to {hours2}:{minutes2}"



if __name__ == "__main__":
    main()
