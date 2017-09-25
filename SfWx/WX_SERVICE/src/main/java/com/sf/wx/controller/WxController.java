package com.sf.wx.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.sf.sfcm.bean.UserInfo;
import com.sf.sfcm.logger.SFLogger;
import com.sf.wx.service.WxService;


@RestController
public class WxController {

	@Autowired
	private DiscoveryClient client;
	
	@Autowired
	WxService		wxService;
	
	@RequestMapping(value = "/finduser", method = RequestMethod.GET)
    public UserInfo finduser(@RequestParam String username) {

		SFLogger.debug("finduser:"+username);
		return wxService.findByUsername(username);
    }
	
	@RequestMapping(value = "/test", method = RequestMethod.GET)
	public void test(){
		SFLogger.debug("test transaction");
		try {
			wxService.insertTest(0);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
