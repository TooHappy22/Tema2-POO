#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Polynomial.h"
#include "PairPolynomial.h"

using namespace std;

ofstream out("date.out");

int main() {
    ifstream in("dateVector.in");

    out << "Continutul fisierului dateVector.in :\n\n";
    
    int n; in >> n;

    Vector< double > data[n];  
    for(int i = 0; i < n; ++i) {
        in >> data[i];
    }

    for(int i = 0; i < n; ++i) {
        out << "Vectorul #" << i + 1 << " :\n";
        out << data[i];
        out << endl;
    }

    Vector< double > sum;
    for(int i = 0; i < n; ++i) {
        sum = sum + data[i];
    }

    out << "Suma celor " << n << " vectori este:\n";
    out << sum << '\n';

    Vector< double > dif = data[0];
    for(int i = 1; i < n; ++i) {
        dif = dif - data[i];
    }

    out << "Diferenta celor " << n << " vectori este:\n";
    out << dif << '\n';

    Vector< double > mul = data[0] * data[1];

    out << "Produsul primilor 2 vectori:\n";
    out << mul << '\n';

    out << "\n\n";

    in.close();

    out << "Continutul fisierului datePolinom.in :\n\n";
    
    ifstream fin("datePolinom.in");

    int m; fin >> m;
    
    Polynomial< double > polynomials[m];

    for(int i = 0; i < m; ++i) {
        fin >> polynomials[i];
    }

    for(int i = 0; i < m; ++i) {
        out << "Polinomul #" << i + 1 << " :\n";
        out << polynomials[i] << "\n\n";
    }

    Polynomial< double > sumPolynomial;

    for(int i = 0; i < m; ++i) {
        sumPolynomial += polynomials[i];
    }    

    out << "Suma celor " << m << " polinoame este:\n";
    out << sumPolynomial << "\n\n";

    Polynomial< double > difPolynomial = polynomials[0] - polynomials[1];

    out << "Diferenta dintre primul polinom si cel de al doilea polinom este:\n";
    out << difPolynomial << "\n\n";

    Polynomial< double > prodPolynomial = polynomials[2] * polynomials[0];

    out << "Inmultirea primului polinom cu cel de al treilea polinom este:\n";
    out << prodPolynomial << "\n\n";

    Polynomial< double > divisionPolynomial;
    try {
        divisionPolynomial = polynomials[2] / polynomials[0];
        
        out << "Impartirea celui de al 3-a polinom la primul polinom este:\n";
        out << divisionPolynomial << "\n\n";
    } catch(const exception& e) {
        std::cout << e.what() << '\n';
    }

    Polynomial< double > reminderPolynomial;
    try {
        reminderPolynomial = polynomials[2] % polynomials[0];

        out << "Restul impartirii celui de al 3-a polinom la primul polinom este:\n";
        out << reminderPolynomial << "\n\n";
    } catch(const exception& e) {
        std::cout << e.what() << '\n';
    }

    bool test = (polynomials[2] == polynomials[2] / polynomials[0] * polynomials[0] + polynomials[2] % polynomials[0]);

    out << "Rezultatul testului suprem A == A / B * B + A % B este:\n";
    out << test << "\n\n";

    out << "Valoarea primului polinom in valoarea -1 este:\n";
    out << polynomials[0].Evaluate(-1) << "\n\n";

    PairPolynomial< double > pair; fin >> pair;
    out << pair << '\n';

    PairPolynomial< double > pairCopy = pair;
    out << pairCopy << '\n';

    out << "Este " << pair.GetValueToCalculate() << " radacina a polinomului: " << (Polynomial< double >)pair << " ?\n";
    out << (pair.IsRoot() ? "DA\n" : "NU\n");

    PairPolynomial< double > p; fin >> p;
    out << p << '\n';

    p[p.GetDegree()] = -2;
    out << p << '\n';

    out << "Este " << p.GetValueToCalculate() << " radacina a polinomului: " << (Polynomial< double >)p << " ?\n";
    out << (p.IsRoot() ? "DA\n" : "NU\n");

    return 0;
}