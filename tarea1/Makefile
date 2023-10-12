SHELL := /bin/bash

# Variables
BUILD_DIR = build
RTREE_EXE = RTree

# Targets
.PHONY: build clear


build:
	@echo "Building..."
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR)
	@make -C $(BUILD_DIR)

clear:
	@echo "Cleaning..."
	@rm -rf $(BUILD_DIR)

run:
	@echo "Running..."
	@./$(BUILD_DIR)/$(RTREE_EXE)
