@echo off


REM Check os version
reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32BIT || set OS=64BIT
if %OS%==32BIT (
    echo Working on 32bit operating system
    set SDL2_LIB_DIR="\dependencies\SDL2\lib\x86"
    set SDL2_ttf_LIB_DIR="\dependencies\SDL2_ttf\lib\x86"
)
if %OS%==64BIT (
    echo Working on 64bit operating system
    set SDL2_LIB_DIR="\dependencies\SDL2\lib\x64"
    set SDL2_ttf_LIB_DIR="\dependencies\SDL2_ttf\lib\x64"
)


SET CFLAGS=/W4 /WX /std:c11 /wd4996 /wd5105 /FC /TC /Zi /nologo

SET INCLUDES=/I ..\dependencies\SDL2\include\SDL2 ^
             /I ..\dependencies\SDL2_ttf\include\^
             /I ..\src\

SET LIBS=..\%SDL2_LIB_DIR%\SDL2.lib ^
         ..\%SDL2_LIB_DIR%\SDL2main.lib ^
         ..\%SDL2_ttf_LIB_DIR%\SDL2_ttf.lib ^
         opengl32.lib User32.lib Gdi32.lib shell32.lib

IF NOT EXIST .\build\ MKDIR .\build\
IF NOT EXIST .\build\fonts\ MKDIR .\build\fonts\

IF NOT EXIST .\build\SDL2.dll (
    COPY .\%SDL2_LIB_DIR%\SDL2.dll .\build\
)
IF NOT EXIST .\build\SDL2_ttf.dll (
    COPY .\%SDL2_ttf_LIB_DIR%\SDL2_ttf.dll .\build\
)

COPY .\fonts\* .\build\fonts\


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
