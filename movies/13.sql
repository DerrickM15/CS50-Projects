SELECT people.name FROM people, stars, movies
WHERE people.id = stars.person_id
AND movies.id = stars.movie_id
AND movie_id IN
(
    SELECT movies.id FROM movies, stars, people
    WHERE movies.id = stars.movie_id
    AND people.id = stars.person_id
    AND people.name = "Kevin Bacon"
    AND people.birth = 1958
)
AND people.name != "Kevin Bacon";