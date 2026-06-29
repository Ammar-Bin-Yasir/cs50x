from cs50 import get_int

# To Get the Height of the Pyramid
while True:
    Height = get_int("Enter The Height: ")
    if 1 <= Height <= 8:
        break

for i in range(Height):
    # white space
    print(" " * (Height - i - 1), end="")
    # Hash
    print("#" * (i + 1), end="")
    # Print middle space
    print("  ", end="")
    # Print left hashes
    print("#" * (i + 1))
