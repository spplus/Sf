package com.sf.wxweb.provider;

import java.util.Map;

import org.springframework.cloud.netflix.feign.FeignClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

import com.sf.sfcm.bean.UserInfo;


@FeignClient("wx-service")
public interface WxServiceProvider {

    @RequestMapping(method = RequestMethod.GET, value = "/add")
    Integer add(@RequestParam(value = "a") Integer a, @RequestParam(value = "b") Integer b);

   
    @RequestMapping(method = RequestMethod.GET, value = "/finduser")
    UserInfo findUserByUserName(@RequestParam(value = "username") String username);
    
    @RequestMapping(value = "addappliance",method = RequestMethod.POST)
	public Map<String,Object> addAppliance(Map<String,Object> reqMap);
    
    @RequestMapping(value = "updateappliance",method = RequestMethod.POST)
	public Map<String,Object> updateAppliance(Map<String,Object> reqMap);
    
    @RequestMapping(value = "queryappliance",method = RequestMethod.GET)
	public Map<String,Object> queryAppliance(Map<String,Object> reqMap);
    
    @RequestMapping(value = "updatecustomer",method = RequestMethod.POST)
	public Map<String,Object> updateCustomer(Map<String,Object> reqMap);
    
    @RequestMapping(value = "addcustomer",method = RequestMethod.POST)
	public Map<String,Object> addCustomer(Map<String,Object> reqMap);
    
    @RequestMapping(value = "querycustomer",method = RequestMethod.GET)
	public Map<String,Object> queryCustomer(Map<String,Object> reqMap);
    
    @RequestMapping(value = "querymyappliance",method = RequestMethod.GET)
	public Map<String,Object> queryMyApplianceList(Map<String, Object> reqMap);
    
    @RequestMapping(value = "querycategorys",method = RequestMethod.GET)
	public Map<String,Object> queryCategorys();
    
    @RequestMapping(value = "querybrands",method = RequestMethod.GET)
	public Map<String,Object> queryBrands(Map<String,Object> reqMap);
    
}