#include <gtest/gtest.h>
#include "Calculator.h"
#include <stdexcept>

class CalculatorTests : public ::testing::Test {
protected:
    Calculator calculator;
};

TEST_F(CalculatorTests, Add_TwoPositiveNumbers_ReturnsSum) {
    // Arrange
    int a = 5;
    int b = 3;

    // Act
    int result = calculator.Add(a, b);

    // Assert
    EXPECT_EQ(8, result);
}

TEST_F(CalculatorTests, Subtract_TwoNumbers_ReturnsDifference) {
    // Arrange
    int a = 10;
    int b = 4;

    // Act
    int result = calculator.Subtract(a, b);

    // Assert
    EXPECT_EQ(6, result);
}

TEST_F(CalculatorTests, Multiply_TwoNumbers_ReturnsProduct) {
    // Arrange
    int a = 6;
    int b = 7;

    // Act
    int result = calculator.Multiply(a, b);

    // Assert
    EXPECT_EQ(42, result);
}

TEST_F(CalculatorTests, Divide_TwoNumbers_ReturnsQuotient) {
    // Arrange
    int a = 20;
    int b = 4;

    // Act
    int result = calculator.Divide(a, b);

    // Assert
    EXPECT_EQ(5, result);
}

TEST_F(CalculatorTests, Divide_ByZero_ThrowsException) {
    // Arrange
    int a = 10;
    int b = 0;

    // Act & Assert
    EXPECT_THROW(calculator.Divide(a, b), std::runtime_error);
}

