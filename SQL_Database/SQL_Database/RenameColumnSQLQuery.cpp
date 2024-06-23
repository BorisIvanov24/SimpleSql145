#include "RenameColumnSQLQuery.h"

RenameColumnSQLQuery::RenameColumnSQLQuery(Database& db, MyString&& table, 
								           MyString&& colName, MyString&& newColName) :
										   AlterTableSQLQuery(db, std::move(table))
{
	this->colName = std::move(colName);
	this->newColName = std::move(newColName);
}

SQLResponse RenameColumnSQLQuery::execute()
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

	if (colIndex == -1)
	{
		return SQLResponse("No such column, 0 rows affected");
	}

	database.setTableColumnName(tableIndex, colIndex, std::move(newColName));

	return SQLResponse("Query OK, 0 rows affected");
}
