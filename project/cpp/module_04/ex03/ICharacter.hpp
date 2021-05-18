#ifndef I_CHARACTER_HPP
# define I_CHARACTER_HPP

# include <string>

class AMateria;

class ICharacter
{
	public:
		virtual ~ICharacter() {}
		virtual const std::string& get_m_name() const = 0;
		virtual void equip(AMateria* m) = 0;
		virtual void unequip(int idx) = 0;
		virtual void use(int idx, ICharacter& target) = 0;
};

#endif
