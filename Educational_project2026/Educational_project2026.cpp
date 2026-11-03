#include "pch.h"
// Educational_project2026.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include <cstdlib>    // Include cstdlib for rand() and srand() functions.
#include <ctime>      // Include ctime for the time() function.
#include <gtest/gtest.h>
#include <windows.h>
#include "App/AppController.hpp"
#include "Tester/AdaptersTest.hpp"

//int main()
int main(int argc, char** argv)
{
    //std::cout << "Hello World!\n";
    SetConsoleOutputCP(CP_UTF8);  // ⬅️ يخلي الـ console يعرض UTF-8 صح

    srand((unsigned)time(NULL)); // Seed random number generator – تهيئة مولّد الأرقام العشوائية

    // ⬅️ غيّر هاد المتغيّر حسب شو بدك تشغّل
    bool runTestsInstead = false;

    if (runTestsInstead) {
        std::cout << "=== Running TestAdapters ===\n";
        TestAdapters();

        std::cout << "\n=== Running GoogleTest Suite ===\n";
        ::testing::InitGoogleTest(&argc, argv);
        int result = RUN_ALL_TESTS();

        std::cout << "\nGoogleTest exit code: " << result << "\n";
        system("pause>0");
        system("cls");
        //return result;
    }

    nsAppController::clsAppController::StartApp(); // Start the application – بدء تشغيل التطبيق

	//TestAdapters(); // Test the new adapters – اختبار المحولات الجديدة

    system("pause>0"); // Pause before exit – توقف مؤقت قبل الإغلاق
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
