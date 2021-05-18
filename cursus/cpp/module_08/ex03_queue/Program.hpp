#ifndef PROGRAM_HPP
# define PROGRAM_HPP

# include <string>
# include <iostream>
# include <array>
# include <queue>
# include <vector>
# include "Instruction.hpp"

class Instruction;

class Program
{
	private:
		size_t m_instruction_pos;
		int m_pointer;
		size_t m_instruction_size;
		std::array<char, 30000> m_stack;
		std::queue<Instruction*> m_instructions;
		std::vector<int> m_log_instructions;
		
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
		void loopStart(bool startByQueue = true);
		void loopEnd(void);
		void input(void);
		void output(void);

		void runCommand(int cmd);
		void runProgram(void);
};

#endif
