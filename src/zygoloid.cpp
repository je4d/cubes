#include "cube.hpp"
#include "algorithms.hpp"

int main()
{
    cube start{}, target{};
    target.r2().f2().u2().f2().r2().f2().u2().f2();
    auto algos =
        find_paths<move::U2, move::D2, move::L2, move::R2, move::F2, move::B2>(
            start, target, 8);
    for (auto alg : algos) {
        for (auto move : alg) {
            std::cout << ' ' << move;
        }
        std::cout << '\n';
    }
}
