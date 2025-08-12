def main():
    # Get the Height From the user
    try:
        height = int(input("Enter the Height: "))
    except ValueError:
        return 1
    else:
        # Iterate over the Height of pryamid, row by row
        for row in range(1, height + 1):

            spaces = " " * (height - row)
            hashes = "#" * row

            print(f"{spaces}{hashes}", end="")

            # 2nd Pryamid

            print("  ", end="")
            print(hashes)


if __name__ == "__main__":
    main()
