#include "AlterTableSQLQuery.h"

AlterTableSQLQuery::AlterTableSQLQuery(Database& db, MyString&& table) : SQLQuery(db)
{
	this->table = std::move(table);
}
