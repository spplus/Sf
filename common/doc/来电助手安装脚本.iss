; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "˼����������"
#define MyAppVersion "1.0.2"
#define MyAppPublisher "˼������Ƽ����޹�˾"
#define MyAppURL "http://www.sifangerp.com/"
#define MyAppExeName "telhelper.exe"
#define APP_PATH "F:\Project\src\Sf\bin\"
#define DOC_PATH "F:\Project\src\Sf\common\doc\"
#define OUT_PATH "F:\Project\src\Sf\common\doc"

#define MAINAPP     "telhelper.exe"
#define STYLE       "style.qss"
#define MSVCP       "msvcp100.dll"
#define MSVCR       "msvcr100.dll"
#define CORE        "QtCore4.dll"
#define GUI         "QtGui4.dll"
#define NETWORK     "QtNetwork4.dll"
#define ZHCN        "qt_zh_CN.qm"
#define BRIDGE      "bridge.dll"
#define QNVICCUB    "qnviccub.dll"
#define WEBKIT      "QtWebKit4.dll"



[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{3AB8D1DF-2236-4516-A878-36C7D04FD00A}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir={#OUT_PATH}
OutputBaseFilename={#MyAppName}-v{#MyAppVersion}
SetupIconFile={#DOC_PATH}tel.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks];Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1
Name: "DesktopIcon"; Description: "���������ݷ�ʽ"  

[Files]

Source: {#APP_PATH}{#MAINAPP}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#BRIDGE}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#STYLE}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#QNVICCUB}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#MSVCP}; DestDir: "{app}"; Flags: ignoreversion              
Source: {#APP_PATH}{#MSVCR}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#CORE}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#GUI}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#NETWORK}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#ZHCN}; DestDir: "{app}"; Flags: ignoreversion
Source: {#APP_PATH}{#WEBKIT}; DestDir: "{app}"; Flags: ignoreversion

; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

