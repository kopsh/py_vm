# include "ArrayList.hpp"
# include <stdio.h>

/*
构造函数
*/
template <typename T>
ArrayList<T>::ArrayList(int n) {
    _length = n;
    _size = 0;
    _array = new T[n];
}

/*
扩展
*/
template <typename T>
void ArrayList<T>::expand() {
    _length <<= 1;
    T* _new_array = new T[_length];

    for (int i=0; i < _size; i++)
        _new_array[i] = _array[i];

    delete[] _array;
    _array = _new_array;

    printf("expand array length to %d\n", _length);
}

/*
追加元素
*/
template <typename T>
void ArrayList<T>::append(T t) {
    if (_size >= _length) {
        expand();
    }

    _array[_size++] = t;
}

/*
指定位置插入
*/
template <typename T>
void ArrayList<T>::insert(int index, T t) {
    append(NULL);

    for (int i=_size-1; i > index; i--)
        _array[i] = _array[i-1];

    _array[index] = t;

}

template <typename T>
T ArrayList<T>::get(int index) {
    return _array[index];
}

/*
指定位置设置元素
*/
template <typename T>
void ArrayList<T>::set(int index, T t) {
    if (_size <= index)
        _size = index + 1;

    while (_size > _length) 
        expand();

    _array[index] = t;
}

template <typename T>
int ArrayList<T>::size() {
    return _size;
}

template <typename T>
int ArrayList<T>::length() {
    return _length;
}

template <typename T>
T ArrayList<T>::pop() {
    return _array[--_size];
}

class HiObject;
template class ArrayList<HiObject*>;

class HiString;
template class ArrayList<HiString*>;

class HiInteger;
template class ArrayList<HiInteger*>;

class Block;
template class ArrayList<Block*>;