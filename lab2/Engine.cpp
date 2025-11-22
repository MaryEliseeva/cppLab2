#include "Engine.h"
#include <stdexcept>

int Engine::execute(const std::string& name, const std::map<std::string, int>& args) {
    auto it = commands.find(name);
    if (it != commands.end()) {
        return it->second(args);
    }
    else {
        throw std::runtime_error("Command not found: " + name);
    }
}
