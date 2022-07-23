SELECT title FROM movies, stars, people, ratings
WHERE movies.id = stars.movie_id
AND people.id = stars.person_id
AND ratings.movie_id = movies.id
AND people.name = "Chadwick Boseman"
ORDER BY rating DESC LIMIT 5;