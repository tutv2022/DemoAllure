#include <gtest/gtest.h>
#include "Calculator.h"
#include "AllureHelper.h"
#include <stdexcept>

class CalculatorTests : public ::testing::Test {
protected:
    void SetUp() override {
        AllureHelper::SetSuite("Calculator Tests");
        AllureHelper::SetOwner("QA Team");
    }
    
    Calculator calculator;
};

TEST_F(CalculatorTests, Add_TwoPositiveNumbers_ReturnsSum) {
    Allure::Severity("critical");
    Allure::Feature("Basic Operations");
    Allure::Story("Addition");
    Allure::Tag("smoke");
    Allure::Tag("math");

    // Arrange
    int a = 5;
    int b = 3;

    // Act
    int result = calculator.Add(a, b);

    // Assert
    EXPECT_EQ(8, result);
}

TEST_F(CalculatorTests, Subtract_TwoNumbers_ReturnsDifference) {
    Allure::Severity("normal");
    Allure::Feature("Basic Operations");
    Allure::Story("Subtraction");
    Allure::Tag("math");

    // Arrange
    int a = 10;
    int b = 4;

    // Act
    int result = calculator.Subtract(a, b);

    // Assert
    EXPECT_EQ(6, result);
}

TEST_F(CalculatorTests, Multiply_TwoNumbers_ReturnsProduct) {
    Allure::Severity("normal");
    Allure::Feature("Basic Operations");
    Allure::Story("Multiplication");
    Allure::Tag("math");

    // Arrange
    int a = 6;
    int b = 7;

    // Act
    int result = calculator.Multiply(a, b);

    // Assert
    EXPECT_EQ(42, result);
}

TEST_F(CalculatorTests, Divide_TwoNumbers_ReturnsQuotient) {
    Allure::Severity("critical");
    Allure::Feature("Basic Operations");
    Allure::Story("Division");
    Allure::Tag("math");

    // Arrange
    int a = 20;
    int b = 4;

    // Act
    int result = calculator.Divide(a, b);

    // Assert
    EXPECT_EQ(5, result);
}

TEST_F(CalculatorTests, Divide_ByZero_ThrowsException) {
    Allure::Severity("critical");
    Allure::Feature("Error Handling");
    Allure::Story("Division by Zero");
    Allure::Tag("error-handling");

    // Arrange
    int a = 10;
    int b = 0;

    // Act & Assert
    EXPECT_THROW(calculator.Divide(a, b), std::runtime_error);
}

