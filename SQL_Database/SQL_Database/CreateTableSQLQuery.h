#pragma once
#include "SQLQuery.h"
#include "MyVector.hpp"

class CreateTableSQLQuery : public SQLQuery
{
public:
	CreateTableSQLQuery(Database& database, MyVector<Column*>&& columns, MyString&& name);
	SQLResponse execute() override;

	//we forbid copying because copying vector of pointers results in a shallow copy
	CreateTableSQLQuery(const CreateTableSQLQuery& other) = delete;
	CreateTableSQLQuery& operator=(const CreateTableSQLQuery) = delete;

	//the destructor of MyVector will only delete the array of pointers
	//we need to manually delete the memory that every pointer points to
	~CreateTableSQLQuery();
private:
	MyString name;
	MyVector<Column*> columns;
};

