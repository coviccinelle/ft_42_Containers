/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:58:53 by thi-phng          #+#    #+#             */
/*   Updated: 2023/03/03 23:07:55 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "rbtree.hpp"
#include "equal.hpp"
#include "reverse_iterator.hpp"

//https://en.cppreference.com/w/cpp/container/set

namespace ft
{
	template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator< RB_node< Key > > >
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
				typedef tree_iterator< key_type, const key_type >	iterator;
				typedef tree_iterator< key_type, const key_type >	const_iterator;
				typedef ft::reverse_iterator< iterator >			reverse_iterator;
				typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;

				class value_compare
				{
					public:
						bool	operator()(const value_type &a, const value_type &b) const {
							return (key_compare()(a, b));}

						value_compare	&operator=(const value_compare &) {
							return (*this);}
				};


			private:
				ft::RB_tree< Key, Compare, Allocator > _tree;
				value_compare 				_value_comp;
				key_compare					_key_comp;
				

			public:

							//--------------------------------//
							//	 ***  MEMBER-FUNCTIONS	 ***  //
							//--------------------------------//

				explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _tree(alloc, comp)
				{
					_value_comp = value_compare();
				}

				template <class InputIt> set(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator()) : _tree(alloc, comp)
				{
					insert(first, last);
				}

				set(const set &x): _tree(x._tree) { }

				~set(void) {}

				set<Key, Compare, Allocator>&operator=(const set<Key, Compare, Allocator>&other)
				{
					if (this == &other)
						return (*this);
					clear();
					insert(other.begin(), other.end());
					return (*this);
				}

				allocator_type  get_allocator() const {return (allocator_type());}

							//--------------------------------//
							//	 *** 	 ITERATORS		 ***  //
							//--------------------------------//
				
				iterator				begin(void) {return (iterator(_tree.begin()));}

				const_iterator			begin(void) const {return (_tree.begin());}

				iterator				end(void) {return (_tree.end());}

				const_iterator			end(void) const {return (_tree.end());}

				reverse_iterator		rbegin(void) {return (_tree.rbegin());}

				const_reverse_iterator	rbegin(void) const {return (_tree.rbegin());}

				reverse_iterator		rend(void) {return (_tree.rend());}

				const_reverse_iterator	rend(void) const {return (_tree.rend());}

							//--------------------------------//
							//	 ***   ELEMENT_ACCES	 ***  //
							//--------------------------------//
				
				key_type		&at(const key_type &key) { return (_tree.at(key)); }

				const key_type	&at(const key_type &key) const { return (_tree.at(key)); }

				key_type		&operator[](const key_type &key) { return (_tree[key] = key); }

							//--------------------------------//
							//	 ***   		CAPACITY	 ***  //
							//--------------------------------//
				
				bool		empty(void) const {return (_tree.size() == 0);}

				size_type	size(void) const {return (_tree.size());}

				size_type	max_size(void) const {return (_tree.max_size());}

							//--------------------------------//
							//	 *** 	  MODIFIERS		 ***  //
							//--------------------------------//
				
				void					clear(void) {_tree.clear();}

				pair<iterator, bool>	insert(const value_type &value) {return (_tree.insert(value));}

				template <class InputIt> void 	insert(InputIt first, InputIt last) 
				{
					for(; first != last; ++first)
						insert(*first);
				}

				iterator	insert(iterator pos, const value_type &value) 
				{
					(void)pos;
					insert(value);
					iterator it = begin();
					for (; begin() != end(); ++it)
					{
						if (*it == value)
							break ;
					}
					return (it);
				}

				void	erase(iterator pos) {_tree.erase(*pos);}

				void	erase(iterator first, iterator last)
				{
					while (first != last)
						_tree.erase(first++);
				}

				size_type	erase(const key_type &key) {return (_tree.erase(key));}

				void	swap(set &other) { _tree.swap(other._tree); }

							//--------------------------------//
							//	 ***   		LOOKUP		 ***  //
							//--------------------------------//
				
				size_type	count(const key_type &key) const
				{
					const_iterator	res = _tree.find(key);

					return ((res == _tree.end()) ? 0 : 1);
				}

				iterator		find(const key_type &key) {return (_tree.find(key));}
				const_iterator	find(const key_type &key) const { return (_tree.find(key));}

				iterator		lower_bound(const Key &key) { return (_tree.lower_bound(key));}

				const_iterator	lower_bound(const Key &key) const { return (_tree.lower_bound(key));}

				iterator		upper_bound(const Key &key) { return (_tree.upper_bound(key));}

				const_iterator	upper_bound(const Key &key) const { return (_tree.upper_bound(key));}

				ft::pair<iterator, iterator> equal_range(const Key &key)
				{
					iterator	lower = lower_bound(key);
					iterator	upper = upper_bound(key);

					return (ft::make_pair(lower, upper));
				}

				ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
				{
					const_iterator	lower = lower_bound(key);
					const_iterator	upper = upper_bound(key);

					return (ft::make_pair(lower, upper));
				}

							//--------------------------------//
							//	 ***   	OBSERVERS		 ***  //
							//--------------------------------//
				
				key_compare		key_comp(void) const { return (_key_comp); }
				value_compare	value_comp(void) const { return (_value_comp); }

		};

							//------------------------------------//
							//	 *** NON MEMBER-FUNCTIONS	 ***  //
							//------------------------------------//

	template <class Key, class Compare, class Alloc>
		bool	operator==(const ft::set<Key, Compare, Alloc> &x, const ft::set<Key, Compare, Alloc> &y)
		{
			if (x.size() != y.size())
				return (false);
			return (ft::equal(x.begin(), x.end(), y.begin()));
		}

	template <class Key, class Compare, class Alloc>
		bool	operator!=(const ft::set<Key, Compare, Alloc> &x, const ft::set<Key, Compare, Alloc> &y)
		{ return (!(x == y)); }

	template <class Key, class Compare, class Alloc>
		bool	operator<(const ft::set<Key, Compare, Alloc> &x, const ft::set<Key, Compare, Alloc> &y)
		{ return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));}

	template <class Key, class Compare, class Alloc>
		bool	operator<=(const ft::set<Key, Compare, Alloc> &x, const ft::set<Key, Compare, Alloc> &y)
		{ return (x == y || x < y); }


	template <class Key, class Compare, class Alloc>
		bool	operator>(const ft::set<Key, Compare, Alloc> &x, const ft::set<Key, Compare, Alloc> &y)
		{ return (y < x); }

	template <class Key, class Compare, class Alloc>
		bool	operator>=(const ft::set<Key, Compare, Alloc> &x, const ft::set<Key, Compare, Alloc> &y)
		{ return ((y == x) || (y < x)); }


	template <class Key, class Compare, class Alloc>
		void	swap(ft::set<Key, Compare, Alloc> &x, ft::set<Key, Compare, Alloc> &y)
		{ x.swap(y); }
}

#endif
