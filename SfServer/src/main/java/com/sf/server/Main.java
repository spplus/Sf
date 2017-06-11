package com.sf.server;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.UUID;

import com.alibaba.rocketmq.client.exception.MQClientException;
import com.alibaba.rocketmq.client.producer.DefaultMQProducer;
import com.alibaba.rocketmq.client.producer.SendResult;
import com.alibaba.rocketmq.common.message.Message;
import com.sf.log.SpLogger;

import net.sf.json.JSONObject;

public class Main {
		
	private static String nameserver = "120.210.205.24:9876";
	private static DefaultMQProducer producer = null;
	

	public static void main(String[] args) {  
		//MinaServer server = new MinaServer();
		
		producer = new DefaultMQProducer("MessageProducer");
		producer.setSendMsgTimeout(10000);

		producer.setNamesrvAddr(nameserver);

		SimpleDateFormat sf = new SimpleDateFormat("yyyyMMddHHmmss");
		Date now = new Date();
		String sendtime = sf.format(now);
		
		try {
			producer.start();
			String key = UUID.randomUUID().toString();
			JSONObject js = new JSONObject();
			js.put("category", "0");
			js.put("siteId", "ff808081586cc3d701586ce8bef50003");
			js.put("sendtime", sendtime);
			Message msg = new Message("topic_audio", "tag_default_new_order_audio", key, (js.toString()).getBytes("UTF-8"));
			
			SendResult sendResult = producer.send(msg);
			SpLogger.info("发送同步消息, key:" + key + "发送结果：" + sendResult);
			
		} catch (MQClientException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch(InterruptedException e){
			e.printStackTrace();
		}catch(Exception e){
			e.printStackTrace();
		}
	}
	
}
