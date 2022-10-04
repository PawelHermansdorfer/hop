@echo off

SET CFLAGS=/W4 /WX /std:c11 /wd4996 /wd5105 /FC /TC /Zi /nologo

SET INCLUDES=/I ..\dependencies\SDL2\include ^
             /I ..\src\

SET LIBS=..\dependencies\SDL2\lib\x64\SDL2.lib ^
         ..\dependencies\SDL2\lib\x64\SDL2main.lib ^
         opengl32.lib User32.lib Gdi32.lib shell32.lib

IF NOT EXIST .\build\ MKDIR .\build\
IF NOT EXIST .\build\SDL2.dll (
    COPY .\dependencies\SDL2\lib\x64\SDL2.dll .\build\
)

PUSHD .\build

SET mode=%1
IF "%mode%" == "/release" (
    cl.exe %INCLUDES% /Femain ..\src\*.c /link %LIBS% -SUBSYSTEM:windows
)
IF "%mode%" == "/debug" (
    cl.exe %INCLUDES% /Femain ..\src\*.c /link %LIBS% -SUBSYSTEM:console
)
IF "%mode%" == "" (
    cl.exe %INCLUDES% /Femain ..\src\*.c /link %LIBS% -SUBSYSTEM:console
)

POPD
