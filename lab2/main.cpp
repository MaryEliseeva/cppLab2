#include "Engine.h"
#include "Wrapper.h"
#include "Subject.h"
#include <iostream>
#include <map>

int main() {
    Subject subj;

    Wrapper<Subject, int, int, int> wrapper(&subj, &Subject::f3, { "arg1", "arg2" });

    Engine engine;
    engine.register_command(&wrapper, "command1");

    std::map<std::string, int> args{ {"arg1", 4}, {"arg2", 5} };

    std::cout << engine.execute("command1", args) << std::endl; // 9

    return 0;
}
