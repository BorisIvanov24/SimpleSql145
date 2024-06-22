#include "DropColumnSQLQuery.h"

DropColumnSQLQuery::DropColumnSQLQuery(Database& db, MyString&& table, MyString&& colName) :
									   AlterTableSQLQuery(db, std::move(table))
{
	this->colName = std::move(colName);
}

SQLResponse DropColumnSQLQuery::execute()
{
	int tableIndex = -1;

	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == table)
		{
			tableIndex = i;
		}
	}

	if (tableIndex == -1)
	{
		return SQLResponse("No such table, 0 rows affected");
	}

	int colIndex = -1;

	for (int i = 0; i < database.getTable(tableIndex).getColsCount(); i++)
	{
		if (database.getTable(tableIndex).getColumnName(i) == colName)
		{
			colIndex = i;
		}
	}

	if (tableIndex == -1)
	{
		return SQLResponse("No such column, 0 rows affected");
	}

	database.removeColumn(tableIndex, colIndex);

	return SQLResponse("Query OK, 0 rows affected");
}
