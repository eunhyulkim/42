#include "ISquad.hpp"
#include "ISpaceMarine.hpp"
#include <iostream>

class Squad : public ISquad
{
	private:
		typedef struct		s_squad
		{
			ISpaceMarine 	*unit;
			s_squad 		*next;
		}					t_squad;

		t_squad				*squad;
		int					totalUnit;
		void				init(Squad *obj);
		void				deepCopy(const Squad& copy);
	public:
		Squad();
		~Squad();
		Squad(const Squad& copy);
		Squad& operator=(const Squad& obj);
		int getCount() const;
		ISpaceMarine* getUnit(int nth) const;
		int push(ISpaceMarine* unit);
};
