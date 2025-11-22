#ifndef SUBJECT_H
#define SUBJECT_H

struct Subject {
    int f0() {
        return 42; 
    }

    int f1(int a) {
        return a * 2; 
    }

    int f2(int a, int b) {
        return a + b; 
    }

    int f3(int a, int b, int c) {
        return a + b + c; 
    }

    int f4(int a, int b, int c, int d) {
        return a * b - c + d; 
    }
};

#endif // SUBJECT_H
