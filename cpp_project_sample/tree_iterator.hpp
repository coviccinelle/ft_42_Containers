/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:59:03 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/24 12:47:49 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

//# include <iterator>
//# include <cstddef>

namespace ft
{
//			class const_tree_iterator ;
	template <class Node>
		class tree_iterator
		{
//			friend class const_tree_iterator ;
			public:
				typedef Node									value_type;
				typedef value_type								*node_ptr;
				typedef typename Node::value_type				data_type;
				typedef data_type &								reference;
				typedef data_type const &						const_reference;
				typedef data_type * 							pointer;
				typedef data_type								const *const_pointer;
				typedef typename std::ptrdiff_t					difference_type;
				typedef std::bidirectional_iterator_tag			iterator_category;
			
			public:
				node_ptr	node;

			private:
				node_ptr _root;
				node_ptr _NIL;

			public:
				tree_iterator(node_ptr node, node_ptr root, node_ptr NIL): node(node), _root(root), _NIL(NIL) {}

				tree_iterator(void) : node(NULL), _root(NULL), _NIL(NULL) {}

				tree_iterator(const tree_iterator &other) : node(other.node), _root(other._root), _NIL(other._NIL) {}

				~tree_iterator(void) {}

				operator tree_iterator<value_type const>(void) const { return tree_iterator<value_type const>(node, _root, _NIL);}

				tree_iterator	&operator=(const tree_iterator &other)
				{
					if (this == &other)
						return (*this);
					this->node = other.node;
					return (*this);
				}

				bool	operator==(const tree_iterator &other) const { return (node == other.node);}

				bool	operator!=(const tree_iterator &other) const { return (node != other.node);}

//				bool	operator<(const tree_iterator &other) const { return (node < other.node);}
//				bool	operator>(const tree_iterator &other) const { return (node > other.node);}
//				bool	operator>=(const tree_iterator &other) const { return (node >= other.node);}
//				bool	operator<=(const tree_iterator &other) const { return (node <= other.node);}

				reference	operator*(void) { return (node->data);}

				const_reference	operator*(void) const { return (node->data); }

				pointer operator->() { return &(operator*()); }

				const_pointer	operator->(void) const { return (&(operator*()));}

				tree_iterator	&operator++(void)
				{
					if (node != _NIL)
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
					if (node != _NIL)
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
//				friend tree_iterator operator+(size_type i) { return operator++;}
//					friend iterator operator+(size_t i, const const_iterator& it) { return it + i;}

//				tree_iterator operator-(size_type n) const { return (tree_iterator(_ptr - n)); }		
//				tree_iterator operator-(size_type n) { return (tree_iterator(_ptr - n)); }		

			private:
				node_ptr	_max(node_ptr node)
				{
					while (node->right != _NIL)
						node = node->right;
					return (node);
				}

				node_ptr	_min(node_ptr node)
				{
					while (node->left != _NIL)
						node = node->left;
					return (node);
				}

				node_ptr	_prev(void)
				{
					node_ptr	n = node;
					node_ptr	prev = _NIL;

					if (n->left != _NIL)
						return _max(n->left);
					prev = n->parent;
					while (prev != _NIL && n == prev->left)
					{
						n = prev;
						prev = prev->parent;
					}
					return (prev);
				}

				node_ptr	_next(void)
				{
					node_ptr	n = node;
					node_ptr	next = _NIL;

					if (n == NULL)
						return (NULL);
					if (n->right != _NIL)
						return _min(n->right);
					next = n->parent;
					while (next != _NIL && n == next->right)
					{
						n = next;
						next = next->parent;
					}
					return (next);
				}
		};

//	template <class Node>
//		class const_tree_iterator
//		{
////			friend class tree_iterator ;
//			public:
//				typedef Node									value_type;
//				typedef value_type								*node_ptr;
//				typedef typename Node::value_type				data_type;
//				typedef data_type &								reference;
//				typedef data_type const &						const_reference;
//				typedef data_type * 							pointer;
//				typedef data_type const *						const_pointer;
//				typedef typename std::ptrdiff_t					difference_type;
//				typedef std::bidirectional_iterator_tag			iterator_category;
//			
//			public:
//				node_ptr	node;
//
//			private:
//				node_ptr _root;
//				node_ptr _NIL;
//
//			public:
//				const_tree_iterator(node_ptr node, node_ptr root, node_ptr NIL): node(node), _root(root), _NIL(NIL) {}
//
//				const_tree_iterator(void) : node(NULL), _root(NULL), _NIL(NULL) {}
//
//				const_tree_iterator(const const_tree_iterator &other): node(other.node), _root(other._root), _NIL(other._NIL) {}
//
//				~const_tree_iterator(void){}
//
//				operator const_tree_iterator<value_type const>(void) const { return const_tree_iterator<value_type const>(node, _root, _NIL);}
//
//				const_tree_iterator	&operator=(const const_tree_iterator &other) const
//				{
//					if (this == &other)
//						return (*this);
//					this->node = other.node;
//					return (*this);
//				}
//
//				bool	operator==(const const_tree_iterator &other) const { return (node == other.node);}
//
//				bool	operator!=(const const_tree_iterator &other) const { return (node != other.node);}
//
////				bool	operator<(const tree_iterator &other) const { return (node < other.node);}
////				bool	operator>(const tree_iterator &other) const { return (node > other.node);}
////				bool	operator>=(const tree_iterator &other) const { return (node >= other.node);}
////				bool	operator<=(const tree_iterator &other) const { return (node <= other.node);}
//
////				const_reference	operator*(void) { return (node->data);}
//
//				const_reference	operator*(void) const { return (node->data); }
//
////				pointer operator->() { return &(operator*()); }
//
//				const_pointer	operator->(void) const { return (&(operator*()));}
//
//				const_tree_iterator	&operator++(void) const
//				{
//					if (node != _NIL)
//						node = _next();
//					return (*this);
//				}
//
//				const_tree_iterator	operator++(int) const
//				{
//					const_tree_iterator tmp(*this);
//					++(*this);
//					return (tmp);
//				}
//
//				const_tree_iterator	&operator--(void) const
//				{
//					if (node != _NIL)
//						node = _prev();
//					else
//						node = _max(_root);
//					return (*this);
//				}
//
//				const_tree_iterator	operator--(int) const
//				{
//					const_tree_iterator tmp(*this);
//					--(*this);
//					return (tmp);
//				}
////				friend tree_iterator operator+(size_type i) { return operator++;}
////					friend iterator operator+(size_t i, const const_iterator& it) { return it + i;}
//
////				tree_iterator operator-(size_type n) const { return (tree_iterator(_ptr - n)); }		
////				tree_iterator operator-(size_type n) { return (tree_iterator(_ptr - n)); }		
//
//			private:
//				node_ptr	_max(node_ptr node)
//				{
//					while (node->right != _NIL)
//						node = node->right;
//					return (node);
//				}
//
//				node_ptr	_min(node_ptr node)
//				{
//					while (node->left != _NIL)
//						node = node->left;
//					return (node);
//				}
//
//				node_ptr	_prev(void)
//				{
//					node_ptr	n = node;
//					node_ptr	prev = _NIL;
//
//					if (n->left != _NIL)
//						return _max(n->left);
//					prev = n->parent;
//					while (prev != _NIL && n == prev->left)
//					{
//						n = prev;
//						prev = prev->parent;
//					}
//					return (prev);
//				}
//
//				node_ptr	_next(void)
//				{
//					node_ptr	n = node;
//					node_ptr	next = _NIL;
//
//					if (n == NULL)
//						return (NULL);
//					if (n->right != _NIL)
//						return _min(n->right);
//					next = n->parent;
//					while (next != _NIL && n == next->right)
//					{
//						n = next;
//						next = next->parent;
//					}
//					return (next);
//				}
//		};
}

#endif