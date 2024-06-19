#include "InsertIntoSQLQuery.h"
#pragma warning(disable:4996)

InsertIntoSQLQuery::InsertIntoSQLQuery(Database& database, MyString&& tableName, 
									   MyVector<MyString>&& cols,
	                                   MyVector<MyVector<OptionalString>>&& values) :
									   SQLQuery(database)
{
	this->tableName = std::move(tableName);
	this->cols = std::move(cols);
	this->values = std::move(values);
}

SQLResponse InsertIntoSQLQuery::execute()
{
	int tableIndex = -1;

	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == tableName)
		{
			tableIndex = i;
		}
	}

	if (tableIndex == -1)
		return SQLResponse("Query not OK, invalid table name, 0 rows affected");

	const Table& table = database.getTable(tableIndex);
	unsigned index = 0;
	size_t rowsCountStart = table.getRowsCount();

	for (int i = 0; i < table.getColsCount(); i++)
	{
		for (int j = 0; j < cols.getSize(); j++)
		{
			if (table.getColumnName(i) == cols[j])
			{
				size_t rowsCount = rowsCountStart;
				
				for (int k = 0; k < values.getSize(); k++)
				{
					//std::cout << values[k][index] <<" "<<rowsCount <<" "<<i << std::endl;
					database.setValue(tableIndex, std::move(values[k][index]), rowsCount, i);
				    rowsCount++;
				}
				//std::cout << "----" << std::endl;

				index++;
			}
		}
	}

	char buffer[16];
	MyString text("Query OK, ");
	text += _itoa(values.getSize(), buffer, 10);
	text += " rows affected";
	return SQLResponse(text);
}
