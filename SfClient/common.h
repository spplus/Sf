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
#define		SF_TCP_PORT		42710

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

#define			DEV_TYPE_AIRCONDITIONER		 1	// �յ�
#define 		DEV_TYPE_REFRIGERATOR  		 2	// ����
#define 		DEV_TYPE_HEATER		 		 3	// ��ˮ��
#define 		DEV_TYPE_TV			  		 4	// ���ӻ�
#define 		DEV_TYPE_HOODS		  		 5	// ���̻�
#define 		DEV_TYPE_WASHER 	 		 6	// ϴ�»�
#define 		DEV_TYPE_COOKINGBENCH  		 7	// ��̨
#define 		DEV_TYPE_MICROWAVEOVEN 		 8	// ΢��¯
#define 		DEV_TYPE_SMALL		  		 9	// С�ҵ�


#define			FACTORY_MEDIA		"midea"
#define			KEY_FACTORY			"factory"


// URL����

// ͼƬ��֤�������ַ
#define			URL_CAPTCHA				"http://localhost:8000/captcha"

// ���ҵ�¼�ӿ�
#define			URL_FACTORY_LONGIN		"http://localhost:8000/login"

// ҵ���������ַ
#define			URL_MAIN_SERVER			"http://www.sifangerp.com/mainserver/sfm/main/receiveOrders"

#define			URL_REPT				"http://local.b"

#endif