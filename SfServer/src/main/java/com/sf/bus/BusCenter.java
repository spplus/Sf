package com.sf.bus;

import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import net.sf.json.JSONObject;

import com.sf.bean.ClientBean;
import com.sf.cnst.ConstDef;
import com.sf.log.SpLogger;
import com.sf.server.ClientMgr;
import com.sf.server.SpMessage;

/**
 * 业务处理中心.解包后的业务消息，统一投递到业务处理中心进行按类型分拣处理.
 * @author yls
 *
 */

public class BusCenter {

	ExecutorService pool = Executors.newCachedThreadPool();
	
	private final ConcurrentLinkedQueue<SpMessage> msgque = new ConcurrentLinkedQueue<SpMessage>();
	
	private static BusCenter instance = null;
	
	private BusCenter(){
		startWorkThreadPool();
	}
	
	public static BusCenter instance(){
		
		if(instance == null){
			instance = new BusCenter();
		}
		
		return instance;
	}

	
	public void putq(SpMessage mb){
		
		msgque.add(mb);
		
		SpLogger.debug("new message inqueue:"+mb.getContent());
	}
	
	private SpMessage deque(){
		SpMessage mb = msgque.poll();
		if(mb != null){
			SpLogger.debug("dequeue message:"+mb.getContent());
		}
		
		return mb;
	}
	
	private void startWorkThreadPool(){
		
		pool.execute(new Runnable() {
			
			public void run() {

				while(true){
					
					SpMessage mb = deque();
					if(mb != null){
						dealMsg(mb);
					}
					
					try {
						//SpLogger.debug("buscenter is working");
						Thread.sleep(10);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				
			}
		});
		
	}
	
	private void dealMsg(SpMessage mb){
		
		
		switch(mb.getMsgtype()){
		
			case ConstDef.SF_CMD_REG:
				ClientBean bean = new ClientBean();
				// 去掉内容区域的外面的中括号"[]"
				String content = mb.getContent().trim();
				if(content.length()>2){
					
					String newcontent = content.substring(1,content.length()-1);
					JSONObject jsobj = JSONObject.fromObject(newcontent);
					bean.setId(jsobj.getString("siteId"));
					ClientMgr.instance().setClientInfo(mb.getConnectId(), bean);
					
					SpLogger.info("new client reg:"+bean.getId());
				}else{
					SpLogger.info("error reg message:"+bean.getId());
				}
			
				
				// 测试代码 ，向客户端发送业务提醒消息
				//ClientMgr.instance().sendData(bean.getId(), ConstDef.SF_CMD_MESSAGE, "hello");
				
				break;
			case ConstDef.SF_CMD_MESSAGE:
				//ClientMgr.instance().sendData(bean.getId(), ConstDef.SF_CMD_MESSAGE, "hello");
				break;
				
			default:
				SpLogger.warn("unkown cmd message");
				break;
		}
	}
	

}
