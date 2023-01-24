/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:51:45 by thi-phng          #+#    #+#             */
/*   Updated: 2023/01/24 16:42:46 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR__HPP

#include "vector.hpp"
#include "iterator_traits.hpp"

namespace ft{
	template< class iterator >
	class reverse_iterator{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;

	// constructor
			reverse_iterator(void) : _ptr() {};
			explicit reverse_iterator( iterator_type x ) : _ptr(x) {};

			reverse_iterator( const reverse_iterator< iterator >& other ) : _ptr(other._ptr_ {} ;
			~reverve_iterator() {};
			
			reverse_iterator &operator=(const reverse_iterator &other){
				_ptr = other._ptr;
				return (*this);
			}

			operator reverse_iterator<iterator<value_type const> > () const{
				return (reverse_iterator<value_type const> >(_ptr));
			}
			operator reverse_iterator<iterator<value_type > > () {
				return (reverse_iterator<value_type > >(_ptr));
			}
			iterator_type base() const{
				return (_ptr);	
			}

	//bool
			bool	operator==(const reverse_iterator& other) const
				{return _ptr == other._ptr;}
			bool	operator!=(const reverse_iterator& other) const
				{return _ptr != other._ptr;}
			bool	operator<(const reverse_iterator& other) const
				{return _ptr < other._ptr;}
			bool	operator>(const reverse_iterator& other) const
				{return _ptr > other._ptr;}
			bool	operator<=(const reverse_iterator& other) const
				{return _ptr >= other._ptr;}
			bool	operator>=(const reverse_iterator& other) const
				{return _ptr <= other._ptr;}
			
	//increment/decrement
			//pre-increment (++a)
    		reverse_iterator& operator++()
			{
				++_ptr;
				return (*this); 
			}
			//post-decrement (--a)
    		reverse_iterator& operator--(){
				--_ptr;
				return (*this); 
			}
			// post-increment (a++)
    		reverse_iterator operator++(int){
				iterator tmp(*this);
				++(*this);
			 	return (tmp);
			}
			//pret-decrement (a--)
    		reverse_iterator operator--(int){
				iterator tmp(*this);
				--(*this);
				return (tmp);
			}



		private:
			iterator_type			_ptr;



	};
}

#endif
