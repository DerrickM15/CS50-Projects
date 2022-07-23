SELECT movies.title, ratings.rating FROM movies
JOIN ratings
ON movies.id = ratings.movie_id
Where movies.id IN (SELECT id from movies WHERE year = 2010)
Order BY rating DESC, title ASC;