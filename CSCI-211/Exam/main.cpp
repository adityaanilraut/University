#include <iostream>
using namespace std;

class Animal {
public:
    virtual void makeSound() const=0 ;
};

class Dog : public Animal {
public:
    void makeSound() const override {
        cout << "The dog barks" << endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() const override {
        cout << "The cat meows" << endl;
    }
};

class Bird : public Animal {
public:
    void makeSound() const override {
        cout << "The bird sings" << endl;
    }
};

int main() {
    Animal *animals[] = {new Dog(), new Cat(), new Bird()};

    for (Animal *animal : animals) {
        animal->makeSound();
    }

    delete[] *animals;

    return 0;
}