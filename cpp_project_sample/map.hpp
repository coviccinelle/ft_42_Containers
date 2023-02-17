/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:24:04 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/15 13:24:33 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

namespace ft
{
	class map
	{
		public:
			map(void);
			~map(void);
			map(map const &src);
			map	&operator=(map const &rhs);
		private:
	};
}
#endif
