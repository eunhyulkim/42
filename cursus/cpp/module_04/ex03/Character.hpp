#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include <iostream>

# include "ICharacter.hpp"
# include "AMateria.hpp"

class AMateria;

class Character : public ICharacter
{
	private:
		const std::string m_name;
		AMateria *m_srcs[4];
		int m_count;
		Character();
	public:
		Character(const std::string name);
		Character(const Character& copy);
		Character& operator=(const Character& obj);
		virtual ~Character();

		/* getter function */
		int get_m_count() const;

		/* inherit overload function */
		virtual const std::string& get_m_name() const;
		virtual void equip(AMateria* m);
		virtual void unequip(int idx);
		virtual void use(int idx, ICharacter& target);

		/* declare member function */
		AMateria* getMateria(int idx) const;
};

#endif
