set QMAKE="C:\Qt\qt-5.6.0-x64-msvc2013\5.6\msvc2013_64\bin\qmake.exe"

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64\vcvars64.bat"

%QMAKE% nfd/nfd.pro -spec win32-msvc2013
nmake
