#ifndef SQUAD_HPP
# define SQUAD_HPP

# include <string>
# include <iostream>

# include "ISquad.hpp"

class Squad : public ISquad
{
	private:
		typedef struct		s_squad
		{
			ISpaceMarine 	*unit;
			s_squad 		*next;
		}					t_squad;
		t_squad 			*m_squad;
		int 				m_total_unit;
		
	protected:
		void init(Squad *obj);
		void deepCopy(const Squad& copy);
	public:
		Squad();
		Squad(const Squad& copy);
		Squad& operator=(const Squad& obj);
		virtual ~Squad();

		/* inherit overload function */
		virtual int getCount() const;
		virtual ISpaceMarine* getUnit(int nth) const;
		virtual int push(ISpaceMarine* unit);
};

#endif
