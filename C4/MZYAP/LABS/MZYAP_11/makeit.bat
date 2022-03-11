@echo off
: -------------------------------
: if resources exist, build them
: -------------------------------
H:\masm32\BIN\rc.exe /v rsrc.rc
H:\masm32\BIN\CVTRES.EXE /machine:ix86 rsrc.res

if exist %1.obj del "project.obj"
if exist %1.exe del "project.exe"

: -----------------------------------------
: assemble Project.asm into an OBJ file
: -----------------------------------------
H:\masm32\BIN\ml.exe /c /coff "project.asm"
if errorlevel 1 goto errasm

: --------------------------------------------------
: link the main OBJ file with the resource OBJ file
: --------------------------------------------------
H:\masm32\BIN\LINK.EXE /SUBSYSTEM:WINDOWS "project.obj" rsrc.obj
if errorlevel 1 goto errlink
dir "project.*"
goto TheEnd

:errlink
: ----------------------------------------------------
: display message if there is an error during linking
: ----------------------------------------------------
echo.
echo There has been an error while linking this project.
echo.
goto TheEnd

:errasm
: -----------------------------------------------------
: display message if there is an error during assembly
: -----------------------------------------------------
echo.
echo There has been an error while assembling this project.
echo.
goto TheEnd

:TheEnd

pause
