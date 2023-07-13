#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"

/*
 * C++ Starter code for CS241 A3
 *
 * This file contains the main function of your program. By default, it just
 * prints the scanned list of tokens back to standard output.
 */
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
      /*
      for (auto &token : tokenLine) {
        std::cout << token << ' ';
      }
      */

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
		        char byte;
			while (num) {
				byte = num = num >> 8;
				std::cout << byte;
			}
			std::cout << std::endl;
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
