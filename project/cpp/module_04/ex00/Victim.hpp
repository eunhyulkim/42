#ifndef VICTIM_HPP
# define VICTIM_HPP

# include <string>
# include <iostream>

class Victim
{
	private:
		std::string m_name;
	protected:
		Victim();
	public:
		Victim(const std::string& name);
		Victim(const Victim& copy);
		Victim& operator=(const Victim& obj);
		virtual ~Victim();

		/* getter function */
		std::string get_m_name() const;

		/* declare member function */
		virtual void getPolymorphed(void) const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Victim& victim);

#endif
