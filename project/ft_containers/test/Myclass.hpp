#ifndef MYCLASS_HPP
# define MYCLASS_HPP

# include <string>
# include <iostream>

class Myclass
{
	private:
		std::string m_name;
	public:
		Myclass();
		Myclass(const std::string& name);
		Myclass(const Myclass& copy);
		Myclass& operator=(const Myclass& obj);
		virtual ~Myclass();

		const std::string& get_m_name() const;

		std::string& 		operator*();
		const std::string&	operator*() const;
		bool				operator!=(const Myclass& obj) const;
		bool				operator==(const Myclass& obj) const;
		bool				operator<(const Myclass& obj) const;
		bool				operator<=(const Myclass& obj) const;
		bool				operator>(const Myclass& obj) const;
		bool				operator>=(const Myclass& obj) const;

};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Myclass& myclass);

#endif
