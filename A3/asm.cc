#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"
#include <map>

/*
 * C++ Starter code for CS241 A3
 *
 * This file contains the main function of your program. By default, it just
 * prints the scanned list of tokens back to standard output.
 */



enum Idcode {
	IADD = 0,
	ISUB,
	IMULT,
	IMULTU,
	IDIV,
	IDIVU,
	IMFHI,
	IMFLO,
	ILIS,
	ISLT,
	ISLTU,
	IBEQ,
	IBNE,
	ILW,
	ISW
};

const std::map<std::string, int> idMap = {
	{"add"	, IADD},
	{"sub"	, ISUB},
	{"mult"	, IMULT},
	{"multu", IMULTU},
	{"div"	, IDIV},
	{"divu"	, IDIVU},
	{"mfhi"	, IMFHI},
	{"mflo"	, IMFLO},
	{"lis"	, ILIS},
	{"slt"	, ISLT},
	{"sltu"	, ISLTU},
	{"beq"	, IBEQ},
	{"bne"	, IBNE},
	{"lw"	, ILW},
	{"sw"	, ISW}	
};


enum Fncode {
	ADD		= 0x20,		// 10 0000
	SUB		= 0x22,		// 10 0010
	MULT		= 0x18,		// 01 1000
	MULTU		= 0x19,		// 01 1001
	DIV		= 0x1A,		// 01 1010
	DIVU		= 0x1B,		// 01 1011
	MFHI		= 0x10,		// 01 0000
	MFLO		= 0x12,		// 01 0010
	LIS		= 0x14,		// 01 0100
	SLT		= 0x2A,		// 10 1010
	SLTU		= 0x2B,		// 10 1011
	IMD		= 0x00
};

enum Opcode {
	REG		= 0x00,
	BEQ 		= 0x04, 	// 00 0100
	BNE 		= 0x05, 	// 00 0101
	LW 		= 0x23, 	// 10 0011
	SW 		= 0x2B  	// 10 1011
};

int getInstruction(Opcode opcode, Fncode fncode, int arg1=0, int arg2=0, int arg3=0) {
	if (opcode == 0x00) {
		arg1 = arg1 << 21;
		arg2 = arg2 << 16;
		arg3 = arg3 << 11;
		return fncode | arg1 | arg2 | arg3;
	}
	int new_opcode = opcode << 25;
	arg1 = arg1 << 21;
	arg2 = arg2 << 16;
	return opcode | arg1 | arg2 | arg3;
}

void printInstruction(int instruction) {
	char byte;
	while (instruction) {
		byte = instruction;
		instruction = instruction >> 8;
		std::cout << byte;
	}
	std::cout << std::endl;
}
	


int main() {
  std::string line;
  try {
    while (getline(std::cin, line)) {
      // This example code just prints the scanned tokens on each line.
      std::vector<Token> tokenLine = scan(line);

      // This code is just an example - you don't have to use a range-based
      // for loop in your actual assembler. You might find it easier to
      // use an index-based loop like this:
      // for(int i=0; i<tokenLine.size(); i++) { ... }
      
      for (auto &token : tokenLine) {
        std::cout << token << ' ';
      }
      

      Token::Kind command = tokenLine[0].getKind();
      switch (command){
	      case Token::Kind::WORD:
		      {
			/* This case does not need to consider a leading byte for command.
			 * input number is stored in variable "num" and is bitwise-shifted 
			 * into "byte" by 8 bits each time until it becomes 0. As a result,
			 * each byte printed is the representative of 8 bits of the input
			 * number. In this version, .word of labels is not accounted for yet.
			 */

		      	int64_t num = tokenLine[1].toNumber();
		        printInstruction(num);
			break;
		      }
		
	      case Token::Kind::ID:
		      {
			      
			      std::string lexeme = tokenLine[0].getLexeme();
			      int arg1 = tokenLine[1].toNumber();
			      int arg2 = tokenLine[2].toNumber();
			      int arg3 = tokenLine[3].toNumber();
			      switch (idMap.at(lexeme)){
				      case IADD:
				      		printInstruction(getInstruction(
									REG, ADD, 
									arg1, arg2, arg3));
						break;
					case IBEQ:
						printInstruction(getInstruction(
									BEQ, IMD, 
									arg1, arg2, arg3));
						break;
					default:
						break;

			      }
			      break;

		      }
		      
		      
		      // To be implemented for more commands.
		       
		default:
		      {
			std::cout << "Irrelevant" << std::endl;
			break;
		      }
      }
      // Remove this when you're done playing with the example program!
      // Printing a random newline character as part of your machine code
      // output will cause you to fail the Marmoset tests.
    }
  } catch (ScanningFailure &f) {
    std::cerr << f.what() << std::endl;
    return 1;
  }
  // You can add your own catch clause(s) for other kinds of errors.
  // Throwing exceptions and catching them is the recommended way to
  // handle errors and terminate the program cleanly in C++. Do not
  // use the std::exit function, which may leak memory.
  
  return 0;
}
