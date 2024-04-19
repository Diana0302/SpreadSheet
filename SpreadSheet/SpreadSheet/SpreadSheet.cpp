#include "spreadsheet.h"

SpreadSheet::SpreadSheet()
    : SpreadSheet(2, 2)
{}

SpreadSheet::SpreadSheet(size_t size)
    : SpreadSheet(size, size)
{}

SpreadSheet::SpreadSheet(size_t row, size_t col)
    : row1 { row }
    , col1 { col }
    , arr1{ new Cell * [row1] }
{
    for (int i = 0; i < row1; ++i) {
        arr1[i] = new Cell[col1];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
    : row1 { rhv.row1 }
    , col1 { rhv.col1 }
    , arr1{ new Cell * [row1] }
{
    for (int i = 0; i < row1; ++i) {
        arr1[i] = new Cell[col1];
    }
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
            arr1[i][j] = rhv.arr1[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
    : row1{ rhv.row1 }
    , col1{ rhv.col1 }
    , arr1{ new Cell * [row1] }
{
    rhv.row1 = 0;
    rhv.col1 = 0;
    rhv.arr1 = nullptr;
}

const SpreadSheet& SpreadSheet::operator= (const SpreadSheet& rhv)
{
    if (this != &rhv) {
        for (int i = 0; i < row1; ++i) {
            delete[] arr1[i];
        }
        delete arr1;
        row1 = rhv.row1;
        col1 = rhv.col1;
        arr1 = new Cell * [row1];

        for (int i = 0; i < row1; ++i) {
            arr1[i] = new Cell[col1];
        }

        for (int i = 0; i < row1; ++i) {
            for (int j = 0; j < col1; ++i) {
                arr1[i][j] = rhv.arr1[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator= (SpreadSheet&& rhv)
{
    if (this != &rhv) {
        for (int i = 0; i < row1; ++i) {
            delete[] arr1[i];
        }
        delete arr1;
        row1 = rhv.row1;
        col1 = rhv.col1;
        arr1 = rhv.arr1;
        rhv.arr1 = nullptr;
    }
    return *this;
}

void SpreadSheet::clear() noexcept
{
    for (int i = 0; i < row1; ++i) {
        delete[] arr1[i];
    }
    delete[] arr1;
    arr1 = nullptr;
    col1 = 0;
    row1 = 0;
}

size_t SpreadSheet::row() const
{
    return row1;
}

size_t SpreadSheet::col() const
{
    return col1;
}

void SpreadSheet::resizeRow(int new_row, int value)
{
    int size = row1 + new_row;
    Cell** tmp = new Cell * [size];
    for (int i = 0; i < size; ++i) {
        tmp[i] = new Cell[col1];
    }
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
            tmp[i][j] = arr1[i][j];
        }
    }
    for (int i = row1; i < size; ++i) {
        for (int j = 0; j < col1; ++j) {
            tmp[i][j] = value;
        }
    }
    for (int i = 0; i < row1; ++i) {
        delete[] arr1[i];
    }
    delete[] arr1;
    arr1 = tmp;
    row1 = size;
    tmp = nullptr;
}

void SpreadSheet::resizeCol(int new_col, int value)
{
    int size = col1 + new_col;
    Cell** tmp = new Cell * [row1];
    for (int i = 0; i < row1; ++i) {
        tmp[i] = new Cell[size];
    }
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1; ++j) {
            tmp[i][j] = arr1[i][j];
        }
    }
    for (int i = 0; i < row1; ++i) {
        for (int j = col1; j < size; ++j) {
            tmp[i][j] = value;
        }
    }
    for (int i = 0; i < row1; ++i) {
        delete[] arr1[i];
    }
    delete[] arr1;
    arr1 = tmp;
    col1 = size;
    tmp = nullptr;
}

void SpreadSheet::resize(int newrow, int newcol, int val)
{
    resizeRow(newrow, val);
    resizeCol(newcol, val);
}

void SpreadSheet::mirrorH()
{
    for (int i = 0; i < row1 / 2; ++i) {
        for (int j = 0; j < col1; ++j) {
            std::swap(arr1[i][j], arr1[row1 - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorV()
{
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1 / 2; ++j) {
            std::swap(arr1[i][j], arr1[i][col1 - j - 1]);
        }
    }
}

void SpreadSheet::mirrorD()
{
    for (int i = 1; i < row1; ++i) {
        for (int j = 0; j < i; ++j) {
            std::swap(arr1[i][j], arr1[j][i]);
        }
    }
}

void SpreadSheet::mirrorSD()
{
    for (int i = 0; i < row1; ++i) {
        for (int j = 0; j < col1 - i; ++j) {
            std::swap(arr1[i][j], arr1[row1 - 1 - j][col1 - 1 - i]);
        }
    }
}

void SpreadSheet::rotate(size_t count)
{
    bool f = false;
    if (count < 0) {

        f = true;
        count *= -1;
    }
    count = count % 4;
    if (count == 0) {
        return;
    }
    if (!f) {
        for (int i = 0; i < count; ++i) {
            mirrorH();
            mirrorD();
        }
    }
    else {
        for (int i = 0; i < count; ++i) {
            mirrorV();
            mirrorD();
        }
    }
}

void SpreadSheet::removeRow(size_t row)
{
    if (row >= row1) {
        throw std::out_of_range("Invalid index!");
    }

    row -= 1;
    Cell** tmp = new Cell * [row1 - 1];
    for (int i = 0, k = 0; i < row1; ++i) {
        if (i == row) {
            continue;
        }
        tmp[k] = new Cell[col1];
        for (int j = 0; j < col1; ++j) {
            tmp[k][j] = arr1[i][j];
        }
        ++k;
    }

    for (int i = 0; i < row1; ++i) {
        delete[] arr1[i];
    }
    delete[] arr1;

    arr1 = tmp;
    --row1;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows)
{
    auto it = rows.end();
    while (it != rows.begin()) {
        --it;
        removeRow(*it);
    }
}

void SpreadSheet::removeCol(size_t col)
{
    if (col >= col1) {
        throw std::out_of_range("Invalid index!");
    }

    col -= 1;

    Cell** temp = new Cell * [row1];
    for (int i = 0; i < row1; ++i) {
        temp[i] = new Cell[col1 - 1];
        for (int j = 0, k = 0; j < col1; ++j) {
            if (j == col) {
                continue;
            }
            temp[i][k++] = arr1[i][j];
        }
    }

    for (int i = 0; i < row1; ++i) {
        delete[] arr1[i];
    }
    delete[] arr1;

    arr1 = temp;
    --col1;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols)
{
    auto it = cols.end();
    while (it != cols.begin()) {
        --it;
        removeCol(*it);
    }
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet slicedSt;
    size_t numrows = rows.size();
    size_t numcols = cols.size();
    slicedSt.row1 = numrows;
    slicedSt.col1 = numcols;
    slicedSt.arr1 = new Cell * [numrows];

    size_t rowindex = 0;
    for (auto row : rows) {
        size_t colindex = 0;
        slicedSt.arr1[rowindex] = new Cell[numcols];
        for (auto col : cols) {
            slicedSt.arr1[rowindex][colindex] = arr1[row - 1][col - 1];
            colindex++;
        }
        rowindex++;
    }
    return slicedSt;
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

Proxy SpreadSheet::operator[] (size_t index)
{
    return  Proxy(arr1[index]);
}

const Proxy SpreadSheet::operator[] (size_t  index) const
{
    return Proxy(arr1[index]);
}

Proxy::Proxy(Cell* ptr)
    : c_ptr{ ptr }
{}

Cell& Proxy::operator[] (size_t index)
{
    return c_ptr[index];
}

const Cell& Proxy::operator[] (size_t index) const
{
    return c_ptr[index];
}


std::ostream& operator<<  (std::ostream& out, const SpreadSheet& rhv)
{
    int width = 7;
    double widthtable = rhv.col() * 8.2;
    int h_line = 1;
    for (size_t i = 0; i < rhv.row(); ++i)
    {
        for (size_t k = 0; k < widthtable; ++k)
        {
            out << std::setw(1) << "-";
        }
        out << "\n";
        for (size_t j = 0; j < rhv.col(); ++j)
        {
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << rhv[i][j];
        }
        out << std::setw(h_line) << "|";
        out << "\n";
    }
    for (size_t k = 0; k < widthtable; ++k)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    if ((lhs.col() != rhs.col()) || (lhs.row() != rhs.row())) {
        return false;
    }
    for (int i = 0; i < lhs.row(); ++i) {
        for (int j = 0; j < lhs.col(); ++j) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    return !(lhs == rhs);
}