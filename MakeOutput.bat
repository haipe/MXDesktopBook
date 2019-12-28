
set root_src_path=%~dp0

echo %root_src_path%\

cd %root_src_path%\

set mx_github_path=%root_src_path%\..\

set miniblink_path=%mx_github_path%\miniblink

set output_path=%root_src_path%\bin\win32\output
mkdir %output_path%

set qt_path=E:\Qt\Qt5.12.5\5.12.5\msvc2017\bin\qtenv2.bat

rem ----------------
set bin_path=%root_src_path%\bin\win32\release

xcopy %miniblink_path%\release\node.dll	%output_path% /y /e /h
xcopy %bin_path%\*.exe	%output_path% /y /e /h

start %qt_path%
pause