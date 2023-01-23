/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:51:45 by thi-phng          #+#    #+#             */
/*   Updated: 2023/01/23 11:28:17 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR__HPP

#include <ft/vector.hpp>

namespace ft{
	template< class iterator >
	class reverse_iterator{
		private:
			typedef iterator 	vit;
			iterator			_ptr;


		public:
			typedef iterator   							iterator_type;	
			typedef typename vit::difference_type		difference_type;			
			typedef typename vit::reference				reference;		
			typedef typename vit::pointer				pointer;		

	// constructor
			reverse_iterator(void) : _ptr() {};
			explicit reverse_iterator( iterator_type x ) : _ptr(x) {};

			reverse_iterator( const reverse_iterator< iterator >& other ) : _ptr(other._ptr_ {} ;
			~reverve_iterator() {};
			








	};
}

#endif
