; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "˼����������"
#define MyAppVersion "1.0.2"
#define MyAppPublisher "˼������Ƽ����޹�˾"
#define MyAppURL "http://www.sifangerp.com/"
#define MyAppExeName "SfClient.exe"

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
LicenseFile=D:\work\Doc\Э��.txt
OutputDir=C:\Users\spplus\Desktop
OutputBaseFilename=˼����������
SetupIconFile=D:\work\SfClient\images\logo.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "D:\work\bin\SfClient.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\conf.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\SfClient.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\style.qss"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\updater.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\woodpeckerd.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\msvcp100.dll"; DestDir: "{app}"; Flags: ignoreversion              
Source: "D:\work\bin\msvcr100.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\work\bin\qt_zh_CN.qm"; DestDir: "{app}"; Flags: ignoreversion

; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

