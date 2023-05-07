# Documentation for Parker McLeod's ComputerSim Program

Here is the documentation (mostly for my benefit) of a basic computer simulation program. Watching Crash Course Computer Science made me realize how beautiful computer architecture can be. I wanted to explore the ideas of complex emergent behaviors from simple systems. In this case, how some electrons and transistors can be bullied into "thinking".

## Gates.h

```cpp
// Examples Usage

// Create input signals
Input trueSignal(true);
Input falseSignal(false);

// Create gates and connect them
AndGate andGate(trueSignal, falseSignal);
OrGate orGate(trueSignal, falseSignal);
NotGate notGate(trueSignal);

// Evaluate gates and output results
std::cout << "AND gate output: " << andGate.evaluate() << std::endl;
std::cout << "OR gate output: " << orGate.evaluate() << std::endl;
std::cout << "NOT gate output: " << notGate.evaluate() << std::endl;

// Connect gates to each other
OrGate orAndOrGate(andGate, orGate);

// Evaluate new gate and output result
std::cout << "orAndOrGate gate output: " << orAndOrGate.evaluate() << std::endl;

// Create a half adder and connect the inputs
HalfAdder halfAdder(input1, input2);

// Evaluate the half adder and output the results
std::cout << "Sum: " << halfAdder.sum() << std::endl;
std::cout << "Carry: " << halfAdder.carry() << std::endl;

```
