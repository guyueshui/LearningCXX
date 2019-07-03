/******************************************************************************
* File:             cxxprimer-ex-15.6.cpp
*
* Author:           yychi  
* Created:          2019-07-03 21:23 
*                   Check the correctness of "print_total".
*****************************************************************************/

#include <string>
#include <iostream>

using std::string;

class Quote {
public:
    Quote() = delete;
    Quote(const string& book, double price):
        book_no_(book), price_(price) { }
    string isbn() const { return book_no_; }
    virtual double net_price(size_t n) const
    {
        return n * price_;
    }
    virtual ~Quote() = default;

private:
    string book_no_;

protected:
    double price_ = 0.0;
};

class BulkQuote : public Quote {
public:
    BulkQuote() = delete;
    BulkQuote(const string& book,
              double price,
              size_t num_boughts,
              double discount):
        Quote(book, price),
        min_bouhgts_(num_boughts),
        discount_(discount) { }
    virtual double net_price(size_t n) const override
    {
        if (n >= min_bouhgts_)
            return n * price_ * (1 - discount_);
        else
            return n * price_;
    }
private:
    size_t min_bouhgts_ = 0;
    double discount_ = 0.0;
    
};

void print_total(std::ostream& os, const Quote& q, size_t n)
{
    double ret = q.net_price(n);
    os << "ISBN: " << q.isbn() << ", #sold: " << n
        << ", total due: " << ret << std::endl;
}

// test
int main()
{
    Quote q("cxxprimer", 50.0);
    BulkQuote bq("cxxprimer", 55.0, 10, 0.3);
    print_total(std::cout, q, 23);
    print_total(std::cout, bq, 23);
    return 0;
}
