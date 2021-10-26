#include <iostream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

class rational {
 private:
    int num_, den_;

    int gcd(int a, int b) const //A. Euclides; máximo común divisor.
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    public:
    rational():num_(0), den_(1)        //Constructor por defecto.
    {}
    rational(int num, int den):num_(num), den_(den)   //Constructor parametrizado.
    {
        assert(den != 0);
    }

//Getters y setters.
    int GetNum() const {
        return num_;
    } int GetDen() const {
        return den_;
    } void SetNum(const int num) {
        num_ = num;
    }

    void SetDen(const int den) {
        assert(den != 0);
        den_ = den;
    }

//Funciones principales de la clase.
    void ReadConsole(istream & is = cin);
    void WriteConsole(ostream & os = cout);
    void ReadFile(vector < rational > &ratV, ifstream & tf, int n);
    void WriteFile(ofstream & tf);
    void Add(const rational & a, const rational & b);
    void Sub(const rational & a, const rational & b);
    void Multiply(const rational & a, const rational & b);
    void Divide(const rational & a, const rational & b);
    void Simplify();
    bool Operate(rational a, rational b, int op);
    int Compare(rational a);
    int RationalCount(ifstream & textfileI);
    double Value();

//Sobrecarga de operadores.
    bool operator>(const rational & a) {
        if (Compare(a) == 1)
            return true;
        else
            return false;
    }

    bool operator<(const rational & a) {
        if (Compare(a) == -1)
            return true;
        else
            return false;
    }

    bool operator==(const rational & a) {
        if (Compare(a) == 0)
            return true;
        else
            return false;
    }

    bool operator>=(const rational & a) {
        if (Compare(a) == 1 || Compare(a) == 0)
            return true;
        else
            return false;
    }

    bool operator<=(const rational & a) {
        if (Compare(a) == -1 || Compare(a) == 0)
            return true;
        else
            return false;
    }
};
