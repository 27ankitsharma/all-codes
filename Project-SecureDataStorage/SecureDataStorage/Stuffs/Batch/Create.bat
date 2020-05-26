@ECHO off

set /p VHD="Enter the name for new Drive: "

set /p Size="Enter the size of Drive in MB(>2): "
set /p drletter="Enter the letter for Drive: "

set TargetDrive=E:
set VHDFolder=\Project\SecureDataStorage\SecureDataStorage\Stuffs\VHD

if exist %TargetDrive%%VHDFolder%\%VHD%.vhd goto ErrorExist



ECHO Creating VHD file %TargetDrive%%VHDFolder%\%VHD%.vhd with a maximum size of %Size%MB 
IF EXIST Diskpart-Create.txt DEL Diskpart-Create.txt
ECHO Timeout /T 10 >> Diskpart-create.txt
ECHO create vdisk file="%TargetDrive%%VHDFolder%\%VHD%.vhd" maximum=%size% type=expandable > Diskpart-create.txt
ECHO select vdisk file="%TargetDrive%%VHDFolder%\%VHD%.vhd" >> Diskpart-create.txt
ECHO attach vdisk >> Diskpart-create.txt
ECHO create partition primary >> Diskpart-create.txt
ECHO format FS=NTFS label=%VHD% >> Diskpart-create.txt

ECHO assign letter=%drletter% >> Diskpart-create.txt
ECHO active >> Diskpart-create.txt

ECHO exit >> Diskpart-create.txt


diskpart /s Diskpart-create.txt


