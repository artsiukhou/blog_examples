#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Initial version, C++11/14
void func1(int x) {
    cout << "invoked func1(int): " << x << endl;
}

void func2(int x, int y) {
    cout << "invoked func2(int, int): " << x << " " << y << endl;
}

void func3(double x, int y) {
    cout << "invoked func3(double, int): " << x << " " << y << endl;
}

void func4() {
    cout << "invoked func4()" << endl;
}

template <typename Func, typename ...Args>
void debugger(Func&& f, Args&&... args) {
    int dummy[sizeof...(Args)] = { (cout << args << " ", 0)... };
    if (sizeof...(Args) != 0) {
        cout << endl;
    }
    f(forward<Args>(args)...);
}

// Updated version, C++11/14
void printer() {
    cout << endl;
}

template <typename Head, typename ...Tail>
void printer(Head&& h, Tail&&... tail) {
    cout << h << " ";
    printer(tail...);
}

template <typename Func, typename ...Args>
void debugger_w_printer(Func&& f, Args&&... args) {
    if (sizeof...(Args) != 0) {
        printer(args...);
    }
    f(forward<Args>(args)...);
}


// C++17: constexpr if
template <typename Head, typename ...Tail>
void printer17(Head&& h, Tail&&... tail) {
    cout << h << " ";
    if constexpr (sizeof...(Tail) != 0) {
        printer17(tail...);
    } else {
        cout << endl;
    }
}

template <typename Func, typename ...Args>
void debugger_w_printer17(Func&& f, Args&&... args) {
    if constexpr (sizeof...(Args) != 0) {
        printer17(args...);
    }
    f(forward<Args>(args)...);
}

// C++17: fold expressions
template <typename Func, typename ...Args>
void debugger17(Func&& f, Args&&... args) {
    if constexpr (sizeof...(Args) != 0) {
        ((cout << args << " "), ...);
    }
    f(forward<Args>(args)...);
}

// C++17: join
template <typename ...Args>
string join(Args&&... args) {
    stringstream s;
    ((s << forward<Args>(args) << ","), ...);
    string result = s.str();
    result.pop_back();
    return result;
}

// C++17: push to vector
template <typename T, typename... Args>
void push_all(vector<T>& v, Args&&... args) {
    (v.push_back(args), ...);
}


int main()
{
    debugger(func1, 1);
    debugger(func2, 1, 2);
    debugger(func3, 1.4, 2);
    debugger(func4);
    cout << "------------" << endl;

    debugger_w_printer(func1, 1);
    debugger_w_printer(func2, 1, 2);
    debugger_w_printer(func3, 1.4, 2);
    debugger_w_printer(func4);
    cout << "------------" << endl;

    debugger_w_printer17(func1, 1);
    debugger_w_printer17(func2, 1, 2);
    debugger_w_printer17(func3, 1.4, 2);
    debugger_w_printer17(func4);
    cout << "------------" << endl;

    debugger17(func1, 1);
    debugger17(func2, 1, 2);
    debugger17(func3, 1.4, 2);
    debugger17(func4);
    cout << "------------" << endl;

    cout << join("hello") << endl;
    cout << join(12, "hello", -45.0, "world") << endl;

    vector<int> v;
    push_all(v, 10, 20, -100, 15);
    for (auto el : v) {
        cout << el << " "; 
    }
    cout << endl;

    return 0;
}
