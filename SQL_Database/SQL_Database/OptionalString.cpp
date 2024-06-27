#include "OptionalString.h"
#include <cstring>
#include <algorithm>
#include <fstream>
#include <stdexcept>

#pragma warning(disable : 4996)

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

OptionalString::OptionalString(const char* data)
{
    _size = std::strlen(data);
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data);
}

OptionalString::OptionalString(const MyString& data)
{
    _size = std::strlen(data.c_str());
    _allocatedDataSize = dataToAllocByStringLen(_size);
    _data = new char[_allocatedDataSize];
    std::strcpy(_data, data.c_str());
}

OptionalString::OptionalString(size_t stringLength)
{
    _allocatedDataSize = dataToAllocByStringLen(stringLength);
    _data = new char[_allocatedDataSize];
    _size = 0;
    _data[0] = '\0';
}

OptionalString::OptionalString(const OptionalString& other)
{
    copyFrom(other);
}

OptionalString::OptionalString(OptionalString&& other) noexcept
{
    moveFrom(std::move(other));
}

void OptionalString::moveFrom(OptionalString&& other)
{
    _data = other._data;
    other._data = nullptr;

    _size = other._size;
    other._size = 0;

    _allocatedDataSize = other._allocatedDataSize;
    other._allocatedDataSize = 0;
}

OptionalString& OptionalString::operator=(const OptionalString& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

OptionalString& OptionalString::operator=(OptionalString&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

OptionalString::~OptionalString()
{
    free();
}

bool OptionalString::hasValue() const
{
    return (_data != nullptr);
}

size_t OptionalString::getCapacity() const
{
    return _allocatedDataSize - 1;
}

size_t OptionalString::getSize() const
{
    return _size;
}

void OptionalString::clear()
{
    if (_data) {
        _data[0] = '\0';
        _size = 0;
    }
}

void OptionalString::saveToBinaryFile(std::ofstream& ofs) const
{
    ofs.write(reinterpret_cast<const char*>(&_size), sizeof(size_t));
    if (_size != 0) {
        ofs.write(reinterpret_cast<const char*>(_data), _size * sizeof(char));
    }
}

void OptionalString::loadFromBinaryFile(std::ifstream& ifs)
{
    free();
    ifs.read(reinterpret_cast<char*>(&_size), sizeof(size_t));
    if (_size != 0) {
        _allocatedDataSize = dataToAllocByStringLen(_size);
        _data = new char[_allocatedDataSize];
        _data[_size] = '\0';
        ifs.read(_data, _size * sizeof(char));
    }
}

const char* OptionalString::c_str() const
{
    return _data;
}

OptionalString& OptionalString::operator+=(const OptionalString& other)
{
    if (getSize() + other.getSize() + 1 > _allocatedDataSize) {
        resize(dataToAllocByStringLen(getSize() + other.getSize()));
    }

    std::strncat(_data, other._data, other.getSize());
    _size = getSize() + other.getSize();
    return *this;
}

OptionalString& OptionalString::operator+=(char ch)
{
    if (_size + 1 >= _allocatedDataSize) {
        resize(_allocatedDataSize ? 2 * _allocatedDataSize : 8);
    }
    _data[_size++] = ch;
    _data[_size] = '\0';
    return *this;
}

char& OptionalString::operator[](size_t index)
{
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

const char& OptionalString::operator[](size_t index) const
{
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

std::ostream& operator<<(std::ostream& os, const OptionalString& obj)
{
    return os << obj._data;
}

std::istream& operator>>(std::istream& is, OptionalString& ref)
{
    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity()) {
        ref.resize(dataToAllocByStringLen(buffStringSize));
    }

    std::strcpy(ref._data, buff);
    ref._size = buffStringSize;
    return is;
}

void OptionalString::resize(unsigned newAllocatedDataSize)
{
    char* newData = new char[newAllocatedDataSize];
    if (_data != nullptr) {
        std::strcpy(newData, _data);
        delete[] _data;
    }
    _data = newData;
    _allocatedDataSize = newAllocatedDataSize;
}

void OptionalString::free()
{
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _allocatedDataSize = 0;
}

void OptionalString::copyFrom(const OptionalString& other)
{
    _allocatedDataSize = other._allocatedDataSize;
    if (other._data == nullptr) {
        _data = nullptr;
        _size = 0;
    }
    else {
        _data = new char[_allocatedDataSize];
        std::strcpy(_data, other._data);
        _size = other._size;
    }
}

OptionalString operator+(const OptionalString& lhs, const OptionalString& rhs)
{
    OptionalString result(lhs.getSize() + rhs.getSize());
    result += lhs;
    result += rhs;
    return result;
}

bool operator==(const OptionalString& lhs, const OptionalString& rhs)
{
    if (!lhs.hasValue() && !rhs.hasValue())
        return true;

    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const OptionalString& lhs, const OptionalString& rhs)
{
    if ((!lhs.hasValue() && rhs.hasValue()) || (lhs.hasValue() && !rhs.hasValue()))
        return true;

    if (!lhs.hasValue() && !rhs.hasValue())
        return false;

    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const OptionalString& lhs, const OptionalString& rhs)
{
    if ((!lhs.hasValue() && rhs.hasValue()) || (lhs.hasValue() && !rhs.hasValue()))
        return false;

    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const OptionalString& lhs, const OptionalString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const OptionalString& lhs, const OptionalString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const OptionalString& lhs, const OptionalString& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}