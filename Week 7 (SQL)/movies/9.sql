SELECT DISTINCT(name) FROM stars
JOIN people ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE year = 2004
ORDER BY birth
;
