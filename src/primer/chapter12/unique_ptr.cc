#include <iostream>
#include <memory>

class Record {
public:
    Record() {
        std::cout << "con record" << std::endl;
    }

    ~Record() {
        std::cout << "destroy record" << std::endl;
    }
};

class RecordReleaser {
public:
    void operator()(Record* r) {
        std::cout << "invoke release" << std::endl;
        delete r;
    }
};

int main() {
    {
        std::unique_ptr<Record> p;
        std::unique_ptr<int> p1(new int(42));
    }
    {
        std::unique_ptr<std::string> p1(new std::string("stegosaurus"));
        
        // error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&)
        // std::unique_ptr<std::string> p2(p1);
        
        // error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&)
        // std::unique_ptr<std::string> p3;
        // p3 = p1;
    }

    {
        std::unique_ptr<int> p1;
        std::unique_ptr<Record, RecordReleaser> p2;
        std::unique_ptr<Record> p3(new Record());
        std::unique_ptr<Record, RecordReleaser> p4(new Record());
        RecordReleaser r;
        std::unique_ptr<Record, RecordReleaser> p5(new Record, r);
    }

    {
        std::unique_ptr<Record> p1(new Record());
        p1 = nullptr;
    }
    return 0;
}
