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

	// tezi pointeri v vectora ne trqbva da gi triem zashtoto prehvurlqme otgovornostta
	//za tqh na bazata
private:
	MyString name;
	MyVector<Column*> columns;
};

