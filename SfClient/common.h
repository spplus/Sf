#ifndef __COMMON_H__
#define __COMMON_H__

typedef struct Vendors{
	QString vendorUrl ;
	QString vendorName;
	QString vendorPassword;
	QString vendorLoginName;
	QString	vendorFactory;
	Vendors()
	{
		vendorUrl = "";
		vendorName = "";
		vendorPassword = "";
		vendorLoginName = "";
		vendorFactory = "midea";
	}
}Vendors;


#define		SF_TCP_SERVER	"120.210.205.24"//"120.210.205.24"
#define		SF_TCP_PORT		6666

// 命令定义

// 客户端注册
#define		SF_CMD_REG					1000

// 连接建立
#define		SF_CMD_CONNECTED			1001

// 连接断开
#define		SF_CMD_DISCONNECTED			1002

// 播放语音文件
#define		SF_CMD_PLAY_SOUND			1003

// 心跳
#define		SF_CMD_HEARTBEAT			1111

// 心跳周期
#define		SF_HEARTBEAT_INTERVAL		1000*60

#define			DEV_TYPE_AIRCONDITIONER		 1	// 空调
#define 		DEV_TYPE_REFRIGERATOR  		 2	// 冰箱
#define 		DEV_TYPE_HEATER		 		 3	// 热水器
#define 		DEV_TYPE_TV			  		 4	// 电视机
#define 		DEV_TYPE_HOODS		  		 5	// 油烟机
#define 		DEV_TYPE_WASHER 	 		 6	// 洗衣机
#define 		DEV_TYPE_COOKINGBENCH  		 7	// 灶台
#define 		DEV_TYPE_MICROWAVEOVEN 		 8	// 微波炉
#define 		DEV_TYPE_SMALL		  		 9	// 小家电

#define			SOUND_AIRCONDITIONER		"sound/tip1.mp3"
#define			SOUND_REFRIGERATOR			"sound/tip2.mp3"
#define			SOUND_HEATER				"sound/tip3.mp3"
#define			SOUND_TV					"sound/tip4.mp3"
#define			SOUND_HOODS					"sound/tip5.mp3"
#define			SOUND_WASHER				"sound/tip6.mp3"
#define			SOUND_COOKINGBENCH			"sound/tip7.mp3"
#define			SOUND_MICROWAVEOVEN			"sound/tip8.mp3"
#define			SOUND_SMALL					"sound/tip9.mp3"
#define			SOUND_DEFALT				"sound/tip.mp3"
#endif