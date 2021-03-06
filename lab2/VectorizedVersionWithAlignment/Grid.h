//
// Created by Mackem Meya on 08.02.2022.
//

#ifndef GRID_H
#define GRID_H

#include <cstdlib>

#include "Exceptions/MemoryNotAllocatedException.h"

class Grid {
private:
    size_t m_height;
    size_t m_width;
    double *m_data;

public:
    Grid() = default;

    Grid(size_t gridHeight, size_t gridWidth, double initialValue = 0.0) : m_height{ gridHeight }, m_width{ gridWidth },
                                                                           m_data{ (double *) _mm_malloc(gridHeight *
                                                                                                            gridWidth *
                                                                                                            8, 32) } {
        if (m_data == nullptr) {
            throw MemoryNotAllocatedException{ "Failed to allocate memory for Grid" };
        }

        fill(initialValue);
    }

    Grid(const Grid &other) : m_height{ other.m_height }, m_width{ other.m_width },
                              m_data{ (double *) _mm_malloc(other.m_height * other.m_width, 32) } {
        if (m_data == nullptr) {
            throw MemoryNotAllocatedException{ "Failed to allocate memory for Grid" };
        }

        (*this) = other;
    }

    Grid(Grid &&other) noexcept: m_height{ other.m_height }, m_width{ other.m_width }, m_data{ other.m_data } {
        other.m_height = 0;
        other.m_width = 0;
        other.m_data = nullptr;
    }

    ~Grid() {
        _mm_free(m_data);
    }

    size_t getHeight() const;

    size_t getWidth() const;

    void print() const;

    void fill(double value);

    double &operator()(size_t row, size_t column);

    const double &operator()(size_t row, size_t column) const;

    double *operator*();

    const double *operator*() const;

    Grid &operator=(const Grid &other);

    Grid &operator=(Grid &&other) noexcept;

};

#endif //GRID_H
