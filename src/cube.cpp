#include <iostream>
#include <termcolor/termcolor.hpp>
#include "cube.hpp"

typedef std::ostream &(*colour_scheme[6])(std::ostream &);

constexpr colour_scheme fg_face_colours = {
    termcolor::white,
    [](std::ostream &o) -> std::ostream & {
        return o << termcolor::bold << termcolor::yellow;
    },
    termcolor::blue,
    termcolor::green,
    termcolor::red,
    termcolor::yellow,
};

constexpr colour_scheme bg_face_colours = {
    termcolor::on_white,
    [](std::ostream &o) -> std::ostream & {return o;},
    termcolor::on_blue,
    termcolor::on_green,
    termcolor::on_red,
    termcolor::on_yellow,
};

constexpr bool foreground_only[] = {false, true, false, false, false, false};

enum class block
{
    upper_half,
    lower_eighth,
    lower_quarter,
    lower_three_eighths, lower_half,
    lower_five_eighths,
    lower_three_quarters,
    lower_seven_eighths,
    full,
    left_seven_eighths,
    left_three_quarters,
    left_five_eighths,
    left_half,
    left_three_eighths,
    left_one_quarter,
    left_one_eighth,
    right_half,
    light_shade,
    medium_shade,
    dark_shade,
    upper_one_eighth,
    right_one_eighth,
    lower_left_quadrant,
    lower_right_quadrant,
    upper_left_quadrant,
    upper_right_quadrant_missing,
    upper_left_lower_right_quadrants,
    lower_right_quadrant_missing,
    lower_left_quadrant_missing,
    upper_right_quadrant,
    upper_right_lower_left_quadrants,
    upper_left_quadrant_missing,
};

static constexpr block block_inverse[] =
{
    block::lower_half,
    block::full,
    block::full,
    block::full,
    block::upper_half,
    block::full,
    block::full,
    block::upper_one_eighth,
    block::full,
    block::right_one_eighth,
    block::full,
    block::full,
    block::right_half,
    block::full,
    block::full,
    block::full,
    block::left_half,
    block::dark_shade,
    block::medium_shade,
    block::light_shade,
    block::lower_seven_eighths,
    block::left_seven_eighths,
    block::lower_left_quadrant_missing,
    block::lower_right_quadrant_missing,
    block::upper_left_quadrant_missing,
    block::upper_right_quadrant,
    block::upper_right_lower_left_quadrants,
    block::lower_right_quadrant,
    block::lower_left_quadrant,
    block::upper_right_quadrant_missing,
    block::upper_left_lower_right_quadrants,
    block::upper_left_quadrant,
};



static inline constexpr const char *block_character(block b)
{
    const char *u8[] = {u8"▀", u8"▁", u8"▂", u8"▃", u8"▄", u8"▅", u8"▆", u8"▇",
                        u8"█", u8"▉", u8"▊", u8"▋", u8"▌", u8"▍", u8"▎", u8"▏",
                        u8"▐", u8"░", u8"▒", u8"▓", u8"▔", u8"▕", u8"▖", u8"▗",
                        u8"▘", u8"▙", u8"▚", u8"▛", u8"▜", u8"▝", u8"▞", u8"▟"};
    return u8[static_cast<unsigned char>(b)];
};


struct pixel_grid
{
    //                   ####
    //                ### 02 ###
    //             -----######!!!!!
    //          --- 01 ----!!!! 12 !!!
    //       #####-------****!!!!!!!@@@@@
    //    ### 00 ####-*** 11 ***!@@@@ 22 @@@
    //   ---#######!!!!!******.....@@@@@@@...
    //   ------#!!! 10 !!!!.... 21 ...@......
    //   ------...!!!!!!!****.......---......
    //   ------......!*** 20 ***.------......
    //   ***---......---******...------...###
    //   ******......------......------######
    //   * 01 *###...------......---***######
    //   ******######------......******######
    //   !!!***######***---...###******###@@@
    //   !!!!!!######******######******@@@@@@
    //   ! 00 !@@@###******######***!!!@@@@@@
    //   !!!!!!@@@@@@******######!!!!!!@@@@@@
    //      !!!@ 10 @!!!***###@@@!!!!!!@@@
    //         @@@@@@!!!!!!@@@@@@!!!!!!
    //            @@@!!!!!!@@@@@@!!!
    //               !!!!!!@@@@@@
    //                  !!!@@@
    //
    //
    struct pixel {
        pixel() : fg{-1}, bg{-1}, shape{block::full} {}
        pixel(face fg, block shape) : fg{(char)fg}, bg{-1}, shape{shape} {}
        pixel(face fg, face bg, block shape) : fg{(char)fg}, bg{(char)bg}, shape{shape} {}
        char  fg;
        char  bg;
        block shape;
    };

    void draw(int row, int col, face f, block b)
    {
        if (m_pixels[row][col].fg != -1)
        {
            m_pixels[row][col].bg = m_pixels[row][col].fg;
        }
        m_pixels[row][col].fg = f;
        m_pixels[row][col].shape = b;
    }

    void draw_top(int x, int y, face f)
    {
        int row = 4 - 2 * y + 2 * x;
        int col = 6 * x + 6 * y;

        draw(row+0, col+5,  f, block::lower_half);
        draw(row+0, col+6,  f, block::lower_half);

        draw(row+1, col+1,  f, block::lower_right_quadrant);
        draw(row+1, col+2,  f, block::lower_half);
        draw(row+1, col+3,  f, block::full);
        draw(row+1, col+4,  f, block::full);
        draw(row+1, col+5,  f, block::full);
        draw(row+1, col+6,  f, block::full);
        draw(row+1, col+7,  f, block::full);
        draw(row+1, col+8,  f, block::full);
        draw(row+1, col+9,  f, block::lower_half);
        draw(row+1, col+10, f, block::lower_left_quadrant);

        draw(row+2, col+0,  f, block::lower_right_quadrant);
        draw(row+2, col+1,  f, block::full);
        draw(row+2, col+2,  f, block::full);
        draw(row+2, col+3,  f, block::full);
        draw(row+2, col+4,  f, block::full);
        draw(row+2, col+5,  f, block::full);
        draw(row+2, col+6,  f, block::full);
        draw(row+2, col+7,  f, block::full);
        draw(row+2, col+8,  f, block::full);
        draw(row+2, col+9,  f, block::full);
        draw(row+2, col+10, f, block::full);
        draw(row+2, col+11, f, block::lower_left_quadrant);

        draw(row+3, col+3,  f, block::full);
        draw(row+3, col+4,  f, block::full);
        draw(row+3, col+5,  f, block::full);
        draw(row+3, col+6,  f, block::full);
        draw(row+3, col+7,  f, block::full);
        draw(row+3, col+8,  f, block::full);

        draw(row+4, col+5,  f, block::upper_half);
        draw(row+4, col+6,  f, block::upper_half);

    }
    void draw_left(int x, int y, face f)
    {
        int row = 14 - 4*y + 2 * x;
        int col = 6*x;
        draw(row+0, col+0, f, block::lower_half);
        draw(row+0, col+1, f, block::lower_left_quadrant);

        draw(row+1, col+0, f, block::full);
        draw(row+1, col+1, f, block::full);
        draw(row+1, col+2, f, block::full);
        draw(row+1, col+3, f, block::lower_half);
        draw(row+1, col+4, f, block::lower_left_quadrant);

        draw(row+2, col+0, f, block::full);
        draw(row+2, col+1, f, block::full);
        draw(row+2, col+2, f, block::full);
        draw(row+2, col+3, f, block::full);
        draw(row+2, col+4, f, block::full);
        draw(row+2, col+5, f, block::upper_right_quadrant_missing);

        draw(row+3, col+0, f, block::full);
        draw(row+3, col+1, f, block::full);
        draw(row+3, col+2, f, block::full);
        draw(row+3, col+3, f, block::full);
        draw(row+3, col+4, f, block::full);
        draw(row+3, col+5, f, block::full);

        draw(row+4, col+0, f, block::upper_half);
        draw(row+4, col+1, f, block::lower_left_quadrant_missing);
        draw(row+4, col+2, f, block::full);
        draw(row+4, col+3, f, block::full);
        draw(row+4, col+4, f, block::full);
        draw(row+4, col+5, f, block::full);

        draw(row+5, col+3, f, block::upper_half);
        draw(row+5, col+4, f, block::lower_left_quadrant_missing);
        draw(row+5, col+5, f, block::full);

        draw(row+6, col+5, f, block::upper_right_quadrant);
    }
    void draw_right(int x, int y, face f)
    {
        int row = 18 - 4*y - 2 * x;
        int col = 6*(x+3);

        draw(row+0, col+4, f, block::lower_right_quadrant);
        draw(row+0, col+5, f, block::lower_half);

        draw(row+1, col+1, f, block::lower_right_quadrant);
        draw(row+1, col+2, f, block::lower_half);
        draw(row+1, col+3, f, block::full);
        draw(row+1, col+4, f, block::full);
        draw(row+1, col+5, f, block::full);

        draw(row+2, col+0, f, block::upper_left_quadrant_missing);
        draw(row+2, col+1, f, block::full);
        draw(row+2, col+2, f, block::full);
        draw(row+2, col+3, f, block::full);
        draw(row+2, col+4, f, block::full);
        draw(row+2, col+5, f, block::full);

        draw(row+3, col+0, f, block::full);
        draw(row+3, col+1, f, block::full);
        draw(row+3, col+2, f, block::full);
        draw(row+3, col+3, f, block::full);
        draw(row+3, col+4, f, block::full);
        draw(row+3, col+5, f, block::full);

        draw(row+4, col+0, f, block::full);
        draw(row+4, col+1, f, block::full);
        draw(row+4, col+2, f, block::full);
        draw(row+4, col+3, f, block::full);
        draw(row+4, col+4, f, block::lower_right_quadrant_missing);
        draw(row+4, col+5, f, block::upper_half);

        draw(row+5, col+0, f, block::full);
        draw(row+5, col+1, f, block::lower_right_quadrant_missing);
        draw(row+5, col+2, f, block::upper_half);

        draw(row+6, col+0, f, block::upper_left_quadrant);
    }

    friend std::ostream& operator<<(std::ostream& o, const pixel_grid& g)
    {
        constexpr auto nullop = +[](std::ostream &o) -> std::ostream & { return o; };
        for (const auto& row : g.m_pixels)
        {
            for (const auto& p : row)
            {
                if (p.fg != -1 and p.bg == p.fg)
                {
                    o << fg_face_colours[p.fg]
                      << block_character(block::full)
                      << termcolor::reset;
                }
                else if (p.bg != -1 and foreground_only[p.bg])
                {
                    o << fg_face_colours[p.bg]
                      << bg_face_colours[p.fg]
                      << block_character(block_inverse[(char)p.shape])
                      << termcolor::reset;
                }
                else
                {
                    o << ((p.fg == -1) ? nullop : fg_face_colours[p.fg])
                      << ((p.bg == -1) ? nullop : bg_face_colours[p.bg])
                      << (p.fg + p.bg == -2 ? " " : block_character(p.shape))
                      << termcolor::reset;
                }
            }
            o << '\n';
        }
        return o;
    }
    constexpr static char rows = 25;
    constexpr static char cols = 36;
    pixel m_pixels[rows][cols];

};

void draw(const cube& c)
{
    pixel_grid pg;
    pixel_grid pg2;
    /* drawing order matters! */
    pg.draw_top(0, 2, c.sticker_colour(positions::UBL, U));
    pg.draw_top(0, 1, c.sticker_colour(positions::UL, U));
    pg.draw_top(1, 2, c.sticker_colour(positions::UB, U));
    pg.draw_top(0, 0, c.sticker_colour(positions::UFL, U));
    pg.draw_top(1, 1, U);
    pg.draw_top(2, 2, c.sticker_colour(positions::UBR, U));
    pg.draw_top(1, 0, c.sticker_colour(positions::UF, U));
    pg.draw_top(2, 1, c.sticker_colour(positions::UR, U));
    pg.draw_top(2, 0, c.sticker_colour(positions::UFR, U));

    pg.draw_left(0, 2, c.sticker_colour(positions::UFL, F));
    pg.draw_left(1, 2, c.sticker_colour(positions::UF, F));
    pg.draw_left(2, 2, c.sticker_colour(positions::UFR, F));
    pg.draw_left(0, 1, c.sticker_colour(positions::FL, F));
    pg.draw_left(1, 1, F);
    pg.draw_left(2, 1, c.sticker_colour(positions::FR, F));
    pg.draw_left(0, 0, c.sticker_colour(positions::DFL, F));
    pg.draw_left(1, 0, c.sticker_colour(positions::DF, F));
    pg.draw_left(2, 0, c.sticker_colour(positions::DFR, F));

    pg.draw_right(0, 2, c.sticker_colour(positions::UFR, R));
    pg.draw_right(1, 2, c.sticker_colour(positions::UR, R));
    pg.draw_right(2, 2, c.sticker_colour(positions::UBR, R));
    pg.draw_right(0, 1, c.sticker_colour(positions::FR, R));
    pg.draw_right(1, 1, R);
    pg.draw_right(2, 1, c.sticker_colour(positions::BR, R));
    pg.draw_right(0, 0, c.sticker_colour(positions::DFR, R));
    pg.draw_right(1, 0, c.sticker_colour(positions::DR, R));
    pg.draw_right(2, 0, c.sticker_colour(positions::DBR, R));

    pg2.draw_top(0, 2, c.sticker_colour(positions::DFR, D));
    pg2.draw_top(0, 1, c.sticker_colour(positions::DF, D));
    pg2.draw_top(1, 2, c.sticker_colour(positions::DR, D));
    pg2.draw_top(0, 0, c.sticker_colour(positions::DFL, D));
    pg2.draw_top(1, 1, D);
    pg2.draw_top(2, 2, c.sticker_colour(positions::DBR, D));
    pg2.draw_top(1, 0, c.sticker_colour(positions::DL, D));
    pg2.draw_top(2, 1, c.sticker_colour(positions::DB, D));
    pg2.draw_top(2, 0, c.sticker_colour(positions::DBL, D));

    pg2.draw_left(0, 2, c.sticker_colour(positions::DFL, L));
    pg2.draw_left(1, 2, c.sticker_colour(positions::DL, L));
    pg2.draw_left(2, 2, c.sticker_colour(positions::DBL, L));
    pg2.draw_left(0, 1, c.sticker_colour(positions::FL, L));
    pg2.draw_left(1, 1, L);
    pg2.draw_left(2, 1, c.sticker_colour(positions::BL, L));
    pg2.draw_left(0, 0, c.sticker_colour(positions::UFL, L));
    pg2.draw_left(1, 0, c.sticker_colour(positions::UL, L));
    pg2.draw_left(2, 0, c.sticker_colour(positions::UBL, L));

    pg2.draw_right(0, 2, c.sticker_colour(positions::DBL, B));
    pg2.draw_right(1, 2, c.sticker_colour(positions::DB, B));
    pg2.draw_right(2, 2, c.sticker_colour(positions::DBR, B));
    pg2.draw_right(0, 1, c.sticker_colour(positions::BL, B));
    pg2.draw_right(1, 1, B);
    pg2.draw_right(2, 1, c.sticker_colour(positions::BR, B));
    pg2.draw_right(0, 0, c.sticker_colour(positions::UBL, B));
    pg2.draw_right(1, 0, c.sticker_colour(positions::UB, B));
    pg2.draw_right(2, 0, c.sticker_colour(positions::UBR, B));

    std::cout << pg << std::endl;
    std::cout << pg2 << std::endl;
}

int main() {
    /********
    {
        cube c;
        c.r();
        c.u().u().u();
        c.r();
        c.u();
        c.r();
        c.u();
        c.r();
        c.u(); c.u(); c.u();
        c.r(); c.r(); c.r();
        c.u(); c.u(); c.u();
        c.r(); c.r();
        draw(c);
    }
    {
        cube c;
        draw(c
                .u()
                .r().r().r()
                .u().u().u()
                .r()
                .u().u().u()
                .r()
                .u()
                .r()
                .u().u().u()
                .r().r().r()
                .u()
                .r()
                .u()
                .r().r()
                .u().u().u()
                .r().r().r()
                .u()
                );
    }
    */
    cube c;
    draw(c.l());


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
