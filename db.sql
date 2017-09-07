CREATE DATABASE IF NOT EXISTS `nordelectro` CHARACTER SET utf8 COLLATE utf8_unicode_ci;
USE `nordelectro`;

CREATE TABLE IF NOT EXISTS `keywords` (
`kid` int(10) unsigned NOT NULL,
  `name` varchar(40) CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

CREATE TABLE IF NOT EXISTS `manufacturers` (
`mid` int(10) unsigned NOT NULL,
  `name` varchar(20) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `multiplicy` (
  `pid` int(10) unsigned NOT NULL,
  `main_unit` varchar(20) NOT NULL,
  `main_mult` int(10) unsigned DEFAULT NULL,
  `sec_unit` varchar(20) DEFAULT NULL,
  `sec_mult` int(10) unsigned DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `params` (
  `kid` int(20) unsigned NOT NULL,
  `pid` int(20) unsigned NOT NULL,
  `param1` varchar(40) NOT NULL,
  `param2` varchar(40) DEFAULT NULL,
  `param3` varchar(40) DEFAULT NULL,
  `param4` varchar(40) DEFAULT NULL,
  `param5` varchar(40) DEFAULT NULL,
  `param6` varchar(40) DEFAULT NULL,
  `param7` varchar(40) DEFAULT NULL,
`id` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

CREATE TABLE IF NOT EXISTS `patterns` (
  `kid` int(10) NOT NULL,
  `val1` varchar(40) DEFAULT NULL,
  `val2` varchar(40) DEFAULT NULL,
  `val3` varchar(40) DEFAULT NULL,
  `val4` varchar(40) DEFAULT NULL,
  `val5` varchar(40) DEFAULT NULL,
  `val6` varchar(40) DEFAULT NULL,
  `val7` varchar(40) DEFAULT NULL,
`dummy` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `products` (
`pid` int(10) NOT NULL,
  `art` varchar(30) NOT NULL,
  `description` varchar(255) NOT NULL,
  `mid` int(10) NOT NULL,
  `main_unit` varchar(20) NOT NULL,
  `main_mult` int(11) DEFAULT NULL,
  `sec_unit` varchar(20) DEFAULT NULL,
  `sec_mult` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=COMPACT;

CREATE TABLE IF NOT EXISTS `store` (
  `pid` int(10) NOT NULL,
  `smid` int(10) NOT NULL,
  `count` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `store_date` (
  `smid` int(10) NOT NULL,
  `date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE IF NOT EXISTS `store_manufacturer` (
`smid` int(10) NOT NULL,
  `storePlace` varchar(40) NOT NULL,
  `mid` int(10) NOT NULL,
  `path` varchar(255) DEFAULT NULL,
  `regexp` varchar(255) DEFAULT NULL,
  `lastPath` varchar(255) DEFAULT NULL,
  `startRow` int(10) NOT NULL,
  `articleCol` int(10) NOT NULL,
  `itemCountCol` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `keywords`
 ADD PRIMARY KEY (`kid`), ADD UNIQUE KEY `kid` (`kid`), ADD UNIQUE KEY `name` (`name`);

ALTER TABLE `manufacturers`
 ADD PRIMARY KEY (`mid`), ADD UNIQUE KEY `NAME` (`name`);

ALTER TABLE `multiplicy`
 ADD PRIMARY KEY (`pid`);

ALTER TABLE `params`
 ADD PRIMARY KEY (`id`);

ALTER TABLE `patterns`
 ADD PRIMARY KEY (`dummy`), ADD UNIQUE KEY `kid` (`kid`);

ALTER TABLE `products`
 ADD PRIMARY KEY (`pid`), ADD UNIQUE KEY `pid` (`pid`), ADD KEY `mid` (`mid`);

ALTER TABLE `store_date`
 ADD UNIQUE KEY `uniq` (`smid`);

ALTER TABLE `store_manufacturer`
 ADD PRIMARY KEY (`smid`);

ALTER TABLE `keywords`
MODIFY `kid` int(10) unsigned NOT NULL AUTO_INCREMENT;

ALTER TABLE `manufacturers`
MODIFY `mid` int(10) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;

ALTER TABLE `params`
MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;

ALTER TABLE `patterns`
MODIFY `dummy` int(10) NOT NULL AUTO_INCREMENT;

ALTER TABLE `products`
MODIFY `pid` int(10) NOT NULL AUTO_INCREMENT;

ALTER TABLE `store_manufacturer`
MODIFY `smid` int(10) NOT NULL AUTO_INCREMENT;