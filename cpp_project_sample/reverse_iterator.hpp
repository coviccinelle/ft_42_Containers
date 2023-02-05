/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:51:45 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/05 11:24:01 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

//#include "random_acc_iterator.hpp"
#include "vector.hpp"
#include "iterator_traits.hpp"

namespace ft{
	template< class Iterator >
	class reverse_iterator{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename std::size_t									size_type;
	// constructor
			reverse_iterator(void) : _it(Iterator()) {};
			explicit reverse_iterator( iterator_type x ) : _it(x) {};

			reverse_iterator( const reverse_iterator< Iterator >& other ) : _it(other._it) {};
			~reverse_iterator() {};
			
			reverse_iterator &operator=(const reverse_iterator &other){
				this->_it = other._it;
				return (*this);
			}
			iterator_type base() const{
				return (_it);
			}
			reference operator*() const {
				return (*(_it - 1));
			}
//			pointer operator->() const{ return (this->_it); }
			reference operator[](size_t n) const { return (_it[-n - 1]); }
		private:
			iterator_type	_it;

		public:
//			//assignment
		    reverse_iterator& operator+=(size_type n){
				_it -= n;
				return(* this); }		

		    reverse_iterator& operator-=(size_type n){
				_it += n;
			 	return(* this); }

			// arithmetic
			reverse_iterator operator+(size_type n) const{
				reverse_iterator it(_it);
				it += n;
				return (it);
			}		

			friend reverse_iterator operator+(size_t i, const reverse_iterator& it) { return it + i;}

			reverse_iterator operator-(size_type n) const { return (reverse_iterator(_it + n)); }		

			difference_type operator+(reverse_iterator const &other) const {  return (this->_it - other._it); }		

			difference_type operator-(reverse_iterator const &other) const { return (this->_it + other._it); }		
//	//bool
			bool	operator==(const reverse_iterator& other) const
				{return _it == other._it;}

			bool	operator!=(const reverse_iterator& other) const
				{return _it != other._it;}

			bool	operator<(const reverse_iterator& other) const
				{return _it > other._it;}

			bool	operator>(const reverse_iterator& other) const
				{return _it < other._it;}

			bool	operator<=(const reverse_iterator& other) const
				{return _it >= other._it;}

			bool	operator>=(const reverse_iterator& other) const
				{return _it <= other._it;}
//			
//	//increment/decrement
//			//pre-increment (++a)
    		reverse_iterator& operator++()
			{
				--_it;
				return (*this); 
			}
//			//post-decrement (--a)
    		reverse_iterator& operator--(){
				++_it;
				return (*this); 
			}
//			// post-increment (a++)
    		reverse_iterator operator++(int){
				reverse_iterator tmp(*this);
				--(_it);
			 	return (tmp);
			}
			//pret-decrement (a--)
    		reverse_iterator operator--(int){
				reverse_iterator tmp(*this);
				++(_it);
				return (tmp);
			}


	};
}

#endif
















/*
			operator reverse_iterator<Iterator<value_type const> > () const{
				return (reverse_iterator< value_type const> (_it));
			}
			operator reverse_iterator<Iterator<value_type> > () {
				return (reverse_iterator<value_type > >(_it));
			}
*/
