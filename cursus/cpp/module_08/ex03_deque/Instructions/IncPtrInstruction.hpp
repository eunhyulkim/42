#ifndef INC_PTR_INSTRUCTION_HPP
# define INC_PTR_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class IncPtrInstruction : public Instruction
{
	private:
		IncPtrInstruction();
	public:
		IncPtrInstruction(Program& program);
		IncPtrInstruction(const IncPtrInstruction& copy);
		IncPtrInstruction& operator=(const IncPtrInstruction&);
		virtual ~IncPtrInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
