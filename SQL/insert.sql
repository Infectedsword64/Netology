INSERT INTO
	PERFORMER (NAME)
VALUES
	('Ария'),
	('Король и шут'),
	('Plamenev'),
	('Константин Лем');

INSERT INTO
	GENRE (TITLE)
VALUES
	('Рок'),
	('Панк-рок'),
	('Альтернатива');

INSERT INTO
	ALBUM (TITLE, YEAR)
VALUES
	('Альбом 1', 2019),
	('Альбом 2', 2022),
	('Альбом 3', 2023),
	('Альбом 4', 2019),
	('Альбом 5', 2022),
	('Альбом 6', 2020),
	('Альбом 7', 2019),
	('Альбом 8', 2022),
	('Альбом 9', 2023),
	('Альбом 10', 2007),
	('Альбом 11', 2022),
	('Альбом 12', 2020);

INSERT INTO
	SONG (ALBUM_ID, TITLE, DURATION)
VALUES
	(1, 'моймир', 60),
	(2, 'My life, my rools', 120),
	(3, 'мойбобр', 180),
	(4, 'Трек 4', 240),
	(5, 'мой день', 300),
	(6, 'Трек 6', 360),
	(7, 'my own', 315),
	(8, 'own my', 360),
	(9, 'my', 200),
	(10, 'oh my god', 147),
	(11, 'myself', 240),
	(12, 'день мой', 300),
	(1, 'by myself', 360),
	(2, 'bemy self', 315),
	(3, 'myself by', 360),
	(4, 'by myself by', 200),
	(5, 'beemy', 147),
	(6, 'premyne', 500);

INSERT INTO
	COLLECTION (TITLE, YEAR)
VALUES
	('Сборник 1', 2018),
	('Сборник 2', 2023),
	('Сборник 3', 2019),
	('Сборник 4', 1992);

INSERT INTO
	GENREPERFORMER (GENRE_ID, PERFORMER_ID)
VALUES
	(1, 1),
	(2, 2),
	(3, 3),
	(1, 4);

INSERT INTO
	PERFORMERALBUM (PERFORMER_ID, ALBUM_ID)
VALUES
	(1, 1),
	(1, 2),
	(1, 3),
	(2, 4),
	(2, 5),
	(2, 6),
	(3, 7),
	(3, 8),
	(3, 9),
	(4, 10),
	(4, 11),
	(4, 12);

INSERT INTO
	COLLECTIONSONG (COLLECTION_ID, SONG_ID)
VALUES
	(1, 1),
	(2, 2),
	(3, 3),
	(4, 4),
	(4, 5);

INSERT INTO
	COLLECTIONSONG (COLLECTION_ID, SONG_ID)
VALUES
	(1, 6),
	(2, 7),
	(3, 8),
	(4, 9),
	(4, 10),
	(1, 11),(2, 12),
	(3, 13),
	(4, 14),
	(4, 15),
	(1, 16),
	(2, 17),
	(3, 18);