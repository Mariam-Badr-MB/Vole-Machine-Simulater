# Vole Machine Simulator

This project is a simulation of a basic CPU and memory system, designed to demonstrate fundamental concepts such as memory management, registers, ALU operations, and instruction execution. The simulator models a simple machine architecture, including various components like registers, memory, and the control unit, and it supports operations such as loading and storing data, bitwise operations, arithmetic operations, jumps, and program flow.

## Features

- **Memory Simulation**: Emulates memory with 256 cells, each capable of holding a 2-character string representing machine instructions.
- **Registers**: Supports 16 registers that store integer values, with operations to manipulate them.
- **ALU Operations**: Includes functions for basic arithmetic (addition, two's complement), bitwise operations (AND, OR, XOR), and floating-point operations.
- **Control Unit**: Handles program flow, such as jumps, comparisons, and instruction execution based on opcodes.
- **Program Loading**: Allows loading programs from a file or by entering instructions manually.
- **Program Execution**: Executes instructions in a step-by-step manner, simulating CPU operations and providing state updates after each step.

## Architecture Overview

The simulator includes the following components:

1. **CPU**: Contains the instruction register (IR), program counter (PC), and methods to fetch, decode, and execute instructions.
2. **Memory**: A class that simulates 256 memory cells, each of which can hold a string (machine instruction or data).
3. **Register**: A class to manage 16 general-purpose registers.
4. **ALU**: Arithmetic Logic Unit for performing arithmetic and bitwise operations.
5. **Control Unit (CU)**: Controls the execution of instructions and manages program flow.
6. **Main UI**: Provides a user interface to interact with the machine, allowing users to load programs, input instructions, and view the state of the machine.

## How It Works

- The machine's state is represented by registers and memory, which are modified during program execution.
- Instructions are fetched from memory, decoded, and executed by the CPU.
- Each instruction is represented by an opcode and operands, and the CPU performs the corresponding operation on the registers and memory.

### Instruction Format

The instructions are encoded as hexadecimal pairs. The instruction structure is as follows:
- **Opcode (1 byte)**: Specifies the operation to be performed.
- **Register (1 byte)**: Specifies the register(s) involved in the operation.
- **Immediate Value or Address (2 bytes)**: Used for immediate data or memory addresses, depending on the opcode.

## Usage

1. **Load Program from File**: Input a program file to load the instructions into memory.
2. **Add Instructions Manually**: Input instructions directly as a space-separated list.
3. **View Current State**: View the current values of all registers and memory.
4. **Exit**: Exit the program.

