#include "Engine.h"
#include <unordered_map>
#include <stdexcept>

struct Engine::Impl {
    std::unordered_map<std::string, std::function<int(const std::map<std::string, int>&)>> commands;
};

Engine::Engine(): impl_(std::make_unique<Impl>()){}

Engine::~Engine() = default;

void Engine::register_command(const std::string& name, std::function<int(const std::map<std::string, int>&)> fn) {
    impl_->commands[name] = std::move(fn);
}

int Engine::execute(const std::string& name,
    const std::map<std::string, int>& args) {
    auto it = impl_->commands.find(name);
    if (it != impl_->commands.end())
        return it->second(args);
    throw std::runtime_error("Command not found");
}