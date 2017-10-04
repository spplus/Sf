package com.sf.wxweb.controller;

import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

import javax.servlet.http.HttpServletRequest;

import net.sf.json.JSONObject;

import org.apache.shiro.SecurityUtils;
import org.apache.shiro.authc.IncorrectCredentialsException;
import org.apache.shiro.authc.UnknownAccountException;
import org.apache.shiro.authc.UsernamePasswordToken;
import org.apache.shiro.subject.Subject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import com.sf.sfcm.bean.AjaxResponseBean;
import com.sf.sfcm.logger.SFLogger;
import com.sf.sfcm.util.ParamUtil;
import com.sf.wxweb.provider.WxServiceProvider;

@Controller
public class WxController {
	
	@Autowired
	WxServiceProvider wxService;
	
    @RequestMapping({"/","/index"})
    public String index(){
        return "index";
    }
    
    @RequestMapping({"/","/test"})
    public String test(){
    	
        return "test";
    }
    
    @ResponseBody
    @RequestMapping(value="/adduser",method=RequestMethod.POST)
    public AjaxResponseBean addUser(@RequestBody JSONObject req){
    	
    	//SFLogger.info("addUser:"+req.toString());
    	
    	Map<String,Object> reqMap = new HashMap<String, Object>();
    	String uuid = UUID.randomUUID().toString();
    	reqMap.put("id", uuid);
    	reqMap.put("number", uuid);
    	reqMap.put("open_id", uuid);
    	
    	Map<String,Object> resMap = wxService.addCustomer(reqMap);
    	
    	return ParamUtil.getResultBean(resMap);
    	
    }
    
    

    @RequestMapping(value = "/login")
    public String loginCheck(HttpServletRequest request, String username,String password,Map<String,Object> map) throws Exception{
        
        // 登录失败从request中获取shiro处理的异常信息。
        // shiroLoginFailure:就是shiro异常类的全类名.
       
        if(username != null || password !=null){
        	try{
	        	Subject subject = SecurityUtils.getSubject();
	            UsernamePasswordToken token = new UsernamePasswordToken();
	            token.setUsername(username);
	            token.setPassword(password.toCharArray());
	            subject.login(token);
	            
	            if(subject.isAuthenticated()){
	            
	            	map.put("user",username);
	            	return "index";
	            }
        	}catch(Exception e){

        		 String exception = e.getClass().getName();

        	     String msg = "hello";
        	     if (exception != null) {
        	         if (UnknownAccountException.class.getName().equals(exception)) {

        	        	 msg = "UnknownAccountException -- > 账号不存在：";
        	         } else if (IncorrectCredentialsException.class.getName().equals(exception)) {

        	        	 msg = "IncorrectCredentialsException -- > 密码不正确：";
        	         } else if ("kaptchaValidateFailed".equals(exception)) {

        	         	msg = "kaptchaValidateFailed -- > 验证码错误";
        	         } else {

        	        	 msg = "UnknownAccountException -- > 账号不存在：";
        	         }
        	      }
        	     

        	    map.put("msg", msg);
        		
        	}
        }
        
        // 此方法不处理登录成功,由shiro进行处理
        return "/login";
    }

    @RequestMapping("/403")
    public String unauthorizedRole(){
        return "403";
    }

}