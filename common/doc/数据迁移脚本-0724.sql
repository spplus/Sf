
-- 一 直接插入

-- 1. crm_ac_manager --> crm_non_serviceman
delete from crm_non_serviceman;
insert into crm_non_serviceman (id,user_id,name,img,site_id,mobile,hiredate,update_time,remarks,status,create_by,create_time)
select id,user_id,name,img,site_id,mobile,hiredate,update_time,remarks,status,create_by,create_time
from `sf-erp-order-v1`.crm_ac_manager ;

-- 2. crm_non_serviceman_role_rel
delete from crm_non_serviceman_role_rel;
insert into crm_non_serviceman_role_rel(id,serviceman_id,site_role_id)
select uuid(),id,2 from crm_non_serviceman;

-- 3. crm_barcode_bcm_rel --> crm_barcode_bcm_rel
delete from crm_barcode_bcm_rel;
INSERT INTO crm_barcode_bcm_rel (`id`, `site_id`, `category`, `brand`, `barcode`, `model`,status) 
SELECT `id`, `site_id`, `category`, `brand`, `barcode`, `model`, `status` 
FROM `sf-erp-order-v1`.crm_barcode_bcm_rel ;

-- 4. crm_brand --> crm_brand
delete from crm_brand;
INSERT INTO `crm_brand` (`id`, `name`, `img`, `vendor`, `del_flag`, `update_time`, `first_letter`, `sort`)
SELECT `id`, `name`, `img`, `vendor`, `del_flag`, `update_time`, `first_letter`, `sort` 
FROM `sf-erp-order-v1`.`crm_brand`;

-- 5.crm_category --> crm_category
delete from crm_category;
INSERT INTO `crm_category` (`id`, `name`, `img`, `del_flag`) 
SELECT `id`, `name`, `img`, `del_flag` 
FROM `sf-erp-order-v1`.`crm_category`;


-- 6. crm_employe --> crm_employe
delete from crm_employe;
INSERT INTO `crm_employe` (`id`, `user_id`, `name`, `img`, `mobile`, `province`, `city`, `area`, `address`, `brand`, `hiredate`, `category`, `site_id`, `update_time`, `remarks`, `status`, `create_by`, `create_time`, `read_time`) 
SELECT `id`, `user_id`, `name`, `img`, `mobile`, `province`, `city`, `area`, `address`, `brand`, `hiredate`, `category`, `site_id`, `update_time`, `remarks`, `status`, `create_by`, `create_time`, `read_time` 
FROM `sf-erp-order-v1`.`crm_employe` ;

-- 7.crm_employe_daily_sign --> crm_employe_daily_sign
delete from crm_employe_daily_sign;
INSERT INTO `crm_employe_daily_sign` (`id`, `date`, `sign_address`, `sign_time`,  `employe_id`, `employe_name`, `create_time`, `site_id`, `status`,sign_longitude,sign_latitude,out_time,sign_result) 
SELECT `id`, `date`, `signin_address`, `signin_time`, `employe_id`, `employe_name`, `create_time`, `site_id`, `status`,0,0,0,0
FROM `sf-erp-order-v1`.`crm_employe_daily_sign` ;

-- 8. crm_gps_record--> crm_gps_record
delete from crm_gps_record;
INSERT INTO `crm_gps_record` (`id`, `role_id`, `site_id`, `role_type`, `role_mobile`, `longitude`, `latitude`, `create_date`) 
SELECT `id`, `role_id`, `site_id`, `role_type`, `role_mobile`, `longitude`, `latitude`, `create_date` 
FROM `sf-erp-order-v1`.`crm_gps_record`;

-- 9. crm_malfunction --> crm_malfunction
delete from crm_malfunction;
INSERT INTO `crm_malfunction` (`id`, `category`, `type`, `description`, `solution`, `create_time`, `create_by`, `status`, `user_type`, `site_id`) 
SELECT `id`, `category`, `type`, `description`, `solution`, `create_time`, `create_by`, `status`, `user_type`, `site_id` 
FROM `sf-erp-order-v1`.`crm_malfunction` ;


-- 10. crm_messenger --> crm_non_serviceman

insert into crm_non_serviceman (id,user_id,name,img,site_id,mobile,hiredate,update_time,remarks,status,create_by,create_time)
select id,user_id,name,img,site_id,mobile,hiredate,update_time,remarks,status,create_by,create_time
from `sf-erp-order-v1`.crm_messenger ;


-- 11. crm_non_serviceman --> crm_non_serviceman_role_rel 
insert into crm_non_serviceman_role_rel(id,serviceman_id,site_role_id)
select uuid(),id,1 from crm_non_serviceman;

-- 12. crm_received_sms --> crm_received_sms
delete from crm_received_sms;
INSERT INTO `crm_received_sms` (`id`, `mobile`, `content`, `order_id`, `site_id`, `create_time`, `send_time`, `status`, `extno`)
SELECT `id`, `mobile`, `content`, `order_id`, `site_id`, `create_time`, `send_time`, `status`, `extno` FROM `sf-erp-order-v1`.`crm_received_sms` ;

-- 13. crm_sended_sms --> crm_sended_sms
delete from crm_sended_sms;
INSERT INTO .`crm_sended_sms` (`id`, `sendid`, `template_id`, `mobile`, `content`, `sign`, `order_id`, `type`, `create_time`, `send_time`, `receive_time`, `status`,`create_by`, `site_id`, `create_type`, `site_mobile`, `extno`) 
SELECT `id`, `sendid`, `template_id`, `mobile`, `content`, `sign`, `order_id`, `type`, `create_time`, `send_time`, `receive_time`, `status`, `create_by`, `site_id`, `create_type`, `site_mobile`, `extno` 
FROM `sf-erp-order-v1`.`crm_sended_sms` ;

-- 14. sys_sms_template --> sys_sms_template
delete from sys_sms_template;
INSERT INTO `sys_sms_template` (`id`, `number`, `name`, `content`, `create_time`, `status`, `create_by`, `create_type`, `tag`, `site_id`) 
SELECT `id`, `number`, `name`, `content`, `create_time`, `status`, `create_by`, `create_type`, `tag`, `site_id`
FROM `sf-erp-order-v1`.`sys_sms_template`;

-- 15.CRM_SITE --> CRM_SITE
delete from CRM_SITE;
INSERT INTO CRM_SITE( `id`, `user_id`, `number`, `name`, `license_number`, `license_img`, `contacts`, `corporator`, `email`, `province`, `city`, `area`, `address`, `lnglat`, `category`, `mobile`, `telephone`, `status`, `check_flag`, `remarks`, `create_by`, `create_time`, `update_time`, `area_manager_id`, `due_time`, `share_code`, `share_code_site_parent_id`, `level`, `sms_available_amount`) 
select `id`, `user_id`, `number`, `name`, `license_number`, `license_img`, `contacts`, `corporator`, `email`, `province`, `city`, `area`, `address`, `lnglat`, `category`, `mobile`, `telephone`, `status`, `check_flag`, `remarks`, `create_by`, `create_time`, `update_time`, `area_manager_id`, `due_time`, `share_code`, `share_code_site_parent_id`, `level`, `sms_available_amount`
from `sf-erp-order-v1`.`crm_site`;

-- 16. crm_site_brand_rel --> crm_site_brand_rel

delete  from crm_site_brand_rel;
INSERT INTO `crm_site_brand_rel` (`site_id`, `category_id`, `brand_id`) 
SELECT `site_id`, `category_id`, `brand_id` 
FROM `sf-erp-order-v1`.`crm_site_brand_rel`;

-- 更新category_id为该服务商自己的category id,从category表中根据site_id更新。
update crm_site_brand_rel a set category_id= (select id from crm_category b where b.site_id=a.site_id and b.`sort` =a.`category_id` );

-- 17. crm_site_common_setting --> crm_site_common_setting
delete from crm_site_common_setting;
INSERT INTO `crm_site_common_setting` (`id`, `site_id`, `type`, `set_value`) 
SELECT `id`, `site_id`, `type`, `set_value` 
FROM `sf-erp-order-v1`.`crm_site_common_setting` ;


-- 18.crm_site_order_origin --> crm_site_order_origin
delete from crm_site_order_origin;
INSERT INTO `crm_site_order_origin` (`id`, `site_id`, `name`, `create_time`) 
SELECT `id`, `site_id`, `name`, `create_time` 
FROM `sf-erp-order-v1`.`crm_site_order_origin`;

-- 19. crm_site_qrcode --> crm_site_qrcode
delete from crm_site_qrcode;
INSERT INTO `crm_site_qrcode` (`id`, `scene_id`, `ticket`, `type`, `site_id`, `status`, `create_time`, `check_time`) 
SELECT `id`, `scene_id`, `ticket`, `type`, `site_id`, `status`, `create_time`, `check_time` 
FROM `sf-erp-order-v1`.`crm_site_qrcode`;


-- 20. crm_site_tele_device --> crm_site_tele_device
delete from crm_site_tele_device;
INSERT INTO `crm_site_tele_device` (`id`, `site_id`, `serial_no`, `create_time`, `status`) 
SELECT `id`, `site_id`, `serial_no`, `create_time`, `status` 
FROM `sf-erp-order-v1`.`crm_site_tele_device` ;

-- 21. crm_site_vender_account --> crm_site_vender_account
delete from crm_site_vender_account;
INSERT INTO `crm_site_vender_account` (`id`, `site_id`, `vender_id`, `login_name`, `password`)
SELECT `id`, `site_id`, `vender_id`, `login_name`, `password`, `status` 
FROM `sf-erp-order-v1`.`crm_site_vender_account` ;

-- 22.crm_vender_info --> crm_vender_info
delete from crm_vender_info;
INSERT INTO `crm_vender_info` (`id`, `name`, `url`, `status`)
SELECT `id`, `name`, `url`, `status` 
FROM `sf-erp-order-v1`.`crm_vender_info`;

-- 更新 name link 字段
update crm_site_vender_account a set name =(select b.name from crm_vender_info b where b.id=a.vender_id);
update crm_site_vender_account a set link =(select url from crm_vender_info b where b.id=a.vender_id);

-- 23. s_city --> s_city
DELETE FROM s_city;
INSERT INTO `s_city` (`CityID`, `ProvinceId`, `CityName`, `AreaCode`, `DateCreated`, `DateUpdated`)
SELECT `CityID`, `ProvinceId`, `CityName`, `AreaCode`, `DateCreated`, `DateUpdated` 
FROM `sf-erp-order-v1`.`s_city` ;

-- 24. s_district
delete from s_district;
INSERT INTO `s_district` (`DistrictID`, `CityId`, `DistrictName`, `DateCreated`, `DateUpdated`)
SELECT `DistrictID`, `CityId`, `DistrictName`, `DateCreated`, `DateUpdated` 
FROM `sf-erp-order-v1`.`s_district`;

-- 25.s_province
delete from s_province;
INSERT INTO `s_province` (`ProvinceID`, `ProvinceName`, `DateCreated`, `DateUpdated`)
SELECT `ProvinceID`, `ProvinceName`, `DateCreated`, `DateUpdated` 
FROM `sf-erp-order-v1`.`s_province`;

-- 26. sys_dict
delete from sys_dict;
INSERT INTO `sys_dict` (`id`, `label`, `value`, `type`, `description`, `sort`, `create_by`, `create_date`, `update_by`, `update_date`, `remarks`, `status`, `sys`)
SELECT `id`, `label`, `value`, `type`, `description`, `sort`, `create_by`, `create_date`, `update_by`, `update_date`, `remarks`, `status`, `sys` 
FROM `sf-erp-order-v1`.`sys_dict` ;

-- 27 sys_menu
delete from sys_menu;
INSERT INTO `sys_menu` (`id`, `parent_id`, `parent_ids`, `name`, `href`, `target`, `icon`, `sort`, `is_show`, `is_activiti`, `permission`, `create_by`, `create_date`, `update_by`, `update_date`, `remarks`, `status`) 
SELECT `id`, `parent_id`, `parent_ids`, `name`, `href`, `target`, `icon`, `sort`, `is_show`, `is_activiti`, `permission`, `create_by`, `create_date`, `update_by`, `update_date`, `remarks`, `status` 
FROM `sf-erp-order-v1`.`sys_menu` ;

-- 28.sys_role
delete from sys_role;
INSERT INTO `sys_role` (`id`, `name`, `data_scope`, `create_by`, `create_date`, `update_by`, `update_date`, `remarks`, `status`)
SELECT `id`, `name`, `data_scope`, `create_by`, `create_date`, `update_by`, `update_date`, `remarks`, `status` 
FROM `sf-erp-order-v1`.`sys_role`;


-- 29. sys_role_menu
delete from sys_role_menu
INSERT INTO `sys_role_menu` (`role_id`, `menu_id`) 
SELECT `role_id`, `menu_id` FROM `sf-erp-order-v1`.`sys_role_menu` ;


-- 30.sys_user
delete from sys_user;
INSERT INTO `sys_user` (`id`, `login_name`, `password`, `user_type`, `mobile`, `email`, `create_by`, `create_date`, `create_type`, `remarks`, `registration_id`, `push_id`, `app_type`, `status`, `update_time`, `reset_pwd_token`, `openid`) 
SELECT `id`, `login_name`, `password`, `user_type`, `mobile`, `email`, `create_by`, `create_date`, `create_type`, `remarks`, `fix_channel_id`, `fix_user_id`, `app_type`, `status`, `update_time`, `reset_pwd_token`, `openid` 
FROM `sf-erp-order-v1`.`sys_user` ;

-- 31.product_order --> crm_goods_platform_order
# 函数: func_get_imgUrl
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_rand $$
CREATE FUNCTION func_get_rand() RETURNS varchar(10)
BEGIN
	DECLARE randv int default 0;
	DECLARE rslt varchar(10) default '0';
	select FLOOR(1 + (RAND() * 99)) into randv ;
	
	if randv >9 
	then set rslt=randv;
	else set rslt = CONCAT('0',randv);
	end if;
	
   RETURN rslt;
END$$
DELIMITER $$

delete from crm_goods_platform_order;
insert into crm_goods_platform_order(`id`, `number`, `good_id`, `good_number`, `good_name`, `good_icon`, `good_brand`, `good_model`, `good_category`, 
`customer_name`, `customer_contact`, `customer_address`, `purchase_num`, `good_amount`, `placing_order_by`, `siteself_order_id`, `placing_order_time`, `payer`, `payment_time`, `pay_status`, `status`, `payment_type`, 
`trade_no`, `logistics_name`, `logistics_no`, `site_id`, `creator`, `supplier_id`, `confirm_time`, `sendgood_time`, `finish_time`)

select a.id,CONCAT('T',date_format(a.pay_time, '%Y%m%d%H%i%S%f'),func_get_rand()),2,'SF012','来电弹屏','','思方','sf2.0','来电弹屏',
a.site_name,a.mobile,concat(a.province,a.city,a.area,a.address),b.quantity,a.amount,a.user_id,'',a.created_at,c.user_id,a.pay_time,a.`status`,4,a.pay_way,
a.trade_no,'','',a.site_id,a.site_name,999,a.pay_time,'',a.pay_time
from `sf-erp-order-v1`.product_order a
left join `sf-erp-order-v1`.product_order_line b on a.id=b.product_order_id
left join `sf-erp-order-v1`.crm_site c on a.site_id=c.id;


-- 32.sms_order_payment --> crm_goods_platform_order

insert into crm_goods_platform_order(`id`, `number`, `good_id`, `good_number`, `good_name`, `good_icon`, `good_brand`, `good_model`, `good_category`, 
`customer_name`, `customer_contact`, `customer_address`, `purchase_num`, `good_amount`, `placing_order_by`, `siteself_order_id`, `placing_order_time`, `payer`, `payment_time`, `pay_status`, `status`, `payment_type`, 
`trade_no`, `logistics_name`, `logistics_no`, `site_id`, `creator`, `supplier_id`, `confirm_time`, `sendgood_time`, `finish_time`)

select a.id,CONCAT('S',date_format(a.pay_time, '%Y%m%d%H%i%S%f'),func_get_rand()),1,'SF011','短信','','思方','sf2.0','短信',
b.name,b.mobile,'',a.buy_number,a.amount,'','',a.pay_time,b.user_id,a.pay_time,a.`status`,4,a.pay_way,
a.trade_no,'','',a.site_id,b.name,999,a.pay_time,'',a.pay_time
from `sf-erp-order-v1`.sms_order_payment a
left join `sf-erp-order-v1`.crm_site b on a.site_id=b.id;



-- 2017-07-25 补充 ---------------------------------------------------------

-- 更新签到表签到类型
update crm_employe_daily_sign set sign_type=1 where sign_time is not null;
update crm_employe_daily_sign set sign_type=2 where sign_type is null;

-- 

# 函数: func_get_smsNum
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_smsNum $$
CREATE FUNCTION func_get_smsNum
(f_content varchar(500),f_sign varchar(200)) RETURNS int(11)
BEGIN
	DECLARE str varchar(700) default '';
	DECLARE rlst int default 0;
	declare len int default 0;
	
	set str = concat(f_content,"【",f_sign,"】");
	set len = CHAR_LENGTH(str);
	if len<=0
	then set rlst=0;
	elseif len<=70
	then	set rlst=1;
	elseif len>70 
	then	set rlst = (len+64)/65;
	end if;
	
   RETURN rlst;
END$$
DELIMITER $$

-- 更新短信数量
update crm_sended_sms set sms_num=func_get_smsNum(content,sign);



