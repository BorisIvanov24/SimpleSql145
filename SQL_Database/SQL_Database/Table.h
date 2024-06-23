#pragma once
#include "Column.h"

class Table
{
public:
	Table() = default;
	Table(const Table& other);
	Table(Table&& other) noexcept;
	Table& operator=(const Table& other);
	Table& operator=(Table&& other) noexcept;
	~Table();

	Table(const MyString& name);
	Table(MyString&& name);

	const MyString& getName() const;
	size_t getColumnsCount() const;
	ColumnType getColumnType(unsigned index) const;
	void addColumn(Column* ptr);
	void removeColumn(unsigned index);
	void removeRow(unsigned index);

	const MyString& getColumnName(unsigned index) const;
	void saveToBinaryFile(const MyString& fileName) const;
	void loadFromBinaryFile(const MyString& fileName);

	const OptionalString& getValue(unsigned rowIndex, unsigned colIndex) const;
	void setValue(OptionalString&& value, unsigned rowIndex, unsigned colIndex);
	void addValue(const OptionalString& value, unsigned columnIndex);
	void setColumnName(unsigned colIndex, MyString&& newColName);

	size_t getRowsCount() const;
	size_t getColsCount() const;

private:
	MyString name;
	Column** columns = nullptr;
	size_t size = 0; //colsCount
	size_t rowsCount = 0;

	void copyFrom(const Table& other);
	void moveFrom(Table&& other);
	void free();
	void resize();

	void fillEmpty();
};

