#ifndef A_MATERIA_HPP
# define A_MATERIA_HPP

# include <string>
# include "ICharacter.hpp"

class AMateria
{
	protected:
		std::string _type;
		unsigned int _xp;
		AMateria();
	public:
		AMateria(const std::string& type);
		AMateria(const AMateria& copy);
		AMateria& operator=(const AMateria& obj);
		virtual ~AMateria();

		const std::string& getType() const;
		unsigned int getXP() const;
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};
#endif
