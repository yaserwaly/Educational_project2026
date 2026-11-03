#include <iostream>
#include "c01Problem007.hpp"
#include "../../../Registry/DispatcherRegistrar.hpp"

#include "../../../Shared/Input.hpp"

//#include <bits/stdc++.h>
// Minimal bits/stdc++.h replacement for MSVC
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <numeric>
#include <functional>
#include <iomanip>
#include <fstream>

using namespace std;

namespace c01Problem007 {

    struct Solution {
        int count16PortSwitches, count24PortSwitches, count32PortSwitches;
        int switchCount;
        int availablePorts;
        int cost;
    };

    // دالة مساعدة لطباعة حل
    void PrintSolutionDetails(const Solution& s) {
        cout << "16-port switches: " << s.count16PortSwitches << "  |  ";
        cout << "24-port switches: " << s.count24PortSwitches << "  |  ";
        cout << "32-port switches: " << s.count32PortSwitches << "\n";
        cout << "Total switches: " << s.switchCount << "  |  ";
        cout << "Available ports: " << s.availablePorts << "  |  ";
        cout << "Cost: $" << s.cost << "\n";
        cout << "---------------------------------------------\n";
    }

    // مفتاح فريد لتركيبة السويتشات لتفادي التكرار
    string KeyOf(const Solution& s) {
        return to_string(s.count16PortSwitches) + "-" + to_string(s.count24PortSwitches) + "-" + to_string(s.count32PortSwitches) + "-" +
            to_string(s.switchCount) + "-" + to_string(s.availablePorts) + "-" + to_string(s.cost);
    }

    // Helper to compute a practical S_max based on deviceCount and switch port sizes
    static int ComputeSMax(long long deviceCount, int P16 = 16, int P24 = 24, int P32 = 32) {
        if (deviceCount <= 0) return 1;

        // Lower bound from ports_available = 14*S + 2 >= H (worst-case 16-port with 2-port uplink cost)
        long long S_min_est = (deviceCount - 2 + 14 - 1) / 14;
        if (S_min_est < 1) S_min_est = 1;

        // Bounds by pure port counts (ceil)
        int S_by16 = (int)((deviceCount + P16 - 1) / P16);
        int S_by24 = (int)((deviceCount + P24 - 1) / P24);
        int S_by32 = (int)((deviceCount + P32 - 1) / P32);

        // Base estimate
        int base = (int)max(S_min_est, (long long)max(S_by16, max(S_by24, S_by32)));

        // Margin: at least 10, or 20% of base (rounded)
        int margin = max(10, base / 5);

        // Absolute safety cap to avoid runaway loops (تعديل حسب مواردك)
        const int ABSOLUTE_S_MAX = 1000;

        int S_max = base + margin;
        if (S_max < 50) S_max = max(S_max, 50); // ضمان حد أدنى عملي
        if (S_max > ABSOLUTE_S_MAX) S_max = ABSOLUTE_S_MAX;

        return S_max;
    }


    /*int Switchs() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long deviceCount;
        cout << "Enter number of computers: ";
        if (!(cin >> deviceCount) || deviceCount <= 0) {
            cout << "Please enter a positive integer.\n";
            return 0;
        }

        // مواصفات السويتشات
        const int P16 = 16, P24 = 24, P32 = 32;
        const int C16 = 100, C24 = 125, C32 = 150;

        vector<Solution> candidates;

        // حساب حد علوي عملي لعدد السويتشات S_max
        long long S_min_est = max(1LL, (deviceCount - 2 + 13) / 14); // تقريبياً ceil((deviceCount-2)/14)
        int S_max = (int)max((long long)200, S_min_est + 50);
        int S_min_by32 = (int)((deviceCount + P32 - 1) / P32);
        S_max = max(S_max, S_min_by32 + 100);

        for (int S = 1; S <= S_max; ++S) {
            for (int n16 = 0; n16 <= S; ++n16) {
                for (int n24 = 0; n24 <= S - n16; ++n24) {
                    int n32 = S - n16 - n24;
                    long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24 + 1LL * n32 * P32;
                    long long ports_available;
                    if (S == 1) ports_available = raw_ports;
                    else ports_available = raw_ports - 2LL * (S - 1);

                    if (ports_available < 0) continue;
                    if (ports_available >= deviceCount) {
                        int cost = n16 * C16 + n24 * C24 + n32 * C32;
                        candidates.push_back({ n16, n24, n32, S, (int)ports_available, cost });
                    }
                }
            }
        }

        if (candidates.empty()) {
            cout << "No solution found within limits. Try increasing the maximum number of switches.\n";
            return 0;
        }

        // ترتيب عام للمرشحين: تكلفة ثم فائض ثم عدد سويتشات ثم تفضيل سويتشات أكبر
        sort(candidates.begin(), candidates.end(), [&](const Solution& a, const Solution& b) {
            if (a.cost != b.cost) return a.cost < b.cost;
            int surplusA = a.availablePorts - (int)deviceCount;
            int surplusB = b.availablePorts - (int)deviceCount;
            if (surplusA != surplusB) return surplusA < surplusB;
            if (a.switchCount != b.switchCount) return a.switchCount < b.switchCount;
            if (a.count32PortSwitches != b.count32PortSwitches) return a.count32PortSwitches > b.count32PortSwitches;
            if (a.count24PortSwitches != b.count24PortSwitches) return a.count24PortSwitches < b.count24PortSwitches;
            return a.count16PortSwitches < b.count16PortSwitches;
            });

        // 1) إيجاد أقل تكلفة
        int minCost = candidates.front().cost;

        // 2) جمع كل الحلول التي لها نفس أقل تكلفة (بدون تكرار)
        vector<Solution> minCostSolutions;
        unordered_set<string> seen;
        for (const auto& c : candidates) {
            if (c.cost != minCost) break; // لأن القائمة مرتبة حسب التكلفة
            string k = KeyOf(c);
            if (seen.insert(k).second) {
                minCostSolutions.push_back(c);
            }
        }

        // طباعة كل حلول التكلفة الدنيا (بلا حد)
        cout << "\n=== All minimum-cost solutions (cost = $" << minCost << ") ===\n";
        cout << "Number of solutions with same cost: " << minCostSolutions.size() << "\n";
        cout << "---------------------------------------------\n";
        for (size_t i = 0; i < minCostSolutions.size(); ++i) {
            cout << "Cheap solution #" << (i + 1) << ":\n";
            PrintSolutionDetails(minCostSolutions[i]);
        }

        // 3) إيجاد التكلفة التالية الأعلى (nextCost) ثم طباعة حل واحد من تلك التكلفة ثم التوقف
        int nextCost = -1;
        for (const auto& c : candidates) {
            if (c.cost > minCost) {
                nextCost = c.cost;
                break;
            }
        }

        if (nextCost == -1) {
            cout << "\nNo higher-cost solutions found.\n";
            return 0;
        }

        // جمع حلول التكلفة التالية (بدون تكرار) ثم نختار أول حل بعد ترتيبنا
        vector<Solution> nextCostSolutions;
        seen.clear();
        for (const auto& c : candidates) {
            if (c.cost != nextCost) continue;
            string k = KeyOf(c);
            if (seen.insert(k).second) nextCostSolutions.push_back(c);
        }

        // نطبع حل واحد من التكلفة الأعلى (الأفضل بينها حسب ترتيبنا)
        if (!nextCostSolutions.empty()) {
            cout << "\n=== One solution from the next higher cost (cost = $" << nextCost << ") ===\n";
            cout << "More expensive solution (only one shown):\n";
            PrintSolutionDetails(nextCostSolutions.front());
        }
        else {
            cout << "\nNo unique solutions found for the next higher cost.\n";
        }

        cout << "\nNote: The program printed all cheapest combinations first, then printed one solution from the next higher cost.\n";
        return 0;
    }*/

    // حساب كل التركيبات الممكنة ثم اختيار وعرض الحلول ذات أقل تكلفة ثم حل واحد من التكلفة التالية
    Solution ComputeAndDisplayBest(long long deviceCount) {
        Solution emptyResult = { 0,0,0,0,0,0 };

        // مواصفات السويتشات
        const int P16 = 16, P24 = 24, P32 = 32;
        const int C16 = 100, C24 = 125, C32 = 150;

        vector<Solution> candidates;

        // حساب حد علوي عملي لعدد السويتشات S_max
        //long long S_min_est = max(1LL, (deviceCount - 2 + 13) / 14); // تقريبياً ceil((H-2)/14)
        //int S_max = (int)max((long long)200, S_min_est + 50);
        //int S_min_by32 = (int)((deviceCount + P32 - 1) / P32);
        //S_max = max(S_max, S_min_by32 + 100);

		int S_max = ComputeSMax(deviceCount, P16, P24, P32);

        for (int S = 1; S <= S_max; ++S) {
            for (int n16 = 0; n16 <= S; ++n16) {
                for (int n24 = 0; n24 <= S - n16; ++n24) {
                    int n32 = S - n16 - n24;
                    long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24 + 1LL * n32 * P32;
                    long long ports_available = (S == 1 ? raw_ports : raw_ports - 2LL * (S - 1));

                    if (ports_available < 0) continue;
                    if (ports_available >= deviceCount) {
                        int cost = n16 * C16 + n24 * C24 + n32 * C32;
                        candidates.push_back({ n16, n24, n32, S, (int)ports_available, cost });
                    }
                }
            }
        }

        if (candidates.empty()) {
            return emptyResult;
        }

        // ترتيب عام للمرشحين: تكلفة ثم فائض ثم عدد سويتشات ثم تفضيل سويتشات أكبر
        sort(candidates.begin(), candidates.end(), [&](const Solution& a, const Solution& b) {
            if (a.cost != b.cost) return a.cost < b.cost;
            int surplusA = a.availablePorts - (int)deviceCount;
            int surplusB = b.availablePorts - (int)deviceCount;
            if (surplusA != surplusB) return surplusA < surplusB;
            if (a.switchCount != b.switchCount) return a.switchCount < b.switchCount;
            if (a.count32PortSwitches != b.count32PortSwitches) return a.count32PortSwitches > b.count32PortSwitches;
            if (a.count24PortSwitches != b.count24PortSwitches) return a.count24PortSwitches < b.count24PortSwitches;
            return a.count16PortSwitches < b.count16PortSwitches;
            });

        // 1) إيجاد أقل تكلفة
        int minCost = candidates.front().cost;

        // 2) جمع كل الحلول التي لها نفس أقل تكلفة (بدون تكرار)
        vector<Solution> minCostSolutions;
        unordered_set<string> seen;
        for (const auto& c : candidates) {
            if (c.cost != minCost) break; // لأن القائمة مرتبة حسب التكلفة
            string k = KeyOf(c);
            if (seen.insert(k).second) {
                minCostSolutions.push_back(c);
            }
        }

        // طباعة كل حلول التكلفة الدنيا (بلا حد)
        cout << "\n=== All minimum-cost solutions (cost = $" << minCost << ") ===\n";
        cout << "Number of solutions with same cost: " << minCostSolutions.size() << "\n";
        cout << "---------------------------------------------\n";
        for (size_t i = 0; i < minCostSolutions.size(); ++i) {
            cout << "Cheap solution #" << (i + 1) << ":\n";
            PrintSolutionDetails(minCostSolutions[i]);
        }

        // 3) إيجاد التكلفة التالية الأعلى (nextCost) ثم طباعة حل واحد من تلك التكلفة ثم التوقف
        int nextCost = -1;
        for (const auto& c : candidates) {
            if (c.cost > minCost) {
                nextCost = c.cost;
                break;
            }
        }

        if (nextCost == -1) {
            cout << "\nNo higher-cost solutions found.\n";
            return minCostSolutions.front();
        }

        // جمع حلول التكلفة التالية (بدون تكرار) ثم نختار أول حل بعد ترتيبنا
        vector<Solution> nextCostSolutions;
        seen.clear();
        for (const auto& c : candidates) {
            if (c.cost != nextCost) continue;
            string k = KeyOf(c);
            if (seen.insert(k).second) nextCostSolutions.push_back(c);
        }

        // نطبع حل واحد من التكلفة الأعلى (الأفضل بينها حسب ترتيبنا)
        if (!nextCostSolutions.empty()) {
            cout << "\n=== One solution from the next higher cost (cost = $" << nextCost << ") ===\n";
            cout << "More expensive solution (only one shown):\n";
            PrintSolutionDetails(nextCostSolutions.front());
        }
        else {
            cout << "\nNo unique solutions found for the next higher cost.\n";
        }

        cout << "\nNote: The program printed all cheapest combinations first, then printed one solution from the next higher cost.\n";

        return minCostSolutions.front();
    }

    void clsProblem007::Run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long deviceCount = Input::ReadFloatPositiveNumber("Enter number of computers: ");
        Solution result = ComputeAndDisplayBest(deviceCount);
        // result already printed inside ComputeAndDisplayBest; still show brief summary
        cout << "\nSummary (first minimum-cost solution):\n";
        PrintSolutionDetails(result);
    }

    static bool _reg = ([]() {
        nsDispatcherRegistrar::clsDispatcherRegistrar::Register("c01Problem007::clsProblem007::Run", []() {
            c01Problem007::clsProblem007::Run();
        });
        return true;
    })();

}
