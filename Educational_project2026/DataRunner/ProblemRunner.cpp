#include "pch.h"
#include "../Registry/DispatcherRunner.hpp"
#include "ProblemRunner.hpp"

namespace ProblemRunner {

    /**
     * Run a problem by invoking its registered dispatcher logic – تشغيل المشكلة عبر مناداة منطق التنفيذ المسجّل
     *
     * @param ns full namespace signature of the problem – التوقيع الكامل لـ namespace الخاص بالمشكلة
     */
    void RunProblem(const std::string& ns) {
        nsDispatcherRunner::clsDispatcherRunner::Run(ns); // Execute the registered function – تنفيذ الدالة المسجّلة
    }

}
