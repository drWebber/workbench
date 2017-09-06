-- phpMyAdmin SQL Dump
-- version 4.2.11
-- http://www.phpmyadmin.net
--
-- Хост: 127.0.0.1
-- Время создания: Сен 06 2017 г., 19:53
-- Версия сервера: 5.6.21
-- Версия PHP: 5.6.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `nordelectro`
--

-- --------------------------------------------------------

--
-- Структура таблицы `keywords`
--

CREATE TABLE IF NOT EXISTS `keywords` (
`kid` int(10) unsigned NOT NULL,
  `name` varchar(40) CHARACTER SET utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

-- --------------------------------------------------------

--
-- Структура таблицы `manufacturers`
--

CREATE TABLE IF NOT EXISTS `manufacturers` (
`mid` int(10) unsigned NOT NULL,
  `name` varchar(20) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `manufacturers`
--

INSERT INTO `manufacturers` (`mid`, `name`) VALUES
(2, 'дкс'),
(1, 'тдм');

-- --------------------------------------------------------

--
-- Структура таблицы `multiplicy`
--

CREATE TABLE IF NOT EXISTS `multiplicy` (
  `pid` int(10) unsigned NOT NULL,
  `main_unit` varchar(20) NOT NULL,
  `main_mult` int(10) unsigned DEFAULT NULL,
  `sec_unit` varchar(20) DEFAULT NULL,
  `sec_mult` int(10) unsigned DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `params`
--

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

-- --------------------------------------------------------

--
-- Структура таблицы `patterns`
--

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

-- --------------------------------------------------------

--
-- Структура таблицы `products`
--

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

-- --------------------------------------------------------

--
-- Структура таблицы `store`
--

CREATE TABLE IF NOT EXISTS `store` (
  `pid` int(10) NOT NULL,
  `smid` int(10) NOT NULL,
  `count` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `store_date`
--

CREATE TABLE IF NOT EXISTS `store_date` (
  `smid` int(10) NOT NULL,
  `date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Структура таблицы `store_manufacturer`
--

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

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `keywords`
--
ALTER TABLE `keywords`
 ADD PRIMARY KEY (`kid`), ADD UNIQUE KEY `kid` (`kid`), ADD UNIQUE KEY `name` (`name`);

--
-- Индексы таблицы `manufacturers`
--
ALTER TABLE `manufacturers`
 ADD PRIMARY KEY (`mid`), ADD UNIQUE KEY `NAME` (`name`);

--
-- Индексы таблицы `multiplicy`
--
ALTER TABLE `multiplicy`
 ADD PRIMARY KEY (`pid`);

--
-- Индексы таблицы `params`
--
ALTER TABLE `params`
 ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `patterns`
--
ALTER TABLE `patterns`
 ADD PRIMARY KEY (`dummy`), ADD UNIQUE KEY `kid` (`kid`);

--
-- Индексы таблицы `products`
--
ALTER TABLE `products`
 ADD PRIMARY KEY (`pid`), ADD UNIQUE KEY `pid` (`pid`), ADD KEY `mid` (`mid`);

--
-- Индексы таблицы `store_date`
--
ALTER TABLE `store_date`
 ADD UNIQUE KEY `uniq` (`smid`);

--
-- Индексы таблицы `store_manufacturer`
--
ALTER TABLE `store_manufacturer`
 ADD PRIMARY KEY (`smid`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `keywords`
--
ALTER TABLE `keywords`
MODIFY `kid` int(10) unsigned NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `manufacturers`
--
ALTER TABLE `manufacturers`
MODIFY `mid` int(10) unsigned NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT для таблицы `params`
--
ALTER TABLE `params`
MODIFY `id` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `patterns`
--
ALTER TABLE `patterns`
MODIFY `dummy` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `products`
--
ALTER TABLE `products`
MODIFY `pid` int(10) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `store_manufacturer`
--
ALTER TABLE `store_manufacturer`
MODIFY `smid` int(10) NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
