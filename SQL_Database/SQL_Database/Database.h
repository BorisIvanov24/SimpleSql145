#pragma once
#include "Table.h"
#include "MyString.h"
#include "MyVector.hpp"
#include "SQLResponse.h"

class Database
{
public:
	Database();
	Database(const MyString& filePath);
	Database(const Database& other);
	Database(Database&& other) noexcept;
	Database& operator=(const Database& other);
	Database& operator=(Database&& other) noexcept;
	~Database();

	void addTable(Table* table);
	void saveToBinaryFile() const;
	void loadFromBinaryFile();
	
	size_t getSize() const;
	const Table& getTable(unsigned index) const;
	void setValue(unsigned tableIndex, OptionalString&& value, unsigned rowIndex, unsigned colIndex);
	void addValue(unsigned tableIndex, unsigned columnIndex, const OptionalString& value);
	void addColumn(unsigned tableIndex, Column* col);
	void removeColumn(unsigned tableIndex, unsigned colIndex);
	void setTableColumnName(unsigned tableIndex, unsigned colIndex, MyString&& newColName);
	void removeRow(unsigned tableIndex, unsigned rowIndex);
	void removeTable(unsigned tableIndex);

	SQLResponse executeQuery(const MyString& query);

private:
	MyString filePath;
	Table** tables = nullptr;
	size_t size = 0; //number of tables in the database
	size_t capacity = 0;


	void copyFrom(const Database& other);
	void moveFrom(Database&& other);
	void free();
	void resize(size_t newCapacity);
};

