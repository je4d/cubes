#ifndef ASCII_CUBE_HPP
#define ASCII_CUBE_HPP

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

    static constexpr auto front_cell_height = 4;
    static constexpr auto front_cell_skew = 2;
    static constexpr auto front_cell_width = 7;

    static constexpr auto top_cell_height = 2;
    static constexpr auto cell_width = 7;

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
        int row = (top_cell_height * 2) - top_cell_height * y + top_cell_height * x - 1;
        int col = cell_width * x + cell_width * y;

        draw(row+1, col+4, f, block::lower_half);
        draw(row+1, col+5, f, block::upper_left_quadrant_missing);
        draw(row+1, col+6, f, block::full);
        draw(row+1, col+7, f, block::upper_right_quadrant_missing);
        draw(row+1, col+8, f, block::lower_half);

        draw(row+2, col+1,  f, block::lower_half);
        draw(row+2, col+2,  f, block::upper_left_quadrant_missing);
        draw(row+2, col+3,  f, block::full);
        draw(row+2, col+4,  f, block::full);
        draw(row+2, col+5,  f, block::full);
        draw(row+2, col+6,  f, block::full);
        draw(row+2, col+7,  f, block::full);
        draw(row+2, col+8,  f, block::full);
        draw(row+2, col+9,  f, block::full);
        draw(row+2, col+10, f, block::upper_right_quadrant_missing);
        draw(row+2, col+11, f, block::lower_half);

        draw(row+3, col+2,  f, block::upper_right_quadrant);
        draw(row+3, col+3,  f, block::upper_half);
        draw(row+3, col+4,  f, block::full);
        draw(row+3, col+5,  f, block::full);
        draw(row+3, col+6,  f, block::full);
        draw(row+3, col+7,  f, block::full);
        draw(row+3, col+8,  f, block::full);
        draw(row+3, col+9,  f, block::upper_half);
        draw(row+3, col+10, f, block::upper_left_quadrant);

        draw(row+4, col+5,  f, block::upper_right_quadrant);
        draw(row+4, col+6,  f, block::upper_half);
        draw(row+4, col+7,  f, block::upper_left_quadrant);
    }

    void draw_bottom(int x, int y, face f)
    {
        int row = (top_cell_height * 2) - top_cell_height * y + top_cell_height * x - 1 + front_cell_height * 3;
        int col = cell_width * x + cell_width * y;

        draw(row+1, col+5, f, block::lower_right_quadrant);
        draw(row+1, col+6, f, block::lower_half);
        draw(row+1, col+7, f, block::lower_left_quadrant);

        draw(row+2, col+2,  f, block::lower_right_quadrant);
        draw(row+2, col+3,  f, block::lower_half);
        draw(row+2, col+4,  f, block::full);
        draw(row+2, col+5,  f, block::full);
        draw(row+2, col+6,  f, block::full);
        draw(row+2, col+7,  f, block::full);
        draw(row+2, col+8,  f, block::full);
        draw(row+2, col+9,  f, block::lower_half);
        draw(row+2, col+10, f, block::lower_left_quadrant);

        draw(row+3, col+1,  f, block::upper_half);
        draw(row+3, col+2,  f, block::lower_left_quadrant_missing);
        draw(row+3, col+3,  f, block::full);
        draw(row+3, col+4,  f, block::full);
        draw(row+3, col+5,  f, block::full);
        draw(row+3, col+6,  f, block::full);
        draw(row+3, col+7,  f, block::full);
        draw(row+3, col+8,  f, block::full);
        draw(row+3, col+9,  f, block::full);
        draw(row+3, col+10, f, block::lower_right_quadrant_missing);
        draw(row+3, col+11, f, block::upper_half);

        draw(row+4, col+4,  f, block::upper_half);
        draw(row+4, col+5,  f, block::lower_left_quadrant_missing);
        draw(row+4, col+6,  f, block::full);
        draw(row+4, col+7,  f, block::lower_right_quadrant_missing);
        draw(row+4, col+8,  f, block::upper_half);
    }

    void draw_lr_1(int x, int y, face f, bool left)
    {
        int row = (front_cell_height * 2) - front_cell_height * y
                  + front_cell_skew * x + (left ? top_cell_height * 3 : 0);
        int col = front_cell_width * (x + (left ? 0 : 3));

        if (left) {
            draw(row+0, col+0, f, block::lower_half);
            draw(row+0, col+1, f, block::lower_left_quadrant);

            draw(row+1, col+0, f, block::full);
            draw(row+1, col+1, f, block::full);
            draw(row+1, col+2, f, block::full);
            draw(row+1, col+3, f, block::lower_half);
            draw(row+1, col+4, f, block::lower_left_quadrant);
        } else {
            draw(row+0, col+0, f, block::lower_half);

            draw(row+1, col+0, f, block::full);
            draw(row+1, col+1, f, block::full);
            draw(row+1, col+2, f, block::upper_right_quadrant_missing);
            draw(row+1, col+3, f, block::lower_half);
        }

        draw(row+2, col+0, f, block::full);
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

        if (left) {
            draw(row+4, col+2, f, block::upper_half);
            draw(row+4, col+3, f, block::lower_left_quadrant_missing);
            draw(row+4, col+4, f, block::full);
            draw(row+4, col+5, f, block::full);

            draw(row+5, col+5, f, block::upper_half);
        } else {
            draw(row+4, col+1, f, block::upper_right_quadrant);
            draw(row+4, col+2, f, block::upper_half);
            draw(row+4, col+3, f, block::full);
            draw(row+4, col+4, f, block::full);
            draw(row+4, col+5, f, block::full);

            draw(row+5, col+4, f, block::upper_right_quadrant);
            draw(row+5, col+5, f, block::upper_half);
        }
    }

    void draw_lr_2(int x, int y, face f, bool right)
    {
        int row = (front_cell_height * 2 + front_cell_skew * 2) - front_cell_height * y  - front_cell_skew * x + (right ? top_cell_height * 3 : 0);
        int col = front_cell_width * (x + (right ? 3 : 0));

        if (right) {
            draw(row+0, col+4, f, block::lower_right_quadrant);
            draw(row+0, col+5, f, block::lower_half);

            draw(row+1, col+1, f, block::lower_right_quadrant);
            draw(row+1, col+2, f, block::lower_half);
            draw(row+1, col+3, f, block::full);
            draw(row+1, col+4, f, block::full);
            draw(row+1, col+5, f, block::full);
        } else {
            draw(row+0, col+5, f, block::lower_half);

            draw(row+1, col+2, f, block::lower_half);
            draw(row+1, col+3, f, block::upper_left_quadrant_missing);
            draw(row+1, col+4, f, block::full);
            draw(row+1, col+5, f, block::full);
        }

        draw(row+2, col+0, f, block::full);
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

        if (right) {
            draw(row+4, col+0, f, block::full);
            draw(row+4, col+1, f, block::full);
            draw(row+4, col+2, f, block::lower_right_quadrant_missing);
            draw(row+4, col+3, f, block::upper_half);

            draw(row+5, col+0, f, block::upper_half);
        } else {
            draw(row+4, col+0, f, block::full);
            draw(row+4, col+1, f, block::full);
            draw(row+4, col+2, f, block::full);
            draw(row+4, col+3, f, block::upper_half);
            draw(row+4, col+4, f, block::upper_left_quadrant);

            draw(row+5, col+0, f, block::upper_half);
            draw(row+5, col+1, f, block::upper_left_quadrant);
        }
    }

    void draw_left(int x, int y, face f)
    {
        draw_lr_1(x, y, f, true);
    }

    void draw_left_under(int x, int y, face f)
    {
        draw_lr_2(x, y, f, false);
    }

    void draw_right(int x, int y, face f)
    {
        return draw_lr_2(x, y, f, true);
    }

    void draw_right_under(int x, int y, face f)
    {
        return draw_lr_1(x, y, f, false);
    }

    constexpr static char rows = 24;
    constexpr static char cols = 41;
    pixel m_pixels[rows][cols];

};

struct pixel_grid_pair
{
    pixel_grid top;
    pixel_grid bottom;

    friend std::ostream& operator<<(std::ostream& o, const pixel_grid_pair& pgp)
    {
        auto print_row = [&o](const auto& row) {
            constexpr auto nullop = +[](std::ostream &o) -> std::ostream & { return o; };
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
        };

        auto row2 = pgp.bottom.m_pixels;
        for (const auto& row : pgp.top.m_pixels)
        {
            print_row(row);
            o << "  ";
            print_row(*row2++);
            o << "\n";
        }
        return o;
    }
};

void draw(const cube& c)
{
    pixel_grid_pair p;
    /* drawing order matters! */
    p.top.draw_top(0, 2, c.sticker_colour(positions::UBL, U));
    p.top.draw_top(0, 1, c.sticker_colour(positions::UL, U));
    p.top.draw_top(1, 2, c.sticker_colour(positions::UB, U));
    p.top.draw_top(0, 0, c.sticker_colour(positions::UFL, U));
    p.top.draw_top(1, 1, U);
    p.top.draw_top(2, 2, c.sticker_colour(positions::UBR, U));
    p.top.draw_top(1, 0, c.sticker_colour(positions::UF, U));
    p.top.draw_top(2, 1, c.sticker_colour(positions::UR, U));
    p.top.draw_top(2, 0, c.sticker_colour(positions::UFR, U));

    p.top.draw_left(0, 2, c.sticker_colour(positions::UFL, F));
    p.top.draw_left(1, 2, c.sticker_colour(positions::UF, F));
    p.top.draw_left(2, 2, c.sticker_colour(positions::UFR, F));
    p.top.draw_left(0, 1, c.sticker_colour(positions::FL, F));
    p.top.draw_left(1, 1, F);
    p.top.draw_left(2, 1, c.sticker_colour(positions::FR, F));
    p.top.draw_left(0, 0, c.sticker_colour(positions::DFL, F));
    p.top.draw_left(1, 0, c.sticker_colour(positions::DF, F));
    p.top.draw_left(2, 0, c.sticker_colour(positions::DFR, F));

    p.top.draw_right(0, 2, c.sticker_colour(positions::UFR, R));
    p.top.draw_right(1, 2, c.sticker_colour(positions::UR, R));
    p.top.draw_right(2, 2, c.sticker_colour(positions::UBR, R));
    p.top.draw_right(0, 1, c.sticker_colour(positions::FR, R));
    p.top.draw_right(1, 1, R);
    p.top.draw_right(2, 1, c.sticker_colour(positions::BR, R));
    p.top.draw_right(0, 0, c.sticker_colour(positions::DFR, R));
    p.top.draw_right(1, 0, c.sticker_colour(positions::DR, R));
    p.top.draw_right(2, 0, c.sticker_colour(positions::DBR, R));

    p.bottom.draw_bottom(0, 2, c.sticker_colour(positions::DBL, D));
    p.bottom.draw_bottom(0, 1, c.sticker_colour(positions::DB, D));
    p.bottom.draw_bottom(1, 2, c.sticker_colour(positions::DL, D));
    p.bottom.draw_bottom(0, 0, c.sticker_colour(positions::DBR, D));
    p.bottom.draw_bottom(1, 1, D);
    p.bottom.draw_bottom(2, 2, c.sticker_colour(positions::DFL, D));
    p.bottom.draw_bottom(1, 0, c.sticker_colour(positions::DR, D));
    p.bottom.draw_bottom(2, 1, c.sticker_colour(positions::DF, D));
    p.bottom.draw_bottom(2, 0, c.sticker_colour(positions::DFR, D));

    p.bottom.draw_left_under(0, 2, c.sticker_colour(positions::UBR,  B));
    p.bottom.draw_left_under(1, 2, c.sticker_colour(positions::UB,   B));
    p.bottom.draw_left_under(2, 2, c.sticker_colour(positions::UBL,  B));
    p.bottom.draw_left_under(0, 1, c.sticker_colour(positions::BR,   B));
    p.bottom.draw_left_under(1, 1, B);
    p.bottom.draw_left_under(2, 1, c.sticker_colour(positions::BL,   B));
    p.bottom.draw_left_under(0, 0, c.sticker_colour(positions::DBR,  B));
    p.bottom.draw_left_under(1, 0, c.sticker_colour(positions::DB,   B));
    p.bottom.draw_left_under(2, 0, c.sticker_colour(positions::DBL,  B));

    p.bottom.draw_right_under(0, 2, c.sticker_colour(positions::UBL, L));
    p.bottom.draw_right_under(1, 2, c.sticker_colour(positions::UL,  L));
    p.bottom.draw_right_under(2, 2, c.sticker_colour(positions::UFL, L));
    p.bottom.draw_right_under(0, 1, c.sticker_colour(positions::BL,  L));
    p.bottom.draw_right_under(1, 1, L);
    p.bottom.draw_right_under(2, 1, c.sticker_colour(positions::FL,  L));
    p.bottom.draw_right_under(0, 0, c.sticker_colour(positions::DBL, L));
    p.bottom.draw_right_under(1, 0, c.sticker_colour(positions::DL,  L));
    p.bottom.draw_right_under(2, 0, c.sticker_colour(positions::DFL, L));

    std::cout << p;
}

#endif // ASCII_CUBE_HPP
