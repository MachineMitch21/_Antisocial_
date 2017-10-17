cd "./build"

cmake ..
make

cp "libantisocial.so"   "../../AntisocialTest/build/"

find ./ -name '*.xsl' -exec cp -prv '{}' '/path/to/targetDir/' ';'

sudo cp "libantisocial.so" "/usr/lib"

cd "../"
