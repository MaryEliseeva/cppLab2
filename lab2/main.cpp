#include "Engine.h"
#include "Wrapper.h"
#include "Subject.h"
#include <iostream>
#include <map>

void test_f0(Engine& engine, Subject& subj) {
    Wrapper<Subject, int> w0(&subj, &Subject::f0, {});
    engine.register_command(&w0, "cmd0");
    std::cout << "f0: " << engine.execute("cmd0", {}) << std::endl;
}

void test_f1(Engine& engine, Subject& subj) {
    Wrapper<Subject, int, int> w1(&subj, &Subject::f1, { "a" });
    engine.register_command(&w1, "cmd1");
    std::cout << "f1: " << engine.execute("cmd1", { {"a",5} }) << std::endl;
}

void test_f2(Engine& engine, Subject& subj) {
    Wrapper<Subject, int, int, int> w2(&subj, &Subject::f2, { "a","b" });
    engine.register_command(&w2, "cmd2");
    std::cout << "f2: " << engine.execute("cmd2", { {"a",3},{"b",7} }) << std::endl;
}

void test_f3(Engine& engine, Subject& subj) {
    Wrapper<Subject, int, int, int, int> w3(&subj, &Subject::f3, { "a","b","c" });
    engine.register_command(&w3, "cmd3");
    std::cout << "f3: " << engine.execute("cmd3", { {"a",1},{"b",2},{"c",3} }) << std::endl;
}

void test_f4(Engine& engine, Subject& subj) {
    Wrapper<Subject, int, int, int, int, int> w4(&subj, &Subject::f4, { "a","b","c","d" });
    engine.register_command(&w4, "cmd4");
    std::cout << "f4: " << engine.execute("cmd4", { {"a",2},{"b",3},{"c",1},{"d",4} }) << std::endl;
}

int main() {
    Subject subj;
    Engine engine;

    test_f0(engine, subj);
    test_f1(engine, subj);
    test_f2(engine, subj);
    test_f3(engine, subj);
    test_f4(engine, subj);

    return 0;
}
