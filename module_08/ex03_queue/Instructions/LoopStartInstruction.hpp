#ifndef LOOP_START_INSTRUCTION_HPP
# define LOOP_START_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class LoopStartInstruction : public Instruction
{
	private:
		LoopStartInstruction();
	public:
		LoopStartInstruction(Program& program);
		LoopStartInstruction(const LoopStartInstruction& copy);
		LoopStartInstruction& operator=(const LoopStartInstruction&);
		virtual ~LoopStartInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
