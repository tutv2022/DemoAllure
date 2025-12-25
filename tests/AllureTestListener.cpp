#include "AllureTestListener.h"
#include <sstream>

void AllureTestListener::OnTestStart(const ::testing::TestInfo& test_info) {
    testPassed = true;
    errorMessage = "";
    
    // Start Allure test
    std::string testName = std::string(test_info.test_suite_name()) + "." + test_info.name();
    AllureHelper::StartTest(testName);
}

void AllureTestListener::OnTestPartResult(const ::testing::TestPartResult& test_part_result) {
    if (test_part_result.failed()) {
        testPassed = false;
        if (errorMessage.empty()) {
            std::stringstream ss;
            ss << test_part_result.file_name() << ":" << test_part_result.line_number() 
               << " - " << test_part_result.message();
            errorMessage = ss.str();
        }
    }
}

void AllureTestListener::OnTestEnd(const ::testing::TestInfo& test_info) {
    // End Allure test
    AllureHelper::EndTest(testPassed, errorMessage);
}

