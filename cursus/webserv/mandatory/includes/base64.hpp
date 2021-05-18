/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 04:40:14 by eunhkim           #+#    #+#             */
/*   Updated: 2020/10/17 04:40:15 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H_
#define BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;

namespace ft {
    std::string base64_encode(BYTE const* buf, unsigned int bufLen);
    std::vector<BYTE> base64_decode(std::string const&);
}
#endif
