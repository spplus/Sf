-- 函数 
-- 函数：func_get_repairName
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_repairName $$
CREATE FUNCTION func_get_repairName
(f_caid varchar(50)) RETURNS varchar(50)
BEGIN
CASE f_caid
    WHEN 1 THEN RETURN '维修';
    WHEN 2 THEN RETURN '安装';
    WHEN 3 THEN RETURN '咨询';
    WHEN 4 THEN RETURN '保养';
    WHEN 5 THEN RETURN '工程';
    WHEN 6 THEN RETURN '其他';
    ELSE RETURN '未知';
  END CASE;
  
END$$
DELIMITER $$

-- 函数：func_get_orderType
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_orderType $$
CREATE FUNCTION func_get_orderType
(f_origin varchar(50),f_createby varchar(50)) RETURNS int(11)
BEGIN
	declare mgr varchar(10) default 'MAINSERVER';
	declare rlst int default 0;
	
	if f_createby!=mgr
	then set rlst = 1;
	elseif f_createby = mgr && f_origin=1
	then set rlst = 2;
	elseif f_createby = mgr && f_origin=6
	then set rlst = 3;
	elseif f_createby = mgr && f_origin=8
	then set rlst = 4;
	end if;
  return rlst;
END$$
DELIMITER $$


-- 函数：func_get_level
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_level $$
CREATE FUNCTION func_get_level
(f_level varchar(50)) RETURNS int(11)
BEGIN
	declare rlst int default 0;
	if f_level=1
	then set rlst = 1;
	else set rlst = 2;
	end if;
  return rlst;
END$$
DELIMITER $$

-- 函数: func_get_serviceType
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_serviceType $$
CREATE FUNCTION func_get_serviceType
(f_level int) RETURNS int(11)
BEGIN
	declare rlst int default 0;
	if f_level=3
	then set rlst = 1;
	else set rlst = f_level;
	end if;
  return rlst;
END$$
DELIMITER $$

-- 函数： func_get_statusName
DELIMITER $$
DROP FUNCTION IF EXISTS func_get_statusName $$
CREATE FUNCTION func_get_statusName
(f_status int,f_invalid int) RETURNS int(11)
BEGIN
	declare rlst int default 0;
	if f_invalid=2
	then set rlst = 8;
	else set rlst = f_status;
	end if;
  return rlst;
END$$
DELIMITER $$



--1. crm_order 
delete from crm_order;
INSERT INTO `crm_order` (`id`, `number`, `appliance_category`, `appliance_brand`, `appliance_model`, `appliance_barcode`, `appliance_buy_time`,  `appliance_machine_code`, 
`create_time`,repair_time, `customer_name`, `customer_address`, `customer_mobile`, `customer_telephone`, `customer_lnglat`, `customer_feedback`, `malfunction_type`, 
`promise_time`, `promise_limit`, `remarks`, `site_id`, `site_name`, `employe_id`, `employe_name`, `messenger_id`, `messenger_name`, `origin`, `order_type`, 
`create_by`, `service_type`, `level`, `warranty_type`, `update_time`, `status`, `return_card`,
  `fitting_flag`, `whether_collection`, `canoper`, `return_card_time`,`end_time`,serve_cost,confirm_cost) 
SELECT a.`id`, `number`, `appliance_category`, `appliance_brand`, `appliance_model`, `appliance_barcode`, `appliance_buy_time`,  `appliance_inn_code`,
 a.`create_time`,a.`create_time`,`customer_name`, `customer_address`, `customer_mobile`, `customer_telephone`, `customer_lnglat`, `customer_feedback`, `malfunction_type`,
  `promise_time`, `promise_limit`, a.`remarks`, a.`site_id`, a.`site_name`, a.`employe_id`, a.`employe_name`, a.`messenger_id`, a.`messenger_name`, `source`, func_get_orderType(origin,a.create_by),
  a.`create_by`, func_get_repairName(repair_type), func_get_level(level), func_get_serviceType(service_type),  a.`update_time`,  func_get_statusName(a.status,invalid), `return_card`,
  `machine_code`, `whether_collection`, `canoper`, `return_card_time`,b.end_time,c.total_collection,c.paid_in_amount 
FROM `sf-erp-order-v1`.`crm_order` a
left join `sf-erp-order-v1`.crm_order_dispatch b on a.id=b.order_id and b.`status`=5
left join `sf-erp-order-v1`.crm_order_callback c on b.id=c.dispatch_id and b.`status`=5

-- 更新callback_result 和callback_time 字段 
update crm_order a set callback_result=(select result from `jojowonettest`.crm_order_callback b where b.order_id=a.id order by create_time desc limit 1) where status in(2,3,4,5);
update crm_order a set callback_time=(select create_time from `jojowonettest`.crm_order_callback b where b.order_id=a.id order by create_time desc limit 1) where status in(2,3,4,5);


-- 2.crm_order_settlement
delete from crm_order_settlement;
INSERT INTO `crm_order_settlement` (`id`, `order_id`, `dispatch_id`, `create_time`, `create_by`, `create_name`, `sum_money`, `remarks`,  `service_measures`, `cost_detail`, `profits`,site_id,settlement_time)
SELECT a.`id`, `order_id`, a.`dispatch_id`, a.`create_time`, a.`create_by`, a.`create_name`, `sum_money`, a.`remarks`,  `service_measures`, `cost_detail`, `profit`,b.site_id,date_format(a.create_time,'%Y%m%d') 
FROM `sf-erp-order-v1`.crm_order_settlement a
LEFT JOIN `sf-erp-order-v1`.crm_order b on a.order_id=b.id;

-- 3.crm_order_settlement_detail
delete from crm_order_settlement_detail;
INSERT INTO `crm_order_settlement_detail` (`id`, `settlement_id`, `order_id`, `create_time`,settlement_time, `employe_id`, `employe_name`, `sum_money`, `service_measures`, `cost_detail`,site_id) 
SELECT a.`id`, `settlement_id`, `order_id`,  a.`create_time`, date_format(a.create_time,'%Y%m%d') ,a.`employe_id`, a.`employe_name`, `sum_money`, `service_measures`, `cost_detail`,b.site_id
FROM `sf-erp-order-v1`.`crm_order_settlement_detail` a
LEFT JOIN `sf-erp-order-v1`.crm_order b on a.order_id=b.id;


-- 4.crm_site_settlement_template
delete from crm_site_settlement_template;
INSERT INTO `crm_site_settlement_template` (`id`, `site_id`, `status`, `category`, `service_measures`, `charge_name`, `charge_amount`, `create_time`, `create_by`, `update_time`) 
SELECT `id`, `site_id`, `status`, `category`, `service_measures`, `charge_name`, `charge_amount`, `create_time`, `create_by`, `update_time` 
FROM `sf-erp-order-v1`.`crm_site_settlement_template`;

-- 5.crm_order_callback
delete from crm_order_callback;
INSERT INTO `crm_order_callback` (`id`, `order_id`, `dispatch_id`, `service_attitude`, `create_time`, `create_by`, `create_name`, `safety_evaluation`, `result`, `remarks`, `multiple_dropin`) 
SELECT `id`, `order_id`, `dispatch_id`, `service_attitude`, `create_time`, `create_by`, `create_name`, `safety_evaluation`, `result`, `remarks`,  `multiple_repair`
FROM `sf-erp-order-v1`.`crm_order_callback` ;


-- 6.crm_order_dispatch
delete from crm_order_dispatch;
INSERT INTO `crm_order_dispatch` (`id`, `order_id`, `dispatch_time`, `status`, `end_time`, `drop_in_time`, `update_time`, `remarks`, `messenger_id`, `messenger_name`, `employe_id`, `employe_name`,  `site_id`,promise_flag) 
SELECT `id`, `order_id`, `dispatch_time`, `status`, `end_time`, `drop_in_time`, `update_time`, `remarks`, `messenger_id`, `messenger_name`, `employe_id`, `employe_name`,  `site_id`,
case status
when 1 then 0
when 3 then 0
when 6 then 0
else  1
end as promise_flag
FROM `sf-erp-order-v1`.`crm_order_dispatch` ;


-- 7.crm_order_feedback
delete from crm_order_feedback;
INSERT INTO `crm_order_feedback` (`id`, `order_id`, `dispatch_id`, `feedback_time`, `feedback_id`, `feedback_name`, `user_type`, `feedback`, `feedback_result`, `feedback_img`, `remarks`,site_id,feedback_type)
SELECT a.`id`, `order_id`, `dispatch_id`, `feedback_time`, `feedback_id`, `feedback_name`, `user_type`, `feedback`, `feedback_result`, `feedback_img`,  a.`remarks`,b.site_id,1
 FROM `sf-erp-order-v1`.`crm_order_feedback` a
 LEFT JOIN `sf-erp-order-v1`.crm_order b on a.order_id=b.id;
 
 
-- 8 .
delete from crm_order_dispatch_employe_rel;
INSERT INTO `crm_order_dispatch_employe_rel` (`order_id`, `dispatch_id`, `emp_id`, `emp_name`, `site_id`)
SELECT `order_id`, `dispatch_id`, `emp_id`, `emp_name`, `site_id` 
FROM `sf-erp-order-v1`.`crm_order_dispatch_employe_rel`; 
