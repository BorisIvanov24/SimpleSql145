#include "SelectSQLQuery.h"
#include "SimpleTablePrinter.h"
#include <sstream>
#pragma warning(disable:4996)

SelectSQLQuery::SelectSQLQuery(Database& database, MyVector<MyString>&& cols, 
							   MyVector<MyString> tables, Expression* 
							   expression) : SQLQuery(database)
{
	this->cols = std::move(cols);
	this->tables = std::move(tables);
	this->expression = expression;
}

SQLResponse SelectSQLQuery::execute()
{
	int tableIndex = -1;

	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == tables[0])
			tableIndex = i;
	}

	if (tableIndex == -1)
	{
		return SQLResponse("No such table, 0 rows affected\n");
	}

	const Table& table = database.getTable(tableIndex);
	MyVector<unsigned> colIds;

	//std::cout << table.getColsCount() << ' ' << table.getRowsCount() << std::endl;
	unsigned numberOfCols;

	if (cols.empty())
	{
		numberOfCols = table.getColsCount();
		for (unsigned i = 0; i < table.getColsCount(); i++)
			colIds.pushBack(i);
	}
	else
	{
		numberOfCols = cols.getSize();
		for (unsigned i = 0; i < cols.getSize(); i++)
		{
			for (unsigned j = 0; j < table.getColsCount(); j++)
			{
				if (cols[i] == table.getColumnName(j))
					colIds.pushBack(j);
			}
		}
	}

	Table selectTable;

	MyVector<bool> expressionValues;
	unsigned trueCount = 0;

	for (unsigned j = 0; j < table.getRowsCount(); j++)
	{
		if (expression == nullptr)
			expressionValues.pushBack(true);
		else
			expressionValues.pushBack(expression->evaluate(table, j));	

		if (expressionValues[j])
			trueCount++;
	}

	
	for (unsigned i = 0; i < colIds.getSize(); i++)
	{
		Column* ptr = new Column(table.getColumnName(colIds[i]), table.getColumnType(colIds[i]));

		for (unsigned j = 0; j < table.getRowsCount(); j++)
		{
			if (expressionValues[j])
			{
				ptr->addValue(table.getValue(j, colIds[i]));
			}
		}

		selectTable.addColumn(ptr);
	}

	std::stringstream ss("");

	SimpleTablePrinter::getInstance().print(selectTable, ss);

	char buffer[32];

	MyString message("\n");
	message += _itoa(trueCount, buffer, 10);

	if (trueCount > 1)
		message += " rows in set\n";
	else
		message += " row in set\n";
	
	ss << message;

	return SQLResponse(ss.str().c_str());
}

SelectSQLQuery::~SelectSQLQuery()
{
	delete expression;
}
