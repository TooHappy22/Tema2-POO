#include <iostream>
#include "VectorInternal.h"

const unsigned int defaultVectorSize = 1;

template< class T >
Vector< T >::Vector() : array(new T[defaultVectorSize]), size(0), capacity(defaultVectorSize) {
    this->array[0] = T();
}

template< class T >
Vector< T >::Vector(unsigned int size) : array(new T[size]), size(size), capacity(size) {
    for(unsigned int i = 0; i < this->size; ++i) {
        this->array[i] = T();
    }
}

template< class T >
Vector< T >::Vector(unsigned int size, const T& value) : array(new T[size]), size(size), capacity(size) {
    for(unsigned int i = 0; i < this->size; ++i) {
        this->array[i] = value;
    }
}

template< class T >
Vector< T >::Vector(unsigned int size, const T* myArray) : array(new T[size]), size(size), capacity(size) {
    for(unsigned int i = 0; i < this->size; ++i) {
        this->array[i] = myArray[i];
    }
}

template< class T >
Vector< T >::Vector(unsigned int size, Vector< T >& myVector) : array(new T[size]), size(size), capacity(size) {
    for(unsigned int i = 0; i < this->size; ++i) {
        this->array[i] = myVector[i];
    }
}

template< class T >
Vector< T >::Vector(const Vector< T >& other) : size(other.size), capacity(other.capacity) {
    this->array = new T[this->size];

    for(unsigned int i = 0; i < this->size; ++i) {
        this->array[i] = other.array[i];
    }
}

template< class T >
Vector< T >::~Vector() {
    this->Clear();
}

template< class T >
void Vector< T >::Clear() {
    this->size = 0;
    this->capacity = defaultVectorSize;
    delete[] this->array;
    this->array = new T[defaultVectorSize];
}

template< class T >
Vector< T >& Vector< T >::operator=(const Vector< T >& other) {
    delete[] this->array;

    this->size = other.size;
    this->capacity = other.capacity;
    this->array = new T[this->size];

    for(unsigned int i = 0; i < this->size; ++i) {
        this->array[i] = other.array[i];
    }

    return *this;
}

template< class T >
bool Vector< T >::operator==(const Vector< T >& other) const {
    if(this->size != other.size) {
        return false;
    }

    for(unsigned int i = 0; i < this->size; ++i) {
        if(this->array[i] != other.array[i]) {
            return false;
        }
    }

    return true;
}

template< class T >
bool Vector< T >::operator!=(const Vector< T >& other) const {
    return (!(*this == other));
}

template< class T >
bool Vector< T >::operator<(const Vector< T >& other) const {
    if(this->size < other.size) {
        return true;
    }
    if(this->size > other.size) {
        return false;
    }

    for(unsigned int i = 0; i < std::min(this->size, other.size); ++i) {
        if(this->array[i] == other.array[i]) {
            continue;
        }

        if(this->array[i] < other.array[i]) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

template< class T >
unsigned int Vector< T >::GetSize() const {
    return this->size;
}

template< class T >
unsigned int Vector< T >::GetCapacity() const {
    return this->capacity;
}

template< class T >
inline bool Vector< T >::IsEmpty() const {
    return (this->size == 0);
}

template< class T >
void Vector< T >::Reserve(unsigned int newCapacity) {
    T* newArray = new T[newCapacity];

    for(unsigned int i = 0; i < this->size; ++i) {
        newArray[i] = this->array[i];
    }

    delete[] this->array;
    this->capacity = newCapacity;
    this->array = newArray;
}

template< class T >
void Vector< T >::Resize(unsigned int newSize) {
    this->Reserve(newSize);
    this->size = newSize;
}

template< class T >
void Vector< T >::Push_back(const T& value) {
    if(this->size == this->capacity) {
        this->Reserve(2 * this->size);
    }

    this->array[this->size++] = value;
}

template< class T >
void Vector< T >::Pop_back() {
    if(!this->IsEmpty()) {
        this->size--;
    }
}

template< class T >
T& Vector< T >::operator[](unsigned int index) const {
    if(index < 0 || index >= this->size) {
        throw std::invalid_argument("Pozitie invalida! In afara vectorului!\n");
    }
    
    return this->array[index];
}

template< class T >
Vector< T > Vector< T >::operator+(const Vector< T >& other) const {
    Vector< T > result(std::max(this->size, other.size));

    for(unsigned int i = 0; i < result.size; ++i) {
        if(i < this->size) {
            result.array[i] += this->array[i];
        }
        if(i < other.size) {
            result.array[i] += other.array[i];
        }
    }

    return result;
}

template< class T >
Vector< T > Vector< T >::operator-() const {
    Vector< T > result(*this);

    for(unsigned int i = 0; i < result.size; ++i) {
        if(result.array[i] == 0) {
            continue;
        }

        result.array[i] *= -1;
    }

    return result;
}

template< class T >
Vector< T > Vector< T >::operator-(const Vector< T >& other) const {
    return *this + (-other);
}

template< class T >
Vector< T > Vector< T >::operator*(const Vector< T >& other) const {
    Vector< T > result(this->size + other.size);

    for(unsigned int i = 0; i < this->size; ++i) {
        for(unsigned int j = 0; j < other.size; ++j) {
            result.array[i + j] += (this->array[i] * other.array[j]);
        }
    }

    unsigned int i = result.size - 1;
    while(i >= 0 && result.array[i] == T()) {
        result.Pop_back();
        --i;
    }

    return result;
}

template< class T >
std::istream& operator>>(std::istream& in, Vector< T >& other) {
    other.Clear();

    unsigned int n; in >> n;

    // other.array = new T[other.size];
    // for(unsigned int i = 0; i < other.size; ++i) {
    //     in >> other.array[i];
    // }
    
    for(unsigned int i = 0; i < n; ++i) {
        T value; in >> value;
        other.Push_back(value);
    }

    return in;
}

template< class T >
std::ostream& operator<<(std::ostream& out, const Vector< T >& other) {
    // out << "Size: " << other.size << '\n';

    out << "Elements: ";
    for(unsigned int i = 0; i < other.size; ++i) {
        out << other.array[i] << " ";
    }
    out << '\n';

    return out;
}