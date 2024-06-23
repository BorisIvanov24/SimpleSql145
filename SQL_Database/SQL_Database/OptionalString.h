#pragma once
#include <iostream>
#include "MyString.h"

class OptionalString {

public:
    OptionalString() = default;
    OptionalString(const char* data);
    OptionalString(const MyString& data);

    OptionalString(const OptionalString& other);
    OptionalString(OptionalString&& other) noexcept;

    OptionalString& operator=(const OptionalString& other);

    OptionalString& operator=(OptionalString&& other) noexcept;
    ~OptionalString();

    bool hasValue() const;
    size_t getCapacity() const;
    size_t getSize() const;
    void clear();

    void saveToBinaryFile(std::ofstream& ofs) const;
    void loadFromBinaryFile(std::ifstream& ifs);

    const char* c_str() const;

    OptionalString& operator+=(const OptionalString& other);
    OptionalString& operator+=(char ch);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const OptionalString& obj);
    friend std::istream& operator>>(std::istream& is, OptionalString& ref);
    friend OptionalString operator+(const OptionalString& lhs, const OptionalString& rhs);
private:
    explicit OptionalString(size_t stringLength);
    void resize(unsigned newAllocatedDataSize);

    void free();
    void copyFrom(const OptionalString& other);

    void moveFrom(OptionalString&& other);

    char* _data = nullptr;
    size_t _size = 0;
    size_t _allocatedDataSize = 0;

};