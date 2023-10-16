SHELL := /bin/bash

# Variables
BUILD_DIR = build
RTREE_EXE = RTree

# Targets
.PHONY: build clear

# makeflags
MAKEFLAGS += --no-print-directory


build:
	@echo "Building..."
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR)
	@make -C $(BUILD_DIR)

run:
	@echo "Running..."
	@./$(BUILD_DIR)/$(RTREE_EXE)

clean-build:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)

cache-usage:
	@free -h | awk '/^Mem:/ {print $$6}'

free-cache:
	@echo "Freeing cache..."
	@sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"

clear-input-data:
	@echo "Clearing input data..."
	@rm -rf data/rectangles/*.txt
