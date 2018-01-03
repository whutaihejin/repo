#include <iostream>

class Quote {
public:
    Quote(const std::string& isbn): isbn_(isbn) {}
    std::string Isbn() const;
    virtual double NetPrice(std::size_t size) const;
private:
    std::string isbn_;
};

class BulkQuote : public Quote {
public:
    BulkQuote(const std::string& isbn): Quote(isbn) {}
    virtual double NetPrice(std::size_t size) const;
};

std::string Quote::Isbn() const {
    return this->isbn_;
}

double Quote::NetPrice(std::size_t) const {
    std::cout << "Quote" << std::endl;
    return 1.0;
}

double BulkQuote::NetPrice(std::size_t) const {
    std::cout << "BulkQuote" << std::endl;
    return 2.0;
}

double PrintTotal(std::ostream& out, Quote& item, std::size_t size) {
    double ret = item.NetPrice(size);
    out << "ISBN: " << item.Isbn()
        << " # sold: " << size
        << " total due: " << ret << std::endl;
    return ret;
}

int main() {
    Quote q("quote");
    BulkQuote b("bulk_quote");
    PrintTotal(std::cout, q, 1);
    PrintTotal(std::cout, b, 2);
    return 0;
}
