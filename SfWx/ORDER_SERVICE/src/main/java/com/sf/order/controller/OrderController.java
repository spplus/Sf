package com.sf.order.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.sf.order.service.OrderService;
import com.sf.sfcm.bean.UserInfo;
import com.sf.sfcm.logger.SFLogger;


@RestController
public class OrderController {

	@Autowired
	private DiscoveryClient client;
	
	@Autowired
	OrderService		wxService;
	
	
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
