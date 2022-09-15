SELECT DISTINCT name FROM people, stars, movies
WHERE people.id = stars.person_id AND movies.id = stars.movie_id AND movies.year = 2004
ORDER BY people.birth;