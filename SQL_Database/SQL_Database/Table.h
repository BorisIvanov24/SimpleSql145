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
	void addColumn(Column* ptr);
	void removeColumn(unsigned index);

	void saveToBinaryFile(std::ofstream& ofs) const;
	void loadFromBinaryFile(std::ifstream& ifs);

	const OptionalString& getValue(unsigned rowIndex, unsigned colIndex) const;
	void setValue(const OptionalString& value, unsigned rowIndex, unsigned colIndex);

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
