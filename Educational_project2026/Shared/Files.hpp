#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace Files
{
    void AddDataLineToFile(std::string FileName, std::string stDataLine)
    {
        std::fstream MyFile;
        MyFile.open(FileName, std::ios::out | std::ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << "\n";
            MyFile.close();
        }
    }
}