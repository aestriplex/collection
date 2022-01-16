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
        inline T head();
        flist<T> drop(int n);
        flist<T> tail();
        flist<T> init();
        inline T last();
        flist<T> take(int n);
        flist<T> copy();
        T foldr(std::function<T(T,T)> f, T base);
        T foldl(std::function<T(T,T)> f, T base);
        flist<T> scanr(std::function<T(T,T)> f, T base);
        flist<T> scanl(std::function<T(T,T)> f, T base);
        flist<flist<T>> group_by(std::function<bool(T,T)> f);
        flist<flist<T>> group();
        flist<T> map(std::function<T(T)> f);
        flist<T> filter(std::function<bool(T)> predicate);
        flist<flist<T>> zip(flist<T> other);
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
        T sum();
        T product();
        T min();
        T max();
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
