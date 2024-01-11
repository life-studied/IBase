/*
 Navicat Premium Data Transfer

 Source Server         : localBase
 Source Server Type    : MySQL
 Source Server Version : 80100 (8.1.0)
 Source Host           : localhost:3306
 Source Schema         : bandbase

 Target Server Type    : MySQL
 Target Server Version : 80100 (8.1.0)
 File Encoding         : 65001

 Date: 11/12/2023 18:21:09
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
INSERT INTO `account` VALUES ('111111', '111111', 'Alice Johnson', 'Fan');
INSERT INTO `account` VALUES ('123456', 'admin', 'yunyin', 'Admin');
INSERT INTO `account` VALUES ('222222', '222222', 'Mike Anderson', 'Member');

-- ----------------------------
-- Table structure for album
-- ----------------------------
DROP TABLE IF EXISTS `album`;
CREATE TABLE `album`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `time` date NOT NULL,
  `intro` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of album
-- ----------------------------
INSERT INTO `album` VALUES (1, 'Rock Anthem', '2022-05-20', 'Our debut rock album with powerful anthems.', 1);
INSERT INTO `album` VALUES (2, 'Pop Sensation', '2022-08-10', 'A collection of catchy pop tunes that will make you dance.', 2);
INSERT INTO `album` VALUES (3, 'Jazz Exploration', '2022-11-15', 'An experimental jazz album pushing the boundaries of the genre.', 3);

-- ----------------------------
-- Table structure for albumlikes
-- ----------------------------
DROP TABLE IF EXISTS `albumlikes`;
CREATE TABLE `albumlikes`  (
  `albumid` int NOT NULL,
  `fanid` int NOT NULL,
  PRIMARY KEY (`albumid`, `fanid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of albumlikes
-- ----------------------------
INSERT INTO `albumlikes` VALUES (1, 1);
INSERT INTO `albumlikes` VALUES (1, 3);
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
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of attendconcert
-- ----------------------------
INSERT INTO `attendconcert` VALUES (1, 1);
INSERT INTO `attendconcert` VALUES (2, 1);
INSERT INTO `attendconcert` VALUES (3, 1);
INSERT INTO `attendconcert` VALUES (5, 1);
INSERT INTO `attendconcert` VALUES (1, 3);

-- ----------------------------
-- Table structure for band
-- ----------------------------
DROP TABLE IF EXISTS `band`;
CREATE TABLE `band`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `createtime` date NOT NULL,
  `intro` text CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL,
  `leader` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of band
-- ----------------------------
INSERT INTO `band` VALUES (1, 'Rock Band', '2022-01-01', 'We are a rock band from the city.', 'John Doe');
INSERT INTO `band` VALUES (2, 'Pop Group', '2022-02-15', 'Catchy tunes and vibrant performances.', 'Jane Smith');
INSERT INTO `band` VALUES (3, 'Jazz Ensemble', '2022-03-20', 'Exploring the depths of jazz music.', 'Robert Johnson');

-- ----------------------------
-- Table structure for bandlikes
-- ----------------------------
DROP TABLE IF EXISTS `bandlikes`;
CREATE TABLE `bandlikes`  (
  `fanid` int NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`fanid`, `bandid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of bandlikes
-- ----------------------------
INSERT INTO `bandlikes` VALUES (1, 1);
INSERT INTO `bandlikes` VALUES (2, 2);
INSERT INTO `bandlikes` VALUES (3, 3);
INSERT INTO `bandlikes` VALUES (4, 1);
INSERT INTO `bandlikes` VALUES (5, 2);

-- ----------------------------
-- Table structure for concert
-- ----------------------------
DROP TABLE IF EXISTS `concert`;
CREATE TABLE `concert`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `time` date NOT NULL,
  `place` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

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
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of evaluation
-- ----------------------------
INSERT INTO `evaluation` VALUES (1, 1, 5, 'Fantastic album!');
INSERT INTO `evaluation` VALUES (1, 2, 4, 'Great songs, but could use more variety');
INSERT INTO `evaluation` VALUES (2, 3, 5, 'Absolutely love every track!');
INSERT INTO `evaluation` VALUES (2, 4, 3, 'Some songs are good, but others are not my style');
INSERT INTO `evaluation` VALUES (3, 1, 5, 'A masterpiece of musical creativity');
INSERT INTO `evaluation` VALUES (3, 5, 4, 'Innovative jazz fusion, enjoyed the experimentation');

-- ----------------------------
-- Table structure for fans
-- ----------------------------
DROP TABLE IF EXISTS `fans`;
CREATE TABLE `fans`  (
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `sex` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `age` int NOT NULL,
  `job` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `degree` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of fans
-- ----------------------------
INSERT INTO `fans` VALUES (1, 'Alice Johnson', 'Female', 27, 'Software Engineer', 'Bachelor');
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
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of member
-- ----------------------------
INSERT INTO `member` VALUES (1, 'Mike Anderson', 'Male', 'Guitarist', '2022-01-10 08:00:00', NULL, 1);
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
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of songlikes
-- ----------------------------
INSERT INTO `songlikes` VALUES (1, 1);
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
  `id` int NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `authorid` int NOT NULL,
  `albumid` int NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

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

-- ----------------------------
-- Table structure for vocals
-- ----------------------------
DROP TABLE IF EXISTS `vocals`;
CREATE TABLE `vocals`  (
  `songid` int NOT NULL,
  `bandid` int NOT NULL,
  PRIMARY KEY (`songid`, `bandid`) USING BTREE,
  INDEX `fk_vovals_band_1`(`bandid` ASC) USING BTREE,
  CONSTRAINT `fk_vovals_band_1` FOREIGN KEY (`bandid`) REFERENCES `band` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `fk_vovals_songs_1` FOREIGN KEY (`songid`) REFERENCES `songs` (`id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of vocals
-- ----------------------------
INSERT INTO `vocals` VALUES (1, 1);
INSERT INTO `vocals` VALUES (4, 1);
INSERT INTO `vocals` VALUES (8, 1);
INSERT INTO `vocals` VALUES (11, 1);
INSERT INTO `vocals` VALUES (2, 2);
INSERT INTO `vocals` VALUES (5, 2);
INSERT INTO `vocals` VALUES (7, 2);
INSERT INTO `vocals` VALUES (10, 2);
INSERT INTO `vocals` VALUES (12, 2);
INSERT INTO `vocals` VALUES (3, 3);
INSERT INTO `vocals` VALUES (6, 3);
INSERT INTO `vocals` VALUES (9, 3);

SET FOREIGN_KEY_CHECKS = 1;
