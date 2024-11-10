@echo off
set CC=gcc
set CFLAGS=-Wall -Wextra -g
set TARGET=1320project.exe
set SRCS=1320project.c 

%CC% %CFLAGS% %SRCS% -o %TARGET%

if %ERRORLEVEL% equ 0 (
    echo Compilation successful. Running the program...
    %TARGET%
) else (
    echo Compilation failed.
)
