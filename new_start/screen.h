#include<iostream>
#include<string>
#include"window_mgr.h"

class Screen{
    //friend std::ostream& operator<<(std::ostream&,Screen&);
    friend void Window_mgr::clear(ScreenIndex);
    public:
        using pos=std::string::size_type;
        Screen()=default;
        Screen(pos ht,pos wd):height(ht),width(wd),contents(ht*wd,' '){};
        Screen(pos ht,pos wd,char c):height(ht),width(wd),contents(ht*wd,c){}
        char get() const {return contents[cursor];}
        inline char get(pos ht,pos wd) const {return contents[ht*width+wd];}
        Screen& move(pos r,pos c);
        Screen& set(char);
        Screen& set(pos,pos,char);
        //分两次重载display函数，做到了返回值不同，
        //区分常对象和非常量对象，统一调用底层的do_display函数
        //这样常量对象可以调用常量版本display
        //非常两对象可以调用非常量版本display，
        //同时返回非常量引用，可以继续调用其他成员函数如set
        const Screen& display(std::ostream& os) const {
            std::cout<<"const display called!"<<std::endl;
            do_display(os);
            return *this;
        }
        Screen& display(std::ostream& os){
            std::cout<<"non-const display called!"<<std::endl;
            do_display(os);
            return *this;
        }

    private:
        void do_display(std::ostream&) const;
        //含有类内初始值
        pos cursor=0;
        pos height=0,width=0;
        std::string contents;

};

Screen& Screen::move(pos r,pos c){
    pos row=r*width;
    cursor=row+c;
    return *this;
}

inline Screen& Screen::set(char c){
    contents[cursor]=c;
    return *this;
}


inline Screen& Screen::set(pos r,pos col,char ch){
    contents[r*width+col]=ch;
    return *this;
}

void Screen::do_display(std::ostream& os) const {
    for(std::string::size_type i=0;i<height;++i){
        for(std::string::size_type j=0;j<width;++j){
            os<<contents[i*width+j];
        }
        os<<std::endl;
    }
}
