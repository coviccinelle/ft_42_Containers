/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:25:09 by thi-phng          #+#    #+#             */
/*   Updated: 2023/03/03 17:58:40 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
		struct pair
		{
			typedef T1 first_type;
			typedef T2 second_type;

			first_type		first;
			second_type		second;


				// *** default *** //
			pair(void) : first(), second() {}
				// *** copy *** //
			pair(const T1& x, const T2& y) : first(x), second(y) {}

				// *** copy template *** //
			template <class U1, class U2>
				pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

				// *** = operator *** //
			pair& operator=(const pair& other)
			{
				if (this != &other)
				{
					first = other.first;
					second = other.second;
				}
				return *this;
			}

		};

	template <typename Pair1, typename Pair2>
		bool operator==(const ft::pair<Pair1, Pair2>& x, const ft::pair<Pair1, Pair2>& y) { return (x.first == y.first && x.second == y.second); }

	template <typename Pair1, typename Pair2>
		bool operator!=(const ft::pair<Pair1, Pair2>& x, const ft::pair<Pair1, Pair2>& y) { return (!(x == y)); }

	template <typename Pair1, typename Pair2>
		bool operator<(const ft::pair<Pair1, Pair2>& x, const ft::pair<Pair1, Pair2>& y) { return (x.first < y.first || (x.first == y.first && x.second < y.second)); }

	template <typename Pair1, typename Pair2>
		bool operator>(const ft::pair<Pair1, Pair2>& x, const ft::pair<Pair1, Pair2>& y) { return (y < x); }

	template <typename Pair1, typename Pair2>
		bool operator>=(const ft::pair<Pair1, Pair2>& x, const ft::pair<Pair1, Pair2>& y) { return (!(x < y)); }

	template <typename Pair1, typename Pair2>
		bool operator<=(const ft::pair<Pair1, Pair2>& x, const ft::pair<Pair1, Pair2>& y) { return (!(y < x)); }

	/*
    ** Construct a pair object with "first" and "second".
    ** Return the pair object.
    */
	template<typename T1, typename T2> ft::pair<T1, T2> 	make_pair(T1 first, T2 second)
	{
		return ft::pair<T1, T2>(first, second);
	}

}
#endif
