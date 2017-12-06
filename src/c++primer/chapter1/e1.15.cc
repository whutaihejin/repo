#include <iostream>

int main() {
    // error: expected ';' after expression
    // std::cout << "Read each file." << std::endl:
    

    // error: expected ';' after expression
    // std::cout << Update master. << std::endl;
    //                            ^
    // error: use of undeclared identifier 'Update'
    // std::cout << Update master. << std::endl;
    //                            ^
    // error: use of undeclared identifier 'master'
    // std::cout << Update master. << std::endl;
    //                           ^
    // error: expected unqualified-id
    // std::cout << Update master. << std::endl;
    //

    // error: reference to overloaded function could not be resolved; did you mean to call it?
    //        std::cout << "Write new master" std::endl;
    // std::cout << "Write new master" std::endl
    
    // error: expected ';' after return statement
    // return 0
    
    int v1 = 0, v2 = 0;
    // error: use of undeclared identifier 'cout'; did you mean 'std::cout'?
    // cout << v1 + v2 << std::endl; 
    std::cout << v1 + v2 << std::endl;
    return 0;
}
