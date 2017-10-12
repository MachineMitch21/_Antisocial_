
cd "./build"

cmake -G "MinGW Makefiles" ..
"C:/MinGW/bin/mingw32-make.exe"
@echo off

copy /y "libantisocial.dll"   "../../AntisocialTest/build/"
copy /y "libantisocial.dll.a" "C:/MinGW/lib/"

cd "../src"

@echo "Copying header files to test project location"

copy /y "*.h" "../../AntisocialTest/external"

cd "../"

pause
