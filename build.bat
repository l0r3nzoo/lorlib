@echo off
if not exist build mkdir build

cl /TC /Zi /Od ^
  /Fo:build\ ^
  /Fd:build\build.pdb ^
  /Fe:build\main.exe ^
  main.c stack.c vector.c dictionary.c queue.c

if errorlevel 1 exit /b 1

echo Build successful
