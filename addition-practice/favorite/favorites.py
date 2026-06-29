from collections import Counter
import csv

with open("favorites.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    counts = Counter()

    # Iterate over the csv file, counting favorites
    for row in reader:
        favorite = row["problem"]
        counts[favorite] += 1

# Print counts
favorite = input("Favorite: ")
print(f"{favorite}: {counts[favorite]}")
