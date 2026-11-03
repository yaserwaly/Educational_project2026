#include <iostream>
#include "c01Problem001.hpp"

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

namespace c01Problem001 {

    struct Solution {
        //int count16PortSwitches;
        int switchCount;
        int availablePorts;
    };

    // طباعة حل بدون تكلفة وبدون 24-port
    void PrintSolutionDetails(const Solution& s) {
        //cout << "16-port switches: " << s.count16PortSwitches << "\n";
        cout << "Total switches: " << s.switchCount << "  |  ";
        cout << "Available ports: " << s.availablePorts << "\n";
        cout << "---------------------------------------------\n";
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

        // Switch specs (only 16-port)
        const int P16 = 16;

        vector<Solution> candidates;

        // Heuristic bounds for S
        int S_max = 200; // حد عملي يمكن زيادته اذا لزم
        S_max = max(S_max, (int)((deviceCount + P16 - 1) / P16 + 10)); // buffer

        for (int S = 1; S <= S_max; ++S) {
            // iterate all partitions n16 = S (since only 16-port exists)
            int n16 = S;

            long long raw_ports = 1LL * n16 * P16;
            long long ports_available;

            if (S == 1) {
                ports_available = raw_ports;
            }
            else {
                ports_available = raw_ports - 2LL * (S - 1);
            }

            if (ports_available < 0) continue;
            if (ports_available >= deviceCount) {
                candidates.push_back({ n16, S, (int)ports_available });
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
            // نختار الحل بأقل عدد سويتشات S، ثم الأقرب إلى deviceCount (أقل فائض)
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

        cout << "\nBest solution (only 16-port switches):\n";

        PrintSolutionDetails(best);

        cout << "\nNote: 24-port and 32-port switches were removed. Selection is based on minimal number of switches, then minimal surplus.\n";

        return 0;
    }*/

    Solution ComputeMinimumSwitches(long long deviceCount) {
        Solution result;
        // حساب S_min مباشرة من المعادلة ports_available = 14*S + 2 >= H
        long long minSwitchCount = (deviceCount - 2 + 14 - 1) / 14; // ceil((deviceCount-2)/14)
        if (minSwitchCount < 1) minSwitchCount = 1;

        result.switchCount = (int)minSwitchCount;
        result.availablePorts = 14 * result.switchCount + 2; // كما اشتقنا
        //result.count16PortSwitches = (int)result.switchCount;

        return result;
    }


    void clsProblem001::Run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        long long deviceCount = Input::ReadFloatPositiveNumber("Enter number of computers: ");
        Solution result = ComputeMinimumSwitches(deviceCount);
        cout << "\nBest solution (only 16-port switches):\n";
        PrintSolutionDetails(result);
        
        cout << "\nNote: No search performed. Computed minimal S using 14*S+2 >= H.\n";
    }

}