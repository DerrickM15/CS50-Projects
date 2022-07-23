import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Review arguments")
        exit(1)
    # Read database file into a variable
    people = []
    str_list = []
    with open(sys.argv[1], "r") as database:
        reader = csv.DictReader(database)
        for row in reader:
            for key in row:
                if key != 'name':
                    row[key] = int(row[key])
                    if key not in str_list:
                        str_list.append(key)
            people.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    matches = {}
    for i in range(len(str_list)):
        matches[str_list[i]] = (longest_match(sequence, str_list[i]))

    # Check database for matching profiles
    perfect_match = "No match"
    for people_dict in people:
        count = 0
        for key, value in matches.items():
            if people_dict[key] != value:
                break
            else:
                count += 1
            if count == len(people_dict) - 1:
                perfect_match = people_dict['name']

    print(perfect_match)
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
