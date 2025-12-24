#pragma once
#include <string>

namespace UIHelpers {

    // يطبع عنوان منسّق
    void PrintHeader(const std::string& title);

    // يطبع خط فاصل
    void PrintDivider();

    // يوقف التنفيذ حتى ضغط مفتاح
    void Pause();

    // يقرأ عدد صحيح ضمن مجال محدد
    int ReadInt(const std::string& prompt, int min, int max);

    // يقرأ نص من المستخدم
    std::string ReadString(const std::string& prompt);

    // يسأل المستخدم سؤال نعم/لا
    bool ConfirmYes(const std::string& question);

}
