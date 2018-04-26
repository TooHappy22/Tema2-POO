#ifndef __POLYNOMIALINTERNAL_H_INCLUDED__
#define __POLYNOMIALINTERNAL_H_INCLUDED__

#include <iostream>

template< class T >
class Polynomial : public Vector< T > {
    private:
        int degree;
    public:
        Polynomial();
        Polynomial(int);
        Polynomial(int, Vector< T >&);
        Polynomial(const Polynomial< T >&);
        virtual ~Polynomial();
        virtual void Clear();

        Polynomial< T >& operator=(const Polynomial< T >&);
        bool operator==(const Polynomial< T >&) const;
        bool operator!=(const Polynomial< T >&) const;
        bool operator<(const Polynomial< T >&) const;

        int GetDegree() const;
        unsigned int GetSize() const;
        bool IsNull() const;
        void ReducePolynomial();
        T Evaluate(T) const;
        void Push_back(const T&);
        void Pop_back();

        Polynomial< T > operator+(const Polynomial< T >&) const;
        Polynomial< T >& operator+=(const Polynomial< T >&);
        Polynomial< T > operator-() const;
        Polynomial< T > operator-(const Polynomial< T >&) const;
        Polynomial< T >& operator-=(const Polynomial< T >&);
        Polynomial< T > operator*(const Polynomial< T >&) const;
        Polynomial< T > operator/(const Polynomial< T >&) const;
        Polynomial< T > operator%(const Polynomial< T >&) const;

        template< class U > friend std::istream& operator>>(std::istream&, Polynomial< U >&);
        template< class U > friend std::ostream& operator<<(std::ostream&, const Polynomial< U >&);
};

#endif