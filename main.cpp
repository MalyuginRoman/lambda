#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Motivation

struct Lookup {
    explicit Lookup(int v) : m_value{v} {
    }

    void operator()(int entry) {
        if (entry == m_value) {
            cout << "Found!" << endl;
        } else {
            cout << "Not found!" << endl;
        }
    }

private:
    int m_value;
};

void lookupAndPrint(const vector<int> &values, int v) {
    for_each(values.begin(), values.end(), Lookup{v});
}

struct Closure {
    explicit Closure(int z_) : z(z_){}

    int operator()(int a, int b){
        return z + a + b;
    }

    int z;
};

// Basic
void example_1() {
    Closure cl(100);
    cout << cl(1, 2) << endl;
}

// Easy
void example_2(){
    cout << Closure(100)(1, 2) << endl;
}

struct Closure2 {
    explicit Closure2(int z_) : z(z_){}

    int operator()(int a, int b) {
        return z + a + b;
    }
private:
    int z;
};

// Middle
void example_3() {
    auto closure = [z = 100](int a, int b) { return z + a + b; };
    cout << closure(1, 2) << endl;

    auto closure2 = [](int a, int b, int c) {
        return a + b + c;
    };
    cout << closure2(1, 2, 3) << endl;

}

// Hard
void example_4() {

    cout << [z = 100](int a, int b) { return z + a + b; }(1,2) << endl;

    vector<int> values = {0, 1, 2, 3, 3, 3, 4, 5, 6};
    for_each(
                values.begin(),
                values.end(),
                [value = 3](int entry) {
        if (entry == value)
            cout << "Found!" << endl;
    });

    int value = 3;
    for_each(
                values.begin(),
                values.end(),
                [value](int entry) {
        if (entry == value)
            cout << "Found!" << endl;
    });

    auto closure = [z = 100](int a, int b) mutable -> int {
        z = 150;
        return a + b + z;
    };
    cout << closure(1, 2) << endl;

    auto closure2 = [z = 100](int a1, int a2) mutable -> decltype(a1 + a2) {
        z = 150;
        return a1 + a2 + z;
    };
    cout << closure2(2, 3) << endl;

    auto closure3 = [](auto a1, auto a2) { return a1 + a2; };
    cout << closure3(1.5, 2.7) << endl;

    cout << "value = " << value << endl;
    auto closure4 = [&value]() { value = 100; };
    closure4();
    cout << "value = " << value << endl;
}


int main(int ac, char **av)
{
    vector<int> values = {0, 1, 2, 3, 3, 3, 4, 5, 6};
    lookupAndPrint(values, 3);

    example_1();
    example_2();
    example_3();
    example_4();
}
