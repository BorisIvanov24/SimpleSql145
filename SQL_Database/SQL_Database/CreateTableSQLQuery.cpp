#include "CreateTableSQLQuery.h"

CreateTableSQLQuery::CreateTableSQLQuery(Database& database, MyVector<Column*>&& columns, 
										 MyString&& name) : SQLQuery(database)
{
	this->columns = std::move(columns);
	this->name = std::move(name);
}

SQLResponse CreateTableSQLQuery::execute()
{
	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == name)
			return SQLResponse("Table already in db, 0 rows affected");
	}

	Table* table = new Table(name);
	
	for (int i = 0; i < columns.getSize(); i++)
	{
		table->addColumn(columns[i]);
	}

	database.addTable(table);

	return SQLResponse("Query OK\n");
}


