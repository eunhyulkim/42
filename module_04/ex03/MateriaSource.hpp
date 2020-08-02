#ifndef MATERIA_SOURCE_HPP
# define MATERIA_SOURCE_HPP

# include <string>
# include "AMateria.hpp"
# include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria	*srcs[4];
		int			count;
	public:
		MateriaSource();
		MateriaSource(const MateriaSource& copy);
		MateriaSource& operator=(const MateriaSource& obj);
		~MateriaSource();

		int	getCount() const;
		void learnMateria(AMateria* materia);
		AMateria* createMateria(std::string const & type);
};

#endif
