/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 14:05:16 by thi-phng          #+#    #+#             */
/*   Updated: 2023/03/03 22:52:58 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "pair.hpp"
# include "reverse_iterator.hpp"
# include "tree_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "iterator_traits.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "equal.hpp"

# define RED	true
# define BLACK	false

// https://www.programiz.com/dsa/red-black-tree

namespace ft
{
	template <class T>
		struct RB_node
		{
			typedef T	value_type;
			RB_node		*parent;
			RB_node		*left;
			RB_node		*right;
			bool		color;
			bool		is_nil;
			T			data;
			RB_node(T const &data) : data(data) {}
		};

	template <class T, class Compare, class Allocator = std::allocator<RB_node<T> > >
		class RB_tree
		{
			public:
				typedef T										value_type;
				typedef size_t									size_type;
				typedef Compare									compare;
				typedef Allocator								allocator;
				typedef RB_node<value_type>						node;
				typedef node *									node_ptr;
				typedef std::ptrdiff_t							difference_type;
				typedef ft::tree_iterator<T, T>					iterator;
				typedef ft::tree_iterator<T, const T>			const_iterator;
				typedef ft::reverse_iterator<iterator>			reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			private:
				node_ptr	root;
				node_ptr	NIL;
				compare		_compare;
				allocator	_alloc;
				size_type	_size;

			public:

				//--------------------------------//
				//	 ***  MEMBER-FUNCTIONS	 ***  //
				//--------------------------------//

				RB_tree(const allocator &alloc = allocator(), const compare &comp = compare()): _compare(comp), _size(0)
				{
					_alloc = alloc;

					NIL = _alloc.allocate(1);
					_alloc.construct(NIL, value_type());
					NIL->parent = NIL;
					NIL->left = NIL;
					NIL->right = NIL;
					NIL->color = BLACK;
					NIL->is_nil = 1;
					root = NIL;
				}

				RB_tree(RB_tree const &other)
				{
					_alloc = other._alloc;
					_compare = other._compare;
					_size = other._size;
					NIL = _alloc.allocate(1);
					NIL->parent = NIL;
					NIL->left = NIL;
					NIL->right = NIL;
					NIL->color = BLACK;
					NIL->is_nil = 1;
					root = _recursive_copy(other.root);
				}

				~RB_tree()
				{
					clear();
					_alloc.destroy(NIL);
					_alloc.deallocate(NIL, 1);
				}

				RB_tree	&operator=(const RB_tree &other)
				{
					if (this == &other)
						return (*this);
					clear();
					_alloc = other._alloc;
					_compare = other._compare;
					_size = other._size;
					root = _recursive_copy(other.root);
					return *this;
				}

				node_ptr	GetNil(void) const { return (this->NIL); }
				node_ptr	GetRoot(void) const { return (this->root); }

				//--------------------------------//
				//	 *** 	 ITERATORS		 ***  //
				//--------------------------------//
				
				iterator		begin() { node_ptr min = _minimum(root); return (iterator(min, min->parent));}
				const_iterator	begin() const { node_ptr min = _minimum(root); return (const_iterator(min, min->parent));}
				iterator		end() { return (iterator(NIL, _maximum(root)));}
				const_iterator	end() const { return (const_iterator(NIL, _maximum(root)));}

				reverse_iterator	rbegin()
				{
					iterator	it = end();
					return (reverse_iterator(it));
				}

				const_reverse_iterator	rbegin() const
				{
					const_iterator	it = end();
					return (const_reverse_iterator(it));
				}

				reverse_iterator	rend()
				{
					iterator	it = begin();
					return (reverse_iterator(it));
				}

				const_reverse_iterator	rend() const
				{
					const_iterator	it = begin();
					return (const_reverse_iterator(it));
				}

				//--------------------------------//
				//	 ***   	CAPACITY		 ***  //
				//--------------------------------//
				
				size_type	size() const {return (_size);}
				size_type	max_size() const {return (_alloc.max_size());}

				void	swap(RB_tree &other)
				{
					std::swap(_alloc, other._alloc);
					std::swap(_compare, other._compare);
					std::swap(_size, other._size);
					std::swap(NIL, other.NIL);
					std::swap(root, other.root);
				}


				//--------------------------------//
				//	 ***   	MODIFIERS		 ***  //
				//--------------------------------//
				
				ft::pair<iterator, bool>	insert(value_type const &value)
				{
					node_ptr	n = _new_node(value);
					ft::pair<node_ptr, bool> r = _insert_recursive(root, n);
					if (r.second == 0)
					{
						_alloc.destroy(n);
						_alloc.deallocate(n, 1);
						return (ft::make_pair(iterator(r.first, (r.first)->parent), false));
					}
					_size++;
					if (n->parent == NIL)
					{
						n->color = BLACK;
						n->is_nil = 0;
					}
					else
						_insert_fixup(n);
					root = n;
					while (root->parent != NIL)
						root = root->parent;
					return (ft::make_pair(iterator(n, n->parent), true));
				}

				iterator	insert(iterator hint, const value_type &value)
				{
					node_ptr	next = _next(hint.node);

					if (_compare(*hint, value) && _compare(value, next->data))
					{
						node_ptr	n = _new_node(value);
						ft::pair<node_ptr, bool>	r = _insert_recursive(hint.node, n);

						_size++;
						return (iterator(r.first, (r.first)->parent));
					}
					else
						return (insert(value).first);
				}

				size_type	erase(value_type const &value)
				{
					node_ptr	n = _find_node(value);

					if (n)
					{
						_delete_node(n);
						return (1);
					}
					else
						return (0);
				}

				void	erase(iterator pos)
				{
					if (pos.node != NIL)
						_delete_node(pos.node);
				}

				void	erase(const_iterator pos)
				{
					if (pos.node != NIL)
						_delete_node(pos.node);
				}
				
				void	clear()
				{
					_recursive_clear(root);
					root = NIL;
					_size = 0;
				}

				//--------------------------------//
				//	 ***   		LOOKUP		 ***  //
				//--------------------------------//
				
				iterator	find(value_type const &value)
				{
					node_ptr	found = _find_node(value);

					if (!found)
						return (end());
					else
						return (iterator(found, found->parent));
				}

				const_iterator	find(value_type const &value) const
				{
					node_ptr	found = _find_node(value);

					if (!found)
						return (end());
					else
						return (iterator(found, found->parent));
				}
				
				iterator	lower_bound(const value_type &value)
				{
					for (iterator it = begin(); it != end(); ++it)
					{
						if (_compare(value, it.node->data)
								|| _compare(it.node->data, value) == 0)
							return (it);
					}
					return (end());
				}

				const_iterator	lower_bound(const value_type &value) const
				{
					for (const_iterator it = begin(); it != end(); ++it)
					{
						if (_compare(value, it.node->data)
								|| _compare(it.node->data, value) == 0)
							return (it);
					}
					return (end());
				}

				iterator	upper_bound(const value_type &value)
				{
					for (iterator it = begin(); it != end(); ++it)
					{
						if (_compare(value, it.node->data))
							return (it);
					}
					return (end());
				}

				const_iterator	upper_bound(const value_type &value) const
				{
					for (const_iterator it = begin(); it != end(); ++it)
					{
						if (_compare(value, it.node->data))
							return (it);
					}
					return (end());
				}


				//--------------------------------//
				//	 *** 	 HELPERS		 ***  //
				//--------------------------------//
				
				void recursePrintHelper(node *root, int space) const
				{
					if (root == NIL)
						return ;

					space += 5;

					recursePrintHelper(root->right, space); 
					for (int i = 0; i < space; ++i)
						std::cout << "-";
					std::cout << "[first, second, color, is_nil] (" << root->data.first << ", " << root->data.second << ", " << root->color << ", [" << root->is_nil << "])" << "\n";
					recursePrintHelper(root->left, space); 
				}

				void	printHelper(node *root) const
				{
					std::cout << "nil node info : " << NIL->is_nil <<  std::endl;
					recursePrintHelper(root, 0);
				}

			private:

				node	*_new_node(value_type const &data)
				{
					node	*node = _alloc.allocate(1);

					_alloc.construct(node, data);
					node->is_nil = 0;
					node->color = RED;
					node->left = NIL;
					node->right = NIL;
					node->parent = NIL;
					return (node);
				}

				node_ptr	_grand_parent(node_ptr const node) const
				{
					node_ptr	grand_parent = node->parent->parent;
					return (grand_parent);
				}

				node_ptr	_sibling(node_ptr const node) const
				{
					node_ptr	parent = node->parent;

					if (node == parent->left)
						return (parent->right);
					else
						return (parent->left);
				}

				node_ptr	_uncle(node_ptr const node) const
				{
					node_ptr	grand_parent = _grand_parent(node);
					return (_sibling(grand_parent));
				}

				void	_rotate_left(node_ptr x)
				{
					node_ptr	y = x->right;

					x->right = y->left;
					if (y->left != NIL)
						y->left->parent = x;
					y->parent = x->parent;
					if (x->parent == NIL)
						root = y;
					else if (x == x->parent->left)
						x->parent->left = y;
					else
						x->parent->right = y;
					y->left = x;
					x->parent = y;
				}

				void	_rotate_right(node_ptr x)
				{
					node_ptr	y = x->left;

					x->left = y->right;
					if (y->right != NIL)
						y->right->parent = x;
					y->parent = x->parent;
					if (x->parent == NIL)
						root = y;
					else if (x == x->parent->right)
						x->parent->right = y;
					else
						x->parent->left = y;
					y->right = x;
					x->parent = y;
				}

				ft::pair<node_ptr, bool>	_insert_recursive(node_ptr root, node_ptr n)
				{
					if (root != NIL && _compare(n->data, root->data))
					{
						if (root->left != NIL)
							return (_insert_recursive(root->left, n));
						else
							root->left = n;
					}
					else if (root != NIL && _compare(root->data, n->data))
					{
						if (root->right != NIL)
							return (_insert_recursive(root->right, n));
						else
							root->right = n;
					}
					else if (root != NIL)
						return (ft::make_pair(root, false));
					n->parent = root;
					n->is_nil = 0;
					n->color = RED;
					n->left = n->right = NIL;
					return (ft::make_pair(n, true));
				}

				void	_insert_fixup(node_ptr k)
				{
					node_ptr	u;

					while (k->parent->color == RED)
					{
						if (k->parent == k->parent->parent->right)
						{
							u = k->parent->parent->left;
							if (u->color == RED)
							{
								u->color = BLACK;
								k->parent->color = BLACK;
								k->parent->parent->color = RED;
								k = k->parent->parent;
							}
							else
							{
								if (k == k->parent->left)
								{
									k = k->parent;
									_rotate_right(k);
								}
								k->parent->color = BLACK;
								k->parent->parent->color = RED;
								_rotate_left(k->parent->parent);
							}
						}
						else
						{
							u = k->parent->parent->right;

							if (u->color == RED)
							{
								u->color = BLACK;
								k->parent->color = BLACK;
								k->parent->parent->color = RED;
								k = k->parent->parent;
							}
							else
							{
								if (k == k->parent->right)
								{
									k = k->parent;
									_rotate_left(k);
								}
								k->parent->color = BLACK;
								k->parent->parent->color = RED;
								_rotate_right(k->parent->parent);
							}
						}
						if (k == root)
							break ;
					}
					root->color = BLACK;
					root->is_nil = 0;
				}

				node_ptr	_find_node(value_type const &data) const
				{
					node_ptr	current = root;

					while (current != NIL)
					{
						if (_compare(data, current->data))
							current = current->left;
						else if (_compare(current->data, data))
							current = current->right;
						else
							return (current);
					}
					return (NULL);
				}

				void	_transplant(node_ptr u, node_ptr v)
				{
					if (u->parent == NIL)
						root = v;
					else if (u == u->parent->left)
						u->parent->left = v;
					else
						u->parent->right = v;
					v->parent = u->parent;
				}

				node_ptr	_minimum(node_ptr x) const
				{
					while (x->left != NIL)
						x = x->left;
					return (x);
				}
				node_ptr	_maximum(node_ptr x) const
				{
					while (x->right != NIL)
						x = x->right;
					return (x);
				}

				void	_delete_node(node_ptr z)
				{
					node_ptr	y = z;
					node_ptr	x;
					bool		y_original_color = y->color;

					if (z->left == NIL)
					{
						x = z->right;
						_transplant(z, z->right);
					}
					else if (z->right == NIL)
					{
						x = z->left;
						_transplant(z, z->left);
					}
					else
					{
						y = _minimum(z->right);
						y_original_color = y->color;
						x = y->right;
						if (y->parent == z)
							x->parent = y;
						else
						{
							_transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						_transplant(z, y);
						y->left = z->left;
						y->left->parent = y;
						y->color = z->color;
					}
					_alloc.destroy(z);
					_alloc.deallocate(z, 1);
					_size--;
					if (y_original_color == BLACK)
						_delete_fixup(x);
				}

				void	_delete_fixup(node_ptr x)
				{
					node_ptr	s;

					while (x != root && x->color == BLACK)
					{
						if (x == x->parent->left)
						{
							s = x->parent->right;
							if (s->color == RED)
							{
								s->color = BLACK;
								x->parent->color = RED;
								_rotate_left(x->parent);
								s = x->parent->right;
							}
							if (s->left->color == BLACK && s->right->color == BLACK)
							{
								s->color = RED;
								x = x->parent;
							}
							else
							{
								if (s->right->color == BLACK)
								{
									s->left->color = BLACK;
									s->color = RED;
									_rotate_right(s);
									s = x->parent->right;
								}
								s->color = x->parent->color;
								x->parent->color = BLACK;
								s->right->color = BLACK;
								_rotate_left(x->parent);
								x = root;
							}
						}
						else
						{
							s = x->parent->left;
							if (s->color == RED)
							{
								s->color = BLACK;
								x->parent->color = RED;
								_rotate_right(x->parent);
								s = x->parent->left;
							}
							if (s->right->color == BLACK && s->left->color == BLACK)
							{
								s->color = RED;
								x = x->parent;
							}
							else
							{
								if (s->left->color == BLACK)
								{
									s->right->color = BLACK;
									s->color = RED;
									_rotate_left(s);
									s = x->parent->left;
								}
								s->color = x->parent->color;
								x->parent->color = BLACK;
								s->left->color = BLACK;
								_rotate_right(x->parent);
								x = root;
							}
						}
					}
					x->color = BLACK;
				}

				void	_recursive_clear(node_ptr x)
				{
					if (x != NIL)
					{
						_recursive_clear(x->left);
						_recursive_clear(x->right);
						_alloc.destroy(x);
						_alloc.deallocate(x, 1);
					}
				}

				node	*_recursive_copy(node_ptr x)
				{
					if (x->is_nil)
						return (NIL);
					node *nnode = _new_node(x->data);
					nnode->color = x->color;

					nnode->left = _recursive_copy(x->left);
					nnode->left->parent = nnode;

					nnode->right = _recursive_copy(x->right);
					nnode->right->parent = nnode;

					return (nnode);
				}

				node_ptr	_prev(node_ptr node) const
				{
					node_ptr	prev = NIL;

					if (node->left != NIL)
						return (_minimum(node->left));
					prev = node->parent;
					while (prev != NIL && node == prev->left)
					{
						node = prev;
						prev = prev->parent;
					}
					return (prev);
				}

				node_ptr	_next(node_ptr node) const
				{
					if (node->right != NIL)
						return (_minimum(node->right));

					node_ptr next = node->parent;
					while (next != NIL && node == next->right)
					{
						node = next;
						next = next->parent;
					}
					return (next);
				}
		};

}

#endif
