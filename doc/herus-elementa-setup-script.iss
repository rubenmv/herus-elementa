; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{0D43A6EF-CC16-4BE3-A019-F9A74486671D}
AppName=Herus Elementa
AppVersion=0.1
;AppVerName=Herus Elementa 0.1
AppPublisher=4TheLulZ
AppPublisherURL=https://github.com/rubenmv/herus-elementa
AppSupportURL=https://github.com/rubenmv/herus-elementa
AppUpdatesURL=https://github.com/rubenmv/herus-elementa
DefaultDirName={pf}\Herus Elementa
DefaultGroupName=Herus Elementa
LicenseFile=C:\Users\Ruben\Desktop\Herus Elementa Installer\LICENSE.txt
InfoAfterFile=C:\Users\Ruben\Desktop\Herus Elementa Installer\README.txt
OutputDir=C:\Users\Ruben\Desktop\Herus Elementa Setup Compiler
OutputBaseFilename=herus-elementa-installer
SetupIconFile=C:\Users\Ruben\Desktop\Herus Elementa Installer\icon.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\Users\Ruben\Desktop\Herus Elementa Installer\herus-elementa.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\Ruben\Desktop\Herus Elementa Installer\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Herus Elementa"; Filename: "{app}\herus-elementa.exe";  IconFilename: "{app}\icon.ico"
Name: "{group}\{cm:UninstallProgram,Herus Elementa}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Herus Elementa"; Filename: "{app}\herus-elementa.exe";  IconFilename: "{app}\icon.ico"; Tasks: desktopicon

[Run]
Filename: "{app}\herus-elementa.exe"; Description: "{cm:LaunchProgram,Herus Elementa}"; Flags: nowait postinstall skipifsilent

