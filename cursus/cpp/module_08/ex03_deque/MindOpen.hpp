#ifndef MIND_OPEN_HPP
# define MIND_OPEN_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <fstream>
# include <array>
# include <deque>
# include <Program.hpp>
# include "Instructions/IncPtrInstruction.hpp"
# include "Instructions/DecPtrInstruction.hpp"
# include "Instructions/IncValInstruction.hpp"
# include "Instructions/DecValInstruction.hpp"
# include "Instructions/InputInstruction.hpp"
# include "Instructions/OutputInstruction.hpp"
# include "Instructions/LoopStartInstruction.hpp"
# include "Instructions/LoopEndInstruction.hpp"

class MindOpen
{
	private:
		std::string m_raw_string;
	protected:
		Program m_program;
	public:
		MindOpen();
		MindOpen(const MindOpen& copy);
		MindOpen& operator=(const MindOpen& obj);
		virtual ~MindOpen();

		/* setter function */
		bool set_m_raw_string(const std::string& filename);
		bool set_m_program(void);

		/* declare member function */
		void runProgram(void);
};

#endif
