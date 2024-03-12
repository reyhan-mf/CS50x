-- Keep a log of any SQL queries you execute as you solve the mystery.

-- airports              crime_scene_reports   people
-- atm_transactions      flights               phone_calls
-- bakery_security_logs  interviews
-- bank_accounts         passengers

-- Track crime scene that has duck inside the description
 SELECT * FROM crime_scene_reports WHERE description LIKE '%duck%';

-- 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT * FROM interviews WHERE month = 7 AND day= 28 ;

-- | 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--                                           If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

--License Plate?

-- Found suspects
SELECT name, people.license_plate FROM bakery_security_logs
    JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND (hour = 10 AND minute >= 10 AND minute < 25) AND activity = "exit";




-- | 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it was someone I recognized.
--                                           Earlier this morning, before I arrived at Emma's bakery,
--                                           I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- ATM Transaction
SELECT person_id, name, phone_number, passport_number, bank_accounts.account_number FROM atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
WHERE day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";

--Intersects a person that in the parking lot and withdraws some money from ATM
SELECT * FROM bakery_security_logs
    JOIN people ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND month = 7 AND (hour = 10 AND minute >= 10 AND minute < 25) AND activity = "exit";
INNER JOIN
SELECT COUNT(*) FROM atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
WHERE day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";


-- | 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--                                             In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--                                             The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- Phone Calls
SELECT * FROM people
    JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND duration < 60;

--Earliest Flight
SELECT * FROM flights WHERE day = 29 AND month = 7 AND hour < 10;

-- id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |

-- The thief
-- This query above to find out the person who flights to new york city which is represented by flight_id = 36
SELECT * FROM (
    SELECT person_id, name, phone_number, passport_number, bank_accounts.account_number FROM atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
    WHERE day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
) AS atm_people
JOIN passengers ON passengers.passport_number = atm_people.passport_number
WHERE flight_id = 36;

-- +-----------+--------+----------------+-----------------+----------------+-----------+-----------------+------+
-- | person_id |  name  |  phone_number  | passport_number | account_number | flight_id | passport_number | seat |
-- +-----------+--------+----------------+-----------------+----------------+-----------+-----------------+------+
-- | 686048    | Bruce  | (367) 555-5533 | 5773159633      | 49610011       | 36        | 5773159633      | 4A   |
-- | 395717    | Kenny  | (826) 555-1652 | 9878712108      | 28296815       | 36        | 9878712108      | 7A   |
-- | 467400    | Luca   | (389) 555-5198 | 8496433585      | 28500762       | 36        | 8496433585      | 7B   |
-- | 449774    | Taylor | (286) 555-6063 | 1988161715      | 76054385       | 36        | 1988161715      | 6D   |
-- +-----------+--------+----------------+-----------------+----------------+-----------+-----------------+------+

-- This query below to determine the person who calls when the theft happened.
SELECT * FROM people
    JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND duration < 60;

-- +--------+---------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate | id  |     caller     |    receiver    | year | month | day | duration |
-- +--------+---------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       | 221 | (130) 555-0289 | (996) 555-8899 | 2023 | 7     | 28  | 51       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | 224 | (499) 555-9472 | (892) 555-8872 | 2023 | 7     | 28  | 36       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       | 251 | (499) 555-9472 | (717) 555-1342 | 2023 | 7     | 28  | 50       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 254 | (286) 555-6063 | (676) 555-6554 | 2023 | 7     | 28  | 43       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 255 | (770) 555-1861 | (725) 555-3243 | 2023 | 7     | 28  | 49       |
-- | 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       | 261 | (031) 555-6622 | (910) 555-3251 | 2023 | 7     | 28  | 38       |
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 279 | (826) 555-1652 | (066) 555-9701 | 2023 | 7     | 28  | 55       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 281 | (338) 555-6650 | (704) 555-2131 | 2023 | 7     | 28  | 54       |
-- +--------+---------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+

--GOTCHA, It waas BRUCE! Why? because Bruce was both in those both query, Bruce are going to flights into new york city and he was calling for a less than
-- a minute when the theft happened.


-- Accomplice, Its time to find who is the accomplice?
SELECT * FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE name = "Bruce" AND duration < 60 AND day = 28 AND month = 7;

-- +--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
-- |   id   | name  |  phone_number  | passport_number | license_plate | id  |     caller     |    receiver    | year | month | day | duration |
-- +--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | 233 | (367) 555-5533 | (375) 555-8161 | 2023 | 7     | 28  | 45       |
-- +--------+-------+----------------+-----------------+---------------+-----+----------------+----------------+------+-------+-----+----------+

-- GOTCHA, time to do last query to know who is the receiver!

SELECT * FROM people WHERE phone_number = "(375) 555-8161";

-- --+--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 864400 | Robin | (375) 555-8161 | NULL            | 4V16VO0       |
-- +--------+-------+----------------+-----------------+---------------+

-- THE ACCOMPLICE WAS ROBIN!! FINALLYYY GOD THAT WAS FELT SO SATISFFYINGG
