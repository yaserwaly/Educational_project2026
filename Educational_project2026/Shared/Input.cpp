#include "Input.hpp"
#include <iostream>
#include <limits>
#include <string>

namespace Input {

    static void ClearStdinOnFail() {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    short ReadShortNumber(const std::string& Message, short From, short To)
    {
        short Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number < From || Number > To);
        return Number;
    }

    short ReadShortPositiveNumber(const std::string& Message, short From, short To)
    {
        short Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number <= 0 || Number < From || Number > To);
        return Number;
    }

    short ReadShortNegativeNumber(const std::string& Message, short From, short To)
    {
        short Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number >= 0 || Number < From || Number > To);
        return Number;
    }

    int ReadIntNumber(const std::string& Message, int From, int To)
    {
        int Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number < From || Number > To);
        return Number;
    }

    int ReadIntPositiveNumber(const std::string& Message, int From, int To)
    {
        int Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number <= 0 || Number < From || Number > To);
        return Number;
    }

    int ReadIntNegativeNumber(const std::string& Message, int From, int To)
    {
        int Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number >= 0 || Number < From || Number > To);
        return Number;
    }

    long long ReadLongLongNumber(const std::string& Message, long long From, long long To)
    {
        long long Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number < From || Number > To);
        return Number;
    }

    long long ReadLongLongPositiveNumber(const std::string& Message, long long From, long long To)
    {
        long long Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number <= 0 || Number < From || Number > To);
        return Number;
    }

    long long ReadLongLongNegativeNumber(const std::string& Message, long long From, long long To)
    {
        long long Number = 0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number >= 0 || Number < From || Number > To);
        return Number;
    }

    float ReadFloatNumber(const std::string& Message, float From, float To)
    {
        float Number = 0.0f;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number < From || Number > To);
        return Number;
    }

    float ReadFloatPositiveNumber(const std::string& Message, float From, float To)
    {
        float Number = 0.0f;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number <= 0.0f || Number < From || Number > To);
        return Number;
    }

    float ReadFloatNegativeNumber(const std::string& Message, float From, float To)
    {
        float Number = 0.0f;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number >= 0.0f || Number < From || Number > To);
        return Number;
    }

    double ReadDoubleNumber(const std::string& Message, double From, double To)
    {
        double Number = 0.0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number < From || Number > To);
        return Number;
    }

    double ReadDoublePositiveNumber(const std::string& Message, double From, double To)
    {
        double Number = 0.0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number <= 0.0 || Number < From || Number > To);
        return Number;
    }

    double ReadDoubleNegativeNumber(const std::string& Message, double From, double To)
    {
        double Number = 0.0;
        do {
            std::cout << Message;
            std::cin >> Number;
            ClearStdinOnFail();
        } while (Number >= 0.0 || Number < From || Number > To);
        return Number;
    }

    std::string ReadString(const std::string& Message)
    {
        std::string S1;
        std::cout << Message;
        std::getline(std::cin >> std::ws, S1);
        return S1;
    }

    char ReadChar(const std::string& Message)
    {
        char Ch1 = '\0';
        std::cout << Message;
        std::cin >> Ch1;
        ClearStdinOnFail();
        return Ch1;
    }

} // namespace Input
