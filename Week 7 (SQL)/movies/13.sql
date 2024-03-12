SELECT a.name FROM
(SELECT name, movies.id FROM people
    JOIN stars ON stars.person_id = people.id
    JOIN movies ON movies.id = stars.movie_id) as a
INNER JOIN
(SELECT movies.id FROM movies
    JOIN stars ON stars.movie_id = movies.id
    JOIN people ON people.id = stars.person_id
WHERE name = "Kevin Bacon" and birth = 1958) as b
on a.id = b.id
WHERE a.name != "Kevin Bacon";

