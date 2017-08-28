#ifndef CUBE_VIEW_HPP
#define CUBE_VIEW_HPP
#include <iosfwd>

#include "cube.hpp"

enum class cube_turn : std::uint8_t
{
    X,
    Xp,
    X2,
    Y,
    Yp,
    Y2,
    Z,
    Zp,
    Z2,
};

enum class view_face_position : uint8_t
{
    U, D,
    F, B,
    L, R,
};

std::ostream &operator<<(std::ostream &o, view_face_position f)
{
    static const char *names[] = {"U", "D", "F", "B", "L", "R"};
    return o << names[static_cast<std::uint8_t>(f)];
}

enum class view_edge_position
{
    UF, UL, UB, UR,
    FL, BL, BR, FR,
    DF, DL, DB, DR,
};

std::ostream &operator<<(std::ostream &o, view_edge_position pos)
{
    static const char *names[] = {"UF", "UL", "UB", "UR", "FL", "BL",
                                  "BR", "FR", "DF", "DL", "DB", "DR"};
    return o << names[static_cast<std::uint8_t>(pos)];
}

enum class view_corner_position
{
    UFL, UBL, UBR, UFR,
    DFL, DBL, DBR, DFR,
};

std::ostream &operator<<(std::ostream &o, view_corner_position cp)
{
    static const char * names[] = {"UFL", "UBL", "UBR", "UFR",
                                   "DFL", "DBL", "DBR", "DFR"};
    return o << names[static_cast<std::uint8_t>(cp)];
}

namespace view_positions
{
    constexpr view_face_position U = view_face_position::U;
    constexpr view_face_position D = view_face_position::D;
    constexpr view_face_position F = view_face_position::F;
    constexpr view_face_position B = view_face_position::B;
    constexpr view_face_position L = view_face_position::L;
    constexpr view_face_position R = view_face_position::R;

    constexpr view_edge_position UF = view_edge_position::UF;
    constexpr view_edge_position UL = view_edge_position::UL;
    constexpr view_edge_position UB = view_edge_position::UB;
    constexpr view_edge_position UR = view_edge_position::UR;
    constexpr view_edge_position FL = view_edge_position::FL;
    constexpr view_edge_position BL = view_edge_position::BL;
    constexpr view_edge_position BR = view_edge_position::BR;
    constexpr view_edge_position FR = view_edge_position::FR;
    constexpr view_edge_position DF = view_edge_position::DF;
    constexpr view_edge_position DL = view_edge_position::DL;
    constexpr view_edge_position DB = view_edge_position::DB;
    constexpr view_edge_position DR = view_edge_position::DR;

    constexpr view_corner_position UFL = view_corner_position::UFL;
    constexpr view_corner_position UBL = view_corner_position::UBL;
    constexpr view_corner_position UBR = view_corner_position::UBR;
    constexpr view_corner_position UFR = view_corner_position::UFR;
    constexpr view_corner_position DFL = view_corner_position::DFL;
    constexpr view_corner_position DBL = view_corner_position::DBL;
    constexpr view_corner_position DBR = view_corner_position::DBR;
    constexpr view_corner_position DFR = view_corner_position::DFR;
}


struct cube_view
{
    cube_view()
    {
        using namespace positions;
        m_face_map = {{U, D, F, B, L, R}};
    }
private:
    template <typename E>
    constexpr auto u8(E e) const noexcept
    {
        return static_cast<std::uint8_t>(e);
    };

public:

    cube cube() const { return m_cube; }

    using face_transform_t = std::array<std::array<view_face_position, 6>, 9>;
    static constexpr auto face_transform = []() -> face_transform_t {
        using namespace view_positions;
        return {{
            // U D F  B  L  R
            {F, B, D, U, L, R}, // X,
            {B, F, U, D, L, R}, // Xp,
            {D, U, B, F, L, R}, // X2,
            {U, D, R, L, F, B}, // Y,
            {U, D, L, R, B, F}, // Yp,
            {U, D, B, F, R, L}, // Y2,
            {L, R, F, B, D, U}, // Z,
            {R, L, F, B, U, D}, // Zp,
            {D, U, F, B, R, L}, // Z2,
        }};
    }();

    cube_view& apply(cube_turn t)
    {
        std::array<face_position,6> new_face_map;
        using namespace view_positions;
        new_face_map[u8(U)] = m_face_map[u8(face_transform[u8(t)][u8(U)])];
        new_face_map[u8(D)] = m_face_map[u8(face_transform[u8(t)][u8(D)])];
        new_face_map[u8(F)] = m_face_map[u8(face_transform[u8(t)][u8(F)])];
        new_face_map[u8(B)] = m_face_map[u8(face_transform[u8(t)][u8(B)])];
        new_face_map[u8(L)] = m_face_map[u8(face_transform[u8(t)][u8(L)])];
        new_face_map[u8(R)] = m_face_map[u8(face_transform[u8(t)][u8(R)])];
        m_face_map = new_face_map;
        return *this;
    };

    template <typename... Ts>
    constexpr face_colour sticker_colour(view_face_position f,
                                         Ts &&... ts) const noexcept
    {
        return m_cube.sticker_colour(m_face_map[u8(f)],
                                     std::forward<Ts>(ts)...);
    }

    // indexed by view_edge_position
    using edge_faces_t =
        std::array<std::pair<view_face_position, view_face_position>, 12>;
    constexpr static edge_faces_t edge_faces = []() -> edge_faces_t {
        using namespace view_positions;
        return {{
            {U, F}, {U, L}, {U, B}, {U, R},
            {F, L}, {B, L}, {B, R}, {F, R},
            {D, F}, {D, L}, {D, B}, {D, R},
        }};
    }();

    // indexed by face_position, face_position
    using faces_to_edge_t = std::array<std::array<edge_position, 6>, 6>;
    constexpr static faces_to_edge_t faces_to_edge = []() constexpr
                                                         ->faces_to_edge_t
    {
        using namespace positions;
        constexpr edge_position xx = static_cast<edge_position>(-1);
        return {{
            // U  D   F   B   L   R
            { xx, xx, UF, UB, UL, UR}, // U
            { xx, xx, DF, DB, DL, DR}, // D
            { UF, DF, xx, xx, FL, FR}, // F
            { UB, DB, xx, xx, BL, BR}, // B
            { UL, DL, FL, BL, xx, xx}, // L
            { UR, DR, FR, BR, xx, xx}, // R
        }};
    }();

    template <typename... Ts>
    constexpr face_colour sticker_colour(view_edge_position vep,
                                         view_face_position f,
                                         Ts &&... ts) const noexcept
    {
        auto faces = edge_faces[u8(vep)];
        edge_position ep = faces_to_edge[u8(m_face_map[u8(faces.first)])]
                                        [u8(m_face_map[u8(faces.second)])];
        return m_cube.sticker_colour(
            ep, m_face_map[u8(f)], std::forward<Ts>(ts)...);
    }

    constexpr face_colour sticker_colour(view_edge_position        vep,
                                         view_face_position        f,
                                         const cube::edge_stickers &st) const noexcept
    {
        auto faces = edge_faces[u8(vep)];
        edge_position ep = faces_to_edge[u8(m_face_map[u8(faces.first)])]
                                        [u8(m_face_map[u8(faces.second)])];
        return m_cube.sticker_colour(ep, m_face_map[u8(f)], st);
    }

    // indexed by view_corner_position
    struct corner_faces
    {
        view_face_position up;
        view_face_position cw;
        view_face_position acw;
    };
    using corner_faces_t = std::array<corner_faces, 8> ;
    constexpr static corner_faces_t corner_faces = []() -> corner_faces_t {
        using namespace view_positions;
        return {{{U, F, L},
                 {U, B, L},
                 {U, B, R},
                 {U, F, R},
                 {D, F, L},
                 {D, B, L},
                 {D, B, R},
                 {D, F, R}}};
    }();

    // indexed by face_position, face_position
    using faces_to_corner_t =
        std::array<std::array<std::array<corner_position, 6>, 6>, 6>;
    constexpr static faces_to_corner_t faces_to_corner = []() constexpr
                                                             ->faces_to_corner_t
    {
        using namespace positions;
        constexpr corner_position xxx = static_cast<corner_position>(-1);
        return {{
            //  U*   D    F    B    L    R
            {{{{xxx, xxx, xxx, xxx, xxx, xxx}},   // U
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // D
              {{xxx, xxx, xxx, xxx, UFL, UFR}},   // F
              {{xxx, xxx, xxx, xxx, UBL, UBR}},   // B
              {{xxx, xxx, UFL, UBL, xxx, xxx}},   // L
              {{xxx, xxx, UFR, UBR, xxx, xxx}}}}, // R
            //  U    D*   F    B    L    R
            {{{{xxx, xxx, xxx, xxx, xxx, xxx}},   // U
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // D
              {{xxx, xxx, xxx, xxx, DFL, DFR}},   // F
              {{xxx, xxx, xxx, xxx, DBL, DBR}},   // B
              {{xxx, xxx, DFL, DBL, xxx, xxx}},   // L
              {{xxx, xxx, DFR, DBR, xxx, xxx}}}}, // R
            //  U   D    F*   B    L    R
            {{{{xxx, xxx, xxx, xxx, UFL, UFR}},   // U
              {{xxx, xxx, xxx, xxx, DFL, DFR}},   // D
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // F
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // B
              {{UFL, DFL, xxx, xxx, xxx, xxx}},   // L
              {{UFR, DFR, xxx, xxx, xxx, xxx}}}}, // R
            //  U   D    F    B*   L    R
            {{{{xxx, xxx, xxx, xxx, UBL, UBR}},   // U
              {{xxx, xxx, xxx, xxx, DBL, DBR}},   // D
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // F
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // B
              {{UBL, DBL, xxx, xxx, xxx, xxx}},   // L
              {{UBR, DBR, xxx, xxx, xxx, xxx}}}}, // R
            //  U   D    F    B    L*   R
            {{{{xxx, xxx, UFL, UBL, xxx, xxx}},   // U
              {{xxx, xxx, DFL, DBL, xxx, xxx}},   // D
              {{UFL, DFL, xxx, xxx, xxx, xxx}},   // F
              {{UBL, DBL, xxx, xxx, xxx, xxx}},   // B
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // L
              {{xxx, xxx, xxx, xxx, xxx, xxx}}}}, // R
            //  U   D    F    B    L    R*
            {{{{xxx, xxx, UFR, UBR, xxx, xxx}},   // U
              {{xxx, xxx, DFR, DBR, xxx, xxx}},   // D
              {{UFR, DFR, xxx, xxx, xxx, xxx}},   // F
              {{UBR, DBR, xxx, xxx, xxx, xxx}},   // B
              {{xxx, xxx, xxx, xxx, xxx, xxx}},   // L
              {{xxx, xxx, xxx, xxx, xxx, xxx}}}}, // R
        }};
    }();

    template <typename... Ts>
    constexpr face_colour sticker_colour(view_corner_position vcp,
                                         view_face_position   f,
                                         Ts &&... ts) const noexcept
    {
        auto faces = corner_faces[u8(vcp)];
        corner_position cp = faces_to_corner[u8(m_face_map[u8(faces.up )])]
                                            [u8(m_face_map[u8(faces.cw )])]
                                            [u8(m_face_map[u8(faces.acw)])];
        return m_cube.sticker_colour(
            cp, m_face_map[u8(f)], std::forward<Ts>(ts)...);
    }

    struct cube &(cube::*ops[6][3])() = {
        {&cube::u, &cube::up, &cube::u2},
        {&cube::d, &cube::dp, &cube::d2},
        {&cube::f, &cube::fp, &cube::f2},
        {&cube::b, &cube::bp, &cube::b2},
        {&cube::l, &cube::lp, &cube::l2},
        {&cube::r, &cube::rp, &cube::r2}};

    constexpr cube_view &face_turn(std::int8_t face, std::int8_t move) noexcept
    {
        (m_cube.*ops[u8(m_face_map[face])][move])();
        return *this;
    }

    constexpr cube_view &u()   noexcept { return face_turn(0, 0); }
    constexpr cube_view &up()  noexcept { return face_turn(0, 1); }
    constexpr cube_view &u2()  noexcept { return face_turn(0, 2); }
    constexpr cube_view &d()   noexcept { return face_turn(1, 0); }
    constexpr cube_view &dp()  noexcept { return face_turn(1, 1); }
    constexpr cube_view &d2()  noexcept { return face_turn(1, 2); }
    constexpr cube_view &f()   noexcept { return face_turn(2, 0); }
    constexpr cube_view &fp()  noexcept { return face_turn(2, 1); }
    constexpr cube_view &f2()  noexcept { return face_turn(2, 2); }
    constexpr cube_view &b()   noexcept { return face_turn(3, 0); }
    constexpr cube_view &bp()  noexcept { return face_turn(3, 1); }
    constexpr cube_view &b2()  noexcept { return face_turn(3, 2); }
    constexpr cube_view &l()   noexcept { return face_turn(4, 0); }
    constexpr cube_view &lp()  noexcept { return face_turn(4, 1); }
    constexpr cube_view &l2()  noexcept { return face_turn(4, 2); }
    constexpr cube_view &r()   noexcept { return face_turn(5, 0); }
    constexpr cube_view &rp()  noexcept { return face_turn(5, 1); }
    constexpr cube_view &r2()  noexcept { return face_turn(5, 2); }

    constexpr cube_view &uw () noexcept { return d ().y (); }
    constexpr cube_view &uwp() noexcept { return dp().yp(); }
    constexpr cube_view &uw2() noexcept { return d2().y2(); }
    constexpr cube_view &dw () noexcept { return u ().yp(); }
    constexpr cube_view &dwp() noexcept { return up().y (); }
    constexpr cube_view &dw2() noexcept { return u2().y2(); }
    constexpr cube_view &fw () noexcept { return b ().z (); }
    constexpr cube_view &fwp() noexcept { return bp().zp(); }
    constexpr cube_view &fw2() noexcept { return b2().z2(); }
    constexpr cube_view &bw () noexcept { return f ().zp(); }
    constexpr cube_view &bwp() noexcept { return fp().z (); }
    constexpr cube_view &bw2() noexcept { return f2().z2(); }
    constexpr cube_view &lw () noexcept { return r ().xp(); }
    constexpr cube_view &lwp() noexcept { return rp().x (); }
    constexpr cube_view &lw2() noexcept { return r2().x2(); }
    constexpr cube_view &rw () noexcept { return l ().x (); }
    constexpr cube_view &rwp() noexcept { return lp().xp(); }
    constexpr cube_view &rw2() noexcept { return l2().x2(); }

    constexpr cube_view &m () noexcept { return r ().lp().xp(); }
    constexpr cube_view &mp() noexcept { return rp().l ().x (); }
    constexpr cube_view &m2() noexcept { return r2().l2().x2(); }
    constexpr cube_view &e () noexcept { return u ().dp().yp(); }
    constexpr cube_view &ep() noexcept { return up().d ().y (); }
    constexpr cube_view &e2() noexcept { return u2().d2().y2(); }
    constexpr cube_view &s () noexcept { return fp().b ().z (); }
    constexpr cube_view &sp() noexcept { return f ().bp().zp(); }
    constexpr cube_view &s2() noexcept { return f2().b2().z2(); }

    constexpr cube_view &x()  noexcept { return apply(cube_turn::X); }
    constexpr cube_view &xp() noexcept { return apply(cube_turn::Xp); }
    constexpr cube_view &x2() noexcept { return apply(cube_turn::X2); }
    constexpr cube_view &y()  noexcept { return apply(cube_turn::Y); }
    constexpr cube_view &yp() noexcept { return apply(cube_turn::Yp); }
    constexpr cube_view &y2() noexcept { return apply(cube_turn::Y2); }
    constexpr cube_view &z()  noexcept { return apply(cube_turn::Z); }
    constexpr cube_view &zp() noexcept { return apply(cube_turn::Zp); }
    constexpr cube_view &z2() noexcept { return apply(cube_turn::Z2); }

    friend constexpr bool operator==(const cube_view &a,
                                     const cube_view &b) noexcept
    {
        return a.m_cube == b.m_cube && a.m_face_map == b.m_face_map;
    }

private:
    struct cube                 m_cube;
    std::array<face_position,6> m_face_map;
};

#endif // CUBE_VIEW_HPP
