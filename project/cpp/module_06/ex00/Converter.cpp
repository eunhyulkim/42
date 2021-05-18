#include "Converter.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Converter::Converter() {
	this->m_char = 0;
	this->m_int = 0;
	this->m_float = 0;
	this->m_double = 0;
	for (int i = 0; i < 4; i++)
		this->m_status[i] = DEFAULT;
}

Converter::Converter(const Converter&) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Converter::~Converter() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Converter& Converter::operator=(const Converter&) { return (*this); }

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Converter::get_m_type() const { return (this->m_type); }
int Converter::get_m_status(int nth) const { return (this->m_status[nth]); }
char Converter::get_m_char() const { return (this->m_char); }
int Converter::get_m_int() const { return (this->m_int); }
float Converter::get_m_float() const { return (this->m_float); }
double Converter::get_m_double() const { return (this->m_double); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Converter::set_m_status(int nth, int v) { this->m_status[nth] = v; }
void Converter::set_m_char(char c) { this->m_char = c; }
void Converter::set_m_int(int n) { this->m_int = n; }
void Converter::set_m_float(float f) { this->m_float = f; }
void Converter::set_m_double(double d) { this->m_double = d; }

namespace {
	bool is_double(std::string data)
	{
		bool e_occur = false;
		bool dot_occur = false;
		int size = static_cast<int>(data.size());
		for (int i = 0; i < size; i++)
		{
			if (data[i] < 48 || data[i] > 57)
			{
				if (data[i] == '+' || data[i] == '-')
				{
					if (i == 0 || (data[i - 1] == 'e' && (i != size - 1) && data[i + 1] >= 48 && data[i + 1] <= 57))
						continue ;
					else
						return (false);
				}
				else if (data[i] == 'e' && e_occur == false)
				{
					if (data[i + 1] == '-' || data[i + 1] == '+')
						e_occur = true;
					else
						return (false);
				}
				else if (data[i] == '.' && dot_occur == false)
				{
					if (data[i - 1] >= 48 && data[i - 1] <= 57 && ((static_cast<int>(data.size()) - 1 == i) || data[i + 1] != 'e'))
						dot_occur = true;
					else
						return (false);
				}
				else
					return (false);
			}
		}
		return (true);
	}

	bool parse_type_char(Converter& machine, const std::string& data)
	{
		if (data.size() == 1 && (data[0] < 48 || data[0] > 57))
			machine.set_m_char(data[0]);
		else if (data.size() == 3 && data[0] == '\'' && data[2] == '\'')
			machine.set_m_char(data[1]);
		else
			return (false);
		if (machine.get_m_char() < 32 || machine.get_m_char() > 126)
			machine.set_m_status(CHAR_STAT, NON_DISPLAYABLE);
		return (true);
	}

	bool parse_type_int(Converter& machine, const std::string& data)
	{
		std::string newData = data;

		if (newData.size() == 1 && (newData[0] == '-' || newData[0] == '+'))
			return (false);
		if (newData.size() == 2 && newData[0] == '-' && newData[1] == '0')
			newData = "0";
		if (newData.size() >= 2 && newData[0] == '+')
			newData = newData.substr(1);
		for (int i = 0; i < static_cast<int>(newData.size()); i++)
		{
			if (newData[i] < 48 || newData[i] > 57)
			{
				if (i != 0 || (newData[i] != '+' && newData[i] != '-'))
					return (false);
			}
		}
		try {
			machine.set_m_int(stoi(data));
		} catch (std::out_of_range& e) {
			machine.set_m_status(INT_STAT, IMPOSSIBLE);
		}
		return (true);
	}

	bool parse_type_float(Converter& machine, const std::string& data)
	{
		if (data == "nanf")
			machine.set_m_status(FLOAT_STAT, NANV);
		else if (data == "inff" || data == "+inff")
			machine.set_m_status(FLOAT_STAT, INF);
		else if (data == "-inff")
			machine.set_m_status(FLOAT_STAT, NINF);
		else if (data[data.size() - 1] != 'f')
			return (false);
		else if (data.size() == 2 && (data[0] == '+' || data[0] == '-'))
			return (false);
		else if (data[0] == '.' || ((data[0] == '+' || data[0] == '-') && data[1] == '.'))
			return (false);
		if (data == "nanf" || data == "inff" || data == "+inff" || data == "-inff")
			return (true);
		if (data == "nan" || data == "inf" || data == "+inf" || data == "-inf")
			return (false);
		if (is_double(data.substr(0, data.size() - 1)) == false)
			return (false);
		try {
			machine.set_m_float(std::stof(data));
		} catch (std::invalid_argument&) {
			return (false);
		} catch (std::out_of_range&) {
			machine.set_m_status(FLOAT_STAT, IMPOSSIBLE);
			return (true);
		}

		std::ostringstream out;
		out << machine.get_m_float();
		std::string t = out.str();
		if (t.find("e") != std::string::npos)
			machine.set_m_status(FLOAT_STAT, SCIENCE);
		else if (t.find(".") == std::string::npos)
			machine.set_m_status(FLOAT_STAT, INTEGER);
		
		return (true);
	}

	bool parse_type_double(Converter& machine, const std::string& data)
	{
		if (data == "nan")
			machine.set_m_status(DOUBLE_STAT, NANV);
		else if (data == "inf" || data == "+inf")
			machine.set_m_status(DOUBLE_STAT, INF);
		else if (data == "-inf")
			machine.set_m_status(DOUBLE_STAT, NINF);
		else if (data.size() == 1 && (data[0] < 32 || data[0] > 126))
			return (false);
		else if (data[0] == '.' || (data.size() == 2 && (data[0] == '+' || data[0] == '-') && data[1] == '.'))
			return (false);
		if (data == "nanf" || data == "inff" || data == "+inff" || data == "-inff")
			return (false);
		if (data == "nan" || data == "inf" || data == "+inf" || data == "-inf")
			return (true);
		if (is_double(data) == false)
			return (false);
		try {
			machine.set_m_double(std::stod(data));
		} catch (std::invalid_argument&) {
			return (false);
		} catch (std::out_of_range&) {
			machine.set_m_status(DOUBLE_STAT, IMPOSSIBLE);
			return (true);
		}	

		std::ostringstream out;
		out << machine.get_m_double();
		std::string t = out.str();
		if (t.find("e") != std::string::npos)
			machine.set_m_status(DOUBLE_STAT, SCIENCE);
		else if (t.find(".") == std::string::npos)
			machine.set_m_status(DOUBLE_STAT, INTEGER);

		return (true);
	}
}

void Converter::parse(const std::string& data) 
{	
	this->m_data = data;
	if (parse_type_char(*this, data))
		this->m_type = "char";
	else if (parse_type_int(*this, data))
		this->m_type = "int";
	else if (parse_type_float(*this, data))
		this->m_type = "float";
	else if (parse_type_double(*this, data))
		this->m_type = "double";
	else
	{
		for (int i = 0; i < 4; i++)
			set_m_status(i, IMPOSSIBLE);
		this->m_type = data;
	}
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

namespace {
	void setRangeStatus(Converter& machine, int start, int last, int status)
	{
		for (int i = start; i <= last; i++)
			machine.set_m_status(i, status);
	}
}

void
Converter::charToOthers(void)
{
	this->m_int = static_cast<int>(this->m_char);
	this->m_float = static_cast<float>(this->m_char);
	this->m_double = static_cast<double>(this->m_char);
	this->set_m_status(FLOAT_STAT, INTEGER);
	this->set_m_status(DOUBLE_STAT, INTEGER);
}

void
Converter::intToOthers(void)
{
	if (this->get_m_status(INT_STAT) == IMPOSSIBLE)
		return (setRangeStatus(*this, 0, 3, IMPOSSIBLE));

	this->m_char = static_cast<char>(this->m_int);
	this->m_float = static_cast<float>(this->m_int);
	this->m_double = static_cast<double>(this->m_int);

	if (this->m_int < 0 || this->m_int > 255)
		this->set_m_status(CHAR_STAT, IMPOSSIBLE);
	else if (this->m_int < 32 || this->m_int > 126)
		this->set_m_status(CHAR_STAT, NON_DISPLAYABLE);

	std::ostringstream out;
	out << static_cast<double>(this->m_int);
	std::string t = out.str();
	if (t.find("e") != std::string::npos)
		setRangeStatus(*this, FLOAT_STAT, DOUBLE_STAT, SCIENCE);
	else
		setRangeStatus(*this, FLOAT_STAT, DOUBLE_STAT, INTEGER);
}

void
Converter::floatToOthers(void)
{	
	
	int status = this->get_m_status(FLOAT_STAT);
	this->set_m_status(DOUBLE_STAT, status);
	if (status == INF || status == NINF || status == NANV || status == IMPOSSIBLE)
	{
		setRangeStatus(*this, 0, 1, IMPOSSIBLE);
		return ;
	}

	if (status != INTEGER || this->m_float < 0 || this->m_float > 255)
		this->m_status[CHAR_STAT] = IMPOSSIBLE;
	else if (static_cast<int>(this->m_float) < 32 || static_cast<int>(this->m_float) > 126)
		this->m_status[CHAR_STAT] = NON_DISPLAYABLE;
	else
		this->set_m_char(static_cast<char>(this->m_float));

	if (this->m_float > std::numeric_limits<int>::max() || this->m_float < std::numeric_limits<int>::min())
		this->m_status[INT_STAT] = IMPOSSIBLE;
	else
		this->m_int = static_cast<int>(this->m_float);

	this->m_double = static_cast<double>(this->m_float);
}

void
Converter::doubleToOthers(void)
{
	int status = this->get_m_status(DOUBLE_STAT);
	this->set_m_status(FLOAT_STAT, status);
	if (status == INF || status == NINF || status == NANV || status == IMPOSSIBLE)
	{
		setRangeStatus(*this, 0, 1, IMPOSSIBLE);
		return ;
	}

	if (status != INTEGER || this->m_double < 0 || this->m_double > 255)
		this->m_status[CHAR_STAT] = IMPOSSIBLE;
	else if (static_cast<int>(this->m_double) < 32 || static_cast<int>(this->m_double) > 126)
		this->m_status[CHAR_STAT] = NON_DISPLAYABLE;
	else
		this->set_m_char(static_cast<char>(this->m_double));

	if (this->m_double > std::numeric_limits<int>::max() || this->m_double < -std::numeric_limits<int>::max())
		this->m_status[INT_STAT] = IMPOSSIBLE;
	else
		this->m_int = static_cast<int>(this->m_double);

	if (this->m_double > std::numeric_limits<float>::max() || this->m_double < -std::numeric_limits<float>::max())
		this->m_status[FLOAT_STAT] = IMPOSSIBLE;
	else
		this->m_float = static_cast<float>(this->m_double);
}

void
Converter::convert(void) {
	if (this->m_type == "char")
		this->charToOthers();
	else if (this->m_type == "int")
		this->intToOthers();
	else if (this->m_type == "float")
		this->floatToOthers();
	else if (this->m_type == "double")
		this->doubleToOthers();
}

namespace {
	std::string charToStr(const Converter& machine)
	{
		char c = machine.get_m_char();
		int status = machine.get_m_status(CHAR_STAT);

		if (status == NON_DISPLAYABLE)
			return ("Non displayable");
		else if (status == IMPOSSIBLE)
			return ("impossible");
		else
		{
			char a[4] = {'\'', c, '\'', 0};
			return (a);
		}
	}

	std::string intToStr(const Converter& machine)
	{
		int n = machine.get_m_int();
		int status = machine.get_m_status(INT_STAT);

		if (status == IMPOSSIBLE)
			return ("impossible");
		else
			return (std::to_string(n));
	}

	std::string floatToStr(const Converter& machine)
	{
		std::ostringstream ss;
		ss << machine.get_m_float();
		std::string f(ss.str());
		int status = machine.get_m_status(FLOAT_STAT);

		if (status == IMPOSSIBLE)
			return ("impossible");
		else if (status == NANV)
			return ("nanf");
		else if (status == INF)
			return ("+inff");
		else if (status == NINF)
			return ("-inff");
		else if (status == SCIENCE || status == DEFAULT)
			return (f + "f");
		else if (status == INTEGER)
			return (f + ".0f");	
		return ("impossible");
	}

	std::string doubleToStr(const Converter& machine)
	{
		std::ostringstream ss;
		ss << machine.get_m_double();
		std::string d(ss.str());
		int status = machine.get_m_status(DOUBLE_STAT);

		if (status == IMPOSSIBLE)
			return ("impossible");
		else if (status == NANV)
			return ("nan");
		else if (status == INF)
			return ("+inf");
		else if (status == NINF)
			return ("-inf");
		else if (status == INTEGER)
			return (d + ".0");		
		else if (status == SCIENCE || status == DEFAULT)
			return (d);
		return ("impossible");
	}
}

void
Converter::print(void) {
	std::cout << "char: " << charToStr(*this) << std::endl;
	std::cout << "int: " << intToStr(*this) << std::endl;
	std::cout << "float: " << floatToStr(*this) << std::endl;
	std::cout << "double: " << doubleToStr(*this) << std::endl;
}
