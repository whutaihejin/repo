#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

struct AbsInt {
  int operator()(int val) const { return val < 0 ? -val : val; }
};

class PrintString {
 public:
  PrintString(std::ostream& os = std::cout, char c = ' ') : os_(os), sep_(c) {}

  void operator()(const std::string& s) const { os_ << s << sep_; }

 private:
  std::ostream& os_;
  char sep_;
};

int GetSize() { return 10; }

struct PenaltyStrategy {
  int edgePenalty;
  int turnPenalty;
  float edgePenaltyTimes;  // 倍数
  float turnPenaltyTimes;  // 倍数
  int edgePenaltyType;
  int turnPenaltyType;

  // ~PenaltyStrategy() {
  //   const int k = -1;
  //   edgePenalty = k;
  //   turnPenalty = k;
  //   edgePenaltyTimes = k;
  //   turnPenaltyTimes = k;
  //   edgePenaltyType = k;
  //   turnPenaltyType = k;
  // }

  PenaltyStrategy() {
    edgePenalty = 0;
    turnPenalty = 0;
    edgePenaltyTimes = 0;
    turnPenaltyTimes = 0;
    edgePenaltyType = 0;
    turnPenaltyType = 0;
  }

  PenaltyStrategy(int edgePenalty, int turnPenalty, float edgePenaltyTimes, float turnPenaltyTimes, int edgePenaltyType,
                  int turnPenaltyType)
      : edgePenalty(edgePenalty),
        turnPenalty(turnPenalty),
        edgePenaltyTimes(edgePenaltyTimes),
        turnPenaltyTimes(turnPenaltyTimes),
        edgePenaltyType(edgePenaltyType),
        turnPenaltyType(turnPenaltyType) {}

  PenaltyStrategy(const PenaltyStrategy& other)
      : edgePenalty(other.edgePenalty),
        turnPenalty(other.turnPenalty),
        edgePenaltyTimes(other.edgePenaltyTimes),
        turnPenaltyTimes(other.turnPenaltyTimes),
        edgePenaltyType(other.edgePenaltyType),
        turnPenaltyType(other.turnPenaltyType) {}

  bool operator==(const PenaltyStrategy& other) {
    return edgePenalty == other.edgePenalty && turnPenalty == other.turnPenalty &&
           edgePenaltyTimes == other.edgePenaltyTimes && turnPenaltyTimes == other.turnPenaltyTimes &&
           edgePenaltyType == other.edgePenaltyType && turnPenaltyType == other.turnPenaltyType;
  }

  std::string toString() const {
    char buf[512] = {0};
    int n = snprintf(buf, sizeof(buf), "{%u, %u, %.2f, %.2f, %d, %d}", edgePenalty, turnPenalty, edgePenaltyTimes,
                     turnPenaltyTimes, edgePenaltyType, turnPenaltyType);
    return std::string(buf, n);
  }
};

class Sandbox {
 public:
  Sandbox(const std::string& n, const PenaltyStrategy& penalty) : member_(n), penalty_(penalty) {}
  friend std::ostream& operator<<(std::ostream&, const Sandbox&);

 private:
  const std::string& member_;
  const PenaltyStrategy& penalty_;
};

std::ostream& operator<<(std::ostream& os, const Sandbox& box) {
  os << "Sanbox{member=" << box.member_ << ", penalty=" << box.penalty_.toString() << "}";
  return os;
}

PenaltyStrategy GetPenalty() {
  PenaltyStrategy p;
  p.edgePenalty = 22;
  p.turnPenalty = 22;
  p.edgePenaltyTimes = 22;
  p.turnPenaltyTimes = 22;
  p.edgePenaltyType = 22;
  p.turnPenaltyType = 22;
  return p;
}

int main() {
  std::cout << "hello" << std::endl;
  AbsInt abs_int;
  assert(1 == abs_int(1));
  assert(1 == abs_int(-1));
  std::cout << abs_int(-10) << std::endl;

  PrintString printer;
  std::string str = "hello world";
  printer(str);

  PrintString errors(std::cerr, '\n');
  errors(str);

  std::vector<std::string> words{"How", "are", "you"};
  std::for_each(words.begin(), words.end(), PrintString(std::cerr, '\n'));

  std::stable_sort(words.begin(), words.end(),
                   [](const std::string& a, const std::string& b) { return a.size() < b.size(); });
  int ival = 1024;
  int& ref_val = ival;  // ref_val指向ival(是ival的另一个名字)
  // 错误：‘ref_val2’声明为引用却未被初始化
  // int& ref_val2;  // 报错：引用必须被初始化
  int& ref_val3 = ref_val;
  int ii = ref_val;
  // 0x7fff14b6c09c,0x7fff14b6c09c,0x7fff14b6c09c,0x7fff14b6c098
  std::cout << &ival << "," << &ref_val << "," << &ref_val3 << "," << &ii << std::endl;

  int i = 1024, i2 = 2048;  // i和i2都是int
  int &r = i, r2 = i2;      // r是一个引用，与i绑定在一起，r2是int
  int i3 = 1024, &ri = i3;  // i3是int，ri是一个引用，与i3绑定在一起
  int &r3 = i3, &r4 = i2;   // r3和r4都是引用

  // cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
  // int& ref_val4 = 10;
  double dval = 3.14;
  // cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
  // int& ref_val5 = dval;
  const int& ref_val6 = dval;
  std::cout << ref_val6 << std::endl;
  std::cout << "&dval=" << &dval << ",&ref_val6=" << &ref_val6 << std::endl;

  // exercise 2.15
  {
    int ival = 1.01;
    // int& rvall = 1.01; // cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    int& rval2 = ival;
    // int& rval3; // ‘rval3’声明为引用却未被初始化
  }

  // exercise 2.16
  {
    int i = 0, &r1 = i;
    double d = 0, &r2 = d;
    r2 = 3.14159;  // 对d赋值
    std::cout << "d=" << d << ",r2=" << r2 << std::endl;
    r2 = r1;  // 用i的值对d进行赋值
    std::cout << "r2=" << r2 << std::endl;
    i = r2;  // 用d的值对进行赋值
    std::cout << "i=" << i << std::endl;
    r1 = d;  // 用d的值对r1进行赋值
    std::cout << "r1=" << r1 << std::endl;
  }

  // exercise 2.17
  {
    int i, &ri = i;
    i = 5;
    ri = 10;
    std::cout << i << " " << ri << std::endl;
  }

  {
    const int buf_size = 512;
    // 错误：向只读变量‘buf_size’赋值
    // buf_size = 1024;

    const int i = GetSize();
    const int j = 32;
    // 错误：未初始化的常量‘k’ [-fpermissive]
    // const int k;
  }

  {
    int i = 22;
    const int ci = i;  // 正确：i的值被拷贝给了ci
    int j = ci;        // 正确：ci的值被拷贝给了j
    // 尽管ci是整型常量，但无论如何ci的值还是一个整型数。ci的常量特征仅仅在执行改变ci的操作时才会发挥作用。
    // 当用ci去初始化j时，根本无需在意ci是不是一个常量。拷贝一个对象的值并不会改变它，一旦拷贝完成，新的对象就和
    // 原来的对象没有什么关系了。
  }

  {
    const int ci = 1024;
    const int& r1 = ci;
    // 错误：向只读形参‘r1’赋值
    // r1 = 42;
    // 错误：binding reference of type ‘int&’ to ‘const int’ discards qualifiers
    // int& r2 = ci;
  }

  {
    // Does a const reference class member prolong the life of a temporary?
    Sandbox sandbox(std::string("four"), GetPenalty());
    std::cout << sandbox << std::endl;

    std::string five("five");
    PenaltyStrategy p = GetPenalty();
    Sandbox sandbox2(five, p);
    std::cout << sandbox2 << std::endl;

    // The standard specifies such behavior in §8.5.3/5, [dcl.init.ref], the section on initializers of reference
    // declarations. The reference in your example is bound to the constructor's argument n, and becomes invalid when
    // the object n is bound to goes out of scope.

    // The lifetime extension is not transitive through a function argument. §12.2/5 [class.temporary]:

    // The second context is when a reference is bound to a temporary. The temporary to which the reference is bound or
    // the temporary that is the complete object to a subobject of which the temporary is bound persists for the
    // lifetime of the reference except as specified below. A temporary bound to a reference member in a constructor’s
    // ctor-initializer (§12.6.2 [class.base.init]) persists until the constructor exits. A temporary bound to a
    // reference parameter in a function call (§5.2.2 [expr.call]) persists until the completion of the full expression
    // containing the call.

    // Does a const reference class member prolong the life of a temporary?
    Sandbox sandbox3(std::string("four"), GetPenalty());
    std::cout << sandbox3 << std::endl;

    // Does a const reference class member prolong the life of a temporary?
    Sandbox sandbox4(std::string("four"), GetPenalty());
    std::cout << sandbox4 << std::endl;
  }
  return 0;
}