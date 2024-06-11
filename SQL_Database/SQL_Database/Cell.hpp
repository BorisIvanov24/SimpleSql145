#pragma once

template<class T>
class Cell
{
public:
	Cell() = default;
	Cell(T* value);
	Cell(const Cell<T>& other);
	Cell(Cell<T>&& other) noexcept;
	Cell<T>& operator=(const Cell<T>& other);
	Cell<T>& operator=(Cell<T>&& other) noexcept;
	~Cell();

	const T& getValue() const;
	bool isNull() const;
	void setValue(T* value);
	void setValue(const T& value);

private:
	T* value = nullptr;

	void copyFrom(const Cell<T>& other);
	void moveFrom(Cell<T>&& other);
	void free();
};

template<class T>
void Cell<T>::copyFrom(const Cell<T>& other)
{
	value = new T(*(other.value));
}

template<class T>
void Cell<T>::moveFrom(Cell<T>&& other)
{
	value = other.value;
	other.value = nullptr;
}

template<class T>
void Cell<T>::free()
{
	delete value;
}

template<class T>
Cell<T>::Cell(T* value) : value(value)
{
}

template<class T>
Cell<T>::Cell(const Cell<T>& other)
{
		copyFrom(other);
}

template<class T>
Cell<T>& Cell<T>::operator=(const Cell<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
Cell<T>::Cell(Cell<T>&& other) noexcept
{
	moveFrom(other);
}

template<class T>
Cell<T>& Cell<T>::operator=(Cell<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(other);
	}

	return *this;
}

template<class T>
Cell<T>::~Cell()
{
	free();
}

template<class T>
const T& Cell<T>::getValue() const
{
	return *value;
}

template<class T>
bool Cell<T>::isNull() const
{
	return (value == nullptr);
}

template<class T>
void Cell<T>::setValue(T* value)
{
	free();
	this->value = value;
}

template<class T>
void Cell<T>::setValue(const T& value)
{
	free();
	this->value = new T(value);
}