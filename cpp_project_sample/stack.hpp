/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:40:05 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/12 14:48:11 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

//https://en.cppreference.com/w/cpp/container/stack
//https://cplusplus.com/reference/stack/stack/

// stack container, which is a data structure that implements a last-in-first-out (LIFO) policy.
// The stack container is defined in the <stack> header file and is implemented as an adapter class 
// over a container, such as deque or vector.

namespace ft
{
	template <class Type, class Container = ft::vector<Type> >
		class stack
		{
			public:
				typedef	Type									value_type;
				typedef	Container								container_type;
				typedef typename container_type::size_type		size_type;
			//protected:
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

			protected:
				container_type		c;
			public:
				stack(const stack &other) : c(other.c) {}
				explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
				~stack(void) {}

				stack	&operator=(stack const &other)
				{
					if (this != &other)
						c = other.c;
					return (*this);
				}

				//--------------------------------//
				//	 *** 	ELEMENT ACCESS 	 ***  //
				//--------------------------------//

				reference top() { return (c.back()); }
				const_reference top() const { return ( c.back()); }

				//--------------------------------//
				//	 *** 	 CAPACITY		 ***  //
				//--------------------------------//
				// ( empty, size )

				bool empty() const { return (c.empty()); }
				size_type size() const { return (c.size()); }

				//--------------------------------//
				//	 *** 	 MODIFIERS		 ***  //
				//--------------------------------//
				//	( push, pop)

				void push( const value_type& value ) { return (c.push_back(value)); }
				void pop() { return (c.pop_back()); }

		};

	template< class Type, class Container >
		bool operator==( const stack<Type, Container>& x, const stack<Type, Container>& y )
		{return (x.c == y.c);}

		template< class Type, class Container >
		bool operator!=( const stack<Type, Container>& x, const stack<Type, Container>& y )
		{return !(x.c == y.c);}

		template< class Type, class Container >
		bool operator< ( const stack<Type, Container>& x, const stack<Type, Container>& y )
		{return (x.c < y.c);}

		template< class Type, class Container >
		bool operator<=( const stack<Type, Container>& x, const stack<Type, Container>& y )
		{ return !(y.c < x.c); }

		template< class Type, class Container >
		bool operator> ( const stack<Type, Container>& x, const stack<Type, Container>& y )
		{ return (y.c < x.c); }

		template< class Type, class Container >
		bool operator>=( const stack<Type, Container>& x, const stack<Type, Container>& y )
		{ return !(x.c < y.c); }

}
#endif
