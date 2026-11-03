#include <iostream>
#include "c01Problem008.hpp"

#include "../../../Shared/Input.hpp"

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

namespace c01Problem008 {

    struct Solution {
        int count16PortSwitches;
        int count24PortSwitches;
        int count32PortSwitches;
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

        // Absolute safety cap to avoid runaway loops
        const int ABSOLUTE_S_MAX = 1000;

        int S_max = base + margin;
        if (S_max < 50) S_max = max(S_max, 50);
        if (S_max > ABSOLUTE_S_MAX) S_max = ABSOLUTE_S_MAX;

        return S_max;
    }

    // حساب كل التركيبات الممكنة مع تحسينات قطع مبكر PASS 1 إيجاد أقل تكلفة PASS 2 جمع الحلول
    map<int, vector<Solution>> ComputeGroupedSolutions(long long deviceCount) {
        map<int, vector<Solution>> grouped; // cost -> list
        const int P16 = 16, P24 = 24, P32 = 32;
        const int C16 = 100, C24 = 125, C32 = 150;

        // حساب S_min عملياً باستخدام max_ports(S) = 30*S + 2
        long long S_min = max(1LL, (deviceCount - 2 + 29) / 30); // ceil((deviceCount-2)/30)
        int S_max = ComputeSMax(deviceCount, P16, P24, P32);

        long long bestCost = LLONG_MAX;
        bool foundAny = false;

        // PASS 1: نبحث فقط عن أقل تكلفة
        for (int S = (int)S_min; S <= S_max; ++S) {
            long long max_ports_with_S = 30LL * S + 2;
            if (max_ports_with_S < deviceCount) continue;

            long long minPossibleCostForS = 1LL * S * C32;
            if (foundAny && minPossibleCostForS > bestCost) break; // قطع مبكر آمن

            for (int n16 = 0; n16 <= S; ++n16) {
                int max_n24 = S - n16;
                for (int n24 = 0; n24 <= max_n24; ++n24) {
                    int n32 = S - n16 - n24;
                    long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24 + 1LL * n32 * P32;
                    long long ports_available = (S == 1 ? raw_ports : raw_ports - 2LL * (S - 1));
                    if (ports_available < deviceCount) continue;
                    long long cost = 1LL * n16 * C16 + 1LL * n24 * C24 + 1LL * n32 * C32;
                    if (cost < bestCost) {
                        bestCost = cost;
                        foundAny = true;
                    }
                }
            }
        }

        if (!foundAny) {
            return grouped; // empty
        }

        // PASS 2: نجمع الحلول لكن فقط بعد معرفة bestCost ونستخدم قطع مبكر أفضل
        unordered_set<string> seen;

        for (int S = (int)S_min; S <= S_max; ++S) {
            long long max_ports_with_S = 30LL * S + 2;
            if (max_ports_with_S < deviceCount) continue;

            long long minPossibleCostForS = 1LL * S * C32;
            if (minPossibleCostForS > bestCost && !grouped.empty()) {
                // إذا أقل تكلفة ممكنة لهذا S أكبر من bestCost، لا حاجة لفحص S أكبر
                break;
            }

            for (int n16 = 0; n16 <= S; ++n16) {
                int max_n24 = S - n16;
                for (int n24 = 0; n24 <= max_n24; ++n24) {
                    int n32 = S - n16 - n24;
                    long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24 + 1LL * n32 * P32;
                    long long ports_available = (S == 1 ? raw_ports : raw_ports - 2LL * (S - 1));
                    if (ports_available < deviceCount) continue;
                    int cost = n16 * C16 + n24 * C24 + n32 * C32;
                    if (cost >= bestCost) {
                        Solution sol{ n16, n24, n32, S, (int)ports_available, cost };
                        string k = KeyOf(sol);
                        if (seen.insert(k).second) grouped[cost].push_back(sol);
                    }
                }
            }
        }

        return grouped;
    }

    // دالة طباعة النتائج المجمعة
    void PrintGroupedSolutions(const map<int, vector<Solution>>& grouped, long long deviceCount) {
        if (grouped.empty()) {
            cout << "No solution found within limits. Try increasing S_max or adjusting parameters.\n";
            return;
        }

        // أقل تكلفة موجودة في بداية الخريطة
        int bestCost = grouped.begin()->first;

        cout << "\n=== All minimum-cost solutions (cost = $" << bestCost << ") ===\n";
        for (size_t i = 0; i < grouped.at(bestCost).size(); ++i) {
            cout << "Cheap solution #" << (i + 1) << ":\n";
            PrintSolutionDetails(grouped.at(bestCost)[i]);
        }

        cout << "\n=== All higher-cost solution groups (ascending by cost) ===\n";
        for (auto& entry : grouped) {
            if (entry.first == bestCost) continue;
            cout << "\n*** Solutions with cost $" << entry.first << " ***\n";
            auto vec = entry.second;
            sort(vec.begin(), vec.end(), [&](const Solution& a, const Solution& b) {
                int surplusA = a.availablePorts - (int)deviceCount;
                int surplusB = b.availablePorts - (int)deviceCount;
                if (surplusA != surplusB) return surplusA < surplusB;
                if (a.switchCount != b.switchCount) return a.switchCount < b.switchCount;
                if (a.count32PortSwitches != b.count32PortSwitches) return a.count32PortSwitches > b.count32PortSwitches;
                if (a.count24PortSwitches != b.count24PortSwitches) return a.count24PortSwitches < b.count24PortSwitches;
                return a.count16PortSwitches < b.count16PortSwitches;
                });
            for (auto& sol : vec) PrintSolutionDetails(sol);
        }

        cout << "\nNote: The search used a two-pass strategy: first to find the minimum achievable cost, then to collect and display solutions at that cost and above.\n";
    }

    void clsProblem008::Run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long deviceCount = Input::ReadFloatPositiveNumber("Enter number of computers: ");

        auto grouped = ComputeGroupedSolutions(deviceCount);
        PrintGroupedSolutions(grouped, deviceCount);
    }

} // namespace c01Problem008
