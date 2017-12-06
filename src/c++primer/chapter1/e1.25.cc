#include <iostream>
#include <string>

class SalesItem {
public:
    std::string Isbn() const {
        return isbn_;
    }

    SalesItem& operator+=(const SalesItem& rhs) {
       this->sold_number_ += rhs.sold_number_;
       this->total_revenue_ += rhs.total_revenue_;
       return *this;
    }

friend std::istream& operator>>(std::istream& in, SalesItem& item) {
    double price;
    in >> item.isbn_ >> item.sold_number_ >> price;

    if (in) {
        item.total_revenue_ = price * item.sold_number_;
    } else {
        item.isbn_ = "";
        item.total_revenue_ = 0;
        item.sold_number_ = 0;
    }
    return in;
}

friend std::ostream& operator<<(std::ostream& out, const SalesItem& item) {
    double average_price = item.total_revenue_ / std::max(item.sold_number_ , 1);
    out << item.isbn_ 
        << " " << item.sold_number_ 
        << " " << item.total_revenue_
        << " " << average_price;
    return out;
}

friend SalesItem& operator+(SalesItem& x, SalesItem& y) {
    if (x.Isbn() == y.Isbn()) {
        x.sold_number_ += y.sold_number_;
        x.total_revenue_ += y.total_revenue_;
    }
    return x;
}

private:
    std::string isbn_;
    // total revenue
    double total_revenue_; 
    // number of copies sold
    int sold_number_;
};

int main() {

    SalesItem total;
    if (std::cin >> total) {
        SalesItem trans;
        while (std::cin >> trans) {
            if (total.Isbn() == trans.Isbn()) {
                total += trans;
            } else {
                std::cout << total << std::endl;
                total = trans;
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}
