//
// Created by artyom on 10/3/19.
//

#ifndef GRAPHIC_MEMORY_HPP
#define GRAPHIC_MEMORY_HPP
#include <cstring>
#include <initializer_list>
#include "type/traits.hpp"

namespace grbus
{

template<typename T>
void memcpy(T* to, const T* from, int count)
{
    if (std::is_pod<T>::value)
    {
        std::memcpy(to, from, count * sizeof(T));
    }
    else
    {
        for (int i = 0; i != count; ++i)
        {
            to[i] = from[i];
        }
    }
}


template <typename T>
void insert_flattened(const T* first,const T* last,T*& to)
{
    //std::cout<<"insert_flattened(const T* first,const T* last)"<<std::endl;
    std::memcpy(to, first, (last-first)*sizeof(T));
    to+=(last-first);
}


template <typename T,typename V>
void insert_flattened(const std::initializer_list<T>* first, const std::initializer_list<T>* last,V*& to) {
    //std::cout<<"insert_flattened(const std::initializer_list<T>* first, const std::initializer_list<T>* last"<<std::endl;
    while (first != last) {
        insert_flattened(first->begin(), first->end(),to);
        first++;
    }
}


template <typename T,typename V>
void insert_flattened(const std::initializer_list<T> &list,V* to)
{
    //std::cout<<"insert_flattened(const std::initializer_list<T> &list,V* to)"<<std::endl;
    insert_flattened(list.begin(),list.end(),to);
}

}
#endif //GRAPHIC_MEMORY_HPP
