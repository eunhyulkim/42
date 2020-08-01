#include "ISquad.hpp"
#include "ISpaceMarine.hpp"
#include <iostream>

class Squad : public ISquad
{
	private:
		typedef struct		s_unit
		{
			ISpaceMarine 	*unit;
			s_unit 			*next;
		}					t_unit;

		t_unit				*squad;
		int					totalUnit;
	public:
		Squad();
		~Squad();
		Squad(const Squad& copy);
		Squad& operator=(const Squad& obj);

		// int getCount() const;
		// ISpaceMarine* getUnit(int nth);
		// int push(ISpaceMarine* unit);
};
