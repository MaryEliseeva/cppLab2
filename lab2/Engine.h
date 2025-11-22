#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory> 

class Engine {
public:
    Engine();
    ~Engine();

    template<typename WrapperType>
    void register_command(WrapperType* wrapper, const std::string& name) {
        impl_->commands[name] = [wrapper](const std::map<std::string, int>& args) {
            return (*wrapper)(args);
            };
    }

    int execute(const std::string& name, const std::map<std::string, int>& args);

private:
    struct Impl {
        std::unordered_map<std::string, std::function<int(const std::map<std::string, int>&)>> commands;
    };

    std::unique_ptr<Impl> impl_;
};

#endif // ENGINE_H
