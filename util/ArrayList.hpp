template <typename T>
class ArrayList {
private:
    int _length;
    T*  _array;
    int _size;

    void expand();


public:
    ArrayList(int n = 8);

    void append(T t);
    void insert(int index, T t);
    T    get(int index);
    void set(int index, T t);
    int  size();
    int  length();
    T    pop();
    
    ~ArrayList() {
        delete[] _array;
    };
};