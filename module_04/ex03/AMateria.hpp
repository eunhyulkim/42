#ifndef A_MATERIA_HPP
# define A_MATERIA_HPP

# include <string>

# include "ICharacter.hpp"

class AMateria
{
	protected:
		std::string m_type;
		unsigned int m_xp;
		AMateria();
	public:
		AMateria(const std::string& type);
		AMateria(const AMateria& copy);
		AMateria& operator=(const AMateria& obj);
		virtual ~AMateria();

		/* getter function */
		std::string get_m_type() const;
		unsigned int get_m_xp() const;

		/* declare member function */
		virtual AMateria* clone() const = 0;
		virtual void use(ICharacter& target);
};

/* global operator overload */

#endif
