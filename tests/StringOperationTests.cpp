#include <gtest/gtest.h>
#include "StringOperations.h"
#include "AllureHelper.h"

class StringOperationTests : public ::testing::Test {
protected:
    void SetUp() override {
        AllureHelper::SetSuite("String Operations Tests");
        AllureHelper::SetOwner("QA Team");
    }
};

TEST_F(StringOperationTests, Concatenate_TwoStrings_ReturnsCombinedString) {
    Allure::Severity("normal");
    Allure::Feature("String Manipulation");
    Allure::Story("Concatenation");
    Allure::Tag("string");
    Allure::Tag("smoke");

    // Arrange
    std::string str1 = "Hello";
    std::string str2 = "World";

    // Act
    std::string result = StringOperations::Concatenate(str1, str2);

    // Assert
    EXPECT_EQ("Hello World", result);
}

TEST_F(StringOperationTests, GetStringLength_ValidString_ReturnsCorrectLength) {
    Allure::Severity("normal");
    Allure::Feature("String Manipulation");
    Allure::Story("Length");
    Allure::Tag("string");

    // Arrange
    std::string str = "Allure Reporting";

    // Act
    int length = StringOperations::GetLength(str);

    // Assert
    EXPECT_EQ(16, length);
}

TEST_F(StringOperationTests, ToUpperCase_ValidString_ReturnsUpperCase) {
    Allure::Severity("normal");
    Allure::Feature("String Manipulation");
    Allure::Story("Case Conversion");
    Allure::Tag("string");

    // Arrange
    std::string str = "allure reporting";

    // Act
    std::string result = StringOperations::ToUpperCase(str);

    // Assert
    EXPECT_EQ("ALLURE REPORTING", result);
}

