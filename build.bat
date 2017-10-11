@echo off

cd "./build"

copy /y "libantisocial.dll"   "../../AntisocialTest/build/"
copy /y "libantisocial.dll.a" "C:/MinGW/lib/"

@echo "Copied files"

cd "../"
