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

class DiscQuote : public Quote {
public:
    DiscQuote() = delete;
    DiscQuote(const string& book, 
              double price,
              size_t min_boughts,
              double discount):
        Quote(book, price),
        min_boughts_(min_boughts),
        discount_(discount) { }
    virtual ~DiscQuote() = default;
    virtual double net_price(size_t num_sales) const = 0;

protected:
    size_t min_boughts_;
    double discount_;
};


int main()
{
    DiscQuote dq("cxxprimer", 55.5, 10, 0.3);
    return 0;
}

/* the compiler complains: */
/*
cxxprimer-ex-15.17.cpp: 在函数‘int main()’中:
cxxprimer-ex-15.17.cpp:58:15: 错误：不能将变量‘dq’声明为具有抽象类型‘DiscQuote’
   58 |     DiscQuote dq("cxxprimer", 55.5, 10, 0.3);
      |               ^~
cxxprimer-ex-15.17.cpp:37:7: 附注：因为下列虚函数在‘DiscQuote’中为纯虚函数：
   37 | class DiscQuote : public Quote {
      |       ^~~~~~~~~
cxxprimer-ex-15.17.cpp:48:20: 附注：    ‘virtual double DiscQuote::net_price(size_t) const’
   48 |     virtual double net_price(size_t num_sales) const = 0;
      |                    ^~~~~~~~~
*/
