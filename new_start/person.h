#ifndef _PERSON_H_
#define _PERSON_H_
#include<iostream>
#include<string>

class Person{
    friend std::istream& operator>>(std::istream&,Person&);
    private:
        std::string name;
        std::string address;

    public:
        Person()=default;
        Person(std::istream &is){is>>*this;}
        Person(std::string n,std::string a):name(n),address(a){}
        std::string get_name() const {return name;}
        std::string get_addr() const {return address;}
};

std::ostream& operator<<(std::ostream& os,const Person& one){
    std::cout<<one.get_name()<<" "<<one.get_addr();
    return os;
}

std::istream& operator>>(std::istream& is,Person& one){
    std::cin>>one.name>>one.address;
    return is;
}

#endif
