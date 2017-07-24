# 函数：func_get_categoryName
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_categoryName $$
CREATE FUNCTION func_get_categoryName
(f_caid varchar(50)) RETURNS varchar(50)
BEGIN
	CASE f_caid
    WHEN 1 THEN RETURN '空调';
    WHEN 2 THEN RETURN '冰箱';
    WHEN 3 THEN RETURN '热水器';
 
    WHEN 5 THEN RETURN '油烟机';
    WHEN 6 THEN RETURN '洗衣机';

    WHEN 9 THEN RETURN '小家电';

    ELSE RETURN '未知';
  END CASE;
  
END$$
DELIMITER $$

# 函数: func_get_imgUrl
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_imgUrl $$
CREATE FUNCTION func_get_imgUrl
(f_caid varchar(50)) RETURNS varchar(50)
BEGIN
	DECLARE imgUrl varchar(50) default '';
	select img into imgUrl from crm_category where id=f_caid;
   RETURN imgUrl;
END$$
DELIMITER $$


# 函数：func_split_TotalLength
DELIMITER $$
DROP FUNCTION IF EXISTS func_split_TotalLength $$
CREATE FUNCTION func_split_TotalLength
(f_string varchar(1000),f_delimiter varchar(5)) RETURNS int(11)
BEGIN
	return 1+(length(f_string) - length(replace(f_string,f_delimiter,'')));
END$$
DELIMITER $$

# 函数：func_split 
DELIMITER $$
DROP function IF EXISTS func_split $$
CREATE FUNCTION func_split 
(f_string varchar(1000),f_delimiter varchar(5),f_order int) RETURNS varchar(255) CHARSET utf8 
BEGIN 
    # 拆分传入的字符串，返回拆分后的新字符串 
        declare result varchar(255) default ''; 
        set result = reverse(substring_index(reverse(substring_index(f_string,f_delimiter,f_order)),f_delimiter,1));
        return result;
END$$
DELIMITER $$;

# 存储过程：splitString 
DELIMITER $$ 
DROP PROCEDURE IF EXISTS `splitString` $$ 
CREATE PROCEDURE `splitString` 
(IN f_string varchar(1000),IN idstr varchar(50), IN f_delimiter varchar(5)) 
BEGIN 
# 拆分结果 
declare cnt int default 0; 
declare i int default 0; 
set cnt = func_split_TotalLength(f_string,f_delimiter); 
DROP TABLE IF EXISTS `tmp_split`; 
create temporary table `tmp_split` (`status` varchar(128) not null,`ids` varchar(50) ) DEFAULT CHARSET=utf8; 
while i < cnt 
do 
    set i = i + 1; 
    insert into tmp_split(`status`,`ids`) values (func_split(f_string,f_delimiter,i),idstr); 
end while; 
END$$ 
DELIMITER $$; 

# 插入分隔数据
DELIMITER $$ 
DROP PROCEDURE IF EXISTS `valinsert` $$ 
CREATE PROCEDURE `valinsert` () 
BEGIN
    declare siteid varchar(50) default ''; 
  	 declare tmpName varchar(100) default '' ;
    declare tmpCategory varchar(500) default '' ;
-- 定义游标
    declare cur1  CURSOR FOR SELECT category FROM crm_site ;
    DECLARE cur2     CURSOR FOR SELECT id FROM crm_site;
    declare CONTINUE HANDLER FOR SQLSTATE '02000' SET tmpName = null;
-- 开游标 
    OPEN cur1 ;
    OPEN cur2;
    FETCH cur1 INTO tmpCategory;
    FETCH cur2 INTO siteid;
    -- 清空带插入的表
    -- TRUNCATE  shop_goods_image;
    WHILE ( tmpName is not null) DO
        -- 调取分隔字段的存储过程splitString
        call splitString(tmpCategory,siteid,",");
        INSERT INTO crm_category (name,img,site_id,sort,create_time) SELECT func_get_categoryName(status),func_get_imgUrl(status),ids,status,now() from tmp_split; 
        FETCH cur1 INTO tmpCategory;
        FETCH cur2 INTO siteid;
    END WHILE;
    CLOSE cur1;
    CLOSE cur2;
select * from crm_category; 
END$$ 
DELIMITER $$; 

call valinsert();

select * from tmp_split;

