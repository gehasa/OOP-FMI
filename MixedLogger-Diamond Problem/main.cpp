#include "MixedLogger.hpp"
#include <fstream>
#include <iostream>
#include <cassert>

// Helper to read entire file content
std::string readFile(const std::string& path) {
    std::ifstream in(path);
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return content;
}

void clearFile(const std::string& path) {
    std::ofstream out(path, std::ios::trunc);
}

void runTests() {
    std::string file = "log.txt";
    clearFile(file);

    std::cout << "Running Tests...\n";

    MixedLogger logger(file, "[Test]");

    // Test 1: Basic log
    logger.log("Hello World!");
    std::string content = readFile(file);
    assert(content.find("[Test] Hello World!") != std::string::npos);
    std::cout << "Test 1 Passed\n";

    // Test 2: Empty message
    logger.log("");
    content = readFile(file);
    assert(content.find("[Test] ") != std::string::npos);
    std::cout << "Test 2 Passed\n";

    // Test 3: Long message
    std::string longMsg(1000, 'x');
    logger.log(longMsg);
    content = readFile(file);
    assert(content.find("[Test] " + longMsg) != std::string::npos);
    std::cout << "Test 3 Passed\n";

    // Test 4: Multiple messages
    logger.log("Line 1");
    logger.log("Line 2");
    logger.log("Line 3");
    content = readFile(file);
    assert(content.find("[Test] Line 1") != std::string::npos);
    assert(content.find("[Test] Line 2") != std::string::npos);
    assert(content.find("[Test] Line 3") != std::string::npos);
    std::cout << "Test 4 Passed\n";

    // Test 5: Invalid file name (should throw)
    try {
        MixedLogger badLogger("abc", "[Bad]");
        std::cerr << "Test 5 Failed (Expected exception)\n";
    }
    catch (const std::invalid_argument&) {
        std::cout << "Test 5 Passed\n";
    }

    std::cout << "All tests completed.\n";
}

int main() {
    runTests();
    return 0;
}
