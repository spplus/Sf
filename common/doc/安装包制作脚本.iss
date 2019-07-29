; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "思方工单助手"
#define MyAppVersion "0.9.0"
#define MyAppPublisher "思方网络科技有限公司"
#define MyAppURL "http://www.sifangerp.com/"
#define MyAppExeName "SfClient.exe"
#define APP_PATH "F:\Project\src\Sf\bin\"
#define DOC_PATH "F:\Project\src\Sf\common\doc\"
#define OUT_PATH "F:\Project\src\Sf\common\doc"
#define SOUND_DIR "sound\"
#define INSTALL_PATH "D:\Program Files (x86)\SfErp\"
#define JPEG_PLUGIN_PATH  "plugins\imageformats\"
#define CODE_PLUGIN_PATH  "plugins\codecs\"


#define SFCLIENT    "SfClient.exe"
#define CONF        "conf.ini"
#define STYLE       "style.qss"
#define UPDATER     "updater.exe"
#define WDP         "woodpeckerdn.exe"
#define MSVCP       "msvcp100.dll"
#define MSVCR       "msvcr100.dll"
#define CORE        "QtCore4.dll"
#define GUI         "QtGui4.dll"
#define NETWORK     "QtNetwork4.dll"
#define ZHCN        "qt_zh_CN.qm"
#define DEFALT_SOUND0  "tip0.wav"
#define DEFALT_SOUND1  "tip1.wav"
#define DEFALT_SOUND2  "tip2.wav"
#define DEFALT_SOUND3  "tip3.wav"
#define DEFALT_SOUND4  "tip4.wav"
#define DEFALT_SOUND5  "tip5.wav"
#define DEFALT_SOUND6  "tip6.wav"
#define DEFALT_SOUND7  "tip7.wav"
#define DEFALT_SOUND8  "tip8.wav"
#define DEFALT_SOUND9  "tip9.wav"
#define QJPEG          "qjpeg4.dll"
#define QCNCODECS      "qcncodecs4.dll" 


[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppId={{E41FE52B-CC21-4EEF-B455-97CED7EDBBCE}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={#INSTALL_PATH}
DefaultGroupName={#MyAppName}
LicenseFile={#DOC_PATH}协议.txt
OutputDir={#OUT_PATH}
OutputBaseFilename={#MyAppName}-v{#MyAppVersion}
SetupIconFile={#DOC_PATH}logo.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
;Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1
Name: "DesktopIcon"; Description: "创建桌面快捷方式"  


[Files]
Source: {#APP_PATH}{#SFCLIENT}; DestDir: "{app}"; Flags: ignoreversion
Source: {#DOC_PATH}{#CONF}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#STYLE}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#UPDATER}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#WDP}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#MSVCP}; DestDir: "{app}"; Flags: ignoreversion              
Source: {#APP_PATH}{#MSVCR}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#CORE}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#GUI}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#NETWORK}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#ZHCN}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND0}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND1}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND2}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND3}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND4}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND5}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND6}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND7}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND8}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#SOUND_DIR}{#DEFALT_SOUND9}; DestDir: "{app}\{#SOUND_DIR}"; Flags: ignoreversion
Source: {#APP_PATH}{#JPEG_PLUGIN_PATH}{#QJPEG}; DestDir: "{app}\{#JPEG_PLUGIN_PATH}"; Flags: ignoreversion
Source: {#APP_PATH}{#CODE_PLUGIN_PATH}{#QCNCODECS}; DestDir: "{app}\{#CODE_PLUGIN_PATH}"; Flags: ignoreversion
Source: compiler:IsTask.dll; Flags: dontcopy noencryption

; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Code]
//安装前判断是否有进程正在运行，istask.dll文件与打包的exe文件一起
function RunTask(FileName: string; bFullpath: Boolean): Boolean;
external 'RunTask@files:ISTask.dll stdcall delayload';
function KillTask(ExeFileName: string): Integer;
external 'KillTask@files:ISTask.dll stdcall delayload';

function InitializeSetup(): Boolean;
begin
  Result:= true;
  if RunTask('woodpeckerdn.exe', false) then
      begin
           if MsgBox('安装程序检测到woodpeckerdn正在运行!'#13''#13'点击 "是" 按钮将停止进程然后继续安装;'#13''#13'点击"否" 按钮将终止安装程序!', mbConfirmation, MB_YESNO) = IDYES then
              begin
              KillTask('woodpeckerdn.exe');
              KillTask('woodpeckerdn.exe');
              Result:= true;
              end
           else
              Result:= false;
      end
  else
  Result:= true;
end;


[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

