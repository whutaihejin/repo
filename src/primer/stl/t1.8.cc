#include <iostream>

// #define TestMacro(x) #ifdef x std::cout << #x"defined" << std::endl; #else std::cout << #x"undefined" << std::endl; #endif

int main() {

#if defined(__sgi)
    std::cout << "__sgi" << std::endl
#endif

#if defined(__GNUC__)
    std::cout << "__GNUC__" << std::endl;
    std::cout << __GNUC__ << ' ' << __GNUC_MINOR__ << std::endl;
    // std::cout << __GLIBC__ << std::endl;
#endif

#ifdef __STL_NO_DRAND48
    std::cout << "__STL_NO_DRAND48 defined" << std::endl;
#else
    std::cout << "__STL_NO_DRAND48 undefined" << std::endl;
#endif

#ifdef __STL_STATIC_TEMPLATE_MEMBER_BUG
    std::cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG defined" << std::endl;
#else
    std::cout << "__STL_STATIC_TEMPLATE_MEMBER_BUG undefined" << std::endl;
#endif

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
    std::cout << "__STL_CLASS_PARTIAL_SPECIALIZATION defined" << std::endl;
#else
    std::cout << "__STL_CLASS_PARTIAL_SPECIALIZATION undefined" << std::endl;
#endif

#ifdef __STL_ASSERTIONS
std::cout << "__STL_ASSERTIONS defined" << std::endl;
#else
std::cout << "__STL_ASSERTIONS undefined" << std::endl;
#endif

#ifdef __STL_NEED_EXPLICIT
std::cout << "__STL_NEED_EXPLICIT defined" << std::endl;
#else
std::cout << "__STL_NEED_EXPLICIT undefined" << std::endl;
#endif

#ifdef __STL_NEED_BOOL
std::cout << "__STL_NEED_BOOL defined" << std::endl;
#else
std::cout << "__STL_NEED_BOOL undefined" << std::endl;
#endif

#ifdef __STL_NEED_TYPENAME
std::cout << "__STL_NEED_TYPENAME defined" << std::endl;
#else
std::cout << "__STL_NEED_TYPENAME undefined" << std::endl;
#endif

#ifdef __STL_NO_NAMESPACE
std::cout << "__STL_NO_NAMESPACE defined" << std::endl;
#else
std::cout << "__STL_NO_NAMESPACE undefined" << std::endl;
#endif

#ifdef __STL_WIN32THREADS
std::cout << "__STL_WIN32THREADS defined" << std::endl;
#else
std::cout << "__STL_WIN32THREADS undefined" << std::endl;
#endif

#ifdef __STL_SGI_THREADS
std::cout << "__STL_SGI_THREADS defined" << std::endl;
#else
std::cout << "__STL_SGI_THREADS undefined" << std::endl;
#endif

#ifdef __STL_USE_NAMESPACES
std::cout << "__STL_USE_NAMESPACES defined" << std::endl;
#else
std::cout << "__STL_USE_NAMESPACES undefined" << std::endl;
#endif

#ifdef __STL_USE_EXCEPTIONS
std::cout << "__STL_USE_EXCEPTIONS defined" << std::endl;
#else
std::cout << "__STL_USE_EXCEPTIONS undefined" << std::endl;
#endif

#ifdef __SGI_STL_NO_ARROW_OPERATOR
std::cout << "__SGI_STL_NO_ARROW_OPERATOR defined" << std::endl;
#else
std::cout << "__SGI_STL_NO_ARROW_OPERATOR undefined" << std::endl;
#endif

#ifdef __STL_NON_TYPE_TMPL_PARAM_BUG
std::cout << "__STL_NON_TYPE_TMPL_PARAM_BUG defined" << std::endl;
#else
std::cout << "__STL_NON_TYPE_TMPL_PARAM_BUG undefined" << std::endl;
#endif

#ifdef __STL_LIMITED_DEFAULT_TEMPLATES
std::cout << "__STL_LIMITED_DEFAULT_TEMPLATES defined" << std::endl;
#else
std::cout << "__STL_LIMITED_DEFAULT_TEMPLATES undefined" << std::endl;
#endif

#ifdef __STL_MEMBER_TEMPLATES
std::cout << "__STL_MEMBER_TEMPLATES defined" << std::endl;
#else
std::cout << "__STL_MEMBER_TEMPLATES undefined" << std::endl;
#endif

#ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
std::cout << "__STL_EXPLICIT_FUNCTION_TMPL_ARGS defined" << std::endl;
#else
std::cout << "__STL_EXPLICIT_FUNCTION_TMPL_ARGS undefined" << std::endl;
#endif

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
std::cout << "__STL_FUNCTION_TMPL_PARTIAL_ORDER defined" << std::endl;
#else
std::cout << "__STL_FUNCTION_TMPL_PARTIAL_ORDER undefined" << std::endl;
#endif
    return 0;
}
