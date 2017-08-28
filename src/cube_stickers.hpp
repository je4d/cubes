#ifndef CUBE_STICKERS_HPP
#define CUBE_STICKERS_HPP

struct cube_stickers
{
    face_colour colour(char c)
    {
        return c == '.' ? face_colour::shadow : static_cast<face_colour>(c - '0');
    }

    template <typename E>
    constexpr auto u8(E e) const noexcept
    {
        return static_cast<std::uint8_t>(e);
    };

    cube_stickers(const char (&stickers)[55])
    {
        using namespace positions;
        corners[u8(UFL)][0] = colour(stickers[ 0]);
        edges[u8(UF)][0]    = colour(stickers[ 1]);
        corners[u8(UFR)][0] = colour(stickers[ 2]);
        edges[u8(UL)][1]    = colour(stickers[ 3]);
        faces[u8(U)]        = colour(stickers[ 4]);
        edges[u8(UR)][1]    = colour(stickers[ 5]);
        corners[u8(UBL)][0] = colour(stickers[ 6]);
        edges[u8(UB)][0]    = colour(stickers[ 7]);
        corners[u8(UBR)][0] = colour(stickers[ 8]);
        corners[u8(DFL)][0] = colour(stickers[ 9]);
        edges[u8(DL)][1]    = colour(stickers[10]);
        corners[u8(DBL)][0] = colour(stickers[11]);
        edges[u8(DF)][0]    = colour(stickers[12]);
        faces[u8(D)]        = colour(stickers[13]);
        edges[u8(DB)][0]    = colour(stickers[14]);
        corners[u8(DFR)][0] = colour(stickers[15]);
        edges[u8(DR)][1]    = colour(stickers[16]);
        corners[u8(DBR)][0] = colour(stickers[17]);
        corners[u8(UFL)][1] = colour(stickers[18]);
        edges[u8(FL)][1]    = colour(stickers[19]);
        corners[u8(DFL)][2] = colour(stickers[20]);
        edges[u8(UF)][1]    = colour(stickers[21]);
        faces[u8(F)]        = colour(stickers[22]);
        edges[u8(DF)][1]    = colour(stickers[23]);
        corners[u8(UFR)][2] = colour(stickers[24]);
        edges[u8(FR)][1]    = colour(stickers[25]);
        corners[u8(DFR)][1] = colour(stickers[26]);
        corners[u8(UBR)][1] = colour(stickers[27]);
        edges[u8(BR)][1]    = colour(stickers[28]);
        corners[u8(DBR)][2] = colour(stickers[29]);
        edges[u8(UB)][1]    = colour(stickers[30]);
        faces[u8(B)]        = colour(stickers[31]);
        edges[u8(DB)][1]    = colour(stickers[32]);
        corners[u8(UBL)][2] = colour(stickers[33]);
        edges[u8(BL)][1]    = colour(stickers[34]);
        corners[u8(DBL)][1] = colour(stickers[35]);
        corners[u8(UFL)][2] = colour(stickers[36]);
        edges[u8(UL)][0]    = colour(stickers[37]);
        corners[u8(UBL)][1] = colour(stickers[38]);
        edges[u8(FL)][0]    = colour(stickers[39]);
        faces[u8(L)]        = colour(stickers[40]);
        edges[u8(BL)][0]    = colour(stickers[41]);
        corners[u8(DFL)][1] = colour(stickers[42]);
        edges[u8(DL)][0]    = colour(stickers[43]);
        corners[u8(DBL)][2] = colour(stickers[44]);
        corners[u8(UFR)][1] = colour(stickers[45]);
        edges[u8(FR)][0]    = colour(stickers[46]);
        corners[u8(DFR)][2] = colour(stickers[47]);
        edges[u8(UR)][0]    = colour(stickers[48]);
        faces[u8(R)]        = colour(stickers[49]);
        edges[u8(DR)][0]    = colour(stickers[50]);
        corners[u8(UBR)][2] = colour(stickers[51]);
        edges[u8(BR)][0]    = colour(stickers[52]);
        corners[u8(DBR)][1] = colour(stickers[53]);
    }

    cube::face_stickers   faces;
    cube::edge_stickers   edges;
    cube::corner_stickers corners;
};

#endif // CUBE_STICKERS_HPP
