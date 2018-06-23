cls
@echo off
set "PROJECTDIR=%CD:\=/%"

REM Set you compiler path here, or leave blank if already in PATH
set "COMPILERDIR=%CD:~0,2%/Compilers/MinGW64/bin/"
cd %COMPILERDIR%


REM Set you GIT path here, or leave blank if already in PATH
set "GIT=%CD:~0,2%/Software/Git/"


make %1 %2 -f %PROJECTDIR%/makefile PROJECTDIR=%PROJECTDIR% COMPILERDIR=%COMPILERDIR% GITDIR=%GIT%