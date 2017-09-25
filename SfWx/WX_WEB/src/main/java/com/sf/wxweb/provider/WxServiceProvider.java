package com.sf.wxweb.provider;

import org.springframework.cloud.netflix.feign.FeignClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;

import com.sf.sfcm.bean.UserInfo;


@FeignClient("wx_service")
public interface WxServiceProvider {

    @RequestMapping(method = RequestMethod.GET, value = "/add")
    Integer add(@RequestParam(value = "a") Integer a, @RequestParam(value = "b") Integer b);

   
    @RequestMapping(method = RequestMethod.GET, value = "/finduser")
    UserInfo findUserByUserName(@RequestParam(value = "username") String username);
}