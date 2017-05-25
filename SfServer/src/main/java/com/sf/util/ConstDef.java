package com.sf.util;

public class ConstDef {

	public static final String CLIENT_INFO = "CLIENT_INFO";

	public static final int	PACKET_HEAD = 8888;
	public static final int PACKET_TAIL = 5555;
	public static final int PACKET_HEAD_LEN = 2;
	public static final int PACKET_TAIL_LEN = 2;
	public static final int BUS_CMD_LEN	= 4;
	
	
	/*-------------------- 命令定义 BEGIN-----------------------*/
	
	// 客户端注册
	public static final int			SF_CMD_REG 				= 1000;

	// 业务提醒
	public static  final int		SF_CMD_MESSAGE			= 1003;

	/*-------------------- 命令定义 END-----------------------*/
	
}
