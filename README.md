[![CI](https://github.com/humbertodias/kof/actions/workflows/ci.yml/badge.svg)](https://github.com/humbertodias/kof/actions/workflows/ci.yml)
[![CD](https://github.com/humbertodias/kof/actions/workflows/cd.yml/badge.svg)](https://github.com/humbertodias/kof/actions/workflows/cd.yml)
![GitHub all downloads](https://img.shields.io/github/downloads/humbertodias/kof/total)
# The King of Fighters

A cross-platform implementation of **The King of Fighters**, using **SDL2**.  
Character configuration follows the **M.U.G.E.N** format.

## ✨ Features

- Multi-platform support (Linux, macOS)
- Character format based on MUGEN
- Built using SDL2 and OpenGL
- Includes sound, graphics, font rendering, and input handling

### Clone
```shell
git clone --recurse-submodules https://github.com/humbertodias/kof
```

## 🔧 Dependencies

### vcpkg
```shell
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install
```

## 🛠️ Build Instructions

```shell
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux
cmake --build build
```

## ▶️ Run the Game

```shell
(cd Resource && ../build/kof)
```

## 📸 Preview


https://github.com/user-attachments/assets/ff53fe0a-7dff-4ddb-a5e2-b58a183c7d64


Feel free to open issues or contribute improvements. Happy fighting! 🥋🔥
