#pragma once
#include "Table.h"
#include "MyVector.hpp"
#include "SQLResponse.h"

class Database
{
public:
	Database();
	Database(const MyString& name);
	Database(const Database& other);
	Database(Database&& other) noexcept;
	Database& operator=(const Database& other);
	Database& operator=(Database&& other) noexcept;
	~Database();

	void addTable(Table* table);
	void saveToBinaryFile(const MyString& fileName) const;
	void loadFromBinaryFile(const MyString& fileName);
	
	const MyString& getName() const;
	size_t getSize() const;
	const Table& getTable(unsigned index) const;
	void setValue(unsigned tableIndex, OptionalString&& value, unsigned rowIndex, unsigned colIndex);
	void addValue(unsigned tableIndex, unsigned columnIndex, const OptionalString& value);

	SQLResponse executeQuery(const MyString& query);

private:
	MyString name;
	Table** tables = nullptr;
	size_t size = 0; //number of tables in the database
	size_t capacity = 0;


	void copyFrom(const Database& other);
	void moveFrom(Database&& other);
	void free();
	void resize(size_t newCapacity);
};

