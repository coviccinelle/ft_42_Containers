/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:12:05 by thi-phng          #+#    #+#             */
/*   Updated: 2023/03/03 22:11:40 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

//https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
namespace ft
{
	template <class It1, class It2>
		bool lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2)
		{
			while (first1 != last1 && first2 != last2)
			{
				if (*first1 < *first2)
					return true;
				if (*first2 < *first1)
					return false;
				++first1;
				++first2;
			}
			return (first1 == last1 && first2 != last2);
		}

}
#endif
