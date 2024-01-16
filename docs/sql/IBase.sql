/*
 Navicat Premium Data Transfer

 Source Server         : localBase
 Source Server Type    : MySQL
 Source Server Version : 80100 (8.1.0)
 Source Host           : localhost:3306
 Source Schema         : myband2

 Target Server Type    : MySQL
 Target Server Version : 80100 (8.1.0)
 File Encoding         : 65001

 Date: 16/01/2024 10:08:39
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for account
-- ----------------------------
DROP TABLE IF EXISTS `account`;
CREATE TABLE `account`  (
  `account` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `username` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `permission` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  PRIMARY KEY (`account`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of account
-- ----------------------------
INSERT INTO `account` VALUES ('111111', '111111', 'ffasdfasd', 'Fan');
INSERT INTO `account` VALUES ('123456', 'admin', 'yunyin', 'Admin');
INSERT INTO `account` VALUES ('222222', '222222', 'Mike Anderson', 'Member');

-- ----------------------------
-- Table structure for album
-- ----------------------------
DROP TABLE IF EXISTS `album`;
CREATE TABLE `album`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `time` date NOT NULL,
  `intro` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 11 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of album
-- ----------------------------
INSERT INTO `album` VALUES (1, 'Rock Anthem', '2022-05-20', 'Our debut rock album with powerful anthems.', 1);
INSERT INTO `album` VALUES (2, 'Pop Sensation', '2022-08-10', 'A collection of catchy pop tunes that will make you dance.', 2);
INSERT INTO `album` VALUES (3, 'Jazz Exploration', '2022-11-15', 'An experimental jazz album pushing the boundaries of the genre.', 3);
INSERT INTO `album` VALUES (7, 'sdfasdfasf', '2024-01-16', 'asdfsadf', 1);
INSERT INTO `album` VALUES (9, '111', '2024-01-16', '222', 1);
INSERT INTO `album` VALUES (10, '222', '2024-01-16', '333', 1);

-- ----------------------------
-- Table structure for albumlikes
-- ----------------------------
DROP TABLE IF EXISTS `albumlikes`;
CREATE TABLE `albumlikes`  (
  `albumid` int NOT NULL,
  `fanid` int NOT NULL,
  PRIMARY KEY (`albumid`, `fanid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of albumlikes
-- ----------------------------
INSERT INTO `albumlikes` VALUES (1, 1);
INSERT INTO `albumlikes` VALUES (1, 3);
INSERT INTO `albumlikes` VALUES (2, 1);
INSERT INTO `albumlikes` VALUES (2, 2);
INSERT INTO `albumlikes` VALUES (3, 4);
INSERT INTO `albumlikes` VALUES (3, 5);

-- ----------------------------
-- Table structure for attendconcert
-- ----------------------------
DROP TABLE IF EXISTS `attendconcert`;
CREATE TABLE `attendconcert`  (
  `concertid` int NOT NULL,
  `fanid` int NOT NULL,
  PRIMARY KEY (`concertid`, `fanid`) USING BTREE,
  INDEX `fk_attendconcert_fans_1`(`fanid` ASC) USING BTREE,
  CONSTRAINT `fk_attendconcert_Concert_1` FOREIGN KEY (`concertid`) REFERENCES `concert` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `fk_attendconcert_fans_1` FOREIGN KEY (`fanid`) REFERENCES `fans` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of attendconcert
-- ----------------------------
INSERT INTO `attendconcert` VALUES (1, 1);
INSERT INTO `attendconcert` VALUES (2, 1);
INSERT INTO `attendconcert` VALUES (3, 1);
INSERT INTO `attendconcert` VALUES (4, 1);
INSERT INTO `attendconcert` VALUES (5, 1);
INSERT INTO `attendconcert` VALUES (1, 3);

-- ----------------------------
-- Table structure for band
-- ----------------------------
DROP TABLE IF EXISTS `band`;
CREATE TABLE `band`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `createtime` date NOT NULL,
  `intro` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL,
  `leader` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `membership` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 4 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of band
-- ----------------------------
INSERT INTO `band` VALUES (1, 'Rock Band', '2022-01-01', 'We are a rock band from the city.', 'John Doe', 1);
INSERT INTO `band` VALUES (2, 'Pop Group', '2022-02-15', 'Catchy tunes and vibrant performances.', 'Jane Smith', 2);
INSERT INTO `band` VALUES (3, 'Jazz Ensemble', '2022-03-20', 'Exploring the depths of jazz music.', 'Robert Johnson', 2);

-- ----------------------------
-- Table structure for bandlikes
-- ----------------------------
DROP TABLE IF EXISTS `bandlikes`;
CREATE TABLE `bandlikes`  (
  `fanid` int NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`fanid`, `bandid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of bandlikes
-- ----------------------------
INSERT INTO `bandlikes` VALUES (1, 1);
INSERT INTO `bandlikes` VALUES (1, 2);
INSERT INTO `bandlikes` VALUES (2, 2);
INSERT INTO `bandlikes` VALUES (3, 3);
INSERT INTO `bandlikes` VALUES (4, 1);
INSERT INTO `bandlikes` VALUES (5, 2);

-- ----------------------------
-- Table structure for bestalbum
-- ----------------------------
DROP TABLE IF EXISTS `bestalbum`;
CREATE TABLE `bestalbum`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `time` date NOT NULL,
  `intro` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `bandid` int NOT NULL,
  `score` float NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 21 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of bestalbum
-- ----------------------------
INSERT INTO `bestalbum` VALUES (14, 'Jazz Exploration', '2022-11-15', 'An experimental jazz album pushing the boundaries of the genre.', 3, 4.5);
INSERT INTO `bestalbum` VALUES (15, 'Pop Sensation', '2022-08-10', 'A collection of catchy pop tunes that will make you dance.', 2, 4);
INSERT INTO `bestalbum` VALUES (16, 'Rock Anthem', '2022-05-20', 'Our debut rock album with powerful anthems.', 1, 2);
INSERT INTO `bestalbum` VALUES (17, '123123', '2024-01-14', '3213213', 1, NULL);
INSERT INTO `bestalbum` VALUES (18, 'fdsafasdf', '2024-01-14', 'asdfasdfsadf', 1, NULL);
INSERT INTO `bestalbum` VALUES (19, 'xxx', '2024-01-15', 'yyy', 1, NULL);

-- ----------------------------
-- Table structure for concert
-- ----------------------------
DROP TABLE IF EXISTS `concert`;
CREATE TABLE `concert`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `time` date NOT NULL,
  `place` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 10 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of concert
-- ----------------------------
INSERT INTO `concert` VALUES (1, 'Rock Fest', '2022-06-10', 'City Arena', 1);
INSERT INTO `concert` VALUES (2, 'Pop Extravaganza', '2022-09-25', 'Outdoor Amphitheater', 2);
INSERT INTO `concert` VALUES (3, 'Jazz Fusion Night', '2022-12-05', 'Grand Hall', 3);
INSERT INTO `concert` VALUES (4, 'Acoustic Night', '2023-02-15', 'Small Theater', 1);
INSERT INTO `concert` VALUES (5, 'Electronic Beats Festival', '2023-05-20', 'Outdoor Stadium', 2);
INSERT INTO `concert` VALUES (6, 'Latin Jazz Fusion Evening', '2023-08-10', 'City Park', 3);

-- ----------------------------
-- Table structure for evaluation
-- ----------------------------
DROP TABLE IF EXISTS `evaluation`;
CREATE TABLE `evaluation`  (
  `albumid` int NOT NULL,
  `fanid` int NOT NULL,
  `score` int NOT NULL,
  `evaluation` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  PRIMARY KEY (`albumid`, `fanid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of evaluation
-- ----------------------------
INSERT INTO `evaluation` VALUES (1, 1, 1, 'Fantastic album!');
INSERT INTO `evaluation` VALUES (1, 2, 4, 'Great songs, but could use more variety');
INSERT INTO `evaluation` VALUES (1, 3, 1, 'Innovative jazz fusion, enjoyed the experimentation');
INSERT INTO `evaluation` VALUES (2, 3, 5, 'Absolutely love every track!');
INSERT INTO `evaluation` VALUES (2, 4, 3, 'Some songs are good, but others are not my style');
INSERT INTO `evaluation` VALUES (3, 1, 5, 'A masterpiece of musical creativity');
INSERT INTO `evaluation` VALUES (3, 5, 4, 'Innovative jazz fusion, enjoyed the experimentation');

-- ----------------------------
-- Table structure for fans
-- ----------------------------
DROP TABLE IF EXISTS `fans`;
CREATE TABLE `fans`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `sex` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `age` int NOT NULL,
  `job` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `degree` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 6 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of fans
-- ----------------------------
INSERT INTO `fans` VALUES (1, 'ffasdfasd', 'Female', 27, 'Software Engineer', 'Bachelor');
INSERT INTO `fans` VALUES (2, 'Bob Smith', 'Male', 30, 'Marketing Specialist', 'Master');
INSERT INTO `fans` VALUES (3, 'Cathy Davis', 'Female', 22, 'Student', 'Bachelor');
INSERT INTO `fans` VALUES (4, 'David Wilson', 'Male', 28, 'Graphic Designer', 'Bachelor');
INSERT INTO `fans` VALUES (5, 'Eva Brown', 'Female', 35, 'Teacher', 'PhD');

-- ----------------------------
-- Table structure for member
-- ----------------------------
DROP TABLE IF EXISTS `member`;
CREATE TABLE `member`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `sex` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `duty` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `jointime` datetime NOT NULL,
  `leavetime` datetime NULL DEFAULT NULL,
  `bandid` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of member
-- ----------------------------
INSERT INTO `member` VALUES (1, 'Mike Anderson', 'Female', 'Guitarist', '2024-01-16 10:02:38', NULL, 1);
INSERT INTO `member` VALUES (2, 'Lisa Johnson', 'Female', 'Vocalist', '2022-02-20 09:30:00', NULL, 2);
INSERT INTO `member` VALUES (3, 'Chris Davis', 'Male', 'Drummer', '2022-03-25 10:45:00', NULL, 3);
INSERT INTO `member` VALUES (4, 'Emily White', 'Female', 'Bassist', '2022-01-15 08:30:00', '2023-05-01 12:00:00', 1);
INSERT INTO `member` VALUES (5, 'Mark Taylor', 'Male', 'Pianist', '2022-02-28 11:15:00', '2023-04-20 10:30:00', 2);
INSERT INTO `member` VALUES (6, 'Sophia Martinez', 'Female', 'Saxophonist', '2022-03-30 14:00:00', NULL, 3);

-- ----------------------------
-- Table structure for songlikes
-- ----------------------------
DROP TABLE IF EXISTS `songlikes`;
CREATE TABLE `songlikes`  (
  `songid` int NOT NULL,
  `fanid` int NOT NULL,
  PRIMARY KEY (`songid`, `fanid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of songlikes
-- ----------------------------
INSERT INTO `songlikes` VALUES (1, 1);
INSERT INTO `songlikes` VALUES (2, 1);
INSERT INTO `songlikes` VALUES (2, 2);
INSERT INTO `songlikes` VALUES (3, 3);
INSERT INTO `songlikes` VALUES (4, 4);
INSERT INTO `songlikes` VALUES (5, 5);
INSERT INTO `songlikes` VALUES (6, 1);

-- ----------------------------
-- Table structure for songs
-- ----------------------------
DROP TABLE IF EXISTS `songs`;
CREATE TABLE `songs`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `authorid` int NOT NULL,
  `albumid` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 17 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of songs
-- ----------------------------
INSERT INTO `songs` VALUES (1, 'Rock Anthem', 1, 1);
INSERT INTO `songs` VALUES (2, 'Pop Song', 2, 2);
INSERT INTO `songs` VALUES (3, 'Jazz Fusion', 3, 3);
INSERT INTO `songs` VALUES (4, 'Guitar Solo', 1, 1);
INSERT INTO `songs` VALUES (5, 'Dance Beat', 2, 2);
INSERT INTO `songs` VALUES (6, 'Saxophone Serenade', 3, 3);
INSERT INTO `songs` VALUES (7, 'Electric Guitar Riff', 1, 1);
INSERT INTO `songs` VALUES (8, 'Dreamy Pop Ballad', 2, 2);
INSERT INTO `songs` VALUES (9, 'Smooth Jazz Groove', 3, 3);
INSERT INTO `songs` VALUES (10, 'Bass Solo', 1, 1);
INSERT INTO `songs` VALUES (11, 'Upbeat Dance Track', 2, 2);
INSERT INTO `songs` VALUES (12, 'Trumpet Ensemble', 3, 3);
INSERT INTO `songs` VALUES (16, '333', 1, 9);

-- ----------------------------
-- View structure for v_band1evaluation
-- ----------------------------
DROP VIEW IF EXISTS `v_band1evaluation`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_band1evaluation` AS select `evaluation`.`albumid` AS `albumid`,`evaluation`.`fanid` AS `fanid`,`evaluation`.`score` AS `score`,`evaluation`.`evaluation` AS `evaluation` from `evaluation` where `evaluation`.`albumid` in (select `album`.`id` from `album` where (`album`.`bandid` = 1));

-- ----------------------------
-- View structure for v_band1fans
-- ----------------------------
DROP VIEW IF EXISTS `v_band1fans`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_band1fans` AS select `fans`.`id` AS `id`,`fans`.`name` AS `name`,`fans`.`sex` AS `sex`,`fans`.`age` AS `age`,`fans`.`job` AS `job`,`fans`.`degree` AS `degree` from `fans` where `fans`.`id` in (select `bandlikes`.`fanid` from `bandlikes` where (`bandlikes`.`bandid` = 1));

-- ----------------------------
-- View structure for v_concert
-- ----------------------------
DROP VIEW IF EXISTS `v_concert`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_concert` AS select `attendconcert`.`fanid` AS `fanid`,count(0) AS `attendfrequency` from `attendconcert` group by `attendconcert`.`fanid`;

-- ----------------------------
-- View structure for v_fansage
-- ----------------------------
DROP VIEW IF EXISTS `v_fansage`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_fansage` AS select (select count(0) from `fans` where (`fans`.`age` < 18)) AS `teenager`,(select count(0) from `fans` where ((`fans`.`age` >= 18) and (`fans`.`age` <= 60))) AS `middleage`,(select count(0) from `fans` where (`fans`.`age` > 60)) AS `aged`;

-- ----------------------------
-- View structure for v_fanseducation
-- ----------------------------
DROP VIEW IF EXISTS `v_fanseducation`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_fanseducation` AS select (select count(0) from `fans` where (`fans`.`degree` = 'Bachelor')) AS `本科`,(select count(0) from `fans` where (`fans`.`degree` = 'Master')) AS `硕士`,(select count(0) from `fans` where (`fans`.`degree` = 'PhD')) AS `博士`,(select count(0) from `fans` where ((`fans`.`degree` <> 'Bachelor') and (`fans`.`degree` <> 'Master') and (`fans`.`degree` <> 'PhD'))) AS `其他`;

-- ----------------------------
-- View structure for v_fansex
-- ----------------------------
DROP VIEW IF EXISTS `v_fansex`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_fansex` AS select (select count(0) from `fans` where (`fans`.`sex` = 'Female')) AS `Female`,(select count(0) from `fans` where (`fans`.`sex` = 'Male')) AS `Male`;

-- ----------------------------
-- View structure for v_fansnumber
-- ----------------------------
DROP VIEW IF EXISTS `v_fansnumber`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_fansnumber` AS select `bandlikes`.`bandid` AS `bandid`,count(`bandlikes`.`fanid`) AS `count(fanid)` from `bandlikes` group by `bandlikes`.`bandid`;

-- ----------------------------
-- View structure for v_job
-- ----------------------------
DROP VIEW IF EXISTS `v_job`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_job` AS select (select count(0) from `fans` where (`fans`.`job` = 'Student')) AS `学生`,(select count(0) from `fans` where (`fans`.`job` <> 'Student')) AS `社会人员`;

-- ----------------------------
-- View structure for v_popualrsongs
-- ----------------------------
DROP VIEW IF EXISTS `v_popualrsongs`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `v_popualrsongs` AS select `songlikes`.`songid` AS `songid`,count(`songlikes`.`fanid`) AS `likespersons` from `songlikes` group by `songlikes`.`songid`;

-- ----------------------------
-- Triggers structure for table evaluation
-- ----------------------------
DROP TRIGGER IF EXISTS `update_bestalbum_trigger_after_insert`;
delimiter ;;
CREATE TRIGGER `update_bestalbum_trigger_after_insert` AFTER INSERT ON `evaluation` FOR EACH ROW BEGIN
    -- 删除最佳专辑表的所有内容
    DELETE FROM bestalbum;

    -- 插入新的数据到最佳专辑表
    INSERT INTO bestalbum(name,time,intro,bandid,score)
    SELECT album.name, album.time, album.intro, album.bandid, 
           (SELECT AVG(score) FROM evaluation WHERE evaluation.albumid = album.id) avg_sco
    FROM album
    ORDER BY avg_sco DESC
    LIMIT 10;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table evaluation
-- ----------------------------
DROP TRIGGER IF EXISTS `update_bestalbum_trigger_after_update`;
delimiter ;;
CREATE TRIGGER `update_bestalbum_trigger_after_update` AFTER UPDATE ON `evaluation` FOR EACH ROW BEGIN
    -- 删除最佳专辑表的所有内容
    DELETE FROM bestalbum;

    -- 插入新的数据到最佳专辑表
    INSERT INTO bestalbum(name,time,intro,bandid,score)
    SELECT album.name, album.time, album.intro, album.bandid, 
           (SELECT AVG(score) FROM evaluation WHERE evaluation.albumid = album.id) avg_sco
    FROM album
    ORDER BY avg_sco DESC
    LIMIT 10;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
