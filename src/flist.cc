/*
 *  collection/src/flist.cc
 *  library: collection
 *
 *  Created by Nicoli Matteo on 07/06/2021.
 *  Copyright © 2021 Nicoli Matteo.
 */

#include <iostream>
#include <list>
#include <map>
#include <tuple>
#include <random>
#include <chrono>

namespace fnc {

    flist<int> lrange(int start, int stop, int step = 1)
    {
        flist<int> l;
        
        if (start <= stop) {
            for (int i = start; i < stop; i += step)
                l.push_back(i);
        } else {
            for (int i = start; i > stop; i -= step) 
                l.push_back(i);
        }

        return l;
    }

    inline flist<int> lrange(int stop, int step = 1) { return lrange(0,stop,step); }

    template <typename T>
    flist<T> cycle(flist<T> list, int n)
    {
        if (list.empty()) throw "ERROR: empty vector";
        if (n < 0) throw "n must be greater (or equal) than 0";
        
        flist<T> new_list;
        for (int i = 0; i < n; ++i) {
            for (auto const &i: list) {
                new_list.push_back(i);
            }
        }
        
        return new_list;
    }

    template <typename T>
    flist<T>::flist() : std::list<T>() {}

    template <typename T>
    flist<T>::flist(std::list<T> l) : std::list<T>(l) {}

    template <typename T>
    inline std::list<T> flist<T>::to_list() { return *this; }

    template <typename T>
    inline T flist<T>::head() { return this->front(); }

    template <typename T>
    flist<T> flist<T>::drop(int n)
    {
        flist<T> list;
        
        if (this->empty()) return list;
        
        for (auto first = this->begin()+n; first != this->end(); ++first) {
            list.push_back(*first);
        }
        return list;
    }

    template <typename T>
    flist<T> flist<T>::tail() { return this->drop(1); }

    template <typename T>
    flist<T> flist<T>::init()
    {
        flist<T> new_list(*this);
        new_list.pop_back();
        return new_list;
    }

    template <typename T>
    inline T flist<T>::last()
    {
        return *(this->end()-1);
    }

    template <typename T>
    flist<T> flist<T>::take(int n)
    {
        flist<T> new_list;
        int counter = 0;
        for (auto const &i: *this) {
            if (counter == n) break;
            new_list.push_back(i);
            counter++;
        }
        return new_list;
    }

    template <typename T>
    flist<T> flist<T>::copy()
    {
        flist<T> new_list;
        for (auto const &i: *this) {
            new_list.push_back(i);
        }
        return new_list;
    }

    template <typename T>
    T flist<T>::foldr(std::function<T(T,T)> f, T base)
    {
        if (this->empty()) return base;
        return f(this->head(),this->tail().foldr(f,base));
    }

    template <typename T>
    T flist<T>::foldl(std::function<T(T,T)> f, T base)
    {
        if (this->empty()) return base;
        return this->tail().foldl(f,f(base,this->head()));
    }

    template <typename T>
    flist<T> flist<T>::scanr(std::function<T(T,T)> f, T base)
    {
        flist<T> list;
        auto tails = this->tails();
        for (flist<T> &i: tails) {
            list.push_back(i.foldr(f,base));
        }
        list.push_back(base);
        
        return list;
    }

    template <typename T>
    flist<T> flist<T>::scanl(std::function<T(T,T)> f, T base)
    {
        flist<T> list({base});
        auto inits = this->inits();
        for (flist<T> &i: inits) {
            list.push_back(i.foldl(f,base));
        }
        
        return list;
    }

    template <typename T>
    flist<flist<T> > flist<T>::group()
    {
        flist<flist<T> > grouped;
        std::map<T,int> m;
        for (auto const &e : *this) {
            if (map_contains(m,e)) 
                m[e]++;
            else
                m[e] = 1;
        }

        for (auto const& x : m) {
            flist<T> group;
            for (int i = 0; i < x.second; i++) {
                group.push_back(x.first);
            }
            grouped.push_back(group);
        }
        return grouped;
    }

    template <typename T>
    flist<flist<T> > flist<T>::clusterize_by(std::function<bool(T,T)> f)
    {
        flist<flist<T> > clusterized;
        auto i = this->begin();
        
        while(i != this->end()) {
            flist<T> tmp;
            tmp.push_back(*i);
            while (f(*i,*(i+1))) {
                tmp.push_back(*i);
                ++i;
            }
            ++i;
            clusterized.push_back(tmp);
        }
        
        return clusterized;
    }
    
    template <typename T>
    flist<flist<T> > flist<T>::clusterize()
    {
        return this->clusterize_by([](T x, T y) { return x == y; });
    }

    template <typename T>
    flist<T> flist<T>::map(std::function<T(T)> f)
    {
        flist<T> list;
        for (auto const &i: *this) {
                list.push_back(f(i));
        }
        return list;
    }

    template <typename T>
    flist<T> flist<T>::filter(std::function<bool(T)> predicate)
    {
        flist<T> list;
        for (auto const &i: *this) {
            if (predicate(i))
                list.push_back(i);
        }
        return list;
    }

    template <typename T>
    flist<flist<T> > flist<T>::zip(flist<T> other)
    {
        flist<flist<T> > result;
        
        for (auto first = this->begin(), second = other.begin();
            first != this->end() && second != other.end();
            ++first,++second) {
            flist<T> tmp;
            tmp.push_back(*first);
            tmp.push_back(*second);
            result.push_back(tmp);
        }
        return result;                    
    }

    template <typename T>
    flist<T> flist<T>::zip_with(flist<T> other, std::function<bool(T,T)> f)
    {
        flist<T> result;
        
        for (auto first = this->begin(), second = other.begin();
            first != this->end() && second != other.end();
            ++first,++second) {
            result.push_back(f(*first,*second));
        }
        
        return result;
    }

    template <typename T>
    flist<T> flist<T>::concat(flist<T> other)
    {
        flist<T> list(*this);
        for (auto const &i: other) {
            list.push_back(i);
        }
        
        return list;
    }

    template <typename T>
    flist<flist<T> > flist<T>::inits()
    {
        flist<flist<T> > new_list;
        
        if (this->empty()) return new_list;
        
        new_list.push_back(*this);
        return this->init().inits().concat(new_list);
    }


    template <typename T>
    flist<flist<T> > flist<T>::tails()
    {
        flist<flist<T> > new_list;
        
        if (this->empty()) return new_list;
        
        new_list.push_back(*this);
        return new_list.concat(this->tail().tails());
    }

    template <typename T>
    flist<T> flist<T>::unite(flist<T> other)
    {
        std::map<T,bool> m;
        flist<T> united;
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
    flist<T> flist<T>::intersecate(flist<T> other)
    {
        std::map<T,bool> m;
        flist<T> intersected;
        for (auto const &i: *this) {
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: other) {
            if (map_contains(m,j)) intersected.push_back(j);
        }

        return intersected;
    }

    template <typename T>
    flist<T> flist<T>::distinct()
    {
        std::map<T,bool> m;
        flist<T> new_list;
        for (auto const &i: *this) {
            if (!map_containsKey(m,i)) {
                m[i] = true;
                new_list.push_back(i);
            }
        }
        return new_list;
    }

    template <typename T>
    inline bool flist<T>::any(T elem) { return this->find(elem) != this->end(); }

    template <typename T>
    inline flist<T> flist<T>::singleton(T element) { return flist<T>({element}); }

    template <typename T>
    flist<T> flist<T>::reverse()
    {
        std::list<T> new_list(*this);
        new_list.reverse();
        return new_list;
    }

    template <typename T>
    T flist<T>::sum()
    {
        T sum = 0;

        for (auto const &i: *this) {
            sum += i;
        }
        return sum;
    }

    template <typename T>
    T flist<T>::product()
    {
        T product = 1;

        for (auto const &i: *this) {
            product *= i;
        }
        return product;
    }

    template <typename T>
    T flist<T>::min()
    {
        //if (this->size() == 0)
        if (this->size() == 1) return this->head();
        return std::min(this->head(),this->tail().min());
    }

    template <typename T>
    T flist<T>::max()
    {
        //if (this->size() == 0)
        if (this->size() == 1) return this->head();
        return std::max(this->head(),this->tail().max());
    }

    template <typename T>
    std::tuple<T,T> flist<T>::minmax()
    {
        return std::make_tuple(this->min(),this->max);
    }

    template <typename T>
    void flist<T>::foreach(std::function<void(T)> action)
    {
        for (auto const &i: *this) {
            action(i);
        }
    }

    template <typename T>
    template <typename U>
    flist<U> flist<T>::select(std::function<U(T)> selector)
    {
        flist<U> res;
        for (auto const &i: *this) {
            res.push_back(selector(i));
        }
        return res;
    }

    template <typename T>
    flist<T> flist<T>::except(flist<T> other)
    {
        std::map<T,bool> m;
        flist<T> res;
        for (auto const &i: other) {
            if (! map_contains(m,i)) m[i] = true;
        }
        for (auto const &j: *this) {
            if (!map_contains(m,j)) res.push_back(j);
        }

        return res;
    }

    template <typename T>
    flist<T> flist<T>::sort(std::function<bool(T,T)> comparator)
    {
        std::list<T> sorted(*this);
        sorted.sort(comparator);
        return sorted;
    }

    template <typename T>
    flist<T> flist<T>::sort()
    {
        return this->sort([](T x,T y) { return x <= y; });
    }

    template <typename T>
    flist<T> flist<T>::sort_heap(std::function<bool(T,T)> comparator)
    {
        flist<T> sorted(*this);
        std::sort_heap(sorted.begin(),sorted.end(),comparator);
        return sorted;
    }

    template <typename T>
    flist<T> flist<T>::sort_heap()
    {
        return this->sort_heap([](T x,T y) { return x <= y; });
    }

    template <typename T>
    flist<T> flist<T>::intersperse(T elem)
    {
        flist<T> new_vector;
        
        for (auto start = this->begin(), last = this->end()-1;
            start != this->end(); ++start) {
            
            new_vector.push_back(*start);
            
            if (start != last)
                new_vector.push_back(elem);
        }
        
        return new_vector;
    }

    template <typename T>
    flist<T> flist<T>::rotate_left(int n_positions)
    {
        std::list<T> new_list(*this);
        std::rotate(new_list.begin(),new_list.begin()+n_positions,new_list.end());

        return new_list;
    }

    template <typename T>
    flist<T> flist<T>::shuffle()
    {
        flist<T> new_list(*this);

        auto seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle (new_list.begin(), new_list.end(), std::default_random_engine(seed));
        
        return new_list;
    }


    template <typename T>
    template <typename U>
    inline bool flist<T>::map_contains(std::map<T,U> m, T val)
    {
        return m.find(val) != m.end();
    }
}
