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

        /*
         * `copy` returns a copy of the fset.
         */
        fset<T> copy();

        /*
         * `map` applies to each element of the fset the function
         *
         *    f: T --> T
         *
         * and then returns the fset of mapped elements.
         */
        fset<T> map(std::function<T(T)> f);

        /*
         * `filter` returns an fset with the elements that fullfill the
         * predicate function
         *
         *    f: T --> bool
         */
        fset<T> filter(std::function<bool(T)> predicate);

        fset<T> unite(fset<T> other);

        fset<T> intersecate(fset<T> other);

        bool any(T elem);

        fset<T> singleton(T element);

        /*
         * `sum` returns the sum of the elements.
         * WARNING: T must implement the operator (+)
         */
        T sum();

        /*
         * `product` returns the product of the elements.
         * WARNING: T must implement the operator (*)
         */
        T product();

        /*
         * `min` returns the minimum of the elements.
         * WARNING: T must implement the operator (<=)
         */
        T min();

        /*
         * `min` returns the maximum of the elements.
         * WARNING: T must implement the operator (>=)
         */
        T max();

        /*
         * `minmax` returns the tuple <min,max>.
         * WARNING: T must implement both (<=) and (>=)
         */
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
