#include <iostream>

//= implements a IF-THEN-ELSE in template
template <bool P, class THEN, class ELSE>
struct IF
{
  typedef THEN RESULT;
};

template <class THEN, class ELSE>
struct IF<false, THEN, ELSE>
{
  typedef ELSE RESULT;
};
//========== now you can use IF-THEN-ELSE

// template <bool P, class THEN, class ELSE>
// struct IFNOT
// {
//   typedef ELSE RESULT;
// };
// 
// template <class THEN, class ELSE>
// struct IFNOT<false, THEN, ELSE>
// {
//   typedef THEN RESULT;
// };

template <bool P, class THEN, class ELSE>
using IFNOT = IF<!P, THEN, ELSE>;

//------------------- begin factorial --------------------//
struct Stop
{
  enum { ret = 1 };
};

// factorial template
template <long N>
struct Fact
{
  // Encapsulate data member `ret` in type series `Fact<>` (here, 
  // view type as some kind of data, this is essential), each 
  // `Fact<N>` has a data member `ret` to represent the factorial(N).
  // Things become easy powered by our IF-THEN-ELSE clause,
  // simply check if "N==1"?, if is, we are done, go to the type
  // `Stop` whose `ret` = 1; if not, we go to type `Fact<N-1>`,
  // who also has a data member `ret`, and the following holds:
  //    Fact<N>::ret = N * Fact<N-1>::ret
  // That's it.
  typedef typename IF<N==1, Stop, Fact<N-1>>::RESULT SubFact;
  enum { ret = N * SubFact::ret };
};

/********* VIEW TYPE AS DATA **********/
// The two main thoughts in template programming, are
//  1. view type as data
//  2. view procedure as data

int main()
{
  std::cout << Fact<1>::ret << std::endl;
  std::cout << Fact<2>::ret << std::endl;
  std::cout << Fact<3>::ret << std::endl;
  std::cout << Fact<4>::ret << std::endl;
  std::cout << Fact<5>::ret << std::endl;
  std::cout << Fact<6>::ret << std::endl;
  std::cout << Fact<7>::ret << std::endl;
  std::cout << Fact<8>::ret << std::endl;
  std::cout << Fact<9>::ret << std::endl;
  std::cout << Fact<10>::ret << std::endl;
  std::cout << Fact<11>::ret << std::endl;
  std::cout << Fact<12>::ret << std::endl;
  std::cout << Fact<13>::ret << std::endl;
  std::cout << Fact<14>::ret << std::endl;
  return 0;
}
