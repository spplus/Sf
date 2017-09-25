package com.sf.wxweb;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.cloud.client.loadbalancer.LoadBalanced;
import org.springframework.cloud.netflix.feign.EnableFeignClients;
import org.springframework.context.annotation.Bean;
import org.springframework.web.client.RestTemplate;

import com.sf.sfcm.logger.SFLogger;

@EnableFeignClients
@EnableDiscoveryClient
@SpringBootApplication
public class WebApplication {

	@Bean
	@LoadBalanced
	RestTemplate restTemplate() {
		return new RestTemplate();
	}

	public static void main(String[] args) {
		SFLogger.info("WxApplication 启动成功.");
		SpringApplication.run(WebApplication.class, args);
	}
}
