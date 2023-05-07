#include <iostream>
#include <tuple>
#include <cstdio>

// gates

class Gate {
public:
    virtual bool evaluate() const = 0;
};

class Input : public Gate {
private:
    bool value;

public:
    Input(bool value) : value(value) {}

    bool evaluate() const override {
        return value;
    }
};

class AndGate : public Gate {
private:
    const Gate& input1;
    const Gate& input2;

public:
    AndGate(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) {}

    bool evaluate() const override {
        return input1.evaluate() && input2.evaluate();
    }
};

class OrGate : public Gate {
private:
    const Gate& input1;
    const Gate& input2;

public:
    OrGate(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) {}

    bool evaluate() const override {
        return input1.evaluate() || input2.evaluate();
    }
};

class XorGate : public Gate {
private:
    const Gate& input1;
    const Gate& input2;

public:
    XorGate(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) {}

    bool evaluate() const override {
        return input1.evaluate() != input2.evaluate();
    }
};

class NotGate : public Gate {
private:
    const Gate& input;

public:
    NotGate(const Gate& input) : input(input) {}

    bool evaluate() const override {
        return !input.evaluate();
    }
};

// arithmatic units

class HalfAdder {
private:
    const Gate& input1;
    const Gate& input2;

public:
    HalfAdder(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) {}

    bool sum() const {
        // the sum output is an XOR of the two inputs
        XorGate xorGate(input1, input2);
        return xorGate.evaluate();
    }

    bool carry() const {
        // the carry output is an AND of the two inputs
        AndGate andGate(input1, input2);
        return andGate.evaluate();
    }
};

class FullAdder {
private:
    const Gate& carryInput;
    const Gate& input1;
    const Gate& input2;
    Input halfAdder1SumInput;
    Input halfAdder1CarryInput;

public:
    FullAdder(const Gate& carryInput, const Gate& input1, const Gate& input2)
        : carryInput(carryInput), input1(input1), input2(input2),
          halfAdder1SumInput(HalfAdder(input1, input2).sum()),
          halfAdder1CarryInput(HalfAdder(input1, input2).carry()) {}

    bool sum() const {
        HalfAdder halfAdder1(input1, input2);
        HalfAdder halfAdder2(halfAdder1SumInput, carryInput);
        return halfAdder2.sum();
    }

    bool carry() const {
        HalfAdder halfAdder1(input1, input2);
        HalfAdder halfAdder2(halfAdder1SumInput, carryInput);
        OrGate orGate(halfAdder1CarryInput, Input(halfAdder2.carry()));
        return orGate.evaluate();
    }
};

class RippleCarryAdder {
private:
    const Gate &inputA7, &inputA6, &inputA5, &inputA4, &inputA3, &inputA2, &inputA1, &inputA0,
               &inputB7, &inputB6, &inputB5, &inputB4, &inputB3, &inputB2, &inputB1, &inputB0;
    HalfAdder adder0;
    FullAdder adder1, adder2, adder3, adder4, adder5, adder6, adder7;
    Input adder0CarryInput, adder1CarryInput, adder2CarryInput, adder3CarryInput,
          adder4CarryInput, adder5CarryInput, adder6CarryInput;

public:
    RippleCarryAdder(const Gate& inputA7, const Gate& inputA6, const Gate& inputA5, const Gate& inputA4,
        const Gate& inputA3, const Gate& inputA2, const Gate& inputA1, const Gate& inputA0,
        const Gate& inputB7, const Gate& inputB6, const Gate& inputB5, const Gate& inputB4,
        const Gate& inputB3, const Gate& inputB2, const Gate& inputB1, const Gate& inputB0)
        : inputA7(inputA7), inputA6(inputA6), inputA5(inputA5), inputA4(inputA4),
        inputA3(inputA3), inputA2(inputA2), inputA1(inputA1), inputA0(inputA0),
        inputB7(inputB7), inputB6(inputB6), inputB5(inputB5), inputB4(inputB4),
        inputB3(inputB3), inputB2(inputB2), inputB1(inputB1), inputB0(inputB0),
        adder0(inputA0, inputB0),
        adder1(inputA1, inputB1, Input(adder0.carry())),
        adder2(inputA2, inputB2, Input(adder1.carry())),
        adder3(inputA3, inputB3, Input(adder2.carry())),
        adder4(inputA4, inputB4, Input(adder3.carry())),
        adder5(inputA5, inputB5, Input(adder4.carry())),
        adder6(inputA6, inputB6, Input(adder5.carry())),
        adder7(inputA7, inputB7, Input(adder6.carry())),
        adder0CarryInput(adder0.carry()), adder1CarryInput(adder1.carry()),
        adder2CarryInput(adder2.carry()), adder3CarryInput(adder3.carry()),
        adder4CarryInput(adder4.carry()), adder5CarryInput(adder5.carry()),
        adder6CarryInput(adder6.carry()) {}


    bool evaluate0() {
        bool sum0 = adder0.sum();
        return sum0;
    }

    bool evaluate1() {
        bool sum1 = adder1.sum();
        return sum1;
    }

    bool evaluate2() {
        bool sum2 = adder2.sum();
        return sum2;
    }

    bool evaluate3() {
        bool sum3 = adder3.sum();
        return sum3;
    }

    bool evaluate4() {
        bool sum4 = adder4.sum();
        return sum4;
    }

    bool evaluate5() {
        bool sum5 = adder5.sum();
        return sum5;
    }

    bool evaluate6() {
        bool sum6 = adder6.sum();
        return sum6;
    }

    bool evaluate7() {
        bool sum7 = adder7.sum();
        return sum7;
    }

    bool carry() {
        return adder7.carry();
    }

    void print() {    
        if (carry()) {
            printf("OVERFLOW");
            return;
        } else {
            printf("OUTPUT: ");
            printf("OUTPUT: %d%d%d%d%d%d%d%d", static_cast<int>(evaluate7()), static_cast<int>(evaluate6()), static_cast<int>(evaluate5()), static_cast<int>(evaluate4()), static_cast<int>(evaluate3()), static_cast<int>(evaluate2()), static_cast<int>(evaluate1()), static_cast<int>(evaluate0()));
        }
    }
};


int main() {
    Input One(true);
    Input Zero(false);
    RippleCarryAdder rippleCarryAdder(AndGate(Zero,One),Zero,Zero,Zero,Zero,Zero,Zero,OrGate(Zero,One),Zero,Zero,Zero,Zero,Zero,Zero,Zero,XorGate(Zero,One));
    rippleCarryAdder.print();

    return 0;
};
