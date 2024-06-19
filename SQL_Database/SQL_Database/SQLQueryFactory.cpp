#include "SQLQueryFactory.h"
#include "ShowTablesSQLQuery.h"
#include "CreateTableSQLQuery.h"

enum class QueryType
{
    NONE,
    SHOW_TABLES,
    CREATE_TABLE,
    INSERT_INTO
};

const char* showTablesQuery = "show tables";
const size_t showTablesQuerySize = 11;

const char* createTableQuery = "create table";
const size_t createTableQuerySize = 12;

const char* insertIntoQuery = "insert into";
const size_t insertIntoQuerySize = 11;


static QueryType identifyQuery(const MyString& str)
{
    if (str.substr(0, showTablesQuerySize) == showTablesQuery)
    {
        return QueryType::SHOW_TABLES;
    }
    else if (str.substr(0, createTableQuerySize) == createTableQuery)
    {
        return QueryType::CREATE_TABLE;
    }
    else if (str.substr(0, insertIntoQuerySize) == insertIntoQuery)
    {
        return QueryType::INSERT_INTO;
    }
    else
        return QueryType::NONE;
}

static SQLQuery* makeShowTablesQuery(Database& db)
{
    return new ShowTablesSQLQuery(db);
}

static SQLQuery* makeCreateTableQuery(const MyString& str, Database& db)
{
    MyString tableName;
    MyVector<Column*> columns;

    unsigned index = 0;
    while (str[index] != ' ')
    {
        tableName += str[index];
        index++;
    }

    while (str[index] != ')')
    {
        index += 2;
        MyString name;
        ColumnType type = ColumnType::INTEGER;

        while(str[index] != ' ')
        {
            name += str[index];
            index++;
        }

        index++;

        if (str[index] == 'i')
            type = ColumnType::INTEGER;
        else if (str[index] == 'r')
            type = ColumnType::REAL;
        else if (str[index] == 't')
            type = ColumnType::TEXT;

        while (str[index] != ',' && str[index]!=')')
            index++;

        columns.pushBack(new Column(std::move(name), type));
    }

    return new CreateTableSQLQuery(db, std::move(columns), std::move(tableName));
}

SQLQuery* SQLQueryFactory::makeQuery(const MyString& str, Database& db)
{
    QueryType type = identifyQuery(str);

    switch (type)
    {
        case QueryType::SHOW_TABLES:
        {
            return makeShowTablesQuery(db);
        }
        case QueryType::CREATE_TABLE:
        {
            return makeCreateTableQuery(str.substr(createTableQuerySize + 1,
                                        str.getSize() - createTableQuerySize + 1), db);
        }
    }
}
