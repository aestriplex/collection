/*
 *  collection/src/fset.cc
 *  library: collection
 *
 *  Created by Nicoli Matteo on 09/06/2021.
 *  Copyright © 2021 Nicoli Matteo.
 */

#include <set>
#include <map>

namespace fnc {

    template <typename T>
    fset<T>::fset() : std::set<T>() {}

    template <typename T>
    fset<T>::fset(std::set<T> s) : std::set<T>(s) {}

    template <typename T>
    inline std::set<T> fset<T>::to_set() { return *this; }

    template <typename T>
    fset<T> fset<T>::copy()
    {
        fset<T> new_set;
        for (auto const &i: *this) {
            new_set.insert(i);
        }
        return new_set;
    }

    template <typename T>
    fset<T> fset<T>::map(std::function<T(T)> f)
    {
        fset<T> set;
        for (auto const &i: *this) {
                set.insert(f(i));
        }
        return set;
    }

    template <typename T>
    fset<T> fset<T>::filter(std::function<bool(T)> predicate)
    {
        fset<T> set;
        for (auto const &i: *this) {
            if (predicate(i))
                set.insert(i);
        }
        return set;
    }

    template <typename T>
    fset<T> fset<T>::unite(fset<T> other)
    {
        std::map<T,bool> m;
        fset<T> united;
        for (auto const &i: *this) {
            united.insert(i);
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: other) {
            if (! map_contains(m,j)) united.insert(j);
        }

        return united;
    }

    template <typename T>
    fset<T> fset<T>::intersecate(fset<T> other)
    {
        std::map<T,bool> m;
        fset<T> intersected;
        for (auto const &i: *this) {
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: other) {
            if (map_contains(m,j)) intersected.insert(j);
        }

        return intersected;
    }

    template <typename T>
    inline bool fset<T>::any(T elem) { return this->find(elem) != this->end(); }

    template <typename T>
    inline fset<T> fset<T>::singleton(T element) { return fset<T>({element}); }

    template <typename T>
    T fset<T>::sum()
    {
        T sum = 0;

        for (auto const &i: *this) {
            sum += i;
        }
        return sum;
    }

    template <typename T>
    T fset<T>::product()
    {
        T product = 1;

        for (auto const &i: *this) {
            product *= i;
        }
        return product;
    }

    template <typename T>
    T fset<T>::min()
    {
    
    }

    template <typename T>
    T fset<T>::max()
    {
        
    }

    template <typename T>
    std::tuple<T,T> fset<T>::minmax()
    {
        
    }

    template <typename T>
    void fset<T>::foreach(std::function<void(T)> action)
    {
        for (auto const &i: *this) {
            action(i);
        }
    }

    template <typename T>
    template <typename U> fset<U> fset<T>::select(std::function<U(T)> selector)
    {
        fset<U> res;
        for (auto const &i: *this) {
            res.insert(selector(i));
        }
        return res;
    }

    template <typename T>
    fset<T> fset<T>::except(fset<T> other)
    {
        std::map<T,bool> m;
        fset<T> res;
        for (auto const &i: other) {
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: *this) {
            if (!map_contains(m,j)) res.insert(j);
        }

        return res;
    }

    template <typename T>
    fset<T> fset<T>::intersperse(T elem)
    {
        fset<T> new_set;
        
        for (auto start = this->begin(), last = this->end()-1;
            start != this->end(); ++start) {
            
            new_set.insert(*start);
            
            if (start != last)
                new_set.insert(elem);
        }
        
        return new_set;
    }

    template <typename T>
    inline bool fset<T>::map_contains(std::map<T,bool> m, T val)
    {
        return m.find(val) != m.end();
    }
}
