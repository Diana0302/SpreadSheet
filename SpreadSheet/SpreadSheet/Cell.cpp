#include "cell.h"
#include <iostream>
#include <sstream>

Cell::Cell()
    : cell("")
{}

Cell::Cell(int rhv)
    : cell{ std::to_string(rhv) }
{}

Cell::Cell(bool rhv)
    : cell{ rhv ? "true" : "false" }
{}

Cell::Cell(char rhv)
    : cell{ std::string(1, rhv) }
{}

Cell::Cell(double rhv)
    : cell{ std::to_string(rhv) }
{}

Cell::Cell(std::string rhv)
    : cell{ rhv }
{}


Cell::Cell(const std::vector<int>& rhv)
{
    cell = "{";
    for (int i = 0; i < rhv.size(); ++i) {
        cell += std::to_string(rhv[i]) + " ,";
    }

    cell.pop_back();
    cell += "}";
}

Cell::Cell(const Cell& rhv)
    : cell{ rhv.cell }
{}

Cell::Cell(Cell&& rhv) noexcept
    : cell(std::move(rhv.cell))
{}


Cell::operator int()
{
    try {
        int x = std::stoi(cell);
        return x;
    }
    catch (...) {
        return 0;
    }
}

Cell::operator double()
{
    try {
        double x = std::stod(cell);
        return x;
    }
    catch (...) {
        return 0.0;
    }
}

Cell::operator std::string() const
{
    return cell;
}

Cell::operator bool()
{
    return !cell.empty();
}

Cell::operator char()
{
    if (!cell.empty()) {
        return cell[0];
    }
    else {
        return '\0';
    }
}

Cell::operator std::vector<int>()
{
    std::vector<int> result;
    std::string tmp = cell;
    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == '{' || tmp[i] == '}' || tmp[i] == ',') {
            tmp[i] = ' ';
        }
    }
    std::stringstream strs(tmp);
    int num;
    while (strs >> num) {
        result.push_back(num);
    }
    return result;
}

Cell& Cell::operator= (const Cell& rhv)
{
    if (this != &rhv) {
        cell = rhv.cell;
    }
    return *this;
}

Cell& Cell::operator= (Cell&& rhv) noexcept
{
    if (this != &rhv) {
        cell = std::move(rhv.cell);
    }
    return *this;
}

Cell& Cell::operator= (int a)
{
    cell = (int)a;
    return *this;
}

Cell& Cell::operator= (double a)
{
    cell = (double)a;
    return *this;
}


Cell& Cell::operator=(char rhv)
{
    cell = rhv;
    return *this;
}

Cell& Cell::operator= (bool rhv)
{
    cell = rhv ? "true" : "false";
    return *this;
}
Cell& Cell::operator= (std::string str)
{
    cell = str;
    return *this;
}

Cell& Cell ::operator= (const std::vector<int>& rhv)
{
    cell = "{";
    for (int i = 0; i < rhv.size(); ++i) {
        cell += std::to_string(rhv[i]) + " ,";
    }
    cell.pop_back();
    cell += "}";
    return *this;
}

bool operator== (const Cell& oth1, const Cell& oth2)
{
    return 1;
}

bool operator!= (const Cell& oth1, const Cell& oth2)
{
    return 1;
}


std::ostream& operator<< (std::ostream& out, const Cell& rhv)
{
    out << std::string(rhv);

    return out;
}


std::istream& operator>> (std::istream& in, Cell& rhv)
{
    std::string str;
    in >> str;

    rhv = Cell(str);
    return in;
}