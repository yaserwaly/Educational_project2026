#include <iostream>
#include "c01Problem001.hpp"
#include "../../../Registry/DispatcherRegistrar.hpp"

namespace c01Problem001 {

    void clsProblem001::Run() {
        std::cout << "Hello from Problem 01!\n";
        std::cout << 5 * 15;
    }

    static bool _reg = ([]() {
        nsDispatcherRegistrar::clsDispatcherRegistrar::Register("c01Problem001::clsProblem001::Run", []() {
            c01Problem001::clsProblem001::Run();
            });
        return true;
        })();

}
