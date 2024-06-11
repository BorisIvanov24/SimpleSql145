#pragma once
#include <fstream>

template <typename T>
class MyVector
{
public:
	MyVector();
	MyVector(const MyVector<T>&);
	MyVector<T>& operator=(const MyVector<T>&);
	MyVector(MyVector<T>&&) noexcept;
	MyVector<T>& operator=(MyVector<T>&&) noexcept;
	~MyVector();

	void pushBack(const T& toAdd);
	void pushBack(T&&);
	void popBack();
	void insert(const T& str, unsigned index);
	void insert(T&& str, unsigned index);
	void erase(unsigned index);
	bool empty() const;

	const T& operator[](size_t) const;
	T& operator[](size_t);
	size_t getSize() const;
	friend std::ostream& operator<<(std::ostream&, const MyVector<T>&);

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void free();
	void copyFrom(const MyVector&);
	void moveFrom(MyVector<T>&&);
	void resize(size_t newCap);
};

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

template <typename T>
MyVector<T>::MyVector()
{
	data = new T[capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
MyVector<T>::~MyVector()
{
	free();
}

template <typename T>
void MyVector<T>::pushBack(const T& toAdd)
{

	if (size == capacity)
		resize(roundToPowerOfTwo(size + 1));

	size++;
	data[size - 1] = toAdd;
}

template <typename T>
void MyVector<T>::pushBack(T&& other)
{
	if (size == capacity)
		resize(roundToPowerOfTwo(size + 1));

	size++;
	data[size - 1] = std::move(other);
}

template <typename T>
void MyVector<T>::popBack()
{
	size--;
}

template <typename T>
void MyVector<T>::insert(const T& str, unsigned index)
{
	if (index >= size)
		throw std::invalid_argument("Out of bounds");

	if (size == capacity)
		resize(roundToPowerOfTwo(size + 1));

	size++;

	for (int i = size - 2; i >= index; i--)
	{
		data[i + 1] = data[i];
	}

	data[index] = str;
}

template <typename T>
void MyVector<T>::insert(T&& str, unsigned index)
{
	if (index >= size)
		throw std::invalid_argument("Out of bounds");

	if (size == capacity)
		resize(roundToPowerOfTwo(size + 1));

	for (int i = size - 1; i >= index; i--)
	{
		data[i + 1] = std::move(data[i]);
	}
	size++;

	data[index] = str;
}

template <typename T>
void MyVector<T>::erase(unsigned index)
{
	if (index >= size)
		throw std::invalid_argument("Out of bounds");

	for (unsigned i = index; i < size; i++)
	{
		data[i + 1] = data[i];
	}
	size--;
}

template <typename T>
void MyVector<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 0;
	data = nullptr;
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	data = other.data;
	other.data = nullptr;
	size = other.size;
	other.size = 0;
	capacity = other.capacity;
	other.capacity = 0;
}

template <typename T>
void MyVector<T>::resize(size_t newCapacity)
{
	T* temp = new T[newCapacity];
	for (int i = 0; i < this->size; i++)
	{
		temp[i] = std::move(this->data[i]);
	}
	delete[] data;
	capacity = newCapacity;
	data = temp;
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
T& MyVector<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
bool MyVector<T>::empty() const
{
	return (size == 0);
}

template <typename T>
size_t MyVector<T>::getSize() const
{
	return size;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>&)
{
	for (int i = 0; i < MyVector<T>.size; i++)
	{
		out << MyVector<T>.data[i] << " ";
	}
	return out;
}

