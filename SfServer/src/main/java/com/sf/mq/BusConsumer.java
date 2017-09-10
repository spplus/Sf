package com.sf.mq;

import com.alibaba.rocketmq.client.consumer.DefaultMQPushConsumer;
import com.alibaba.rocketmq.client.exception.MQBrokerException;
import com.alibaba.rocketmq.client.exception.MQClientException;
import com.alibaba.rocketmq.common.consumer.ConsumeFromWhere;
import com.alibaba.rocketmq.common.message.MessageExt;
import com.alibaba.rocketmq.common.protocol.heartbeat.MessageModel;
import com.alibaba.rocketmq.remoting.exception.RemotingException;


import com.sf.cnst.ConstDef;
import com.sf.cnst.SFTopic;
import com.sf.log.SpLogger;
import com.sf.util.Config;

import java.util.Properties;

/**
 * 广播模式的消息订阅和处理类.
 *
 */
public class BusConsumer {

    private static DefaultMQPushConsumer consumer = null;

    /**
     * 得到DefaultMQPushConsumer对象，如果为空进行初始化.
     */
    public static DefaultMQPushConsumer getConsumer() throws MQClientException {
        if (consumer == null) {
            Properties prop = Config.getInstance().getProperties();
            // 一个应用创建一个Consumer，由应用来维护此对象，可以设置为全局对象或者单例
            // 注意：ConsumerGroupName需要由应用来保证唯一
            consumer = new DefaultMQPushConsumer(prop.getProperty("consumergroupnameCust"));
            consumer.setConsumeThreadMin(Integer.parseInt(prop.getProperty("consumethreadmin")));
            consumer.setConsumeThreadMax(Integer.parseInt(prop.getProperty("consumethreadmax")));
            consumer.setConsumeMessageBatchMaxSize(Integer.parseInt(prop.getProperty("consumemessagebatchmaxsize")));
            consumer.setPullBatchSize(Integer.parseInt(prop.getProperty("pullbatchsize")));
            consumer.setNamesrvAddr(prop.getProperty("nameserver"));
        }
        return consumer;
    }

    /**
     * 订阅方法，使用方式给用户感觉是消息从RocketMQ服务器推到了应用客户端.
     */
    public static void subscribe() throws MQClientException {

        consumer = getConsumer();
        consumer.subscribe(SFTopic.TOPIC_AUDIO, "*");
        consumer.subscribe("CustNotification", "*");
        //广播
        consumer.setMessageModel(MessageModel.BROADCASTING);
        consumer.setConsumeFromWhere(ConsumeFromWhere.CONSUME_FROM_LAST_OFFSET);
        consumer.registerMessageListener(new MqMessageListener(consumer));


        // Consumer对象在使用之前必须要调用start初始化，初始化一次即可
        consumer.start();
        SpLogger.info("SF_SERVER 订阅服务已启动");
    }

    /**
     * Consumer消费失败的消息可以选择重新发回到服务器端，并延时消费.
     * 会首先尝试将消息发回到消息之前存储的主机，此时只传送消息Offset，消息体不传送，不会占用网络带宽
     * 如果发送失败，会自动重试发往其他主机，此时消息体也会传送
     * 重传回去的消息只会被当前Consumer Group消费。
     */
    public static void sendMessageBack(MessageExt msg, int delayLevel)
            throws RemotingException, MQBrokerException, InterruptedException, MQClientException {

        consumer = getConsumer();
        consumer.sendMessageBack(msg, delayLevel);
    }

    /**
     * 取消订阅，从当前订阅组内注销，消息会被订阅组内其他订阅者订阅.
     */
    public static void unsubscribe(String topic) throws MQClientException {
        consumer = getConsumer();
        consumer.unsubscribe(topic);
    }

    public static void main(String[] args) throws InterruptedException, MQClientException {
        subscribe();

    }
}
