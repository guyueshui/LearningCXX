#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Representation of a student.
class Student
{
public:
  Student(const string& name, int ch, int ma, int en):
    name_(name), chinese_(ch), math_(ma), english_(en)
  {}
  ~Student() = default;
  
  friend ostream& operator<<(ostream&, const Student&);
  friend bool operator<(const Student&, const Student&);
  friend bool operator==(const Student&, const Student&);

public:
  // implicit inline
  int TotalScore() const
  { return chinese_ + math_ + english_; }

  // selectors
  string name() const { return name_; }
  int chinese() const { return chinese_; }
  int math() const { return math_; }
  int english() const { return english_; }

private:
  string name_;
  int chinese_;
  int math_;
  int english_;
};

// Compare policy.
bool operator<(const Student& lhs, const Student& rhs)
{
  if (lhs.TotalScore() > rhs.TotalScore())
    return true;
  else if (lhs.TotalScore() < rhs.TotalScore())
    return false;

  if (lhs.chinese_ > rhs.chinese_)
    return true;
  else if (lhs.chinese_ < rhs.chinese_)
    return false;

  if (lhs.math_ > rhs.math_)
    return true;
  else if (lhs.math_ < rhs.math_)
    return false;

//  if (lhs.english_ > rhs.english_)
//    return true;
//  else if (lhs.english_ < rhs.english_)
//    return false;

  // now the two students have exactly same scores
  if (lhs.name_ < rhs.name_)
    return true;

  return false;
}

bool operator==(const Student& lhs, const Student& rhs)
{
  return lhs.TotalScore() == rhs.TotalScore()
      && lhs.chinese_ == rhs.chinese_
      && lhs.math_ == rhs.math_;
}

bool operator!=(const Student& lhs, const Student& rhs)
{ return !(lhs == rhs); }

// Print function.
ostream& operator<<(ostream& os, const Student& st)
{
  os << st.name_ << ' '
     << st.chinese_ << ' '
     << st.math_ << ' '
     << st.english_;
  return os;
}

// Filter unpassed stduents.
void FilterPassed(vector<Student>& students)
{
  // remove unpassed
  auto it = std::remove_if(students.begin(), students.end(),
                           [](const Student& st)
                           {
                             if (st.chinese() < 60 ||
                                 st.math() < 60 ||
                                 st.english() < 60)
                             {
                               return true;
                             }
                             if (st.name().size() > 10)
                               return true;
                             return false;
                           });
  // remove the tail
  int remain = students.end() - it;
  for (int i = 0; i < remain; ++i)
    students.pop_back();

  // sort
  std::sort(students.begin(), students.end());
}


int main()
{
  vector<Student> students;
  for (string line; std::getline(cin, line);)
  {
    istringstream is(line);
    string name;
    int chinese, math, english;
    is >> name >> chinese >> math >> english;
    students.emplace_back(name, chinese, math, english);
  }
  // io done
  
  FilterPassed(students);
  cout << "[First round name list]" << endl;
  for (auto &e : students)
    cout << e << endl;

  cout << endl;
  cout << "[Final name list]" << endl;
  for (int cnt = 3, i = 1; cnt > 0 && i < (int)students.size(); ++i)
  {
    cout << students[i-1] << endl;
    if (students[i] != students[i-1]) --cnt;
  }

  return 0;
}
