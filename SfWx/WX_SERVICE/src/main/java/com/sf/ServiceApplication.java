package com.sf;

import org.mybatis.spring.boot.autoconfigure.MybatisAutoConfiguration;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.jdbc.DataSourceAutoConfiguration;
import org.springframework.boot.web.servlet.ServletComponentScan;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import org.springframework.context.annotation.ImportResource;

import com.sf.sfcm.logger.SFLogger;

@ServletComponentScan
@ImportResource("classpath:dbconfig/dbconfig.xml")  
// 这两个exclude 千万不能少，否则会出现 required a single bean, but 2 were found: 被这个问题，整整折磨了一天
@SpringBootApplication(exclude = {DataSourceAutoConfiguration.class,MybatisAutoConfiguration.class})
@EnableDiscoveryClient
public class ServiceApplication {

	public static void main(String[] args) {
		SFLogger.info("ServiceApplication 启动成功.");
		SpringApplication.run(ServiceApplication.class, args);
	}
}
