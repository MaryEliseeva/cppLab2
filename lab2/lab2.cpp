#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

struct Subject {
    int f3(int arg1, int arg2) {
        return arg1 + arg2;
    }
};

template<typename T, typename ReturnType, typename... Args>
class Wrapper {
    T* obj;
    ReturnType(T::* method)(Args...);
    std::vector<std::string> arg_names;

public:
    Wrapper(T* obj, ReturnType(T::* method)(Args...), std::initializer_list<std::string> names)
        : obj(obj), method(method), arg_names(names) {
    }

    ReturnType operator()(const std::map<std::string, int>& args_map) {
        return invoke(args_map, std::index_sequence_for<Args...>{});
    }

private:
    template<std::size_t I>
    int get_arg(const std::map<std::string, int>& m) {
        return m.at(arg_names[I]);
    }

    template<std::size_t... Is>
    ReturnType invoke(const std::map<std::string, int>& m, std::index_sequence<Is...>) {
        return (obj->*method)(get_arg<Is>(m)...);
    }
};

int main() {
    Subject subj;

    Wrapper<Subject, int, int, int> wrapper(
        &subj, &Subject::f3, { "arg1", "arg2" }
    );

    std::map<std::string, int> args{ {"arg1", 4}, {"arg2", 5} };

    std::cout << wrapper(args) << std::endl; // 9
}
