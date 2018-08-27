@echo off
IF NOT DEFINED clset (call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64)

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl -nologo -FC -Zi -DINDIE_SLOW=1 -DRUN_INDIE_TESTS=1 /EHsc /I ..\include ..\code\indie_entry.cpp /link /libpath:..\lib SDL2main.lib SDL2.lib opengl32.lib /SUBSYSTEM:CONSOLE
popd