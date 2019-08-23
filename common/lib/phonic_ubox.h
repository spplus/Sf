#ifndef __PHONIC_UBOX_INCLUDE__
#define __PHONIC_UBOX_INCLUDE__


#ifndef WINVER
#define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif						

#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料

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

#define	VOICE_FRAME_TIME		20			//语音帧时间，单位：毫秒



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
		UBOX_MODE_RECORD	= 0,		//录音模式， 通常使用的模式
		UBOX_MODE_DIAG		= 1,		//诊断模式， 用于捕获线路信息，供信号分析之用，支持的语音编码方式是CODER_PCM
		UBOX_MODE_CONFIG	= 2,		//配置模式，
	}UBOX_WORK_MODE;


	typedef enum ENUM_UBOX_STATE
	{
		UBOX_STATE_PLUG_OUT  = 0,			//无此设备，或设备已被拔出
		//当设备被拔出时，不需要调用 stop_record()，因为 phonic_ubox 已经自动为你调用过了!

		UBOX_STATE_RESET     = 1,			//复位态，表示既非振铃也非摘机的状态。如果此前为振铃态，则此状态表示振铃已停止，如果此前为摘机态，则此状态表示已挂机。
		UBOX_STATE_RINGING   = 2,			//振铃态，表示已检测到线路振铃信号，如果振铃停止，则将触发 UBOX_EVENT_RESET 事件，并汇报 UBOX_STATE_RESET 状态。
		UBOX_STATE_HOOK_OFF  = 3,			//检测到电话机摘机
		UBOX_STATE_HANG		 = 4,			  //悬空态，
        UBOX_STATE_IDLE     = 5,
		UBOX_STATE_REVERSE_HOOKOFF = 6,     //反向摘机，指软件摘机
		UBOX_STATE_POSITIVIE_HOOKOFF = 7,   //正向摘机，指软件摘机
		UBOX_STATE_HANGEX		 = 8,			  //暂悬空态，实际客户应用中不会出现这个状态。  当线路是连接正常， 在有些特殊情况下防止线路出现悬空
		UBOX_STATE_HANG_UP       = 9,        //挂机状态   2012-07-06   增加   只供内部使用
		UBOX_STATE_STOP_REING    = 10,       //停振        2012-07-06   增加   只供内部使用
		UBOX_STATE_RING_CANCEL   = 11,        //振铃取消   2012-07-06   增加   只供内部使用
		UBOX_STATE_HANG_UPEX     = 12,        //临时挂机状态， 防止线路电压跳变   
 
	}UBOX_STATE;

	typedef enum ENUM_UBOX_EVENT
	{
		UBOX_EVENT_DEVICE_PLUG_IN   = 1,	//检测到设备插入，回调函数中param1、param2、param3、param4未使用，
		//参数如果没有说明,未使用，下同
		UBOX_EVENT_DEVICE_PLUG_OUT  = 2,	//检测到设备拔出，

		UBOX_EVENT_ALARM			= 3,	         //报警,param1参照UBOX_ALARM的定义，设备工作不正常，软件退出，检查设备驱动程序是否安装好

		UBOX_EVENT_LINE_RESET       = 10,	      //复位：摘机->挂机，振铃->停振  硬件LED灭 已经将该事件分为两个挂机和停振事件
		UBOX_EVENT_LINE_RINGING     = 11,	      //振铃，硬件LED亮
		UBOX_EVENT_LINE_HOOK_OFF    = 12,	      //摘机，硬件LED亮
		UBOX_EVENT_LINE_HANG		= 13,	         //检测到线路悬空 ，默认线路电压小于3V，认为线路悬空，硬件LED闪烁

		//UBOX_EVENT_LING_FLUSH		= 14,	       //?? 需要吗？

		UBOX_EVENT_RING_CANCEL		= 15,	        //振铃取消，当末次振铃停止超过6秒，则触发此事件，

		UBOX_EVENT_LINE_VOLTAGE     = 16,     //线路电压事件，param1是线路电压值，param1不会出现等于0的电压。
		UBOX_EVENT_STREAM_VOICE     = 20,       //流式录音事件，param1是录音数据地址，需要转换，unsigned char* pvoice= (unsigned char*)param1
		// param2是录音数据长度


		UBOX_EVENT_CALLER_ID		= 21,             //param1是号码地址  param2是时间地址  param3是姓名地址 param4没有用
		                                             //需要类型转换 char* pszcallId =(char*)param1, char* pszcalltime=(char*)param2, 
		                                             //char* pszcallname=(char*) param3

		UBOX_EVENT_DTMF_DOWN		= 22,             //按键事件，param1是按键键值
		UBOX_EVENT_DTMF_UP			= 23,
		UBOX_EVENT_DEVICE_ERROR			= 24,           //设备错误,需要软件重新启动，不然接收不到主叫号码
		UBOX_EVENT_DEVICE_PLAY_END		= 25,          //放音完毕
		UBOX_EVENT_DEVICE_PLAY_ERROR		= 26,       //放音异常
		UBOX_EVENT_DEVICE_BUSY_TONE        = 27,        //检测到忙音，对方挂机
		UBOX_EVENT_CALLOUTFINISH        = 28,           //呼出完成，表示拨号结束
		UBOX_EVENT_POLARITY             = 29,          //检测到极性反转
		UBOX_EVENT_LINE_HOOK_UP         = 30,          //挂机     无线设备param1有效，其它类型的设备param1无效， param1: 1 gsm挂机 2 话机挂机 3 耳麦挂机
		UBOX_EVENT_LINE_RING_STOP       = 31,          //停振 

		UBOX_EVENT_SIM_STATE           = 32,           //param1: 1 sim卡1  2：sim卡2  param2: 0 未插入  1：插入 2:GSM 模块检查Sim卡未插入
		UBOX_EVENT_ANSWER              = 33,
		UBOX_EVENT_GSM_MSG             = 34,         //收到GSM返回的消息
		UBOX_EVENT_SHORT_MSG           =35,          //短信
		UBOX_EVENT_SIGNALE_SIZE        = 36,         //信号大小
		UBOX_EVENT_GSM_VOL_SIZE        = 37,         //param1: 1  gsm play 2：gsm mic  param2: 声音大小
		UBOX_EVENT_SHORT_MSG_SIZE      = 38,         //短信数量   param1：SIM卡 短信数目， param2: SIM卡短信存储空间数目
		
	}UBOX_EVENT;


	typedef enum ENUM_UBOX_ERROR_CODE
	{
		UBOX_ERR_SUCCESS				= 0,	//操作成功

		UBOX_ERR_SYSTEM					= -1,	//系统错误，调用操作系统(windows)的方法时出现错误.
		UBOX_ERR_DEVICE_NOT_FOUND		= -2,	//没有这个设备，可能设备已经被拔出
		UBOX_ERR_INVALID_HANDLE			= -3,	//不合法的 UBOX_HANDLE
		UBOX_ERR_INVALID_PARAMETER		= -4,	//不合法的输入参数
		UBOX_ERR_EXCEPTION				= -5,	//发生异常
		UBOX_ERR_INVALID_WORK_MODE		= -6,	//错误的工作模式
		UBOX_ERR_UBOX_NOT_OPEN			= -7,	//ubox设备尚未打开

		UBOX_ERR_CANNOT_CREATE_DIR		= -10,	//未能创建目录，当指定录音时，如果文件名包含目录路径，则ubox将试图建立相应的目录树。
		UBOX_ERR_CANNOT_CREATE_FILE		= -11,	//未能创建录音文件

		UBOX_ERR_INVALID_VOICE_CODER	= -12,	//不支持的语音编码

		UBOX_ERR_DEVICE_BUSY			= -13,	//设备忙，当设备已经在录音的时候再次指示其同类型(文件与文件、STREAM与STREAM)的录音，就会返回此错误码
		UBOX_ERR_LINE_NOT_FOUND         = -14,
		UBOX_ERR_USING                  = -15,    //不支持该功能,错误使用
		UBOX_ERR_EEPROM_ERROR           = -16,

	}UBOX_ERROR_CODE;

	typedef enum ENUM_UBOX_ALARM
	{
		UBOX_ALARM_CAN_FIND_MIC			= 1,	//未能找到 ubox 的 MIC 设备
		UBOX_ALARM_CAN_OPEN_MIC			= 2,	//未能打开 ubox 的 MIC 设备
		UBOX_ALARM_CAN_OPEN_PLAY        = 3,    //未能打开 ubox 的 放音 设备
		UBOX_ALARM_DEVICE_ERROR			= 4,	//设备故障
		UBOX_WIN7_AUDIO_EXCEPTION       = 5,    //Vista 和win7 audio 设备故障， 需要重新调用ubox_close,然后调用ubox_open
		UBOX_ALARM_RESET_AUDIO_FAILD     =6,    //复位 audio device失败
		UBOX_ALARM_RESET_AUDIO_SUCCESS   =7,    //复位 audio device 成功



	}UBOX_ALARM;


   typedef enum ENUM_UBOX_TALK_LINK
	{
		SLIC_TO_GSM	= 0,		//SLIC到GSM方向
		GSM_TO_SLIC = 1,	    //GSM到SLIC方向
		EARPHONE_TO_GSM	= 2,	//耳麦到GSM方向
		GSM_TO_EARPHONE =3,     //GSM到耳麦方向
		SLIC_TO_EARPHONE = 4,    //电话机坐席到耳麦方向
		EARPHONE_TO_SLIC = 5,     //G耳麦到电话机坐席方向
		USB_TO_EARPHONE = 6,     //USB到耳麦方向     用于电脑播放语音
		USB_TO_GSM = 7,          //USB到GSM方向       用于电脑播放语音
		USB_TO_SLIC = 8,          //USB到电话机坐席方向   用于电脑播放语音

	}UBOX_TALK_LINK;

   typedef enum ENUM_UBOX_REC_SWITCH
	{
		SLIC_REC_	= 0,		//SLIC（电话机方向）录音
		GSM_REC = 1,	         //GSM录音
		EARPHONE_REC	= 2,	//Earphone（耳麦）录音


	}UBOX_REC_SWITCH;

	//事件回调函数
	typedef void ( CALLBACK* UBoxEventNotifyProc )( 
		UBOX_HANDLE uboxHnd                    //设备句柄
		, int eventID                          //事件，参考UBOX_EVENT的定义
		, unsigned long param1                 //下面几个参数不同的事件，其含义不同
		, unsigned long param2          
		, unsigned long param3
		, unsigned long param4
		);



/*注意事项:

   插上USB录音盒硬件会成为系统默认录音设备。硬件版本号3.0以上会修改默认放音设备，软件启动后不能保证修改成系统原来的默认放音
   vista就不能修改。二次开发的软件，在软件帮助中需要告诉用户修改默认录放音频设备。在“控制面板”->“声音、语音和音频设备"->“声音、音频设备属性”
   ->"音频"，从设备列表中选择默认声音播放和录音设备。

*/


//ubox_open:
//功能：proc 回调函数
//参数：mode 设置 ubox 的工作模式，通常的方式是录音方式
//说明：这个函数成功调用并不表示USB设备打开成功,事件UBOX_EVENT_DEVICE_PLUG_IN通知上层程序，设备已插入
// 收到UBOX_EVENT_ALARM和UBOX_EVENT_DEVICE_ERROR，上层应用程序要对它们处理，否则不能正确工作，参考这个两个事件的说明
//所有其他函数都必须在 ubox_open() 之后才能使用，
//      否则，对于返回类型为 int 的函数将返回 UBOX_ERR_SYSTEM，
//      对于返回类型为 UBOX_HANDLE 的函数将返回 INVALID_UBOX_HANDLE。
 int	WINAPI	ubox_open(UBoxEventNotifyProc proc, UBOX_WORK_MODE mode);


 void WINAPI	ubox_close(void);

//ubox_get_work_mode:
//功能：返回当前工作模式
//返回：UBOX_WORK_MODE
 
int			WINAPI			ubox_get_work_mode( void );


//ubox_check_coder:
//功能：检查指定的语音编码是否合法
//返回：0 语音编码是合法的，
//      UBOX_ERR_INVALID_VOICE_CODER  语音编码不合法
//说明：此函数可工作在任何模式。
 
int		WINAPI				ubox_check_coder( int coder );


//ubox_get_line_state:
//功能：
//说明：此函数必需在 UBOX_MODE_RECORD 和 UBOX_MODE_DIAG 模式下使用，否则返回 UBOX_ERR_INVALID_WORK_MODE。
 
int			WINAPI			ubox_get_line_state( UBOX_HANDLE uboxHnd);


//ubox_record_file:
//功能：
//说明：此函数必需在 UBOX_MODE_RECORD 和 UBOX_MODE_DIAG 模式下使用，否则返回 UBOX_ERR_INVALID_WORK_MODE。
//第三个参数参考VOICE_CODER
 int	WINAPI	ubox_record_file(UBOX_HANDLE uboxHnd, const char* filename, int coder );


//ubox_record_stream:
//功能： 开始流式录音，第三个参数参考VOICE_CODER，语音数据以UBOX_EVENT_STREAM_VOICE事件通知
//说明：此函数必需在 UBOX_MODE_RECORD 和 UBOX_MODE_DIAG 模式下使用，否则返回 UBOX_ERR_INVALID_WORK_MODE。
 int	WINAPI	ubox_record_stream(UBOX_HANDLE uboxHnd, int coder );


//ubox_stop_record:
//功能：停止文件和流式录音
//说明：此函数必需在 UBOX_MODE_RECORD 和 UBOX_MODE_DIAG 模式下使用，否则返回 UBOX_ERR_INVALID_WORK_MODE。
 int	WINAPI	ubox_stop_record(UBOX_HANDLE uboxHnd);


//注意：停止使用
//ubox_set_volume:
//功能：设置音量，设置音量为0db就可以了，
//说明：volume取值范围0-19db
 int	WINAPI	ubox_set_volume(UBOX_HANDLE uboxHnd,int volume );


 //注意：停止使用
//ubox_set_volume:
//功能：设置放音音量

//说明：volume取值范围-12db-6db   ,对于3101，3102，3002 volume值为0-20，系统默认值是10
 int	WINAPI	ubox_set_Speakervolume(UBOX_HANDLE uboxHnd, int volume );


//ubox_get_hang_threshold:
//功能：读取悬空门限值
//说明：此函数必需在 UBOX_MODE_CONFIG 模式下使用，否则返回 UBOX_ERR_INVALID_WORK_MODE。
 int	WINAPI	ubox_get_hang_threshold(UBOX_HANDLE uboxHnd );



//ubox_set_hang_threshold:
//功能：设置悬空门限值，参考ubox_set_hookoff_threshold中的说明

 int	WINAPI	ubox_set_hang_threshold(UBOX_HANDLE uboxHnd, int threshold );



//ubox_get_hookoff_threshold:
//功能：读取摘机门限值
//说明：此函数必需在 UBOX_MODE_CONFIG 模式下使用，否则返回 UBOX_ERR_INVALID_WORK_MODE。
 int	WINAPI	ubox_get_hookoff_threshold(UBOX_HANDLE uboxHnd);



//ubox_set_hookoff_threshold:
//功能：设置摘机门限值，threshold的值是稳定摘机电压和挂机电压的之和的一半，摘机电压和挂机电压测量调用ubox_start_read_line_voltage
//和ubox_stop_read_line_voltage，参考这个两个函数的用法.

 int	WINAPI	ubox_set_hookoff_threshold(UBOX_HANDLE uboxHnd, int threshold );




/*硬件是通过压控方式检测电话状态,通常情况下,挂机线路直流电压48V左右,摘机线路直流电压会降到6V左右。USB录音盒设置默认摘机门限值为18V, 
当线路电压大于18V,软件判断为挂机状态,小于18V软件判断为摘机状态。由于电话线的所处的环境不同,线路直流电压值不同,可能摘机线路电压要
大于摘机门限值,或者挂机电压小于摘机门限值,这样软件不能正确检测到电话状态,需要重新设置摘机门限值*/
//功能：开始检测线路电压，每隔200ms送上UBOX_EVENT_LINE_VOLTAGE事件通知,回调函数中param1就是线路电压值，剩下的参数没有用
//       线路电压有一定波动，必须测量一段时间，取平均值，必须调用结束检测线路电压函数
// 成功返回UBOX_ERR_SUCCESS，错误返回为非0
 int	WINAPI	ubox_start_read_line_voltage(UBOX_HANDLE uboxHnd);


//功能：结束检测线路电压，成功返回UBOX_ERR_SUCCESS，错误返回为非0
 int	WINAPI	ubox_stop_read_line_voltage(UBOX_HANDLE uboxHnd);

//功能：在设备打开后，才可以获取硬件的版本号，成功返回UBOX_ERR_SUCCESS，错误返回为非0   version_num由整数部分和1位小数部分组成，
//整数部分是主版本号，小数部分是次版本号
//参数说明：第一个参数是设备句柄，第二个参数是获取版本号，假如你的设备句柄是2，定义float versionnum，调用ubox_get_device_versionnum（2，versionnum）
 int      WINAPI    ubox_get_device_versionnum(UBOX_HANDLE uboxHnd,float &version_num);


//功能：在设备打开后，手动摘电话机，上层应用软件自动拨号，成功返回UBOX_ERR_SUCCESS，错误返回为非0，硬件版本号小于3.0不支持拨号功能
//参数说明：第一个参数是设备句柄，第二个参数是拨号的号码，假如你的设备句柄是2，要拨打10000，调用ubox_send_dtmf（2，"10000"）

 int      WINAPI    ubox_send_dtmf(UBOX_HANDLE uboxHnd,const char* dmftfstring);



//功能：在设备打开后，播放语音文件，该PC具有音频文件的解码器都能播放。成功返回UBOX_ERR_SUCCESS，错误返回为非0
//注意：一边播放文件，会影响录音的效果。放音通道是单声道，硬件版本号小于3.0不支持放音功能
 int WINAPI ubox_play_file(UBOX_HANDLE uboxHnd,const char* filename);

//功能：在设备打开后，停止播放，成功返回UBOX_ERR_SUCCESS，错误返回-1 
 int WINAPI ubox_stop_play(UBOX_HANDLE uboxHnd);

//功能：在设备打开后，正在播放，调用这个函数暂停，再调用一次，又继续播放，成功返回UBOX_ERR_SUCCESS，错误返回为非0
 int  WINAPI ubox_play_pause(UBOX_HANDLE uboxHnd);


//功能：在设备成功打开后，打开和关闭AGC,第二参数为true,关闭agc,为false时，打开agc,默认情况下是打开agc.成功返回UBOX_ERR_SUCCESS，错误返回为非0 
 int WINAPI  ubox_close_agc(UBOX_HANDLE uboxHnd,bool bclose);


//功能：在设备成功打开后，此函数必需在 UBOX_MODE_CONFIG 模式下使用,读取eeprom区域的数据，成功返回UBOX_ERR_SUCCESS，错误返回为非0,
//最后三个参数输入不正确，返回UBOX_ERR_INVALID_PARAMETER
//addr地址范围为0x00-0x07,必须在这个范围内，读取数据最大长度为8个字节,第三个参数为读取数据的地址
//用法：假如uboxHnd＝1，addr=0x00,unsigned char readdata[8]
//ubox_read_eeprom(1,0x00,&readata[0],8),调用成功后，读取的数据在readdata中
 int WINAPI ubox_read_eeprom(UBOX_HANDLE uboxHnd,unsigned char addr,unsigned char* outdata,int len);

//功能：在设备成功打开后，此函数可在任何模式下使用,写入eeprom区域的数据，成功返回UBOX_ERR_SUCCESS，错误返回为非0，
//最后三个参数输入不正确，返回UBOX_ERR_INVALID_PARAMETER
//addr地址范围为0x00-0x08,必须在这个范围内，写入数据最大长度为8个字节,第三个参数为写入数据的地址
//用法：假如uboxHnd＝1，addr=0x00,unsigned char writedata[8] ={0x01,0x20,0x30,0x31,0x32,0x33,0x40,0x70}
//ubox_write_eeprom(1,0x00,&writedata[0],8),可以在同一个地址区域调用ubox_read_eeprom验证，读取的数据和写入数据是否相等
 int WINAPI ubox_write_eeprom(UBOX_HANDLE uboxHnd,unsigned char addr,unsigned char* indata,int len);


//功能：在设备成功打开后，此函数可在任何模式下使用,读取eeprom区域的数据，成功返回UBOX_ERR_SUCCESS，错误返回为非0,
//最后三个参数输入不正确，返回UBOX_ERR_INVALID_PARAMETER
//addr地址范围为0x00-0x08,必须在这个范围内，读取数据最大长度为8个字节,并且addr+len不要大于8，第三个参数为读取数据的地址
//用法：假如uboxHnd＝1，addr=0x00,unsigned char readdata[8]
//ubox_read_eeprom(1,0x00,&readata[0],8),调用成功后，读取的数据在readdata中
//注意调用ubox_write_eeprom写成功后，读取其正确值，必须在软件重新启动后，调用ubox_read_eepromEx才能正确读取上次修改的值。
 
 int WINAPI ubox_read_eepromEx(UBOX_HANDLE uboxHnd,unsigned char addr,unsigned char* outdata,int len);


 //功能：在设备成功打开后，软件摘机，成功返回UBOX_ERR_SUCCESS，错误返回为非0
 //注意：必须在硬件版本3.0以上才支持
 int WINAPI ubox_soft_hook_off(UBOX_HANDLE uboxHnd);

 //功能：在设备成功打开后，软件挂机，成功返回UBOX_ERR_SUCCESS，错误返回为非0
  //注意：必须在硬件版本3.0以上才支持
 int WINAPI ubox_soft_hook_on(UBOX_HANDLE uboxHnd);

 ////功能：在设备成功打开后，此函数读取用户号，成功返回用户号长度，错误返回为小于0的数,
 //用户号的长度是8个字节,所以 参数len不小于8, user-num可用地址空间不能小于8个字节。

 // 如果需要用户号请联系我公司
 int WINAPI ubox_get_usernum(UBOX_HANDLE uboxHnd,unsigned char* user_num,int len);


//功能：在设备成功打开后，如果忙音收不到，才需要设置该参数，此函数设置忙音参数，成功返回UBOX_ERR_SUCCESS，错误返回为非0,

 int WINAPI  ubox_set_busy_tone(UBOX_HANDLE uboxHnd,const tagBusyInfo busyinfo);

 //功能： 在设备成功打开后，获取设备名字
 //返回值是设备名字的长度，设备名字为Fi3001B 是1路高阻录音 设备名字为Fi3002B 是2路高阻录音 设备名字为Fi3102A 是两路外线 设备名字为Fi3101A 是1路带耳麦
int  WINAPI  ubox_get_product_name(UBOX_HANDLE uboxHnd, char* product_name);

//功能：在设备成功打开后，此函数设置留言模式参数，bset=true 打开留言参数，bset=false 关闭留言参数，成功返回UBOX_ERR_SUCCESS，错误返回为非0,
//注意：需要设置留言模式下才需要打开留言参数。
 //要退出留言模式，必须关闭留言参数，否则麦克风不能用
 int WINAPI  ubox_set_message_param(UBOX_HANDLE uboxHnd,bool bset);



 //功能：在设备成功打开后，此函数用于是否打开蜂鸣器，bset=true 蜂鸣器，bset=false 关闭蜂鸣器，成功返回UBOX_ERR_SUCCESS，错误返回为非0,
//注意：默认是关闭蜂鸣器。其作用只接耳麦时，来电时提示用户，如果蜂鸣器已打开，振铃时蜂鸣器会响。
 
 int WINAPI  ubox_open_buzzer_switch(UBOX_HANDLE uboxHnd,bool bset);

//获取产品ID号，返回值就是产品ID,对应的值如下：

//  1             FI3102A   2路USB 外线
//	2             FI3002B   2路USB录音盒
//  3             FI3001B   1路USB录音盒
//	4             FI3101A   带耳麦的USB语音盒（1外1内）

int WINAPI  ubox_get_product_ID(UBOX_HANDLE uboxHnd);

//打开日志文件，该函数可以在调用ubox_open之前调用
//level=0,  显示所有日志信息
//level =1, 显示错误和警告信息显示
void WINAPI  ubox_open_logfile(long level);

//关闭日志文件
void WINAPI  ubox_close_logfile();

//打开日志文件，该函数可以在调用ubox_open之前调用
//dir:记录日志文件的路径,如果为空，就是当前程序目录下。
//level=0,  显示所有日志信息
//level =1, 显示错误和警告信息显示
void WINAPI  ubox_open_logfileEx(const char* dir, long level);


int WINAPI ubox_write_usernum(UBOX_HANDLE uboxHnd,unsigned char* user_num,int len);

/*

功  能：PUT上传录音文件。
参  数：uploadUrl： 上传文件使用的URL（形如192.168.1.1）
paramName:  提交http请求时，上传文件在服务器上名字，可以包括目录，目录必须是存在的。
        uploadFilePath：   待上传的文件全路径（形如D:\\recordFile.wav）
返  回：上传成功返回0，失败返回负数。


*/

int WINAPI ubox_uploadFile(LPCTSTR uploadUrl, LPCTSTR paramName, LPCTSTR uploadFilename);



/*

功  能：POST上传录音文件。
参  数：uploadUrl： 上传文件使用的URL（形如192.168.1.1）
paramName:  提交http请求时，上传文件在服务器上名字，可以包括目录，目录必须是存在的。
        uploadFilePath：   待上传的文件全路径（形如D:\\recordFile.wav）
返  回：上传成功返回0，失败返回负数。


*/

//int WINAPI ubox_uploadFileEx(LPCTSTR uploadUrl, LPCTSTR paramName, LPCTSTR uploadFilename);
/*
    该函数修改拨号参数，同时修改ubox.ini文件中的参数
   tone_time :dtmf音调长度 默认是100ms   支持80-150
   silence_time： dtmf音调长度 默认是80ms   支持50-200
   dtmf_cof:     dtmf系数，默认是1.26, 还可以选择为1
   dtmf_scale:  dtmf幅度，默认是220， 范围是（190-240）
   speaker_volume： 拨号放音音量，默认是10  范围是（5-18）
  */
int  WINAPI  ubox_set_send_dtmf_param(UBOX_HANDLE uboxHnd, int tone_time, int silence_time, float dtmf_cof, int dtmf_scale,int speaker_volume);

int  WINAPI  ubox_get_send_dtmf_param(int& tone_time, int& silence_time, float& dtmf_cof, int& dtmf_scale,int& speaker_volume);

int  WINAPI  ubox_delete_file(LPCTSTR filename);
//int  WINAPI  ubox_judge_file_exist(LPCTSTR filename);
int  WINAPI  ubox_judge_file_size(LPCTSTR filename);

char*    WINAPI   ubox_get_disk_info(void); 
char*    WINAPI   ubox_get_system(void) ; 

//Fi3002B 版本7.07 版本才支持
char*    WINAPI   ubox_get_serial_number(UBOX_HANDLE uboxHnd) ; 

//Fi3301  支持的函数

int       WINAPI   ubox_makecall(UBOX_HANDLE uboxHnd, char* phonenumber);
int       WINAPI   ubox_reject_call(UBOX_HANDLE uboxHnd);

int       WINAPI    ubox_set_talk_link(UBOX_HANDLE uboxHnd, int mode, int value);   //设定通话link 开关
int       WINAPI    ubox_makecallSlic(UBOX_HANDLE uboxHnd, int  ringtime, int stopringtime, char* phonenumber);
int       WINAPI    ubox_set_record_enable(UBOX_HANDLE uboxHnd, int mode, int value);   // 设定录音开关


int       WINAPI    ubox_gsm_power(UBOX_HANDLE uboxHnd, int value);  //0：GSM模块断电， 1：GSM模块上电
int       WINAPI    ubox_gsm_bootkey(UBOX_HANDLE uboxHnd, int value);  //1：GSM开机键， 延时按1~2s,在调用释放命令,  0:GSM开机键释放

int       WINAPI    ubox_feed_slic_polarity(UBOX_HANDLE uboxHnd, int value);  //0：slic正向馈电,  1:slic反向馈电

/*

*/
int       WINAPI    ubox_send_gsm_cmd(UBOX_HANDLE uboxHnd, char* cmd, int len);                   //发送GSM命令，供调试GSM模块使用

int       WINAPI    ubox_send_gsm_msg(UBOX_HANDLE uboxHnd, int mode, char* phonenumber, char* msg, int len);   //发短信,一条短信不要超过70个字
/*
查询GSM设备可存储短信数目和目前有多少条短信
*/
int       WINAPI    ubox_query_gsm_msg_number(UBOX_HANDLE uboxHnd);  

/*
按照索引值，该数值通过ubox_query_gsm_msg_number获取， index从1开始，查询GSM设备内短信内容


*/
int       WINAPI    ubox_query_gsm_msg(UBOX_HANDLE uboxHnd, int index);     //短信内容是unicode方式，需要应用软件再转换

int       WINAPI    ubox_query_gsm_msgEx(UBOX_HANDLE uboxHnd, int index);   //短信内容已经转换为多字节方式

/*删除短信数目
msgtype=0, index是删除单条短信的序号,msgtype为其它值，index设为1
msgtype=1, 删除所有的已经阅读的短消息
msgtype=2, 删除所有的已经阅读和发送出去的短消息
msgtype=3, 删除所有的已经阅读过、已经发送出去的和未发送的短消息
msgtype=4, 删除所有的短消息
*/
int       WINAPI    ubox_delete_gsm_msg(UBOX_HANDLE uboxHnd, int index, int msgtype);

 //设备是单模，支持双卡，0:选择sim卡1， 1：选择sim卡2
// 选择卡后，需要给GSM模块断电，上电，然后调用GSM开机键 ubox_gsm_bootkey(1),延时2秒，最后开机键释放ubox_gsm_bootkey(0)
int       WINAPI    ubox_select_simcard(UBOX_HANDLE uboxHnd, int simcardno);  

/*
设置GSM输出和输入音量， 
type:0 输入音量      0-10
type:1：输出音量     0-100

*/
int       WINAPI    ubox_set_gsm_vol(UBOX_HANDLE uboxHnd, int type, int vol); 

/*
type:0 输入音量 
type:1：输出音量
获取GSM输出和输入音量，以事件UBOX_EVENT_GSM_VOL_SIZE通知
*/
int       WINAPI    ubox_get_gsm_vol(UBOX_HANDLE uboxHnd, int type);  

/*
type: 0  耳麦模式， 1：电话机模式
设置耳麦和slic电话机工作模式
type      mode
  0        1        耳麦自动模式，有电话呼入，按耳麦线按钮，电话摘机，再按按一次，挂断GSM通话
  0        1        关闭耳麦自动模式

  1         1       话机自动模式，电话呼入，电话机振铃，电话机挂机，挂断GSM通话

  1         0       关闭话机自动模式
*/

int       WINAPI    ubox_set_gsm_work_mode(UBOX_HANDLE uboxHnd, int type, int mode);

/*
 让GSM模块产生本地定制单音， 用于电话呼入的时候，耳麦里面能够听到声音，提醒有来电 
mode           0    停止播放 
              1  开始播放 
freq         播放单音频率 
periodon    一个周期内播放单音的时长 
periodoff   一个周期内静音的时长 
duration   单音播放总时长，单位为毫秒 
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
			os << "状态=" << me.state_code_ << " : 空设备";	
			break;
		case UBOX_STATE_RESET:
			os << "状态=" << me.state_code_ << " : 复位";	
			break;
		case UBOX_STATE_RINGING:
			os << "状态=" << me.state_code_ << " : 振铃";	
			break;
		case UBOX_STATE_HOOK_OFF:
			os << "状态=" << me.state_code_ << " : 摘机";	
			break;
		case UBOX_STATE_HANG:
			os << "状态=" << me.state_code_ << " : 悬空";	
			break;

		case UBOX_STATE_REVERSE_HOOKOFF:
			os << "状态=" << me.state_code_ << " : 反向摘机";	
			break;
		case UBOX_STATE_POSITIVIE_HOOKOFF:
			os << "状态=" << me.state_code_ << " : 正向摘机";	
			break;

	/*	case UBOX_STATE_TELEPHONE_HOOKON:
             os << "状态=" << me.state_code_ << " : 电话机挂机";	
			break;*/
		default:
			os << "状态=" << me.state_code_ << " : 未定义";	
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
			os << "事件=" << me.event_code_ << " : 设备插入";	
			break;
		case UBOX_EVENT_DEVICE_PLUG_OUT:
			os << "事件=" << me.event_code_ << " : 设备拔出";	
			break;

		case UBOX_EVENT_LINE_RESET:
			os << "事件=" << me.event_code_ << " : 线路复位";	
			break;

		case UBOX_EVENT_LINE_RINGING:
			os << "事件=" << me.event_code_ << " : 线路振铃";	
			break;

		case UBOX_EVENT_LINE_HOOK_OFF:
			os << "事件=" << me.event_code_ << " : 线路摘机";	
			break;

		case UBOX_EVENT_LINE_HANG://检测到线路悬空
			os << "事件=" << me.event_code_ << " : 线路悬空";	
			break;


		case UBOX_EVENT_STREAM_VOICE:
			os << "事件=" << me.event_code_ << " : 实时语音";	
			break;


		case UBOX_EVENT_CALLER_ID:
			os << "事件=" << me.event_code_ << " : 来电号码";	
			break;

		case UBOX_EVENT_DTMF_DOWN:
			os << "事件=" << me.event_code_ << " : DTMF按下";	
			break;

		case UBOX_EVENT_DTMF_UP:
			os << "事件=" << me.event_code_ << " : DTMF释放";	
			break;

		case UBOX_EVENT_ALARM:
			os << "事件=" << me.event_code_ << " : 警报通知";	
			break;

		case UBOX_EVENT_RING_CANCEL:
			os << "事件=" << me.event_code_ << " : 振铃取消";	
			break;

		default:
			os << "事件=" << me.event_code_ << " : 未定义的事件码";	
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
			os << "错误码=" << me.err_code_ << " : 操作成功";	
			break;
		case UBOX_ERR_SYSTEM:
			os << "错误码=" << me.err_code_ << " : 系统错误";	
			break;
		case UBOX_ERR_DEVICE_NOT_FOUND:
			os << "错误码=" << me.err_code_ << " : 无此设备";	
			break;
		case UBOX_ERR_INVALID_HANDLE:
			os << "错误码=" << me.err_code_ << " : 非法的 UBOX_HANDLE";	
			break;
		case UBOX_ERR_INVALID_PARAMETER:
			os << "错误码=" << me.err_code_ << " : 非法参数";	
			break;
		case UBOX_ERR_CANNOT_CREATE_DIR:
			os << "错误码=" << me.err_code_ << " : 未能创建目录";	
			break;
		case UBOX_ERR_CANNOT_CREATE_FILE:
			os << "错误码=" << me.err_code_ << " : 未能创建录音文件";	
			break;
		case UBOX_ERR_INVALID_VOICE_CODER:
			os << "错误码=" << me.err_code_ << " : 不支持的语音编码";	
			break;
		case UBOX_ERR_INVALID_WORK_MODE:
			os << "错误码=" << me.err_code_ << " : 错误的工作模式";	
			break;
		case UBOX_ERR_EXCEPTION:
			os << "错误码=" << me.err_code_ << " : 发生异常";	
			break;
		case UBOX_ERR_DEVICE_BUSY:
			os << "错误码=" << me.err_code_ << " : 设备忙";	
			break;
		case UBOX_ERR_UBOX_NOT_OPEN:
			os << "错误码=" << me.err_code_ << " : ubox设备尚未打开";	
			break;


		default:
			os << "错误码=" << me.err_code_ << " : 未定义的错误码";	
			break;
		}
		return os;
	}
};

/*
ubox_err 使用范例：

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
