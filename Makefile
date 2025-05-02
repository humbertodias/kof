# System info
OS    := $(shell uname -s)
ARCH  := $(shell uname -m)
CMAKE := $(shell command -v cmake)

# Git versioning
TAG_NAME := $(shell git describe --tags --exact-match 2>/dev/null || git rev-parse --short HEAD)

.PHONY: build

build:
	$(CMAKE) -Bbuild -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja
	$(CMAKE) --build build

vcpkg/install:
	./vcpkg/bootstrap-vcpkg.sh
	./vcpkg/vcpkg install

docker/build:
	docker build . -t kof

docker/run:
	docker run -it -v `pwd`:/wd -w /wd kof

ci:	docker/build
	docker run --rm -v "$(PWD)":/app -w /app kof sh -c "make clean build"

clean:
	rm -rf build kof-$(TAG_NAME)-$(OS)-$(ARCH).tar.gz

tar/gz:	build
	tar cvfz kof-$(TAG_NAME)-$(OS)-$(ARCH).tar.gz build/kof