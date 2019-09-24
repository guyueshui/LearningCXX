// This file implements a demo of abstract factory pattern.
//
#include <cstdio>

#define PRINT_NAME printf("%s\n", __FUNCTION__)

// cats
class Cat
{
public:
  virtual ~Cat() { PRINT_NAME; }
public:
  virtual void Meow() = 0;
};

class BlackCat : public Cat
{
public:
  ~BlackCat() { PRINT_NAME; }
public:
  void Meow() override { printf("%s\n", "b::meow~"); }
};

class WhiteCat : public Cat
{
public:
  ~WhiteCat() { PRINT_NAME; }
public:
  void Meow() override { printf("%s\n", "w::meow~"); }
};

// dogs
class Dog
{
public:
  virtual ~Dog() { PRINT_NAME; }
public:
  virtual void Bark() = 0;
};

class BlackDog : public Dog
{
public:
  ~BlackDog() { PRINT_NAME; }
public:
  void Bark() override { printf("%s\n", "b::wang~"); }
};

class WhiteDog : public Dog
{
public:
  ~WhiteDog() { PRINT_NAME; }
public:
  void Bark() override { printf("%s\n", "w::wang~"); }
};

// here comes factory
class Factory
{
public:
  virtual ~Factory() { PRINT_NAME; }
public:
  virtual Cat* CreateCat() = 0;
  virtual Dog* CreateDog() = 0;
};

class BlackFactory : public Factory  // factory that dyes animals black
{
public:
  ~BlackFactory() { PRINT_NAME; }
public:
  Cat* CreateCat() override { return new BlackCat(); }
  Dog* CreateDog() override { return new BlackDog(); }
};

class WhiteFactory : public Factory  // factory that dyes animals white
{
public:
  ~WhiteFactory() { PRINT_NAME; }
public:
  Cat* CreateCat() override { return new WhiteCat(); }
  Dog* CreateDog() override { return new WhiteDog(); }
};

///
int main()
{
  Factory* pblack = new BlackFactory();
  Factory* pwhite = new WhiteFactory();

  Cat* black_cat = pblack->CreateCat();
  Cat* white_cat = pwhite->CreateCat();

  Dog* black_dog = pblack->CreateDog();
  Dog* white_dog = pwhite->CreateDog();

  black_cat->Meow();
  black_dog->Bark();
  white_cat->Meow();
  white_dog->Bark();

  delete white_dog;
  delete black_dog;
  delete white_cat;
  delete black_cat;
  delete pwhite;
  delete pblack;
  return 0;
}
