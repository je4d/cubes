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

enum class face_colour : uint8_t
{
    U,
    D,
    F,
    B,
    L,
    R,
    none,
};

std::ostream &operator<<(std::ostream &o, face_colour f)
{
    static const char *names[] = {"U", "D", "F", "B", "L", "R", "-"};
    return o << names[static_cast<std::uint8_t>(f)];
}

enum class face_position : uint8_t
{
    U,
    D,
    F,
    B,
    L,
    R,
};

std::ostream &operator<<(std::ostream &o, face_position f)
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

namespace face_colours
{
    constexpr face_colour U = face_colour::U;
    constexpr face_colour D = face_colour::D;
    constexpr face_colour F = face_colour::F;
    constexpr face_colour B = face_colour::B;
    constexpr face_colour L = face_colour::L;
    constexpr face_colour R = face_colour::R;
}

namespace pieces
{
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

    constexpr corner_piece UFL = corner_piece::UFL;
    constexpr corner_piece UBL = corner_piece::UBL;
    constexpr corner_piece UBR = corner_piece::UBR;
    constexpr corner_piece UFR = corner_piece::UFR;
    constexpr corner_piece DFL = corner_piece::DFL;
    constexpr corner_piece DBL = corner_piece::DBL;
    constexpr corner_piece DBR = corner_piece::DBR;
    constexpr corner_piece DFR = corner_piece::DFR;
}

namespace positions
{
    constexpr face_position U = face_position::U;
    constexpr face_position D = face_position::D;
    constexpr face_position F = face_position::F;
    constexpr face_position B = face_position::B;
    constexpr face_position L = face_position::L;
    constexpr face_position R = face_position::R;

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

    constexpr corner_position UFL = corner_position::UFL;
    constexpr corner_position UBL = corner_position::UBL;
    constexpr corner_position UBR = corner_position::UBR;
    constexpr corner_position UFR = corner_position::UFR;
    constexpr corner_position DFL = corner_position::DFL;
    constexpr corner_position DBL = corner_position::DBL;
    constexpr corner_position DBR = corner_position::DBR;
    constexpr corner_position DFR = corner_position::DFR;
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

    template <typename S,
              typename Piece,
              typename Pos,
              typename Orientation,
              std::uint8_t PosBits,
              std::uint8_t OrBits>
    struct state_base
    {
        using rep_t       = std::uint64_t;
        using idx_t       = std::uint8_t;
        using states      = S;
        using piece       = Piece;
        using position    = Pos;
        using orientation = Orientation;

        static constexpr idx_t stride = PosBits + OrBits;

        // edge   layout: 0bPPPPO, mask: 0b11111<<(5*edge_num)
        // corner layout: 0bPPPPO, mask: 0b11111<<(5*corner_num)
        struct position_state
        {
            using posrep_t = std::uint8_t;
            using piece_t = state_base::piece;
            using orientation_t = state_base::orientation;

            constexpr position_state(posrep_t r) : m_rep{r} {}
            constexpr position_state(piece_t p, orientation_t o)
                    : m_rep{static_cast<posrep_t>(
                          (static_cast<posrep_t>(p) << OrBits)
                          | static_cast<posrep_t>(o))}
            {}
            constexpr piece piece() const
            {
                return static_cast<piece_t>(m_rep >> OrBits);
            }
            constexpr orientation orientation() const
            {
                return static_cast<orientation_t>(m_rep & ((1 << OrBits) - 1));
            }
            states at(position pos)
            {
                return {static_cast<rep_t>(m_rep) << state_base::shift(pos)};
            }

        private:
            posrep_t m_rep;
        };

        struct mask
        {
            constexpr mask(position pos) noexcept
                    : rep{static_cast<rep_t>((1 << stride) - 1) << state_base::shift(pos)}
            {}
            constexpr mask operator~() const noexcept { return mask{~rep}; }
            friend constexpr mask operator|(mask a, mask b) noexcept
            { return mask{a.rep | b.rep}; }
            friend constexpr mask operator&(mask a, mask b) noexcept
            { return mask{a.rep & b.rep}; }
            friend constexpr states operator&(mask a, state_base b) noexcept
            { return states{a.rep & b.rep}; }
            friend constexpr states operator&(state_base a, mask b) noexcept
            { return states{a.rep & b.rep}; }

        private:
            constexpr mask(rep_t rep) noexcept : rep{rep} {}

            rep_t rep;
        };

        constexpr static idx_t shift(position pos) noexcept
        {
            return stride * static_cast<idx_t>(pos);
        }

        constexpr position_state operator[](position p) const
        {
            return position_state(((*this) & mask(p)).rep >> shift(p));
        }

        constexpr states move(position from, position to) const noexcept
        {
            return (*this)[from].at(to);
            //return {(((*this) & mask(from)).rep >> shift(from)) << shift(to)};
        }

        template <position... Positions>
        constexpr static mask make_mask()
        {
            return (mask(Positions) | ...);
        }

        template <position P1, position P2, position P3, position P4>
        constexpr states rot_90() const noexcept
        {
            return (*this & ~make_mask<P1, P2, P3, P4>())
                   | move(P1, P2)
                   | move(P2, P3)
                   | move(P3, P4)
                   | move(P4, P1);
        }

        template <position P1, position P2, position P3, position P4>
        constexpr states rot_180() const noexcept
        {
            return (*this & ~make_mask<P1, P2, P3, P4>())
                   | move(P1, P3)
                   | move(P2, P4)
                   | move(P3, P1)
                   | move(P4, P2);
        }

        friend constexpr bool operator==(const states &a, const states &b)
        { return a.rep == b.rep; }
        friend constexpr states operator|(states a, states b) noexcept
        { return states{a.rep | b.rep}; }

        rep_t rep = 0;
    };

    struct edges_state : state_base<edges_state,
                                    edge_piece,
                                    edge_position,
                                    edge_orientation,
                                    4, 1>
    {
        using edge_stickers_t = std::array<std::array<face_colour,2>,12>;
        static constexpr edge_stickers_t edge_stickers = []() {
            using namespace face_colours;
            return edge_stickers_t{{{U, F}, {L, U}, {U, B}, {R, U},
                                    {L, F}, {L, B}, {R, B}, {R, F},
                                    {D, F}, {L, D}, {D, B}, {R, D}}};
        }();

        static constexpr std::array<std::array<edge_orientation, 6>, 12>
            edge_faces = [] () constexpr {
                std::array<std::array<edge_orientation, 6>, 12> ret{};
                for (int e = 0; e < 12; ++e) {
                    for (int f = 0; f < 6; ++f) {
                        auto fc = static_cast<face_colour>(f);
                        ret[e][f] =
                            (edge_stickers[e][unflipped] == fc) ?
                                unflipped :
                                (edge_stickers[e][flipped] == fc) ?
                                flipped :
                                eo_invalid;
                    }
                }
                return ret;
            }();

        template <edge_position ...Edges>
        constexpr edges_state flip() const
        {
            return {rep ^ ((rep_t{0b1} << shift(Edges)) | ...)};
        }

        face_colour sticker_colour(edge_position pos, face_position f) const
        {
            auto es = (*this)[pos];
            auto pos_no   = static_cast<idx_t>(pos);
            auto face_no  = static_cast<idx_t>(f);
            auto piece_no = static_cast<idx_t>(es.piece());
            auto sticker_pos =
                (edge_faces[pos_no][face_no] + 2 - es.orientation()) % 2;
            return edge_stickers[piece_no][sticker_pos];
        }
    };

    struct corners_state : state_base<corners_state,
                                      corner_piece,
                                      corner_position,
                                      corner_orientation,
                                      3, 2>
    {
        using corner_stickers_t = std::array<std::array<face_colour, 3>, 8>;
        static constexpr corner_stickers_t corner_stickers = []() {
            using namespace face_colours;
            return corner_stickers_t{{{ U, F, L },
                                      { U, L, B },
                                      { U, B, R },
                                      { U, R, F },
                                      { D, L, F },
                                      { D, B, L },
                                      { D, R, B },
                                      { D, F, R }}};
        }();

        static constexpr std::array<std::array<corner_orientation, 6>, 8>
            corner_faces = [] () constexpr {
                std::array<std::array<corner_orientation, 6>, 8> ret{};
                for (int c = 0; c < 8; ++c) {
                    for (int f = 0; f < 6; ++f) {
                        auto fc = static_cast<face_colour>(f);
                        ret[c][f] =
                            (corner_stickers[c][upright] == fc) ?
                                upright :
                                (corner_stickers[c][clockwise] == fc) ?
                                clockwise :
                                (corner_stickers[c][anticlockwise] == fc) ?
                                anticlockwise :
                                co_invalid;
                    }
                }
                return ret;
            }();

        template <corner_position ...Corners>
        constexpr corners_state turn_cw() const noexcept
        {
            auto pre_mod = rep + ((rep_t{1} << shift(Corners)) | ...);
            auto low_bits = 0b00001'00001'00001'00001'00001'00001'00001'00001;
            return {pre_mod - 3 * ((pre_mod >> 1) & pre_mod & low_bits)};
        }

        template <corner_position ...Corners>
        constexpr corners_state turn_acw() const noexcept
        {
            auto low_bits = ((rep_t{0b1} << shift(Corners)) | ...);
            auto prepared = rep + 3 * (~((rep >> 1) | rep) & low_bits);
            return {prepared - ((rep_t{1} << shift(Corners)) | ...)};
        }

        face_colour sticker_colour(corner_position pos, face_position f) const
        {
            auto cs       = (*this)[pos];
            auto pos_no   = static_cast<idx_t>(pos);
            auto face_no  = static_cast<idx_t>(f);
            auto piece_no = static_cast<idx_t>(cs.piece());
            auto sticker_pos =
                (corner_faces[pos_no][face_no] + 3 - cs.orientation()) % 3;
            return corner_stickers[piece_no][sticker_pos];
        }
    };

    using edge_state   = edges_state::position_state;
    using corner_state = corners_state::position_state;

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

    template <edge_position... Edges>
    constexpr static auto mask()
    {
        return (edges_state::mask(Edges) | ...);
    }

    template <corner_position... Corners>
    constexpr static auto mask()
    {
        return (corners_state::mask(Corners) | ...);
    }

    /*
     * Queries
     */

    constexpr face_colour sticker_colour(edge_position ep, face_position f) const
    {
        return m_edges.sticker_colour(ep, f);
    }

    constexpr face_colour sticker_colour(corner_position cp, face_position f) const
    {
        return m_corners.sticker_colour(cp, f);
    }

    /*
     * Moves
     */

    template <edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4>
    cube &ud_90()
    {
        m_edges =
            m_edges.rot_90<E1, E2, E3, E4>().template flip<E1, E2, E3, E4>();
        m_corners = m_corners.rot_90<C1, C2, C3, C4>();
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
        m_corners = m_corners.rot_90<C1, C2, C3, C4>()
                             .template turn_acw<AcwC1, AcwC2>()
                             .template turn_cw<CwC1, CwC2>();
        m_edges = m_edges.rot_90<E1, E2, E3, E4>();
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

    template <edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4>
    cube &udfblr_180()
    {
        m_edges = m_edges.rot_180<E1, E2, E3, E4>();
        m_corners = m_corners.rot_180<C1, C2, C3, C4>();
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

    friend constexpr bool operator==(const cube &a, const cube &b) noexcept
    {
        return a.m_edges == b.m_edges && a.m_corners == b.m_corners;
    }

    //                            layouts: P = position, O = orientation
    edges_state   m_edges{};   // layout: 0bPPPPO, mask: 0b11111<<(5*edge_num)
    corners_state m_corners{}; // layout: 0bPPPOO, mask: 0b11111<<(5*corner_num)
};

struct cube_view
{
};

static_assert(sizeof(cube) == 16, "");

#endif // CUBE_HPP
