
cd "./build"

"C:/MinGW/bin/mingw32-make.exe"
@echo off

copy /y "libantisocial.dll"   "../../AntisocialTest/build/"
copy /y "libantisocial.dll.a" "C:/MinGW/lib/"

@echo "Copied files"

cd "../"

pause
