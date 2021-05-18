/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HtmlWriter.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:43:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/10/17 04:55:17 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HtmlWriter.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

/*
** make html form tag by constructor
** @param: no param
** @return: void
*/
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

/*
** add title tag in header section
** @param: tilte content
** @return: void
*/
void
HtmlWriter::add_title(std::string title_content)
{
	std::string token = "<title>" + title_content + "</title>";
	if (m_body.find("<head>") == std::string::npos) {
		m_body.insert(m_body.find("\n") + 1, "<head></head>\n");
	}
	m_body.insert(m_body.find("<head>") + 6, token);
}

/*
** add inline color css in body open tag
** @param: color of background
** @return: void
*/
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

/*
** add pair tag
** @param1: position to insert
** @param2: tag name
** @param3: content between tag
** @return: void
*/
void
HtmlWriter::add_tag(std::string front_token, std::string tag, std::string content, bool newline)
{
	std::string token = "<" + tag + ">";

	if (newline)
		token.append("\n");
	token.append(content);
	if (newline && !content.empty())
		token.append("\n");
	token.append("</" + tag + ">\n");
	m_body.insert(m_body.find(front_token) + front_token.size(), token);
}

/*
** insert text with '\n' to back of token(using rfind)
** @param: text to insert
** @return: void
*/
void
HtmlWriter::add_text(std::string front_token, std::string content, bool newline)
{
	std::string token = content;

	if (newline)
		token.append("\n");
	m_body.insert(m_body.rfind(front_token) + front_token.size(), token);
}

/*
** make a tag token with address and content
** @param1: relative/absolute path
** @param2: content in a tag
** @return: <a> token
*/
std::string
HtmlWriter::makeLink(std::string address, std::string content)
{
	std::string token = "<a href=\"" + address + "\">";
	if (!content.empty())
		token.append(content);
	else
		token.append(address);
	token.append("</a>");
	return (token);
}

/*
** insert text with '\n' by line number
** @param1: line index to insert
** @param2: line to insert
** @return: void
*/
void
HtmlWriter::add_line(int line_idx, std::string line)
{
	int idx = 1;
	int pos = 0;
	std::string body = m_body;
	while (idx < line_idx) {
		pos += body.find("\n") + 1;
		body = body.substr(body.find("\n") + 1);
		++idx;
	}

	m_body.insert(pos, line + "\n");
}
