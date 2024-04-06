@echo off

set directory=%1
set module="%1\makefile.msvc"

echo %1 | find ".." >nul
if errorlevel 1 (set PARENT_DIR=0) else (set PARENT_DIR=1)

if %PARENT_DIR% leq 0 (
    if exist %module% (
        cd %directory%
        nmake /C /S /f makefile.msvc
    )
)