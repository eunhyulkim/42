#ifndef STAR_HPP
# define STAR_HPP

class Star
{
	private:
		/* declare variable */
	public:
		Star();
		Star(const std::string& /* parameter */,);
		Star(const Star& copy);
		Star& operator=(const Star& obj);
		virtual ~Star();
};

std::ostream&	operator<<(std::ostream& out, const Star& Star);

#endif
