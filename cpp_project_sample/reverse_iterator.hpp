/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:51:45 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/26 13:10:46 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

//# include "vector.hpp"
# include "iterator_traits.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
	template< class Iterator >
		class reverse_iterator
		{
			public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
//			typedef typename iterator_traits<Iterator>::reference const		const_reference;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename std::size_t									size_type;

			protected:
				iterator_type	_it;

			public:
			// constructor
			reverse_iterator(void) : _it(Iterator()) {};
			explicit reverse_iterator( iterator_type x ) : _it(x) {};
			template< class U >
				reverse_iterator( const reverse_iterator<U>& other ) : _it(other.base()) {}

			reverse_iterator( const reverse_iterator< Iterator >& other ) : _it(other._it) {};
			~reverse_iterator() {};

			reverse_iterator &operator=(const reverse_iterator &other){
				this->_it = other._it;
				return (*this);
			}
///user-defined conversion function/
//			operator	reverse_iterator<iterator_type<value_type const> >() const
//			{return (reverse_iterator<iterator_type<value_type const> >(_ptr));}
//			operator	reverse_iterator<iterator_type<value_type> >()
//			{return (reverse_iterator<iterator_type<value_type> >(_ptr));}

			iterator_type base() const { return (_it); }

			reference operator*() const {
				iterator_type tmp = _it;
				return *(--tmp);
			}

			pointer operator->() const{ return (&operator*()); }

			reference operator[](size_t n) const { return (_it[-n - 1]); }
//---------------------------------------------------------------------------//
			//assignment
			reverse_iterator& operator+=(difference_type n){
				_it -= n;
				return(* this); }		

			reverse_iterator& operator-=(difference_type n){
				_it += n;
				return(* this); }

			// arithmetic
			reverse_iterator operator+(difference_type n) const
			{
				if (n < 0)
					return (operator-(-n));
				reverse_iterator it(_it);
				for (difference_type i = 0; i < n; i++)
					++it;
				return (it);
			}		

			friend reverse_iterator operator+(size_t i, const reverse_iterator& it) { return it + i;}

			reverse_iterator operator-(difference_type n) const
			{
				if (n < 0)
					return (operator+(-n));
				reverse_iterator it(_it);;
				for (difference_type i = 0; i < n; i++)
					--it;
				return (it);
			}

//			reverse_iterator operator-(size_type n) const { return (reverse_iterator(_it.operator+(n))); }		
//			difference_type operator-(const difference_type& n) const {
//				return (_it + n - 1) - _it.begin();
//			}

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


				//--------------------------------//
				//	 ***  NON_MEMBERS  	***   //
				//--------------------------------//
				//
	template< class Iterator1, class Iterator2 >
		bool operator==( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.base() == y.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator!=( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.base() != y.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator<( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.base() > y.base() ;}
//		bool operator<( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.operator>( y.base()) ;}

	template< class Iterator1, class Iterator2 >
		bool operator>( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.base() < y.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator<=( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.base() >= y.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator>=( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y ) { return x.base() <= y.base() ;}

	template< class Iterator>
		reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{return (rev_it.base() + n);}

	template< class Iterator1, class Iterator2 >
		typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y )
		{ return y.base().operator-(x.base()) ; }
//		{ return y.base() - x.base() ; }

}

#endif

