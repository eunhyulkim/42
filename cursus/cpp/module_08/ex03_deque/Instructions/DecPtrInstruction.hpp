#ifndef DEC_PTR_INSTRUCTION_HPP
# define DEC_PTR_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class DecPtrInstruction : public Instruction
{
	private:
		DecPtrInstruction();
	public:
		DecPtrInstruction(Program& program);
		DecPtrInstruction(const DecPtrInstruction& copy);
		DecPtrInstruction& operator=(const DecPtrInstruction&);
		virtual ~DecPtrInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
