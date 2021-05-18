/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.ipp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhkim <eunhkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 17:11:08 by eunhkim           #+#    #+#             */
/*   Updated: 2020/08/16 17:16:43 by eunhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<typename T>
void Span::addNumber(T begin, T end)
{
    if (this->m_vector.size() + std::distance(begin, end) > this->m_size)
        throw (Span::FullSpanException());
    this->m_vector.insert(this->m_vector.end(), begin, end);
}
