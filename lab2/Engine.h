#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <memory>
#include <string>
#include <functional>

class Engine {
public:
    Engine();
    ~Engine();

    void register_command( const std::string& name, std::function<int(const std::map<std::string, int>&)> fn);

    int execute(const std::string& name, const std::map<std::string, int>& args);

    template<typename WrapperType>
    void register_command(WrapperType* wrapper, const std::string& name) {
        register_command(name, [wrapper](const auto& args) {
            return (*wrapper)(args);
            });
    }

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

#endif // ENGINE_H