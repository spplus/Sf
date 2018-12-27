; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "思方工单助手"
#define MyAppVersion "1.0.2"
#define MyAppPublisher "思方网络科技有限公司"
#define MyAppURL "http://www.sifangerp.com/"
#define MyAppExeName "SfClient.exe"

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
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
LicenseFile=D:\work\Doc\协议.txt
OutputDir=C:\Users\spplus\Desktop
OutputBaseFilename=思方工单助手
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

; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

