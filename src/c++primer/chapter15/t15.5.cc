#include <iostream>

class Base {
protected:
    int prot_member_;
};

class Sneaky : public Base {
friend void Clobber(Sneaky&);
friend void Clobber(Base&);
int j;

public:
    void f() {
        prot_member_ = 0;
    }

    void f2(Sneaky& s) {
        s.prot_member_ = 0;
    }
    
    void f2(Base& s) {
        // prot_member_' is a protected member of 'Base'
        // s.prot_member_ = 0;
    }
};

void Clobber(Sneaky& s) {
    s.j = s.prot_member_ = 0;
}

void Clobber(Base& b) {
    // 'prot_member_' is a protected member of 'Base'
    // b.prot_member_ = 0;
}

class Base1 {
public:
    void pub_f() {}
protected:
    void pro_f() {}
private:
    void pri_f() {}
};

struct PubDerived : public Base1 {
    void f() {
        pub_f();
        pro_f();
        // 'pri_f' is a private member of 'Base1'
        // pri_f();
    }
};

struct ProDerived : protected Base1 {
    void f() {
        pub_f();
        pro_f();
        // pri_f();
    }
};

struct PriDerived : protected Base1 {
    void f() {
        pub_f();
        pro_f();
        // pri_f();
    }
};

int main() {
    PubDerived pub;
    pub.pub_f();
    // pub.pro_f();
    // pub.pri_f();
    ProDerived pro;
    // pro.pub_f();
    // pro.pro_f();
    // pro.pri_f();
    PriDerived pri;
    // pri.pub_f();
    // pri.pro_f();
    // pri.pri_f();
    return 0;
}
