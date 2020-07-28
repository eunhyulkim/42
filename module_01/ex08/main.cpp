#include "Human.hpp"

int		main(void)
{
	Human t;

	t.action("meleeAttack", "opponent1");
	t.action("rangedAttack", "opponent2");
	t.action("intimidatingShout", "opponent3");
	t.action("Anonymous Action", "opponent4");
	return (0);
}
