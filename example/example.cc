#include <iostream>
#include "../src/collection.h"

using namespace fnc;

void fvec_example()
{
    double max_val = 4.0;

    std::cout << std::endl << "Filtered vector (n < " << max_val << ") ----------------" << std::endl << std::endl;
    fvec<double> v({1.5, 3.14, 5.00, 6, -4.3});
        v.filter([max_val](double x) { return x <= max_val; })
        .foreach([](double x){ std::cout << x << " "; });
    std::cout << std::endl;

    std::cout << std::endl << "Grouped vector ----------------" << std::endl << std::endl;
    fvec<int> vec({7, -4, 5, 8, 8, 0, -3, 7});
    fvec<fvec<int>> vv = vec.group();
    for (auto const &i: vv) {
        std::cout << "[";
        for (auto const &j: i) {
            std::cout << j << "\t";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::endl << "Clusterized vector ----------------" << std::endl << std::endl;
    fvec<fvec<int>> clusterize_vec = vec.clusterize();
    for (auto const &i: clusterize_vec) {
        std::cout << "[";
        for (auto const &j: i) {
            std::cout << j << "\t";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;

    std::cout << std::endl << "Except ----------------" << std::endl << std::endl;
    fvec<int> r = vrange(10);
    fvec<int> other({3, 4, 4, 3, 3});
    auto scan = r.except(other);

    for (auto const &j: scan) {
        std::cout << j << "\t";
    }
    std::cout << std::endl;

    std::cout << std::endl << "Cycle ----------------" << std::endl << std::endl;
    auto cc = cycle(scan, 3);
    for (auto const &j: cc) {
        std::cout << j << "\t";
    }
    std::cout << std::endl;

    std::cout << std::endl << "Sum ----------------" << std::endl << std::endl;
    int _s = other.sum();
    std::cout << _s ;
    std::cout << std::endl;

    std::cout << std::endl << "Even numbers (0 to 48) ----------------" << std::endl << std::endl;
    fvec<int> even_numbers_squared = vrange(0,50,1)
       .filter([](int x) { return x%2 == 0; })
       .map([](int x) { return x*x; });

   for (auto const &i: even_numbers_squared) {
       std::cout << i << " ";
   }
   std::cout << std::endl;
}

void flist_example()
{
    std::cout << std::endl << "Head of the list [0..10] ----------------" << std::endl << std::endl;
    flist<int> l2 = lrange(11);
    int h = l2.head();
    std::cout << h;
    std::cout << std::endl << std::endl;

    std::cout << std::endl << "First 4 elements of the list [0..10] ----------------" << std::endl << std::endl;
    flist<int> t = l2.take(4);
    for (auto const &i: t) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << std::endl << "Odd numbers in the list [0..10] ----------------" << std::endl << std::endl;
    flist<int> filtered = l2.filter([](int x) { return x%2 != 0; });
    for (auto const &i: filtered) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << std::endl << "Zip ----------------" << std::endl << std::endl;
    flist<flist<int>> z = l2.zip(filtered);
    for (auto const &i: z) {
        for (auto const &j: i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int main()
{
    fvec_example();
    flist_example();
}
