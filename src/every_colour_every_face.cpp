#include "cube.hpp"
#include "algorithms.hpp"

int main()
{
    cube start{};
    auto every_colour_every_face = [](cube c) {
        constexpr std::uint8_t all_colours = [] {
            std::uint8_t ret{};
            for (auto fc :
                 {face_colours::U, face_colours::D, face_colours::F,
                  face_colours::B, face_colours::L, face_colours::R})
                ret |= 1u << int(fc);
            return ret;
        }();
        std::uint8_t colours{};

        auto set = [=, &colours](face_position fp, auto position) {
            if constexpr (std::is_same_v<decltype(position), face_position>)
                colours |= 1u << int(c.sticker_colour(fp));
            else
                colours |= 1u << int(c.sticker_colour(position, fp));
        };
        {
            colours = {};
            set(face_position::U, face_position::U);
            set(face_position::U, edge_position::UF);
            set(face_position::U, edge_position::UB);
            set(face_position::U, edge_position::UL);
            set(face_position::U, edge_position::UR);
            set(face_position::U, corner_position::UFL);
            set(face_position::U, corner_position::UFR);
            set(face_position::U, corner_position::UBL);
            set(face_position::U, corner_position::UBR);
            if (colours != all_colours)
                return false;
        }
        {
            colours = {};
            set(face_position::D, face_position::D);
            set(face_position::D, edge_position::DF);
            set(face_position::D, edge_position::DB);
            set(face_position::D, edge_position::DL);
            set(face_position::D, edge_position::DR);
            set(face_position::D, corner_position::DFL);
            set(face_position::D, corner_position::DFR);
            set(face_position::D, corner_position::DBL);
            set(face_position::D, corner_position::DBR);
            if (colours != all_colours)
                return false;
        }
        {
            colours = {};
            set(face_position::F, face_position::F);
            set(face_position::F, edge_position::UF);
            set(face_position::F, edge_position::DF);
            set(face_position::F, edge_position::FL);
            set(face_position::F, edge_position::FR);
            set(face_position::F, corner_position::UFL);
            set(face_position::F, corner_position::UFR);
            set(face_position::F, corner_position::DFL);
            set(face_position::F, corner_position::DFR);
            if (colours != all_colours)
                return false;
        }
        {
            colours = {};
            set(face_position::B, face_position::B);
            set(face_position::B, edge_position::UB);
            set(face_position::B, edge_position::DB);
            set(face_position::B, edge_position::BL);
            set(face_position::B, edge_position::BR);
            set(face_position::B, corner_position::UBL);
            set(face_position::B, corner_position::UBR);
            set(face_position::B, corner_position::DBL);
            set(face_position::B, corner_position::DBR);
            if (colours != all_colours)
                return false;
        }
        {
            colours = {};
            set(face_position::L, face_position::L);
            set(face_position::L, edge_position::UL);
            set(face_position::L, edge_position::DL);
            set(face_position::L, edge_position::FL);
            set(face_position::L, edge_position::BL);
            set(face_position::L, corner_position::UFL);
            set(face_position::L, corner_position::UBL);
            set(face_position::L, corner_position::DFL);
            set(face_position::L, corner_position::DBL);
            if (colours != all_colours)
                return false;
        }
        {
            colours = {};
            set(face_position::R, face_position::R);
            set(face_position::R, edge_position::UR);
            set(face_position::R, edge_position::DR);
            set(face_position::R, edge_position::FR);
            set(face_position::R, edge_position::BR);
            set(face_position::R, corner_position::UFR);
            set(face_position::R, corner_position::UBR);
            set(face_position::R, corner_position::DFR);
            set(face_position::R, corner_position::DBR);
            if (colours != all_colours)
                return false;
        }
        return true;
    };

//    auto algos =
//        find_paths<move::U, move::Up, move::U2, move::D, move::Dp, move::D2,
//                   move::L, move::Lp, move::L2, move::R, move::Rp, move::R2,
//                   move::F, move::Fp, move::F2, move::B, move::Bp,
//                   move::B2>(start, every_colour_every_face, 7);
    auto algos =
        find_paths<move::U, move::D, move::L, move::R, move::F, move::B>(
            start, every_colour_every_face, 7);
    for (auto alg : algos) {
        for (auto move : alg)
        {
            std::cout << ' ' << move;
        }
        std::cout << '\n';
    }
}
