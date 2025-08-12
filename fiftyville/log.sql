-- Keep a log of any SQL queries you execute as you solve the mystery.
-- See what's inside the database
.tables

-- Investigate the crime_scene_reports
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7
AND street = 'Humphery Street'

-- INFO: Time: 10:15am, 3 witnesses, each of their interview transcripts mentions the bakery.

-- SEE what the witness had to say
SELECT name,transcript FROM interviews
WHERE day = 28 AND MONTH = 7;

-- INFO: Ruth: Look at the bakery(Emma's bakery) parking lot security footage within 10mins of theft 10:15-10:25 am
--       Eugene: Earlier the morning of the theft, the theif used the atm on Leggett Street
--       Raymond: As he was leaving the bakery, he called someone for less then a minute, planed to take the earliest flight out of fiftyville 'tomorrow', theif asked his friend to book a ticket.

-- Bakery security logs
SELECT activity, license_plate,hour,minute FROM bakery_security_logs
WHERE month = 7 AND day = 28
AND hour = 10 AND
minute BETWEEN 15 AND 25

-- INFO: 8 cars, left:
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- ATM transactions on Leggett Street
SELECT * FROM atm_transactions
WHERE day = 28 AND month = 7
AND atm_location = 'Leggett Street';

-- INFO: 8 transactions,
-- account_numbers,amount:
-- 28500762   48
-- 28296815   20
-- 76054385   60
-- 49610011   50
-- 16153065   80
-- 25506511   20
-- 81061156   30
-- 26013199   35

-- JOIN atm_transactions, bank_accounts,people,bakery_security_logs.
-- fiter by the bank_account numbers we have and the license plates to get the person name,phone_num,passport
SELECT phone_number, name, passport_number FROM people
WHERE people.id IN
(
    SELECT person_id FROM bank_accounts
    WHERE account_number IN
    (
        28500762, 28296815, 76054385, 49610011, 16153065, 25506511, 81061156, 26013199
    )
)
AND people.license_plate IN
(
    '5P2BI95', '94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55'
);

-- INFO: phone_number, name, passport_number
-- (829) 555-5269, Iman, 7049073643 (Suspect Cleared)
-- (389) 555-5198, Luca, 8496433585 (Suspect Cleared)
-- (770) 555-1861, Diana,3592750733
-- (367) 555-5533, Bruce,5773159633

-- Investigate the phone_nums
SELECT * FROM phone_calls
WHERE caller IN ('(829) 555-5269', '(389) 555-5198', '(770) 555-1861', '(367) 555-5533')
AND day = 28 AND month = 7
AND duration < 60;

-- INFO: Caller, REciever:
-- (367) 555-5533, (375) 555-8161
-- (770) 555-1861, (725) 555-3243


-- See which one of the suspect booked a flight on 29th july
SELECT * FROM passengers
JOIN flights ON flights.id = passengers.flight_id
WHERE passport_number IN (3592750733, 5773159633)
AND flight_id IN (18, 23, 36, 43, 53)
AND flights.day = 29 AND flights.month = 7 and flights.year = 2023;


-- See who the Accomplice is
SELECT name from people
WHERE phone_number IN ('(375) 555-8161', '(725) 555-3243');
