@echo off
pushd %~dp0\..\
call .\Vendor\Premake\Binaries\premake5.exe vs2022
popd
pause
