SELECT DISTINCT name FROM people, ratings, directors, movies
WHERE people.id = directors.person_id AND movies.id = directors.movie_id
AND movies.id = ratings.movie_id AND ratings.rating >= 9.0;