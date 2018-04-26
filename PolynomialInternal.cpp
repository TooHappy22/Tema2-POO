#include <iostream>
#include <math.h>
#include "PolynomialInternal.h"

template< class T >
Polynomial< T >::Polynomial() : Vector< T >(), degree(-1) {
}

template< class T >
Polynomial< T >::Polynomial(int degree) : Vector< T >(degree + 1), degree(degree) {
}

template< class T >
Polynomial< T >::Polynomial(int degree, Vector< T >& other) : Vector< T >(degree + 1, other), degree(degree) {
}

template< class T >
Polynomial< T >::Polynomial(const Polynomial< T >& other) : Vector< T >(other), degree(other.degree) {
}

template< class T >
Polynomial< T >::~Polynomial() {
    this->Clear();
}

template< class T >
void Polynomial< T >::Clear() {
    this->degree = -1;
    this->Vector< T >::Clear();
}

template< class T >
Polynomial< T >& Polynomial< T >::operator=(const Polynomial< T >& other) {
    if(this == &other) {
        return *this;
    }

    this->Clear();

    this->degree = other.degree;
    (Vector< T >&)*this = (Vector< T >&)other;
    // this->Resize(other.GetSize());

    // for(unsigned int i = 0; i < this->GetSize(); ++i) {
    //     this->array[i] = other.array[i];
    // }
    this->ReducePolynomial();

    return *this;
}

template< class T >
bool Polynomial< T >::operator==(const Polynomial< T >& other) const {
    if(this->degree != other.degree) {
        return false;
    }

    if((Vector< T >&)*this == (Vector< T >&)other) {
        return true;
    } else {
        return false;
    }

    // for(int i = 0; i <= this->degree; ++i) {
    //     if(this->array[i] != other.array[i]) {
    //         return false;
    //     }
    // }

    // return true;
}

template< class T >
bool Polynomial< T >::operator!=(const Polynomial< T >& other) const {
    return (!(*this == other));
}

template< class T >
bool Polynomial< T >::operator<(const Polynomial<T >& other) const {
    return ((Vector< T >&)*this < (Vector< T >&)other);
}

template< class T >
int Polynomial< T >::GetDegree() const {
    return this->degree;
}

template< class T >
unsigned int Polynomial< T >::GetSize() const {
    return this->Vector< T >::GetSize();
}

template< class T >
bool Polynomial< T >::IsNull() const {
    return (this->degree < 0);
}

template< class T >
void Polynomial< T >::ReducePolynomial() {
    int i = this->degree;

    while(i >= 0 && this->array[i] == T()) {
        this->Vector< T >::Pop_back();
        this->degree--;
        i--;
    }
}

template< class T >
T Polynomial< T >::Evaluate(T value) const {
    T result = this->array[0];

    for(int i = 1; i <= this->degree; ++i) {
        result += (pow(value, i) * this->array[i]);
    }

    return result;
}

template< class T >
void Polynomial< T >::Push_back(const T& value) {
    this->degree++;
    this->Vector< T >::Push_back(value);
}

template< class T >
void Polynomial< T >::Pop_back() {
    this->degree--;
    this->Vector< T >::Pop_back();
}

template< class T >
Polynomial< T > Polynomial< T >::operator+(const Polynomial< T >& other) const {
    Vector< T > lhs(this->GetSize(), this->array);
    Vector< T > rhs(other.GetSize(), other.array);

    Vector< T > sum = lhs + rhs;

    Polynomial< T > result(std::max(this->GetDegree(), other.GetDegree()), sum);
    result.ReducePolynomial();

    return result;
}

template< class T >
Polynomial< T >& Polynomial< T >::operator+=(const Polynomial< T >& other) {
    *this = *this + other;

    return *this;
}

template< class T >
Polynomial< T > Polynomial< T >::operator-() const {
    Polynomial< T > result(this->degree);
    (Vector< T >&)result = -(Vector< T >&)(*this);

    return result;
}

template< class T >
Polynomial< T > Polynomial< T >::operator-(const Polynomial< T >& other) const {
    Polynomial< double > result;

    result = *this + (-other);

    result.ReducePolynomial();

    return result;
}

template< class T >
Polynomial< T >& Polynomial< T >::operator-=(const Polynomial< T >& other) {
    *this = *this - other;

    return *this;
}

template< class T >
Polynomial< T > Polynomial< T >::operator*(const Polynomial< T >& other) const {
    Polynomial< T > result(this->degree + other.degree);

    (Vector< T >&)result = (Vector< T >&)(*this) * (Vector< T >&)other;

    result.ReducePolynomial();

    return result;
}

template< class T >
Polynomial< T > Polynomial< T >::operator/(const Polynomial< T >& other) const {
    if(this->degree < other.degree) {
		Polynomial< T > result;
		return result;
	}
	if(other.IsNull()) {
		throw std::invalid_argument("Impartire la polinomul nul! Eroare!\n");
	}

	Polynomial< T > result(this->degree - other.degree);
	Polynomial< T > temp(*this);

	while(temp.degree >= other.degree) {
		result.array[temp.degree - other.degree] = temp.array[temp.degree] / other.array[other.degree];
		Polynomial< T > aux(temp.degree);

		for(int i = 0; i < other.degree + 1; ++i) {
			aux.array[temp.degree - other.degree + i] = result.array[temp.degree - other.degree] * other.array[i];
		}

		temp = temp - aux;
	}
    result.ReducePolynomial();

	return result;
}

template< class T >
Polynomial< T > Polynomial< T >::operator%(const Polynomial< T >& other) const {
    if(other.IsNull()) {
		throw std::invalid_argument("Impartire la polinomul nul! Eroare!\n");
	}
        
    Polynomial< T > reminder = (*this - (*this / other) * other);
    
    return reminder;
}

template< class T >
std::istream& operator>>(std::istream& in, Polynomial< T >& other) {
    other.Clear();

    in >> other.degree;

    for(int i = 0; i <= other.degree; ++i) {
        T value; in >> value;
        other.Vector< T >::Push_back(value);
    }

    other.ReducePolynomial();

    return in;
}

template< class T >
std::ostream& operator<<(std::ostream& out, const Polynomial< T >& other) {
    if(other.degree < 0) {
        out << other.array[0];

        return out;
    }

    bool printedFirst = false;
    if(other.array[other.degree] != T() && other.degree > T()) {
        out << other.array[other.degree] << " * X^" << other.degree;
        printedFirst = true;
    }

    for(int i = other.degree - 1; i > 0; --i) {
        if(other.array[i] > T()) {
            if(printedFirst) {
                out << " + " << other.array[i];
            } else {
                out << other.array[i];
                printedFirst = true;
            }
        } else {
            if(other.array[i] < T()) {
                if(printedFirst) {
                    out << " - " << -other.array[i];
                } else {
                    out << other.array[i];
                    printedFirst = true;
                }
            } else {
                continue;
            }
        }
        out << " * X^" << i;
    }

    if(other.array[0] > T()) {
        if(printedFirst) {
            out << " + " << other.array[0];
        } else {
            out << other.array[0];
        }
    } else {
        if(other.array[0] < T()) {
            if(printedFirst) {
                out << " - " << -other.array[0];
            } else {
                out << other.array[0];
            }
        }
    }

    return out;
}