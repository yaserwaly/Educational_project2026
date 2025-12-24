#pragma once

#include <string>

namespace nsDefaultProblem {

    // Class for handling default problem storage per course – كلاس لمعالجة تخزين المشكلة الافتراضية لكل دورة
    class clsDefaultProblem {
    private:
        /**
         * ID of the course associated with the default problem – معرف الدورة المرتبطة بالمشكلة الافتراضية
         */
        int CourseID;

        /**
         * Generate the file path for storing the default problem – توليد مسار الملف الخاص بالمشكلة الافتراضية
         * @return full path to the default problem file – يرجع المسار الكامل لملف المشكلة الافتراضية
         */
        std::string FilePath() const;

    public:
        /**
         * Constructor to initialize with course ID – مُنشئ لتهيئة الكلاس بمعرّف الدورة
         * @param courseID ID of the course – معرف الدورة
         */
        clsDefaultProblem(int courseID);

        /**
         * Load the default problem code from file – تحميل كود المشكلة الافتراضية من الملف
         * @return problem code if found, -1 if not – يرجع الكود إذا وُجد، أو -1 إذا لم يُوجد
         */
        int Load() const;

        /**
         * Save the given problem code to file – حفظ كود المشكلة المحددة في الملف
         * @param code problem code to save – الكود المطلوب حفظه
         */
        void Save(int code) const;

        /**
         * Clear the contents of the default problem file – مسح محتويات ملف المشكلة الافتراضية
         */
        void Clear() const;

        /**
         * Remove the default problem file from disk – حذف ملف المشكلة الافتراضية من القرص
         */
        void Remove() const;

        /**
         * Check if the default problem file exists – التحقق من وجود ملف المشكلة الافتراضية
         * @return true if file exists – يرجع true إذا كان الملف موجودًا
         */
        bool Exists() const;
    };

}
