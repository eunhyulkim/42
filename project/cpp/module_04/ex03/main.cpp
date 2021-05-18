#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

void	print(std::string msg) {
	std::cout << std::endl
	<< "\033[1;37;41m" << msg << "\033[0m"
	<< std::endl << std::endl;
}

int main()
{
	print("BASIC TEST");
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;

	{
		print("CUSTOM TEST");
		ICharacter* me = new Character("eunhkim");
		IMateriaSource* src = new MateriaSource();
		
		print("EXPECT LEARN I-C-C-C");
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		src->learnMateria(new Cure());
		src->learnMateria(nullptr);
		src->learnMateria(new Cure());
		src->learnMateria(new Ice());

		AMateria* tmp = nullptr;
		tmp = src->createMateria("Ice");
		print("EXPECT NOT CREATE(nullptr)");
		std::cout << tmp << std::endl;
		tmp = src->createMateria("Cure");
		std::cout << tmp << std::endl;

		print("0 SLOT EQUIP, 1-2 NOT");
		tmp = src->createMateria("cure");
		ICharacter *you = new Character("friend");
		me->equip(tmp);
		me->equip(nullptr);
		me->equip(tmp);
		std::cout << "0: ";
		me->use(0, *you);
		std::cout << "1: \n";
		me->use(1, *you);
		std::cout << "2: \n";
		me->use(2, *you);
		print("MATERIA EXPECT(10)");
		std::cout << "XP: " << tmp->get_m_xp() << std::endl;
		print("TEST END");
	}

	return 0;
}
