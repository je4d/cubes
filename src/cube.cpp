#include <random>
#include <iomanip>
#include <iostream>
#include <thread>

#include <readline/readline.h>
#include <readline/history.h>

#include "cube_view.hpp"
#include "ascii_cube.hpp"


void apply_moves(cube_view& c, std::string moves)
{
    cube_view c2 = c;
    const char *op_names[18][3] = {
        {"U",  "U'",  "U2" }, {"D",  "D'",  "D2" },
        {"F",  "F'",  "F2" }, {"B",  "B'",  "B2" },
        {"L",  "L'",  "L2" }, {"R",  "R'",  "R2" },
        {"UW", "UW'", "UW2"}, {"DW", "DW'", "DW2"},
        {"FW", "FW'", "FW2"}, {"BW", "BW'", "BW2"},
        {"LW", "LW'", "LW2"}, {"RW", "RW'", "RW2"},
        {"M",  "M'",  "M2" }, {"E",  "E'",  "E2" },
        {"S",  "S'",  "S2" }, {"X",  "X'",  "X2" },
        {"Y",  "Y'",  "Y2" }, {"Z",  "Z'",  "Z2" }};
    cube_view &(cube_view::*ops[18][3])() = {
        {&cube_view::u,  &cube_view::up,  &cube_view::u2},
        {&cube_view::d,  &cube_view::dp,  &cube_view::d2},
        {&cube_view::f,  &cube_view::fp,  &cube_view::f2},
        {&cube_view::b,  &cube_view::bp,  &cube_view::b2},
        {&cube_view::l,  &cube_view::lp,  &cube_view::l2},
        {&cube_view::r,  &cube_view::rp,  &cube_view::r2},
        {&cube_view::uw, &cube_view::uwp, &cube_view::uw2},
        {&cube_view::dw, &cube_view::dwp, &cube_view::dw2},
        {&cube_view::fw, &cube_view::fwp, &cube_view::fw2},
        {&cube_view::bw, &cube_view::bwp, &cube_view::bw2},
        {&cube_view::lw, &cube_view::lwp, &cube_view::lw2},
        {&cube_view::rw, &cube_view::rwp, &cube_view::rw2},
        {&cube_view::m,  &cube_view::mp,  &cube_view::m2},
        {&cube_view::e,  &cube_view::ep,  &cube_view::e2},
        {&cube_view::s,  &cube_view::sp,  &cube_view::s2},
        {&cube_view::x,  &cube_view::xp,  &cube_view::x2},
        {&cube_view::y,  &cube_view::yp,  &cube_view::y2},
        {&cube_view::z,  &cube_view::zp,  &cube_view::z2}};
    enum
    {
        normal,
        modifier,
        modifier_p_only
    } state;
    int8_t move_base;
    int move_index;
    auto reset = [&] {
        state      = normal;
        move_index = 0;
    };
    reset();
    auto handle_modifier_state = [&](auto ch) {
        if (state == normal)
            return false;
        bool ret = true;
        switch (std::toupper(ch)) {
        case 'W':
            if (state == modifier and not(move_base < 6))
                return false;
            move_base += 6;
            return true;
        case '\'':
            if (not move_index)
                move_index = 1;
            break;
        case '2':
            state      = modifier_p_only;
            move_index = 2;
            return true;
        default: ret = false; break;
        }
        (c2.*(ops[move_base][move_index]))();
        reset();
        return ret;
    };
    for (auto ch : moves)
    {
        if (not handle_modifier_state(ch))
        {
            state = modifier;
            switch (std::toupper(ch)) {
                using namespace positions;
            case 'U': move_base =  0; break;
            case 'D': move_base =  1; break;
            case 'F': move_base =  2; break;
            case 'B': move_base =  3; break;
            case 'L': move_base =  4; break;
            case 'R': move_base =  5; break;
            case 'M': move_base = 12; break;
            case 'E': move_base = 13; break;
            case 'S': move_base = 14; break;
            case 'X': move_base = 15; break;
            case 'Y': move_base = 16; break;
            case 'Z': move_base = 17; break;
            default:
                if (std::isspace(ch)) {
                    state = normal;
                    continue;
                } else {
                    std::cout << "parse error\n";
                    return;
                }
                break;
            }
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
    cube_view cv;

    int move{};
    std::chrono::system_clock::time_point start{}, now{};
    bool playing = true;

    auto reset = [&] {
        move = 1;
        cv = cube_view{};
        auto scramble = generate_scramble();
        std::cout << scramble << "\n\n";
        apply_moves(cv, scramble);
        draw(cv);
        start = std::chrono::system_clock::now();
        now = start;
    };
    auto fmt_time = [&](std::ostream &o) -> std::ostream & {
        auto cv(
            std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
                .count());
        return o << "T+" << std::setfill('0') << std::setw(2) << (cv / 3600000)
                 << ":" << std::setw(2) << ((cv % 3600000) / 60000) << ":"
                 << std::setw(2) << ((cv % 600000) / 1000) << "."
                 << std::setw(3) << (cv % 1000);
    };
    auto prompt = [&] {
        std::ostringstream p;
        if (playing) {
            fmt_time(p) << ", move " << move << "> ";
        } else {
            p << "sandbox> ";
        }
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

            if (line == "solve")
            {
                playing = false;
                cv = decltype(cv){};
                std::cout << "\n";
                draw(cv);
            }
            else if (not playing && line == "play")
            {
                playing = true;
                reset();
            }
            else
            {
                apply_moves(cv, line);
                std::cout << "\n";
                draw(cv);
                if (playing && cv.cube() == cube{}) {
                    fmt_time(std::cout << "\n") << u8"    (☞°◡°)☞\n"
                                                << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    reset();
                } else {
                    ++move;
                }
            }
        }

        ::free(cline);
    }
    std::cout << "\n";
}
