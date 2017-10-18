cd "./build"

cmake ..
make

cp "libantisocial.so"   "../../AntisocialTest/build/"
sudo cp "libantisocial.so" "/usr/lib"

cd "../src"
find ./ -name '*.h' -exec cp -prv '{}' '../../AntisocialTest/external' ';'

cd "../"
