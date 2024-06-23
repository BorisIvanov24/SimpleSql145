#pragma once
#include "OptionalString.h"
#include "MyVector.hpp"
#include "MyString.h"

enum class ColumnType
{
	NONE,
	INTEGER,
	REAL,
	TEXT
};

class Column
{
public:
	Column() = default;
	Column(const MyString& name, ColumnType type);
	Column(MyString&& name, ColumnType type);

	void setValue(const OptionalString& value, unsigned index);
	void setValue(OptionalString&& value, unsigned index);

	void addNullValue();
	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);
	const MyString& getName() const;
	void addValue(const OptionalString& value);
	void removeValue(unsigned index);

	const OptionalString& getValue(unsigned index);
	ColumnType getColumnType() const;
	size_t getSize() const;
	void setName(MyString&& newName);

private:
	ColumnType type = ColumnType::NONE;
	MyString name;
	MyVector<OptionalString> values;

};

