package com.sf.server;

public class SpMessage {  
    
	private int length;  
    private short msghead;
	private int msgtype;
	private short msgtail;
    private String content;  
      
    public SpMessage(){  
          msghead = 8888;
          msgtail = 5555;
          
    }  
      
    public SpMessage(int len,short head,int type,short tail,String content){  
        this.msghead = head;
        this.msgtype = type;
        this.msgtail = tail;
        this.content=content;  
        this.length=len;  
    }  
      
    public SpMessage(byte[] bs){  
       
    	/*
    	if(bs!=null && bs.length>=5){  
            length=GFCommon.bytes2int(GFCommon.bytesCopy(bs, 0, 4));  
            flag=bs[4];  
            content=new String(GFCommon.bytesCopy(bs, 5, length-5));  
        } 
        */ 
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
        this.content = content;  
        length = content.length()+2+4+2;
    }  
      
    public String toString(){  
        StringBuffer sb=new StringBuffer();  
        sb.append(" len:").append(length);  
        sb.append(" head:").append(msghead);
        sb.append(" cmd:").append(msgtype);
        sb.append(" tail:").append(msgtail);
        sb.append(" content:").append(content);  
        return sb.toString();  
    }  
}  