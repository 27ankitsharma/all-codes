@ECHO Off

set /p VHD="Enter the name of Drive: "



set TargetDrive=E:
set VHDFolder=\Project\SecureDataStorage\SecureDataStorage\Stuffs\VHD

IF NOT EXIST E:\Project\SecureDataStorage\SecureDataStorage\Stuffs\VHD\%VHD.vhd% GOTO END
:END
ECHO There is no drive associated with the input drive name.Please make sure you have created it earlier.


IF EXIST Diskpart-Create.txt DEL Diskpart-Create.txt


ECHO select vdisk file="%TargetDrive%%VHDFolder%\%VHD%.vhd" >> Diskpart-create.txt
ECHO attach vdisk >> Diskpart-create.txt

ECHO exit >> Diskpart-create.txt
echo Drive associated with name="%VHD%" is about to be mounted.
pause


diskpart /s Diskpart-create.txt


