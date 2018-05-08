#include <random>
#include <sstream>

#include "ascii_cube.hpp"
#include "game.hpp"

struct pll_scramble_gen
{
    std::string operator()()
    {
        const char *uy_algos[] = {
            "U", "U'", "U2",
            "DW", "DW'", "DW2",
            "Y", "Y'", "Y2",
        };
        const char *pll_algos[] = {
            "RU'RU-RURU'R'U'R2",                  // n1b, U
            "R2U-RUR'U'-R'U'-R'UR'",              // n2b, U
            "UR'U'RU'RURU'R'URUR2U'R'U",          // n5,  Z
            "M2'UM2'U2M2'UM2'",                   // n6,  H
            "x'L'UL'D2'LU'L'D2L2x",               // n4,  A
            "x'RU'RD2'R'URD2R2x",                 // n3,  A
            "RU*R'U'R'FR2-U'R'U'RUR'F'*",         // n8,  T
            "R'URU'-R2'F'U'F-URU'RLw-U'R'Ux",     // n10, F (Cubefreak's old F)
            "R'U2'RU2'-R'FRUR'U'-R'F'R2U'",       // n11, Ra
            "U'RU'R'U'RURD-R'U'RD'R'U2'R'",       // n12, Rb (not what i use)
            "RU2'R'U'RU2'-L'UR'U'L",              // n13, Ja
            "R'U2'RUR'U2'-LU'RUL'",               // n14, Jb
            "R'UR'Dw'-R'F'R2-U'R'ULw'-URUx'(y')", // n9,  V
            "FRU'R'U'RUR'F'*RUR'U'-R'FRF'",       // n15, Y
            "R'UR'FRF'RU'R'F'UF-RUR'U'R",         // n20, Nb
            "LU'RU2L'UR'-LU'RU2L'UR'-U'",         // n21, Na
            "xUR'U'L-URU'Rw2'U'RULU'R'Ux",        // n7,  E
            "RUR'y'-R2Uw'RU'R'U-R'UwR2(y)",       // n16, Ga
            "L'U'Ly-L2'UwL'ULU'-LUw'L2(y')",      // n17, Gb
            "R2Uw'RU'RUR'-Uw-(R2'x)UwR'Uw'x'",    // n18, Gc
            "R2'UwR'UR'U'RUw'-(R2x)-Dw'RUz'(y')", // n19, Gd
            // "R'UR'U'-R'U'-R'URUR2",               // n1a, U (FB mirror of n1b)
            // "R2U'R'U'RU-RURU'R",                  // n2a, U (FB mirror of n2b)
            // "xR'UR'DDRU'R'DDR2x'",                // n4,  A  (not what i use)
            // "xR2'DDRUR'DDRU'Rx'",                 // n3,  A  (not what i use)
            // "R'U'F'*RUR'-U'R'FR2-U'R'U'RUR'UR",   // n10, F
            // "R'URU'-R2'F'U'F-URU'R2B'R'B",        // n10, F ("Old F, but with less rotation")
            // "R'UR'Dw'-R'F'R2U'R'UR'FRF",          // n9,  V
            // "R2U'R'U(RU'x')z'-L'U'RU'R'U'LU",     // n15, Y
            // "U-LU'R-U2'L'ULR'U'RU2'L'UR'",        // n21, Na
            // "x'RU'R'DRUR'D'RUR'DRU'R'D'x",        // n7, E
            // "R2Uw-R'UR'U'RUw'-(R2x')-Uw'RUw",     // n19, Gd (refingering of what I do)
        };
        std::random_device rd;
        std::mt19937       gen(rd());
        std::uniform_int_distribution<> uy_dis(0, sizeof(uy_algos)/sizeof(const char*)-1);
        std::uniform_int_distribution<> pll_dis(0, sizeof(pll_algos)/sizeof(const char*)-1);
        std::ostringstream oss;
        bool first = true;
        for (int i = 0; i < 30; ++i)
        {
            if (not first)
            {
                oss << "       ";
            }
            first = false;
            oss << uy_algos[uy_dis(gen)];
            oss << pll_algos[pll_dis(gen)];
        }
        return oss.str();
    }

    std::mt19937                    gen{std::random_device{}()};
    std::uniform_int_distribution<> dis{0, 17};
};

int main()
{
    play_game(pll_scramble_gen{}, [](cube c) { draw_single(c); });
}
