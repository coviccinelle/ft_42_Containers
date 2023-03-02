/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:53 by thi-phng          #+#    #+#             */
/*   Updated: 2023/03/02 23:42:30 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>
# include <memory>

#include "map.hpp"

namespace ft
{
	template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair< Key, Key> > >
		class set
		{
			public:
				typedef Key										key_type;
				typedef	Key										value_type;
				typedef std::size_t								size_type;
				typedef std::ptrdiff_t							difference_type;
				typedef Compare									key_compare;
				typedef Allocator								allocator_type;
				typedef value_type								&reference;
				typedef const value_type						&const_reference;
				typedef value_type								*pointer;
				typedef const value_type						*const_pointer;
				class value_compare;
				typedef typename RB_tree<ft::pair< key_type, value_type >, value_compare>::iterator		iterator;
				typedef typename RB_tree<ft::pair< key_type, value_type >, value_compare>::const_iterator	const_iterator;
				typedef typename RB_tree<ft::pair < key_type, value_type >, value_compare>::reverse_iterator	reverse_iterator;
				typedef typename RB_tree<ft::pair < key_type, value_type >, value_compare>::const_reverse_iterator	const_reverse_iterator;


				class value_compare
				{
					public:
						bool	operator()(const value_type &a, const value_type &b) const
						{return (key_compare()(a.first, b.first));}

						value_compare	&operator=(const value_compare &)
						{return (*this);}
				};


			private:
				ft::map< Key, Key, Compare > _map;
				value_compare _value_comp;
				

			public:

				explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _map(comp, alloc)
				{
					_value_comp = value_compare();
				}

				template <class InputIt>
					set(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _map(first, last, comp, alloc)
					{
						insert(first, last);
					}

				set(const set &other)
				{
					_map = other._map;
				}

				~set(void) {}

				set	&operator=(const set &other)
				{
					_map = other._map;
					return (*this);
				}

				allocator_type	get_allocator() const {return (_map.get_allocator());}

				iterator	begin(void) {return (_map.begin());}

				const_iterator	begin(void) const {return (_map.begin());}

				iterator	end(void) {return (_map.end());}

				const_iterator	end(void) const {return (_map.end());}

				reverse_iterator	rbegin(void) {return (_map.rbegin());}

				const_reverse_iterator	rbegin(void) const {return (_map.rbegin());}

				reverse_iterator	rend(void) {return (_map.rend());}

				const_reverse_iterator	rend(void) const {return (_map.rend());}

				key_type	&at(const key_type &key)
				{
					return (_map.at(key));
				}

				const key_type	&at(const key_type &key) const
				{
					return (_map.at(key));
				}

				key_type	&operator[](const key_type &key)
				{
					return (_map[key] = ft::make_pair(key, key));
				}

				bool	empty(void) const {return (_map.size() == 0);}

				size_type	size(void) const {return (_map.size());}

				size_type	max_size(void) const {return (_map.max_size());}

				void	clear(void) {_map.clear();}

				ft::pair<iterator, bool>	insert(const value_type &value) {return (_map.insert(ft::make_pair(value, value)));}

				template <class InputIt>
					void	insert(InputIt first, InputIt last)
					{
							_map.insert(first, last);
					}

				iterator	insert(iterator hint, const value_type &value) {return (_map.insert(hint, ft::make_pair(value, value)));}

				void	erase(iterator pos) {_map.erase(pos);}

				void	erase(iterator first, iterator last)
				{
					_map.erase(first, last);
				}

				size_type	erase(const key_type &key) {return (_map.erase(ft::make_pair(key, key_type())));}

				void	swap(set &other)
				{
					_map.swap(other._map);
				}

				size_type	count(const key_type &key) const
				{
					return (_map.count(key));
				}

				iterator		find(const key_type &key) {return (_map.find(key));}
				const_iterator	find(const key_type &key) const { return (_map.find(key));}
				iterator		lower_bound(const Key &key) { return (_map.lower_bound(key));}

				const_iterator	lower_bound(const Key &key) const { return (_map.lower_bound(key));}

				iterator		upper_bound(const Key &key) { return (_map.upper_bound(key));}

				const_iterator	upper_bound(const Key &key) const { return (_map.upper_bound(key));}

				ft::pair<iterator, iterator>
					equal_range(const Key &key)
					{
						return (_map.equal_range(key));
					}

				ft::pair<const_iterator, const_iterator>
					equal_range(const Key &key) const
					{
						return (_map.equal_range(key));
					}

				key_compare	key_comp(void) const { return (_map.key_comp());}

				value_compare	value_comp(void) const { return (_map.value_comp());}

		};

	template <class Key, class T, class Compare, class Alloc>
		bool	operator==(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template <class Key, class Compare, class Alloc>
		bool	operator!=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
		{return (!(lhs == rhs));}

	template <class Key, class Compare, class Alloc>
		bool	operator<(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
		{return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}

	template <class Key, class Compare, class Alloc>
		bool	operator<=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
		{return (lhs == rhs || lhs < rhs);}

	template <class Key, class Compare, class Alloc>
		bool	operator>(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
		{return (rhs < lhs);}

	template <class Key, class Compare, class Alloc>
		bool	operator>=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs)
		{return (rhs == lhs || rhs < lhs);}

	template <class Key, class Compare, class Alloc>
		void	swap(ft::set<Key, Compare, Alloc> &lhs, ft::set<Key, Compare, Alloc> &rhs)
		{ lhs.swap(rhs); }
}

#endif