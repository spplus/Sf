package com.sf.server;

import java.nio.charset.Charset;  
import org.apache.mina.core.session.IoSession;  
import org.apache.mina.filter.codec.ProtocolCodecFactory;  
import org.apache.mina.filter.codec.ProtocolDecoder;  
import org.apache.mina.filter.codec.ProtocolEncoder;  
public class SpProtocalCodecFactory   implements ProtocolCodecFactory {  
        private final SpProtocalEncoder encoder;  
        private final SpProtocalDecoder decoder;  
          
        public SpProtocalCodecFactory(Charset charset) {  
            encoder=new SpProtocalEncoder(charset);  
            decoder=new SpProtocalDecoder(charset);  
        }  
           
        public ProtocolEncoder getEncoder(IoSession session) {  
            return encoder;  
        }  
        public ProtocolDecoder getDecoder(IoSession session) {  
            return decoder;  
        }  
          
}  