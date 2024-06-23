#include "SimpleTablePrinter.h"

SimpleTablePrinter& SimpleTablePrinter::getInstance()
{
    static SimpleTablePrinter obj;

    return obj;
}

void SimpleTablePrinter::print(const Table& table, std::ostream& os) const
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

    os << '+';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < maxLengths[i] + 2; j++)
        {
            os << '-';
        }
        os << '+';
    }
    os << std::endl;

    os << '|';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        os << ' ';
        size_t numberOfSpaces = maxLengths[i] - table.getColumnName(i).getSize();
        for (int j = 0; j < numberOfSpaces; j++)
        {
            os << ' ';
        }
        os << table.getColumnName(i)<<" |";
    }
    os << std::endl;

    os << '+';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < maxLengths[i] + 2; j++)
        {
            os << '-';
        }
        os << '+';
    }
    os << std::endl;

    for (int i = 0; i < table.getRowsCount(); i++)
    {
        os << '|';
        for (int j = 0; j < table.getColsCount(); j++)
        {
            size_t numberOfSpaces;
            if (table.getValue(i, j).hasValue())
                numberOfSpaces = maxLengths[j] - table.getValue(i, j).getSize();
            else
                numberOfSpaces = maxLengths[j] - 4; // because NULL

            os << ' ';
            for (int k = 0; k < numberOfSpaces; k++)
            {
                os << ' ';
            }
            
            if (table.getValue(i, j).hasValue())
                os << table.getValue(i, j);
            else
                os << "NULL";
            os << " |";
        }
        os << std::endl;
    }

    os << '+';
    for (int i = 0; i < table.getColsCount(); i++)
    {
        for (int j = 0; j < maxLengths[i] + 2; j++)
        {
            os << '-';
        }
        os << '+';
    }

    os << std::endl;
}
