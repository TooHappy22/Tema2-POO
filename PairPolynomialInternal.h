#ifndef __PAIRPOLYNOMIALINTERNAL_H_INCLUDED__
#define __PAIRPOLYNOMIALINTERNAL_H_INCLUDED__

#include <iostream>

template< class T >
class PairPolynomial : public Polynomial< T > {
    private:
        T valueToCalculate;
    public:
        PairPolynomial();
        PairPolynomial(T, const Polynomial< T >&);
        PairPolynomial(const PairPolynomial< T >&);
        ~PairPolynomial();
        void Clear();

        PairPolynomial< T >& operator=(const PairPolynomial< T >&);
        bool operator==(const PairPolynomial< T >&) const;
        bool operator!=(const PairPolynomial< T >&) const;
        bool operator<(const PairPolynomial< T >&) const;

        T GetValueToCalculate();
        bool IsRoot() const;

        template< class U > friend std::istream& operator>>(std::istream&, PairPolynomial< U >&);
        template< class U > friend std::ostream& operator<<(std::ostream&, const PairPolynomial< U >&);
};

#endif
