-- 1. crm_site_fitting
delete from crm_site_fitting;
INSERT INTO `crm_site_fitting` (`id`, `code`, `name`, `brand`, `suit_category`, `version`, `supplier`, `remarks`, `status`, `site_id`, `create_time`, `create_by`, `keyword`, 
`warning`, `number`, `audited_sum`,  `cjnum`, `site_price`, `employe_price`, `customer_price`,refund_old_flag,unit,unit_type
,total)
SELECT `id`, `code`, `name`, `brand`, `category`, `version`, `supplier`, `remarks`, `status`, `site_id`, `create_time`, `create_by`, `keyword`,
 `warning`, `number`, `audited_sum`, `cjnum`, `site_price`, `employe_price`, `customer_price`,0,'个' ,'i',
 ifnull(warning,0)+ifnull(number,0)+ifnull(cjnum,0)
FROM `jojowonettest`.`crm_site_fitting` ;


-- 2.crm_site_fitting_apply
delete from crm_site_fitting_apply;
INSERT INTO `crm_site_fitting_apply` (`id`, `number`, `type`, `site_id`, 
`employe_id`, employe_name,`employe_feedback`, `confirmor`, `confirmor_id`, `auditor`,
 `auditor_id`, `auditor_feedback`, `order_id`, `fitting_version`, `status`, `fitting_id`, 
`fitting_code`, `fitting_name`, `fitting_img`, `fitting_apply_num`, 
`create_time`, `audit_time`, `end_time`, `creator`, fitting_audit_num,suit_category) 

SELECT a.`id`, a.`number`, `type`, a.`site_id`, `employe_id`,b.name, `employe_feedback`, 
`confirmor`, `confirmor_id`, `auditor`, `auditor_id`, `confirmor_feedback`, `order_id`, 
`fitting_version`, case a.`status` when 0 then 0 when 1 then 4 when 3 then 7 when 4 then 6 when 5 then 1 when 6 then 2 end as status, 
`fitting_id`, `fitting_code`, `fitting_name`, `fitting_img`,
 `fitting_apply_num`, a.`create_time`, `check_time`, `confirm_time`, `creator`,fitting_apply_num,c.category
 FROM `jojowonettest`.`crm_site_fitting_apply` a
 left join `jojowonettest`.crm_employe b on a.employe_id=b.id
 left join `jojowonettest`.crm_site_fitting c on c.id=a.fitting_id;
 
 -- 3. crm_site_fitting_keep
delete from crm_site_fitting_keep;
INSERT INTO `crm_site_fitting_keep` (`id`, `number`, `type`, `fitting_id`, `fitting_code`, `fitting_name`, `amount`, `price`, `employe_price`, `customer_price`, `remarks`, `create_time`, `employe_name`, `messenger_name`, `site_id`, `create_by`) 
SELECT `id`, `number`, `type`, `fitting_id`, `fitting_code`, `fitting_name`, `amount`, `price`, `employe_price`, `customer_price`, `remarks`, `create_time`, `employe_name`, `messenger_name`, `site_id`, `create_by` 
FROM `jojowonettest`.`crm_site_fitting_keep` ;

-- 4. crm_site_apply_use_record
delete from crm_site_apply_use_record;
INSERT INTO crm_site_apply_use_record (`id`, `fitting_id`, `site_id`, `order_id`, `type`, `description`, `used_num`, `employe_id`, 
`user_name`, `create_by`, `status`, `confirmor`, `confirmor_id`,  `used_time`, `check_time`, `old_fitting_flag`, `collection_flag`,
fitting_code,fitting_name,fitting_version,category,brand) 
SELECT a.`id`, `fitting_id`, a.`site_id`, `order_id`, `type`, `description`, `used_num`, a.`employe_id`, 
`user_name`, a.`create_by`, a.`status`, `confirmor`, `confirmor_id`,  `used_time`, `check_time`, `old_fitting_flag`, `paid_flag`,
b.code,b.name,b.version,c.appliance_category,c.appliance_brand 
FROM `jojowonettest`.`crm_site_apply_use_record` a
left join `jojowonettest`.crm_site_fitting b on a.fitting_id=b.id 
left join `jojowonettest`.crm_order c on a.order_id=c.id;
 
-- 5.crm_employe_fitting
delete from  crm_employe_fitting;
INSERT INTO `crm_employe_fitting` (`id`, `fitting_id`, `employe_id`, `status`, `site_id`, `create_time`, `create_by`, `warning`, `number`, `total`, `cjnum`) 
SELECT `id`, `fitting_id`, `employe_id`, `status`, `site_id`, `create_time`, `create_by`, `warning`, `number`, `total`, `cjnum` 
FROM `jojowonettest`.`crm_employe_fitting`;
 