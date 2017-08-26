#include "cube.hpp"
#include "ascii_cube.hpp"

int main() {
    /*
    for (auto op :
         {&cube::u, &cube::up, &cube::u2, &cube::d, &cube::dp, &cube::d2,
          &cube::f, &cube::fp, &cube::f2, &cube::b, &cube::bp, &cube::b2,
          &cube::l, &cube::lp, &cube::l2, &cube::r, &cube::rp, &cube::r2}) {
        cube c;
        draw((c.*op)());
    }
    */
    cube c;
    draw(c.u2().d2().f2().b2().l2().r2());


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
