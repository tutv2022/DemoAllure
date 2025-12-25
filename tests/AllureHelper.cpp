#include "AllureHelper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <random>

// Simple implementation using environment variables and file system
// This creates Allure-compatible JSON result files

namespace fs = std::filesystem;

std::string AllureHelper::currentSuite = "";
std::string AllureHelper::currentOwner = "";
std::string AllureHelper::currentSeverity = "";
std::string AllureHelper::currentFeature = "";
std::string AllureHelper::currentStory = "";
std::vector<std::string> AllureHelper::currentTags;
std::string AllureHelper::resultsDir = "allure-results";
std::string AllureHelper::currentTestName = "";
long long AllureHelper::startTime = 0;

void AllureHelper::SetResultsDirectory(const std::string& dir) {
    resultsDir = dir;
    // Create directory if it doesn't exist
    fs::create_directories(resultsDir);
}

std::string AllureHelper::GenerateUUID() {
    // Generate a simple UUID-like string
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);
    
    std::stringstream ss;
    ss << std::hex;
    for (int i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (int i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (int i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (int i = 0; i < 12; i++) {
        ss << dis(gen);
    }
    return ss.str();
}

std::string AllureHelper::EscapeJsonString(const std::string& str) {
    std::stringstream ss;
    for (char c : str) {
        if (c == '"') ss << "\\\"";
        else if (c == '\\') ss << "\\\\";
        else if (c == '\n') ss << "\\n";
        else if (c == '\r') ss << "\\r";
        else if (c == '\t') ss << "\\t";
        else ss << c;
    }
    return ss.str();
}

std::string AllureHelper::GetCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::to_string(time);
}

void AllureHelper::SetSuite(const std::string& suite) {
    currentSuite = suite;
}

void AllureHelper::SetOwner(const std::string& owner) {
    currentOwner = owner;
}

void AllureHelper::SetSeverity(const std::string& severity) {
    currentSeverity = severity;
}

void AllureHelper::SetFeature(const std::string& feature) {
    currentFeature = feature;
}

void AllureHelper::SetStory(const std::string& story) {
    currentStory = story;
}

void AllureHelper::AddTag(const std::string& tag) {
    currentTags.push_back(tag);
}

void AllureHelper::StartTest(const std::string& testName) {
    currentTestName = testName;
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    currentTags.clear();
}

void AllureHelper::EndTest(bool passed, const std::string& errorMessage) {
    WriteResultFile(currentTestName, passed, errorMessage);
}

void AllureHelper::WriteResultFile(const std::string& testName, bool passed, const std::string& errorMessage) {
    fs::create_directories(resultsDir);
    
    std::string uuid = GenerateUUID();
    std::string filename = resultsDir + "/" + uuid + "-result.json";
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to create Allure result file: " << filename << std::endl;
        return;
    }
    
    auto endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    long long duration = endTime - startTime;
    
    file << "{\n";
    file << "  \"uuid\": \"" << uuid << "\",\n";
    file << "  \"name\": \"" << EscapeJsonString(testName) << "\",\n";
    file << "  \"status\": \"" << (passed ? "passed" : "failed") << "\",\n";
    file << "  \"statusDetails\": {\n";
    if (!passed && !errorMessage.empty()) {
        file << "    \"message\": \"" << EscapeJsonString(errorMessage) << "\"\n";
    }
    file << "  },\n";
    file << "  \"start\": " << startTime << ",\n";
    file << "  \"stop\": " << endTime << ",\n";
    file << "  \"stage\": \"finished\",\n";
    file << "  \"labels\": [\n";
    
    bool first = true;
    if (!currentSuite.empty()) {
        file << (first ? "" : ",\n") << "    {\"name\": \"suite\", \"value\": \"" << EscapeJsonString(currentSuite) << "\"}";
        first = false;
    }
    if (!currentOwner.empty()) {
        file << (first ? "" : ",\n") << "    {\"name\": \"owner\", \"value\": \"" << EscapeJsonString(currentOwner) << "\"}";
        first = false;
    }
    if (!currentSeverity.empty()) {
        file << (first ? "" : ",\n") << "    {\"name\": \"severity\", \"value\": \"" << EscapeJsonString(currentSeverity) << "\"}";
        first = false;
    }
    if (!currentFeature.empty()) {
        file << (first ? "" : ",\n") << "    {\"name\": \"feature\", \"value\": \"" << EscapeJsonString(currentFeature) << "\"}";
        first = false;
    }
    if (!currentStory.empty()) {
        file << (first ? "" : ",\n") << "    {\"name\": \"story\", \"value\": \"" << EscapeJsonString(currentStory) << "\"}";
        first = false;
    }
    for (const auto& tag : currentTags) {
        file << (first ? "" : ",\n") << "    {\"name\": \"tag\", \"value\": \"" << EscapeJsonString(tag) << "\"}";
        first = false;
    }
    
    file << "\n  ]\n";
    file << "}\n";
    
    file.close();
}

// Simplified Allure namespace implementation
namespace Allure {
    void Label(const std::string& name, const std::string& value) {
        if (name == "suite") AllureHelper::SetSuite(value);
        else if (name == "owner") AllureHelper::SetOwner(value);
        else if (name == "severity") AllureHelper::SetSeverity(value);
        else if (name == "feature") AllureHelper::SetFeature(value);
        else if (name == "story") AllureHelper::SetStory(value);
    }
    
    void Severity(const std::string& level) {
        AllureHelper::SetSeverity(level);
    }
    
    void Feature(const std::string& feature) {
        AllureHelper::SetFeature(feature);
    }
    
    void Story(const std::string& story) {
        AllureHelper::SetStory(story);
    }
    
    void Tag(const std::string& tag) {
        AllureHelper::AddTag(tag);
    }
    
    void Step(const std::string& stepName) {
        // Step implementation can be added if needed
    }
}

