#include<iostream>
#include<string>

using namespace std;

class Sales_data{
    friend istream &operator>>(istream &is,Sales_data &item);
    public:
        Sales_data()=default;
        Sales_data(string a):bookNo(a){}  //absolutely it's a definition not a declaration,";" is not needed
        Sales_data(string a,unsigned b,double c):bookNo(a),units_sold(b),revenue(c*b){}
        Sales_data(istream& is){is>>*this;}
        /*ostream &operator<<(ostream &os,const Sales_data &item){
            os<<item.isbn()<<" "<<item.units_sold<<" "<<item.revenue<<" "<<item.avg_price();
            return os;
        }*/
        /*istream &operator>>(istream& is,const Sales_data& item){
            double price;
            is>>item.bookNo>>item.units_sold>>price;
            if(is) item.revenue=item.units_sold*price;
            else item=Sales_data();
            return is;
        }*/
        Sales_data& operator+=(Sales_data&);
        string isbn() const {return bookNo;}
        //double avg_price() const;
        int get_unitsolds() const {return units_sold;}
        double get_revenue() const {return revenue;}
        double avg_price() const {return units_sold?revenue/units_sold:0;}
        Sales_data& operator=(Sales_data &item);

    private:
        string bookNo;
        unsigned units_sold=0;
        double revenue=0.0;
};

ostream &operator<<(ostream &os,const Sales_data &item){
    os<<item.isbn()<<" "<<item.get_unitsolds()<<" "<<item.get_revenue();
    return os;
}

istream &operator>>(istream& is,Sales_data& item){
    double price=0;
    is>>item.bookNo>>item.units_sold>>price;
    if(is) item.revenue=item.units_sold*price;
    return is;
}

Sales_data& Sales_data::operator=(Sales_data& item){
    this->bookNo=item.bookNo;
    this->units_sold=item.units_sold;
    this->revenue=item.revenue;
    return *this;
}

void fun(){
    Sales_data total;
    cout<<"please input the sales data:"<<endl;
    if(cin>>total){
        Sales_data trans;
        while(cin>>trans){
            if(total.isbn()==trans.isbn()) total+=trans;
            else{
                cout<<total<<endl;
                total=trans;
            }
        }
        cout<<total<<endl;
    }else cerr<<"No data?!"<<endl;
}

Sales_data& Sales_data::operator+=(Sales_data& item){
    if(this->bookNo==item.isbn()){
        units_sold+=item.units_sold;
        revenue+=item.revenue;
    }else{
        cerr<<"the isbn must match!"<<endl;
    }
    return *this;
}

int main(){
    Sales_data book1("data_structure");
    Sales_data book2("data_structure",5,80);
    Sales_data book3;
    Sales_data book4(cin);
    book1+=book3;
    book2+=book4;
    cout<<book1<<endl;
    cout<<book2<<endl;
    //fun();
    //void (*p)()=fun;     //pointer of function
    return 0;
}
