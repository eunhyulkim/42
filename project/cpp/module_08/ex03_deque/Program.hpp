#ifndef PROGRAM_HPP
# define PROGRAM_HPP

# include <string>
# include <iostream>
# include <array>
# include <deque>
# include <vector>
# include "Instruction.hpp"

class Instruction;

class Program
{
	private:
		size_t m_instruction_pos;
		int m_pointer;
		std::array<char, 30000> m_stack;
		std::deque<Instruction*> m_instructions;
		
		enum InstructionType {
			DEFAULT,
			INCPTR,
			DECPTR,
			INCVAL,
			DECVAL,
			INPUT,
			OUTPUT,
			LOOPSTART,
			LOOPEND
		};
	public:
		Program();
		Program(const Program& copy);
		Program& operator=(const Program& obj);
		virtual ~Program();

		/* declare member function */
		void addInstruction(Instruction *instruction);
	
		void incPtr(void);
		void decPtr(void);
		void incVal(void);
		void decVal(void);
		void loopStart(void);
		void loopEnd(void);
		void input(void);
		void output(void);

		void runProgram(void);
};

#endif
