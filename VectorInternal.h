#ifndef __VECTORINTERNAL_H_INCLUDED__
#define __VECTORINTERNAL_H_INCLUDED__

#include <iostream>

template< class T >
class Vector {
    protected:
        T* array;
    private:
        unsigned int size;
        unsigned int capacity;
    public:
        Vector();
        Vector(unsigned int);
        Vector(unsigned int, const T&);
        Vector(unsigned int, const T*);
        Vector(unsigned int, Vector< T >&);
        Vector(const Vector< T >&);
        virtual ~Vector();
        virtual void Clear();

        Vector< T >& operator=(const Vector< T >&);
        virtual bool operator==(const Vector< T >&) const;
        bool operator!=(const Vector< T >&) const;
        virtual bool operator<(const Vector< T >&) const;

        virtual unsigned int GetSize() const;
        unsigned int GetCapacity() const;
        inline bool IsEmpty() const;
        void Reserve(unsigned int);
        void Resize(unsigned int);
        virtual void Push_back(const T&);
        virtual void Pop_back();

        T& operator[](unsigned int) const;
        virtual Vector< T > operator+(const Vector< T >&) const;
        Vector< T > operator-() const;
        virtual Vector< T > operator-(const Vector< T >&) const;
        Vector< T > operator*(const Vector< T >&) const;
        
        template< class U > friend std::istream& operator>>(std::istream&, Vector< U >&);
        template< class U > friend std::ostream& operator<<(std::ostream&, const Vector< U >&);
};

#endif