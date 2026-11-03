#include "pch.h"
#include "ProblemActions.hpp"
// #include <iostream>  // مكرر: موجود أصلاً بـ pch.h
#include <unordered_set>
#include <limits>
#include "../UIHelpers.hpp"
//#include "../Managers/ProblemManager.hpp"
//#include "../Registry/FileHelpers.hpp"
#include "../Adapters/Repositories/ProblemRepositoryAdapter.hpp"

using namespace std;

namespace nsProblemActions {

    enum enProblemUpdateMenuOptions {
        eNameCourse = 1,
        eDescriptionCourse = 2,
        eFullDescriptionCourse = 3,
        eAllInfoCourse = 4,
        eExitUpdate = 5
    };

    static nsProblemData::sProblemData NewDataProblem() {
        nsProblemData::sProblemData newProblem{};
        newProblem.Name = UIHelpers::ReadString("Enter Problem Name? ");
        newProblem.Description = UIHelpers::ReadString("Enter Problem Description? ");
        newProblem.FullDescription = UIHelpers::ReadString("Enter Problem Full Description? ");
        return newProblem;
    }

    bool clsProblemActions::AddNewProblem(nsCourseData::sCourseData& Course) {
        nsProblemData::sProblemData newProblem = NewDataProblem();

        /*nsProblemManager::clsProblemManager manager(Course);
        int nextProblemIndex = manager.GetNextProblemIDSafe();

        if (manager.CreateProblemOnDisk(Course.ID, newProblem, nextProblemIndex, 3)) {
            std::cout << "Problem created successfully. Name: " << newProblem.Name << "\n";
            return true;
        }*/

        nsAdapters::clsProblemRepositoryAdapter ProblemRepo;
        if (ProblemRepo.SaveProblem(Course.ID, newProblem))
        {
            std::cout << "Problem created successfully. Name: " << newProblem.Name << "\n";
            return true;
        }


        std::cout << "Failed to create problem.\n";
        return false;
    }

    static nsProblemData::sProblemData ShowProblemsUpdateMenueOption(enProblemUpdateMenuOptions opt, nsProblemData::sProblemData& Problem) {
        nsProblemData::sProblemData updated{};
        updated.ID = Problem.ID;

        switch (opt) {
        case eNameCourse:
            updated.Name = UIHelpers::ReadString("Enter New Problem Name? ");
            updated.Description = Problem.Description;
            updated.FullDescription = Problem.FullDescription;
            break;
        case eDescriptionCourse:
            updated.Name = Problem.Name;
            updated.Description = UIHelpers::ReadString("Enter New Description? ");
            updated.FullDescription = Problem.FullDescription;
            break;
        case eFullDescriptionCourse:
            updated.Name = Problem.Name;
            updated.Description = Problem.Description;
            updated.FullDescription = UIHelpers::ReadString("Enter New Full Description? ");
            break;
        case eAllInfoCourse:
            updated.Name = UIHelpers::ReadString("Enter New Problem Name? ");
            updated.Description = UIHelpers::ReadString("Enter New Description? ");
            updated.FullDescription = UIHelpers::ReadString("Enter New Full Description? ");
            break;
        case eExitUpdate:
            updated = Problem;
            break;
        }

        return updated;
    }

    static void ShowProblemUpdateMenu() {
        cout << "========================================\n";
        cout << "\t\tModify Menu Problem\n";
        cout << "========================================\n";
        cout << "\t[1] Modify Name Problem.\n";
        cout << "\t[2] Modify Description Problem.\n";
        cout << "\t[3] Modify Full Description Problem.\n";
        cout << "\t[4] Modify All Info Problem.\n";
        cout << "\t[5] Exit.\n";
        cout << "========================================\n";
    }

    static nsProblemData::sProblemData HandleProblemUpdateMenu(nsProblemData::sProblemData& Problem) {
        ShowProblemUpdateMenu();
        int opt = UIHelpers::ReadInt("Enter Option Menu: ", 1, 5);
        return ShowProblemsUpdateMenueOption((enProblemUpdateMenuOptions)opt, Problem);
    }

    bool clsProblemActions::UpdateProblem(nsCourseData::sCourseData& Course, nsProblemData::sProblemData& selectedProblem) {
        nsProblemData::sProblemData Updated = HandleProblemUpdateMenu(selectedProblem);

        nsAdapters::clsProblemRepositoryAdapter ProblemRepo;
        if (ProblemRepo.UpdateProblem(Course.ID, Updated)) {
            std::cout << "Problem modified successfully. Name: " << Updated.Name << "\n";
            selectedProblem = Updated;
            return true;
        }

        std::cout << "Failed to modify problem.\n";
        return false;
    }

    bool clsProblemActions::DeleteProblem(const nsCourseData::sCourseData& Course, const nsProblemData::sProblemData& selectedProblem) {
        if (!UIHelpers::ConfirmYes("Are you sure you want to DELETE this problem?")) {
            std::cout << "Deletion cancelled.\n";
            return false;
        }

        /*nsProblemManager::clsProblemManager manager(const_cast<nsCourseData::sCourseData&>(Course));
        if (manager.DeleteProblemFromDiskAndProject(Course.ID, selectedProblem.ID, 3, "Educational_project.vcxproj")) {
            std::cout << "Problem deleted successfully.\n";
            return true;
        }*/

        nsAdapters::clsProblemRepositoryAdapter ProblemRepo;
        if (ProblemRepo.DeleteProblem(Course.ID, selectedProblem.ID)) {
            std::cout << "Problem deleted successfully using NEW system.\n";
            return true;
        }

        std::cout << "Failed to delete problem.\n";
        return false;
    }

}
