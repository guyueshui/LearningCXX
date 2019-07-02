/******************************************************************************
* File:             cxxprimer-ex-15.3.cpp
*
* Author:           yychi  
* Created:          2019-07-02 22:26 
* Description:      Define your "Quote" and "Bulk_Quote".
*****************************************************************************/

#include <string>
#include <iostream>

using std::string;

class Quote {
public:
    Quote() = delete;
    Quote(const string& book, double sales_price):
        book_no_(book), price_(sales_price) { }
    virtual ~Quote() = default;
    std::string isbn() const
    {
        return book_no_;
    }
    virtual double net_price(size_t num_sales) const
    {
        std::cout << __FUNCTION__ << " of base called---> ";
        return num_sales * price_;
    }

private:
    string book_no_;

protected:
    double price_ = 0.0;
};

class BulkQuote : public Quote {
public:
    BulkQuote() = delete;
    BulkQuote(const string& book, 
              double sales_price,
              size_t num_boughts,
              double discnt):
        Quote(book, sales_price),
        min_boughts_(num_boughts),
        discount_(discnt) { }
    double net_price(size_t num_sales) const override
    {
        std::cout << __FUNCTION__ << " of derived called---> ";
        if (num_sales >= min_boughts_)
            return num_sales * (1 - discount_) * price_;
        else
            return num_sales * price_;
    }
private:
    size_t min_boughts_ = 0;
    double discount_ = 0.0;
};

// dynamic binding here, will call "net_price()" of Quote and BulkQuote
// according to runtime type of parameter q.
double print_total(std::ostream& os, const Quote& q, size_t n)
{
    double ret = q.net_price(n);
    os << "ISBN: " << q.isbn() << ", #sold: " << n
        << ", total due: " << ret << std::endl;
    return ret;
}


int main()
{
    Quote q("cxxprimer", 50.0);
    BulkQuote bq("c++primer", 55.0, 10, 0.3);
    print_total(std::cout, q, 23);
    print_total(std::cout, bq, 23);
    return 0;
}
