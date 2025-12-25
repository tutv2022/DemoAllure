#ifndef ALLURE_HELPER_H
#define ALLURE_HELPER_H

#include <string>
#include <vector>

// Simple Allure helper for C++/GoogleTest
// This generates Allure-compatible JSON files
class AllureHelper {
public:
    static void SetSuite(const std::string& suite);
    static void SetOwner(const std::string& owner);
    static void SetSeverity(const std::string& severity);
    static void SetFeature(const std::string& feature);
    static void SetStory(const std::string& story);
    static void AddTag(const std::string& tag);
    static void StartTest(const std::string& testName);
    static void EndTest(bool passed, const std::string& errorMessage = "");
    static void SetResultsDirectory(const std::string& dir);
    
private:
    static std::string GenerateUUID();
    static void WriteResultFile(const std::string& testName, bool passed, const std::string& errorMessage);
    static std::string EscapeJsonString(const std::string& str);
    
    static std::string currentSuite;
    static std::string currentOwner;
    static std::string currentSeverity;
    static std::string currentFeature;
    static std::string currentStory;
    static std::vector<std::string> currentTags;
    static std::string resultsDir;
    static std::string currentTestName;
    static long long startTime;
};

// Simplified Allure namespace for easy use in tests
namespace Allure {
    void Label(const std::string& name, const std::string& value);
    void Severity(const std::string& level);
    void Feature(const std::string& feature);
    void Story(const std::string& story);
    void Tag(const std::string& tag);
    void Step(const std::string& stepName);
}

#endif // ALLURE_HELPER_H

