/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:08:32 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/12 13:19:29 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

//https://en.cppreference.com/w/cpp/algorithm/equal
namespace ft
{
	template <class Ite1, class Ite2>
		bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
		{
			while (first1 != last1)
			{
				if (*first1 != *first2)
					return false;
				++first1;
				++first2;
			}
			return true;
		}
	template< class It1, class It2, class BinaryPredicate >
			bool equal( It1 first1, It1 last1, It2 first2, BinaryPredicate pred )
			{
				while (first1 != last1)
				{
					if (!pred(*first1, *first2))
						return (false);
					++first1;
					++first2;
				}
				return (true);
			}

	template <class Ite>
		size_t distance(Ite first, Ite last)
		{
			size_t i = 0;
			while (first != last) {
				++first;
				++i;
			}
			return i;
		}
}
#endif
