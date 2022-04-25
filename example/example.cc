#include <iostream>
#include "../src/fvec.h"

using namespace fnc;

void fvec_example()
{
    double max_val = 4.0;
    fvec<double> v({1.5, 3.14, 5.00, 6, -4.3});
    v.filter([max_val](double x) { return x <= max_val; })
    .foreach([](double x){ std::cout << x << " "; });

    fvec<int> vec({-4,5,8,8,0,-3,7});
    fvec<fvec<int>> vv = vec.group();
    for (auto const &i: vv) {
        for (auto const &j: i) {
            std::cout << j << "\t";
        }
        std::cout << std::endl;
    }

    fvec<int> r = vrange(10);
    fvec<int> ot({3,4,4,3,3});
    auto scan = r.except(ot);

    for (auto const &j: scan) {
        std::cout << j << "\t";
    }
    std::cout << std::endl << "---------------------------\n\n";

    auto cc = cycle(scan, 3);
    for (auto const &j: cc) {
        std::cout << j << "\t";
    }
    std::cout << std::endl;

    std::cout << std::endl << "SUM-------------------------\n\n";
    int _s = ot.sum();

    std::cout << _s << "\t";

    std::cout << std::endl;

    fvec<int> even_numbers_squared = vrange(0,50,1)
       .filter([](int x) { return x%2 == 0; })
       .map([](int x) { return x*x; });

   for (auto const &i: even_numbers_squared) {
       std::cout << i << " ";
   }
   std::cout << std::endl;
}

int main()
{
    fvec_example();
}
