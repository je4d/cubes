#include "cube.hpp"
#include "ascii_cube.hpp"

int main() {


    cube c;
    const char *op_names[6][3] = {
        {"U", "U'", "U2"}, {"D", "D'", "D2"},
        {"F", "F'", "F2"}, {"B", "B'", "B2"},
        {"L", "L'", "L2"}, {"R", "R'", "R2"}};
    cube &(cube::*ops[6][3])() = {
        {&cube::u, &cube::up, &cube::u2}, {&cube::d, &cube::dp, &cube::d2},
        {&cube::f, &cube::fp, &cube::f2}, {&cube::b, &cube::bp, &cube::b2},
        {&cube::l, &cube::lp, &cube::l2}, {&cube::r, &cube::rp, &cube::r2}};
    //std::string scramble = "D2 B2 D U' R' U' R2 B2 L2 R U' B D2 R D2 B F U L' R2 B2 D' B' D' L F' D2 R2 B U";
    std::string scramble = "F2 L2 F D B D2 L' U2 L2 F' L F' L2 U2 B2 R B2 R' F' R2 U R D2 L' B' L R' D B F2";
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
            std::cout << ' ' << op_names[f][move_index];
            (c.*(ops[f][move_index]))();
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
                    return 1;
                }
                break;
            }
        } else {
            mode = normal;
        }
    }
    handle_modifier_state(' ');
    std::cout << "\n";
    draw(c);

    /*
    for (auto op :
         {&cube::u, &cube::up, &cube::u2, &cube::d, &cube::dp, &cube::d2,
          &cube::f, &cube::fp, &cube::f2, &cube::b, &cube::bp, &cube::b2,
          &cube::l, &cube::lp, &cube::l2, &cube::r, &cube::rp, &cube::r2}) {
        cube c;
        draw((c.*op)());
    }
    */
//    cube c;
//    draw(c.u2().d2().f2().b2().l2().r2());


    /*
    for (unsigned char i = 0; i < 6; ++i)
    {
        std::cout << "\t" << face{i};
    }
        std::cout << "\n";
    int i = 0;
    for (auto piece : cube::corner_faces)
    {
        std::cout << corner_piece{i++};
        for (auto o : piece)
        {
            std::cout << "\t" << o;
        }
        std::cout << "\n";
    }
    */

    // char grid[23][36];
}
