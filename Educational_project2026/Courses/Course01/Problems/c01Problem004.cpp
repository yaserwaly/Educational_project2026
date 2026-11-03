#include <iostream>
#include "c01Problem004.hpp"

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

namespace c01Problem004 {

    struct Solution {
        int count16PortSwitches, count24PortSwitches, count32PortSwitches;
        int switchCount;
        int availablePorts;
        int cost;
    };

    // طباعة حل مع التكلفة
    void PrintSolutionDetails(const Solution& s) {
        cout << "16-port switches: " << s.count16PortSwitches << "  |  ";
        cout << "24-port switches: " << s.count24PortSwitches << "  |  ";
        cout << "32-port switches: " << s.count32PortSwitches << "\n";
        cout << "Total switches: " << s.switchCount << "  |  ";
        cout << "Available ports: " << s.availablePorts << "  |  ";
        cout << "Cost: $" << s.cost << "\n";
        cout << "---------------------------------------------\n";
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

        // Switch specs
        const int P16 = 16, P24 = 24, P32 = 32;
        const int C16 = 100, C24 = 125, C32 = 150;

        vector<Solution> candidates;

        // Heuristic bounds for S
        int S_max = 200; // حد عملي يمكن زيادته اذا لزم
        // يمكن تحسين S_max بناءً على deviceCount:
        S_max = max(S_max, (int)((deviceCount + P16 - 1) / P16 + 10)); // buffer

        for (int S = 1; S <= S_max; ++S) {
            // iterate all partitions n16 + n24 + n32 = S
            for (int n16 = 0; n16 <= S; ++n16) {
                for (int n24 = 0; n24 <= S - n16; ++n24) {
                    int n32 = S - n16 - n24;

                    long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24 + 1LL * n32 * P32;
                    long long ports_available;

                    if (S == 1) {
                        ports_available = raw_ports;
                    }
                    else {
                        ports_available = raw_ports - 2LL * (S - 1);
                    }

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

        // تفضيل الحلول التي تطابق بالضبط deviceCount
        vector<Solution> exact;
        for (auto& c : candidates) if (c.availablePorts == deviceCount) exact.push_back(c);

        auto pick_best = [&](const vector<Solution>& list) {
            // نختار الحل الاقل تكلفة، وإذا تساوت التكلفة نختار الحل ذو اقل عدد سويتشات، ثم اقل فائض منافذ
            Solution best = list[0];
            for (size_t i = 1; i < list.size(); ++i) {
                const Solution& s = list[i];

                if (s.cost < best.cost) best = s;
                else if (s.cost == best.cost) {
                    if (s.switchCount < best.switchCount) best = s;
                    else if (s.availablePorts == best.availablePorts) {
                        if (s.cost < best.cost) best = s;
                    }
                }
            }
            return best;
            };

        Solution best;
        if (!exact.empty()) {
            best = pick_best(exact);
        }
        else {
            best = pick_best(candidates);
        }

        cout << "\nBest solution:\n";
        cout << "16-port switches: " << best.count16PortSwitches << "\n";
        cout << "24-port switches: " << best.count24PortSwitches << "\n";
        cout << "32-port switches: " << best.count32PortSwitches << "\n";
        cout << "Total switches: " << best.switchCount << "\n";
        cout << "Available ports: " << best.availablePorts << "\n";
        cout << "Total cost: $" << best.cost << "\n";

        // عرض تفسير قصير
        cout << "\nNote: The calculation subtracts two ports for each inter-switch link (2*(S-1)).\n";
        cout << "If you want to change the uplink policy (e.g., central uplink or only subtract 1 port on first/last),\n";
        cout << "the formula can be adjusted easily.\n";

        return 0;
    }*/

    // حساب أفضل حل بالبحث البسيط مع مراعاة التكلفة
    Solution ComputeBestSwitches(long long deviceCount) {
        Solution bestResult = { 0, 0, 0, 0, 0, 0 };

        // Switch specs
        const int P16 = 16, P24 = 24, P32 = 32;
        const int C16 = 100, C24 = 125, C32 = 150;

        vector<Solution> candidates;

        // Heuristic bounds for S
        //int S_max = 200; // حد عملي يمكن زيادته اذا لزم
        //S_max = max(S_max, (int)((deviceCount + P16 - 1) / P16 + 10)); // buffer
        
        int S_max = ComputeSMax(deviceCount, P16, P24, P32);

        for (int S = 1; S <= S_max; ++S) {
            // iterate all partitions n16 + n24 + n32 = S
            for (int n16 = 0; n16 <= S; ++n16) {
                for (int n24 = 0; n24 <= S - n16; ++n24) {
                    int n32 = S - n16 - n24;

                    long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24 + 1LL * n32 * P32;
                    long long ports_available;

                    if (S == 1) {
                        ports_available = raw_ports;
                    }
                    else {
                        ports_available = raw_ports - 2LL * (S - 1);
                    }

                    if (ports_available < 0) continue;
                    if (ports_available >= deviceCount) {
                        int cost = n16 * C16 + n24 * C24 + n32 * C32;
                        candidates.push_back({ n16, n24, n32, S, (int)ports_available, cost });
                    }
                }
            }
        }

        // إذا لم نجد مرشحين نعيد نتيجة افتراضية
        if (candidates.empty()) {
            return bestResult;
        }

        // تفضيل الحلول التي تطابق بالضبط deviceCount
        vector<Solution> exact;
        for (auto& c : candidates) if (c.availablePorts == deviceCount) exact.push_back(c);

        auto pick_best = [&](const vector<Solution>& list) {
            // نختار الحل الاقل تكلفة، وإذا تساوت التكلفة نختار الحل ذو اقل فائض ثم اقل عدد سويتشات ثم نفضّل سويتشات 32 أكثر
            Solution best = list[0];
            for (size_t i = 1; i < list.size(); ++i) {
                const Solution& s = list[i];

                if (s.cost < best.cost) {
                    best = s;
                    continue;
                }
                if (s.cost > best.cost) continue;

                int surplus_s = s.availablePorts - (int)deviceCount;
                int surplus_b = best.availablePorts - (int)deviceCount;
                if (surplus_s < surplus_b) {
                    best = s;
                    continue;
                }
                if (surplus_s > surplus_b) continue;

                if (s.switchCount < best.switchCount) {
                    best = s;
                    continue;
                }
                if (s.switchCount > best.switchCount) continue;

                if (s.count32PortSwitches > best.count32PortSwitches) {
                    best = s;
                    continue;
                }
                if (s.count24PortSwitches > best.count24PortSwitches && s.count32PortSwitches == best.count32PortSwitches) {
                    best = s;
                }
            }
            return best;
            };

        if (!exact.empty()) {
            bestResult = pick_best(exact);
        }
        else {
            bestResult = pick_best(candidates);
        }

        return bestResult;
    }

    void clsProblem004::Run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long deviceCount = Input::ReadFloatPositiveNumber("Enter number of computers: ");
        Solution result = ComputeBestSwitches(deviceCount);
        cout << "\nBest solution:\n";
        PrintSolutionDetails(result);

        // عرض تفسير قصير
        cout << "\nNote: The calculation subtracts two ports for each inter-switch link (2*(S-1)).\n";
        cout << "If you want to change the uplink policy (e.g., central uplink or only subtract 1 port on first/last),\n";
        cout << "the formula can be adjusted easily.\n";
    }

}
