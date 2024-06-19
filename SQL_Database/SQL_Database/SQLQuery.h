#pragma once
#include "Database.h"
#include "SQLResponse.h"

class SQLQuery
{
public:
	SQLQuery(Database& database);
	virtual SQLResponse execute() = 0;

	virtual ~SQLQuery() = default;
protected:
	Database& database;
};

