# Allure Reporting for C++ Project with GoogleTest

This project demonstrates how to integrate Allure reporting with a C++ project using GoogleTest and generate reports in Jenkins.

## Prerequisites

- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.14 or higher
- GoogleTest (automatically downloaded via CMake)
- Jenkins with Allure Plugin installed
- Allure Commandline tool installed on Jenkins agent

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
│   ├── AllureHelper.h
│   ├── AllureHelper.cpp
│   ├── CalculatorTests.cpp
│   └── StringOperationTests.cpp
├── Jenkinsfile
├── allureConfig.json
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

4. **Generate Allure report:**
```bash
# Allure results are automatically generated in allure-results directory
allure generate allure-results -o allure-report --clean
allure open allure-report
```

## Allure Integration

The project includes a custom `AllureHelper` class that generates Allure-compatible JSON result files. This allows you to use Allure reporting without requiring external Allure C++ libraries.

### Using Allure in Tests

```cpp
#include "AllureHelper.h"

TEST_F(MyTestSuite, MyTest) {
    AllureHelper::StartTest("MyTest");
    Allure::Severity("critical");
    Allure::Feature("My Feature");
    Allure::Story("My Story");
    Allure::Tag("smoke");
    
    // Your test code here
    EXPECT_EQ(expected, actual);
    
    AllureHelper::EndTest(true);
}
```

### Available Allure Functions

- `Allure::Severity(level)` - Set test severity (critical, normal, minor, trivial, blocker)
- `Allure::Feature(feature)` - Set feature name
- `Allure::Story(story)` - Set user story
- `Allure::Tag(tag)` - Add a tag
- `Allure::Label(name, value)` - Add a custom label
- `AllureHelper::StartTest(testName)` - Start a test
- `AllureHelper::EndTest(passed, errorMessage)` - End a test

## Jenkins Setup

### 1. Install Required Plugins

- **Allure Plugin** - For generating and publishing Allure reports
- **Pipeline Plugin** (usually pre-installed)

### 2. Configure Allure Commandline

1. Go to **Jenkins** → **Manage Jenkins** → **Global Tool Configuration**
2. Find **Allure Commandline** section
3. Add Allure installation:
   - **Name**: `allure` (or your preferred name)
   - **Installation directory**: Path where Allure is installed

### 3. Configure Build Tools

Ensure the following are installed on your Jenkins agent:
- **CMake** (3.14 or higher)
- **C++ Compiler** (GCC, Clang, or MSVC)
- **Make** or **Ninja** (for building)

### 4. Create Jenkins Pipeline Job

1. Create a new **Pipeline** job
2. Configure the pipeline to use the `Jenkinsfile` from SCM
3. Or copy the Jenkinsfile content into the pipeline script

### 5. Run the Pipeline

The pipeline will:
1. Checkout the code
2. Configure the build with CMake
3. Build the project
4. Run tests and generate Allure results
5. Generate and publish Allure report

## Test Features Demonstrated

The test suite includes examples of:
- **Suite** - Organizing tests into suites
- **Owner** - Assigning test ownership
- **Severity** - Setting test severity levels (critical, normal)
- **Feature** - Grouping tests by feature
- **Story** - Organizing tests by user stories
- **Tag** - Tagging tests for filtering (smoke, math, string, error-handling)

## Test Categories

- **Smoke Tests**: Tagged with `smoke`
- **Math Operations**: Tagged with `math`
- **String Operations**: Tagged with `string`
- **Error Handling**: Tagged with `error-handling`

## Building on Different Platforms

### Linux
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/DemoAllureProjectTests
```

### Windows (Visual Studio)
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
.\bin\Release\DemoAllureProjectTests.exe
```

### macOS
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/DemoAllureProjectTests
```

## Troubleshooting

### CMake not found
- Install CMake: `sudo apt-get install cmake` (Linux) or download from cmake.org
- Ensure CMake is in PATH

### GoogleTest download fails
- Check internet connection
- Verify CMake version is 3.14 or higher
- Try building with `cmake .. -DFETCHCONTENT_QUIET=OFF` for verbose output

### Allure results not generated
- Ensure tests are running successfully
- Check that `allure-results` directory is created after test execution
- Verify AllureHelper is properly linked in CMakeLists.txt

### Jenkins Allure report not showing
- Verify Allure Plugin is installed
- Check Allure Commandline is configured in Jenkins
- Ensure `allure-results` directory exists and contains results
- Check Jenkins console output for errors

### Compilation errors
- Ensure C++17 support is enabled
- Check compiler version compatibility
- Verify all source files are included in CMakeLists.txt

## Additional Resources

- [Allure Framework Documentation](https://docs.qameta.io/allure/)
- [GoogleTest Documentation](https://google.github.io/googletest/)
- [CMake Documentation](https://cmake.org/documentation/)
- [Jenkins Allure Plugin](https://plugins.jenkins.io/allure-jenkins-plugin/)
