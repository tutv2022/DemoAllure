# Jenkins Setup Guide for Allure Reporting

This guide will help you set up Jenkins to run the Allure reporting pipeline.

## Prerequisites

1. **Jenkins** installed and running
2. **Allure Commandline** installed on Jenkins agent
3. **.NET 8 SDK** installed on Jenkins agent

## Step 1: Install Jenkins Plugins

1. Go to **Jenkins** → **Manage Jenkins** → **Plugins**
2. Install the following plugins:
   - **Allure Plugin** (ID: `allure-jenkins-plugin`)
   - **Pipeline Plugin** (usually pre-installed)
   - **.NET SDK Plugin** (optional, for SDK management)

## Step 2: Configure Allure Commandline

1. Go to **Jenkins** → **Manage Jenkins** → **Global Tool Configuration**
2. Scroll to **Allure Commandline** section
3. Click **Add Allure Commandline**
4. Configure:
   - **Name**: `allure` (or your preferred name)
   - **Installation directory**: Path where Allure is installed
     - Example: `/usr/local/bin/allure` (Linux) or `C:\allure\bin\allure.bat` (Windows)
   - Or use **Install automatically** if you want Jenkins to download it

## Step 3: Configure .NET SDK (Optional)

If using .NET SDK Plugin:

1. Go to **Jenkins** → **Manage Jenkins** → **Global Tool Configuration**
2. Scroll to **.NET SDK** section
3. Click **Add .NET SDK**
4. Configure:
   - **Name**: `dotnet`
   - **Installation directory**: Path where .NET SDK is installed
     - Example: `/usr/share/dotnet` (Linux) or `C:\Program Files\dotnet` (Windows)

**Note**: If not using the plugin, ensure `dotnet` is in the system PATH.

## Step 4: Create Jenkins Pipeline Job

1. Go to **Jenkins** → **New Item**
2. Enter a job name (e.g., `DemoAllureProject`)
3. Select **Pipeline** and click **OK**
4. In the job configuration:
   - **Pipeline Definition**: Select **Pipeline script from SCM**
   - **SCM**: Select your version control (Git, SVN, etc.)
   - **Repository URL**: Enter your repository URL
   - **Branch**: Enter branch name (e.g., `*/main` or `*/master`)
   - **Script Path**: `Jenkinsfile`
5. Click **Save**

## Step 5: Run the Pipeline

1. Click **Build Now** on your pipeline job
2. Monitor the build progress in the console output
3. After completion, you should see:
   - **Allure Report** link in the build sidebar
   - Test results and detailed Allure report

## Step 6: View Allure Report

1. After a successful build, click on the build number
2. In the left sidebar, click **Allure Report**
3. You'll see:
   - Test execution overview
   - Test results with categories (Feature, Story, Severity, etc.)
   - Graphs and statistics
   - Test history

## Troubleshooting

### Allure Commandline Not Found

**Error**: `allure: command not found`

**Solution**:
- Verify Allure is installed on Jenkins agent
- Check the path in Global Tool Configuration
- Ensure the path is correct for your OS (Linux vs Windows)

### .NET SDK Not Found

**Error**: `dotnet: command not found`

**Solution**:
- Install .NET 8 SDK on Jenkins agent
- Add to system PATH or configure in Global Tool Configuration
- Verify with `dotnet --version` command

### No Allure Results Generated

**Possible causes**:
- Tests are not running
- Allure.XUnit package not properly installed
- Check console output for errors

**Solution**:
- Verify tests are executing successfully
- Check that `allure-results` directory is created
- Review test execution logs

### Allure Report Not Showing

**Possible causes**:
- Allure Plugin not installed
- Results path incorrect
- No results generated

**Solution**:
- Verify Allure Plugin is installed and enabled
- Check results path in Jenkinsfile matches actual location
- Ensure at least one test has run

## Pipeline Stages

The pipeline includes the following stages:

1. **Checkout**: Gets code from SCM
2. **Restore**: Restores NuGet packages
3. **Build**: Builds the .NET project
4. **Test**: Runs tests and generates Allure results
5. **Generate Allure Report**: Creates HTML report from results
6. **Publish**: Publishes report to Jenkins UI

## Customization

### Change Allure Results Location

Edit the `Jenkinsfile` and modify the results path:

```groovy
results: [[path: 'your-custom-path/allure-results']]
```

### Add Additional Test Categories

Modify test files to add more Allure attributes:

```csharp
[AllureTag("custom-tag")]
[AllureSeverity(SeverityLevel.blocker)]
```

### Configure Allure Properties

Edit `allureConfig.json` in the test project to customize Allure behavior.

## Additional Resources

- [Allure Jenkins Plugin Documentation](https://plugins.jenkins.io/allure-jenkins-plugin/)
- [Allure Framework Documentation](https://docs.qameta.io/allure/)
- [Jenkins Pipeline Documentation](https://www.jenkins.io/doc/book/pipeline/)

