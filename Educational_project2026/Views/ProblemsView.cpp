#include "ProblemsView.hpp"
#include <iostream>

namespace nsProblemsView {

    /**
     * Display detailed information about a single problem – عرض معلومات تفصيلية عن مشكلة واحدة
     *
     * @param problem the problem to display – المشكلة المطلوب عرضها
     */
    void clsProblemsView::ShowProblemInfo(const nsProblemData::sProblemData& problem) {
        system("cls"); // Clear screen – مسح الشاشة
        std::cout << "========================================\n";
        std::cout << "\t\tProblem Info\n";
        std::cout << "========================================\n";
        std::cout << "Name            : " << problem.Name << "\n";             // اسم المشكلة
        std::cout << "Description     : " << problem.Description << "\n";      // وصف مختصر
        std::cout << "Full Description: " << problem.FullDescription << "\n";  // وصف تفصيلي
        std::cout << "Namespace       : " << problem.Namespace << "\n";        // مساحة الاسم للتنفيذ
        std::cout << "File Path       : " << problem.FilePath << "\n";         // مسار الملف
        std::cout << "========================================\n\n";
    }

    /**
     * Display a list of all available problems – عرض قائمة بجميع المشاكل المتاحة
     *
     * @param views simplified problem views – نماذج عرض مبسّطة للمشاكل
     */
    void clsProblemsView::ListProblems(const std::vector<nsViewModels::sProblemView>& views) {
        std::cout << "========================================\n";
        std::cout << "\t\tAvailable Problems\n";
        std::cout << "========================================\n";
        for (const auto& p : views) {
            std::cout << "- (ID: " << p.Code << ") " << p.Name << " -- " << p.Description << "\n";
            // عرض رمز المشكلة واسمها ووصفها المختصر
        }
        std::cout << "========================================\n";
    }

}
