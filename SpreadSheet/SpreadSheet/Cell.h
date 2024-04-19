#pragma once
#include <string>
#include <vector>

class Cell
{
private:
    std::string cell;
public:

    explicit Cell();
    explicit Cell(int rhv);
    explicit Cell(double rhv);
    explicit Cell(std::string rhv);
    explicit Cell(char rhv);
    explicit Cell(bool rhv);
    explicit Cell(const std::vector<int>& rhv);
    explicit Cell(const Cell& rhv);
    Cell(Cell&& rhv) noexcept;

    Cell& operator= (const Cell& rhv);
    Cell& operator= (int rhv);
    Cell& operator= (char rhv);
    Cell& operator= (bool rhv);
    Cell& operator= (Cell&& rhv) noexcept;
    Cell& operator= (double rhv);
    Cell& operator= (std::string rhv);
    Cell& operator= (const std::vector<int>& rhv);

    operator int();
    operator double();
    operator bool();
    operator char();
    operator std::string() const;
    operator std::vector<int>();


};

bool operator== (const Cell& oth1, const Cell& oth2);
bool operator!= (const Cell& oth1, const Cell& oth2);

std::ostream& operator<< (std::ostream& out, const Cell& rhv);
std::istream& operator>> (std::istream& in, Cell& rhv);