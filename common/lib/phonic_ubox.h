#ifndef __PHONIC_UBOX_INCLUDE__
#define __PHONIC_UBOX_INCLUDE__


#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif						

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����

#include <windows.h>

#include <iostream>



/*
#ifdef PHONIC_UBOX_EXPORTS
#define PHONIC_UBOX_API extern "C" __declspec(dllexport)
#else
#define PHONIC_UBOX_API extern "C" __declspec(dllimport)
#endif
*/

#ifdef __cplusplus
extern "C" {
#endif


typedef unsigned long			UBOX_HANDLE;

#define INVALID_UBOX_HANDLE		(UBOX_HANDLE)(-1)

#define	VOICE_FRAME_TIME		20			//����֡ʱ�䣬��λ������



/* ---------------------------------------------
	BusyInfo.busy_dual_frequency    = 0;
	BusyInfo.busy_frequency0        = 450;
	BusyInfo.busy_frequency1        = 420;
	BusyInfo.busy_on                = 35;
	BusyInfo.busy_off               = 35;
	BusyInfo.busy_on_off_error      = 5;
	BusyInfo.busy_enery_gate        = 12;
    BusyInfo.busy_period_count      = 3;
*/

	struct tagBusyInfo
	{
		long  busy_dual_frequency;
		long  busy_frequency0;
		long  busy_frequency1;
		long  busy_on;
		long  busy_off;
		long  busy_on_off_error;
		long  busy_enery_gate;
		long  busy_period_count;
	};

	typedef enum ENUM_VOICE_CODER
	{
		CODER_ALAW		= 0,
		CODER_PCM		= 1,
		CODER_G729		= 3,
		CODER_MP3       = 38,
		CODER_SPEEX		= 20,
		CODER_ULAW		= 100,
	}VOICE_CODER;


	typedef enum ENUM_UBOX_WORK_MODE
	{
		UBOX_MODE_RECORD	= 0,		//¼��ģʽ�� ͨ��ʹ�õ�ģʽ
		UBOX_MODE_DIAG		= 1,		//���ģʽ�� ���ڲ�����·��Ϣ�����źŷ���֮�ã�֧�ֵ��������뷽ʽ��CODER_PCM
		UBOX_MODE_CONFIG	= 2,		//����ģʽ��
	}UBOX_WORK_MODE;


	typedef enum ENUM_UBOX_STATE
	{
		UBOX_STATE_PLUG_OUT  = 0,			//�޴��豸�����豸�ѱ��γ�
		//���豸���γ�ʱ������Ҫ���� stop_record()����Ϊ phonic_ubox �Ѿ��Զ�Ϊ����ù���!

		UBOX_STATE_RESET     = 1,			//��λ̬����ʾ�ȷ�����Ҳ��ժ����״̬�������ǰΪ����̬�����״̬��ʾ������ֹͣ�������ǰΪժ��̬�����״̬��ʾ�ѹһ���
		UBOX_STATE_RINGING   = 2,			//����̬����ʾ�Ѽ�⵽��·�����źţ��������ֹͣ���򽫴��� UBOX_EVENT_RESET �¼������㱨 UBOX_STATE_RESET ״̬��
		UBOX_STATE_HOOK_OFF  = 3,			//��⵽�绰��ժ��
		UBOX_STATE_HANG		 = 4,			  //����̬��
        UBOX_STATE_IDLE     = 5,
		UBOX_STATE_REVERSE_HOOKOFF = 6,     //����ժ����ָ���ժ��
		UBOX_STATE_POSITIVIE_HOOKOFF = 7,   //����ժ����ָ���ժ��
		UBOX_STATE_HANGEX		 = 8,			  //������̬��ʵ�ʿͻ�Ӧ���в���������״̬��  ����·������������ ����Щ��������·�ֹ��·��������
		UBOX_STATE_HANG_UP       = 9,        //�һ�״̬   2012-07-06   ����   ֻ���ڲ�ʹ��
		UBOX_STATE_STOP_REING    = 10,       //ͣ��        2012-07-06   ����   ֻ���ڲ�ʹ��
		UBOX_STATE_RING_CANCEL   = 11,        //����ȡ��   2012-07-06   ����   ֻ���ڲ�ʹ��
		UBOX_STATE_HANG_UPEX     = 12,        //��ʱ�һ�״̬�� ��ֹ��·��ѹ����   
 
	}UBOX_STATE;

	typedef enum ENUM_UBOX_EVENT
	{
		UBOX_EVENT_DEVICE_PLUG_IN   = 1,	//��⵽�豸���룬�ص�������param1��param2��param3��param4δʹ�ã�
		//�������û��˵��,δʹ�ã���ͬ
		UBOX_EVENT_DEVICE_PLUG_OUT  = 2,	//��⵽�豸�γ���

		UBOX_EVENT_ALARM			= 3,	         //����,param1����UBOX_ALARM�Ķ��壬�豸����������������˳�������豸���������Ƿ�װ��

		UBOX_EVENT_LINE_RESET       = 10,	      //��λ��ժ��->�һ�������->ͣ��  Ӳ��LED�� �Ѿ������¼���Ϊ�����һ���ͣ���¼�
		UBOX_EVENT_LINE_RINGING     = 11,	      //���壬Ӳ��LED��
		UBOX_EVENT_LINE_HOOK_OFF    = 12,	      //ժ����Ӳ��LED��
		UBOX_EVENT_LINE_HANG		= 13,	         //��⵽��·���� ��Ĭ����·��ѹС��3V����Ϊ��·���գ�Ӳ��LED��˸

		//UBOX_EVENT_LING_FLUSH		= 14,	       //?? ��Ҫ��

		UBOX_EVENT_RING_CANCEL		= 15,	        //����ȡ������ĩ������ֹͣ����6�룬�򴥷����¼���

		UBOX_EVENT_LINE_VOLTAGE     = 16,     //��·��ѹ�¼���param1����·��ѹֵ��param1������ֵ���0�ĵ�ѹ��
		UBOX_EVENT_STREAM_VOICE     = 20,       //��ʽ¼���¼���param1��¼�����ݵ�ַ����Ҫת����unsigned char* pvoice= (unsigned char*)param1
		// param2��¼�����ݳ���


		UBOX_EVENT_CALLER_ID		= 21,             //param1�Ǻ����ַ  param2��ʱ���ַ  param3��������ַ param4û����
		                                             //��Ҫ����ת�� char* pszcallId =(char*)param1, char* pszcalltime=(char*)param2, 
		                                             //char* pszcallname=(char*) param3

		UBOX_EVENT_DTMF_DOWN		= 22,             //�����¼���param1�ǰ�����ֵ
		UBOX_EVENT_DTMF_UP			= 23,
		UBOX_EVENT_DEVICE_ERROR			= 24,           //�豸����,��Ҫ���������������Ȼ���ղ������к���
		UBOX_EVENT_DEVICE_PLAY_END		= 25,          //�������
		UBOX_EVENT_DEVICE_PLAY_ERROR		= 26,       //�����쳣
		UBOX_EVENT_DEVICE_BUSY_TONE        = 27,        //��⵽æ�����Է��һ�
		UBOX_EVENT_CALLOUTFINISH        = 28,           //������ɣ���ʾ���Ž���
		UBOX_EVENT_POLARITY             = 29,          //��⵽���Է�ת
		UBOX_EVENT_LINE_HOOK_UP         = 30,          //�һ�     �����豸param1��Ч���������͵��豸param1��Ч�� param1: 1 gsm�һ� 2 �����һ� 3 ����һ�
		UBOX_EVENT_LINE_RING_STOP       = 31,          //ͣ�� 

		UBOX_EVENT_SIM_STATE           = 32,           //param1: 1 sim��1  2��sim��2  param2: 0 δ����  1������ 2:GSM ģ����Sim��δ����
		UBOX_EVENT_ANSWER              = 33,
		UBOX_EVENT_GSM_MSG             = 34,         //�յ�GSM���ص���Ϣ
		UBOX_EVENT_SHORT_MSG           =35,          //����
		UBOX_EVENT_SIGNALE_SIZE        = 36,         //�źŴ�С
		UBOX_EVENT_GSM_VOL_SIZE        = 37,         //param1: 1  gsm play 2��gsm mic  param2: ������С
		UBOX_EVENT_SHORT_MSG_SIZE      = 38,         //��������   param1��SIM�� ������Ŀ�� param2: SIM�����Ŵ洢�ռ���Ŀ
		
	}UBOX_EVENT;


	typedef enum ENUM_UBOX_ERROR_CODE
	{
		UBOX_ERR_SUCCESS				= 0,	//�����ɹ�

		UBOX_ERR_SYSTEM					= -1,	//ϵͳ���󣬵��ò���ϵͳ(windows)�ķ���ʱ���ִ���.
		UBOX_ERR_DEVICE_NOT_FOUND		= -2,	//û������豸�������豸�Ѿ����γ�
		UBOX_ERR_INVALID_HANDLE			= -3,	//���Ϸ��� UBOX_HANDLE
		UBOX_ERR_INVALID_PARAMETER		= -4,	//���Ϸ����������
		UBOX_ERR_EXCEPTION				= -5,	//�����쳣
		UBOX_ERR_INVALID_WORK_MODE		= -6,	//����Ĺ���ģʽ
		UBOX_ERR_UBOX_NOT_OPEN			= -7,	//ubox�豸��δ��

		UBOX_ERR_CANNOT_CREATE_DIR		= -10,	//δ�ܴ���Ŀ¼����ָ��¼��ʱ������ļ�������Ŀ¼·������ubox����ͼ������Ӧ��Ŀ¼����
		UBOX_ERR_CANNOT_CREATE_FILE		= -11,	//δ�ܴ���¼���ļ�

		UBOX_ERR_INVALID_VOICE_CODER	= -12,	//��֧�ֵ���������

		UBOX_ERR_DEVICE_BUSY			= -13,	//�豸æ�����豸�Ѿ���¼����ʱ���ٴ�ָʾ��ͬ����(�ļ����ļ���STREAM��STREAM)��¼�����ͻ᷵�ش˴�����
		UBOX_ERR_LINE_NOT_FOUND         = -14,
		UBOX_ERR_USING                  = -15,    //��֧�ָù���,����ʹ��
		UBOX_ERR_EEPROM_ERROR           = -16,

	}UBOX_ERROR_CODE;

	typedef enum ENUM_UBOX_ALARM
	{
		UBOX_ALARM_CAN_FIND_MIC			= 1,	//δ���ҵ� ubox �� MIC �豸
		UBOX_ALARM_CAN_OPEN_MIC			= 2,	//δ�ܴ� ubox �� MIC �豸
		UBOX_ALARM_CAN_OPEN_PLAY        = 3,    //δ�ܴ� ubox �� ���� �豸
		UBOX_ALARM_DEVICE_ERROR			= 4,	//�豸����
		UBOX_WIN7_AUDIO_EXCEPTION       = 5,    //Vista ��win7 audio �豸���ϣ� ��Ҫ���µ���ubox_close,Ȼ�����ubox_open
		UBOX_ALARM_RESET_AUDIO_FAILD     =6,    //��λ audio deviceʧ��
		UBOX_ALARM_RESET_AUDIO_SUCCESS   =7,    //��λ audio device �ɹ�



	}UBOX_ALARM;


   typedef enum ENUM_UBOX_TALK_LINK
	{
		SLIC_TO_GSM	= 0,		//SLIC��GSM����
		GSM_TO_SLIC = 1,	    //GSM��SLIC����
		EARPHONE_TO_GSM	= 2,	//����GSM����
		GSM_TO_EARPHONE =3,     //GSM��������
		SLIC_TO_EARPHONE = 4,    //�绰����ϯ��������
		EARPHONE_TO_SLIC = 5,     //G���󵽵绰����ϯ����
		USB_TO_EARPHONE = 6,     //USB��������     ���ڵ��Բ�������
		USB_TO_GSM = 7,          //USB��GSM����       ���ڵ��Բ�������
		USB_TO_SLIC = 8,          //USB���绰����ϯ����   ���ڵ��Բ�������

	}UBOX_TALK_LINK;

   typedef enum ENUM_UBOX_REC_SWITCH
	{
		SLIC_REC_	= 0,		//SLIC���绰������¼��
		GSM_REC = 1,	         //GSM¼��
		EARPHONE_REC	= 2,	//Earphone������¼��


	}UBOX_REC_SWITCH;

	//�¼��ص�����
	typedef void ( CALLBACK* UBoxEventNotifyProc )( 
		UBOX_HANDLE uboxHnd                    //�豸���
		, int eventID                          //�¼����ο�UBOX_EVENT�Ķ���
		, unsigned long param1                 //���漸��������ͬ���¼����京�岻ͬ
		, unsigned long param2          
		, unsigned long param3
		, unsigned long param4
		);



/*ע������:

   ����USB¼����Ӳ�����ΪϵͳĬ��¼���豸��Ӳ���汾��3.0���ϻ��޸�Ĭ�Ϸ����豸������������ܱ�֤�޸ĳ�ϵͳԭ����Ĭ�Ϸ���
   vista�Ͳ����޸ġ����ο�����������������������Ҫ�����û��޸�Ĭ��¼����Ƶ�豸���ڡ�������塱->����������������Ƶ�豸"->����������Ƶ�豸���ԡ�
   ->"��Ƶ"�����豸�б���ѡ��Ĭ���������ź�¼���豸��

*/


//ubox_open:
//���ܣ�proc �ص�����
//������mode ���� ubox �Ĺ���ģʽ��ͨ���ķ�ʽ��¼����ʽ
//˵������������ɹ����ò�����ʾUSB�豸�򿪳ɹ�,�¼�UBOX_EVENT_DEVICE_PLUG_IN֪ͨ�ϲ�����豸�Ѳ���
// �յ�UBOX_EVENT_ALARM��UBOX_EVENT_DEVICE_ERROR���ϲ�Ӧ�ó���Ҫ�����Ǵ�����������ȷ�������ο���������¼���˵��
//�������������������� ubox_open() ֮�����ʹ�ã�
//      ���򣬶��ڷ�������Ϊ int �ĺ��������� UBOX_ERR_SYSTEM��
//      ���ڷ�������Ϊ UBOX_HANDLE �ĺ��������� INVALID_UBOX_HANDLE��
 int	WINAPI	ubox_open(UBoxEventNotifyProc proc, UBOX_WORK_MODE mode);


 void WINAPI	ubox_close(void);

//ubox_get_work_mode:
//���ܣ����ص�ǰ����ģʽ
//���أ�UBOX_WORK_MODE
 
int			WINAPI			ubox_get_work_mode( void );


//ubox_check_coder:
//���ܣ����ָ�������������Ƿ�Ϸ�
//���أ�0 ���������ǺϷ��ģ�
//      UBOX_ERR_INVALID_VOICE_CODER  �������벻�Ϸ�
//˵�����˺����ɹ������κ�ģʽ��
 
int		WINAPI				ubox_check_coder( int coder );


//ubox_get_line_state:
//���ܣ�
//˵�����˺��������� UBOX_MODE_RECORD �� UBOX_MODE_DIAG ģʽ��ʹ�ã����򷵻� UBOX_ERR_INVALID_WORK_MODE��
 
int			WINAPI			ubox_get_line_state( UBOX_HANDLE uboxHnd);


//ubox_record_file:
//���ܣ�
//˵�����˺��������� UBOX_MODE_RECORD �� UBOX_MODE_DIAG ģʽ��ʹ�ã����򷵻� UBOX_ERR_INVALID_WORK_MODE��
//�����������ο�VOICE_CODER
 int	WINAPI	ubox_record_file(UBOX_HANDLE uboxHnd, const char* filename, int coder );


//ubox_record_stream:
//���ܣ� ��ʼ��ʽ¼���������������ο�VOICE_CODER������������UBOX_EVENT_STREAM_VOICE�¼�֪ͨ
//˵�����˺��������� UBOX_MODE_RECORD �� UBOX_MODE_DIAG ģʽ��ʹ�ã����򷵻� UBOX_ERR_INVALID_WORK_MODE��
 int	WINAPI	ubox_record_stream(UBOX_HANDLE uboxHnd, int coder );


//ubox_stop_record:
//���ܣ�ֹͣ�ļ�����ʽ¼��
//˵�����˺��������� UBOX_MODE_RECORD �� UBOX_MODE_DIAG ģʽ��ʹ�ã����򷵻� UBOX_ERR_INVALID_WORK_MODE��
 int	WINAPI	ubox_stop_record(UBOX_HANDLE uboxHnd);


//ע�⣺ֹͣʹ��
//ubox_set_volume:
//���ܣ�������������������Ϊ0db�Ϳ����ˣ�
//˵����volumeȡֵ��Χ0-19db
 int	WINAPI	ubox_set_volume(UBOX_HANDLE uboxHnd,int volume );


 //ע�⣺ֹͣʹ��
//ubox_set_volume:
//���ܣ����÷�������

//˵����volumeȡֵ��Χ-12db-6db   ,����3101��3102��3002 volumeֵΪ0-20��ϵͳĬ��ֵ��10
 int	WINAPI	ubox_set_Speakervolume(UBOX_HANDLE uboxHnd, int volume );


//ubox_get_hang_threshold:
//���ܣ���ȡ��������ֵ
//˵�����˺��������� UBOX_MODE_CONFIG ģʽ��ʹ�ã����򷵻� UBOX_ERR_INVALID_WORK_MODE��
 int	WINAPI	ubox_get_hang_threshold(UBOX_HANDLE uboxHnd );



//ubox_set_hang_threshold:
//���ܣ�������������ֵ���ο�ubox_set_hookoff_threshold�е�˵��

 int	WINAPI	ubox_set_hang_threshold(UBOX_HANDLE uboxHnd, int threshold );



//ubox_get_hookoff_threshold:
//���ܣ���ȡժ������ֵ
//˵�����˺��������� UBOX_MODE_CONFIG ģʽ��ʹ�ã����򷵻� UBOX_ERR_INVALID_WORK_MODE��
 int	WINAPI	ubox_get_hookoff_threshold(UBOX_HANDLE uboxHnd);



//ubox_set_hookoff_threshold:
//���ܣ�����ժ������ֵ��threshold��ֵ���ȶ�ժ����ѹ�͹һ���ѹ��֮�͵�һ�룬ժ����ѹ�͹һ���ѹ��������ubox_start_read_line_voltage
//��ubox_stop_read_line_voltage���ο���������������÷�.

 int	WINAPI	ubox_set_hookoff_threshold(UBOX_HANDLE uboxHnd, int threshold );




/*Ӳ����ͨ��ѹ�ط�ʽ���绰״̬,ͨ�������,�һ���·ֱ����ѹ48V����,ժ����·ֱ����ѹ�ή��6V���ҡ�USB¼��������Ĭ��ժ������ֵΪ18V, 
����·��ѹ����18V,����ж�Ϊ�һ�״̬,С��18V����ж�Ϊժ��״̬�����ڵ绰�ߵ������Ļ�����ͬ,��·ֱ����ѹֵ��ͬ,����ժ����·��ѹҪ
����ժ������ֵ,���߹һ���ѹС��ժ������ֵ,�������������ȷ��⵽�绰״̬,��Ҫ��������ժ������ֵ*/
//���ܣ���ʼ�����·��ѹ��ÿ��200ms����UBOX_EVENT_LINE_VOLTAGE�¼�֪ͨ,�ص�������param1������·��ѹֵ��ʣ�µĲ���û����
//       ��·��ѹ��һ���������������һ��ʱ�䣬ȡƽ��ֵ��������ý��������·��ѹ����
// �ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0
 int	WINAPI	ubox_start_read_line_voltage(UBOX_HANDLE uboxHnd);


//���ܣ����������·��ѹ���ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0
 int	WINAPI	ubox_stop_read_line_voltage(UBOX_HANDLE uboxHnd);

//���ܣ����豸�򿪺󣬲ſ��Ի�ȡӲ���İ汾�ţ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0   version_num���������ֺ�1λС��������ɣ�
//�������������汾�ţ�С�������Ǵΰ汾��
//����˵������һ���������豸������ڶ��������ǻ�ȡ�汾�ţ���������豸�����2������float versionnum������ubox_get_device_versionnum��2��versionnum��
 int      WINAPI    ubox_get_device_versionnum(UBOX_HANDLE uboxHnd,float &version_num);


//���ܣ����豸�򿪺��ֶ�ժ�绰�����ϲ�Ӧ������Զ����ţ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0��Ӳ���汾��С��3.0��֧�ֲ��Ź���
//����˵������һ���������豸������ڶ��������ǲ��ŵĺ��룬��������豸�����2��Ҫ����10000������ubox_send_dtmf��2��"10000"��

 int      WINAPI    ubox_send_dtmf(UBOX_HANDLE uboxHnd,const char* dmftfstring);



//���ܣ����豸�򿪺󣬲��������ļ�����PC������Ƶ�ļ��Ľ��������ܲ��š��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0
//ע�⣺һ�߲����ļ�����Ӱ��¼����Ч��������ͨ���ǵ�������Ӳ���汾��С��3.0��֧�ַ�������
 int WINAPI ubox_play_file(UBOX_HANDLE uboxHnd,const char* filename);

//���ܣ����豸�򿪺�ֹͣ���ţ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�-1 
 int WINAPI ubox_stop_play(UBOX_HANDLE uboxHnd);

//���ܣ����豸�򿪺����ڲ��ţ��������������ͣ���ٵ���һ�Σ��ּ������ţ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0
 int  WINAPI ubox_play_pause(UBOX_HANDLE uboxHnd);


//���ܣ����豸�ɹ��򿪺󣬴򿪺͹ر�AGC,�ڶ�����Ϊtrue,�ر�agc,Ϊfalseʱ����agc,Ĭ��������Ǵ�agc.�ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0 
 int WINAPI  ubox_close_agc(UBOX_HANDLE uboxHnd,bool bclose);


//���ܣ����豸�ɹ��򿪺󣬴˺��������� UBOX_MODE_CONFIG ģʽ��ʹ��,��ȡeeprom��������ݣ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0,
//��������������벻��ȷ������UBOX_ERR_INVALID_PARAMETER
//addr��ַ��ΧΪ0x00-0x07,�����������Χ�ڣ���ȡ������󳤶�Ϊ8���ֽ�,����������Ϊ��ȡ���ݵĵ�ַ
//�÷�������uboxHnd��1��addr=0x00,unsigned char readdata[8]
//ubox_read_eeprom(1,0x00,&readata[0],8),���óɹ��󣬶�ȡ��������readdata��
 int WINAPI ubox_read_eeprom(UBOX_HANDLE uboxHnd,unsigned char addr,unsigned char* outdata,int len);

//���ܣ����豸�ɹ��򿪺󣬴˺��������κ�ģʽ��ʹ��,д��eeprom��������ݣ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0��
//��������������벻��ȷ������UBOX_ERR_INVALID_PARAMETER
//addr��ַ��ΧΪ0x00-0x08,�����������Χ�ڣ�д��������󳤶�Ϊ8���ֽ�,����������Ϊд�����ݵĵ�ַ
//�÷�������uboxHnd��1��addr=0x00,unsigned char writedata[8] ={0x01,0x20,0x30,0x31,0x32,0x33,0x40,0x70}
//ubox_write_eeprom(1,0x00,&writedata[0],8),������ͬһ����ַ�������ubox_read_eeprom��֤����ȡ�����ݺ�д�������Ƿ����
 int WINAPI ubox_write_eeprom(UBOX_HANDLE uboxHnd,unsigned char addr,unsigned char* indata,int len);


//���ܣ����豸�ɹ��򿪺󣬴˺��������κ�ģʽ��ʹ��,��ȡeeprom��������ݣ��ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0,
//��������������벻��ȷ������UBOX_ERR_INVALID_PARAMETER
//addr��ַ��ΧΪ0x00-0x08,�����������Χ�ڣ���ȡ������󳤶�Ϊ8���ֽ�,����addr+len��Ҫ����8������������Ϊ��ȡ���ݵĵ�ַ
//�÷�������uboxHnd��1��addr=0x00,unsigned char readdata[8]
//ubox_read_eeprom(1,0x00,&readata[0],8),���óɹ��󣬶�ȡ��������readdata��
//ע�����ubox_write_eepromд�ɹ��󣬶�ȡ����ȷֵ��������������������󣬵���ubox_read_eepromEx������ȷ��ȡ�ϴ��޸ĵ�ֵ��
 
 int WINAPI ubox_read_eepromEx(UBOX_HANDLE uboxHnd,unsigned char addr,unsigned char* outdata,int len);


 //���ܣ����豸�ɹ��򿪺����ժ�����ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0
 //ע�⣺������Ӳ���汾3.0���ϲ�֧��
 int WINAPI ubox_soft_hook_off(UBOX_HANDLE uboxHnd);

 //���ܣ����豸�ɹ��򿪺�����һ����ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0
  //ע�⣺������Ӳ���汾3.0���ϲ�֧��
 int WINAPI ubox_soft_hook_on(UBOX_HANDLE uboxHnd);

 ////���ܣ����豸�ɹ��򿪺󣬴˺�����ȡ�û��ţ��ɹ������û��ų��ȣ����󷵻�ΪС��0����,
 //�û��ŵĳ�����8���ֽ�,���� ����len��С��8, user-num���õ�ַ�ռ䲻��С��8���ֽڡ�

 // �����Ҫ�û�������ϵ�ҹ�˾
 int WINAPI ubox_get_usernum(UBOX_HANDLE uboxHnd,unsigned char* user_num,int len);


//���ܣ����豸�ɹ��򿪺����æ���ղ���������Ҫ���øò������˺�������æ���������ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0,

 int WINAPI  ubox_set_busy_tone(UBOX_HANDLE uboxHnd,const tagBusyInfo busyinfo);

 //���ܣ� ���豸�ɹ��򿪺󣬻�ȡ�豸����
 //����ֵ���豸���ֵĳ��ȣ��豸����ΪFi3001B ��1·����¼�� �豸����ΪFi3002B ��2·����¼�� �豸����ΪFi3102A ����·���� �豸����ΪFi3101A ��1·������
int  WINAPI  ubox_get_product_name(UBOX_HANDLE uboxHnd, char* product_name);

//���ܣ����豸�ɹ��򿪺󣬴˺�����������ģʽ������bset=true �����Բ�����bset=false �ر����Բ������ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0,
//ע�⣺��Ҫ��������ģʽ�²���Ҫ�����Բ�����
 //Ҫ�˳�����ģʽ������ر����Բ�����������˷粻����
 int WINAPI  ubox_set_message_param(UBOX_HANDLE uboxHnd,bool bset);



 //���ܣ����豸�ɹ��򿪺󣬴˺��������Ƿ�򿪷�������bset=true ��������bset=false �رշ��������ɹ�����UBOX_ERR_SUCCESS�����󷵻�Ϊ��0,
//ע�⣺Ĭ���ǹرշ�������������ֻ�Ӷ���ʱ������ʱ��ʾ�û�������������Ѵ򿪣�����ʱ���������졣
 
 int WINAPI  ubox_open_buzzer_switch(UBOX_HANDLE uboxHnd,bool bset);

//��ȡ��ƷID�ţ�����ֵ���ǲ�ƷID,��Ӧ��ֵ���£�

//  1             FI3102A   2·USB ����
//	2             FI3002B   2·USB¼����
//  3             FI3001B   1·USB¼����
//	4             FI3101A   �������USB�����У�1��1�ڣ�

int WINAPI  ubox_get_product_ID(UBOX_HANDLE uboxHnd);

//����־�ļ����ú��������ڵ���ubox_open֮ǰ����
//level=0,  ��ʾ������־��Ϣ
//level =1, ��ʾ����;�����Ϣ��ʾ
void WINAPI  ubox_open_logfile(long level);

//�ر���־�ļ�
void WINAPI  ubox_close_logfile();

//����־�ļ����ú��������ڵ���ubox_open֮ǰ����
//dir:��¼��־�ļ���·��,���Ϊ�գ����ǵ�ǰ����Ŀ¼�¡�
//level=0,  ��ʾ������־��Ϣ
//level =1, ��ʾ����;�����Ϣ��ʾ
void WINAPI  ubox_open_logfileEx(const char* dir, long level);


int WINAPI ubox_write_usernum(UBOX_HANDLE uboxHnd,unsigned char* user_num,int len);

/*

��  �ܣ�PUT�ϴ�¼���ļ���
��  ����uploadUrl�� �ϴ��ļ�ʹ�õ�URL������192.168.1.1��
paramName:  �ύhttp����ʱ���ϴ��ļ��ڷ����������֣����԰���Ŀ¼��Ŀ¼�����Ǵ��ڵġ�
        uploadFilePath��   ���ϴ����ļ�ȫ·��������D:\\recordFile.wav��
��  �أ��ϴ��ɹ�����0��ʧ�ܷ��ظ�����


*/

int WINAPI ubox_uploadFile(LPCTSTR uploadUrl, LPCTSTR paramName, LPCTSTR uploadFilename);



/*

��  �ܣ�POST�ϴ�¼���ļ���
��  ����uploadUrl�� �ϴ��ļ�ʹ�õ�URL������192.168.1.1��
paramName:  �ύhttp����ʱ���ϴ��ļ��ڷ����������֣����԰���Ŀ¼��Ŀ¼�����Ǵ��ڵġ�
        uploadFilePath��   ���ϴ����ļ�ȫ·��������D:\\recordFile.wav��
��  �أ��ϴ��ɹ�����0��ʧ�ܷ��ظ�����


*/

//int WINAPI ubox_uploadFileEx(LPCTSTR uploadUrl, LPCTSTR paramName, LPCTSTR uploadFilename);
/*
    �ú����޸Ĳ��Ų�����ͬʱ�޸�ubox.ini�ļ��еĲ���
   tone_time :dtmf�������� Ĭ����100ms   ֧��80-150
   silence_time�� dtmf�������� Ĭ����80ms   ֧��50-200
   dtmf_cof:     dtmfϵ����Ĭ����1.26, ������ѡ��Ϊ1
   dtmf_scale:  dtmf���ȣ�Ĭ����220�� ��Χ�ǣ�190-240��
   speaker_volume�� ���ŷ���������Ĭ����10  ��Χ�ǣ�5-18��
  */
int  WINAPI  ubox_set_send_dtmf_param(UBOX_HANDLE uboxHnd, int tone_time, int silence_time, float dtmf_cof, int dtmf_scale,int speaker_volume);

int  WINAPI  ubox_get_send_dtmf_param(int& tone_time, int& silence_time, float& dtmf_cof, int& dtmf_scale,int& speaker_volume);

int  WINAPI  ubox_delete_file(LPCTSTR filename);
//int  WINAPI  ubox_judge_file_exist(LPCTSTR filename);
int  WINAPI  ubox_judge_file_size(LPCTSTR filename);

char*    WINAPI   ubox_get_disk_info(void); 
char*    WINAPI   ubox_get_system(void) ; 

//Fi3002B �汾7.07 �汾��֧��
char*    WINAPI   ubox_get_serial_number(UBOX_HANDLE uboxHnd) ; 

//Fi3301  ֧�ֵĺ���

int       WINAPI   ubox_makecall(UBOX_HANDLE uboxHnd, char* phonenumber);
int       WINAPI   ubox_reject_call(UBOX_HANDLE uboxHnd);

int       WINAPI    ubox_set_talk_link(UBOX_HANDLE uboxHnd, int mode, int value);   //�趨ͨ��link ����
int       WINAPI    ubox_makecallSlic(UBOX_HANDLE uboxHnd, int  ringtime, int stopringtime, char* phonenumber);
int       WINAPI    ubox_set_record_enable(UBOX_HANDLE uboxHnd, int mode, int value);   // �趨¼������


int       WINAPI    ubox_gsm_power(UBOX_HANDLE uboxHnd, int value);  //0��GSMģ��ϵ磬 1��GSMģ���ϵ�
int       WINAPI    ubox_gsm_bootkey(UBOX_HANDLE uboxHnd, int value);  //1��GSM�������� ��ʱ��1~2s,�ڵ����ͷ�����,  0:GSM�������ͷ�

int       WINAPI    ubox_feed_slic_polarity(UBOX_HANDLE uboxHnd, int value);  //0��slic��������,  1:slic��������

/*

*/
int       WINAPI    ubox_send_gsm_cmd(UBOX_HANDLE uboxHnd, char* cmd, int len);                   //����GSM���������GSMģ��ʹ��

int       WINAPI    ubox_send_gsm_msg(UBOX_HANDLE uboxHnd, int mode, char* phonenumber, char* msg, int len);   //������,һ�����Ų�Ҫ����70����
/*
��ѯGSM�豸�ɴ洢������Ŀ��Ŀǰ�ж���������
*/
int       WINAPI    ubox_query_gsm_msg_number(UBOX_HANDLE uboxHnd);  

/*
��������ֵ������ֵͨ��ubox_query_gsm_msg_number��ȡ�� index��1��ʼ����ѯGSM�豸�ڶ�������


*/
int       WINAPI    ubox_query_gsm_msg(UBOX_HANDLE uboxHnd, int index);     //����������unicode��ʽ����ҪӦ�������ת��

int       WINAPI    ubox_query_gsm_msgEx(UBOX_HANDLE uboxHnd, int index);   //���������Ѿ�ת��Ϊ���ֽڷ�ʽ

/*ɾ��������Ŀ
msgtype=0, index��ɾ���������ŵ����,msgtypeΪ����ֵ��index��Ϊ1
msgtype=1, ɾ�����е��Ѿ��Ķ��Ķ���Ϣ
msgtype=2, ɾ�����е��Ѿ��Ķ��ͷ��ͳ�ȥ�Ķ���Ϣ
msgtype=3, ɾ�����е��Ѿ��Ķ������Ѿ����ͳ�ȥ�ĺ�δ���͵Ķ���Ϣ
msgtype=4, ɾ�����еĶ���Ϣ
*/
int       WINAPI    ubox_delete_gsm_msg(UBOX_HANDLE uboxHnd, int index, int msgtype);

 //�豸�ǵ�ģ��֧��˫����0:ѡ��sim��1�� 1��ѡ��sim��2
// ѡ�񿨺���Ҫ��GSMģ��ϵ磬�ϵ磬Ȼ�����GSM������ ubox_gsm_bootkey(1),��ʱ2�룬��󿪻����ͷ�ubox_gsm_bootkey(0)
int       WINAPI    ubox_select_simcard(UBOX_HANDLE uboxHnd, int simcardno);  

/*
����GSM��������������� 
type:0 ��������      0-10
type:1���������     0-100

*/
int       WINAPI    ubox_set_gsm_vol(UBOX_HANDLE uboxHnd, int type, int vol); 

/*
type:0 �������� 
type:1���������
��ȡGSM������������������¼�UBOX_EVENT_GSM_VOL_SIZE֪ͨ
*/
int       WINAPI    ubox_get_gsm_vol(UBOX_HANDLE uboxHnd, int type);  

/*
type: 0  ����ģʽ�� 1���绰��ģʽ
���ö����slic�绰������ģʽ
type      mode
  0        1        �����Զ�ģʽ���е绰���룬�������߰�ť���绰ժ�����ٰ���һ�Σ��Ҷ�GSMͨ��
  0        1        �رն����Զ�ģʽ

  1         1       �����Զ�ģʽ���绰���룬�绰�����壬�绰���һ����Ҷ�GSMͨ��

  1         0       �رջ����Զ�ģʽ
*/

int       WINAPI    ubox_set_gsm_work_mode(UBOX_HANDLE uboxHnd, int type, int mode);

/*
 ��GSMģ��������ض��Ƶ����� ���ڵ绰�����ʱ�򣬶��������ܹ��������������������� 
mode           0    ֹͣ���� 
              1  ��ʼ���� 
freq         ���ŵ���Ƶ�� 
periodon    һ�������ڲ��ŵ�����ʱ�� 
periodoff   һ�������ھ�����ʱ�� 
duration   ����������ʱ������λΪ���� 
*/

int  WINAPI    ubox_gsm_generate_tone(UBOX_HANDLE uboxHnd, int mode, int freq, int periodon, int periodoff, int duration);


 #ifdef __cplusplus
}
#endif

#ifdef __cplusplus


class ubox_state_formator
{
	int			state_code_;

	ubox_state_formator();

public:
	ubox_state_formator( int code ):state_code_(code){;}
	ubox_state_formator( const ubox_state_formator& rhs):state_code_(rhs.state_code_){;}
	ubox_state_formator& operator = ( const ubox_state_formator& rhs)
	{
		state_code_ = rhs.state_code_;
		return *this;
	}


	friend std::ostream & operator << (std::ostream& os ,const ubox_state_formator& me )
	{
		switch( me.state_code_ )
		{
		case UBOX_STATE_PLUG_OUT:
			os << "״̬=" << me.state_code_ << " : ���豸";	
			break;
		case UBOX_STATE_RESET:
			os << "״̬=" << me.state_code_ << " : ��λ";	
			break;
		case UBOX_STATE_RINGING:
			os << "״̬=" << me.state_code_ << " : ����";	
			break;
		case UBOX_STATE_HOOK_OFF:
			os << "״̬=" << me.state_code_ << " : ժ��";	
			break;
		case UBOX_STATE_HANG:
			os << "״̬=" << me.state_code_ << " : ����";	
			break;

		case UBOX_STATE_REVERSE_HOOKOFF:
			os << "״̬=" << me.state_code_ << " : ����ժ��";	
			break;
		case UBOX_STATE_POSITIVIE_HOOKOFF:
			os << "״̬=" << me.state_code_ << " : ����ժ��";	
			break;

	/*	case UBOX_STATE_TELEPHONE_HOOKON:
             os << "״̬=" << me.state_code_ << " : �绰���һ�";	
			break;*/
		default:
			os << "״̬=" << me.state_code_ << " : δ����";	
			break;
		}
		return os;
	}
};


class ubox_event_formator
{
	int			event_code_;

	ubox_event_formator();

public:
	ubox_event_formator( int code ):event_code_(code){;}
	ubox_event_formator( const ubox_event_formator& rhs):event_code_(rhs.event_code_){;}
	ubox_event_formator& operator = ( const ubox_event_formator& rhs)
	{
		event_code_ = rhs.event_code_;
		return *this;
	}

	friend std::ostream & operator << (std::ostream& os ,const ubox_event_formator& me )
	{
		switch( me.event_code_ )
		{
		case UBOX_EVENT_DEVICE_PLUG_IN:
			os << "�¼�=" << me.event_code_ << " : �豸����";	
			break;
		case UBOX_EVENT_DEVICE_PLUG_OUT:
			os << "�¼�=" << me.event_code_ << " : �豸�γ�";	
			break;

		case UBOX_EVENT_LINE_RESET:
			os << "�¼�=" << me.event_code_ << " : ��·��λ";	
			break;

		case UBOX_EVENT_LINE_RINGING:
			os << "�¼�=" << me.event_code_ << " : ��·����";	
			break;

		case UBOX_EVENT_LINE_HOOK_OFF:
			os << "�¼�=" << me.event_code_ << " : ��·ժ��";	
			break;

		case UBOX_EVENT_LINE_HANG://��⵽��·����
			os << "�¼�=" << me.event_code_ << " : ��·����";	
			break;


		case UBOX_EVENT_STREAM_VOICE:
			os << "�¼�=" << me.event_code_ << " : ʵʱ����";	
			break;


		case UBOX_EVENT_CALLER_ID:
			os << "�¼�=" << me.event_code_ << " : �������";	
			break;

		case UBOX_EVENT_DTMF_DOWN:
			os << "�¼�=" << me.event_code_ << " : DTMF����";	
			break;

		case UBOX_EVENT_DTMF_UP:
			os << "�¼�=" << me.event_code_ << " : DTMF�ͷ�";	
			break;

		case UBOX_EVENT_ALARM:
			os << "�¼�=" << me.event_code_ << " : ����֪ͨ";	
			break;

		case UBOX_EVENT_RING_CANCEL:
			os << "�¼�=" << me.event_code_ << " : ����ȡ��";	
			break;

		default:
			os << "�¼�=" << me.event_code_ << " : δ������¼���";	
			break;
		}
		return os;
	}
};

class ubox_err
{
	int		err_code_;
public:
	ubox_err(int code):err_code_(code){;}

	friend std::ostream & operator << (std::ostream& os ,const ubox_err& me )
	{
		switch( me.err_code_ )
		{
		case UBOX_ERR_SUCCESS:
			os << "������=" << me.err_code_ << " : �����ɹ�";	
			break;
		case UBOX_ERR_SYSTEM:
			os << "������=" << me.err_code_ << " : ϵͳ����";	
			break;
		case UBOX_ERR_DEVICE_NOT_FOUND:
			os << "������=" << me.err_code_ << " : �޴��豸";	
			break;
		case UBOX_ERR_INVALID_HANDLE:
			os << "������=" << me.err_code_ << " : �Ƿ��� UBOX_HANDLE";	
			break;
		case UBOX_ERR_INVALID_PARAMETER:
			os << "������=" << me.err_code_ << " : �Ƿ�����";	
			break;
		case UBOX_ERR_CANNOT_CREATE_DIR:
			os << "������=" << me.err_code_ << " : δ�ܴ���Ŀ¼";	
			break;
		case UBOX_ERR_CANNOT_CREATE_FILE:
			os << "������=" << me.err_code_ << " : δ�ܴ���¼���ļ�";	
			break;
		case UBOX_ERR_INVALID_VOICE_CODER:
			os << "������=" << me.err_code_ << " : ��֧�ֵ���������";	
			break;
		case UBOX_ERR_INVALID_WORK_MODE:
			os << "������=" << me.err_code_ << " : ����Ĺ���ģʽ";	
			break;
		case UBOX_ERR_EXCEPTION:
			os << "������=" << me.err_code_ << " : �����쳣";	
			break;
		case UBOX_ERR_DEVICE_BUSY:
			os << "������=" << me.err_code_ << " : �豸æ";	
			break;
		case UBOX_ERR_UBOX_NOT_OPEN:
			os << "������=" << me.err_code_ << " : ubox�豸��δ��";	
			break;


		default:
			os << "������=" << me.err_code_ << " : δ����Ĵ�����";	
			break;
		}
		return os;
	}
};

/*
ubox_err ʹ�÷�����

int result = ubox_record_stream(uboxHnd, coder );
if( result != UBOX_ERR_SUCCESS )
{
std::cout << "ubox_record_stream(, " << coder << " ) faild! "
<< ubox_err(result) 
<< std::endl;
}
*/

#endif //__cplusplus

#endif//__PHONIC_UBOX_INCLUDE__
