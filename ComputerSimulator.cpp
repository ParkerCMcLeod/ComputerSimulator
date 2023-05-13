#include <cstdio>
#include <stdexcept>
#include <iostream>

// gates

class Gate {
public:
    virtual bool evaluate() const = 0;
    
    void output() {
        std::cout << evaluate() << std::endl;
    }
};

class Input : public Gate {
private:
    bool value;

public:
    Input(bool value) : value(value) 
    {}

    bool evaluate() const override {
        return value;
    }
};

class AndGate : public Gate {
private:
    const Gate& input1;
    const Gate& input2;

public:
    AndGate(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) 
    {}

    bool evaluate() const override {
        return input1.evaluate() && input2.evaluate();
    }
};

class OrGate : public Gate {
private:
    const Gate& input1;
    const Gate& input2;

public:
    OrGate(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) 
    {}

    bool evaluate() const override {
        return input1.evaluate() || input2.evaluate();
    }
};

class XorGate : public Gate {
private:
    const Gate& input1;
    const Gate& input2;

public:
    XorGate(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) 
    {}

    bool evaluate() const override {
        return input1.evaluate() ^ input2.evaluate();
    }
};

class NotGate : public Gate {
private:
    const Gate& input;

public:
    NotGate(const Gate& input) : input(input) 
    {}

    bool evaluate() const override {
        return !input.evaluate();
    }
};

// arithmetic units

class HalfAdder {
private:
    const Gate& input1;
    const Gate& input2;

public:
    HalfAdder(const Gate& input1, const Gate& input2) : input1(input1), input2(input2) 
    {}

    bool sum() const {
        XorGate xorGate(input1, input2);
        return xorGate.evaluate();
    }

    bool carry() const {
        AndGate andGate(input1, input2);
        return andGate.evaluate();
    }
};

class FullAdder {
private:
    HalfAdder halfAdder1;
    Input halfAdder1Sum;
    HalfAdder halfAdder2;

public:
    FullAdder(const Gate& carryInput, const Gate& input1, const Gate& input2)
        : halfAdder1(input1, input2), halfAdder1Sum(halfAdder1.sum()), halfAdder2(halfAdder1Sum, carryInput) 
    {}

    bool sum() const {
        return halfAdder1.sum() ^ halfAdder2.sum();
    }

    bool carry() const {
        OrGate orGate(Input(halfAdder1.carry()), Input(halfAdder2.carry()));
        return orGate.evaluate();
    }
};

class RippleCarryAdder {
private:
    const Gate& inputA7;
    const Gate& inputA6;
    const Gate& inputA5;
    const Gate& inputA4;
    const Gate& inputA3;
    const Gate& inputA2;
    const Gate& inputA1;
    const Gate& inputA0;
    const Gate& inputB7;
    const Gate& inputB6;
    const Gate& inputB5;
    const Gate& inputB4;
    const Gate& inputB3;
    const Gate& inputB2;
    const Gate& inputB1;
    const Gate& inputB0;
    HalfAdder adder0;
    bool sum0;
    Input adder0Carry;
    FullAdder adder1;
    bool sum1;
    Input adder1Carry;
    FullAdder adder2;
    bool sum2;
    Input adder2Carry;
    FullAdder adder3;
    bool sum3;
    Input adder3Carry;
    FullAdder adder4;
    bool sum4;
    Input adder4Carry;
    FullAdder adder5;
    bool sum5;
    Input adder5Carry;
    FullAdder adder6;
    bool sum6;
    Input adder6Carry;
    FullAdder adder7;
    bool sum7;
    Input adder7Carry;
    bool overflow;

public:
    RippleCarryAdder(const Gate& inputA7, const Gate& inputA6, const Gate& inputA5, const Gate& inputA4,
                     const Gate& inputA3, const Gate& inputA2, const Gate& inputA1, const Gate& inputA0,
                     const Gate& inputB7, const Gate& inputB6, const Gate& inputB5, const Gate& inputB4,
                     const Gate& inputB3, const Gate& inputB2, const Gate& inputB1, const Gate& inputB0)
        : inputA7(inputA7), inputA6(inputA6), inputA5(inputA5), inputA4(inputA4), inputA3(inputA3), inputA2(inputA2),
          inputA1(inputA1), inputA0(inputA0), inputB7(inputB7), inputB6(inputB6), inputB5(inputB5), inputB4(inputB4),
          inputB3(inputB3), inputB2(inputB2), inputB1(inputB1), inputB0(inputB0),
          adder0(inputA0, inputB0), sum0(adder0.sum()), adder0Carry(adder0.carry()),
          adder1(adder0Carry, inputA1, inputB1), sum1(adder1.sum()), adder1Carry(adder1.carry()),
          adder2(adder1Carry, inputA2, inputB2), sum2(adder2.sum()), adder2Carry(adder2.carry()),
          adder3(adder2Carry, inputA3, inputB3), sum3(adder3.sum()), adder3Carry(adder3.carry()),
          adder4(adder3Carry, inputA4, inputB4), sum4(adder4.sum()), adder4Carry(adder4.carry()),
          adder5(adder4Carry, inputA5, inputB5), sum5(adder5.sum()), adder5Carry(adder5.carry()),
          adder6(adder5Carry, inputA6, inputB6), sum6(adder6.sum()), adder6Carry(adder6.carry()),
          adder7(adder6Carry, inputA7, inputB7), sum7(adder7.sum()), adder7Carry(adder7.carry()),
          overflow(adder7Carry.evaluate()) 
    {}

    bool getSum0() const {
        return sum0;
    }

    bool getSum1() const {
        return sum1;
    }

    bool getSum2() const {
        return sum2;
    }

    bool getSum3() const {
        return sum3;
    }

    bool getSum4() const {
        return sum4;
    }

    bool getSum5() const {
        return sum5;
    }

    bool getSum6() const {
        return sum6;
    }

    bool getSum7() const {
        return sum7;
    }

    bool getOverflow() const {
        return overflow;
    }

    void output() {
        if (overflow) {
            std::cout << "OVERFLOW" << std::endl;
        } else {
            std::cout << "OUTPUT: ";
            std::cout << getSum7() << getSum6() << getSum5() << getSum4() << getSum3() << getSum2() << getSum1() << getSum0() << std::endl;
        }
    }
};

int main() {
    Input one(true);
    Input zero(false);

    RippleCarryAdder rippleCarryAdder(zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, zero, one, one, one);
    rippleCarryAdder.output();

    return 0;
}
