#include "UpdateSQLQuery.h"
#pragma warning (disable:4996)

UpdateSQLQuery::UpdateSQLQuery(Database& db, MyString&& table, MyString&& colName, 
							   MyString&& value, Expression* exp) : SQLQuery(db)
{
	this->table = std::move(table);
	this->colName = std::move(colName);
	this->value = std::move(value);
	this->exp = exp;
}

SQLResponse UpdateSQLQuery::execute()
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

	unsigned rowsAffected = 0;

	

	for (int i = 0; i < database.getTable(tableIndex).getRowsCount(); i++)
	{
		if (exp == nullptr || exp->evaluate(database.getTable(tableIndex), i))
		{
			rowsAffected++;

			if(value == "NULL")
				database.setValue(tableIndex, OptionalString(), i, colIndex);
			else
				database.setValue(tableIndex, OptionalString(value), i, colIndex);
		}
	
	}

	char buffer[32];
	MyString message = "Query OK, ";
	message += _itoa(rowsAffected, buffer, 10);

	if (rowsAffected > 1)
		message += " rows affected";
	else
		message += " row affected";

	return SQLResponse(message);
}

UpdateSQLQuery::~UpdateSQLQuery()
{
	delete exp;
}
