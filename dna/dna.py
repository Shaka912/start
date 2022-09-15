import csv
import sys


def main():

    s1 = "AGATC"
    s2 = "AATG"
    s3 = "TATC"
    STR_counts = {"AGATC":[],"AATG":[],"TATC":[]}
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: program name / .CSV /.txt")
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        csv_data = list(reader)
    file.close()

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as f2:
        data = f2.read()

    # TODO: Find longest match of each STR in DNA sequence
        for i in csv_data[0]:
            STR_counts[i] = longest_match(data, i)

    f2.close()
    
    # TODO: Check database for matching profiles
    suspect = 'no match'
    suspect_count = 1
    for i in range(len(csv_data)):
        for j in STR_counts:
            #casting int to str
            if str(STR_counts[j]) == csv_data[i][j]:
                suspect_count += 1
        if suspect_count == len(STR_counts):
            suspect = csv_data[i]['name']
            break
        else:
            suspect_count = 1
    print(f"{suspect}")
    #print(f"{csv_data}")
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
