package com.sf.server;

import java.net.InetSocketAddress;
import java.nio.charset.Charset;
import java.util.logging.Logger;

import org.apache.mina.core.service.IoAcceptor;
import org.apache.mina.core.session.IdleStatus;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;

public class MinaServer {  
    // 服务器监听端口  
	private static final int PORT = 6666;  
/** 
*  
*/  
	public MinaServer() {  
		// TODO Auto-generated constructor stub  
	}  

/** 
* @param args 
*/  
public static void main(String[] args) {  
	// 服务器端的主要对象  
	IoAcceptor acceptor = new NioSocketAcceptor();  
	
	// 设置Filter链   
	acceptor.getFilterChain().addLast("logger", new LoggingFilter());  
	
	acceptor.getFilterChain().addLast("codec", new ProtocolCodecFilter(new SpProtocalCodecFactory(Charset.forName("GBK"))));  
    acceptor.getSessionConfig().setReadBufferSize(1024);  
    acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10);  

	
	
	// 设置消息处理类（创建、关闭Session，可读可写等等，继承自接口IoHandler）  
	acceptor.setHandler(new ServerHandler() );  
	// 设置接收缓存区大小  
	acceptor.getSessionConfig().setReadBufferSize(2048);  
	acceptor.getSessionConfig().setIdleTime(IdleStatus.BOTH_IDLE, 10);  
	try {  
		// 服务器开始监听  
		acceptor.bind( new InetSocketAddress(PORT) );  
		System.out.println("启动端口："+PORT);
	}catch(Exception e){  
		e.printStackTrace();  
		}  
	}  

}  


