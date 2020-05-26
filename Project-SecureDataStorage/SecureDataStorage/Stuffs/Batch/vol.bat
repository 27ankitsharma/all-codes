@ECHO Off
IF EXIST vol-info.txt DEL vol-info.txt


echo list volume >> vol-info.txt
ECHO exit >> vol-info.txt

diskpart /s vol-info.txt
pause


