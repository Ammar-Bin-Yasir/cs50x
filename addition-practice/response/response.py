import validators

def main():
    # Get input from user
    email = input("What's your email address? ")

    # Validate that email
    if validators.email(email):
        print("Valid")
    else:
        print("Invalid")


if __name__ == "__main__":
    main()
