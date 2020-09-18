/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yopark <yopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 15:45:39 by yopark            #+#    #+#             */
/*   Updated: 2020/09/18 16:51:54 by yopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <iostream>

	    // enum Method { GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE };
        // enum URIType { DIRECTORY, FILE, CGI_PROGRAM };
        // enum TransferType { GENERAL, CHUNKED };

int main(void)
{
	try
	{
		Request a(NULL, NULL, "PUT /a.out HTTP/1.1");
		std::cout << a.get_m_method() << ' ';
		std::cout << a.get_m_uri() << ' ';
		std::cout << a.get_m_uri_type() << ' ';
		std::cout << a.get_m_protocol() << ' ';
		std::cout << a.get_m_transfer_type() << ' ';
		std::cout << std::endl;

		a.add_header("Content-Type: chunked ");
		std::cout << a.get_m_transfer_type() << std::endl;
		a.add_header("Host: www.example.com");
		// a.add_header("content-length: 424242");
		a.add_content("<!DOCTYPE html>\n");
		a.add_content("<head></head>\n");
		std::cout << a.get_m_content() << std::endl;
	}
	catch (const char *e)
	{
		std::cerr << e << std::endl;
	}
	return (0);
}