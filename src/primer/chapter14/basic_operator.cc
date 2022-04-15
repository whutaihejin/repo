#include <cassert>
#include <iostream>

struct Vec {
  int x;
  int y;
  Vec& operator+(Vec& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
};

Vec operator+(Vec& lhs, Vec& rhs) {
  Vec r;
  r.x = lhs.x + rhs.x;
  r.y = lhs.y + rhs.y;
  return r;
}

struct Point {
  int lng;
  int lat;

  Point operator+(Point& rhs) {
    lng += rhs.lng;
    lat += rhs.lat;
    return *this;
  }

  Point& operator+=(Point& rhs) {
    lng += rhs.lng;
    lat += rhs.lat;
    return *this;
  }
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "Point{" << p.lng << "," << p.lat << "}";
  return os;
}

class Link {
 public:
  Link(int lng = 0, int lat = 0) : lng_(lng), lat_(lat) {}

  Link& operator=(const Link& rhs) {
    lng_ = rhs.lng_;
    lat_ = rhs.lat_;
    return *this;
  }

  Link& operator+=(const Link& rhs) {
    lng_ += rhs.lng_;
    lat_ += rhs.lat_;
    return *this;
  }

  friend Link operator+(const Link&, const Link&);
  friend bool operator==(const Link&, const Link&);
  friend bool operator!=(const Link&, const Link&);
  friend bool operator<(const Link&, const Link&);
  friend bool operator<=(const Link&, const Link&);
  friend bool operator>(const Link&, const Link&);
  friend bool operator>=(const Link&, const Link&);
  friend std::istream& operator>>(std::istream&, Link&);
  friend std::ostream& operator<<(std::ostream&, const Link&);

 private:
  int lng_;
  int lat_;
};

Link operator+(const Link& lhs, const Link& rhs) {
  Link l(lhs);
  l += rhs;
  return l;
}

std::istream& operator>>(std::istream& is, Link& link) {
  is >> link.lng_ >> link.lat_;
  return is;
}

std::ostream& operator<<(std::ostream& os, const Link& link) {
  os << "Link{" << link.lng_ << "," << link.lat_ << "}";
  return os;
}

bool operator==(const Link& lhs, const Link& rhs) {
  return lhs.lng_ == rhs.lng_ && lhs.lat_ == rhs.lat_;
}

bool operator!=(const Link& lhs, const Link& rhs) { return !(lhs == rhs); }

bool operator<(const Link& lhs, const Link& rhs) {
  if (lhs.lng_ < rhs.lng_) {
    return true;
  } else if (lhs.lng_ > rhs.lng_) {
    return false;
  } else {
    return lhs.lat_ < rhs.lat_;
  }
}

bool operator<=(const Link& lhs, const Link& rhs) {
  return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Link& lhs, const Link& rhs) { return !(lhs <= rhs); }

bool operator>=(const Link& lhs, const Link& rhs) { return !(lhs < rhs); }

int main() {
  Vec v1{1, 1};
  Vec v2{2, 2};
  Vec v3 = operator+(v1, v2);
  std::cout << v3.x << "," << v3.y << std::endl;

  Point p1{1, 1};
  Point p2{2, 2};
  Point p3 = p1 + p2;
  std::cout << p3 << std::endl;

  Point p4{3, 3};
  Point p5{2, 2};
  p4 += p5;
  assert(p4.lng == 5 && p4.lat == 5);
  std::cout << p4 << std::endl;

  Link lk1(1, 1);
  Link lk2(2, 2);
  Link lk3 = lk1 + lk2;
  std::cout << lk3 << std::endl;

  Link lk4;
  std::cout << "Input Link with lng lag" << std::endl;
  std::cin >> lk4;
  std::cout << lk4 << std::endl;

  Link lk5, lk6;
  assert(lk5 == lk6);

  Link lk7(1, 1);
  Link lk8(1, 1);
  assert(lk7 == lk8);
  assert(!(lk7 != lk8));
  assert(lk7 <= lk8);
  assert(lk7 >= lk8);

  Link lk9(1, 2);
  Link lk10(2, 3);
  assert(lk9 < lk10);
  assert(lk9 <= lk10);
  assert(!(lk9 == lk10));
  assert(lk9 != lk10);
  assert(!(lk9 > lk10));
  assert(!(lk9 >= lk10));
  return 0;
}