#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Check if the build directory already exists
if [ -d "$BUILD_DIR" ]; then
    echo "Build directory '$BUILD_DIR' already exists. Cleaning up..."
    rm -rf "$BUILD_DIR"
fi

# Create a new build directory
echo "Creating build directory '$BUILD_DIR'..."
mkdir "$BUILD_DIR"

# Navigate to the build directory
cd "$BUILD_DIR" || exit

# Run CMake to generate the build files
echo "Running CMake to generate build files..."
cmake ..

# Check if CMake succeeded
if [ $? -ne 0 ]; then
    echo "CMake failed. Exiting."
    exit 1
fi

# Build the project
echo "Building the project..."
cmake --build .

# Check if the build succeeded
if [ $? -ne 0 ]; then
    echo "Build failed. Exiting."
    exit 1
fi

# Inform the user the build was successful
echo "Build completed successfully. You can now run './nosod' from the build directory."
