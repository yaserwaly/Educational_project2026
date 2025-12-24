#pragma once

#include <string>

namespace nsDefaultCourse {

    // Class for handling default course storage – كلاس لمعالجة تخزين الدورة الافتراضية
    class clsDefaultCourse {
    private:
        /**
         * Path to the file storing the default course code – مسار الملف الذي يخزن كود الدورة الافتراضية
         */
        std::string StoragePath;

    public:
        /**
         * Constructor to initialize with optional file path – مُنشئ لتهيئة الكلاس بمسار ملف اختياري
         * @param path path to the default course file – مسار ملف الدورة الافتراضية
         */
        clsDefaultCourse(const std::string& path = "Courses/DefaultCourse.txt");

        /**
         * Load the default course code from file – تحميل كود الدورة الافتراضية من الملف
         * @return course code if found, -1 if not – يرجع الكود إذا وُجد، أو -1 إذا لم يُوجد
         */
        int Load() const;

        /**
         * Save the given course code to file – حفظ كود الدورة المحدد في الملف
         * @param code course code to save – الكود المطلوب حفظه
         */
        void Save(int code) const;

        /**
         * Clear the contents of the default course file – مسح محتويات ملف الدورة الافتراضية
         */
        void Clear() const;

        /**
         * Remove the default course file from disk – حذف ملف الدورة الافتراضية من القرص
         */
        void Remove() const;

        /**
         * Check if the default course file exists – التحقق من وجود ملف الدورة الافتراضية
         * @return true if file exists – يرجع true إذا كان الملف موجودًا
         */
        bool Exists() const;
    };

}
