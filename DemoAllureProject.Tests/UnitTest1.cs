using Allure.Xunit.Attributes;
using Allure.Net.Commons;

namespace DemoAllureProject.Tests;

[AllureSuite("Calculator Tests")]
public class CalculatorTests
{
    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.critical)]
    [AllureFeature("Basic Operations")]
    [AllureStory("Addition")]
    [AllureTag("smoke", "math")]
    public void Add_TwoPositiveNumbers_ReturnsSum()
    {
        // Arrange
        var calculator = new Calculator();
        var a = 5;
        var b = 3;

        // Act
        var result = calculator.Add(a, b);

        // Assert
        Assert.Equal(8, result);
    }

    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.normal)]
    [AllureFeature("Basic Operations")]
    [AllureStory("Subtraction")]
    [AllureTag("math")]
    public void Subtract_TwoNumbers_ReturnsDifference()
    {
        // Arrange
        var calculator = new Calculator();
        var a = 10;
        var b = 4;

        // Act
        var result = calculator.Subtract(a, b);

        // Assert
        Assert.Equal(6, result);
    }

    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.normal)]
    [AllureFeature("Basic Operations")]
    [AllureStory("Multiplication")]
    [AllureTag("math")]
    public void Multiply_TwoNumbers_ReturnsProduct()
    {
        // Arrange
        var calculator = new Calculator();
        var a = 6;
        var b = 7;

        // Act
        var result = calculator.Multiply(a, b);

        // Assert
        Assert.Equal(42, result);
    }

    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.critical)]
    [AllureFeature("Basic Operations")]
    [AllureStory("Division")]
    [AllureTag("math")]
    public void Divide_TwoNumbers_ReturnsQuotient()
    {
        // Arrange
        var calculator = new Calculator();
        var a = 20;
        var b = 4;

        // Act
        var result = calculator.Divide(a, b);

        // Assert
        Assert.Equal(5, result);
    }

    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.critical)]
    [AllureFeature("Error Handling")]
    [AllureStory("Division by Zero")]
    [AllureTag("error-handling")]
    public void Divide_ByZero_ThrowsException()
    {
        // Arrange
        var calculator = new Calculator();
        var a = 10;
        var b = 0;

        // Act & Assert
        Assert.Throws<DivideByZeroException>(() => calculator.Divide(a, b));
    }
}

[AllureSuite("String Operations Tests")]
public class StringOperationTests
{
    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.normal)]
    [AllureFeature("String Manipulation")]
    [AllureStory("Concatenation")]
    [AllureTag("string", "smoke")]
    public void Concatenate_TwoStrings_ReturnsCombinedString()
    {
        // Arrange
        var str1 = "Hello";
        var str2 = "World";

        // Act
        var result = str1 + " " + str2;

        // Assert
        Assert.Equal("Hello World", result);
    }

    [Fact]
    [AllureOwner("QA Team")]
    [AllureSeverity(SeverityLevel.normal)]
    [AllureFeature("String Manipulation")]
    [AllureStory("Length")]
    [AllureTag("string")]
    public void GetStringLength_ValidString_ReturnsCorrectLength()
    {
        // Arrange
        var str = "Allure Reporting";

        // Act
        var length = str.Length;

        // Assert
        Assert.Equal(16, length);
    }
}

// Simple Calculator class for testing
public class Calculator
{
    public int Add(int a, int b) => a + b;
    public int Subtract(int a, int b) => a - b;
    public int Multiply(int a, int b) => a * b;
    public int Divide(int a, int b)
    {
        if (b == 0)
            throw new DivideByZeroException("Cannot divide by zero");
        return a / b;
    }
}
