-- SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred
-- Select names of those persons
SELECT name
FROM people
WHERE id IN
(
    -- Select the ID of those people who stared in those movies
    SELECT person_id
    FROM stars
    WHERE movie_id IN
    (
        SELECT movie_id
        FROM stars
        WHERE person_id = (SELECT id FROM people WHERE name = 'Kevin Bacon')
    )
)
AND name != 'Kevin Bacon';
