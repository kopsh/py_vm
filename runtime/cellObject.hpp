# ifndef CELL_OBJECT_HPP
# define CELL_OBJECT_HPP

# include "object/Klass.hpp"
# include "object/HiObject.hpp"
# include "object/HiList.hpp"


class CellKlass : public Klass {
private:
    static CellKlass* instance;
    CellKlass();

public:
    static CellKlass* get_instance();
};

// 为了让闭包中的cell变量感知到其在函数外被修改，所以创建CellObject
// 使用传引用，而不是传值的方法
class CellObject : public HiObject {
friend class CellKlass;
private:
    HiList* _table; // 存储cell变量的closure表
    int _index; // cell变量在closure表中的位置

public:
    CellObject(HiList* table, int i): _table(table), _index(i) {}
    HiObject* value() { return _table->get(_index); }
};

# endif