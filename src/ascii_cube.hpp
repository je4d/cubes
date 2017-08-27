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
        pixel() : fg{face_colour::none},
                  bg{face_colour::none},
                  shape{block::full}
        {}
        pixel(face_colour fg, block shape)
                : fg{fg}, bg{face_colour::none}, shape{shape}
        {}
        pixel(face_colour fg, face_colour bg, block shape)
                : fg{fg}, bg{bg}, shape{shape}
        {}
        face_colour fg;
        face_colour bg;
        block       shape;
    };

    static constexpr auto front_cell_height = 4;
    static constexpr auto front_cell_skew = 2;
    static constexpr auto front_cell_width = 7;

    static constexpr auto top_cell_height = 2;
    static constexpr auto cell_width = 7;

    void draw(int row, int col, face_colour f, block b)
    {
        if (m_pixels[row][col].fg != face_colour::none)
        {
            m_pixels[row][col].bg = m_pixels[row][col].fg;
        }
        m_pixels[row][col].fg = f;
        m_pixels[row][col].shape = b;
    }

    void draw_top(int x, int y, face_colour f)
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

    void draw_bottom(int x, int y, face_colour f)
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

    void draw_lr_1(int x, int y, face_colour f, bool left)
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

    void draw_lr_2(int x, int y, face_colour f, bool right)
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

    void draw_left(int x, int y, face_colour f)
    {
        draw_lr_1(x, y, f, true);
    }

    void draw_left_under(int x, int y, face_colour f)
    {
        draw_lr_2(x, y, f, false);
    }

    void draw_right(int x, int y, face_colour f)
    {
        return draw_lr_2(x, y, f, true);
    }

    void draw_right_under(int x, int y, face_colour f)
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
                auto fg_idx = static_cast<std::uint8_t>(p.fg);
                auto bg_idx = static_cast<std::uint8_t>(p.bg);
                if (p.fg != face_colour::none and p.bg == p.fg)
                {
                    o << fg_face_colours[fg_idx]
                      << block_character(block::full)
                      << termcolor::reset;
                }
                else if (p.bg != face_colour::none and foreground_only[bg_idx])
                {
                    o << fg_face_colours[bg_idx]
                      << bg_face_colours[fg_idx]
                      << block_character(block_inverse[(char)p.shape])
                      << termcolor::reset;
                }
                else
                {
                    o << ((p.fg == face_colour::none) ? nullop :
                                                        fg_face_colours[fg_idx])
                      << ((p.bg == face_colour::none) ? nullop :
                                                        bg_face_colours[bg_idx])
                      << ((p.fg == face_colour::none
                           and p.bg == face_colour::none) ?
                              " " :
                              block_character(p.shape))
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

void draw(const cube_view& c)
{
    pixel_grid_pair p;
    /* drawing order matters! */
    using namespace view_positions;
    p.top.draw_top(0, 2, c.sticker_colour(UBL, U));
    p.top.draw_top(0, 1, c.sticker_colour(UL, U));
    p.top.draw_top(1, 2, c.sticker_colour(UB, U));
    p.top.draw_top(0, 0, c.sticker_colour(UFL, U));
    p.top.draw_top(1, 1, c.sticker_colour(U));
    p.top.draw_top(2, 2, c.sticker_colour(UBR, U));
    p.top.draw_top(1, 0, c.sticker_colour(UF, U));
    p.top.draw_top(2, 1, c.sticker_colour(UR, U));
    p.top.draw_top(2, 0, c.sticker_colour(UFR, U));

    p.top.draw_left(0, 2, c.sticker_colour(UFL, F));
    p.top.draw_left(1, 2, c.sticker_colour(UF, F));
    p.top.draw_left(2, 2, c.sticker_colour(UFR, F));
    p.top.draw_left(0, 1, c.sticker_colour(FL, F));
    p.top.draw_left(1, 1, c.sticker_colour(F));
    p.top.draw_left(2, 1, c.sticker_colour(FR, F));
    p.top.draw_left(0, 0, c.sticker_colour(DFL, F));
    p.top.draw_left(1, 0, c.sticker_colour(DF, F));
    p.top.draw_left(2, 0, c.sticker_colour(DFR, F));

    p.top.draw_right(0, 2, c.sticker_colour(UFR, R));
    p.top.draw_right(1, 2, c.sticker_colour(UR, R));
    p.top.draw_right(2, 2, c.sticker_colour(UBR, R));
    p.top.draw_right(0, 1, c.sticker_colour(FR, R));
    p.top.draw_right(1, 1, c.sticker_colour(R));
    p.top.draw_right(2, 1, c.sticker_colour(BR, R));
    p.top.draw_right(0, 0, c.sticker_colour(DFR, R));
    p.top.draw_right(1, 0, c.sticker_colour(DR, R));
    p.top.draw_right(2, 0, c.sticker_colour(DBR, R));

    p.bottom.draw_bottom(0, 2, c.sticker_colour(DBL, D));
    p.bottom.draw_bottom(0, 1, c.sticker_colour(DB, D));
    p.bottom.draw_bottom(1, 2, c.sticker_colour(DL, D));
    p.bottom.draw_bottom(0, 0, c.sticker_colour(DBR, D));
    p.bottom.draw_bottom(1, 1, c.sticker_colour(D));
    p.bottom.draw_bottom(2, 2, c.sticker_colour(DFL, D));
    p.bottom.draw_bottom(1, 0, c.sticker_colour(DR, D));
    p.bottom.draw_bottom(2, 1, c.sticker_colour(DF, D));
    p.bottom.draw_bottom(2, 0, c.sticker_colour(DFR, D));

    p.bottom.draw_left_under(0, 2, c.sticker_colour(UBR,  B));
    p.bottom.draw_left_under(1, 2, c.sticker_colour(UB,   B));
    p.bottom.draw_left_under(2, 2, c.sticker_colour(UBL,  B));
    p.bottom.draw_left_under(0, 1, c.sticker_colour(BR,   B));
    p.bottom.draw_left_under(1, 1, c.sticker_colour(B));
    p.bottom.draw_left_under(2, 1, c.sticker_colour(BL,   B));
    p.bottom.draw_left_under(0, 0, c.sticker_colour(DBR,  B));
    p.bottom.draw_left_under(1, 0, c.sticker_colour(DB,   B));
    p.bottom.draw_left_under(2, 0, c.sticker_colour(DBL,  B));

    p.bottom.draw_right_under(0, 2, c.sticker_colour(UBL, L));
    p.bottom.draw_right_under(1, 2, c.sticker_colour(UL,  L));
    p.bottom.draw_right_under(2, 2, c.sticker_colour(UFL, L));
    p.bottom.draw_right_under(0, 1, c.sticker_colour(BL,  L));
    p.bottom.draw_right_under(1, 1, c.sticker_colour(L));
    p.bottom.draw_right_under(2, 1, c.sticker_colour(FL,  L));
    p.bottom.draw_right_under(0, 0, c.sticker_colour(DBL, L));
    p.bottom.draw_right_under(1, 0, c.sticker_colour(DL,  L));
    p.bottom.draw_right_under(2, 0, c.sticker_colour(DFL, L));

    std::cout << p;
}

#endif // ASCII_CUBE_HPP
