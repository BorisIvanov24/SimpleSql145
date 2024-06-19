#include "SimpleTablePrinter.h"

SimpleTablePrinter& SimpleTablePrinter::getInstance()
{
    static SimpleTablePrinter obj;

    return obj;
}

void SimpleTablePrinter::print(const Table& table) const
{
    MyVector<size_t> maxLengths;

    for (int i = 0; i < table.getColsCount(); i++)
    {
        maxLengths.pushBack(table.getColumnName(i).getSize());
    }

    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < table.getRowsCount(); j++)
        {
            if (table.getValue(j, i).hasValue())
            {
                size_t currSize = table.getValue(j, i).getSize();
                if (currSize > maxLengths[i])
                    maxLengths[i] = currSize;
            }
            else
            {
                size_t currSize = 4; // because it is NULL
                if (currSize > maxLengths[i])
                    maxLengths[i] = currSize;
            }
        }
    }

    std::cout << '+';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < maxLengths[i] + 2; j++)
        {
            std::cout << '-';
        }
        std::cout << '+';
    }
    std::cout << std::endl;

    std::cout << '|';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        std::cout << ' ';
        size_t numberOfSpaces = maxLengths[i] - table.getColumnName(i).getSize();
        for (int j = 0; j < numberOfSpaces; j++)
        {
            std::cout << ' ';
        }
        std::cout << table.getColumnName(i)<<" |";
    }
    std::cout << std::endl;

    std::cout << '+';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < maxLengths[i] + 2; j++)
        {
            std::cout << '-';
        }
        std::cout << '+';
    }
    std::cout << std::endl;

    for (int i = 0; i < table.getRowsCount(); i++)
    {
        std::cout << '|';
        for (int j = 0; j < table.getColsCount(); j++)
        {
            size_t numberOfSpaces;
            if (table.getValue(i, j).hasValue())
                numberOfSpaces = maxLengths[j] - table.getValue(i, j).getSize();
            else
                numberOfSpaces = maxLengths[j] - 4; // because NULL

            std::cout << ' ';
            for (int k = 0; k < numberOfSpaces; k++)
            {
                std::cout << ' ';
            }
            
            if (table.getValue(i, j).hasValue())
                std::cout << table.getValue(i, j);
            else
                std::cout << "NULL";
            std::cout << " |";
        }
        std::cout << std::endl;
    }

    std::cout << '+';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < maxLengths[i] + 2; j++)
        {
            std::cout << '-';
        }
        std::cout << '+';
    }

    std::cout << std::endl;
}
