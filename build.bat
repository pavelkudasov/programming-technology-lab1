@echo off
chcp 65001 >nul
cd /d "%~dp0"
set "LAB_COMPILER=C:\msys64\mingw64\bin\g++.exe"
if not exist "%LAB_COMPILER%" set "LAB_COMPILER=g++"
"%LAB_COMPILER%" -std=c++17 -Wall -Wextra -Wpedantic -static src\Queue.cpp src\Stack.cpp src\main.cpp -o lab1.exe
if errorlevel 1 (
  echo Ошибка сборки. Нужен компилятор g++.
  pause
  exit /b 1
)
echo Сборка завершена. Для запуска выполните .\lab1.exe
pause
