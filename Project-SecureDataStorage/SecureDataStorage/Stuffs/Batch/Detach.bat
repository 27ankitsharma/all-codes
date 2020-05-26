@ECHO off
set /p vhdname="Please enter drive name: "
set TargetDrive=E:
set VHDFolder=\Project\SecureDataStorage\SecureDataStorage\Stuffs\VHD
IF EXIST Diskpart-Detach.txt DEL Diskpart-Detach.txt
ECHO select vdisk file=%TargetDrive%%VHDFolder%\%vhdname%.vhd > Diskpart-Detach.txt
ECHO detach vdisk >> Diskpart-Detach.txt
diskpart /s Diskpart-Detach.txt
echo The drive associated with file name "%vhdname%" has been successfully dismounted.
pause