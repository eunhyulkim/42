#ifndef INC_VAL_INSTRUCTION_HPP
# define INC_VAL_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class IncValInstruction : public Instruction
{
	private:
		IncValInstruction();
	public:
		IncValInstruction(Program& program);
		IncValInstruction(const IncValInstruction& copy);
		IncValInstruction& operator=(const IncValInstruction&);
		virtual ~IncValInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
