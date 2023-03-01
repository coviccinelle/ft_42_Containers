/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:59:03 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/28 21:58:29 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

//# include <iterator>
# include "rbtree.hpp"

namespace ft
{
	template <class T>
		struct RB_node;
	template <class NodeType, class IteType>
		class tree_iterator
		{
			public:
				typedef IteType									value_type;
				typedef ft::RB_node<NodeType>*					node_ptr;
//				typedef typename Node::value_type				data_type;
				typedef value_type &							reference;
				typedef value_type const &						const_reference;
				typedef value_type * 							pointer;
				typedef value_type const *						const_pointer;
				typedef typename std::ptrdiff_t					difference_type;
				typedef std::bidirectional_iterator_tag			iterator_category;
			
				node_ptr	node;
			private:
				node_ptr _root;

			public:
				tree_iterator(node_ptr node, node_ptr root): node(node), _root(root) {}

				tree_iterator(void) : node(NULL), _root(NULL) {}

				tree_iterator(const tree_iterator &other) : node(other.node), _root(other._root) {}

				~tree_iterator(void) {}

				operator tree_iterator<NodeType, const IteType>(void) const { return tree_iterator<NodeType, const IteType>(node, _root);}

				tree_iterator	&operator=(const tree_iterator &other)
				{
					if (this == &other)
						return (*this);
					this->node = other.node;
					return (*this);
				}


				reference	operator*(void) { return (node->data);}
				const_reference	operator*(void) const { return (node->data); }

				pointer operator->() { return &(operator*()); }
				const_pointer	operator->(void) const { return (&(operator*()));}

				tree_iterator	&operator++(void)
				{
					if (node->is_nil == 0)
						node = _next();
					return (*this);
				}

				tree_iterator	operator++(int)
				{
					tree_iterator tmp(*this);
					++(*this);
					return (tmp);
				}

				tree_iterator	&operator--(void)
				{
					if (node->is_nil == 0)
						node = _prev();
					else
						node = _max(_root);
					return (*this);
				}

				tree_iterator	operator--(int)
				{
					tree_iterator tmp(*this);
					--(*this);
					return (tmp);
				}

			private:
				node_ptr	_max(node_ptr node)
				{
					if (node->is_nil == 0)
						return (node);
					while (node->right->is_nil == 0)
						node = node->right;
					return (node);
				}

				node_ptr	_min(node_ptr node)
				{
					if (node->is_nil)
						return (node);
					while (node->left->is_nil == 0)// && node != node->left)
					{
//						std::cout << "2.0 BOUCLE, node = " << node << "and node -> left = " << node->left << std::endl;
						node = node->left;
					}
					return (node);
				}

				node_ptr	_prev(void)
				{
					node_ptr	n = node;
					node_ptr	prev;

					if (n->left->is_nil == 0)
						return _max(n->left);
					prev = n->parent;
					while (prev->is_nil == 0 && n == prev->left)
					{
						n = prev;
						prev = prev->parent;
					}
					return (prev);
				}

				node_ptr	_next(void)
				{
					node_ptr	n = node;
					node_ptr	next;

					if (n->is_nil)
						return (n);
					if (n->right->is_nil == 0)
						return _min(n->right);
					next = n->parent;
					while (next->is_nil == 0 && n == next->right)
					{
						n = next;
						next = next->parent;
					}
					return (next);
				}
		};

template <typename N1, typename I1, typename N2, typename I2>
	bool	operator==(const tree_iterator<N1, I1>& x, const tree_iterator<N2, I2> &y){ return (x.operator->() == y.operator->());}
template <typename N1, typename I1, typename N2, typename I2>
	bool	operator!=(const tree_iterator<N1, I1>& x, const tree_iterator<N2, I2> &y){ return (!(x == y));}
template <typename N1, typename I1, typename N2, typename I2>
	bool	operator<(const tree_iterator<N1, I1>& x, const tree_iterator<N2, I2> &y){ return (x.operator->() < y.operator->()) ;}
template <typename N1, typename I1, typename N2, typename I2>
	bool	operator>(const tree_iterator<N1, I1>& x, const tree_iterator<N2, I2> &y){ return (x.operator->() > y.operator->());}
template <typename N1, typename I1, typename N2, typename I2>
	bool	operator>=(const tree_iterator<N1, I1>& x, const tree_iterator<N2, I2> &y){ return (x.operator->() >= y.operator->());}
template <typename N1, typename I1, typename N2, typename I2>
	bool	operator<=(const tree_iterator<N1, I1>& x, const tree_iterator<N2, I2> &y){ return (x.operator->() <= y.operator->());}
}

#endif
