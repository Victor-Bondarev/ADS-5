// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"


int pr(char x) {
    if (x == '(')
        return 0;
    else if (x == ')')
        return 1;
    else if (x == '-' || x == '+')
        return 2;
    else if (x == '/' || x == '*')
        return 3;
    return -1;
}

int numb(char x) {
    return (x <= '9' && x >= '0');
}

int op(char x) {
    return (x == '-' || x == '+' || x == '/' || x == '*');
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> s1;
    std::string st = "";
    for (int i = 0; i < inf.length(); i++) {
        if (numb(inf[i])) {
            st += inf[i];
            st += " ";
        } else if (inf[i] == '(') {
            s1.push(inf[i]);
        } else if (inf[i] == ')') {
            while (!s1.isEmpty() && s1.get() != '(') {
                st += s1.get();
                st += " ";
                s1.pop();
            }
            s1.pop();
        } else if (op(inf[i])) {
            while (!s1.isEmpty() && pr(inf[i]) <= pr(s1.get())) {
                st += s1.get();
                st += " ";
                s1.pop();
            }
            s1.push(inf[i]);
        }
    }
    while (!s1.isEmpty()) {
        st += s1.get();
        st += " ";
        s1.pop();
    }
    st.erase(st.length() - 1);
    return st;
}

int eval(std::string post) {
    TStack<int, 100> s2;
    for (int i = 0; i < post.length(); i++) {
        if (post[i] == ' ') {
            continue;
        } else if (numb(post[i])) {
            int n = post[i] - '0';
            s2.push(n);
        } else if (op(post[i])) {
            int n2 = s2.get();
            s2.pop();
            int n1 = s2.get();
            s2.pop();
            if (post[i] == '-') {
                s2.push(n1 - n2);
            } else if (post[i] == '+') {
                s2.push(n1 + n2);
            } else if (post[i] == '/') {
                s2.push(n1 / n2);
            } else if (post[i] == '*') {
                s2.push(n1 * n2);
            }
        }
    }
    return s2.get();
}
