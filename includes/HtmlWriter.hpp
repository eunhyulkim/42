#ifndef HTML_WRITER_HPP
# define HTML_WRITER_HPP

# include <string>
# include <iostream>

class HtmlWriter
{
	private:
		std::string m_body;
	public:
		HtmlWriter();
		HtmlWriter(const HtmlWriter& copy);
		HtmlWriter& operator=(const HtmlWriter& obj);
		virtual ~HtmlWriter();

		/* getter function */
		std::string get_m_body() const;

		/* setter function */
		void set_m_body(std::string body);

		/* declare member function */
		void add_title(std::string head_content);
		void add_bgcolor(std::string bg_color);
		void add_tag(std::string front_token, std::string tag, std::string content = "", bool newline = false);
		void add_link(std::string address, std::string front_token = "", std::string content = "");
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const HtmlWriter& htmlWriter);

#endif
