#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include <sstream>
#include <iomanip>

namespace nsDispatcherRegistrar {

    /**
     * Responsible for registering and mapping problem dispatchers – مسؤول عن تسجيل وربط دوال تنفيذ المشاكل
     */
    class clsDispatcherRegistrar {
    public:
        /**
         * Access the internal map of registered dispatchers – الوصول إلى خريطة الدوال المسجّلة داخليًا
         *
         * @return reference to the dispatcher map – مرجع إلى خريطة التنفيذ
         */
        static std::unordered_map<std::string, std::function<void()>>& Map() {
            static std::unordered_map<std::string, std::function<void()>> m;
            return m;
        }

        /**
         * Generate a unique key from course and problem IDs – توليد مفتاح فريد باستخدام معرف الدورة والمشكلة
         *
         * @param courseId ID of the course – معرف الدورة
         * @param problemId ID of the problem – معرف المشكلة
         * @return formatted key like "c02p00" – مفتاح منسّق مثل "c02p00"
         */
        static std::string MakeKey(int courseId, int problemId) {
            std::ostringstream oss;
            oss << "c" << std::setw(2) << std::setfill('0') << courseId
                << "p" << std::setw(2) << std::setfill('0') << problemId;
            return oss.str();
        }

        /**
         * Register a dispatcher using course/problem IDs – تسجيل دالة تنفيذ باستخدام معرفات الدورة والمشكلة
         *
         * @param courseId ID of the course – معرف الدورة
         * @param problemId ID of the problem – معرف المشكلة
         * @param fn function to execute – الدالة المطلوب تنفيذها
         */
        static void Register(int courseId, int problemId, const std::function<void()>& fn) {
            Map()[MakeKey(courseId, problemId)] = fn;
        }

        /**
         * Register a dispatcher using a custom name – تسجيل دالة تنفيذ باستخدام اسم مخصص
         *
         * @param name custom key or namespace – مفتاح مخصص أو namespace
         * @param fn function to execute – الدالة المطلوب تنفيذها
         */
        static void Register(const std::string& name, const std::function<void()>& fn) {
            Map()[name] = fn;
        }
    };

}
