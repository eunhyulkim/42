#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

class Program;

# include "Program.hpp"

class Instruction
{
	private:
	protected:
		Instruction();
		Program* m_program;
	public:
		Instruction(Program& program);
		Instruction(Program* program);
		Instruction(const Instruction& copy);
		Instruction& operator=(const Instruction&);
		virtual ~Instruction();

		/* declare member function */
		virtual void execute(void) = 0;
		virtual int getType(void) = 0;
};

#endif
