#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>

using namespace std;

class Poly; // predefine
class Term; // predefine

Term* av = NULL;

class Term
{
public:
    friend istream &operator>>(istream &is, Poly &x);
    friend ostream &operator<<(ostream &os, const Poly &x);
    friend class Poly;

private:
    double coef;
    int exp;
    Term *link;
};

class Poly
{
public:
    // DONE:
    friend istream &operator>>(istream &is, Poly &x);
    // DONE:
    friend ostream &operator<<(ostream &os, const Poly &x);
    // DONE:
    Poly operator+(const Poly &b);
    // DONE:
    Poly operator-(const Poly &b);
    // DONE:
    Poly operator*(const Poly &b);
    // DONE:
    const Poly &operator=(const Poly& a);
    // DONE:
    Poly();
    // DONE:
    Poly(const Poly &a);
    // DONE:
    ~Poly();
    // DONE:
    void Insert(double c, int e);
    // DONE:
    double Eval(const double x);
    // DONE:
    Term* GetNode();
    // DONE:
    void RetNode(Term* t);

private:
    Term *poly;
};

// DONE:
Term*
Poly::GetNode()
{
    if(av)
    {
        cout << "Reuse av" << endl;
        Term* tmp = av;
        av = av->link;
        return tmp;
    }
    cout << "Empty av" << endl;
    return new Term();
}

// DONE:
void
Poly::RetNode(Term* t)
{
    t->link = av;
    av = t;
}

// DONE:
Poly::Poly()
{
    //poly = new Term(); // header
    poly = GetNode();
    poly->link = poly; // header point to itself
}

// DONE:
Poly::Poly(const Poly &a)
{
    //poly = new Term(); // header
    poly = GetNode(); 
    poly->link = poly; // header point to itself
    
    Term *now = a.poly->link; // the base first element
    Term *copyNow = poly;
    Term *copyLast = poly;

    while (now != a.poly)
    {
        //copyNow = new Term();
        copyNow = GetNode();
        copyNow->coef = now->coef;
        copyNow->exp = now->exp;
        copyNow->link = copyLast->link;
        copyLast->link = copyNow;
        copyLast = copyNow;
        now = now->link;
    }
}

// DONE:
Poly::~Poly()
{
    Term* now = this->poly->link;
    while(now != this->poly)
    {
        Term* tmp = now;
        now = now->link;
        RetNode(tmp);
    }
    delete this->poly;
}

// DONE:
istream &
operator>>(istream &is, Poly &x)
{
    double c;
    int e, num;
    cout << "How many element do you want to add: ";
    is >> num;
    while(num--)
    {
        is >> c >> e;
        x.Insert(c,e);
    }
    return is;
}

// DONE:
ostream &
operator<<(ostream &os, const Poly &x)
{
    // no element in poly
    if (x.poly == x.poly->link)
    {
        os << "The Poly is empty.";
        return os;
    }
    // at least one element
    for (Term *now = x.poly->link; now != x.poly; now = now->link)
    {
        os << now->coef << "X^" << now->exp;
        if (now->link != x.poly)
            cout << " + ";
    }
    return os;
}

// DONE:
// Insert(coef, exp) to this and store in the right place
void Poly::Insert(double c, int e)
{
    // avoid insert 0 coef -> useless
    if(c == 0) return;

    // init new Term
    //Term *tmp = new Term();
    Term *tmp = GetNode();
    tmp->coef = c;
    tmp->exp = e;

    Term* now = this->poly; // now is header
    for(; now->link != this->poly && now->link->exp > e; now = now->link);
    // the exist exp
    if(now->link != this->poly && now->link->exp == e)
    {
        now->link->coef += c;
        //delete tmp;
        RetNode(tmp);
        if(now->link->coef == 0)
        {
            Term* tmp = now->link;
            now->link = now->link->link;
            //delete tmp;
            RetNode(tmp);
        }
        return;
    }
    tmp->link = now->link;
    now->link = tmp;
    return;
}

// DONE:
Poly
Poly::operator+(const Poly &b)
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

// DONE:
Poly
Poly::operator-(const Poly &b)
{
    Poly c(*this);
    Term *now = b.poly->link;
    while (now != b.poly)
    {
        c.Insert((now->coef)*(-1), now->exp);
        now = now->link;
    }
    return c;
}

// DONE:
Poly
Poly::operator*(const Poly &b)
{
    Poly* c = new Poly();
    int co;
    int ex;
    for(Term* i = this->poly->link; i != this->poly; i = i->link)
    {
        for(Term* j = b.poly->link; j != b.poly; j = j->link)
        {
            co = i->coef * j->coef;
            ex = i->exp + j->exp;
            c->Insert(co, ex);
        }
    }
    return *c;
}

// DONE:
const Poly& 
Poly::operator=(const Poly& a)
{
    this->poly = a.poly;
    return *this;
}

// DONE:
double 
Poly::Eval(const double x)
{
    double result = 0;
    for(Term* now = this->poly->link; now != this->poly; now = now->link)
    {
        double tmp = 1;
        // calculate X^exp
        for(int i = 0; i < now->exp; i++)
        {
            tmp *= x;
        }
        result += now->coef * tmp;
    }
    return result;
}

#endif // FUNCTION_HPP