@echo off
pushd %~dp0\..\
call .\Vendor\Premake\Binaries\premake5.exe vs%1
popd
pause
