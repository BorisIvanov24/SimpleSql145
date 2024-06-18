#pragma once
#include "SQLQuery.h"

class ShowTablesSQLQuery : public SQLQuery
{
public:
	ShowTablesSQLQuery(Database& database);
	SQLResponse execute() override;
};

