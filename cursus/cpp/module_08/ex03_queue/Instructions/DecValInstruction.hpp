#ifndef DEC_VAL_INSTRUCTION_HPP
# define DEC_VAL_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class DecValInstruction : public Instruction
{
	private:
		DecValInstruction();
	public:
		DecValInstruction(Program& program);
		DecValInstruction(const DecValInstruction& copy);
		DecValInstruction& operator=(const DecValInstruction&);
		virtual ~DecValInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
