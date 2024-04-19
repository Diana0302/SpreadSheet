#pragma once
#include <cstddef>
#include <iostream>
#include <iomanip>
#include "cell.h"


class Proxy
{
private:
    Cell* c_ptr;
public:
    explicit Proxy(Cell* p);
    Cell& operator[] (size_t i);
    const Cell& operator[] (size_t i) const;

};


class SpreadSheet
{

private:
    size_t row1;
    size_t col1;
    Cell** arr1;
public:
    SpreadSheet();
    SpreadSheet(size_t size);
    SpreadSheet(size_t row, size_t col);
    SpreadSheet(const SpreadSheet& rhv);
    SpreadSheet(SpreadSheet&& rhv);
    const SpreadSheet& operator= (const SpreadSheet& rhv);
    const SpreadSheet& operator= (SpreadSheet&& rhv);
    ~SpreadSheet();

    Proxy operator[] (size_t index);
    const Proxy operator[] (size_t index) const;

    void clear() noexcept;
    size_t row() const;
    size_t col() const;
    void resizeRow(int new_row, int value = 0);
    void resizeCol(int new_col, int value = 0);
    void resize(int new_row, int new_col, int value = 0);

    void mirrorH();
    void mirrorV();
    void mirrorD();
    void mirrorSD();
    void rotate(size_t count);
    void removeRow(size_t row);
    void removeRows(std::initializer_list<size_t> rows);
    void removeCol(size_t col);
    void removeCols(std::initializer_list<size_t> cols);
    SpreadSheet slice(std::initializer_list<size_t> rows,
        std::initializer_list<size_t> cols);
};

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob);
bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs);
bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs);