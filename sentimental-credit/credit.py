import cs50

def main():
    while True:
        number = cs50.get_int("Enter The Number: ")
        if number > 0:
            break

    digit = checksum(number)

    if digit % 10 == 0:
        # Get the length of the digits to check different cards
        length = len(str(number))

        # See the first 2 digits to determine the different cards
        start_digits = int(str(number)[:2])

        # Print AMEX, VISA, MASTERCARD, INVALID
        if length == 15 and (start_digits == 34 or start_digits == 37):
            print("AMEX")
        elif length == 16 and (51 <= start_digits <= 55):
            print("MASTERCARD")
        elif (length == 13 or length == 16) and (str(number)[0] == "4"):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")

def checksum(number):
    number = str(number)
    sumld = 0
    sumsld = 0

    # Start from the last digit, moving backward
    for i in range(len(number) - 1, -1, -1):
        digit = int(number[i])
        # Double every second digit from the end
        if (len(number) - i) % 2 == 0:
            doubled = digit * 2
            sumsld += (doubled // 10 + doubled % 10) if doubled > 9 else doubled
        else:
            sumld += digit

    return sumld + sumsld

main()
