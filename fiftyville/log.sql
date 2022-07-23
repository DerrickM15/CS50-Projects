-- Want to start with reading crime scene reports for the day of the theft, identified theft took place at 10:15AM and the bakery, 3 witnesses
SELECT * FROM crime_scene_reports
Where year = 2021
AND month = 7
AND day = 28;

-- Reading the interviews from the day of the theft, found out thief had ATM transaction earlier in the morning day of theft, made a phone call, was taking flight out next day, and left the parking lot within 10 minutes of the theft
SELECT transcript, name FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;

-- Search for any names that match the ATM transactions for the morning of, the phone calls the day of, and the flight passengers the following day

SELECT name FROM people, bank_accounts, atm_transactions
WHERE people.id = bank_accounts.person_id
AND atm_transactions.account_number = bank_accounts.account_number
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
INTERSECT
SELECT name FROM people, phone_calls
WHERE people.phone_number = phone_calls.caller
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
INTERSECT
SELECT name FROM people, passengers, flights, airports
WHERE people.passport_number = passengers.passport_number
AND passengers.flight_id = flights.id
AND flights.origin_airport_id =
(
    SELECT airports.id FROM airports
    WHERE airports.city LIKE "Fiftyville"
)
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29;

-- Narrowed down to 7 suspects, need to check bakery security logs after realizing someone saw theif drive out of the bakery parking lot within 10 minutes after the theft
SELECT name FROM people, bank_accounts, atm_transactions
WHERE people.id = bank_accounts.person_id
AND atm_transactions.account_number = bank_accounts.account_number
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
INTERSECT
SELECT name FROM people, phone_calls
WHERE people.phone_number = phone_calls.caller
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
INTERSECT
SELECT name FROM people, passengers, flights, airports
WHERE people.passport_number = passengers.passport_number
AND passengers.flight_id = flights.id
AND flights.origin_airport_id =
(
    SELECT airports.id FROM airports
    WHERE airports.city LIKE "Fiftyville"
)
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
INTERSECT
SELECT name FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate
AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute > 15
AND bakery_security_logs.minute < 25;
-- That narrowed it down to Bruce or Diana, maybe refine the transaction location and type
SELECT name FROM people, bank_accounts, atm_transactions
WHERE people.id = bank_accounts.person_id
AND atm_transactions.account_number = bank_accounts.account_number
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.transaction_type = "withdraw"
INTERSECT
SELECT name FROM people, phone_calls
WHERE people.phone_number = phone_calls.caller
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
INTERSECT
SELECT name FROM people, passengers, flights, airports
WHERE people.passport_number = passengers.passport_number
AND passengers.flight_id = flights.id
AND flights.origin_airport_id =
(
    SELECT airports.id FROM airports
    WHERE airports.city LIKE "Fiftyville"
)
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
INTERSECT
SELECT name FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate
AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute > 15
AND bakery_security_logs.minute < 25;
-- Still Diana or Bruce, last piece is the time of the flight..
SELECT * FROM flights WHERE day = 29 AND hour < 10 LIMIT 10;
-- Earliest flight is during 8 hour
SELECT name FROM people, bank_accounts, atm_transactions
WHERE people.id = bank_accounts.person_id
AND atm_transactions.account_number = bank_accounts.account_number
AND atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.transaction_type = "withdraw"
INTERSECT
SELECT name FROM people, phone_calls
WHERE people.phone_number = phone_calls.caller
AND phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
INTERSECT
SELECT name FROM people, passengers, flights, airports
WHERE people.passport_number = passengers.passport_number
AND passengers.flight_id = flights.id
AND flights.origin_airport_id =
(
    SELECT airports.id FROM airports
    WHERE airports.city LIKE "Fiftyville"
)
AND flights.year = 2021
AND flights.month = 7
AND flights.day = 29
AND flights.hour = 8
INTERSECT
SELECT name FROM people, bakery_security_logs
WHERE people.license_plate = bakery_security_logs.license_plate
AND bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute > 15
AND bakery_security_logs.minute < 25;
-- It was bruce, now just need to check the phone logs so I know the accomplice
SELECT DISTINCT name FROM people, phone_calls
WHERE people.phone_number = phone_calls.receiver
AND phone_calls.receiver =
(
    SELECT phone_calls.receiver from phone_calls
    WHERE caller =
        (
            SELECT people.phone_number FROM people WHERE name = "Bruce"
            AND year = 2021
            AND month = 7
            AND day = 28
            AND phone_calls.duration < 60
        )
);
-- ROBIN
-- Next need to know the destination of his flight for the escape city
SELECT DISTINCT airports.city FROM airports, flights, passengers
WHERE airports.id = destination_airport_id
AND flights.destination_airport_id =
(
    SELECT flights.destination_airport_id FROM flights
    WHERE flights.origin_airport_id =
    (
        SELECT airports.id FROM airports
        WHERE airports.city LIKE "Fiftyville"
        AND flights.year = 2021
        AND flights.month = 7
        AND flights.day = 29
        AND flights.hour = 8
    )
);
-- New York City

