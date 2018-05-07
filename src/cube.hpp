#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <cstdint>
#include <bitset>
#include <sstream>
#include <iosfwd>

/*
void pf_hdr() {
    std::cout << "LR  FB  UD   /  R  L  B  F  D  U\n";
};

void pf(std::uint64_t faces) {
    std::ostringstream oss;
    oss << std::bitset<3 * 3 + 6 * 2>(faces >> 40);
    auto bitstr = oss.str();
    auto bsp    = bitstr.begin();
    for (int i = 0; i < 9; ++i) {
        if (i and not(i % 3))
            std::cout << " ";
        std::cout << *bsp++;
    }
    std::cout << "  /  ";
    for (int i = 0; i < 12; ++i) {
        if (i and not(i % 2))
            std::cout << " ";
        std::cout << *bsp++;
    }
    std::cout << std::endl;
};

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
    shadow,
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
    static const char *names[] = {".", "U", "D", "F", "B", "L", "R", ""};
    return o << names[static_cast<std::uint8_t>(f)];
}

enum class face_piece : uint8_t
{
    U,
    D,
    F,
    B,
    L,
    R,
};

std::ostream &operator<<(std::ostream &o, face_piece f)
{
    static const char *names[] = {"U", "D", "F", "B", "L", "R"};
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

enum class face_orientation : uint8_t
{
    U,
    R,
    D,
    L,
};

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
    constexpr face_piece U = face_piece::U;
    constexpr face_piece D = face_piece::D;
    constexpr face_piece F = face_piece::F;
    constexpr face_piece B = face_piece::B;
    constexpr face_piece L = face_piece::L;
    constexpr face_piece R = face_piece::R;

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

enum class move : int8_t
{
    // Face turns
    U, Up, Uʹ = Up, U2,
    D, Dp, Dʹ = Dp, D2,
    F, Fp, Fʹ = Fp, F2,
    B, Bp, Bʹ = Bp, B2,
    L, Lp, Lʹ = Lp, L2,
    R, Rp, Rʹ = Rp, R2,

    // Deep face turns
    Uw, Uwp, Uwʹ = Uwp, Uw2,
    Dw, Dwp, Dwʹ = Dwp, Dw2,
    Fw, Fwp, Fwʹ = Fwp, Fw2,
    Bw, Bwp, Bwʹ = Bwp, Bw2,
    Lw, Lwp, Lwʹ = Lwp, Lw2,
    Rw, Rwp, Rwʹ = Rwp, Rw2,

    // Slices
    M, Mp, Mʹ = Mp, M2,
    E, Ep, Eʹ = Ep, E2,
    S, Sp, Sʹ = Sp, S2,

    // Whole cube rotations
    X, Xp, Xʹ = Xp, X2,
    Y, Yp, Yʹ = Yp, Y2,
    Z, Zp, Zʹ = Zp, Z2
};

std::ostream& operator<<(std::ostream& o, move m)
{
    static constexpr auto move_names = []() constexpr {
        std::array<const char*, 54> ret{};
        ret[static_cast<std::size_t>(move::U)]   = "U";
        ret[static_cast<std::size_t>(move::Up)]  = "Uʹ";
        ret[static_cast<std::size_t>(move::U2)]  = "U2";
        ret[static_cast<std::size_t>(move::D)]   = "D";
        ret[static_cast<std::size_t>(move::Dp)]  = "Dʹ";
        ret[static_cast<std::size_t>(move::D2)]  = "D2";
        ret[static_cast<std::size_t>(move::F)]   = "F";
        ret[static_cast<std::size_t>(move::Fp)]  = "Fʹ";
        ret[static_cast<std::size_t>(move::F2)]  = "F2";
        ret[static_cast<std::size_t>(move::B)]   = "B";
        ret[static_cast<std::size_t>(move::Bp)]  = "Bʹ";
        ret[static_cast<std::size_t>(move::B2)]  = "B2";
        ret[static_cast<std::size_t>(move::L)]   = "L";
        ret[static_cast<std::size_t>(move::Lp)]  = "Lʹ";
        ret[static_cast<std::size_t>(move::L2)]  = "L2";
        ret[static_cast<std::size_t>(move::R)]   = "R";
        ret[static_cast<std::size_t>(move::Rp)]  = "Rʹ";
        ret[static_cast<std::size_t>(move::R2)]  = "R2";
        ret[static_cast<std::size_t>(move::Uw)]  = "Uw";
        ret[static_cast<std::size_t>(move::Uwp)] = "Uwʹ";
        ret[static_cast<std::size_t>(move::Uw2)] = "Uw2";
        ret[static_cast<std::size_t>(move::Dw)]  = "Dw";
        ret[static_cast<std::size_t>(move::Dwp)] = "Dwʹ";
        ret[static_cast<std::size_t>(move::Dw2)] = "Dw2";
        ret[static_cast<std::size_t>(move::Fw)]  = "Fw";
        ret[static_cast<std::size_t>(move::Fwp)] = "Fwʹ";
        ret[static_cast<std::size_t>(move::Fw2)] = "Fw2";
        ret[static_cast<std::size_t>(move::Bw)]  = "Bw";
        ret[static_cast<std::size_t>(move::Bwp)] = "Bwʹ";
        ret[static_cast<std::size_t>(move::Bw2)] = "Bw2";
        ret[static_cast<std::size_t>(move::Lw)]  = "Lw";
        ret[static_cast<std::size_t>(move::Lwp)] = "Lwʹ";
        ret[static_cast<std::size_t>(move::Lw2)] = "Lw2";
        ret[static_cast<std::size_t>(move::Rw)]  = "Rw";
        ret[static_cast<std::size_t>(move::Rwp)] = "Rwʹ";
        ret[static_cast<std::size_t>(move::Rw2)] = "Rw2";
        ret[static_cast<std::size_t>(move::M)]   = "M";
        ret[static_cast<std::size_t>(move::Mp)]  = "Mʹ";
        ret[static_cast<std::size_t>(move::M2)]  = "M2";
        ret[static_cast<std::size_t>(move::E)]   = "E";
        ret[static_cast<std::size_t>(move::Ep)]  = "Eʹ";
        ret[static_cast<std::size_t>(move::E2)]  = "E2";
        ret[static_cast<std::size_t>(move::S)]   = "S";
        ret[static_cast<std::size_t>(move::Sp)]  = "Sʹ";
        ret[static_cast<std::size_t>(move::S2)]  = "S2";
        ret[static_cast<std::size_t>(move::X)]   = "X";
        ret[static_cast<std::size_t>(move::Xp)]  = "Xʹ";
        ret[static_cast<std::size_t>(move::X2)]  = "X2";
        ret[static_cast<std::size_t>(move::Y)]   = "Y";
        ret[static_cast<std::size_t>(move::Yp)]  = "Yʹ";
        ret[static_cast<std::size_t>(move::Y2)]  = "Y2";
        ret[static_cast<std::size_t>(move::Z)]   = "Z";
        ret[static_cast<std::size_t>(move::Zp)]  = "Zʹ";
        ret[static_cast<std::size_t>(move::Z2)]  = "Z2";
        return ret;
    }();
    return o << move_names[static_cast<std::size_t>(m)];
}

/* Cube state representation */
struct cube
{
    // Cube state representation
    // =========================
    //
    // Face orientation
    // -----------
    //
    // Face orientaiton is one of 'U', 'R', 'D', and 'L' respectively. When the
    // cube is solved, all faces are in the 'U' state. When a face is rotated
    // clockwise, it moves to the nedt state in the sequence U, R, D, L, U, R,
    // D, L, etc.
    //
    // Edge orientation
    // ----------------
    //
    // Edge orientation is a boolean. Edges are in their 'unflipped' state when
    // they in the same orientation as the they would be if they had arrived in
    // the same position via the F,B,R,L group.
    // Each edge has an 'unflipped' and 'flipped' sticker. The unflipped
    // sticker on the UF edge is the sticker on the U face. The unflipped
    // sticker on other edges is the sticker in the position that the UF edge's
    // unflipped sticker would be in if the UF edge was moved to the position
    // of the other edge via the F,B,R,L group. The other sticker is the
    // flipped sticker.
    //
    // Corner Orientation
    // ------------------
    //
    // Corner orientations are one of 'upright', 'clockwise' and
    // 'anticlockwise'. These are represented as 0, 1 and 2 respectively.
    // Corners are in their upright state when they are in the same orientation
    // as they would be if they had arrived in the same position via the
    // U,D,F2,B2,R2,L2 group. Corners are in their clockwise state if they are
    // rotated in-place one position clockwise from the upright state. Corners
    // are in their anticlockwise state if they are rotated in-place one
    // position anticlockwise from the upright state.
    // Each corner has an 'upright', 'clockwise' and 'anticlockwise' sticker.
    // The sticker on the U or D face is the upright sticker, the sticker one
    // position clockwise from it is the clockwise sticker, and the remaining
    // sticker is the anticlockwise sticker.
    //
    // Face Position
    // -------------
    //
    // Faces are numbered from 0-5 as follows:
    // U D F B L R
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
    // Edge orientation:   2 bits * 6      | 11 bits         | 2 bis * 6   = 12
    // Edge orientation:   1 bit * 12      | 1 bit * 11      | 1 bis * 12  = 12
    // Corner Orientation: ln2(3) bits * 8 | ln2(3) bits * 7 | 2 bit * 8   = 16
    // Face Position:      0 bits          | 0 bits          | 3 bit * 3   = 9
    // Edge Position:      ln2(12!) bits   | ln2(12!/2) bits | 4 bit * 12  = 48
    // Corner Position:    ln2(8!) bits    | ln2(8!) bits    | 3 bit * 8   = 24
    // Total:              80.8            | 76.2            | 121

private:
    template <typename S,
              typename Piece,
              typename Pos,
              typename Orientation,
              std::uint8_t OrBits,
              std::uint8_t PieceBits,
              std::uint8_t Offset = 0
              >
    struct state_base
    {
        using rep_t       = std::uint64_t;
        using idx_t       = std::uint8_t;
        using states      = S;
        using piece       = Piece;
        using position    = Pos;
        using orientation = Orientation;

        static constexpr idx_t stride = PieceBits + OrBits;

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
            { return static_cast<piece_t>(m_rep >> OrBits); }

            constexpr orientation orientation() const
            { return static_cast<orientation_t>(m_rep & ((1 << OrBits) - 1)); }

            states at(position pos)
            { return {static_cast<rep_t>(m_rep) << state_base::shift(pos)}; }

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
        { return stride * static_cast<idx_t>(pos) + Offset; }

        constexpr position_state operator[](position p) const
        { return position_state(((*this) & mask(p)).rep >> shift(p)); }

        constexpr states move(position from, position to) const noexcept
        { return (*this)[from].at(to); }

        template <position... Positions>
        constexpr static mask make_mask()
        { return (mask(Positions) | ...); }

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

    // faces layout:
    // P = position, O = orientation, - = unused, * = used by corners
    //      LR FB UD R L B F D U
    // 0b---PppPppPppOoOoOoOoOoOo........................................
    struct faces_state : state_base<faces_state,
                                    face_piece,
                                    face_position,
                                    face_orientation,
                                    2, 0, 40> // 40 = bits used by corners
    {
        static constexpr idx_t pos_stride = 3;
        static constexpr idx_t pos_offset = 52; // corners + face orientation

        enum class face_position_pair : uint8_t
        {
            UD,
            FB,
            LR,
        };

        constexpr static face_position_pair pair(face_position fp) noexcept
        { return static_cast<face_position_pair>(static_cast<idx_t>(fp) >> 1); }

        constexpr static face_position flip(face_position fp) noexcept
        { return static_cast<face_position>(static_cast<idx_t>(fp)^1); }

        constexpr static faces_state place(face_piece p, face_position_pair pos) noexcept
        { return {static_cast<rep_t>(p) << shift(pos)}; }

        struct pos_mask
        {
            constexpr pos_mask(face_position_pair pos) noexcept
                    : rep{static_cast<rep_t>((1 << pos_stride) - 1)
                          << faces_state::shift(pos)}
            {}
            constexpr pos_mask operator~() const noexcept
            { return pos_mask{~rep}; }
            friend constexpr pos_mask operator|(pos_mask a, pos_mask b) noexcept
            { return pos_mask{a.rep | b.rep}; }
            friend constexpr pos_mask operator&(pos_mask a, pos_mask b) noexcept
            { return pos_mask{a.rep & b.rep}; }
            friend constexpr faces_state operator&(pos_mask    a,
                                                   faces_state b) noexcept
            { return faces_state{a.rep & b.rep}; }
            friend constexpr faces_state operator&(faces_state a,
                                                   pos_mask    b) noexcept
            { return faces_state{a.rep & b.rep}; }

        private:
            constexpr pos_mask(rep_t rep) noexcept : rep{rep} {}

            rep_t rep;
        };

        using state_base::shift;
        constexpr static idx_t shift(face_position_pair pos) noexcept
        { return pos_stride * static_cast<idx_t>(pos) + pos_offset; }

        face_piece operator[](face_position p) const
        {
            auto pp = pair(p);
            return static_cast<face_piece>((((*this) & pos_mask(pp)).rep >> shift(pp)) ^ (static_cast<idx_t>(p)&1));
        }

        constexpr states move(face_position from, face_position_pair to) const noexcept
        { return place((*this)[from], to); }

        template <face_position_pair... Positions>
        constexpr static pos_mask make_mask()
        { return (pos_mask(Positions) | ...); }

        constexpr face_piece piece_at(face_position pos) const
        {
            idx_t pos_no = static_cast<idx_t>(pos);
            idx_t off_face = pos_no&1;
            auto pos_pair = static_cast<face_position_pair>(pos_no>>1);
            return static_cast<face_piece>(
                (((*this) & pos_mask(pos_pair)).rep >> shift(pos_pair)) ^ off_face);
        }

        /*
         * stickers
         */

        using stickers = std::array<face_colour, 6>;
        static constexpr stickers standard_stickers = []() {
            using namespace face_colours;
            return stickers{{U, D, F, B, L, R}};
        }();

        constexpr face_colour sticker_colour(face_position pos) const
        { return sticker_colour(pos, standard_stickers); }

        constexpr face_colour sticker_colour(face_position   pos,
                                             const stickers &st) const noexcept
        { return st[static_cast<idx_t>((*this)[pos])]; }

        /*
         * moves
         */

        template <position P1, position P2, position P3, position P4>
        constexpr faces_state rot_90() const noexcept
        {
            return (state_base::rot_90<P1, P2, P3, P4>()
                    & ~make_mask<pair(P1), pair(P2)>())
                   | move(P1, pair(P2))
                   | move(P4, pair(P1));
        }

        template <position P1, position P2, position P3, position P4>
        constexpr faces_state rot_180() const noexcept
        {
            return (state_base::rot_180<P1, P2, P3, P4>()
                    & ~make_mask<pair(P1), pair(P2)>())
                   | move(P3, pair(P1))
                   | move(P4, pair(P2));
        }

        template <face_position ...Faces>
        constexpr faces_state turn_cw() const noexcept
        {
            auto low_bits = ((rep_t{0b1} << shift(Faces)) | ...);
            auto prepared = rep - 4 * ((rep >> 1) & rep & low_bits);
            return {prepared + ((rep_t{1} << shift(Faces)) | ...)};
        }

        template <face_position ...Faces>
        constexpr faces_state turn_acw() const noexcept
        {
            auto low_bits = ((rep_t{0b1} << shift(Faces)) | ...);
            auto prepared = rep + 4 * (~((rep >> 1) | rep) & low_bits);
            return {prepared - ((rep_t{1} << shift(Faces)) | ...)};
        }

        template <face_position ...Faces>
        constexpr faces_state turn_180() const noexcept
        {
            return {rep ^ ((rep_t{2} << shift(Faces)) | ...)};
        }

        constexpr faces_state reset_orientations() const noexcept
        {
            using namespace positions;
            return *this & ~state_base::make_mask<U, D, F, B, L, R>();
        }
    };

    // edges layout:
    // P = position, O = orientation, - = unused
    //       DR   DB   DL   DF   FR   BR   BL   FL   UR   UB   UL   UF
    // 0b----PpppOPpppOPpppOPpppOPPPOOPPPOOPPPOOPPPOOPPPOOPPPOOPPPOOPPPOO
    struct edges_state : state_base<edges_state,
                                    edge_piece,
                                    edge_position,
                                    edge_orientation,
                                    1, 4>
    {
        using stickers = std::array<std::array<face_colour, 2>, 12>;
        static constexpr stickers standard_stickers = []() {
            using namespace face_colours;
            return stickers{{{U, F}, {L, U}, {U, B}, {R, U},
                             {L, F}, {L, B}, {R, B}, {R, F},
                             {D, F}, {L, D}, {D, B}, {R, D}}};
        }();

        static constexpr std::array<std::array<edge_orientation, 6>, 12>
            edge_faces = [] () constexpr {
                using namespace face_colours;
                std::array<std::array<edge_orientation, 6>, 12> ret{};
                for (int e = 0; e < 12; ++e) {
                    for (auto fc : {U, D, F, B, L, R}) {
                        auto fi = static_cast<idx_t>(fc)-1;
                        ret[e][fi] =
                            (standard_stickers[e][unflipped] == fc) ?
                                unflipped :
                                (standard_stickers[e][flipped] == fc) ?
                                flipped :
                                eo_invalid;
                    }
                }
                return ret;
            }();

        constexpr face_colour sticker_colour(edge_position   pos,
                                             face_position   f,
                                             const stickers &stickers) const
        {
            auto es = (*this)[pos];
            auto pos_no   = static_cast<idx_t>(pos);
            auto face_no  = static_cast<idx_t>(f);
            auto piece_no = static_cast<idx_t>(es.piece());
            auto sticker_no =
                (edge_faces[pos_no][face_no] + es.orientation()) % 2;
            return stickers[piece_no][sticker_no];
        }

        constexpr face_colour sticker_colour(edge_position pos,
                                             face_position f) const
        {
            return sticker_colour(pos, f, standard_stickers);
        }

        template <edge_position ...Edges>
        constexpr edges_state flip() const
        {
            return {rep ^ ((rep_t{0b1} << shift(Edges)) | ...)};
        }
    };

    // corners layout:
    // P = position, O = orientation, - = unused, * = used by edges
    //                           DBR  DBL  DFL  UFR  UBR  UBL  UFL  DFR
    // 0b---.....................PppOoPppOoPppOoPppOoPppOoPppOoPppOoPppOo
    struct corners_state : state_base<corners_state,
                                      corner_piece,
                                      corner_position,
                                      corner_orientation,
                                      2, 3>
    {
        using stickers = std::array<std::array<face_colour, 3>, 8>;
        static constexpr stickers standard_stickers = []() {
            using namespace face_colours;
            return stickers{{{ U, F, L }, { U, L, B },
                             { U, B, R }, { U, R, F },
                             { D, L, F }, { D, B, L },
                             { D, R, B }, { D, F, R }}};
        }();

        using corner_faces_t = std::array<std::array<corner_orientation, 6>, 8>;
        static constexpr corner_faces_t corner_faces = []() constexpr
        {
            corner_faces_t ret{};
            for (int c = 0; c < 8; ++c) {
                for (int f = 0; f < 6; ++f) {
                    auto fc   = static_cast<face_colour>(f+1);
                    ret[c][f] = (standard_stickers[c][upright] == fc) ?
                                    upright :
                                    (standard_stickers[c][clockwise] == fc) ?
                                    clockwise :
                                    (standard_stickers[c][anticlockwise] == fc) ?
                                    anticlockwise :
                                    co_invalid;
                }
            }
            return ret;
        }();

        constexpr face_colour sticker_colour(corner_position pos,
                                             face_position   f,
                                             const stickers &st) const noexcept
        {
            auto cs       = (*this)[pos];
            auto pos_no   = static_cast<idx_t>(pos);
            auto face_no  = static_cast<idx_t>(f);
            auto piece_no = static_cast<idx_t>(cs.piece());
            auto sticker_no =
                (corner_faces[pos_no][face_no] + 3 - cs.orientation()) % 3;
            return st[piece_no][sticker_no];
        }

        constexpr face_colour sticker_colour(corner_position pos,
                                             face_position   f) const noexcept
        {
            return sticker_colour(pos, f, standard_stickers);
        }

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
    };

    using face_state   = corners_state::position_state;
    using edge_state   = edges_state::position_state;
    using corner_state = corners_state::position_state;

public:
    using face_stickers   = faces_state::stickers;
    using edge_stickers   = edges_state::stickers;
    using corner_stickers = corners_state::stickers;

    struct stickers
    {
        face_stickers   faces{};
        edge_stickers   edges{};
        corner_stickers corners{};
    };

    static constexpr stickers standard_stickers {
        faces_state::standard_stickers,
        edges_state::standard_stickers,
        corners_state::standard_stickers
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
        m_faces = m_faces
                | faces_state::place(pieces::U, faces_state::face_position_pair::UD)
                | faces_state::place(pieces::F, faces_state::face_position_pair::FB)
                | faces_state::place(pieces::L, faces_state::face_position_pair::LR);
    }

    /*
     * Queries
     */

    constexpr face_colour sticker_colour(face_position f) const noexcept
    { return m_faces.sticker_colour(f); }

    constexpr face_colour sticker_colour(face_position   f,
                                         const stickers &st) const noexcept
    { return m_faces.sticker_colour(f, st.faces); }

    constexpr face_colour sticker_colour(edge_position ep,
                                         face_position f) const noexcept
    { return m_edges.sticker_colour(ep, f); }

    constexpr face_colour sticker_colour(edge_position   ep,
                                         face_position   f,
                                         const stickers &st) const noexcept
    { return m_edges.sticker_colour(ep, f, st.edges); }

    constexpr face_colour sticker_colour(corner_position cp,
                                         face_position   f) const noexcept
    { return m_corners.sticker_colour(cp, f); }

    constexpr face_colour sticker_colour(corner_position cp,
                                         face_position   f,
                                         const stickers &st) const noexcept
    { return m_corners.sticker_colour(cp, f, st.corners); }

    bool solved() const
    {
        using namespace positions;
        cube c = *this;
        c.m_faces = c.m_faces.reset_orientations();
        bool f_is_f;
        face_position known_good;
        switch(c.sticker_colour(U))
        {
        case face_colour::D: c.x2();
        case face_colour::U:
            switch(c.sticker_colour(F))
            {
            case face_colour::B: c.y2(); break;
            case face_colour::L: c.y(); break;
            case face_colour::R: c.yp(); break;
            default: break;
            }
            return c == cube{};
        case face_colour::F: c.xp(); known_good = F; break;
        case face_colour::B: c.x();  known_good = F; break;
        case face_colour::L: c.zp(); known_good = L; break;
        case face_colour::R: c.z(); known_good = L; break;
        default: break;
        }
        switch(c.sticker_colour(face_position::U))
        {
        case face_colour::D: known_good == F ? c.z2() : c.x2(); break;
        case face_colour::F: c.xp(); break;
        case face_colour::B: c.x(); break; // F on F
        case face_colour::L: c.zp(); break; // L on L
        case face_colour::R: c.z(); break; // L on L
        default: break;
        }
        return c == cube{};
    }

    /*
     * Moves
     */

    constexpr cube& apply(move m) noexcept
    {
        return (this->*(m_move_fns[static_cast<std::size_t>(m)]))();
    }

    constexpr cube& u() noexcept
    {
        using namespace positions;
        return ud_90<U, true, UF, UL, UB, UR, UFL, UBL, UBR, UFR>();
    }
    constexpr cube& up() noexcept
    {
        using namespace positions;
        return ud_90<U, false, UF, UR, UB, UL, UFL, UFR, UBR, UBL>();
    }
    constexpr cube& u2() noexcept
    {
        using namespace positions;
        return udfblr_180<U, UF, UL, UB, UR, UFL, UBL, UBR, UFR>();
    }

    constexpr cube& d() noexcept
    {
        using namespace positions;
        return ud_90<D, true, DF, DR, DB, DL, DFL, DFR, DBR, DBL>();
    }
    constexpr cube& dp() noexcept
    {
        using namespace positions;
        return ud_90<D, false, DF, DL, DB, DR, DFL, DBL, DBR, DFR>();
    }
    constexpr cube& d2() noexcept
    {
        using namespace positions;
        return udfblr_180<D, DF, DL, DB, DR, DFL, DBL, DBR, DFR>();
    }

    constexpr cube &f() noexcept
    {
        using namespace positions;
        return fblr_90<F, true, UF, FR, DF, FL, UFL, UFR, DFR, DFL, false>();
    }
    constexpr cube &fp() noexcept
    {
        using namespace positions;
        return fblr_90<F, false, UF, FL, DF, FR, UFL, DFL, DFR, UFR, false>();
    }
    constexpr cube &f2() noexcept
    {
        using namespace positions;
        return udfblr_180<F, UF, FR, DF, FL, UFL, UFR, DFR, DFL>();
    }

    constexpr cube &b() noexcept
    {
        using namespace positions;
        return fblr_90<B, true, UB, BL, DB, BR, UBL, DBL, DBR, UBR, true>();
    }
    constexpr cube &bp() noexcept
    {
        using namespace positions;
        return fblr_90<B, false, UB, BR, DB, BL, UBL, UBR, DBR, DBL, true>();
    }
    constexpr cube &b2() noexcept
    {
        using namespace positions;
        return udfblr_180<B, UB, BL, DB, BR, UBL, DBL, DBR, UBR>();
    }

    constexpr cube &l() noexcept
    {
        using namespace positions;
        return fblr_90<L, true, UL, FL, DL, BL, UFL, DFL, DBL, UBL, true>();
    }
    constexpr cube &lp() noexcept
    {
        using namespace positions;
        return fblr_90<L, false, UL, BL, DL, FL, UFL, UBL, DBL, DFL, true>();
    }
    constexpr cube &l2() noexcept
    {
        using namespace positions;
        return udfblr_180<L, UL, FL, DL, BL, UFL, DFL, DBL, UBL>();
    }

    constexpr cube &r() noexcept
    {
        using namespace positions;
        return fblr_90<R, true, UR, BR, DR, FR, UFR, UBR, DBR, DFR, false>();
    }
    constexpr cube &rp() noexcept
    {
        using namespace positions;
        return fblr_90<R, false, UR, FR, DR, BR, UFR, DFR, DBR, UBR, false>();
    }
    constexpr cube &r2() noexcept
    {
        using namespace positions;
        return udfblr_180<R, UR, BR, DR, FR, UFR, UBR, DBR, DFR>();
    }

    constexpr cube &m() noexcept
    {
        using namespace positions;
        return mes_90<R, L, U, F, D, B, UF, DF, DB, UB>();
    }
    constexpr cube &mp() noexcept
    {
        using namespace positions;
        return mes_90<L, R, F, U, B, D, UF, UB, DB, DF>();
    }
    constexpr cube &m2() noexcept
    {
        using namespace positions;
        return mes_180<L, R, F, U, B, D, UF, UB, DB, DF>();
    }

    constexpr cube &e() noexcept
    {
        using namespace positions;
        return mes_90<U, D, L, F, R, B, FL, FR, BR, BL>();
    }
    constexpr cube &ep() noexcept
    {
        using namespace positions;
        return mes_90<D, U, F, L, B, R, FL, BL, BR, FR>();
    }
    constexpr cube &e2() noexcept
    {
        using namespace positions;
        return mes_180<U, D, L, F, R, B, FL, FR, BR, BL>();
    }

    constexpr cube &s() noexcept
    {
        using namespace positions;
        return mes_90<B, F, L, U, R, D, UL, UR, DR, DL>();
    }
    constexpr cube &sp() noexcept
    {
        using namespace positions;
        return mes_90<F, B, U, L, D, R, UL, DL, DR, UR>();
    }
    constexpr cube &s2() noexcept
    {
        using namespace positions;
        return mes_180<F, B, L, U, R, D, UL, UR, DR, DL>();
    }

    constexpr cube &uw () noexcept { return u ().ep(); }
    constexpr cube &uwp() noexcept { return up().e (); }
    constexpr cube &uw2() noexcept { return u2().e2(); }
    constexpr cube &dw () noexcept { return d ().e (); }
    constexpr cube &dwp() noexcept { return dp().ep(); }
    constexpr cube &dw2() noexcept { return d2().e2(); }
    constexpr cube &fw () noexcept { return f ().s (); }
    constexpr cube &fwp() noexcept { return fp().sp(); }
    constexpr cube &fw2() noexcept { return f2().s2(); }
    constexpr cube &bw () noexcept { return b ().sp(); }
    constexpr cube &bwp() noexcept { return bp().s (); }
    constexpr cube &bw2() noexcept { return b2().s2(); }
    constexpr cube &lw () noexcept { return l ().m (); }
    constexpr cube &lwp() noexcept { return lp().mp(); }
    constexpr cube &lw2() noexcept { return l2().m2(); }
    constexpr cube &rw () noexcept { return r ().mp(); }
    constexpr cube &rwp() noexcept { return rp().m (); }
    constexpr cube &rw2() noexcept { return r2().m2(); }

    constexpr cube &x()  noexcept { return rw ().lp(); }
    constexpr cube &xp() noexcept { return rwp().l();  }
    constexpr cube &x2() noexcept { return rw2().l2(); }
    constexpr cube &y()  noexcept { return uw ().dp(); }
    constexpr cube &yp() noexcept { return uwp().d();  }
    constexpr cube &y2() noexcept { return uw2().d2(); }
    constexpr cube &z()  noexcept { return fw ().bp(); }
    constexpr cube &zp() noexcept { return fwp().b();  }
    constexpr cube &z2() noexcept { return fw2().b2(); }

    /*
     * Associated free functions
     */

    friend constexpr bool operator==(const cube &a, const cube &b) noexcept
    { return a.m_edges == b.m_edges && a.m_corners == b.m_corners; }
    friend constexpr bool operator!=(const cube &a, const cube &b) noexcept
    { return !(a==b); }

private:
    template <face_position   F,  bool            CW,
              edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4>
    cube &ud_90()
    {
        m_faces = CW ? m_faces.turn_cw<F>() : m_faces.turn_acw<F>();
        m_edges = m_edges.rot_90<E1, E2, E3, E4>()
                          .template flip<E1, E2, E3, E4>();
        m_corners = m_corners.rot_90<C1, C2, C3, C4>();
        return *this;
    }

    template <face_position   F,  bool            CW,
              edge_position   E1, edge_position   E2,
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
        m_faces = CW ? m_faces.turn_cw<F>() : m_faces.turn_acw<F>();
        m_corners = m_corners.rot_90<C1, C2, C3, C4>()
                             .template turn_acw<AcwC1, AcwC2>()
                             .template turn_cw<CwC1, CwC2>();
        m_edges = m_edges.rot_90<E1, E2, E3, E4>();
        return *this;
    }

    template <face_position   F,
              edge_position   E1, edge_position   E2,
              edge_position   E3, edge_position   E4,
              corner_position C1, corner_position C2,
              corner_position C3, corner_position C4>
    cube &udfblr_180()
    {
        m_faces = m_faces.turn_180<F>();
        m_edges = m_edges.rot_180<E1, E2, E3, E4>();
        m_corners = m_corners.rot_180<C1, C2, C3, C4>();
        return *this;
    }

    template <face_position FCW, face_position FACW,
              face_position F1,  face_position F2,
              face_position F3,  face_position F4,
              edge_position E1,  edge_position E2,
              edge_position E3,  edge_position E4>
    cube &mes_90()
    {
        m_faces = m_faces.rot_90<F1, F2, F3, F4>()
                         .template turn_cw<FCW>()
                         .template turn_acw<FACW>();
        m_edges = m_edges.rot_90<E1, E2, E3, E4>()
                         .template flip<E1, E2, E3, E4>();
        return *this;
    }

    template <face_position  FT1, face_position FT2,
              face_position  F1,  face_position F2,
              face_position  F3,  face_position F4,
              edge_position  E1,  edge_position E2,
              edge_position  E3,  edge_position E4>
    cube &mes_180()
    {
        m_faces = m_faces.rot_180<F1, F2, F3, F4>()
                    .template turn_180<FT1, FT2>();
        m_edges = m_edges.rot_180<E1, E2, E3, E4>();
        return *this;
    }

    static constexpr auto m_move_fns = []() constexpr {
        std::array<cube &(cube::*)() noexcept, 54> ret{};
        ret[static_cast<std::size_t>(move::U)]   = &cube::u;
        ret[static_cast<std::size_t>(move::Up)]  = &cube::up;
        ret[static_cast<std::size_t>(move::U2)]  = &cube::u2;
        ret[static_cast<std::size_t>(move::D)]   = &cube::d;
        ret[static_cast<std::size_t>(move::Dp)]  = &cube::dp;
        ret[static_cast<std::size_t>(move::D2)]  = &cube::d2;
        ret[static_cast<std::size_t>(move::F)]   = &cube::f;
        ret[static_cast<std::size_t>(move::Fp)]  = &cube::fp;
        ret[static_cast<std::size_t>(move::F2)]  = &cube::f2;
        ret[static_cast<std::size_t>(move::B)]   = &cube::b;
        ret[static_cast<std::size_t>(move::Bp)]  = &cube::bp;
        ret[static_cast<std::size_t>(move::B2)]  = &cube::b2;
        ret[static_cast<std::size_t>(move::L)]   = &cube::l;
        ret[static_cast<std::size_t>(move::Lp)]  = &cube::lp;
        ret[static_cast<std::size_t>(move::L2)]  = &cube::l2;
        ret[static_cast<std::size_t>(move::R)]   = &cube::r;
        ret[static_cast<std::size_t>(move::Rp)]  = &cube::rp;
        ret[static_cast<std::size_t>(move::R2)]  = &cube::r2;
        ret[static_cast<std::size_t>(move::Uw)]  = &cube::uw;
        ret[static_cast<std::size_t>(move::Uwp)] = &cube::uwp;
        ret[static_cast<std::size_t>(move::Uw2)] = &cube::uw2;
        ret[static_cast<std::size_t>(move::Dw)]  = &cube::dw;
        ret[static_cast<std::size_t>(move::Dwp)] = &cube::dwp;
        ret[static_cast<std::size_t>(move::Dw2)] = &cube::dw2;
        ret[static_cast<std::size_t>(move::Fw)]  = &cube::fw;
        ret[static_cast<std::size_t>(move::Fwp)] = &cube::fwp;
        ret[static_cast<std::size_t>(move::Fw2)] = &cube::fw2;
        ret[static_cast<std::size_t>(move::Bw)]  = &cube::bw;
        ret[static_cast<std::size_t>(move::Bwp)] = &cube::bwp;
        ret[static_cast<std::size_t>(move::Bw2)] = &cube::bw2;
        ret[static_cast<std::size_t>(move::Lw)]  = &cube::lw;
        ret[static_cast<std::size_t>(move::Lwp)] = &cube::lwp;
        ret[static_cast<std::size_t>(move::Lw2)] = &cube::lw2;
        ret[static_cast<std::size_t>(move::Rw)]  = &cube::rw;
        ret[static_cast<std::size_t>(move::Rwp)] = &cube::rwp;
        ret[static_cast<std::size_t>(move::Rw2)] = &cube::rw2;
        ret[static_cast<std::size_t>(move::M)]   = &cube::m;
        ret[static_cast<std::size_t>(move::Mp)]  = &cube::mp;
        ret[static_cast<std::size_t>(move::M2)]  = &cube::m2;
        ret[static_cast<std::size_t>(move::E)]   = &cube::e;
        ret[static_cast<std::size_t>(move::Ep)]  = &cube::ep;
        ret[static_cast<std::size_t>(move::E2)]  = &cube::e2;
        ret[static_cast<std::size_t>(move::S)]   = &cube::s;
        ret[static_cast<std::size_t>(move::Sp)]  = &cube::sp;
        ret[static_cast<std::size_t>(move::S2)]  = &cube::s2;
        ret[static_cast<std::size_t>(move::X)]   = &cube::x;
        ret[static_cast<std::size_t>(move::Xp)]  = &cube::xp;
        ret[static_cast<std::size_t>(move::X2)]  = &cube::x2;
        ret[static_cast<std::size_t>(move::Y)]   = &cube::y;
        ret[static_cast<std::size_t>(move::Yp)]  = &cube::yp;
        ret[static_cast<std::size_t>(move::Y2)]  = &cube::y2;
        ret[static_cast<std::size_t>(move::Z)]   = &cube::z;
        ret[static_cast<std::size_t>(move::Zp)]  = &cube::zp;
        ret[static_cast<std::size_t>(move::Z2)]  = &cube::z2;
        return ret;
    }();

    // Cube state representation:
    //  Each of these holds a 64-bit value encoding the state for edges,
    //  corners and faces respectively.
    //  Both members of the faces and corners union are effectively active at
    //  all times. They use different parts of underlying uint64. Due to C++'s
    //  rules regarding standard layout types and common initial sequences,
    //  this is actually guaranteed to work.
    edges_state       m_edges;
    union {
        corners_state m_corners;
        faces_state   m_faces;
    };
};

static_assert(sizeof(cube) == 16, "");


#endif // CUBE_HPP
