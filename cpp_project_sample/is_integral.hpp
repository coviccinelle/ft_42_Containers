/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:26:38 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/10 11:27:42 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

# ifdef __APPLE__
#  include <stdint.h>
# else
#  include <uchar.h>
# endif

namespace ft
{
	template <typename T>
		struct is_integral
		{const static bool value = false;};

	template <>
		struct is_integral<char>
		{const static bool value = true;};

	template <>
		struct is_integral<char16_t>
		{const static bool value = true;};

	template <>
		struct is_integral<char32_t>
		{const static bool value = true;};

	template <>
		struct is_integral<wchar_t>
		{const static bool value = true;};

	template <>
		struct is_integral<short>
		{const static bool value = true;};

	template <>
		struct is_integral<int>
		{const static bool value = true;};

	template <>
		struct is_integral<long>
		{const static bool value = true;};

	template <>
		struct is_integral<long long>
		{const static bool value = true;};
}

#endif
