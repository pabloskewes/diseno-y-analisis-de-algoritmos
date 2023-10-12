# Makefile for RTree project

# Variables
BUILD_DIR = build

# Targets
.PHONY: all clean run

all: $(BUILD_DIR)/RTree

$(BUILD_DIR)/RTree: CMakeLists.txt src/main.cpp src/rtree/rtree.cpp include/rtree/rtree.hpp
    mkdir -p $(BUILD_DIR)
    cd $(BUILD_DIR) && cmake .. && make

clean:
    rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/RTree
    cd $(BUILD_DIR) && ./RTree
	