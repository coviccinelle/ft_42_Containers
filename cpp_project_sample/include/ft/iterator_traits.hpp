/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:11:09 by thi-phng          #+#    #+#             */
/*   Updated: 2023/01/20 17:35:16 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP


namespace ft{
	template< class Iter >
	struct iterator_traits{
		typedef Iter::difference_type   difference_type		
		typedef Iter::value_type        value_type			
		typedef Iter::pointer           pointer				
		typedef Iter::reference         reference			
		typedef Iter::iterator_category iterator_category	
	};


	template< class T >
	struct iterator_traits<T*>{
		typedef std::ptrdiff_t						difference_type		
		typedef T									value_type			
		typedef T*									pointer				
		typedef T&									reference			
		typedef std::random_access_iterator_tag		iterator_category	
	};
	

	template< class T >
	struct iterator_traits<const T*>{
		typedef std::ptrdiff_t						difference_type		
		typedef const T								value_type			
		typedef const T*							pointer				
		typedef const T&							reference			
		typedef std::random_access_iterator_tag		iterator_category	
	};
}

#endif
