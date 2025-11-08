#include <gtest/gtest.h>
#include "utils.hpp"

// Test trim with leading spaces
TEST(UtilsTest, TrimLeadingSpaces) {
    std::string input = "  hello";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}

// Test trim with trailing spaces
TEST(UtilsTest, TrimTrailingSpaces) {
    std::string input = "hello  ";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}

// Test trim with both leading and trailing spaces
TEST(UtilsTest, TrimBothEnds) {
    std::string input = "  hello  ";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}

// Test trim with tabs and newlines
TEST(UtilsTest, TrimWhitespace) {
    std::string input = "\t\nhello\n\t";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}

// Test trim with only whitespace
TEST(UtilsTest, TrimOnlyWhitespace) {
    std::string input = "   \t\n  ";
    std::string result = Utils::trim(input);
    EXPECT_TRUE(result.empty());
}

// Test trim with empty string
TEST(UtilsTest, TrimEmptyString) {
    std::string input;
    std::string result = Utils::trim(input);
    EXPECT_TRUE(result.empty());
}

// Test trim with no whitespace
TEST(UtilsTest, TrimNoWhitespace) {
    std::string input = "hello";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}

// Test trim with mixed whitespace characters
TEST(UtilsTest, TrimMixedWhitespace) {
    std::string input = " \t \n hello \r \f \v ";
    std::string result = Utils::trim(input);
    EXPECT_EQ(result, "hello");
}
