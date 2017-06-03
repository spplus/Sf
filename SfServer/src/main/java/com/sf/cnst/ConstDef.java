package com.sf.cnst;

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
	
	// 心跳消息
	public static final int 		SF_CMD_HEARTBEAT		= 1111;

	/*-------------------- 命令定义 END-----------------------*/
	
	public static final int			DEV_TYPE_AIRCONDITIONER = 1;	// 空调
	public static final int 		DEV_TYPE_REFRIGERATOR  	= 2;	// 冰箱
	public static final int 		DEV_TYPE_HEATER		 	= 3;	// 热水器
	public static final int 		DEV_TYPE_TV			  	= 4;	// 电视机
	public static final int 		DEV_TYPE_HOODS		  	= 5;	// 油烟机
	public static final int 		DEV_TYPE_WASHER 	 	= 6;	// 洗衣机
	public static final int 		DEV_TYPE_COOKINGBENCH  	= 7;	// 灶台
	public static final int 		DEV_TYPE_MICROWAVEOVEN 	= 8;	// 微波炉
	public static final int 		DEV_TYPE_SMALL		  	= 9;	// 小家电
	
}
