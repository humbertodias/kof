.PHONY: build

build:
	cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux
	cmake --build build

vcpkg/install:
	./vcpkg/bootstrap-vcpkg.sh
	./vcpkg/vcpkg install

docker/build:
	docker build . -t kof

docker/run:
	docker run -it -v `pwd`:/wd -w /wd kof

ci:
	docker build -t kof .
	docker run --rm -v "$(PWD)":/app -w /app kof sh -c "make clean build"

clean:
	rm -rf build vcpkg_installed

ARCH  := $(shell uname -m)
CMAKE_VERSION=3.31.7
cmake/install:
	curl -L -o cmake.sh https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-linux-$(ARCH).sh
	chmod +x cmake.sh
	./cmake.sh --prefix=/usr/local --skip-license
	rm cmake.sh
