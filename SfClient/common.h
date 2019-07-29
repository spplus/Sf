#ifndef __COMMON_H__
#define __COMMON_H__
#include "configer.h"

typedef struct Vendors{
	int		id;
	QString sfAccount;
	QString vendorUrl ;
	QString vendorName;
	QString vendorPassword;
	QString vendorLoginName;
	QString	vendorFactory;
	QString serverId;
	Vendors()
	{	
		id = 0;
		sfAccount = "";
		vendorUrl = "";
		vendorName = "";
		vendorPassword = "";
		vendorLoginName = "";
		vendorFactory = "midea";
		serverId = "";
	}
}Vendors;

typedef enum Factory {
	GREE,
	TCL,
	Midea,
	Haier,
	Hisense,
	Whirlpool,
	MeiLing,
	Aux,
	Old_Haier,
	Suning,
	GoMe,
	JD,
	Supor,
	ChuangWei,
	Haiercdk
}Factory;


//#define		SF_TCP_SERVER	"120.210.205.24"//"120.210.205.24"
//#define		SF_TCP_PORT		42710

// �����

// �ͻ���ע��
#define		SF_CMD_REG					1000

// ���ӽ���
#define		SF_CMD_CONNECTED			1001

// ���ӶϿ�
#define		SF_CMD_DISCONNECTED			1002

// ���������ļ�
#define		SF_CMD_PLAY_SOUND			1003

// ����
#define		SF_CMD_HEARTBEAT			1111

// ��������
#define		SF_HEARTBEAT_INTERVAL		1000*60

// ����������
#define		SF_SESSIONCHER_INTERVAL		1000*60

// ��֤��ˢ�¼��
#define		SF_CAPTCHA_INTERVAL			1000*100

#define			DEV_TYPE_AIRCONDITIONER		 1	// �յ�
#define 		DEV_TYPE_REFRIGERATOR  		 2	// ����
#define 		DEV_TYPE_HEATER		 		 3	// ��ˮ��
#define 		DEV_TYPE_TV			  		 4	// ���ӻ�
#define 		DEV_TYPE_HOODS		  		 5	// ���̻�
#define 		DEV_TYPE_WASHER 	 		 6	// ϴ�»�
#define 		DEV_TYPE_COOKINGBENCH  		 7	// ��̨
#define 		DEV_TYPE_MICROWAVEOVEN 		 8	// ΢��¯
#define 		DEV_TYPE_SMALL		  		 9	// С�ҵ�

#define			FACTORY_TCL			"tcl"
#define			FACTORY_MEDIA		"midea"
#define			FACTORY_HAIERCDK	"haiercdk"


#define			KEY_FACTORY			"/SF/factory"
#define			PROPERTY_ROWNUM		"rownum"
#define			PROPERTY_FACTORY	"factory"
#define			PROPERTY_USER		"user"
#define			PROPERTY_PWD		"pwd"
#define			PROPERTY_ID			"id"

#define			RESULT_TRUE			"true"

#define			ERROR_PWD						"�������ϵ��˺Ż����벻��ȷ�����޸ĺ����µ�¼��"
#define			ERROR_ALREADY_LONGIN			"�˺�������ҳ�˵�½�����˳���ҳ�˺������µ�¼���֣�"

// URL����

// ͼƬ��֤�������ַ20881
#define			URL_CAPTCHA				"http://localhost:20081/captcha/"

// ���ҵ�¼�ӿ�
#define			URL_FACTORY_LONGIN		"http://localhost:20081/login"

// ϵͳ�˳�
#define			URL_EXIT				"http://localhost:20081/exit"


// ҵ���������ַ
// #define			URL_MAIN_SERVER			"http://192.168.2.23:8780/netDC/main/receiveOrders"
#define			URL_MAIN_SERVER			Configer::instance()->getMainSvr()//"http://www.sifangerp.com/mainserver/sfm/main/receiveOrders"

#define			URL_REPT				"http://local.b"

// session ��ʱ���
#define			URL_SESSION_CHECK		"http://localhost:20081/sessionValid"

// ����session����
#define			URL_REMOVE_SESSION_TIMEOUT	"http://localhost:20081/consumeInvalid"

// ��ӳ���
#define			URL_ADD_FACTORY				"http://www.sifangerp.cn/order2.0/a/main/redirect/addFactoryAccount"

// �༭����
#define			URL_EDIT_FACTORY			"http://www.sifangerp.cn/order2.0/a/main/redirect/modFactoryAccount"

// #define			URL_ADD_FACTORY				"http://192.168.2.58:8080/order/a/main/redirect/addFactoryAccount"

// ɾ������
// #define			URL_DEL_FACTORY				"http://192.168.2.58:8080/order/a/main/redirect/delFactoryAccount?id=%1"
#define			URL_DEL_FACTORY				"http://www.sifangerp.cn/order2.0/a/main/redirect/delFactoryAccount?id=%1"

#endif