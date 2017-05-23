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


#define		SF_TCP_SERVER	"192.168.0.231"//"120.210.205.24"
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


#endif