#include <random>
#include <sstream>

#include "ascii_cube.hpp"
#include "cube.hpp"
#include "game.hpp"

int main()
{
    const cube::stickers& cs = cube::standard_stickers; // cube_stickers("....0....111111511.22.22.21.33.33.33...444444.52.55.55");

    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(0, 17);

    auto scrambler = [&] {
        constexpr const char *op_names[18] = {"U", "U'", "U2", "D", "D'", "D2",
                                              "F", "F'", "F2", "B", "B'", "B2",
                                              "L", "L'", "L2", "R", "R'", "R2"};
        std::ostringstream    oss;
        bool                  first = true;
        for (int i = 0; i < 30; ++i) {
            if (not first)
                oss << " ";
            first = false;
            oss << op_names[dis(gen)];
        }
        return oss.str();
    };

    play_game(scrambler, [](cube c) { draw(c, cs); });
}
