#include <gtest/gtest.h>
#include <iostream>
#include "AllureHelper.h"
#include "AllureTestListener.h"

int main(int argc, char **argv) {
    // Set Allure results directory
    AllureHelper::SetResultsDirectory("allure-results");
    
    ::testing::InitGoogleTest(&argc, argv);
    
    // Add Allure test listener
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new AllureTestListener());
    
    int result = RUN_ALL_TESTS();
    
    return result;
}

