/*
 *  functor/fvec.cc
 *  library: functor
 *
 *  Created by Nicoli Matteo on 07/06/2021.
 *  Copyright © 2021 Nicoli Matteo.
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <tuple>

#include "fvec.h"

namespace fnc {

    fvec<int> vrange(int start, int stop, int step = 1)
    {
        fvec<int> v;
    
        if (start <= stop) {
            for (int i = start; i < stop; i += step) 
                v.push_back(i);
        } else {
            for (int i = start; i > stop; i -= step) 
                v.push_back(i);
        }

        return v;
    }

    inline fvec<int> vrange(int stop, int step = 1) { return vrange(0,stop,step); }

    template <typename T>
    fvec<T> cycle(fvec<T> vec, int n)
    {
        if (vec.empty()) throw "ERROR: empty vector";
        if (n < 0) throw "n must be greater (or equal) than 0";
    
        fvec<T> new_vec;
        for (int i = 0; i < n; ++i) {
            for (auto const &i: vec) {
                new_vec.push_back(i);
            }
        }
    
        return new_vec;
    }

    template <typename T>
    fvec<T>::fvec() : std::vector<T>() {}

    template <typename T>
    fvec<T>::fvec(std::vector<T> v) : std::vector<T>(v) {}

    template <typename T>
    inline std::vector<T> fvec<T>::to_vector() { return *this; }

    template <typename T>
    inline T fvec<T>::head() { return this->front(); }

    template <typename T>
    fvec<T> fvec<T>::drop(int n)
    {
        fvec<T> vector;
    
        if (this->empty()) return vector;
    
        for (auto first = this->begin()+n; first != this->end(); ++first) {
            vector.push_back(*first);
        }
        return vector;
    }

    template <typename T>
    fvec<T> fvec<T>::tail() { return this->drop(1); }

    template <typename T>
    fvec<T> fvec<T>::init()
    {
        fvec<T> new_vec(*this);
        new_vec.pop_back();
        return new_vec;
    }

    template <typename T>
    inline T fvec<T>::last()
    {
        return *(this->end()-1);
    }

    template <typename T>
    fvec<T> fvec<T>::take(int n)
    {
        fvec<T> new_vec;
        int counter = 0;
        for (auto const &i: *this) {
            if (counter == n) break;
            new_vec.push_back(i);
            counter++;
        }
        return new_vec;
    }

    template <typename T>
    fvec<T> fvec<T>::copy()
    {
        fvec<T> new_vec;
        for (auto const &i: *this) {
            new_vec.push_back(i);
        }
        return new_vec;
    }

    template <typename T>
    T fvec<T>::foldr(std::function<T(T,T)> f, T base)
    {
        if (this->empty()) return base;
        return f(this->head(),this->tail().foldr(f,base));
    }

    template <typename T>
    T fvec<T>::foldl(std::function<T(T,T)> f, T base)
    {
        if (this->empty()) return base;
        return this->tail().foldl(f,f(base,this->head()));
    }

    template <typename T>
    fvec<T> fvec<T>::scanr(std::function<T(T,T)> f, T base)
    {
        fvec<T> vec;
        auto tails = this->tails();
        for (fvec<T> &i: tails) {
            vec.push_back(i.foldr(f,base));
        }
        vec.push_back(base);
    
        return vec;
    }

    template <typename T>
    fvec<T> fvec<T>::scanl(std::function<T(T,T)> f, T base)
    {
        fvec<T> vec({base});
        auto inits = this->inits();
        for (fvec<T> &i: inits) {
            vec.push_back(i.foldl(f,base));
        }
    
        return vec;
    }

    template <typename T>
    fvec<fvec<T> > fvec<T>::group_by(std::function<bool(T,T)> f)
    {
        fvec<fvec<T>> grouped;
        auto i = this->begin();
    
        while(i != this->end()) {
            fvec<T> tmp;
            tmp.push_back(*i);
            while (f(*i,*(i+1))) {
                tmp.push_back(*i);
                ++i;
            }
            ++i;
            grouped.push_back(tmp);
        }
    
        return grouped;
    }

    template <typename T>
    fvec<fvec<T> > fvec<T>::group()
    {
        return this->group_by([](T x, T y) { return x == y; });
    }

    template <typename T>
    fvec<T> fvec<T>::map(std::function<T(T)> f)
    {
        fvec<T> vector;
        for (auto const &i: *this) {
            vector.push_back(f(i));
        }
        return vector;
    }

//template fvec<int> fvec<int>::map(std::function<int(int)> predicate);

    template <typename T>
    fvec<T> fvec<T>::filter(std::function<bool(T)> predicate)
    {
        fvec<T> vector;
        for (auto const &i: *this) {
            if (predicate(i))
                vector.push_back(i);
        }
        return vector;
    }

template fvec<int> fvec<int>::filter(std::function<bool(int)> predicate);

    template <typename T>
    fvec<fvec<T> > fvec<T>::zip(fvec<T> other)
    {
        fvec<fvec<T>> result;
    
        for (auto first = this->begin(), second = other.begin();
             first != this->end() && second != other.end();
             ++first,++second) {
            fvec<T> tmp;
            tmp.push_back(*first);
            tmp.push_back(*second);
            result.push_back(tmp);
        }
        return result;                    
    }

    template <typename T>
    fvec<T> fvec<T>::zip_with(fvec<T> other, std::function<bool(T,T)> f)
    {
        fvec<T> result;
    
        for (auto first = this->begin(), second = other.begin();
             first != this->end() && second != other.end();
             ++first,++second) {
            result.push_back(f(*first,*second));
        }
    
        return result;
    }

    template <typename T>
    fvec<T> fvec<T>::concat(fvec<T> other)
    {
        fvec<T> vec(*this);
        for (auto const &i: other) {
            vec.push_back(i);
        }
    
        return vec;
    }

    template <typename T>
    fvec<fvec<T> > fvec<T>::inits()
    {
        fvec<fvec<T>> new_vec;
    
        if (this->empty()) return new_vec;
    
        new_vec.push_back(*this);
        return this->init().inits().concat(new_vec);
    }

    template <typename T>
    fvec<fvec<T> > fvec<T>::tails()
    {
        fvec<fvec<T>> new_vec;
    
        if (this->empty()) return new_vec;
    
        new_vec.push_back(*this);
        return new_vec.concat(this->tail().tails());
    }

    template <typename T>
    fvec<T> fvec<T>::unite(fvec<T> other)
    {
        std::map<T,bool> m;
        fvec<T> united;
        for (auto const &i: *this) {
            united.push_back(i);
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: other) {
            if (! map_contains(m,j)) united.push_back(j);
        }

        return united;
    }

    template <typename T>
    fvec<T> fvec<T>::intersecate(fvec<T> other)
    {
        std::map<T,bool> m;
        fvec<T> intersected;
        for (auto const &i: *this) {
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: other) {
            if (map_contains(m,j)) intersected.push_back(j);
        }

        return intersected;
    }

    template <typename T>
    fvec<T> fvec<T>::distinct()
    {
        std::map<T,bool> m;
        fvec<T> new_vec;
        for (auto const &i: *this) {
            if (!map_containsKey(m,i)) {
    		m[i] = true;
    		new_vec.push_back(i);
            }
        }
        return new_vec;
    }

    template <typename T>
    inline bool fvec<T>::any(T elem) { return this->find(elem) != this->end(); }

    template <typename T>
    inline fvec<T> fvec<T>::singleton(T element) { return fvec<T>({element}); }

    template <typename T>
    fvec<T> fvec<T>::reverse()
    {
        if (this->size() <= 1) return *this;

        fvec<T> vec;
        for (auto i = this->end(); i != this->begin(); --i) {
            vec.push_back(*i);
        }
        return vec;
    }

    template <typename T>
    T fvec<T>::sum()
    {
        T sum = 0;

        for (auto const &i: *this) {
            sum += i;
        }
        return sum;
    }

    template <typename T>
    T fvec<T>::product()
    {
        T product = 1;

        for (auto const &i: *this) {
            product *= i;
        }
        return product;
    }

    template <typename T>
    T fvec<T>::min()
    {
        if (this->size() == 0) throw "Cannot calculate the minimum of an empty vector";
        if (this->size() == 1) return this->head();
        return std::min(this->head(),this->tail().min());
    }

    template <typename T>
    T fvec<T>::max()
    {
        if (this->size() == 0) throw "Cannot calculate the maximum of an empty vector";
        if (this->size() == 1) return this->head();
        return std::max(this->head(),this->tail().max());
    }

//    template <typename T>
//    std::tuple<T,T> fvec<T>::minmax()
//    {
//        return std::make_tuple(this->min(),this->max);
//    }

    template <typename T>
    void fvec<T>::foreach(std::function<void(T)> action)
    {
        for (auto const &i: *this) {
            action(i);
        }
    }

    template <typename T>
    template <typename U>
    fvec<U> fvec<T>::select(std::function<U(T)> selector)
    {
        fvec<U> res;
        for (auto const &i: *this) {
            res.push_back(selector(i));
        }
        return res;
    }

    template <typename T>
    fvec<T> fvec<T>::except(fvec<T> other)
    {
        std::map<T,bool> m;
        fvec<T> res;
        for (auto const &i: other) {
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: *this) {
            if (!map_contains(m,j)) res.push_back(j);
        }

        return res;
    }

    template <typename T>
    fvec<T> fvec<T>::sort(std::function<bool(T,T)> comparator)
    {
        fvec<T> sorted(*this);
        std::sort(sorted.begin(),sorted.end(),comparator);
        return sorted;
    }

    template <typename T>
    fvec<T> fvec<T>::sort()
    {
        return this->sort([](T x,T y) { return x <= y; });
    }

    template <typename T>
    fvec<T> fvec<T>::sort_heap(std::function<bool(T,T)> comparator)
    {
        fvec<T> sorted(*this);
        std::sort_heap(sorted.begin(),sorted.end(),comparator);
        return sorted;
    }

    template <typename T>
    fvec<T> fvec<T>::sort_heap()
    {
        return this->sort_heap([](T x,T y) { return x <= y; });
    }

    template <typename T>
    fvec<T> fvec<T>::intersperse(T elem)
    {
        fvec<T> new_vector;
    
        for (auto start = this->begin(), last = this->end()-1;
             start != this->end(); ++start) {
        
            new_vector.push_back(*start);
        
            if (start != last)
                new_vector.push_back(elem);
        }
    
        return new_vector;
    }

    template <typename T>
    fvec<T> fvec<T>::rotate_left(int n_positions)
    {
        std::vector<T> new_vec(*this);
        std::rotate(new_vec.begin(),new_vec.begin()+n_positions,new_vec.end());

        return new_vec;
    }

    template <typename T>
    fvec<T> fvec<T>::shuffle()
    {
        fvec<T> new_vec(*this);

        auto seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle (new_vec.begin(), new_vec.end(), std::default_random_engine(seed));
    
        return new_vec;
    }

    template <typename T>
    inline bool fvec<T>::map_contains(std::map<T,bool> m, T val)
    {
        return m.find(val) != m.end();
    }
}

//using namespace fnc;
//
//int main()
//{
//    fvec<int> even_numbers_squared = vrange(0,50,1)
//        .filter([](int x) { return x%2 == 0; })
//        .map([](int x) { return x*x; });
//
//    for (auto const &i: even_numbers_squared) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//}


/*
  int main(int argc, const char * argv[])
  {
    
  // Let vec be a vector that stores the results of a computation.
  // The code below filters such results keeping only these greater
  // that a certain value `x`, and finally it prints them.
     
  double max_val = 4.0;
  fvec<double> v({1.5, 3.14, 5.00, 6, -4.3});
  v.filter([max_val](double x) { return x <= max_val; })
  .foreach([](double x){ std::cout << x << " "; });
   
    
    
//    for (auto const &i: v) {
//        for (auto const &j: i) {
//            std::cout << j << "\t";
//        }
//        std::cout << std::endl;
//    }
    
    
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
    
return 0;
}
*/
