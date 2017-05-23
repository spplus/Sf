package com.sf.server;

import java.nio.charset.Charset;  
import org.apache.mina.core.buffer.IoBuffer;  
import org.apache.mina.core.session.IoSession;  
import org.apache.mina.filter.codec.ProtocolEncoderAdapter;  
import org.apache.mina.filter.codec.ProtocolEncoderOutput;  
public class SpProtocalEncoder extends ProtocolEncoderAdapter {  
    private final Charset charset;  
    public SpProtocalEncoder(Charset charset) {  
        this.charset = charset;  
    }  
    //在此处实现对MyProtocalPack包的编码工作，并把它写入输出流中  
    public void encode(IoSession session, Object message, ProtocolEncoderOutput out) throws Exception {  
        SpMessage value = (SpMessage) message;  
        IoBuffer buf = IoBuffer.allocate(value.getLength());  
        buf.setAutoExpand(true);  
        
        buf.putInt(Integer.reverseBytes(value.getLength()));  
        buf.putShort(Short.reverseBytes(value.getMsghead()));
        buf.putInt(Integer.reverseBytes(value.getMsgtype()));
        
        if (value.getContent() != null)  
            buf.put(value.getContent().getBytes());  
        buf.putShort(Short.reverseBytes(value.getMsgtail()));
        
        buf.flip();  
        out.write(buf);  
    }  
    public void dispose() throws Exception {  
    }  
}  