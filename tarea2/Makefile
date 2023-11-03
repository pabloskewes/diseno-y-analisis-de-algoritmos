SHELL := /bin/bash

# Variables
BUILD_DIR = build
RTREE_EXE = Sorting

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
