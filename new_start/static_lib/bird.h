#ifndef __BIRD_H__
#define __BIRD_H__

#include <string>

class Bird
{
private:
    std::string name_;
    std::string identity() { return "Bird/" + name_; }

public:
    Bird(const std::string& name): name_(name) {}
    Bird(const char* name): name_(name) {}
    void eat(std::string food);
    void fly();
};
#endif /* ifndef __BIRD_H__ */
