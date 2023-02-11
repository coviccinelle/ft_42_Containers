/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:51:45 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/11 17:29:24 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

//#include "random_acc_iterator.hpp"
#include "vector.hpp"
#include "iterator_traits.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
	template< class Iterator >
		class const_reverse_iterator ;
	template< class Iterator >
		class reverse_iterator
		{
			template< class Iterator3 >
				friend class const_reverse_iterator ;
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
			template< class U >
				reverse_iterator( const reverse_iterator<U>& other ) : _it(other.base()) {}
//			explicit reverse_iterator( const_reverse_iterator<Iterator> x) : _it(x.base()) {}
//			explicit reverse_iterator( reverse_iterator<Iterator> const & x) : _it(x.base()) {}

			reverse_iterator( const reverse_iterator< Iterator >& other ) : _it(other._it) {};
//			reverse_iterator( const const_reverse_iterator< Iterator >& other ) : _it(other._it) {};
			~reverse_iterator() {};

			reverse_iterator &operator=(const reverse_iterator &other){
				this->_it = other._it;
				return (*this);
			}
//
//			operator	reverse_iterator<iterator_type<value_type const> >() const
//			{return (reverse_iterator<iterator_type<value_type const> >(_ptr));}
//			operator	reverse_iterator<iterator_type<value_type> >()
//			{return (reverse_iterator<iterator_type<value_type> >(_ptr));}
//

			iterator_type base() const { return (_it); }
			reference operator*() const { return (*(_it - 1)); }
			pointer operator->() const{ return (&operator*()); }
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
//			reverse_iterator operator-(size_type n) const { return (const reverse_iterator(this->_it + n)); }		
//
//			difference_type operator+(reverse_iterator const &other) const {  return (this->_it - other._it); }		
//			template <typename U>
//				typename reverse_iterator<Iterator>::difference_type operator+(const reverse_iterator<U>& other) const {
//					return (_it - other._it); }

//			difference_type operator-(reverse_iterator const &other) const { return (this->_it + other._it); }		
//			template <typename U>
//				typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<U>& other) const {
//					return (this->_it + other._it); }

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
////	//bool
//			template <class Ii> bool	operator==(const reverse_iterator<Ii>& other) const {return this->_it == other.base();}
//			template <class Ii> bool	operator!=(const reverse_iterator<Ii>& other) const {return this->_it != other.base();}
//			template <class Ii> bool	operator<(const reverse_iterator<Ii>& other) const {return this->_it > other.base();}
//			template <class Ii> bool	operator>(const reverse_iterator<Ii>& other) const {return this->_it < other.base();}
//			template <class Ii> bool	operator<=(const reverse_iterator<Ii>& other) const {return this->_it >= other.base();}
//			template <class Ii> bool	operator>=(const reverse_iterator<Ii>& other) const {return this->_it <= other.base();}
	};


				//--------------------------------//
				//	 ***  NON_MEMBERS  	***   //
				//--------------------------------//
				//
	template< class Iterator1, class Iterator2 >
		bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() == rhs.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() != rhs.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() > rhs.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() < rhs.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() >= rhs.base() ;}

	template< class Iterator1, class Iterator2 >
		bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() <= rhs.base() ;}

//	template <class Ii> bool	operator==(const reverse_iterator<Ii>& other) const {return this->_it == other.base();}
//	template <class Ii> bool	operator!=(const reverse_iterator<Ii>& other) const {return this->_it != other.base();}
//	template <class Ii> bool	operator<(const reverse_iterator<Ii>& other) const {return this->_it > other.base();}
//	template <class Ii> bool	operator>(const reverse_iterator<Ii>& other) const {return this->_it < other.base();}
//	template <class Ii> bool	operator<=(const reverse_iterator<Ii>& other) const {return this->_it >= other.base();}
//	template <class Ii> bool	operator>=(const reverse_iterator<Ii>& other) const {return this->_it <= other.base();}
	template< class Iterator>
		reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
		{return (rev_it.base() + n);}

	template< class Iterator1, class Iterator2 >
		typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() - lhs.base() ;}
//		reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
//		{return (rev_it - n);}



//
//	template< class Iterator >
//	class const_reverse_iterator{
//		public:
//			template< class Iterator2 >
//				friend class reverse_iterator ;
//			typedef Iterator												iterator_type;
//			typedef typename iterator_traits<Iterator>::value_type			value_type;
//			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
//			typedef typename iterator_traits<Iterator>::pointer				pointer;
////			typedef typename const iterator_traits<Iterator>::pointer				const_pointer;
//			typedef typename iterator_traits<Iterator>::reference			reference;
////			typedef typename const iterator_traits<Iterator>::reference		const_reference;
//			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
//			typedef typename std::size_t									size_type;
//	// constructor
//			const_reverse_iterator(void) : _it(Iterator()) {};
//			explicit const_reverse_iterator( iterator_type x ) : _it(x) {};
//			explicit const_reverse_iterator(reverse_iterator<Iterator> x) : _it(x.base()) {
//				std::cout << "\n\nosjaioish" << std::endl;
//			}
//
//			const_reverse_iterator( const const_reverse_iterator< Iterator >& other ) : _it(other._it) {};
////			const_reverse_iterator( const reverse_iterator< Iterator >& other ) : _it(other._it) {};
//			~const_reverse_iterator() {};
//			
//			const_reverse_iterator &operator=(const const_reverse_iterator &other){
//				this->_it = other._it;
//				return (*this);
//			}
//
//			iterator_type base() const { return (_it); }
//			reference operator*() const { return (*(_it - 1)); }
//			pointer operator->() const{ return (this->_it); }
//			reference operator[](size_t n) const { return (_it[-n - 1]); }
//		private:
//			iterator_type	_it;
//
//		public:
////			//assignment
//		    const_reverse_iterator& operator+=(size_type n){
//				_it -= n;
//				return(* this); }		
//
//		    const_reverse_iterator& operator-=(size_type n){
//				_it += n;
//			 	return(* this); }
//
//			// arithmetic
//			const_reverse_iterator operator+(size_type n) const{
//				const_reverse_iterator it(_it);
//				it += n;
//				return (it);
//			}		
//
//			friend const_reverse_iterator operator+(size_t i, const const_reverse_iterator& it) { return it + i;}
//
//			const_reverse_iterator operator-(size_type n) const { return (const_reverse_iterator(_it + n)); }		
////			const_reverse_iterator operator-(size_type n) const { return (reverse_iterator(_it + n)); }		
//
//			difference_type operator+(const_reverse_iterator const &other) const {  return (this->_it - other._it); }		
//
//			difference_type operator-(const_reverse_iterator const &other) const { return (this->_it + other._it); }		
////			difference_type operator-(reverse_iterator const &other) const { return (this->_it + other._it); }		
//			template <typename U>
//				typename const_reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<U>& other) const {
//					return (_it + other._it); }
//			
////	//increment/decrement
////			//pre-increment (++a)
//    		const_reverse_iterator& operator++()
//			{
//				--_it;
//				return (*this); 
//			}
////			//post-decrement (--a)
//    		const_reverse_iterator& operator--(){
//				++_it;
//				return (*this); 
//			}
////			// post-increment (a++)
//    		const_reverse_iterator operator++(int){
//				const_reverse_iterator tmp(*this);
//				--(_it);
//			 	return (tmp);
//			}
//			//pret-decrement (a--)
//    		const_reverse_iterator operator--(int){
//				const_reverse_iterator tmp(*this);
//				++(_it);
//				return (tmp);
//			}
////	//bool
//			template <class Ii> bool	operator==(const const_reverse_iterator<Ii>& other) const {return this->_it == other.base();}
//			template <class Ii> bool	operator!=(const const_reverse_iterator<Ii>& other) const {return this->_it != other.base();}
//			template <class Ii> bool	operator<(const reverse_iterator<Ii>& other) const {return this->_it > other.base();}
//			template <class Ii> bool	operator>(const reverse_iterator<Ii>& other) const {return this->_it < other.base();}
//			template <class Ii> bool	operator<=(const reverse_iterator<Ii>& other) const {return this->_it >= other.base();}
//			template <class Ii> bool	operator>=(const reverse_iterator<Ii>& other) const {return this->_it <= other.base();}
//	};

}

#endif

