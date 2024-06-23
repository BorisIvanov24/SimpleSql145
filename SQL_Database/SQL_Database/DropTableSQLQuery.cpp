#include "DropTableSQLQuery.h"

DropTableSQLQuery::DropTableSQLQuery(Database& db, MyString&& table) : SQLQuery(db)
{
	this->table = std::move(table);
}

SQLResponse DropTableSQLQuery::execute()
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

	database.removeTable(tableIndex);

	return SQLResponse("Query OK, 0 rows affected");
}
