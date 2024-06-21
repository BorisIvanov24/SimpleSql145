//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

#include <iostream>
#include "MyString.h"
#include "Column.h"
#include "Table.h"
#include "SimpleTablePrinter.h"
#include <iostream>
#include "Database.h"
#include "ShowTablesSQLQuery.h"
#include "CreateTableSQLQuery.h"
#include "InsertIntoSQLQuery.h" 
#include "SQLQueryFactory.h"
#include "GreaterThanExpression.h"
#include "LowerThanExpression.h"
#include "EqualExpression.h"
#include "ConjunctionExpression.h"
#include "DisjunctionExpression.h"
#include "ExpressionFactory.h"
#include "SelectSQLQuery.h"

//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

/*
Expression-a zaduljitelno skobuvan po sledniq nachin:
    Where ((col2) = (Boris)) or ((col3) < (3.125))

ne se poddurjat izrazi ot sledniq vid:
	Where (col2) > (col3)

*/

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	/*Database db("DatabaseTest");
	Table* table = new Table("table1");		

	table->addColumn(new Column("col1", ColumnType::INTEGER));
	table->addColumn(new Column("col2", ColumnType::TEXT));
	table->addColumn(new Column("col3", ColumnType::REAL));

	table->setValue("12", 3, 0);
	table->setValue("Boris", 0, 1);
	table->setValue("3.14", 2, 2);*/

	/*db.addTable(table);

	SimpleTablePrinter::getInstance().print(db.getTable(0));

	SQLQuery* ptr = SQLQueryFactory::makeQuery("insert into table2 (col1, col3) values (9, 10)", db);
	
	ptr->execute();
	delete ptr;
	std::cout << std::endl;
	SimpleTablePrinter::getInstance().print(db.getTable(0));*/

	//_CrtDumpMemoryLeaks();

	
	Table* table = new Table("table1");

	table->addColumn(new Column("col1", ColumnType::INTEGER));
	table->addColumn(new Column("col2", ColumnType::TEXT));
	table->addColumn(new Column("col3", ColumnType::REAL));

	table->setValue("12", 0, 0);
	table->setValue("Boris", 0, 1);
	table->setValue("3.14", 0, 2);
	table->setValue("3.14", 3, 2);

	Database db("DatabaseTest");
	db.addTable(table);

	SimpleTablePrinter::getInstance().print(*table);

	//Expression* exp = ExpressionFactory::makeExpression("(col3) = (3.14)");

	//Expression* exp = ExpressionFactory::makeExpression("((col2) = (Boris)) and ((col3) = (3.14))");

	//Expression* exp = ExpressionFactory::makeExpression("(((col1) = (12)) and ((col2) = (Boris))) or ((col3) = (3.14))");

	SQLQuery* query = SQLQueryFactory::makeQuery("select col1 from table1 where (col3) = (NULL)", db);

	std::cout << query->execute().getMessage() << std::endl;


	/*for (int i = 0; i < 4; i++)
	{
		std::cout << exp->evaluate(*table, i) << std::endl;
	}*/
	
	/*
								+------+-------+------+
								| col1 |  col2 | col3 |
								+------+-------+------+
								|   12 | Boris | 3.14 |
								| NULL |  NULL | NULL |
								| NULL |  NULL | NULL |
								| NULL |  NULL | 3.14 |
								+------+-------+------+
	*/
}