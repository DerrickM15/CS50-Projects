from cs50 import get_int, get_string

# Get the user's card number
number = get_string("Number: ")
card_length = len(number)
multiplied_digits = ""
sum_multiplied_digits = 0
other_digits = 0
card_valid = False
for i in range(card_length - 2, -1, -2):
    multiplied_digits += str(int(number[i]) * 2)
for i in range(len(multiplied_digits)):
    sum_multiplied_digits += int(multiplied_digits[i])
for i in range(card_length - 1, -1, -2):
    other_digits += int(number[i])
if ((sum_multiplied_digits + other_digits) % 10) == 0:
    card_valid = True
# VISA case
if card_length == 16 and number[0] == "4" and card_valid == True:
    print("VISA")
# AMEX case
elif card_length == 15 and card_valid == True:
    print("AMEX")
# MASTERCARD case
elif card_length == 16 and number[0] == "5" and card_valid == True:
    print("MASTERCARD")
# INVALID case
else:
    print("INVALID")