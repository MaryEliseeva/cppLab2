#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <unordered_map>
#include <functional>

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


class Engine {
    std::unordered_map<std::string, std::function<int(const std::map<std::string, int>&)>> commands;

public:
    template<typename WrapperType>
    void register_command(WrapperType* wrapper, const std::string& name) {

        commands[name] = [wrapper](const std::map<std::string, int>& args) {
            return (*wrapper)(args);
            };
    }

    int execute(const std::string& name, const std::map<std::string, int>& args) {
        auto it = commands.find(name);
        if (it != commands.end()) {
            return it->second(args);
        }
        else {
            throw std::runtime_error("Command not found: " + name);
        }
    }
};


int main() {
    Subject subj;

    Wrapper<Subject, int, int, int> wrapper(
        &subj, &Subject::f3, { "arg1", "arg2" }
    );

    Engine engine;
    engine.register_command(&wrapper, "command1");

    std::map<std::string, int> args{ {"arg1", 4}, {"arg2", 5} };

    std::cout << engine.execute("command1", args) << std::endl; // 9

    return 0;
}
