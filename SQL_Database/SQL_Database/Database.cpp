#include "Database.h"

Database::Database()
{
	tables = new Table * [8];
	size = 0;
	capacity = 8;
}

Database::Database(const MyString& name) : Database()
{
	this->name = name;
}

Database::Database(const Database& other)
{
	copyFrom(other);
}

Database::Database(Database&& other) noexcept
{
	moveFrom(std::move(other));
}

Database& Database::operator=(const Database& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Database& Database::operator=(Database&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Database::~Database()
{
	free();
}

void Database::addTable(Table* table)
{
	if (size == capacity)
		resize(capacity * 2);

	tables[size++] = table;
}

void Database::saveToBinaryFile(const MyString& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::binary | std::ios::out);

	if (!ofs.is_open())
		throw std::exception("Unable to open file!");

	ofs.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		tables[i]->saveToBinaryFile(ofs);
	}
}

void Database::loadFromBinaryFile(const MyString& fileName)
{
	free();

	std::ifstream ifs(fileName.c_str(), std::ios::binary | std::ios::in);

	if (!ifs.is_open())
		throw std::exception("Unable to open file!");

	ifs.read(reinterpret_cast<char*>(&size), sizeof(size_t));

	if (size != 0)
		tables = new Table* [size];

	for (int i = 0; i < size; i++)
	{
		tables[i] = new Table();

		tables[i]->loadFromBinaryFile(ifs);
	}
}

const MyString& Database::getName() const
{
	return name;
}

size_t Database::getSize() const
{
	return size;
}

const Table& Database::getTable(unsigned index) const
{
	return *(tables[index]);
}

void Database::setValue(unsigned tableIndex, OptionalString&& value, unsigned rowIndex, unsigned colIndex)
{
	tables[tableIndex]->setValue(std::move(value), rowIndex, colIndex);
}

void Database::addValue(unsigned tableIndex, unsigned columnIndex, const OptionalString& value)
{
	tables[tableIndex]->addValue(value, columnIndex);
}

void Database::copyFrom(const Database& other)
{
	tables = new Table * [other.capacity] {nullptr};
	
	for (int i = 0; i < other.size; i++)
	{
		tables[i] = new Table(*(other.tables[i]));
	}

	name = other.name;
	size = other.size;
	capacity = other.capacity;
}

void Database::moveFrom(Database&& other)
{
	tables = other.tables;
	other.tables = nullptr;

	name = std::move(name);
	size = other.size;
	capacity = other.capacity;
}

void Database::free()
{
	for (int i = 0; i < size; i++)
	{
		delete tables[i];
	}

	delete[] tables;
}

void Database::resize(size_t newCapacity)
{
	Table** temp = new Table* [newCapacity];

	for (int i = 0; i < size; i++)
	{
		temp[i] = tables[i];
	}

	delete[] tables;

	tables = temp;
}
