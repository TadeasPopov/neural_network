@echo off

set "do_configure=0"
set "do_build=0"
set "do_run=0"
set "do_release=0"

if "%1" == "-c" (
	set "do_configure=1"
)
if "%2" == "-c" (
	set "do_configure=1"
)
if "%3" == "-c" (
	set "do_configure=1"
)
if "%4" == "-c" (
	set "do_configure=1"
)

if "%1" == "-b" (
	set "do_build=1"
)
if "%2" == "-b" (
	set "do_build=1"
)
if "%3" == "-b" (
	set "do_build=1"
)
if "%4" == "-b" (
	set "do_build=1"
)

if "%1" == "-r" (
	set "do_run=1"
)
if "%2" == "-r" (
	set "do_run=1"
)
if "%3" == "-r" (
	set "do_run=1"
)
if "%4" == "-r" (
	set "do_run=1"
)

if "%1" == "-R" (
	set "do_release=1"
)
if "%2" == "-R" (
	set "do_release=1"
)
if "%3" == "-R" (
	set "do_release=1"
)
if "%4" == "-R" (
	set "do_release=1"
)

if "%1" == "-a" (
	set "do_configure=1"
	set "do_build=1"
	set "do_run=1"
)
if "%2" == "-a" (
	set "do_configure=1"
	set "do_build=1"
	set "do_run=1"
)
if "%3" == "-a" (
	set "do_configure=1"
	set "do_build=1"
	set "do_run=1"
	set "do_release=1"
)

if %do_configure% == 1 (
	echo configuring...
	cmake -S ./ -B ./build -Dbuild_src=ON --log-level=VERBOSE || goto :error
	echo configuring - DONE
)
if %do_build% == 1 (
	echo building...

	if %do_release% == 1 (
		MSBuild.exe ./build/neural-network.sln /p:configuration=release || goto :error
	) else (
		MSBuild.exe ./build/neural-network.sln /p:configuration=debug || goto :error
	)
	echo building - DONE
)
if %do_run% == 1 (
	echo running...
	if %do_release% == 1 (
		"build/Release/neural-network.exe" || goto :error
	) else (
		"build/Debug/neural-network.exe" || goto :error
	)
)
goto :EOF

:error
echo Failed with error: #%errorlevel%.
exit /b %errorlevel%
