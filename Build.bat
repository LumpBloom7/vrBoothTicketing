cls
@echo off
set "PROJECTDIR=%CD:\=/%"

REM Set you compiler path here, or leave blank if already in PATH
cd %CD:~0,2%/Compilers/MinGW64/bin/


set "bash=%cd%/bash/"
set "GIT=%CD:~0,2%/Software/Git/Bin/"

REM GETTING GIT INFO
(%GIT%git.exe -C %PROJECTDIR% --no-pager describe --tags --always )> tmpfile
set /p GITVER=<tmpFile
del tmpfile
(%GIT%git.exe -C %PROJECTDIR% rev-parse --verify HEAD)> tmpfile
set /p GITCOM=<tmpFile
del tmpfile
(%GIT%git.exe -C %PROJECTDIR% --no-pager show --date=iso-strict --format="%%ad" --name-only)> tmpfile
set /p GITDATE=<tmpFile
del tmpfile
(%bash%date.exe --iso=seconds)> tmpfile
set /p BUILDDATE=<tmpFile
del tmpfile
(%GIT%git.exe -C %PROJECTDIR% status --porcelain)> tmpfile
set /p GITSTATUS=<tmpFile
for /f %%i in ("tmpfile") do set size=%%~zi
if %size% gtr 0 set "GITVER=%GITVER%-D"
del tmpfile


make %1 %2 -f %PROJECTDIR%/makefile OLDDIR=%PROJECTDIR% GIT_VERSION=%GITVER% GIT_COMMIT=%GITCOM% BUILD_DATE=%BUILDDATE% GIT_DATE=%GITDATE%