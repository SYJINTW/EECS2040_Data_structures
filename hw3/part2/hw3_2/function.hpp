#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>

using namespace std;

class Poly; // predefine
class Term; // predefine

Term *av = NULL;

class Term
{

    friend istream &operator>>(istream &is, Poly &x);
    friend ostream &operator<<(ostream &os, const Poly &x);
    friend Poly operator+(const Poly &b);

public:
    friend class Poly;

private:
    double coef;
    int exp;
    Term *link;
};

class Poly
{
public:
    friend istream &operator>>(istream &is, Poly &x);
    friend ostream &operator<<(ostream &os, const Poly &x);
    Poly operator+(const Poly &b);
    Poly();
    Poly(const Poly &a);
    ~Poly();
    void Insert(double c, int e);

private:
    Term *poly;
};

Poly::Poly()
{
    poly = new Term();
    poly->link = poly;
}

Poly::Poly(const Poly &a)
{
    poly = new Term();
    poly->link = poly;
    Term *now = a.poly->link;
    Term *copyLast = poly;
    while (now != a.poly)
    {
        Term *copyNow = new Term;
        copyNow->coef = now->coef;
        copyNow->exp = now->exp;
        copyNow->link = copyLast->link;
        copyLast->link = copyNow;
        copyLast = copyNow;
        now = now->link;
    }
}

Poly::~Poly()
{
    if (poly->link != poly)
    {
        Term *now = poly->link;
        while (now->link != poly)
        {
            now = now->link;
        }
        av = poly->link;
        poly->link = NULL;
    }
}

istream &
operator>>(istream &is, Poly &x)
{
    Term *now = x.poly;
    Term *tmp = new Term();
    is >> tmp->coef >> tmp->exp;

    // no element in poly
    if (x.poly->link == x.poly)
    {
        x.poly->link = tmp;
        tmp->link = x.poly; // circular
        return is;
    }

    // at least one element in poly
    Term *last = now;
    now = now->link;

    while (now != x.poly && tmp->exp < now->exp)
    {
        last = now;
        now = now->link;
    }

    if (tmp->exp == now->exp)
    {
        now->coef = tmp->coef;
    }
    else
    {
        tmp->link = now;
        last->link = tmp;
    }
    return is;
}

ostream &
operator<<(ostream &os, const Poly &x)
{
    // no element in poly
    if (x.poly == x.poly->link)
    {
        os << "The Poly is empty.\n";
        return os;
    }
    // at least one element
    for (Term *now = x.poly->link; now != x.poly; now = now->link)
    {
        os << now->coef << " X^" << now->exp;
        if (now->link != x.poly)
            cout << " + ";
    }
    return os;
}

void Poly::Insert(double c, int e)
{
    // init new Term
    Term *tmp = new Term();
    tmp->coef = c;
    tmp->exp = e;

    // no element
    if (this->poly == this->poly->link)
    {
        this->poly->link = tmp;
        tmp->link = this->poly;
        return;
    }

    // at least one element
    Term *now = this->poly->link;
    // first one is the same exp
    if (now->exp == e)
    {
        now->coef += c;
        return;
    }

    while (now->link != this->poly && e > now->link->exp)
    {
        now = now->link;
    }

    // the end of the poly
    if (now->link == this->poly)
    {
        tmp->link = now->link;
        now->link = tmp;
    }
    // have the same exp
    else if (now->link->exp == e)
    {
        now->link->coef += c;
    }
    else
    {
        tmp->link = now->link;
        now->link = tmp;
    }
    return;
}

Poly Poly::operator+(const Poly &b)
{
    Poly c(*this);
    Term *now = b.poly->link;
    while (now != b.poly)
    {
        c.Insert(now->coef, now->exp);
        now = now->link;
    }
    return c;
}

#endif // FUNCTION_HPP