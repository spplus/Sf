; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "˼����������"
#define MyAppVersion "1.0.5"
#define MyAppPublisher "˼������Ƽ����޹�˾"
#define MyAppURL "http://www.sifangerp.com/"
#define MyAppExeName "SfClient.exe"
#define APP_PATH "F:\Project\src\Sf\bin\"
#define DOC_PATH "F:\Project\src\Sf\common\doc\"
#define OUT_PATH "F:\Project\src\Sf\common\doc"

#define SFCLIENT    "SfClient.exe"
#define CONF        "conf.ini"
#define STYLE       "style.qss"
#define UPDATER     "updater.exe"
#define WDP         "woodpeckerd.exe"
#define MSVCP       "msvcp100.dll"
#define MSVCR       "msvcr100.dll"
#define CORE        "QtCore4.dll"
#define GUI         "QtGui4.dll"
#define NETWORK     "QtNetwork4.dll"
#define ZHCN        "qt_zh_CN.qm"




[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{E41FE52B-CC21-4EEF-B455-97CED7EDBBCE}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile={#DOC_PATH}Э��.txt
OutputDir={#OUT_PATH}
OutputBaseFilename={#MyAppName}-v{#MyAppVersion}
SetupIconFile={#DOC_PATH}logo.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

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

; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

