#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <iostream>
#include "DispatcherRegistrar.hpp"

namespace nsDispatcherRunner {

    /**
     * Responsible for executing registered problem logic – مسؤول عن تنفيذ منطق المشاكل المسجّلة
     */
    class clsDispatcherRunner {
    public:
        /**
         * Run a problem using course and problem IDs – تشغيل مشكلة باستخدام معرف الدورة ومعرف المشكلة
         *
         * @param courseId ID of the course – معرف الدورة
         * @param problemId ID of the problem – معرف المشكلة
         */
        static void Run(int courseId, int problemId) {
            std::string key = nsDispatcherRegistrar::clsDispatcherRegistrar::MakeKey(courseId, problemId);
            auto it = nsDispatcherRegistrar::clsDispatcherRegistrar::Map().find(key);
            if (it != nsDispatcherRegistrar::clsDispatcherRegistrar::Map().end()) {
                it->second(); // Execute registered function – تنفيذ الدالة المسجّلة
            }
            else {
                std::cout << "Problem not implemented: " << key << "\n"; // لم يتم تنفيذ المشكلة
            }
        }

        /**
         * Run a problem using a custom name or namespace – تشغيل مشكلة باستخدام اسم مخصص أو namespace
         *
         * @param name custom key or namespace – مفتاح مخصص أو مساحة اسم
         */
        static void Run(const std::string& name) {
            auto it = nsDispatcherRegistrar::clsDispatcherRegistrar::Map().find(name);
            if (it != nsDispatcherRegistrar::clsDispatcherRegistrar::Map().end()) {
                it->second(); // Execute registered function – تنفيذ الدالة المسجّلة
            }
            else {
                std::cout << "Problem not implemented: " << name << "\n"; // لم يتم تنفيذ المشكلة
            }
        }
    };

}
