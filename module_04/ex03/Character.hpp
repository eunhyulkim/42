#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"

class AMateria;

class Character : public ICharacter
{
	private:
		std::string _name;
		AMateria	*_srcs[4];
		int			_count;
		Character();

	public:
		Character(const std::string name);
		Character(const Character& copy);
		Character& operator=(const Character& obj);
		~Character();

		std::string const & getName() const;
		int getCount() const;
		AMateria* getMateria(int idx) const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
};
#endif
