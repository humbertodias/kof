The King of Fighters that supports multiple platforms is implemented using sdl. 
The character configuration format comes from mugen.
This is probably code from around 2015, which is quite old. 
I'm not sure if it can still run.

dependencies
ubuntu
```shell
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-gfx-dev  libsdl2-ttf-dev libsdl2-mixer-dev libglew-dev libgles2-mesa-dev 
```
macOS
```shell
brew install sdl2 sdl2_image sdl2_gfx sdl2_ttf sdl2_mixer glew
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
