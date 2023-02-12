/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:40:05 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/12 14:00:45 by thi-phng         ###   ########.fr       */
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
				typedef typename container_type::size_type		container_type;

			protected:
				container_type		_ctn;
			public:
				stack(void);
				~stack(void);
				stack(stack const &src);
				stack	&operator=(stack const &rhs);

		};

}
#endif
