package com.sf.mq;

import com.alibaba.rocketmq.client.consumer.DefaultMQPushConsumer;
import com.alibaba.rocketmq.client.consumer.listener.ConsumeConcurrentlyContext;
import com.alibaba.rocketmq.client.consumer.listener.ConsumeConcurrentlyStatus;
import com.alibaba.rocketmq.client.consumer.listener.MessageListenerConcurrently;
import com.alibaba.rocketmq.common.message.MessageConst;
import com.alibaba.rocketmq.common.message.MessageExt;
import com.sf.log.SpLogger;
import com.sf.server.ClientMgr;
import com.sf.util.ConstDef;

import net.sf.json.JSONObject;

import java.io.UnsupportedEncodingException;
import java.util.*;

/**
 * MQ消息消费处理类.
 *
 * @author yuanls
 */
public class MqMessageListener implements MessageListenerConcurrently{

    private DefaultMQPushConsumer consumer = null;

    public MqMessageListener(DefaultMQPushConsumer cm) {
        consumer = cm;

    }

    /**
     * 消费消息回调.
     */
    public ConsumeConcurrentlyStatus consumeMessage(List<MessageExt> msgs, ConsumeConcurrentlyContext context) {

        // 消息内容
        MessageExt msg = msgs.get(0);
        SpLogger.info("进入接受参数tag:" + msg.getTags());
        long offset = msgs.get(0).getQueueOffset();
        String maxOffset = msgs.get(0).getProperty(MessageConst.PROPERTY_MAX_OFFSET);
        long diff = Long.parseLong(maxOffset) - offset;
        if (diff > 100000) {
            SpLogger.warn("消费堆积超过100000，跳过该条:" + msg.toString());
            return ConsumeConcurrentlyStatus.CONSUME_SUCCESS;
        }

        // 判断消息完整性
        if (msg.getTopic() == null || msg.getTags() == null) {

            SpLogger.warn("消费消息失败，主题或频道内容为空:" + msg.toString());
            return null;
        }

        MessageExt breakmsg = msgs.get(0);
        byte[] btparam = breakmsg.getBody();

        // 获取消息内容
        String parms = null;
        ;
        JSONObject jb = new JSONObject();

        try {

            parms = new String(btparam, "UTF-8");
            jb = JSONObject.fromObject(parms);

        } catch (UnsupportedEncodingException e) {
            SpLogger.warn("消息消息失败：解析消息内容出错。TOPIC：" + msg.getTopic() + "TAG:" + msg.getTags(), e);
            return ConsumeConcurrentlyStatus.RECONSUME_LATER;
        }

        SpLogger.debug("接收MQ消息,Topic:" + breakmsg.getTopic() + ",Tag:" + breakmsg.getTags() + ",msgid:" + breakmsg.getMsgId() + ",keys:" + breakmsg.getKeys() + ",消息内容："
                + jb.toString());
        
        // 主题
        String strTopic = msg.getTopic();

        // 频道
        String strTag = msg.getTags();

        // 频道
        
        
        if (strTopic.equals(ConstDef.TOPIC_NOTICE)) {

            if (strTag.equals(ConstDef.TOPIC_NOTICE_TAG)) {
            	
            	String siteId = jb.getString("siteId");
            	ClientMgr.instance().sendData(siteId, ConstDef.SF_CMD_MESSAGE,"");           	
            } 
        }
         
        return ConsumeConcurrentlyStatus.CONSUME_SUCCESS;

    }

 
}
