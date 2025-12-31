@echo off
REM 切换到仓库根（批文件位于 Scripts）
pushd "%~dp0\.."

REM 预期 premake 路径（相对于仓库根）
set "PREMAKE_PATH=%CD%\Programs\ThirdParty\premake\bin\premake5.exe"

if not exist "%PREMAKE_PATH%" (
    echo Premake not found at "%PREMAKE_PATH%".
    echo Please ensure premake5.exe is located under Programs\ThirdParty\premake\bin.
    popd
    exit /b 1
)

echo Using Premake: "%PREMAKE_PATH%"
REM 根据你的项目需要调整下面的动作（例如 vs2019 / vs2022 等）
"%PREMAKE_PATH%" vs2022
set "RC=%ERRORLEVEL%"

REM 如果传入 nopause 则直接退出
if /I "%~1"=="nopause" (
    popd
    exit /b %RC%
)

echo.
if %RC% EQU 0 (
    echo Generating projects completed.
) else (
    echo Premake returned error code %RC%.
)
echo Press any key to continue . . .
pause >nul
popd
exit /b %RC%