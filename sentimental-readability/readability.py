from cs50 import get_string
import math
# Initialize variables
letters = 0
words = 1
sentences = 0
# Get input text from the user
text = get_string("Text: ")
# Loop through the text
for i in text:
    # If the character at the current index is in the alphbet
    if i.isalpha():
        # Increase letter count
        letters += 1
for i in text:
    # If the character at the current index is a space
    if i.isspace():
        # Increase word count
        words += 1
for i in text:
    # If the character at the current index is a punctuation mark
    if i == "." or i == "!" or i == "?":
        # Increase sentence count
        sentences += 1

L = letters / words * 100
S = sentences / words * 100

grade = round((0.0588 * L) - (0.296 * S) - 15.8)
if grade >= 16:
    print("Grade 16+")
elif grade <= 1:
    print("Before Grade 1")
else:
    print(f"Grade {grade}")