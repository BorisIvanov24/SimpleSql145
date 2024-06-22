#include "AddColumnSQLQuery.h"

AddColumnSQLQuery::AddColumnSQLQuery(Database& db, MyString&& table, 
									 MyString&& colName, ColumnType type) : 
									 AlterTableSQLQuery(db, std::move(table))
{
	this->colName = std::move(colName);
	this->type = type;
}

SQLResponse AddColumnSQLQuery::execute()
{
	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == table)
		{
			database.addColumn(i, new Column(std::move(colName), type));
			return SQLResponse("Query OK, 0 rows affected");
		}
	}

	return SQLResponse("No such table, 0 rows affected");
}
