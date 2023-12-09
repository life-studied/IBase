-- 插入乐队数据
INSERT INTO `band` (`id`, `name`, `createtime`, `intro`, `leader`) VALUES
(1, 'Rock Band', '2022-01-01', 'We are a rock band from the city.', 'John Doe'),
(2, 'Pop Group', '2022-02-15', 'Catchy tunes and vibrant performances.', 'Jane Smith'),
(3, 'Jazz Ensemble', '2022-03-20', 'Exploring the depths of jazz music.', 'Robert Johnson');

-- 插入成员数据
INSERT INTO `member` (`id`, `name`, `sex`, `duty`, `jointime`, `leavetime`, `bandid`) VALUES
(1, 'Mike Anderson', 'Male', 'Guitarist', '2022-01-10 08:00:00', NULL, 1),
(2, 'Lisa Johnson', 'Female', 'Vocalist', '2022-02-20 09:30:00', NULL, 2),
(3, 'Chris Davis', 'Male', 'Drummer', '2022-03-25 10:45:00', NULL, 3),
(4, 'Emily White', 'Female', 'Bassist', '2022-01-15 08:30:00', '2023-05-01 12:00:00', 1),
(5, 'Mark Taylor', 'Male', 'Pianist', '2022-02-28 11:15:00', '2023-04-20 10:30:00', 2),
(6, 'Sophia Martinez', 'Female', 'Saxophonist', '2022-03-30 14:00:00', NULL, 3);

-- 插入专辑数据
INSERT INTO `album` (`id`, `name`, `time`, `intro`, `bandid`) VALUES
(1, 'Rock Anthem', '2022-05-20', 'Our debut rock album with powerful anthems.', 1),
(2, 'Pop Sensation', '2022-08-10', 'A collection of catchy pop tunes that will make you dance.', 2),
(3, 'Jazz Exploration', '2022-11-15', 'An experimental jazz album pushing the boundaries of the genre.', 3);

-- 插入粉丝数据
INSERT INTO `fans` (`id`, `name`, `sex`, `age`, `job`, `degree`) VALUES
(1, 'Alice Johnson', 'Female', 25, 'Software Engineer', 'Bachelor'),
(2, 'Bob Smith', 'Male', 30, 'Marketing Specialist', 'Master'),
(3, 'Cathy Davis', 'Female', 22, 'Student', 'Bachelor'),
(4, 'David Wilson', 'Male', 28, 'Graphic Designer', 'Bachelor'),
(5, 'Eva Brown', 'Female', 35, 'Teacher', 'PhD');

-- 插入专辑喜欢关系数据
INSERT INTO `albumlikes` (`albumid`, `fanid`) VALUES
(1, 1),  -- Alice likes Rock Anthem
(1, 3),  -- Cathy likes Rock Anthem
(2, 2),  -- Bob likes Pop Sensation
(3, 4),  -- David likes Jazz Exploration
(3, 5);  -- Eva likes Jazz Exploration

-- 插入音乐会数据
INSERT INTO `concert` (`id`, `name`, `time`, `place`, `bandid`) VALUES
(1, 'Rock Fest', '2022-06-10', 'City Arena', 1),
(2, 'Pop Extravaganza', '2022-09-25', 'Outdoor Amphitheater', 2),
(3, 'Jazz Fusion Night', '2022-12-05', 'Grand Hall', 3);

-- 插入歌曲数据
INSERT INTO `songs` (`id`, `name`, `authorid`, `albumid`) VALUES
(1, 'Rock Anthem', 1, 1),   -- Rock Anthem by Rock Band
(2, 'Pop Song', 2, 2),      -- Pop Song by Pop Group
(3, 'Jazz Fusion', 3, 3),    -- Jazz Fusion by Jazz Ensemble
(4, 'Guitar Solo', 1, 1),    -- Guitar Solo by Rock Band
(5, 'Dance Beat', 2, 2),     -- Dance Beat by Pop Group
(6, 'Saxophone Serenade', 3, 3);  -- Saxophone Serenade by Jazz Ensemble

-- 插入乐队喜欢关系数据
INSERT INTO `bandlikes` (`fanid`, `bandid`) VALUES
(1, 1),  -- Alice likes Rock Band
(2, 2),  -- Bob likes Pop Group
(3, 3),  -- Cathy likes Jazz Ensemble
(4, 1),  -- David likes Rock Band
(5, 2);  -- Eva likes Pop Group

-- 插入更多歌曲数据
INSERT INTO `songs` (`id`, `name`, `authorid`, `albumid`) VALUES
(7, 'Electric Guitar Riff', 1, 1),
(8, 'Dreamy Pop Ballad', 2, 2),
(9, 'Smooth Jazz Groove', 3, 3),
(10, 'Bass Solo', 1, 1),
(11, 'Upbeat Dance Track', 2, 2),
(12, 'Trumpet Ensemble', 3, 3);

-- 插入歌曲喜欢关系数据
INSERT INTO `songlikes` (`songid`, `fanid`) VALUES
(1, 1),   -- Alice likes Rock Anthem
(2, 2),   -- Bob likes Pop Song
(3, 3),   -- Cathy likes Jazz Fusion
(4, 4),   -- David likes Guitar Solo
(5, 5),   -- Eva likes Dance Beat
(6, 1);   -- Alice likes Saxophone Serenade

-- 插入更多音乐会数据
INSERT INTO `concert` (`id`, `name`, `time`, `place`, `bandid`) VALUES
(4, 'Acoustic Night', '2023-02-15', 'Small Theater', 1),
(5, 'Electronic Beats Festival', '2023-05-20', 'Outdoor Stadium', 2),
(6, 'Latin Jazz Fusion Evening', '2023-08-10', 'City Park', 3);

-- 插入专辑评价数据
INSERT INTO `evaluation` (`albumid`, `fanid`, `score`, `evaluation`) VALUES
(1, 1, 5, 'Fantastic album!'),
(1, 2, 4, 'Great songs, but could use more variety'),
(2, 3, 5, 'Absolutely love every track!'),
(2, 4, 3, 'Some songs are good, but others are not my style'),
(3, 5, 4, 'Innovative jazz fusion, enjoyed the experimentation'),
(3, 1, 5, 'A masterpiece of musical creativity');

-- 插入歌曲演唱者关系数据
INSERT INTO `vocals` (`songid`, `bandid`) VALUES
(1, 1),   -- Rock Anthem by Rock Band
(2, 2),   -- Pop Song by Pop Group
(3, 3),   -- Jazz Fusion by Jazz Ensemble
(4, 1),   -- Guitar Solo by Rock Band
(5, 2),   -- Dance Beat by Pop Group
(6, 3);   -- Saxophone Serenade by Jazz Ensemble

-- 插入乐队演唱其他乐队歌曲的关系数据
INSERT INTO `vocals` (`songid`, `bandid`) VALUES
(7, 2),   -- Electric Guitar Riff by Pop Group
(8, 1),   -- Dreamy Pop Ballad by Rock Band
(9, 3),   -- Smooth Jazz Groove by Jazz Ensemble
(10, 2),  -- Bass Solo by Pop Group
(11, 1),  -- Upbeat Dance Track by Rock Band
(12, 2);  -- Trumpet Ensemble by Pop Group
