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

# Run tests
echo "Running tests..."
./bin/DemoAllureProjectTests --gtest_output=xml:test-results.xml || true

# Generate Allure report if allure command is available
if command -v allure &> /dev/null; then
    echo "Generating Allure report..."
    if [ -d "allure-results" ] && [ "$(ls -A allure-results)" ]; then
        allure generate allure-results -o allure-report --clean
        echo "Allure report generated in build/allure-report"
        echo "To view: allure open build/allure-report"
    else
        echo "Warning: No Allure results found"
    fi
else
    echo "Allure commandline not found. Install it to generate reports."
fi

echo "Build complete!"

