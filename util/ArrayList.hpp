# ifndef ARRAY_LIST_HPP
# define ARRAY_LIST_HPP
template <typename T>
class ArrayList {
private:
    int _length;
    T*  _array;
    int _size;

    void resize(int new_size);


public:
    ArrayList(int n = 8);
    ArrayList(const ArrayList<T>* other);

    void append(T t);
    void insert(int index, T t);
    T    get(int index);
    void set(int index, T t);
    int  size();
    int  length();
    T    pop();
    void delete_index(int index);

    ~ArrayList() {
        delete[] _array;
    };
};

class HiObject;
typedef ArrayList<HiObject*>* ObjList;

# endif