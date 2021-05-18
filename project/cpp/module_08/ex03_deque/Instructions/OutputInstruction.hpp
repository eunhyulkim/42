#ifndef OUTPUT_INSTRUCTION_HPP
# define OUTPUT_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class OutputInstruction : public Instruction
{
	private:
		OutputInstruction();
	public:
		OutputInstruction(Program& program);
		OutputInstruction(const OutputInstruction& copy);
		OutputInstruction& operator=(const OutputInstruction&);
		virtual ~OutputInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
