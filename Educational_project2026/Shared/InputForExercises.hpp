#pragma once

#include <string>
#include <cfloat>
#include <cstdint>

namespace Input
{
    short ReadShortNumber(const std::string& Message, short From = -32768, short To = 32767);
    short ReadShortPositiveNumber(const std::string& Message, short From = -32768, short To = 32767);
    short ReadShortNegativeNumber(const std::string& Message, short From = -32768, short To = 32767);

    int ReadIntNumber(const std::string& Message, int From = INT32_MIN, int To = INT32_MAX);
    int ReadIntPositiveNumber(const std::string& Message, int From = INT32_MIN, int To = INT32_MAX);
    int ReadIntNegativeNumber(const std::string& Message, int From = INT32_MIN, int To = INT32_MAX);

    long long ReadLongLongNumber(const std::string& Message, long long From = LLONG_MIN, long long To = LLONG_MAX);
    long long ReadLongLongPositiveNumber(const std::string& Message, long long From = LLONG_MIN, long long To = LLONG_MAX);
    long long ReadLongLongNegativeNumber(const std::string& Message, long long From = LLONG_MIN, long long To = LLONG_MAX);

    float ReadFloatNumber(const std::string& Message, float From = -FLT_MAX, float To = FLT_MAX);
    float ReadFloatPositiveNumber(const std::string& Message, float From = -FLT_MAX, float To = FLT_MAX);
    float ReadFloatNegativeNumber(const std::string& Message, float From = -FLT_MAX, float To = FLT_MAX);

    double ReadDoubleNumber(const std::string& Message, double From = -DBL_MAX, double To = DBL_MAX);
    double ReadDoublePositiveNumber(const std::string& Message, double From = -DBL_MAX, double To = DBL_MAX);
    double ReadDoubleNegativeNumber(const std::string& Message, double From = -DBL_MAX, double To = DBL_MAX);

    std::string ReadString(const std::string& Message);
    char ReadChar(const std::string& Message);
}