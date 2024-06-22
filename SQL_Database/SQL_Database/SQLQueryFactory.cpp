#include "SQLQueryFactory.h"
#include "ShowTablesSQLQuery.h"
#include "CreateTableSQLQuery.h"
#include "InsertIntoSQLQuery.h"
#include "SelectSQLQuery.h"
#include "ExpressionFactory.h"
#include "AddColumnSQLQuery.h"
#include "DropColumnSQLQuery.h"

enum class QueryType
{
    NONE,
    SHOW_TABLES,
    CREATE_TABLE,
    INSERT_INTO,
    SELECT,
    ALTER_TABLE,
    ADD_COLUMN
};

const char* showTablesQuery = "show tables";
const size_t showTablesQuerySize = 11;

const char* createTableQuery = "create table";
const size_t createTableQuerySize = 12;

const char* insertIntoQuery = "insert into";
const size_t insertIntoQuerySize = 11;

const char* selectQuery = "select";
const size_t selectQuerySize = 6;

const char* alterTableQuery = "alter table";
const size_t alterTableQuerySize = 11;

const char* addColumnQuery = "add";
const size_t addColumnQuerySize = 3;

const char* dropColumnQuery = "drop column";
const size_t dropColumnQuerySize = 11;


static unsigned countCharOccurs(const MyString& str, char ch)
{
    unsigned counter = 0;
    for (int i = 0; i < str.getSize(); i++)
    {
        if (str[i] == ch)
            counter++;
    }

    return counter;
}

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
    else if (str.substr(0, selectQuerySize) == selectQuery)
    {
        return QueryType::SELECT;
    }
    else if (str.substr(0, alterTableQuerySize) == alterTableQuery)
    {
        return QueryType::ALTER_TABLE;
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

static SQLQuery* makeInsertIntoQuery(const MyString& str, Database& db)
{
    MyString tableName;
    MyVector<MyString> cols;
    MyVector<MyVector<OptionalString>> values;
    unsigned index = 0;

    while (str[index] != ' ')
    {
        tableName += str[index];
        index++;
    }

    while (str[index] != ')')
    {
        MyString tempName;
        index += 2;
        while (str[index] != ',' && str[index]!=')')
        {
            tempName += str[index];
            index++;
        }

        cols.pushBack(std::move(tempName));
    }
    index+=2;

    while (str[index] != ' ')
    index++;
    
    //test_table (field1, field2) values (1, 1.0), (2, 2.0)
    int rowsToAdd = countCharOccurs(str, ')') - 1;

    for (int i = 0; i < rowsToAdd; i++)
    {
        while (str[index] != ' ')
            index++;

        MyVector<OptionalString> tempVec;

        while (str[index] != ')')
        {
            index += 2;
            OptionalString tempStr;
            while (str[index] != ',' && str[index] != ')')
            {
                tempStr += str[index];
                index++;
            }

            //fix optionalstring
            tempVec.pushBack(std::move(tempStr));
        }

        values.pushBack(std::move(tempVec));
    }
    
    return new InsertIntoSQLQuery(db, std::move(tableName), std::move(cols), std::move(values));
}

static SQLQuery* makeSelectQuery(const MyString& str, Database& db)
{
    MyVector<MyString> cols;
    MyVector<MyString> tables;
    Expression* exp = nullptr;

    //select field1 from test_table where field1=2;
    //field1, field2 from test_table where ((col2) = (Boris)) or ((col3) < (3.125));

    unsigned index = 0;

    if (str[index] != '*')
    {
        while (str[index] != ' ')
        {
            MyString tempStr;

            while (str[index] != ',' && str[index] != ' ')
            {
                tempStr += str[index];
                index++;
            }

            //std::cout << tempStr << std::endl;
            cols.pushBack(std::move(tempStr));
            if(str[index] == ',')
            index+=2;
        }
    }


    if (str[index] == '*')
        index++;

    index += 6;

    MyString tempStr;
    while (str[index] != ' ' && index<str.getSize())
    {
        tempStr += str[index];
        index++;
    }

    //std::cout << tempStr << ' ' << str[index] << std::endl;
    tables.pushBack(std::move(tempStr));

    //std::cout << str.substr(index + 7, str.getSize() - index) << std::endl;
    if (index != str.getSize())
    {
        exp = ExpressionFactory::makeExpression(str.substr(index + 7, str.getSize() - index));
    }

    return new SelectSQLQuery(db, std::move(cols), std::move(tables), exp);
}

static SQLQuery* makeDropColumnQuery(const MyString& str, Database& db, MyString&& table)
{
    unsigned index = 0;
    MyString colName;

    while (index != str.getSize())
    {
        colName += str[index];
        index++;
    }

    return new DropColumnSQLQuery(db, std::move(table), std::move(colName));
}

static SQLQuery* makeAddColumnQuery(const MyString& str, Database& db, MyString&& table)
{
    unsigned index = 0;
    MyString colName;
    ColumnType type;

    while (str[index] != ' ')
    {
        colName += str[index];
        index++;
    }

    index++;

    switch (str[index])
    {
        case 'i':
        {
            type = ColumnType::INTEGER;
            break;
        }
        case 'r':
        {
            type = ColumnType::REAL;
            break;
        }
        case 't':
        {
            type = ColumnType::TEXT;
            break;
        }
        default:
        {
            type = ColumnType::TEXT;
            break;
        }

    }

    return new AddColumnSQLQuery(db, std::move(table), std::move(colName), type);
}

static SQLQuery* makeAlterTableQuery(const MyString& str, Database& db)
{
    MyString table;
    unsigned index = 0;

    while (str[index] != ' ')
    {
        table += str[index];
        index++;
    }

    index++;

    if (str.substr(index, addColumnQuerySize) == addColumnQuery)
    {
        return makeAddColumnQuery(str.substr(index + addColumnQuerySize + 1, 
                                             str.getSize() - (index + addColumnQuerySize + 2)),
                                             db, std::move(table));
    }
    else if (str.substr(index, dropColumnQuerySize) == dropColumnQuery)
    {
        return makeDropColumnQuery(str.substr(index + dropColumnQuerySize + 1,
                                   str.getSize() - (index + dropColumnQuerySize + 2)),
                                   db, std::move(table));
    }
    else
        return nullptr;
    
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
        case QueryType::INSERT_INTO:
        {
            return makeInsertIntoQuery(str.substr(insertIntoQuerySize + 1,
                                       str.getSize() - insertIntoQuerySize + 1), db);
        }
        case QueryType::SELECT:
        {
            return makeSelectQuery(str.substr(selectQuerySize + 1, str.getSize() - selectQuerySize + 1), db);
        }
        case QueryType::ALTER_TABLE:
        {
            return makeAlterTableQuery(str.substr(alterTableQuerySize + 1, str.getSize() - alterTableQuerySize + 1), db);
        }
    }
}
