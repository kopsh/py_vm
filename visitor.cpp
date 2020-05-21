#include <iostream>
#include <stdio.h>
using namespace std;

class Visitor;

class Animal {
public:
    virtual void accept(Visitor *v) {cout << "emmm..." << endl;};
};

class Dog : public Animal {
public:
    virtual void accept(Visitor *v);
};

class Cat : public Animal {
public:
    virtual void accept(Visitor *v);
};

class Fox : public Animal {
public:
    virtual void accept(Visitor *v);
};

class Visitor {
public:
    void visit(Animal * animal) {}
    virtual void visit(Dog * dog) {}
    virtual void visit(Cat * cat) {}
    virtual void visit(Fox * fox) {}
};

class Speaker : public Visitor {
public:
    void visit(Animal * pa) {
        pa->accept(this);
    };

    void visit(Dog * pd) {
        cout << "wang" << endl;
    };

    void visit(Cat * pc) {
        cout << "miao" << endl;
    };

    void visit(Fox * pf) {
        cout << "woo" << endl;
    };
};

void Dog::accept(Visitor * v) {
    v->visit(this);
}

void Cat::accept(Visitor * v) {
    v->visit(this);
}

void Fox::accept(Visitor * v) {
    v->visit(this);
}

int main() {
    Animal * animals[] = {new Dog(), new Cat(), new Fox()};
    Speaker s;
    for (int i = 0; i < sizeof(animals)/sizeof(Animal *); i++) {
        s.visit(animals[i]);
    }

    return 0;
}