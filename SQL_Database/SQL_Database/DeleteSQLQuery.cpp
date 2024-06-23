#include "DeleteSQLQuery.h"
#pragma warning (disable:4996)

DeleteSQLQuery::DeleteSQLQuery(Database& db, MyString&& table, Expression* exp) :
							   SQLQuery(db)
{
	this->table = std::move(table);
	this->exp = exp;
}

SQLResponse DeleteSQLQuery::execute()
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

	MyVector<int> vec;

	unsigned rowsAffected = 0;
	for (int i = 0; i < database.getTable(tableIndex).getRowsCount(); i++)
	{
		if (exp == nullptr || exp->evaluate(database.getTable(tableIndex), i))
		{
			rowsAffected++;
			vec.pushBack(i);
		}
	}

	for (int i = vec.getSize() - 1; i >= 0; i--)
	{
		database.removeRow(tableIndex, vec[i]);
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

DeleteSQLQuery::~DeleteSQLQuery()
{
	delete exp;
}
