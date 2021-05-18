#include "Human.hpp"

typedef void	(Human::* func_member)(std::string const &);

void	Human::meleeAttack(std::string const & target){
	std::cout << "Action of Human to " << target << " 'meleeAttack'!" << std::endl;
}

void	Human::rangedAttack(std::string const & target){
	std::cout << "Action of Human to " << target << " 'rangedAttack'!" << std::endl;
}

void	Human::intimidatingShout(std::string const & target)
{
	std::cout << "Action of Human to " << target << " 'initimdatingShout'!" << std::endl;
}

void	Human::action(std::string const & action_name, std::string const & target)
{
	std::string func_name[3] = {
		"meleeAttack", "rangedAttack", "intimidatingShout"
	};

	func_member	member[3] = {
		&Human::meleeAttack, &Human::rangedAttack, &Human::intimidatingShout
	};

	for (int i = 0; i < 3; i++)
	{
		if (action_name == func_name[i])
		{
			(this->*member[i])(target);
			return;
		}
	}
	std::cout << "'" << action_name << "'" << " not found." << std::endl;
}
