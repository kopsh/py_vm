# include "ArrayList.hpp"
# include "runtime/universe.hpp"

# include <stdio.h>
# include "string.h"

/*
构造函数
*/
template <typename T>
ArrayList<T>::ArrayList(int n) {
    _length = n;
    _size = 0;
    _array = new T[n];
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>* other) {
    _length = other->_length;
    _size = other->_size;
    _array = new T[_length];

    for (int i=0; i < _length; i++) {
        _array[i] = other->_array[i];
    }
}

/*
扩展
*/
// template <typename T>
// void ArrayList<T>::expand() {
//     _length <<= 1;
//     T* _new_array = new T[_length];

//     for (int i=0; i < _size; i++)
//         _new_array[i] = _array[i];

//     delete[] _array;
//     _array = _new_array;

//     printf("expand array length to %d\n", _length);
// }


template <typename T>
void ArrayList<T>::resize(int new_size) {
    if (new_size <= _length && (_length <=8 || new_size >= _length / 2))
        return;

    _length = (new_size >> 3) + (new_size < 9 ? 3 : 6);
    _length += new_size;

    T* _new_array = new T[_length];

    for (int i=0; i < _size; i++)
        _new_array[i] = _array[i];

    delete[] _array;
    _array = _new_array;

    printf("resize array length to %d\n", _length);
}

/*
追加元素
*/
template <typename T>
void ArrayList<T>::append(T t) {
    resize(_size+1);
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
    resize(_size);
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
    resize(_size-1);
    return _array[--_size];
}

template <typename T>
void ArrayList<T>::delete_index(int index) {
    for (int i=index; i < _size; i++) {
        _array[i] = _array[i+1];    
    }
    resize(--_size);
}

template <typename T>
T ArrayList<T>::top() {
    return _array[_size-1];
}

template <>
int ArrayList<HiObject*>::index(HiObject* t) {
    for (int i = 0; i < _size; i++) {
        if (_array[i]->equal(t) == Universe::HiTrue) {
            return i;
        }
    }

    return -1;
}

class HiObject;
template class ArrayList<HiObject*>;

class HiString;
template class ArrayList<HiString*>;

class HiInteger;
template class ArrayList<HiInteger*>;

class Block;
template class ArrayList<Block*>;

template class ArrayList<int>;