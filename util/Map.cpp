# include "runtime/universe.hpp"
# include "util/ArrayList.hpp"
# include "util/Map.hpp"

template <typename K, typename V>
Map<K, V>::Map() {
    _entries = new MapEntry<K, V>[8];
    _size = 0;
    _length = 8;
}

template <typename K, typename V>
MapEntry<K, V>::MapEntry(const MapEntry<K, V>& entry) {
    _k = entry._k;
    _v = entry._v;
}

template <typename K, typename V>
void Map<K, V>::put(K k, V v) {
    for (int i = 0; i < _size; i++) {
        if (_entries[i]._k->equal(k) == Universe::HiTrue) {
            _entries[i]._v = v;
            return;
        }
    }

    expand();
    _entries[_size++] = MapEntry<K, V>(k, v);
}

template <typename K, typename V>
int Map<K, V>::index(K k) {
    for (int i = 0; i < _size; i++) {
        if (_entries[i]._k->equal(k) == Universe::HiTrue)
            return i;
    }

    return -1;
}

template <typename K, typename V>
K Map<K, V>::get_key(int index) {
    if (index >=0 and index < _size)
        return _entries[index]._k;
    
    return Universe::HiNone;
}

template <typename K, typename V>
bool Map<K, V>::has_key(K k) {
    int i = index(k);
    return i >= 0;
}

template <typename K, typename V>
V Map<K, V>::get(K k) {
    int i = index(k);
    if (i < 0)
        return Universe::HiNone;
    return _entries[i]._v;
}

template <typename K, typename V>
void Map<K, V>::expand() {
    if (_size == _length-1) {
        MapEntry<K, V>* temp = new MapEntry<K, V>[_length << 1];

        for (int i = 0; i <= _size; i++) {
            temp[i] = _entries[i];
        }

        _length <<= 1;
        delete[] _entries;
        _entries = temp;
    } 
}

template <typename K, typename V>
V Map<K, V>::remove(K k) {
    int i = index(k);
    if (i >= 0) {
        V v = _entries[i]._v;
        _entries[i] = _entries[--_size];
        return v;
    }
    return Universe::HiNone;
}

template class Map<HiObject*, HiObject*>;