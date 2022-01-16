/*
 *  collection/src/fvec.h
 *  library: collection
 *
 *  Created by Nicoli Matteo on 07/06/2021.
 *  Copyright © 2021 Nicoli Matteo.
 */

#ifndef fvec_h
#define fvec_h

#include <vector>
#include <map>
#include <tuple>



namespace fnc {

    template <typename T>
    class fvec : public std::vector<T> {
    
    public :
        /*
         *
         */
        fvec();
        
        /*
         *
         */
        fvec(std::vector<T> v);

        /*
         *
         */
        inline std::vector<T> to_vector();

        /*
         * `head` returns the first element of the fvec.
         */
        inline T head();

        /*
         * `drop` drops the first n elements of the fvec.
         */
        fvec<T> drop(int n);

        /*
         * `tail` returns the fvec with the first element dropped.
         */
        fvec<T> tail();

        /*
         * `init` returns the fvec with the last element dropped.
         */
        fvec<T> init();

        /*
         * `last` returns the last element of the fvec.
         */
        inline T last();

        /*
         * `take` returns the first n elements of the fvec.
         */
        fvec<T> take(int n);

        /*
         * `copy` returns a copy of the fvec.
         */
        fvec<T> copy();

        /*
         * - f : a function;
         * - base : a starting value (typically the right-identity of the
         *          function;
         * `foldr`reduces the list by applying `f` in a right-associative way
         *
         * Example:
         *
         *     fvec<int> vec({1,2,3,4});
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
         *     fvec<int> vec({1,2,3,4});
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

        /*
         *
         */
        fvec<T> scanr(std::function<T(T,T)> f, T base);

        /*
         *
         */
        fvec<T> scanl(std::function<T(T,T)> f, T base);

        /*
         * `group_by` returns a an fvec of fvec, grouped by the predicate `f`
         *
         * Example:
         *
         *    
         */
        fvec<fvec<T> > group_by(std::function<bool(T,T)> f);

        /*
         * `group` is just a shortcut for:
         *  
         *    group([](int x, int y) {return x == y; })
         */
        
        fvec<fvec<T> > group();

        /*
         * `map` applies to each element of the fvec the function
         *
         *    f: T --> T
         *
         * and then returns the fvec of mapped elements.
         */
        fvec<T> map(std::function<T(T)> f);

        /*
         * `filter` returns an fvec with the elements that fullfill the
         * predicate function
         *
         *    f: T --> bool
         */
        fvec<T> filter(std::function<bool(T)> predicate);

        /*
         * `zip` takes two lists and returns an fvec of corresponding pairs. 
         * The length of the fvec is equal to the length of the shortest fvec.
         */
        fvec<fvec<T> > zip(fvec<T> other);

        /*
         * `zip_with` does the same as `zip`, but you have to specify the
         * comparator function (recommended for custom objects)
         */
        fvec<T> zip_with(fvec<T> other, std::function<bool(T,T)> f);

        /*
         * `concat` appends the 
         */
        fvec<T> concat(fvec<T> other);

        /*
         * 
         */
        fvec<fvec<T> > inits();

        /*
         * 
         */
        fvec<fvec<T> > tails();

        /*
         * 
         */
        fvec<T> unite(fvec<T> other);

        /*
         * 
         */
        fvec<T> intersecate(fvec<T> other);

        /*
         * 
         */
        fvec<T> distinct();

        /*
         * 
         */
        inline bool any(T elem);

        /*
         * 
         */
        inline fvec<T> singleton(T element);

        /*
         * 
         */
        fvec<T> reverse();

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
        //std::tuple<T,T> minmax();

        /*
         * 
         */
        void foreach(std::function<void(T)> action);

        /*
         * 
         */
        template <typename U> fvec<U> select(std::function<U(T)> selector);

        /*
         * 
         */
        fvec<T> except(fvec<T> other);

        /*
         * 
         */
        fvec<T> sort(std::function<bool(T,T)> comparator);

        /*
         * 
         */
        fvec<T> sort();

        /*
         * 
         */
        fvec<T> sort_heap(std::function<bool(T,T)> comparator);

        /*
         * 
         */
        fvec<T> sort_heap();

        /*
         * 
         */
        fvec<T> intersperse(T elem);

        /*
         * 
         */
        fvec<T> rotate_left(int n_positions);

        /*
         * 
         */
        fvec<T> shuffle();
    
    private :
        inline bool map_contains(std::map<T,bool> m, T val);
    };

    fvec<int> vrange(int start, int stop, int step);
    inline fvec<int> vrange(int stop, int step);
    template <typename T> fvec<T> cycle(fvec<T> vec, int n);
    
}
#include "fvec.cc"

#endif
