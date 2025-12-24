#pragma once

#include <iostream>
#include <string>

//using namespace std;

namespace Input
{
    short ReadShortNumber(std::string Message, short From = -32768, short To = 32767)
    {
        short Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number < From || Number > To);

        return Number;
    }

    short ReadShortPositiveNumber(std::string Message, short From = -32768, short To = 32767)
    {
        short Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number <= 0 || Number < From || Number > To);

        return Number;
    }

    short ReadShortNegativeNumber(std::string Message, short From = -32768, short To = 32767)
    {
        short Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number > 0 || Number < From || Number > To);

        return Number;
    }

    int ReadIntNumber(std::string Message, int From = -2147483648, int To = 2147483647)
    {
        int Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number < From || Number > To);

        return Number;
    }

    int ReadIntPositiveNumber(std::string Message, int From = -2147483648, int To = 2147483647)
    {
        int Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number <= 0 || Number < From || Number > To);

        return Number;
    }

    int ReadIntNegativeNumber(std::string Message, int From = -2147483648, int To = 2147483647)
    {
        int Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number > 0 || Number < From || Number > To);

        return Number;
    }

    long long ReadLongLongNumber(std::string Message, long long From = -9223372036854775807 - 1, long long To = 9223372036854775807)
    {
        long long Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number < From || Number > To);

        return Number;
    }

    long long ReadLongLongPositiveNumber(std::string Message, long long From = -9223372036854775807 - 1, long long To = 9223372036854775807)
    {
        long long Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number <= 0 || Number < From || Number > To);

        return Number;
    }

    long long ReadLongLongNegativeNumber(std::string Message, long long From = -9223372036854775807 - 1, long long To = 9223372036854775807)
    {
        long long Number = 0;

        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number > 0 || Number < From || Number > To);

        return Number;
    }

    float ReadFloatNumber(std::string Message, float From = FLT_MIN, float To = FLT_MAX)
    {
        float Number = 0;
        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number < From || Number > To);

        return Number;
    }

    float ReadFloatPositiveNumber(std::string Message, float From = FLT_MIN, float To = FLT_MAX)
    {
        float Number = 0;
        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number <= 0 || Number < From || Number > To);

        return Number;
    }

    float ReadFloatNegativeNumber(std::string Message, float From = FLT_MIN, float To = FLT_MAX)
    {
        float Number = 0;
        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number > 0 || Number < From || Number > To);

        return Number;
    }

    double ReadDoubleNumber(std::string Message, double From = DBL_MIN, double To = DBL_MAX)
    {
        double Number = 0;
        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number < From || Number > To);

        return Number;
    }

    double ReadDoublePositiveNumber(std::string Message, double From = DBL_MIN, double To = DBL_MAX)
    {
        double Number = 0;
        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number <= 0 || Number < From || Number > To);

        return Number;
    }

    double ReadDoubleNegativeNumber(std::string Message, double From = DBL_MIN, double To = DBL_MAX)
    {
        double Number = 0;
        do
        {
            std::cout << Message;
            std::cin >> Number;
        } while (Number > 0 || Number < From || Number > To);

        return Number;
    }

    std::string ReadString(std::string Message)
    {
        std::string S1 = "";
        std::cout << Message;
        std::getline(std::cin >> std::ws, S1);
        return S1;
    }

    char ReadChar(std::string Message)
    {
        char Ch1;
        std::cout << Message;
        std::cin >> Ch1;
        return Ch1;
    }
}