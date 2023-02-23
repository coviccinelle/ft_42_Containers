/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:36:08 by thi-phng          #+#    #+#             */
/*   Updated: 2023/02/17 11:39:09 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

namspace ft
{

	enum Color
	{
		RED,	// 1
		BLACK	// 0
	};

	template <typename T>
struct Node {
    T data;
    Color color;
    Node<T> *left, *right, *parent;

    Node(T value) : data(value), color(RED), left(NULL), right(NULL), parent(NULL) {}

    ~Node() {
        delete left;
        delete right;
    }
};

	class RedBlackTree
	{

		public:
			RedBlackTree(void);
			~RedBlackTree(void);
			RedBlackTree(RedBlackTree const &src);
			RedBlackTree	&operator=(RedBlackTree const &rhs);
		private:
	};

}
#endif
