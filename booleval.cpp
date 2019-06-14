#include <bits/stdc++.h>
using namespace std;

int pos;
string s;

void error(const std::string &str) {
    cout << "Error: " << str << endl;
    exit(0);
}

bool get_bool() {
    if (s[pos] == 't') {
        if (s[pos + 1] != 'r' || s[pos + 2] != 'u' || s[pos + 3] != 'e')
            error("Wrong primary value given (should be true/false)");
        pos += 4;
        return true;
    } else if (s[pos] == 'f') {
        if (s[pos + 1] != 'a' || s[pos + 2] != 'l' || s[pos + 3] != 's' || s[pos + 4] != 'e')
            error("Wrong primary value given (should be true/false)");
        pos += 5;
        return false;
    } else {
        error("Wrong characted got");
        return false;
    }
}

bool formula () {
    if (s[pos] == 't' || s[pos] == 'f') {
        bool b = get_bool();
        if (s[pos] == '(')
            error("Not a function (true/false)");
        return b;
    }

    if (s[pos] == ',') {
        pos++;
        if (s[pos] == ',')
            error("Only one comma expected");
        return formula();
    }

    int op = -1;
    if (s[pos] == 'a') {
        if (s[pos + 1] != 'n' || s[pos + 2] != 'd')
            error("Wrong operation aka and");
        op = 0;
        pos += 3;
    } else if (s[pos] == 'o') {
        if (s[pos + 1] != 'r') {
            error("Wrong operation aka or");
        }
        op = 1;
        pos += 2;
    } else if (s[pos] == 'n') {
        if (s[pos + 1] != 'o' || s[pos + 2] != 't')
            error ("Wrong operation aka not");
        op = 2;
        pos += 3;
    } else
        error("Unexpected symbol got");

    if (s[pos] != '(')
        error("Bracket expected");
    pos++;

    int count = 0;
    bool result = formula();
    while (s[pos] == ',') {
        count++;
        if (op == 0)
            result &= formula();
        if (op == 1)
            result |= formula();
        if (op == 2) {
            result = !result;
            if (s[pos] == ',')
                error("Not expects only one argument");
        }
    }

    if (s[pos] != ',' && op == 2)
        result = !result;
    if (count < 1 && op != 2)
        error("Operation needs two arguments at least");

    if (s[pos] != ')')
        error ("Closing bracket expected");
    else
        pos++;

    return result;
}

// For example: or(false,false,or(false,false),and(true,or(and(true,true),and(true,false))))
// Result: true
int main () {
    cin >> s;
    pos = 0;
    bool value = formula();
    if (pos < s.size())
        cout << "WARNING: Ignored tail symbols" << endl;
    cout << "Result: " << (value ? "true" : "false") << endl;
    return 0;
}
