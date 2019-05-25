#ifndef _SALES_DATA_H_
#define _SALES_DATA_H_

#include <string>
#include <iostream>

class Sales_data {
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

public:
    // constructors
    Sales_data() = default;
    Sales_data(std::string a, unsigned b, double c)
        : bookNo(a), units_sold(b), revenue(c) {}

    // cannot bind const to non-const
    Sales_data(const Sales_data& a) 
        : bookNo(a.bookNo), 
          units_sold(a.units_sold),
          revenue(a.revenue) {}
    
    Sales_data(std::string _bookNo) : Sales_data(_bookNo, 0, 0) {}

    // selectors
    std::string isbn() const { return bookNo; }
    unsigned get_sold() const { return units_sold; }
    double get_revenue() const { return revenue; }

    // modifiers
    Sales_data& set_bookNo(std::string a) {
        bookNo = a;
        return *this;
    }
    Sales_data& set_sold(unsigned a) {
        units_sold = a;
        return *this;
    }
    Sales_data& set_revenue(double a) {
        revenue = a;
        return *this;
    }

    // sum datas for same books
    Sales_data& combine(const Sales_data&);
    double avg_price() const {
        return units_sold? revenue / units_sold
            : 0;
    }
};

//--- non-interface ---//
// add two objects' sales' data
Sales_data add(const Sales_data&, const Sales_data&);
// read bookNo, units_sold, and price from a input stream
std::istream& read(std::istream&, Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);

#endif // _SALES_DATA_H_
