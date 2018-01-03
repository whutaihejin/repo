#include <iostream>

class Quote {
public:
    Quote(const std::string& book_no, double sales_price):
        isbn_(book_no),
        price_(sales_price) {}
    
    std::string Isbn() const;
   
    virtual double NetPrice(std::size_t size) const;
private:
    std::string isbn_;

protected:
    double price_;
};

class BulkQuote : public Quote {
public:
    BulkQuote(const std::string& isbn,
            double sales_price,
            std::size_t qty,
            double discount):
        Quote(isbn, sales_price),
        min_qty_(qty),
        discount_(discount) {}
    virtual double NetPrice(std::size_t size) const override;

private:
    std::size_t min_qty_;
    double discount_;
};

std::string Quote::Isbn() const {
    return this->isbn_;
}

double Quote::NetPrice(std::size_t size) const {
    std::cout << "Quote" << std::endl;
    return size * price_;
}

double BulkQuote::NetPrice(std::size_t size) const {
    std::cout << "BulkQuote" << std::endl;
    return size >= min_qty_ ? size * (1 - discount_) * price_  : size * price_;
}

double PrintTotal(std::ostream& out, Quote& item, std::size_t size) {
    double ret = item.NetPrice(size);
    out << "ISBN: " << item.Isbn()
        << " # sold: " << size
        << " total due: " << ret << std::endl;
    return ret;
}

class NoDerived final {};

class Base {};

class Last final : Base {};

// base 'NoDerived' is marked 'final'
// class Bad : public NoDerived {};

// base 'NoDerived' is marked 'final'
// class Bad2 : public Last {};

int main() {
    Quote q("quote", 1);
    BulkQuote b("bulk_quote", 1, 1, 0.2);
    PrintTotal(std::cout, q, 1);
    PrintTotal(std::cout, b, 2);
    return 0;
}
