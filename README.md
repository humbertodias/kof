The King of Fighters that supports multiple platforms is implemented using sdl. 
The character configuration format comes from mugen.
This is probably code from around 2015, which is quite old. 
I'm not sure if it can still run.

dependencies
```shell
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev  libsdl2-ttf-dev libsdl2-mixer-dev libglew-dev libgles2-mesa-dev 
```

build
```shell
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```
run
```shell
cd Resource
../build/kof
```
