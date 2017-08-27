#include <random>
#include <iomanip>
#include <iostream>
#include <thread>

#include <readline/readline.h>
#include <readline/history.h>

#include "cube.hpp"
#include "ascii_cube.hpp"


void apply_moves(cube& c, std::string scramble)
{
    cube c2 = c;
    const char *op_names[6][3] = {
        {"U", "U'", "U2"}, {"D", "D'", "D2"},
        {"F", "F'", "F2"}, {"B", "B'", "B2"},
        {"L", "L'", "L2"}, {"R", "R'", "R2"}};
    cube &(cube::*ops[6][3])() = {
        {&cube::u, &cube::up, &cube::u2}, {&cube::d, &cube::dp, &cube::d2},
        {&cube::f, &cube::fp, &cube::f2}, {&cube::b, &cube::bp, &cube::b2},
        {&cube::l, &cube::lp, &cube::l2}, {&cube::r, &cube::rp, &cube::r2}};
    enum
    {
        normal,
        modifier
    } mode = normal;
    face f;
    auto handle_modifier_state = [&](auto ch) {
        if (mode == modifier) {
            int move_index = 0;
            switch (ch) {
            case '\'': move_index = 1; break;
            case '2': move_index  = 2; break;
            default: mode = normal; break;
            }
            (c2.*(ops[f][move_index]))();
        }
    };
    for (auto ch : scramble)
    {
        handle_modifier_state(ch);
        if (mode == normal)
        {
            mode = modifier;
            switch (std::toupper(ch)) {
            case 'U': f = U; break;
            case 'D': f = D; break;
            case 'F': f = F; break;
            case 'B': f = B; break;
            case 'L': f = L; break;
            case 'R': f = R; break;
            default:
                if (std::isspace(ch)) {
                    mode = normal;
                    continue;
                } else {
                    std::cout << "parse error\n";
                    return;
                }
                break;
            }
        } else {
            mode = normal;
        }
    }
    handle_modifier_state(' ');
    c = c2;
}

std::string generate_scramble()
{
    const char *op_names[18] = {"U", "U'", "U2", "D", "D'", "D2",
                                "F", "F'", "F2", "B", "B'", "B2",
                                "L", "L'", "L2", "R", "R'", "R2"};

    std::random_device rd;
    std::mt19937       gen(rd());
    std::uniform_int_distribution<> dis(0, 17);
    std::ostringstream oss;
    bool first = true;
    for (int i = 0; i < 30; ++i)
    {
        if (not first)
        {
            oss << " ";
        }
        first = false;
        oss << op_names[dis(gen)];
    }
    return oss.str();
}

int main() {
    cube c;

    int move{};
    std::chrono::system_clock::time_point start{}, now{};

    auto reset = [&] {
        move = 1;
        c = cube{};
        auto scramble = generate_scramble();
        std::cout << scramble << "\n\n";
        apply_moves(c, scramble);
        draw(c);
        start = std::chrono::system_clock::now();
        now = start;
    };
    auto fmt_time = [&](std::ostream &o) ->std::ostream&{
        auto c(std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count());
        return o << "T+" << std::setfill('0') << std::setw(2) << (c / 3600000)
                 << ":" << std::setw(2) << ((c % 3600000) / 60000) << ":"
                 << std::setw(2) << ((c % 600000) / 1000) << "." << std::setw(3)
                 << (c % 1000);
    };
    auto prompt = [&] {
        std::ostringstream p;
        fmt_time(p)  << ", move " << move << "> ";
        return p.str();
    };

    reset();
    while (char *cline = readline(prompt().c_str())) {
        std::string line = cline;

        auto endpos = line.find_last_not_of(" \t");
        auto startpos = line.find_first_not_of(" \t");
        now = std::chrono::system_clock::now();
        if (endpos != std::string::npos) {
            line = line.substr(0, endpos + 1);
            line = line.substr(startpos);
            add_history(line.c_str());
            apply_moves(c, line);
            draw(c);
            if (c == cube{}) {
                fmt_time(std::cout << "\n") << u8"    (☞°◡°)☞\n" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                reset();
            } else {
                ++move;
            }
        }

        ::free(cline);
    }

}
