#ifndef ALLURE_TEST_LISTENER_H
#define ALLURE_TEST_LISTENER_H

#include <gtest/gtest.h>
#include "AllureHelper.h"
#include <string>

// GoogleTest listener that automatically handles Allure test lifecycle
class AllureTestListener : public ::testing::EmptyTestEventListener {
public:
    void OnTestStart(const ::testing::TestInfo& test_info) override;
    void OnTestEnd(const ::testing::TestInfo& test_info) override;
    void OnTestPartResult(const ::testing::TestPartResult& test_part_result) override;

private:
    bool testPassed;
    std::string errorMessage;
};

#endif // ALLURE_TEST_LISTENER_H

