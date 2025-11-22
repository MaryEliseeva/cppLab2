#include "Engine.h"
#include <stdexcept>

Engine::Engine() : impl_(std::make_unique<Impl>()) {}
Engine::~Engine() = default;

int Engine::execute(const std::string& name, const std::map<std::string, int>& args) {
    auto it = impl_->commands.find(name);
    if (it != impl_->commands.end()) return it->second(args);
    throw std::runtime_error("Command not found");
}
