/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:29:59 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/10 11:32:16 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

//using template specialization and overloading

namespace ft
{
	template <bool B, typename T = void>
		struct enable_if {};

	template <typename T>
		struct enable_if<true, T>
		{
			typedef T type;
		};
}

#endif
