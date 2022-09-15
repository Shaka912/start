-- Keep a log of any SQL queries you execute as you solve the mystery.
-- checking crime scene reports from robbery event that took place on 28th of july 2021
SELECT description FROM crime_scene_reports WHERE month = 7 AND day =28 AND year 2021;
-- by checking reports of the witnesss each witness mention the bakery now we will check bakery security logs
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- by checkings transcripts of witness, witness1 said he saw theif leaving parking lot of bakery somewhere about 10minute after the crime scene
SELECT people.name, bakery_security_logs.license_plate,bakery_security_logs.minute FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >=15 AND
bakery_security_logs.minute<=25 AND bakery_security_logs.activity = 'exit'
ORDER BY bakery_security_logs.minute;
-- from interviews transcripts thew 2nd witness said he saw theif withdrawing some money from ATM on 'Leggett Street'
-- CHECKING atm_transactions to get account number
SELECT account_number, amount FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';
-- the 3rd witness said he heard theif talking to somneone on phone they talkaed about for a minute the theif said they are going to leave fifityville by tommarow on plane
-- now we are checking phone calls that were made at that day and the duration is less than a minute
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2021 AND month = 7   AND day = 28
AND duration <100 ORDER BY duration;
-- now we are checking details of flights that are leaving FROM fiftyville and check wheter our prime suspect is in it or not
SELECT id FROM airports WHERE city = 'Fifftyville';
SELECT id, destination_airport_id FROM flights WHERE orgin_airport_id = 8 AND year = 2021 AND month = 7
AND day = 29;
-- our prime suspect is in flight_id 18 that is leaving for boston
SELECT * FROM passengers WHERE flight_id = 18 AND passport_number = 3592750733;
-- now we have to check who the theif was calling to book the flights
SELECT name FROM people WHERE phone_number = '(725) 555-3243';