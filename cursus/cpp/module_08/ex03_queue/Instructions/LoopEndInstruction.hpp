#ifndef LOOP_END_INSTRUCTION_HPP
# define LOOP_END_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class LoopEndInstruction : public Instruction
{
	private:
		LoopEndInstruction();
	public:
		LoopEndInstruction(Program& program);
		LoopEndInstruction(const LoopEndInstruction& copy);
		LoopEndInstruction& operator=(const LoopEndInstruction&);
		virtual ~LoopEndInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
