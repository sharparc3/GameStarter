@echo off

set sourceDir=.\Lib
set destDebugDir=.\BIN\x64\Debug
set destReleaseDir=.\BIN\x64\Release

if not exist %destDebugDir% mkdir %destDebugDir%
if not exist %destReleaseDir% mkdir %destReleaseDir%

copy %sourceDir%\*.dll %destDebugDir%
copy %sourceDir%\*.dll %destReleaseDir%

echo DLL files copied successfully.
