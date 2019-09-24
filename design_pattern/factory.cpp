#include <cstdio>

#define PRINT_NAME printf("%s\n", __FUNCTION__)

class Product
{
public:
  virtual ~Product() { PRINT_NAME; }
public:
  virtual void Operation() = 0;
};

class ProductA : public Product
{
public:
  ~ProductA() { PRINT_NAME; }
public:
  void Operation() override
  {
    printf("%s\n", "ProductA::Operation()");
  }
};

class ProductB : public Product
{
public:
  ~ProductB() { PRINT_NAME; }
public:
  void Operation() override
  {
    printf("%s\n", "ProductB::Operation()");
  }
};

class Creator
{
public:
  virtual ~Creator() { PRINT_NAME; }
public:
  virtual Product* CreateProduct() = 0;
};

class CreatorA : public Creator
{
public:
  ~CreatorA() { PRINT_NAME; }
public:
  Product* CreateProduct() override
  {
    return new ProductA();
  }
};

class CreatorB : public Creator
{
public:
  ~CreatorB() { PRINT_NAME; }
public:
  Product* CreateProduct() override
  {
    return new ProductB();
  }
};

// test
int main()
{
  Creator* ca = new CreatorA;  
  Product* pa = ca->CreateProduct();
  pa->Operation();

  Creator* cb = new CreatorB;
  Product* pb = cb->CreateProduct();
  pb->Operation();

  delete pb;
  delete cb;
  delete pa;
  delete ca;
  return 0;
}
