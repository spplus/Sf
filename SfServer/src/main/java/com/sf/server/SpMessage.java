package com.sf.server;

import com.sf.util.ConstDef;

public class SpMessage {  
    
	private int 		length;  
    private short 		msghead;
	private int 		msgtype;
	private short 		msgtail;
    private String 		content;  
    private Long		connectId;
      
    public SpMessage(){  
          msghead = ConstDef.PACKET_HEAD;
          msgtail = ConstDef.PACKET_TAIL;
          
    }  
      
    public SpMessage(int len,short head,int type,short tail,String content){  
        this.msghead = head;
        this.msgtype = type;
        this.msgtail = tail;
        this.content=content;  
        this.length=len;  
    }  
      
      
    public int getLength() {  
        return length;  
    }  
    public void setLength(int length) {  
        this.length = length;  
    }  
   
    public String getContent() {  
        return content;  
    }  
    public short getMsghead() {
		return msghead;
	}

	public void setMsghead(short msghead) {
		this.msghead = msghead;
	}

	public int getMsgtype() {
		return msgtype;
	}

	public void setMsgtype(int msgtype) {
		this.msgtype = msgtype;
	}

	public short getMsgtail() {
		return msgtail;
	}

	public void setMsgtail(short msgtail) {
		this.msgtail = msgtail;
	}

	public void setContent(String content) {  
		
		/*----------------------------------------------------------------
		 |包大小(4byes) | 包头(2byes) | 命令(4byes)|  data   | 包结尾(2bytes) |
		 -----------------------------------------------------------------*/
        this.content = content;  
        length = content.length()+ConstDef.PACKET_HEAD_LEN+ConstDef.BUS_CMD_LEN+ConstDef.PACKET_TAIL_LEN;
    }  
      
    public Long getConnectId() {
		return connectId;
	}

	public void setConnectId(Long connectId) {
		this.connectId = connectId;
	}

	public String toString(){  
        StringBuffer sb=new StringBuffer();  
        sb.append(" connectId:").append(connectId);
        sb.append(" len:").append(length);  
        sb.append(" head:").append(msghead);
        sb.append(" cmd:").append(msgtype);
        sb.append(" tail:").append(msgtail);
        sb.append(" content:").append(content);  
        return sb.toString();  
    }  
}  