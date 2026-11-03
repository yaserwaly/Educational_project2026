#include <iostream>
#include "c01Problem002.hpp"

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

namespace c01Problem002 {

    struct Solution {
        int count16PortSwitches, count24PortSwitches;
        int switchCount;
        int availablePorts;
    };

    // طباعة حل بدون تكلفة
    void PrintSolutionDetails(const Solution& s) {
        cout << "16-port switches: " << s.count16PortSwitches << "  |  ";
        cout << "24-port switches: " << s.count24PortSwitches << "\n";
        cout << "Total switches: " << s.switchCount << "  |  ";
        cout << "Available ports: " << s.availablePorts << "\n";
        cout << "---------------------------------------------\n";
    }

    // Helper to compute a practical S_max based on deviceCount and switch port sizes
    static int ComputeSMax(long long deviceCount, int P16 = 16, int P24 = 24) {
        if (deviceCount <= 0) return 1;

        // Lower bound from ports_available = 14*S + 2 >= H (worst-case 16-port with 2-port uplink cost)
        long long S_min_est = (deviceCount - 2 + 14 - 1) / 14;
        if (S_min_est < 1) S_min_est = 1;

        // Bounds by pure port counts (ceil)
        int S_by16 = (int)((deviceCount + P16 - 1) / P16);
        int S_by24 = (int)((deviceCount + P24 - 1) / P24);

        // Base estimate
        int base = (int)max(S_min_est, (long long)max(S_by16, S_by24));

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

        // Switch specs (32-port removed)
        const int P16 = 16, P24 = 24;

        vector<Solution> candidates;

        // Heuristic bounds for S
        int S_max = 200; // حد عملي يمكن زيادته اذا لزم
        S_max = max(S_max, (int)((deviceCount + P16 - 1) / P16 + 10)); // buffer

        for (int S = 1; S <= S_max; ++S) {
            // iterate all partitions n16 + n24 = S
            for (int n16 = 0; n16 <= S; ++n16) {
                int n24 = S - n16;

                long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24;
                long long ports_available;

                if (S == 1) {
                    ports_available = raw_ports;
                }
                else {
                    ports_available = raw_ports - 2LL * (S - 1);
                }

                if (ports_available < 0) continue;
                if (ports_available >= deviceCount) {
                    candidates.push_back({ n16, n24, S, (int)ports_available });
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
            // نختار الحل بأقل عدد سويتشات S، ثم الأقرب إلى deviceCount (أقل فائض)، ثم نفضّل أكثر 24-ports
            Solution best = list[0];
            for (size_t i = 1; i < list.size(); ++i) {
                const Solution& s = list[i];

                if (s.switchCount < best.switchCount) {
                    best = s;
                }
                else if (s.switchCount == best.switchCount) {
                    int surplusBest = best.availablePorts - (int)deviceCount;
                    int surplusI = s.availablePorts - (int)deviceCount;
                    if (surplusI < surplusBest) {
                        best = s;
                    }
                    else if (surplusI == surplusBest) {
                        if (s.count24PortSwitches > best.count24PortSwitches) best = s; // تفضيل سويتشات 24 أكثر
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

        cout << "\nBest solution (32-port removed):\n";
        PrintSolutionDetails(best);

        cout << "\nNote: 32-port switches were removed. Selection is based on minimal number of switches, then minimal surplus, then preference for more 24-port switches.\n";

        return 0;
    }*/

    Solution ComputeBestSwitches(long long deviceCount) {
        Solution bestResult = { 0, 0, 0, 0 };

        // Switch specs (32-port removed)
        const int P16 = 16, P24 = 24;

        vector<Solution> candidates;

        // Heuristic bounds for S
        //int S_max = 200; // حد عملي يمكن زيادته اذا لزم
        //S_max = max(S_max, (int)((deviceCount + P16 - 1) / P16 + 10)); // buffer

		int S_max = ComputeSMax(deviceCount, P16, P24);

        for (int S = 1; S <= S_max; ++S) {
            // iterate all partitions n16 + n24 = S
            for (int n16 = 0; n16 <= S; ++n16) {
                int n24 = S - n16;

                long long raw_ports = 1LL * n16 * P16 + 1LL * n24 * P24;
                long long ports_available;

                if (S == 1) {
                    ports_available = raw_ports;
                }
                else {
                    ports_available = raw_ports - 2LL * (S - 1);
                }

                if (ports_available < 0) continue;
                if (ports_available >= deviceCount) {
                    candidates.push_back({ n16, n24, S, (int)ports_available });
                }
            }
        }

        // إذا لم نجد مرشحين (نادر) نعيد نتيجة افتراضية
        if (candidates.empty()) {
            return bestResult;
        }

        // تفضيل الحلول التي تطابق بالضبط deviceCount
        vector<Solution> exact;
        for (auto& c : candidates) if (c.availablePorts == deviceCount) exact.push_back(c);

        auto pick_best = [&](const vector<Solution>& list) {
            // نختار الحل بأقل عدد سويتشات S، ثم الأقرب إلى deviceCount (أقل فائض)، ثم نفضّل أكثر 24-ports
            Solution best = list[0];
            for (size_t i = 1; i < list.size(); ++i) {
                const Solution& s = list[i];

                if (s.switchCount < best.switchCount) {
                    best = s;
                }
                else if (s.switchCount == best.switchCount) {
                    int surplusBest = best.availablePorts - (int)deviceCount;
                    int surplusI = s.availablePorts - (int)deviceCount;
                    if (surplusI < surplusBest) {
                        best = s;
                    }
                    else if (surplusI == surplusBest) {
                        if (s.count24PortSwitches > best.count24PortSwitches) best = s; // تفضيل سويتشات 24 أكثر
                    }
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

    void clsProblem002::Run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long deviceCount = Input::ReadLongLongPositiveNumber("Enter number of computers: ");
        Solution result = ComputeBestSwitches(deviceCount);
        cout << "\nBest solution (32-port removed):\n";
        PrintSolutionDetails(result);
        
        cout << "\nNote: 32-port switches were removed. Selection is based on minimal number of switches, then minimal surplus, then preference for more 24-port switches.\n";
    }

}