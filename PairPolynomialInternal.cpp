#include <iostream>
#include "PairPolynomialInternal.h"

template< class T >
PairPolynomial< T >::PairPolynomial() : Polynomial< T >(), valueToCalculate((T)-1) {
}

template< class T >
PairPolynomial< T >::PairPolynomial(T value, const Polynomial< T >& other) : Polynomial< T >(other), valueToCalculate(value) {
}

template< class T >
PairPolynomial< T >::PairPolynomial(const PairPolynomial< T >& other) : Polynomial< T >(other), valueToCalculate(other.valueToCalculate) {
}

template< class T >
PairPolynomial< T >::~PairPolynomial() {
    this->Clear();
}

template< class T >
void PairPolynomial< T >::Clear() {
    this->valueToCalculate = (T)-1;
    this->Polynomial< T >::Clear();
}

template< class T >
PairPolynomial< T >& PairPolynomial< T >::operator=(const PairPolynomial< T >& other) {
    if(this == &other) {
        return *this;
    }

    this->Clear();

    this->valueToCalculate = other.valueToCalculate;
    (Polynomial< T >&)*this = (Polynomial< T >&)other;

    return *this;
}

template< class T >
bool PairPolynomial< T >::operator==(const PairPolynomial< T >& other) const {
    if((Polynomial< T >&)*this != (Polynomial< T >&)other) {
        return false;
    }

    return (this->valueToCalculate == other.valueToCalculate);
}

template< class T >
bool PairPolynomial< T >::operator!=(const PairPolynomial< T >& other) const {
    return (!(*this == other));
}

template< class T >
bool PairPolynomial< T >::operator<(const PairPolynomial< T >& other) const {
    if((Polynomial< T >&)*this == (Polynomial< T >&)other) {
        return (this->valueToCalculate < other.valueToCalculate);
    }

    return ((Polynomial< T >&)*this < (Polynomial< T >&)other);
}

template< class T >
T PairPolynomial< T >::GetValueToCalculate() {
    return this->valueToCalculate;
}

template< class T >
bool PairPolynomial< T >::IsRoot() const {
    return (this->Evaluate(this->valueToCalculate) == 0);
}

template< class T >
std::istream& operator>>(std::istream& in, PairPolynomial< T >& other) {
    other.Clear();

    in >> other.valueToCalculate;
    in >> (Polynomial< T >&)other;

    return in;
}

template< class T >
std::ostream& operator<<(std::ostream& out, const PairPolynomial< T >& other) {
    out << "Polinomul este: " << (Polynomial< T >&)other << '\n';
    out << "Valoarea pe care o verificam daca e radacina este: " << other.valueToCalculate << '\n';

    return out;
}