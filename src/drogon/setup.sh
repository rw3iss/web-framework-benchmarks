cd benchmark

dir=$(pwd)

# install jsoncpp dependency:
git clone https://github.com/open-source-parsers/jsoncpp /tmp/jsoncpp
cd /tmp/jsoncpp/
mkdir build
cd build
cmake ..
sudo make && sudo  make install


# install drogon dependency:
git clone https://github.com/an-tao/drogon
cd drogon
git submodule update --init
mkdir build
cd build
#cmake ..                           # compiles debug version
cmake -DCMAKE_BUILD_TYPE=Release .. # compiles release version
make && make install


# build this benchmark:
cd $dir
cd build
cmake ..
make