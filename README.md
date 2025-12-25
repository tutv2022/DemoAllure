# C++ Project with GoogleTest

This project demonstrates a C++ project using GoogleTest for unit testing with XML test result output.

## Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.14 or higher
- GoogleTest (automatically downloaded via CMake or pre-installed on system)

## Project Structure

```
DemoAllureProject/
├── CMakeLists.txt
├── src/
│   ├── Calculator.cpp
│   └── StringOperations.cpp
├── include/
│   ├── Calculator.h
│   └── StringOperations.h
├── tests/
│   ├── main.cpp
│   ├── CalculatorTests.cpp
│   └── StringOperationTests.cpp
├── Jenkinsfile
├── build.sh
└── README.md
```

## Building the Project

### Local Build

1. **Configure the project:**
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

2. **Build the project:**
```bash
cmake --build . --config Release
```

3. **Run tests:**
```bash
./bin/DemoAllureProjectTests
```

4. **Run tests with XML output:**
```bash
mkdir -p test-results
./bin/DemoAllureProjectTests --gtest_output=xml:test-results/test-results.xml
```

Or use the build script:
```bash
chmod +x build.sh
./build.sh
```

## GoogleTest XML Output

GoogleTest can generate XML test results using the `--gtest_output` flag:

```bash
# Generate XML to a specific file
./bin/DemoAllureProjectTests --gtest_output=xml:test-results.xml

# Generate XML to a directory (creates test_detail.xml)
./bin/DemoAllureProjectTests --gtest_output=xml:test-results/
```

The XML output follows the JUnit XML format and can be used with:
- Jenkins JUnit plugin
- CI/CD pipelines
- Test result visualization tools

## Jenkins Setup

### 1. Install Required Plugins

- **JUnit Plugin** - For publishing test results
- **Pipeline Plugin** (usually pre-installed)

### 2. Configure Build Tools

Ensure the following are installed on your Jenkins agent:
- **CMake** (3.14 or higher)
- **C++ Compiler** (GCC, Clang, or MSVC)
- **Make** or **Ninja** (for building)

### 3. Create Jenkins Pipeline Job

1. Create a new **Pipeline** job
2. Configure the pipeline to use the `Jenkinsfile` from SCM
3. Or copy the Jenkinsfile content into the pipeline script

### 4. Run the Pipeline

The pipeline will:
1. Checkout the code
2. Configure the build with CMake
3. Build the project
4. Run tests and generate XML results
5. Publish test results using JUnit plugin

## Test Features

The test suite includes:
- **Calculator Tests**: Addition, Subtraction, Multiplication, Division, Error Handling
- **String Operation Tests**: Concatenation, Length, Case Conversion

## Building on Different Platforms

### Linux
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/DemoAllureProjectTests --gtest_output=xml:test-results.xml
```

### Windows (Visual Studio)
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
.\bin\Release\DemoAllureProjectTests.exe --gtest_output=xml:test-results.xml
```

### macOS
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/DemoAllureProjectTests --gtest_output=xml:test-results.xml
```

## Troubleshooting

### CMake not found
- Install CMake: `sudo apt-get install cmake` (Linux) or download from cmake.org
- Ensure CMake is in PATH

### GoogleTest download fails
- Check internet connection
- Verify CMake version is 3.14 or higher
- Try building with `cmake .. -DFETCHCONTENT_QUIET=OFF` for verbose output

### XML file not generated
- Ensure tests are running successfully
- Check that the output directory exists
- Verify the `--gtest_output` flag is correctly formatted

### Compilation errors
- Ensure C++17 support is enabled
- Check compiler version compatibility
- Verify all source files are included in CMakeLists.txt

## Additional Resources

- [GoogleTest Documentation](https://google.github.io/googletest/)
- [CMake Documentation](https://cmake.org/documentation/)
- [Jenkins JUnit Plugin](https://plugins.jenkins.io/junit/)
