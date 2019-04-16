/*
 * Implemention of class `Sales_data`
 */

#include "Sales_data.h"

Sales_data& Sales_data::combine(const Sales_data& rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream& read(std::istream& is, Sales_data& item) {
    double price = 0.0;
    unsigned sales = 0;
    std::string book;
    
    is >> book >> sales >> price;
//    std::cout << "what i read is: "
//        << book << ' '
//        << sales << ' '
//        << price << std::endl;
    item.set_bookNo(book).
        set_sold(sales).
        set_revenue(sales * price);
    return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item) {
    os << item.isbn() << ' '
        << item.get_sold() << ' '
        << item.get_revenue();
    return os;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs; // invoke copy constructor
    sum.combine(rhs);
    return sum;
}
