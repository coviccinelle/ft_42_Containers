/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:11:09 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/12 13:41:40 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "vector.hpp"
//#include "iterator_traits.hpp"

namespace ft
{
	template< class Iter >
		class iterator_traits{
			public:
				typedef typename Iter::difference_type   difference_type;
				typedef typename Iter::value_type        value_type;
				typedef typename Iter::pointer           pointer;	
				typedef typename Iter::reference         reference;
				typedef typename Iter::iterator_category iterator_category;
		};


	template< class T >
		class iterator_traits<T*>{
			public:
				typedef std::ptrdiff_t						difference_type;
				typedef T									value_type;
				typedef T*									pointer;
				typedef T&									reference;
				typedef std::random_access_iterator_tag		iterator_category;
		};


	template< class T >
		class iterator_traits<const T*>{
			public:
				typedef std::ptrdiff_t						difference_type;
				typedef const T								value_type;
				typedef const T*							pointer;
				typedef const T&							reference;
				typedef std::random_access_iterator_tag		iterator_category;
		};

}

#endif
