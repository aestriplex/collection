/*
 *  collection/src/fset.h
 *  library: collection
 *
 *  Created by Nicoli Matteo on 07/06/2021.
 *  Copyright © 2021 Nicoli Matteo.
 */

#ifndef fset_h
#define fset_h

#include <set>

namespace fnc {

    template <typename T>
    class fset : public std::set<T> {
    
    public :
        fset();
        fset(std::set<T> s);
        inline std::set<T> to_set();
        fset<T> copy();
        fset<T> map(std::function<T(T)> f);
        fset<T> filter(std::function<bool(T)> predicate);
        fset<T> unite(fset<T> other);
        fset<T> intersecate(fset<T> other);
        bool any(T elem);
        fset<T> singleton(T element);
        T sum();
        T product();
        T min();
        T max();
        std::tuple<T,T> minmax();
        void foreach(std::function<void(T)> action);
        template <typename U> fset<U> select(std::function<U(T)> selector);
        fset<T> except(fset<T> other);
        fset<T> intersperse(T elem);
        
    
    private :
        inline bool map_contains(std::map<T,bool> m, T val);
    };

}

#include "fset.cc"

#endif
