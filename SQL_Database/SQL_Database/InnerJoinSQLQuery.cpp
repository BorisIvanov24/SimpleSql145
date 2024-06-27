#include "InnerJoinSQLQuery.h"
#include "SimpleTablePrinter.h"
#include <sstream>
#pragma warning (disable:4996)

InnerJoinSQLQuery::InnerJoinSQLQuery(Database& db, MyVector<MyString>&& colNames, 
								     MyString&& table1, MyString&& table2, 
									 MyString&& col1Expression, MyString&& col2Expression) :
									 SQLQuery(db)
{
	this->colNames = std::move(colNames);
	this->table1 = std::move(table1);
	this->table2 = std::move(table2);
	this->col1Expression = std::move(col1Expression);
	this->col2Expression = std::move(col2Expression);
}

SQLResponse InnerJoinSQLQuery::execute()
{
	MyVector<unsigned> table1ColIds;
	MyVector<unsigned> table2ColIds;

	int tableIndex1 = -1;

	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == table1)
		{
			tableIndex1 = i;
		}
	}

	if (tableIndex1 == -1)
		return SQLResponse("Query not OK, invalid table name, 0 rows affected");


	int tableIndex2 = -1;

	for (int i = 0; i < database.getSize(); i++)
	{
		if (database.getTable(i).getName() == table2)
		{
			tableIndex2 = i;
		}
	}

	if (tableIndex2 == -1)
		return SQLResponse("Query not OK, invalid table name, 0 rows affected");

	if (database.getTable(tableIndex1).getRowsCount() != database.getTable(tableIndex2).getRowsCount())
		return SQLResponse("tables have different number of rows, 0 rows affected");

		if (colNames.getSize() == 0)
		{
			for (int i = 0; i < database.getTable(tableIndex1).getColsCount();i++)
			{
				table1ColIds.pushBack(i);
	
			}
			for (int i = 0; i < database.getTable(tableIndex2).getColsCount(); i++)
			{
			
				table2ColIds.pushBack(i);
			}
		}


		for (int i = 0; i < colNames.getSize(); i++)
		{
			for (int j = 0; j < database.getTable(tableIndex1).getColsCount(); j++)
			{
				if (database.getTable(tableIndex1).getColumnName(j) == colNames[i])
				{
					table1ColIds.pushBack(j);
				}

			}
		}

		
	for (int i = 0; i < colNames.getSize(); i++)
	{
		for (int j = 0; j < database.getTable(tableIndex2).getColsCount(); j++)
		{
			
			if (database.getTable(tableIndex2).getColumnName(j) == colNames[i])
			{
				table2ColIds.pushBack(j);
			}
		}
	}

	int col1ExpressionIndex = -1;
	for (int i = 0; i < database.getTable(tableIndex1).getColsCount(); i++)
	{
		//std::cout << database.getTable(tableIndex1).getColumnName(i) << "  -  " <<
		//	col1Expression << std::endl;
		if (database.getTable(tableIndex1).getColumnName(i) == col1Expression)
			col1ExpressionIndex = i;
	}

	if (col1ExpressionIndex == -1)
		return SQLResponse("no such column, 0 rows affected");

	int col2ExpressionIndex = -1;
	for (int i = 0; i < database.getTable(tableIndex2).getColsCount(); i++)
	{
		//std::cout << database.getTable(tableIndex2).getColumnName(i) << "  -  " <<
			//col2Expression << std::endl;
		if (database.getTable(tableIndex2).getColumnName(i) == col2Expression)
			col2ExpressionIndex = i;
	}

	if (col2ExpressionIndex == -1)
		return SQLResponse("no such column, 0 rows affected");

	MyVector<unsigned> rowsIndex;

	for (int i = 0; i < database.getTable(tableIndex1).getRowsCount(); i++)
	{
		if (database.getTable(tableIndex1).getValue(i, col1ExpressionIndex) == database.getTable(tableIndex2).getValue(i, col2ExpressionIndex))
		{
			rowsIndex.pushBack(i);
		}
	}

	Table joinTable;

	for (int i = 0; i < table1ColIds.getSize(); i++)
	{
		Column* col = new Column(database.getTable(tableIndex1).getColumnName(table1ColIds[i]), 
			database.getTable(tableIndex1).getColumnType(table1ColIds[i]));

		for (int j = 0; j < rowsIndex.getSize(); j++)
		{
			col->addValue(database.getTable(tableIndex1).getValue(rowsIndex[j], table1ColIds[i]));
		}

		joinTable.addColumn(col);
	}

	for (int i = 0; i < table2ColIds.getSize(); i++)
	{
		std::cout << table2ColIds[i] << std::endl;

		Column* col = new Column(database.getTable(tableIndex2).getColumnName(table2ColIds[i]),
			database.getTable(tableIndex2).getColumnType(table2ColIds[i]));

		for (int j = 0; j < rowsIndex.getSize(); j++)
		{
			col->addValue(database.getTable(tableIndex2).getValue(rowsIndex[j], table2ColIds[i]));
		}

		joinTable.addColumn(col);
	}

	std::stringstream ss("");

	SimpleTablePrinter::getInstance().print(joinTable, ss);

	char buffer[32];

	MyString message("\n");
	message += _itoa(rowsIndex.getSize(), buffer, 10);

	if (rowsIndex.getSize() > 1)
		message += " rows in set\n";
	else
		message += " row in set\n";

	ss << message;

	return SQLResponse(ss.str().c_str());
	return SQLResponse(message);
}
