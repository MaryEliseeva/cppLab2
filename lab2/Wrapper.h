#ifndef WRAPPER_H
#define WRAPPER_H

#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <utility>

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

#endif // WRAPPER_H
