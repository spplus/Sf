package com.sf.goods.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import com.sf.goods.service.GoodsService;
import com.sf.sfcm.logger.SFLogger;


@RestController
public class GoodsController {

	@Autowired
	private DiscoveryClient client;
	
	@Autowired
	GoodsService	goodsService;
	

	@RequestMapping(value = "/test", method = RequestMethod.GET)
	public void test(){
		SFLogger.debug("test transaction");
		try {
			goodsService.insertTest(0);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
