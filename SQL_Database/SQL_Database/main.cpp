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

int main()
{
	//std::ofstream ofs("file5.dat", std::ios::binary | std::ios::out);
	//std::ifstream ifs("file5.dat", std::ios::binary | std::ios::in);
	Database db("DatabaseTest");
	Table* table = new Table("table1");		

	table->addColumn(new Column("col1", ColumnType::INTEGER));
	table->addColumn(new Column("col2", ColumnType::TEXT));
	table->addColumn(new Column("col3", ColumnType::REAL));

	table->setValue("12", 3, 0);
	table->setValue("Boris", 0, 1);
	table->setValue("3.14", 2, 2);

	db.addTable(table);

	MyString tableName("table1");
	MyVector<MyString> cols;
	cols.pushBack("col1");
	cols.pushBack("col2");
	cols.pushBack("col3");

	MyVector<OptionalString> vec1;
	vec1.pushBack("1");
	vec1.pushBack("Ivanovic");
	vec1.pushBack("345.23");

	MyVector<OptionalString> vec2;
	vec2.pushBack("33");
	vec2.pushBack("Gorna");
	vec2.pushBack("1.999");

	MyVector<MyVector<OptionalString>> values;
	values.pushBack(vec1);
	values.pushBack(vec2);

	InsertIntoSQLQuery insertQuery(db, std::move(tableName), std::move(cols), std::move(values));

	std::cout<<insertQuery.execute().getMessage()<<std::endl;

	SimpleTablePrinter::getInstance().print(db.getTable(0));

	SQLQueryFactory::makeQuery("create table Tablica1 (kola int, kushta text, cena real)", db)->execute();

	std::cout<<SQLQueryFactory::makeQuery("show tables", db)->execute().getMessage()<<std::endl;

	SimpleTablePrinter::getInstance().print(db.getTable(1));



	/*OptionalString str1;
	OptionalString str2;

	std::ifstream ifs("file.dat", std::ios::binary | std::ios::in);

	str1.loadFromBinaryFile(ifs);
	str2.loadFromBinaryFile(ifs);

	if (str1.hasValue())
		std::cout << str1 << std::endl;
	else
		std::cout << "NULL";

	if (str2.hasValue())
		std::cout <<str2<< std::endl;
	else
		std::cout << "NULL";*/

	/*std::ofstream ofs("file1.dat", std::ios::binary | std::ios::out);
	str2.saveToBinaryFile(ofs);
	str1.saveToBinaryFile(ofs);*/

	/*MyString str1;
	MyString str2;

	std::ifstream ifs("file2.dat", std::ios::binary | std::ios::in);

	str1.loadFromBinaryFile(ifs);
	str2.loadFromBinaryFile(ifs);

	std::cout << '_'<<str1<<'_' << std::endl;
	std::cout << str2 << std::endl;*/

	/*Database db("DatabaseTest");

	ShowTablesSQLQuery query(db);

	std::cout<<query.execute().getMessage()<<std::endl;

	MyVector<Column*> vec;
	vec.pushBack(new Column("col1", ColumnType::INTEGER));
	MyString name("added table");

	CreateTableSQLQuery query1(db, std::move(vec), std::move(name));

	query1.execute();

	std::cout << query.execute().getMessage();*/
}