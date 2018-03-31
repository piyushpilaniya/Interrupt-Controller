#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <iomanip>
#include <stdint.h>

//Remove this comment if you are using 64 bit system
//#define BITS64

#ifdef BITS64
typedef uint32_t uint32;
#else
typedef unsigned int uint32;
#endif

#define DATA_SEG 0x500
enum Opcode {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    CMP,
    AND,
    OR,
    NOT,
    MOV,
    LSL,
    LSR,
    ASR,
    NOP,
    LD,
    ST,
    BEQ,
    BGT,
    B,
    CALL,
    RET,
    MOVZ,
    RETZ,
    END,

};

struct Instruction {
    uint32 pc;
    Opcode opcode;
    uint32 encoding;
    std::string operands;
    bool modU;
    bool modH;
    std::string origInst;
    uint32 lineNum;
    Instruction() {
        pc = encoding = 0;
    }
};

struct Data {
    uint32 address;
    std::vector<int> data; //array of values
    Data(uint32 add) {
        address = add;
    }
};

class Assembler {
        public:
            Assembler(char *input, char *output);
        private:
            void assemblerPass1(char *);
            void assemblerPass2(char *);
            void removeInitialWhiteSpace(std::string &);
            void removeDosChar(std::string &);
            void removeWhiteSpace(std::string &);
            bool isComment(std::string &);
            bool isEmpty(std::string &);
            void initOpcodes();
            void readLabel(std::string &input, std::string &label) ;
            void readMemoryOffset(std::string &input, int &offset);
            void readRegisterOperand(std::string &input, int &regIndex, bool &imm);
            void lowerCase(std::string &input);
            uint32 generateEncoding(Opcode opcode);
            uint32 generateEncoding(Opcode opcode, int offset);
            uint32 generateEncoding(Opcode opcode, int reg1, int reg2, int imm);
            uint32 generateEncoding(Opcode opcode, int reg1, int src2, bool imm);
            uint32 generateEncoding(Opcode opcode, int reg1, int src1, int src2, bool imm);
            bool readInstruction(std::string &line, Instruction* inst);
            bool isNoOperand(Opcode opcode);
            bool isSingleOperand(Opcode opcode);
            bool isMemoryOperand(Opcode opcode);
            bool isTwoOperand(Opcode opcode);
            int readNumber(std::string &);

        private:
            std::map<std::string, uint32> mSymTab;
            std::vector<Instruction*> mInstList;
            std::vector<Data*> mDataList;
            std::map<std::string, Opcode> opcodes;
};

#endif
