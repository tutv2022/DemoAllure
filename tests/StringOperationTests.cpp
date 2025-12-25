#include <gtest/gtest.h>
#include "StringOperations.h"

class StringOperationTests : public ::testing::Test {
};

TEST_F(StringOperationTests, Concatenate_TwoStrings_ReturnsCombinedString) {
    // Arrange
    std::string str1 = "Hello";
    std::string str2 = "World";

    // Act
    std::string result = StringOperations::Concatenate(str1, str2);

    // Assert
    EXPECT_EQ("Hello World", result);
}

TEST_F(StringOperationTests, GetStringLength_ValidString_ReturnsCorrectLength) {
    // Arrange
    std::string str = "Allure Reporting";

    // Act
    int length = StringOperations::GetLength(str);

    // Assert
    EXPECT_EQ(16, length);
}

TEST_F(StringOperationTests, ToUpperCase_ValidString_ReturnsUpperCase) {
    // Arrange
    std::string str = "allure reporting";

    // Act
    std::string result = StringOperations::ToUpperCase(str);

    // Assert
    EXPECT_EQ("ALLURE REPORTING", result);
}

