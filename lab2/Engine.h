#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>
#include <unordered_map>
#include <functional>

class Engine {
    std::unordered_map<std::string, std::function<int(const std::map<std::string, int>&)>> commands;

public:
    template<typename WrapperType>
    void register_command(WrapperType* wrapper, const std::string& name) {
        commands[name] = [wrapper](const std::map<std::string, int>& args) {
            return (*wrapper)(args);
            };
    }

    int execute(const std::string& name, const std::map<std::string, int>& args);
};

#endif // ENGINE_H
