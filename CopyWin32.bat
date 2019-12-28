
set root_src_path=%~dp0

echo %root_src_path%\

cd %root_src_path%\

set mx_github_path=%root_src_path%\..\

set miniblink_path=%mx_github_path%\miniblink

rem ----------------
set bin_path=%root_src_path%\bin\win32\debug

xcopy %miniblink_path%\debug\node.dll	%bin_path% /y /e /h
xcopy %miniblink_path%\debug\*.pdb		%bin_path% /y /e /h
rem copy /Y %miniblink_path%\*.*		%bin_path%\

rem ----------------
set bin_path=%root_src_path%\bin\win32\release

xcopy %miniblink_path%\release\node.dll	%bin_path% /y /e /h
xcopy %miniblink_path%\release\*.pdb	%bin_path% /y /e /h
rem copy /Y %miniblink_path%\*.*		%bin_path%\

pause