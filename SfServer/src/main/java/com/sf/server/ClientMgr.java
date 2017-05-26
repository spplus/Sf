package com.sf.server;

import java.util.ArrayList;
import java.util.List;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.mina.core.future.WriteFuture;
import org.apache.mina.core.session.IoSession;

import com.sf.bean.ClientBean;
import com.sf.log.SpLogger;
import com.sf.util.ConstDef;

/**
 * 
 * 客户端管理器，维护客户端在线列表，数据发送接口.
 * 
 * @author yls
 *
 */

public class ClientMgr {

	private static ClientMgr instance = null;
	
	// 在线用户列表集合<连接ID，连接会话>
	private final ConcurrentHashMap<Long, IoSession> online = new ConcurrentHashMap<Long, IoSession>();
	
	private ClientMgr(){
		
	}

	public static ClientMgr instance(){
		if(instance == null){
			instance = new ClientMgr();
		}
		return instance;
	}
	
	/**
	 * 客户端上线.
	 * @param siteId
	 */
	public void addIn(IoSession io){
		online.put(io.getId(), io);
	}
	
	/**
	 * 客户端离线.
	 */
	public void offLine(IoSession io){
		
		for (Entry<Long, IoSession> entry : online.entrySet()) {
			if(entry.getValue() == io){
				online.remove(entry.getKey());
				break;
			}
		}
	}
	
	
	/**
	 * 通过连接ID查找客户端连接.
	 */
	private IoSession getSssion(Long connid){
		
		for (Entry<Long, IoSession> entry : online.entrySet()) {
			if(entry.getKey() == connid){
				return entry.getValue();
			}
		}
		return null;
	}
	
	
	public void setClientInfo(Long connid,ClientBean bean){
		IoSession io = getSssion(connid);
		if(io != null){
			io.setAttribute(ConstDef.CLIENT_INFO, bean);
		}
	}
	
	/**
	 * 发送消息.
	 * 
	 */
	
	public int sendData(String siteId,int cmd,String data){
		
		SpMessage mb = new SpMessage();
		mb.setContent(data);
		mb.setMsgtype(cmd);
		
		List<IoSession> ioList = new ArrayList<IoSession>();
		
		// 查找客户端连接
		for (Entry<Long, IoSession> entry : online.entrySet()) {
			IoSession io = entry.getValue();
			ClientBean bean = (ClientBean) io.getAttribute(ConstDef.CLIENT_INFO);
			if(bean != null && bean.getId().equals(siteId)){
				ioList.add(entry.getValue());
			}
		}
		
		for(int i = 0;i<ioList.size();i++){
			IoSession io = ioList.get(i);
			mb.setConnectId(io.getId());
			WriteFuture wf = io.write(mb);
			wf.awaitUninterruptibly(3000);
			if(wf.isDone()){
				SpLogger.info("send data to cleint:"+mb.toString());
			}
		}
		
		return 0;
	}
	
}
