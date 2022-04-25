/*
 *  collection/src/flist.h
 *  library: collection
 *
 *  Created by Nicoli Matteo on 07/06/2021.
 *  Copyright © 2021 Nicoli Matteo.
 */

#ifndef flist_h
#define flist_h

#include <list>
#include <map>
#include <tuple>
#include <functional>


namespace fnc {

    template <typename T>
    class flist : public std::list<T> {
    
    public :
        flist();

        flist(std::list<T> l);

        inline std::list<T> to_list();

        /*
         * `head` returns the first element of the flist.
         */
        inline T head();

        /*
         * `drop` drops the first n elements of the flist.
         */
        flist<T> drop(int n);

        /*
         * `tail` returns the flist with the first element dropped.
         */
        flist<T> tail();

        /*
         * `init` returns the flist with the last element dropped.
         */
        flist<T> init();

        /*
         * `last` returns the last element of the flist.
         */
        inline T last();

        /*
         * `take` returns the first n elements of the flist.
         */
        flist<T> take(int n);

        /*
         * `copy` returns a copy of the flist.
         */
        flist<T> copy();

        /*
         * - f : a function;
         * - base : a starting value (typically the right-identity of the
         *          function;
         * `foldr`reduces the list by applying `f` in a right-associative way
         *
         * Example:
         *
         *     flist<int> vec({1,2,3,4});
         *     int fold = vec.foldr([](intx, inty) {return x+y; }, 0);
         *
         * Given the vector of integers from 1 to 4, `foldr` applies `f` to
         * the vector in the following way:
         *
         *     int fold = f1(1, f(2, f(3, f(4,0)))); 
         * 
         * i.e.
         *
         *    int fold = 1 + (2 + (3 + (4 + 0)));
         */
        T foldr(std::function<T(T,T)> f, T base);

        /*
         * - f : a function;
         * - base : a starting value (typically the left-identity of the
         *          function;
         * `foldr`reduces the list by applying `f` in a left-associative way
         *
         * Example:
         *
         *     flist<int> vec({1,2,3,4});
         *     int fold = vec.foldl([](intx, inty) {return x+y; }, 0);
         *
         * Given the vector of integers from 1 to 4, `foldl` applies `f` to
         * the vector in the following way:
         *
         *     int fold = f(f(f(f(0,1), 2), 3), 4); 
         * 
         * i.e.
         *
         *    int fold = (((0 + 1) + 2) + 3) + 4;
         */
        T foldl(std::function<T(T,T)> f, T base);

        flist<T> scanr(std::function<T(T,T)> f, T base);

        flist<T> scanl(std::function<T(T,T)> f, T base);

        /*
         * `group_by` returns an flist of flist, grouped by the predicate `f`
         *
         * Example:
         *
         *    
         */
        flist<flist<T>> group_by(std::function<bool(T,T)> f);

        /*
         * `group` is just a shortcut for:
         *  
         *    group_by([](int x, int y) {return x == y; })
         */
        flist<flist<T>> group();

        /*
         * `map` applies to each element of the flist the function
         *
         *    f: T --> T
         *
         * and then returns the flist of mapped elements.
         */
        flist<T> map(std::function<T(T)> f);

        /*
         * `filter` returns an flist with the elements that fullfill the
         * predicate function
         *
         *    f: T --> bool
         */
        flist<T> filter(std::function<bool(T)> predicate);

        /*
         * `zip` takes two lists and returns an flist of corresponding pairs. 
         * The length of the flist is equal to the length of the shortest flist.
         */
        flist<flist<T>> zip(flist<T> other);

        /*
         * `zip_with` does the same as `zip`, but you have to specify the
         * comparator function (recommended for custom objects)
         */
        flist<T> zip_with(flist<T> other, std::function<bool(T,T)> f);

        flist<T> concat(flist<T> other);

        flist<flist<T>> inits();

        flist<flist<T>> tails();

        flist<T> unite(flist<T> other);

        flist<T> intersecate(flist<T> other);

        flist<T> distinct();

        inline bool any(T elem);

        inline flist<T> singleton(T element);

        flist<T> reverse();

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

        template <typename U> flist<U> select(std::function<U(T)> selector);

        flist<T> except(flist<T> other);

        flist<T> sort(std::function<bool(T,T)> comparator);

        flist<T> sort();

        flist<T> sort_heap(std::function<bool(T,T)> comparator);

        flist<T> sort_heap();

        flist<T> intersperse(T elem);

        flist<T> rotate_left(int n_positions);

        flist<T> shuffle();
        
    private :
        inline bool map_contains(std::map<T,bool> m, T val);
        
    };

    flist<int> lrange(int start, int stop, int step);
    inline flist<int> lrange(int stop, int step);
    template <typename T> flist<T> cycle(flist<T> vec, int n);

}

#include "flist.cc"

#endif
