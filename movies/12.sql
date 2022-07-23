SELECT title FROM movies, stars, people
WHERE movies.id = stars.movie_id
AND people.id = stars.person_id
AND people.name = "Johnny Depp"
INTERSECT
SELECT title FROM movies, stars, people
WHERE movies.id = stars.movie_id
AND people.id = stars.person_id
AND people.name = "Helena Bonham Carter";