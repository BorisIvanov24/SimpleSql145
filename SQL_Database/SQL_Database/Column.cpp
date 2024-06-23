#include "Column.h"

Column::Column(const MyString& name, ColumnType type)
{
	this->name = name;
	this->type = type;
}

Column::Column(MyString&& name, ColumnType type)
{
	this->name = std::move(name);
	this->type = type;
}

void Column::setValue(const OptionalString& value, unsigned index)
{
	while (values.getSize() < index + 1)
	{
		values.pushBack(OptionalString());
	}

	values.setValue(value, index);
}

void Column::setValue(OptionalString&& value, unsigned index)
{
	while (values.getSize() < index + 1)
	{
		values.pushBack(OptionalString());
	}

	values.setValue(std::move(value), index);
}

void Column::addNullValue()
{
	values.pushBack(OptionalString());
}

void Column::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&type), sizeof(ColumnType));
	name.saveToBinaryFile(ofs);
	values.saveToBinaryFile(ofs);
}

void Column::loadFromBinaryFile(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&type), sizeof(ColumnType));
	name.loadFromBinaryFile(ifs);
	values.loadFromBinaryFile(ifs);
}

const MyString& Column::getName() const
{
	return name;
}

void Column::addValue(const OptionalString& value)
{
	values.pushBack(value);
}

void Column::removeValue(unsigned index)
{
	values.erase(index);
}

const OptionalString& Column::getValue(unsigned index)
{
	if (index > getSize())
		throw std::invalid_argument("Out of bounds!");

	return values[index];
}

ColumnType Column::getColumnType() const
{
	return type;
}

size_t Column::getSize() const
{
	return values.getSize();
}

void Column::setName(MyString&& newName)
{
	this->name = std::move(newName);
}
