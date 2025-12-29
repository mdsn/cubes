BUILD_DIR := build

BUILD_TYPE ?= Debug

MAKE := make
CMAKE := cmake
GENERATOR := Ninja
CMAKE_FLAGS := \
	-G "$(GENERATOR)" \
	-DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

ifndef VCPKG_ROOT
	$(error VCPKG_ROOT is not set. Export it, e.g. 'export VCPKG_ROOT=$HOME/src/vcpkg')
endif

VCPKG_TOOLCHAIN := $(VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake

ifeq (,$(wildcard $(VCPKG_TOOLCHAIN)))
	$(error vcpkg toolchain not found at $(VCPKG_TOOLCHAIN). Check VCPKG_ROOT.)
endif

CMAKE_FLAGS += -DCMAKE_TOOLCHAIN_FILE=$(VCPKG_TOOLCHAIN)
CMAKE_CACHE := $(BUILD_DIR)/CMakeCache.txt

.PHONY: all configure build clean rebuild run debug release test

all: build

$(CMAKE_CACHE): CMakeLists.txt vcpkg.json
	@mkdir -p $(BUILD_DIR)
	$(CMAKE) -S . -B $(BUILD_DIR) $(CMAKE_FLAGS)

configure: $(CMAKE_CACHE)

build: $(CMAKE_CACHE)
	$(CMAKE) --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build

run: build
	./$(BUILD_DIR)/brix

debug:
	$(MAKE) BUILD_TYPE=Debug build

release:
	$(MAKE) BUILD_TYPE=Release build

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure
