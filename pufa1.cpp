#include <iostream>
#include <vector>

using namespace std;

struct Vector2
{
  double x;
  double y;
  Vector2(double xx, double yy): x(xx), y(yy) {}
  void Printer() {cout << x << " " << y; }
};

Vector2 Middle(const Vector2& p1, const Vector2& p2)
{
  return Vector2(
      (p1.x + p2.x) / 2,
      (p1.y + p2.y) / 2
      );
}

int main()
{
  uint32_t x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  Vector2 p1(x1, y1);
  Vector2 p2(x2, y2);
  Vector2 mid = Middle(p1, p2);
  mid.Printer();
  return 0;
}
