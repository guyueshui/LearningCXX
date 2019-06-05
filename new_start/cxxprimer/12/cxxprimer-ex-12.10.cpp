// --- Ex 12.10 ---
shared_ptr<int> p(new int(42)); 
process(shared_ptr<int>(p));    
// 将p初始化为指向int的指针
// 创建临时智能指针并初始化为p，临时对象与p指向同一块内存，函数调用结束，
// 临时对象被销毁，内存被释放，意味着p成为野指针。

shared_ptr<int> p(new int(42));
process(p);
// 直接使用p，因为process通过拷贝传递参数，在函数内部，p的引用计数为2，
// 函数调用结束，拷贝的对象被销毁，p的引用计数变成1，但仍然可以使用。

// --- Ex 12.11 ---
process(shared_ptr<int>(p.get()));
// 将智能指针p的内存绑定给临时智能指针对象，该临时智能指针获得了管理
// 该块内存的权利，函数调用结束，临时对象被销毁，内存被释放。p成为
// 野指针。

// --- Ex 12.12 ---
auto p = new int();
auto sp = make_shared<int>();
(a). process(sp);
(b). process(new int());
(c). process(p);
(d). process(shared_ptr<int>(p));
/*
 * (a). 合法
 * (b). 非法，不能将普通指针转化为智能指针
 * (c). 非法，同上
 * (d). 合法，创建临时智能指针对象，但p的内存会被释放，
 *      函数调用后p成为野指针
 */

// --- Ex 12.13 ---
auto sp = make_shared<int>();
auto p = sp.get();
delete p;
/*
 * 使用get获得智能指针的内存，并将之释放。导致智能指针计数不为0，却成为了
 * 野指针，因为它指向的内存已经被释放。任何试图访问sp的操作都是未定义的。
 */
