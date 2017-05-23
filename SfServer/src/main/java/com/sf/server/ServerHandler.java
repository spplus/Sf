package com.sf.server;

import java.util.Date;  

import org.apache.mina.core.service.IoHandlerAdapter;  
import org.apache.mina.core.session.IoSession;  
  
/** 
 * 继承自IoHandlerAdapter，IoHandlerAdapter继承接口 IoHandler 
        类IoHandlerAdapter实现了IoHandler的所有方法，只要重载关心的几个方法就可以了 
 */  
public class ServerHandler extends IoHandlerAdapter {  
  
	
	
    @Override
	public void sessionCreated(IoSession session) throws Exception {
    	
		// TODO Auto-generated method stub
    	System.out.println("sessionCreated");  
		super.sessionCreated(session);
	}

	@Override
	public void sessionOpened(IoSession session) throws Exception {
		
		// TODO Auto-generated method stub
		System.out.println("sessionOpened");  
		super.sessionOpened(session);
	}

	@Override  
    public void exceptionCaught(IoSession session, Throwable cause)  
            throws Exception {  
        cause.printStackTrace();  
    }  
  
    /* 
     * 这个方法是目前这个类里最主要的， 
     * 当接收到消息，只要不是quit，就把服务器当前的时间返回给客户端 
     * 如果是quit，则关闭客户端连接*/  
    @Override  
    public void messageReceived(IoSession session, Object message)  
            throws Exception {  
        String str = message.toString();  
       
        System.out.println("接收到客户端消息:"+str);  
        
        SpMessage mb = new SpMessage();
        mb.setMsgtype(1003);
        mb.setContent("hello");
        Thread.sleep(5000);
        session.write(mb);
        
        System.out.println("通知客户端响铃");  
    }  
      
    @Override  
    public void sessionClosed(IoSession session) throws Exception {  
        // TODO Auto-generated method stub  
        super.sessionClosed(session);  
        System.out.println("客户端与服务端断开连接.....");  
    }  
  
}  