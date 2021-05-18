#ifndef CURE_HPP
# define CURE_HPP

# include <string>
# include <iostream>

# include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		Cure();
		Cure(const Cure& copy);
		Cure& operator=(const Cure& obj);
		virtual ~Cure();

		/* inherit overload function */
		virtual AMateria* clone() const;
		virtual void use(ICharacter& target);
};

#endif
