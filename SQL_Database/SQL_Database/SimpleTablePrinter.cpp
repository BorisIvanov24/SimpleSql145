#include "SimpleTablePrinter.h"

SimpleTablePrinter& SimpleTablePrinter::getInstance()
{
    static SimpleTablePrinter obj;

    return obj;
}

void SimpleTablePrinter::print(const Table& table) const
{
    for (int i = 0; i < table.getRowsCount(); i++)
    {
        for (int j = 0; j < table.getColsCount(); j++)
        {
            if (table.getValue(i, j).hasValue())
                std::cout << table.getValue(i, j) << '|';
            else
                std::cout << "NULL|";
        }
        std::cout << std::endl;
    }
}
