#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <memory>
#include <vector>

#include "cube.hpp"

template <move... Moves>
constexpr move moves_array[] = {Moves...};

template <move... Moves, typename Pred, typename Sink>
void find_paths_impl2(const Pred& pred, const Sink& sink, move *it, move const *const end, cube state, move prev)
{
    if (pred(state)) {
        sink(it);
        return;
    }
    if (it == end)
        return;
    for (auto move : moves_array<Moves...>) {
        if (move == prev)
            continue;
        *it = move;
        auto nextState = state;
        nextState.apply(move);
        find_paths_impl2<Moves...>(pred, sink, std::next(it), end, nextState, move);
    }
}

template <move... Moves, typename Pred, typename Sink>
void find_paths_impl(const Pred& pred, const Sink& sink, move *it, move const *const end, cube state)
{
    if (pred(state)) {
        sink(it);
        return;
    }
    if (it == end)
        return;
    for (auto move : moves_array<Moves...>) {
        *it = move;
        auto nextState = state;
        nextState.apply(move);
        find_paths_impl2<Moves...>(pred, sink, std::next(it), end, nextState, move);
    }
}
template <move ...Moves, typename Pred>
std::vector<std::vector<move>> find_paths(cube start, const Pred& end, int max)
{
    std::unique_ptr<move[]>        buffer(new move[max]);
    std::vector<std::vector<move>> ret;
    find_paths_impl<Moves...>(
        end,
        [&](auto it) { ret.push_back(std::vector<move>(buffer.get(), it)); },
        buffer.get(), buffer.get() + max, start);
    return ret;
}

template <move ...Moves>
std::vector<std::vector<move>> find_paths(cube start, cube end, int max)
{
    end = end.reset_faces();
    return find_paths<Moves...>(
        start, [=](cube c) { return c.reset_faces() == end; }, max);
}

#endif // ALGORITHMS_HPP
