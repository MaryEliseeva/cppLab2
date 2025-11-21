#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Subject {
    int f3(int arg1, int arg2) {
        return arg1 + arg2;
    }
};

template<typename T>
class Wrapper {
    T* obj;
    int(T::* method)(int, int);
    std::vector<std::string> arg_names;

public:
    Wrapper(T* obj, int(T::* method)(int, int), std::initializer_list<std::pair<std::string, int>> names)
        : obj(obj), method(method)
    {
        for (auto& p : names) {
            arg_names.push_back(p.first);
        }
    }

    int operator()(const std::map<std::string, int>& args_map) {
        return (obj->*method)(args_map.at(arg_names[0]), args_map.at(arg_names[1]));
    }
};

int main() {
    Subject subj;
    Wrapper<Subject> wrapper(&subj, &Subject::f3, { {"arg1",0},{"arg2",0} });

    std::map<std::string, int> args{ {"arg1",4},{"arg2",5} };
    std::cout << wrapper(args) << std::endl; // 9

    return 0;
}
