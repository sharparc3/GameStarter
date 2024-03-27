@echo off

set sourceDir=.\Lib
set destDir=.\BIN\x64\Debug

if not exist %destDir% mkdir %destDir%

copy %sourceDir%\*.dll %destDir%

echo DLL files copied successfully.
