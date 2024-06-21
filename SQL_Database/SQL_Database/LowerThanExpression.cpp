#include "LowerThanExpression.h"
#include <cstdlib>

LowerThanExpression::LowerThanExpression(MyString&& left, MyString&& right) : 
										BinaryOperatorExpression(std::move(left), std::move(right))
{
}

bool LowerThanExpression::evaluate(const Table& table, unsigned rowIndex) const
{
	unsigned columnIndex = 0;

	//first find the index of the column
	for (int i = 0; i < table.getColsCount(); i++)
	{
		if (table.getColumnName(i) == left)
		{
			columnIndex = i;
		}
	}

	if (!table.getValue(rowIndex, columnIndex).hasValue())
		return false;

	switch (table.getColumnType(columnIndex))
	{
	case ColumnType::INTEGER:
	{
		return (atoi(table.getValue(rowIndex, columnIndex).c_str()) < atoi(right.c_str()));
	}
	case ColumnType::REAL:
	{
		//custom function for conversion from string to double needs to be made
		char* endPtr;

		return (std::strtod(table.getValue(rowIndex, columnIndex).c_str(), &endPtr) <
			    std::strtod(right.c_str(), &endPtr));
	}
	case ColumnType::TEXT:
	{
		return (strcmp(table.getValue(rowIndex, columnIndex).c_str(), right.c_str()) == -1);
	}
	}
}
