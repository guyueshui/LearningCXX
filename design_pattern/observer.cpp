// This file implements a demo of observer pattern.
//
#include <cstdio>
#include <list>
#include <string>

#define PRINT_NAME printf("%s\n", __FUNCTION__)

// front declaration
class Subject;
class Observer;

class Subject
{
public:
  virtual ~Subject() { PRINT_NAME; }

public:
  virtual void attach(Observer* ob);
  virtual void detach(Observer* ob);
  virtual void notify();  // notify all observers
  
  virtual void set_state(int state) = 0;
  virtual int get_state() = 0;

private:
  std::list<Observer*> observers_;
};

class Observer
{
public:
  virtual ~Observer() { PRINT_NAME; }
public:
  virtual void update(Subject* sb) = 0;
};

//================ impl subject ==============
void Subject::attach(Observer* ob) { observers_.push_back(ob); }

void Subject::detach(Observer* ob)
{
  for (auto it = observers_.begin(); it != observers_.end(); ++it)
  {
    if (*it == ob)
    {
      observers_.erase(it);
      break;
    }
  }
}

void Subject::notify()
{
  for (auto ob : observers_)
    ob->update(this);
}

/* a specific subject */
class Weather : public Subject
{
public:
  ~Weather() { PRINT_NAME; }

public:
  void set_state(int s) override { state_ = s; }
  int get_state() override { return state_; }

private:
  int state_;
};

/* a specific observer */
class WeatherAPP : public Observer
{
public:
  WeatherAPP(const std::string& name): name_(name) {}
  ~WeatherAPP() { PRINT_NAME; }

public:
  void update(Subject* sb) override
  {
    state_ = sb->get_state(); 

    printf("Observer %s: ", name_.data());
    switch (state_)
    {
      case 0: printf("default\n");
              break;
      case 1: printf("rainy\n");
              break;
      case 2: printf("cloudy\n");
              break;
      case 3: printf("foggy\n");
              break;
      default: break;
    }
  }

private:
  int state_;
  std::string name_;
};

///
int main()
{
  Subject* weather = new Weather();
  Observer* ob1 = new WeatherAPP("Color TianQi");
  Observer* ob2 = new WeatherAPP("Moji TianQi");
  weather->attach(ob1);
  weather->attach(ob2);

  weather->set_state(1); // rainy
  weather->notify();

  weather->detach(ob2);
  weather->set_state(3); // foggy
  weather->notify();
  
  delete ob2;
  delete ob1;
  delete weather;
  return 0;
}
