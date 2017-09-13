#ifndef __COMMON_H__
#define __COMMON_H__
#include "configer.h"

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


//#define		SF_TCP_SERVER	"120.210.205.24"//"120.210.205.24"
//#define		SF_TCP_PORT		42710

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

// 缓存检查周期
#define		SF_SESSIONCHER_INTERVAL		1000*60

// 验证码刷新间隔
#define		SF_CAPTCHA_INTERVAL			1000*100

#define			DEV_TYPE_AIRCONDITIONER		 1	// 空调
#define 		DEV_TYPE_REFRIGERATOR  		 2	// 冰箱
#define 		DEV_TYPE_HEATER		 		 3	// 热水器
#define 		DEV_TYPE_TV			  		 4	// 电视机
#define 		DEV_TYPE_HOODS		  		 5	// 油烟机
#define 		DEV_TYPE_WASHER 	 		 6	// 洗衣机
#define 		DEV_TYPE_COOKINGBENCH  		 7	// 灶台
#define 		DEV_TYPE_MICROWAVEOVEN 		 8	// 微波炉
#define 		DEV_TYPE_SMALL		  		 9	// 小家电


#define			FACTORY_MEDIA		"midea"
#define			KEY_FACTORY			"/SF/factory"
#define			PROPERTY_ROWNUM		"rownum"
#define			PROPERTY_FACTORY	"factory"
#define			PROPERTY_USER		"user"
#define			PROPERTY_PWD		"pwd"

#define			RESULT_TRUE			"true"

#define			ERROR_PWD						"系统设置下厂家资料的账号或密码不正确，请同步修改后重新登陆！"
#define			ERROR_ALREADY_LONGIN			"账号正在网页端登陆，请退出网页端后再重新登陆助手！"

// URL定义

// 图片验证码请求地址20881
#define			URL_CAPTCHA				"http://localhost:20081/captcha"

// 厂家登录接口
#define			URL_FACTORY_LONGIN		"http://localhost:20081/login"

// 业务服务器地址
//#define			URL_MAIN_SERVER			"http://192.168.2.23:8080/netDC/main/receiveOrders"
#define			URL_MAIN_SERVER			Configer::instance()->getMainSvr()//"http://www.sifangerp.com/mainserver/sfm/main/receiveOrders"

#define			URL_REPT				"http://local.b"

// session 超时检查
#define			URL_SESSION_CHECK		"http://localhost:20081/sessionValid"

// 消除session过期
#define			URL_REMOVE_SESSION_TIMEOUT	"http://localhost:20081/consumeInvalid"

#endif