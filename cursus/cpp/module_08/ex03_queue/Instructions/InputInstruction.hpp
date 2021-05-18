#ifndef INPUT_INSTRUCTION_HPP
# define INPUT_INSTRUCTION_HPP

# include "Program.hpp"
# include "Instruction.hpp"

class InputInstruction : public Instruction
{
	private:
		InputInstruction();
	public:
		InputInstruction(Program& program);
		InputInstruction(const InputInstruction& copy);
		InputInstruction& operator=(const InputInstruction&);
		virtual ~InputInstruction();

		/* inherit overload function */
		virtual void execute(void);
		virtual int getType(void);
};

#endif
