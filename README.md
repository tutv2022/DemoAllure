# Allure Reporting for .NET 8 Project

This project demonstrates how to integrate Allure reporting with a .NET 8 xUnit test project and generate reports in Jenkins.

## Prerequisites

- .NET 8 SDK
- Jenkins with Allure Plugin installed
- Allure Commandline tool installed on Jenkins agent

## Project Structure

```
DemoAllureProject/
├── DemoAllureProject.Tests/
│   ├── DemoAllureProject.Tests.csproj
│   ├── UnitTest1.cs
│   └── allureConfig.json
├── Jenkinsfile
└── README.md
```

## NuGet Packages

The project uses the following Allure packages:
- `Allure.XUnit` (2.14.1) - Allure integration for xUnit
- `Allure.Commons` (3.5.0.73) - Common Allure functionality

## Running Tests Locally

### 1. Run tests and generate Allure results:

```bash
cd DemoAllureProject.Tests
dotnet test --logger "trx;LogFileName=test-results.trx" --results-directory ./allure-results
```

### 2. Generate Allure report:

```bash
allure generate allure-results -o allure-report --clean
```

### 3. Open Allure report:

```bash
allure open allure-report
```

## Jenkins Setup

### 1. Install Required Plugins

- **Allure Plugin** - For generating and publishing Allure reports
- **.NET SDK Plugin** (optional) - For .NET SDK management

### 2. Configure Allure Commandline

1. Go to **Jenkins** → **Manage Jenkins** → **Global Tool Configuration**
2. Find **Allure Commandline** section
3. Add Allure installation:
   - Name: `allure` (or your preferred name)
   - Installation directory: Path where Allure is installed

### 3. Configure .NET SDK (if using .NET SDK Plugin)

1. Go to **Jenkins** → **Manage Jenkins** → **Global Tool Configuration**
2. Find **.NET SDK** section
3. Add .NET SDK installation:
   - Name: `dotnet`
   - Installation directory: Path where .NET SDK is installed

### 4. Create Jenkins Job

1. Create a new **Pipeline** job
2. Configure the pipeline to use the `Jenkinsfile` from SCM
3. Or copy the Jenkinsfile content into the pipeline script

### 5. Run the Pipeline

The pipeline will:
1. Checkout the code
2. Restore NuGet packages
3. Build the project
4. Run tests and generate Allure results
5. Generate and publish Allure report

## Allure Features Demonstrated

The test suite includes examples of:
- **AllureSuite** - Organizing tests into suites
- **AllureOwner** - Assigning test ownership
- **AllureSeverity** - Setting test severity levels
- **AllureFeature** - Grouping tests by feature
- **AllureStory** - Organizing tests by user stories
- **AllureTag** - Tagging tests for filtering

## Test Categories

- **Smoke Tests**: Tagged with `smoke`
- **Math Operations**: Tagged with `math`
- **String Operations**: Tagged with `string`
- **Error Handling**: Tagged with `error-handling`

## Troubleshooting

### Allure results not generated

- Ensure tests are running successfully
- Check that `allure-results` directory is created after test execution
- Verify Allure.XUnit package is properly installed

### Jenkins Allure report not showing

- Verify Allure Plugin is installed
- Check Allure Commandline is configured in Jenkins
- Ensure `allure-results` directory exists and contains results
- Check Jenkins console output for errors

### .NET SDK not found in Jenkins

- Install .NET SDK on Jenkins agent
- Configure .NET SDK in Jenkins Global Tool Configuration
- Or use full path to `dotnet` command in Jenkinsfile

## Additional Resources

- [Allure Framework Documentation](https://docs.qameta.io/allure/)
- [Allure.NET Documentation](https://github.com/allure-framework/allure-csharp)
- [Jenkins Allure Plugin](https://plugins.jenkins.io/allure-jenkins-plugin/)

