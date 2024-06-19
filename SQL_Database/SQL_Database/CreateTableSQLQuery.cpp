#include "CreateTableSQLQuery.h"

CreateTableSQLQuery::CreateTableSQLQuery(Database& database, MyVector<Column*>&& columns, 
										 MyString&& name) : SQLQuery(database)
{
	this->columns = std::move(columns);
	this->name = std::move(name);
}

SQLResponse CreateTableSQLQuery::execute()
{
	Table* table = new Table(name);
	
	for (int i = 0; i < columns.getSize(); i++)
	{
		table->addColumn(columns[i]);
	}

	database.addTable(table);

	return SQLResponse("Query OK");
}

CreateTableSQLQuery::~CreateTableSQLQuery()
{
	for (int i = 0; i < columns.getSize(); i++)
	{
		delete columns[i];
	}
}
