#pragma once

class VariableStore {
public:
    VariableStore() {}

    void setValue(char varName, double val) {
        int idx = getIndex(varName);
        if (idx != -1) {
            values[idx] = val;
            isSet[idx] = true;
        }
    }

    bool getValue(char varName, double& outVal) const {
        int idx = getIndex(varName);
        if (idx != -1 && isSet[idx]) {
            outVal = values[idx];
            return true;
        }
        return false;
    }

    bool hasValue(char varName) const {
        int idx = getIndex(varName);
        return (idx != -1 && isSet[idx]);
    }

private:
    double values[26]{};
    bool isSet[26]{};

    static int getIndex(char c) {
        if (c >= 'a' && c <= 'z') {
            return c - 'a';
        }
        if (c >= 'A' && c <= 'Z') {
            return c - 'A';
        }
        return -1;
    }
};