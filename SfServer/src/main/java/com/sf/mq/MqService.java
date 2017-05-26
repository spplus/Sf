package com.sf.mq;

import com.alibaba.rocketmq.client.exception.MQClientException;
import com.sf.log.SpLogger;
import com.sf.util.Config;

import java.util.Properties;

/**
 * MQ初始化.
 *
 * @author yuanls
 */
public class MqService {

	public MqService(){
		init();
	}
	
    /**
     * 初始化方法，spring容器启动时调用此方法.
     */
    public void init() {
       SpLogger.info("初始化RocketMq");

        try {
           BusConsumer.subscribe();
        } catch (MQClientException e) {
        	SpLogger.error("SFSERVER订阅服务启动失败", e);
        }
    }
}
