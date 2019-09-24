// This file implements a demo for simple factory pattern.
//
#include <cstdio>
#include <string>

#define PRINT_NAME printf("%s\n", __FUNCTION__)

using namespace std;

class Product // abstract product
{
public:
  virtual ~Product() { PRINT_NAME; }
public:
  virtual void Operation() = 0;
};

class ProductA : public Product // concrete product
{
public:
  ~ProductA() { PRINT_NAME; }
public:
  void Operation() override { printf("%s\n", "A::Operation()"); }
};

class ProductB : public Product // concrete product
{
public:
  ~ProductB() { PRINT_NAME; }
public:
  void Operation() override { printf("%s\n", "B::Operation()"); }
};

class Factory // factory
{
public:
  ~Factory() { PRINT_NAME; }
public:
  static Product* CreateProduct(const string& name)
  {
    if (name == "A")
      return new ProductA();
    else if (name == "B")
      return new ProductB;
    else
      return nullptr;
  }
};

///
int main()
{
  Product* pa = Factory::CreateProduct("A");
  Product* pb = Factory::CreateProduct("B");
  pa->Operation();
  pb->Operation();

  delete pb;
  delete pa;
  return 0;
}
