; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "思方来电助手"
#define MyAppVersion "1.0.2"
#define MyAppPublisher "思方软件科技有限公司"
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
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
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
Name: "DesktopIcon"; Description: "创建桌面快捷方式"  

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

; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

