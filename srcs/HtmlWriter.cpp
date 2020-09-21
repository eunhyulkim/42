#include "HtmlWriter.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

HtmlWriter::HtmlWriter()
: m_body("<html>\n<body>\n</body>\n</html>\n") {}

HtmlWriter::HtmlWriter(const HtmlWriter& copy)
: m_body(copy.get_m_body()) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

HtmlWriter::~HtmlWriter() {
	this->m_body.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

HtmlWriter& HtmlWriter::operator=(const HtmlWriter& obj)
{
	if (this == &obj)
		return (*this);
	this->m_body = obj.get_m_body();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const HtmlWriter& htmlWriter)
{
	out << htmlWriter.get_m_body();
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string HtmlWriter::get_m_body() const { return (this->m_body); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void HtmlWriter::set_m_body(std::string body) { this->m_body = body; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
HtmlWriter::add_title(std::string title_content)
{
	std::string token = "<title>" + title_content + "</title>";
	if (m_body.find("<head>") == std::string::npos) {
		m_body.insert(m_body.find("\n") + 1, "<head></head>\n");
	}
	m_body.insert(m_body.find("<head>") + 6, token);
}

void
HtmlWriter::add_bgcolor(std::string bg_color)
{
	int idx = m_body.find("<body");
	std::string token = " bgcolor=\"" + bg_color + "\"";
	if (m_body[idx + 5] == '>') {
		idx += 5;
	} else {
		while (m_body[idx] != '>')
			++idx;
	}
	m_body.insert(idx, token);
}

void
HtmlWriter::add_tag(std::string front_token, std::string tag, std::string content, bool newline)
{
	std::string token = "<" + tag + ">";

	if (newline)
		token.append("\n");
	token.append(content);
	token.append("</" + tag + ">\n");
	m_body.insert(m_body.find(front_token) + front_token.size(), token);
}

void
HtmlWriter::add_link(std::string address, std::string front_token, std::string content)
{
	std::string token = "<a href=\"" + address + "\">";
	if (!content.empty())
		token.append(content);
	else
		token.append(address);
	token.append("</a>\n");
	int idx = m_body.find("</body>");
	if (front_token.empty() && m_body.find("<a href") == std::string::npos) {
		idx = m_body.find("<body") + 5;
		while (m_body[idx] != '>')
			++idx;
		idx += 2;
	}
	else if (!front_token.empty())
		idx = m_body.rfind(front_token) + front_token.size();
	else
		idx = m_body.rfind("/a>") + 4;
	m_body.insert(idx, token);
}
