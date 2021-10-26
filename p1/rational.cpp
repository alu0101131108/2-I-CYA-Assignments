#include "rational.hpp"

void rational::WriteConsole(ostream & os)
{
    Simplify();
    if (GetDen() != 1)
        os << GetNum() << " / " << GetDen() << endl;
    else
        os << GetNum() << endl;
}

void rational::Simplify()
{
    int mcd = gcd(num_, den_);
    if (mcd < 0)
        mcd = mcd * -1;
    SetNum(num_ / mcd);
    SetDen(den_ / mcd);
}

void rational::ReadConsole(istream & is)
{
    int num, den;
    cout << "Numerador: " << endl;
    is >> num;
    cout << "Denominador: " << endl;
    is >> den;
    cout << endl;
    assert(den != 0);
    num_ = num;
    den_ = den;
}

int rational::RationalCount(ifstream & tf)
{
    if (tf.is_open()) {
        char c;
        int count = 0;
        while (!tf.eof()) {
            tf >> c;
            if (c == '/')
                count++;
        }
        return count;

    } else {
        cout << "File is not open." << endl;
        return 0;
    }
}

void rational::ReadFile(vector < rational > &ratV, ifstream & tf, int n)
{
    if (tf.is_open()) {
        char c;
        int aux;
        streampos prev;

        ratV.resize(n);

        for (int i = 0; i < n * 2; i++) {
            prev = tf.tellg();
            tf >> c;
            if (c == '/') {
                tf >> aux;      //denominador
                ratV[(i - 1) / 2].SetDen(aux);
            } else              //numerador
            {
                tf.seekg(prev, ios::beg);
                tf >> aux;
                ratV[i / 2].SetNum(aux);
            }
        }

    } else
        cout << "File is not open" << endl;

}

void rational::WriteFile(ofstream & tf)
{
    Simplify();
    if (tf.is_open()) {
        if (GetDen() != 1)
            tf << GetNum() << " / " << GetDen();
        else
            tf << GetNum();
    } else {
        cout << endl << "File is not open." << endl;
    }
}

void rational::Add(const rational & a, const rational & b)
{
    if (a.GetDen() == b.GetDen()) {
        den_ = a.GetDen();
        num_ = a.GetNum() + b.GetNum();
    } else {
        den_ = a.GetDen() * b.GetDen();
        num_ = b.GetNum() * a.GetDen() + a.GetNum() * b.GetDen();
    }
    Simplify();
}

void rational::Sub(const rational & a, const rational & b)
{
    if (a.GetDen() == b.GetDen()) {
        den_ = a.GetDen();
        num_ = a.GetNum() - b.GetNum();
    } else {
        den_ = a.GetDen() * b.GetDen();
        num_ = a.GetNum() * b.GetDen() - b.GetNum() * a.GetDen();
    }
    Simplify();
}

void rational::Multiply(const rational & a, const rational & b)
{
    num_ = a.GetNum() * b.GetNum();
    den_ = a.GetDen() * b.GetDen();
    Simplify();
}

void rational::Divide(const rational & a, const rational & b)
{
    num_ = a.GetNum() * b.GetDen();
    den_ = a.GetDen() * b.GetNum();
    Simplify();
}

bool rational::Operate(rational a, rational b, int op)
{
    bool aux;
    switch (op) {
    case 0:
        Add(a, b);
        break;

    case 1:
        Sub(a, b);
        break;

    case 2:
        Multiply(a, b);
        break;

    case 3:
        Divide(a, b);
        break;

    case 4:
        aux = (bool) (a > b);
        break;

    case 5:
        aux = (bool) (a < b);
        break;

    case 6:
        aux = (bool) (a == b);
        break;

    case 7:
        aux = (bool) (a <= b);
        break;

    case 8:
        aux = (bool) (a >= b);
        break;
    }
    return aux;
}

int rational::Compare(rational a)
{

    if (num_ * a.GetDen() - den_ * a.GetNum() > 0.0)
        return 1;
    else if (num_ * a.GetDen() - den_ * a.GetNum() < 0.0)
        return -1;
    else
        return 0;
}

double rational::Value()
{
    return num_ / den_;
}
