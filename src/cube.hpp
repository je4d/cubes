#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <cstdint>
#include <bitset>
#include <sstream>

/*
auto pc_hdr = [] { std::cout << "Empty   DFR     DBR     DBL     DFL     UFR     UBR     UBL     UFL\n"; };
auto pc = [](auto corners) {
    std::ostringstream oss;
    oss << std::bitset<9 * 5>(corners);
    auto bitstr = oss.str();
    auto bsp    = bitstr.begin();
    for (int i = 0; i < 9 * 5; ++i) {
        if (i and not(i % 5))
            std::cout << "  ";
        if (not((i + 2) % 5))
            std::cout << ",";
        std::cout << *bsp++;
    }
    std::cout << std::endl;
};
*/

enum face : uint8_t
{
    U,
    D,
    F,
    B,
    L,
    R,
};

std::ostream &operator<<(std::ostream &o, face f)
{
    static const char *names[] = {"U", "D", "F", "B", "L", "R"};
    return o << names[static_cast<std::uint8_t>(f)];
}

enum class edge_piece
{
    UF, UL, UB, UR,
    FL, BL, BR, FR,
    DF, DL, DB, DR,
};

std::ostream &operator<<(std::ostream &o, edge_piece piece)
{
    static const char *names[] = {"UF", "UL", "UB", "UR", "FL", "BL",
                                  "BR", "FR", "DF", "DL", "DB", "DR"};
    return o << names[static_cast<std::uint8_t>(piece)];
}

enum class edge_position
{
    UF, UL, UB, UR,
    FL, BL, BR, FR,
    DF, DL, DB, DR,
};

std::ostream &operator<<(std::ostream &o, edge_position pos)
{
    static const char *names[] = {"UF", "UL", "UB", "UR", "FL", "BL",
                                  "BR", "FR", "DF", "DL", "DB", "DR"};
    return o << names[static_cast<std::uint8_t>(pos)];
}

enum class corner_piece
{
    UFL, UBL, UBR, UFR,
    DFL, DBL, DBR, DFR,
};

std::ostream &operator<<(std::ostream &o, corner_piece cp)
{
    static const char * names[] = {"UFL", "UBL", "UBR", "UFR",
                                   "DFL", "DBL", "DBR", "DFR"};
    return o << names[static_cast<std::uint8_t>(cp)];
}

enum class corner_position
{
    UFL, UBL, UBR, UFR,
    DFL, DBL, DBR, DFR,
};

std::ostream &operator<<(std::ostream &o, corner_position cp)
{
    static const char * names[] = {"UFL", "UBL", "UBR", "UFR",
                                   "DFL", "DBL", "DBR", "DFR"};
    return o << names[static_cast<std::uint8_t>(cp)];
}

enum edge_orientation
{
    unflipped,
    flipped
};

static constexpr edge_orientation eo_invalid = static_cast<edge_orientation>(-1);

enum corner_orientation : std::uint8_t
{
    upright,
    clockwise,
    anticlockwise
};

static constexpr corner_orientation co_invalid = static_cast<corner_orientation>(-1);

namespace pieces
{
    constexpr corner_piece UFL = corner_piece::UFL;
    constexpr corner_piece UBL = corner_piece::UBL;
    constexpr corner_piece UBR = corner_piece::UBR;
    constexpr corner_piece UFR = corner_piece::UFR;
    constexpr corner_piece DFL = corner_piece::DFL;
    constexpr corner_piece DBL = corner_piece::DBL;
    constexpr corner_piece DBR = corner_piece::DBR;
    constexpr corner_piece DFR = corner_piece::DFR;

    constexpr edge_piece UF = edge_piece::UF;
    constexpr edge_piece UL = edge_piece::UL;
    constexpr edge_piece UB = edge_piece::UB;
    constexpr edge_piece UR = edge_piece::UR;
    constexpr edge_piece FL = edge_piece::FL;
    constexpr edge_piece BL = edge_piece::BL;
    constexpr edge_piece BR = edge_piece::BR;
    constexpr edge_piece FR = edge_piece::FR;
    constexpr edge_piece DF = edge_piece::DF;
    constexpr edge_piece DL = edge_piece::DL;
    constexpr edge_piece DB = edge_piece::DB;
    constexpr edge_piece DR = edge_piece::DR;
}

namespace positions
{
    constexpr corner_position UFL = corner_position::UFL;
    constexpr corner_position UBL = corner_position::UBL;
    constexpr corner_position UBR = corner_position::UBR;
    constexpr corner_position UFR = corner_position::UFR;
    constexpr corner_position DFL = corner_position::DFL;
    constexpr corner_position DBL = corner_position::DBL;
    constexpr corner_position DBR = corner_position::DBR;
    constexpr corner_position DFR = corner_position::DFR;

    constexpr edge_position UF = edge_position::UF;
    constexpr edge_position UL = edge_position::UL;
    constexpr edge_position UB = edge_position::UB;
    constexpr edge_position UR = edge_position::UR;
    constexpr edge_position FL = edge_position::FL;
    constexpr edge_position BL = edge_position::BL;
    constexpr edge_position BR = edge_position::BR;
    constexpr edge_position FR = edge_position::FR;
    constexpr edge_position DF = edge_position::DF;
    constexpr edge_position DL = edge_position::DL;
    constexpr edge_position DB = edge_position::DB;
    constexpr edge_position DR = edge_position::DR;
}

/* Cube state representation */
struct cube
{
    // Cube state representation
    // =========================
    //
    // Orientation
    // -----------
    //
    // In the standard western colouring scheme, the canonical orientation is
    // U=White, F=Blue.
    //
    // Edge orientation
    // ----------------
    //
    // THIS HAS CHANGED FIXME
    //
    // Edge orientation is a boolean. Edges are in their '0' state when they in
    // the same orientation as the they would be if they had arrived in the
    // same position via the F,B,R,L group.
    //
    // Corner Orientation
    // ------------------
    //
    // Corner orientations are an integer in the range [0,3). Corners are in
    // their '0' state when they are in the same orientation as they would be
    // if they had arrived in the same position via the U,D,F2,B2,R2,L2 group.
    // Corners are in their '1' state if they are rotated clockwise from the
    // '0' state
    //
    // Edge Position
    // -------------
    //
    // Edges are numbered from 0-11 as follows:
    // UF UL UB UR
    // FL BL BR FR
    // DF DL DB DR
    //
    // Corner Position
    // ---------------
    //
    // Corners are numbered from 0-7 as follows:
    // UFL UBL UBR UFR
    // DFL DBL DBR DFR
    //
    // State size (b=bits)
    // ----
    //                     Theoretical     | with parity     | Practical
    // Edge orientation:   1 bit * 12      | 1 bit * 11      | 1 bis * 12  = 12
    // Corner Orientation: ln2(3) bits * 8 | ln2(3) bits * 7 | 2 bit * 8   = 16
    // Edge Position:      ln2(12!) bits   | ln2(12!/2) bits | 4 bit * 12  = 48
    // Corner Position:    ln2(8!) bits    | ln2(8!) bits    | 3 bit * 8   = 24
    // Total:              68.8            | 65.2            | 100
    //

    struct edge_state
    {
        constexpr edge_state(std::uint8_t s) : m_state{s} {}
        constexpr edge_state(edge_piece piece, edge_orientation eo)
                : m_state{static_cast<std::uint8_t>(
                      (static_cast<std::uint8_t>(piece) << 1)
                      | static_cast<std::uint8_t>(eo))}
        {}
        constexpr edge_piece piece() const
        { return static_cast<edge_piece>(m_state >> 1); }
        constexpr edge_orientation orientation() const
        { return static_cast<edge_orientation>(m_state & 0b1); }
        std::uint64_t at(edge_position pos)
        { return static_cast<std::uint64_t>(m_state) << edge_shift(pos); }

    private:
        std::uint8_t m_state; // layout: 0bPPPPO
    };

    struct corner_state
    {
        constexpr corner_state(std::uint8_t s) : m_state{s} {}
        constexpr corner_state(corner_piece piece, corner_orientation co)
                : m_state{static_cast<std::uint8_t>(
                      (static_cast<std::uint8_t>(piece) << 2)
                      | static_cast<std::uint8_t>(co))}
        {}
        constexpr corner_piece piece() const
        { return static_cast<corner_piece>(m_state >> 2); }
        constexpr corner_orientation orientation() const
        { return static_cast<corner_orientation>(m_state & 0b11); }
        std::uint64_t at(corner_position pos)
        { return static_cast<std::uint64_t>(m_state) << corner_shift(pos); }

    private:
        std::uint8_t m_state; // layout: 0bPPPOO
    };

    constexpr cube() :
        m_edges(edge_state{pieces::UF, unflipped}.at(positions::UF)
               |edge_state{pieces::UL, unflipped}.at(positions::UL)
               |edge_state{pieces::UB, unflipped}.at(positions::UB)
               |edge_state{pieces::UR, unflipped}.at(positions::UR)
               |edge_state{pieces::FL, unflipped}.at(positions::FL)
               |edge_state{pieces::BL, unflipped}.at(positions::BL)
               |edge_state{pieces::BR, unflipped}.at(positions::BR)
               |edge_state{pieces::FR, unflipped}.at(positions::FR)
               |edge_state{pieces::DF, unflipped}.at(positions::DF)
               |edge_state{pieces::DL, unflipped}.at(positions::DL)
               |edge_state{pieces::DB, unflipped}.at(positions::DB)
               |edge_state{pieces::DR, unflipped}.at(positions::DR)),
        m_corners(corner_state{pieces::UFL, upright}.at(positions::UFL)
                 |corner_state{pieces::UBL, upright}.at(positions::UBL)
                 |corner_state{pieces::UBR, upright}.at(positions::UBR)
                 |corner_state{pieces::UFR, upright}.at(positions::UFR)
                 |corner_state{pieces::DFL, upright}.at(positions::DFL)
                 |corner_state{pieces::DBL, upright}.at(positions::DBL)
                 |corner_state{pieces::DBR, upright}.at(positions::DBR)
                 |corner_state{pieces::DFR, upright}.at(positions::DFR))
    {
    }

    static constexpr face edge_sticker_colours[12][2] = {
        {U, F}, {L, U}, {U, B}, {R, U},
        {L, F}, {L, B}, {R, B}, {R, F},
        {D, F}, {L, D}, {D, B}, {R, D}};

    static constexpr std::array<std::array<edge_orientation, 6>, 12>
        edge_faces = [] () constexpr {
            std::array<std::array<edge_orientation, 6>, 12> ret{};
            for (int e = 0; e < 12; ++e) {
                for (int f = 0; f < 6; ++f) {
                    ret[e][f] = (edge_sticker_colours[e][unflipped] == f) ?
                                    unflipped :
                                    (edge_sticker_colours[e][flipped] == f) ?
                                    flipped :
                                    eo_invalid;
                }
            }
            return ret;
        }();

    static constexpr face corner_sticker_colours[8][3] = {{ U, F, L },
                                                          { U, L, B },
                                                          { U, B, R },
                                                          { U, R, F },
                                                          { D, L, F },
                                                          { D, B, L },
                                                          { D, R, B },
                                                          { D, F, R }};

    static constexpr std::array<std::array<corner_orientation, 6>, 8>
        corner_faces = [] () constexpr {
            std::array<std::array<corner_orientation, 6>, 8> ret{};
            for (int c = 0; c < 8; ++c) {
                for (int f = 0; f < 6; ++f) {
                    ret[c][f] =
                        (corner_sticker_colours[c][upright] == f) ?
                            upright :
                            (corner_sticker_colours[c][clockwise] == f) ?
                            clockwise :
                            (corner_sticker_colours[c][anticlockwise] == f) ?
                            anticlockwise :
                            co_invalid;
                }
            }
            return ret;
        }();

    static constexpr std::uint64_t u64_1 = 1;

    constexpr static std::uint8_t edge_shift(edge_position pos)
    {
        return 5 * static_cast<std::uint8_t>(pos);
    }

    constexpr static std::uint64_t edge_mask(edge_position pos)
    {
        return static_cast<std::uint64_t>(0b11111) << edge_shift(pos);
    }

    template <edge_position... Edges>
    constexpr static std::uint64_t mask()
    {
        return (edge_mask(Edges) | ...);
    }

    constexpr static edge_state edge_at(std::uint64_t edges, edge_position ep)
    {
        return edge_state{static_cast<std::uint8_t>((edges & edge_mask(ep)) >> edge_shift(ep))};
    }

    constexpr static std::uint8_t corner_shift(corner_position pos)
    {
        return 5 * static_cast<std::uint8_t>(pos);
    }

    constexpr static std::uint64_t corner_mask()
    {
        return corner_mask(static_cast<corner_position>(0));
    }

    constexpr static std::uint64_t corner_mask(corner_position c)
    {
        return static_cast<std::uint64_t>(0b11111) << corner_shift(c);
    }

    template <corner_position Corner>
    constexpr static std::uint64_t corner_mask()
    {
        return static_cast<std::uint64_t>(0b11111) << corner_shift(Corner);
    }

    template <corner_position... Corners>
    constexpr static std::uint64_t mask()
    {
        return (corner_mask<Corners>() | ...);
    }

    constexpr static corner_state corner_at(std::uint64_t   corners,
                                            corner_position cp)
    {
        return corner_state{static_cast<std::uint8_t>((corners & corner_mask(cp)) >> corner_shift(cp))};
    }

    /*
     * Queries
     */

    /*
    corners = 988530610188, pos = DFR, face = F
      piece: DFR
      orientation: 0
      sticker: 1
      */


    face sticker_colour(std::uint64_t edges, edge_position pos, face f) const
    {
        // if the edge was upright, we'd be looking at 
        auto es = edge_at(edges, pos);
        auto pos_no = static_cast<std::uint8_t>(pos);
        auto piece_no = static_cast<std::uint8_t>(es.piece());
        auto sticker_pos = (edge_faces[pos_no][f] + 2 - es.orientation()) % 2;
        /*
        std::cout << "edges = " << edges << ", pos = " << pos << ", face = " << f << "\n";
        std::cout << "  piece: " << es.piece() << "\n";
        std::cout << "  orientation: " << es.orientation() << "\n";
        std::cout << "  sticker: " << sticker_pos << "\n";
        std::cout << "  edge_sticker_colours[" << (int)piece_no << "="
                  << edge_piece{piece_no} << "][" << (int)sticker_pos
                  << "] = " << edge_sticker_colours[piece_no][sticker_pos]
                  << "\n";
        // */
        return edge_sticker_colours[piece_no][sticker_pos];
    }

    constexpr face sticker_colour(edge_position ep, face f) const
    {
        return sticker_colour(m_edges, ep, f);
    }

    face sticker_colour(std::uint64_t corners, corner_position pos, face f) const
    {
        auto cs = corner_at(corners, pos);
        auto pos_no = static_cast<std::uint8_t>(pos);
        auto piece_no = static_cast<std::uint8_t>(cs.piece());
        auto sticker_pos = (corner_faces[pos_no][f] + 3 - cs.orientation()) % 3;
        /*
        std::cout << "corners = " << corners << ", pos = " << pos << ", face = " << f << "\n";
        std::cout << "  piece: " << cs.piece() << "\n";
        std::cout << "  orientation: " << cs.orientation() << "\n";
        std::cout << "  sticker: " << sticker_pos << "\n";
        std::cout << "  corner_sticker_colours[" << (int)piece_no << "="
                  << corner_piece{piece_no} << "][" << (int)sticker_pos
                  << "] = " << corner_sticker_colours[piece_no][sticker_pos]
                  << "\n";
        // */
        return corner_sticker_colours[piece_no][sticker_pos];
    }

    constexpr face sticker_colour(corner_position cp, face f) const
    {
        return sticker_colour(m_corners, cp, f);
    }

    /*
    face sticker_colour(edge e, face f) {}
    */


    /*
     * Moves
     */

    constexpr static std::uint64_t move(std::uint64_t edges, edge_position from, edge_position to)
    {
        return ((edges >> edge_shift(from))&0b11111) << edge_shift(to);
    }

    template <edge_position ...Edges>
    constexpr static std::uint64_t flip_edges(std::uint64_t edges)
    {
        return edges
               ^ ((static_cast<std::uint64_t>(0b1) << edge_shift(Edges)) | ...);
    }

    constexpr static std::uint64_t move(std::uint64_t corners, corner_position from, corner_position to)
    {
        return ((corners >> corner_shift(from))&0b11111) << corner_shift(to);
    }

    constexpr static std::uint64_t
        fix_corner_orientation(std::uint64_t corner_orientations)
    {
        return corner_orientations
               - 3 * (((corner_orientations >> 1) & corner_orientations)
                      & 0b00001'00001'00001'00001'00001'00001'00001'00001);
    }

    template <corner_position... Corners>
    constexpr static std::uint64_t prepare_corner_orientations_for_acw(
        std::uint64_t corner_orientations)
    {
        constexpr std::uint64_t mask =
            ((static_cast<std::uint64_t>(0b1) << corner_shift(Corners)) | ...);
        return corner_orientations
               + 3 * (~((corner_orientations >> 1) | corner_orientations)
                      & mask);
    }

    template <corner_position ...Corners>
    constexpr static std::uint64_t turn_corners_cw(std::uint64_t corners)
    {
        return fix_corner_orientation(
            corners + ((u64_1 << corner_shift(Corners)) | ...));
    }

    template <corner_position ...Corners>
    constexpr static std::uint64_t turn_corners_acw(std::uint64_t corners)
    {
        return prepare_corner_orientations_for_acw<Corners...>(corners)
               - ((u64_1 << corner_shift(Corners)) | ...);
    }


    template <auto P1, auto P2, auto P3, auto P4>
    constexpr static std::uint64_t rot_90(std::uint64_t pieces)
    {
        return (pieces & ~mask<P1, P2, P3, P4>())
               | move(pieces, P1, P2)
               | move(pieces, P2, P3)
               | move(pieces, P3, P4)
               | move(pieces, P4, P1);
    }

    template <edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4>
    cube &ud_90()
    {
        m_edges = flip_edges<E1, E2, E3, E4>(rot_90<E1, E2, E3, E4>(m_edges));
        m_corners = rot_90<C1, C2, C3, C4>(m_corners);
        return *this;
    }

    cube& u()
    {
        using namespace positions;
        return ud_90<UF, UL, UB, UR, UFL, UBL, UBR, UFR>();
    }
    cube& up()
    {
        using namespace positions;
        return ud_90<UF, UR, UB, UL, UFL, UFR, UBR, UBL>();
    }
    cube& d()
    {
        using namespace positions;
        return ud_90<DF, DR, DB, DL, DFL, DFR, DBR, DBL>();
    }
    cube& dp()
    {
        using namespace positions;
        return ud_90<DF, DL, DB, DR, DFL, DBL, DBR, DFR>();
    }

    template <edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4,
              bool            C1Cw>
    cube &fblr_90()
    {
        constexpr auto CwC1 = C1Cw ? C1 : C2;
        constexpr auto CwC2 = C1Cw ? C3 : C4;
        constexpr auto AcwC1 = C1Cw ? C2 : C1;
        constexpr auto AcwC2 = C1Cw ? C4 : C3;
        m_corners = turn_corners_cw<CwC1, CwC2>(
            turn_corners_acw<AcwC1, AcwC2>(rot_90<C1, C2, C3, C4>(m_corners)));
        m_edges = rot_90<E1, E2, E3, E4>(m_edges);
        return *this;
    }

    cube &f()
    {
        using namespace positions;
        return fblr_90<UF, FR, DF, FL, UFL, UFR, DFR, DFL, false>();
    }
    cube &fp()
    {
        using namespace positions;
        return fblr_90<UF, FL, DF, FR, UFL, DFL, DFR, UFR, false>();
    }
    cube &b()
    {
        using namespace positions;
        return fblr_90<UB, BL, DB, BR, UBL, DBL, DBR, UBR, true>();
    }
    cube &bp()
    {
        using namespace positions;
        return fblr_90<UB, BR, DB, BL, UBL, UBR, DBR, DBL, true>();
    }
    cube &l()
    {
        using namespace positions;
        return fblr_90<UL, FL, DL, BL, UFL, DFL, DBL, UBL, true>();
    }
    cube &lp()
    {
        using namespace positions;
        return fblr_90<UL, BL, DL, FL, UFL, UBL, DBL, DFL, true>();
    }
    cube &r() {
        using namespace positions;
        return fblr_90<UR, BR, DR, FR, UFR, UBR, DBR, DFR, false>();
    }
    cube &rp()
    {
        using namespace positions;
        return fblr_90<UR, FR, DR, BR, UFR, DFR, DBR, UBR, false>();
    }

    template <auto P1, auto P2, auto P3, auto P4>
    static std::uint64_t rot_180(std::uint64_t pieces)
    {
        return (pieces & ~mask<P1, P2, P3, P4>())
               | move(pieces, P1, P3)
               | move(pieces, P2, P4)
               | move(pieces, P3, P1)
               | move(pieces, P4, P2);
    }

    template <edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4>
    cube &udfblr_180()
    {
        m_edges = rot_180<E1, E2, E3, E4>(m_edges);
        m_corners = rot_180<C1, C2, C3, C4>(m_corners);
        return *this;
    }

    cube& u2()
    {
        using namespace positions;
        return udfblr_180<UF, UL, UB, UR, UFL, UBL, UBR, UFR>();
    }
    cube& d2()
    {
        using namespace positions;
        return udfblr_180<DF, DL, DB, DR, DFL, DBL, DBR, DFR>();
    }
    cube &r2() {
        using namespace positions;
        return udfblr_180<UR, BR, DR, FR, UFR, UBR, DBR, DFR>();
    }
    cube &l2()
    {
        using namespace positions;
        return udfblr_180<UL, FL, DL, BL, UFL, DFL, DBL, UBL>();
    }
    cube &f2()
    {
        using namespace positions;
        return udfblr_180<UF, FR, DF, FL, UFL, UFR, DFR, DFL>();
    }
    cube &b2()
    {
        using namespace positions;
        return udfblr_180<UB, BL, DB, BR, UBL, DBL, DBR, UBR>();
    }

    friend bool operator == (const cube& a, const cube& b)
    {
        return a.m_edges == b.m_edges && a.m_corners == b.m_corners;
    }

    // layouts: P = position, O = orientation
    std::uint64_t m_edges   = 0; // layout: 0bPPPPO, mask: 0b11111<<(5*edge_num)
    std::uint64_t m_corners = 0; // layout: 0bPPPOO, mask: 0b11111<<(5*corner_num)
};

static_assert(sizeof(cube) == 16, "");

#endif // CUBE_HPP
