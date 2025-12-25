#!/bin/bash
set -e

echo "Building DemoAllureProject..."

# Create build directory
mkdir -p build
cd build

# Configure
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
echo "Building..."
cmake --build . --config Release

# Run tests with XML output
echo "Running tests..."
mkdir -p test-results
./bin/DemoAllureProjectTests --gtest_output=xml:test-results/test-results.xml || true

# Display results
if [ -f "test-results/test-results.xml" ]; then
    echo "Test results XML generated: test-results/test-results.xml"
    echo "File contents:"
    head -20 test-results/test-results.xml
else
    echo "Warning: Test results XML not found"
fi

echo "Build complete!"
