@echo off
copy ..\build32\Release\tempMute.dll plugins\tempMute_win32.dll
copy ..\build64\Release\tempMute.dll plugins\tempMute_win64.dll
set /p build="Build number: "
mkdir releases\%build%
"C:\Program Files\7-Zip\7z.exe" a releases\%build%\tempMute.ts3_plugin -tzip -mx=9 -mm=Deflate ./package.ini plugins/*
pause