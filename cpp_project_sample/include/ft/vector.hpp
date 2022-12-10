/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:59:18 by thi-phng          #+#    #+#             */
/*   Updated: 2022/12/10 11:02:05 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstring>

// A template is a simple yet very powerful tool in C++. The simple idea is to pass
// data type as a parameter so that we don’t need to write the same code for different
// data types. For example, a software company may need to sort() for different data types. 
// Rather than writing and maintaining multiple codes, we can write one sort() and pass 
// data type as a parameter. 
// C++ adds two new keywords to support templates: ‘template’ and ‘typename’.
// The second keyword can always be replaced by the keyword ‘class’.

// Class template
namespace ft {

	template<typename Type>
	class vector {
		public:
			vector(void) : _c_size(0){
				this->_c_data = this->alloc.allocate(4);
				std::memset(this->_c_data, 0, 4);
			};

			~vector(void){};

			using size_type = std::size_t;
			size_type size() const{
				return (_c_size);
			}

			void push_back( const Type& value ){
				//size_t i = 0;
				(void)value;
				//Type *new_data = this->alloc.allocate(_c_size + 20);
				//if (this->_c_size == 0)
				//	_c_data[0] = value;
				//for (size_t i2 = 0; i2 <= _c_size; i2++){
					//new_data[i] = _c_data[i];}
			//	_c_data[i] = value;
				this->_c_size++;
			}

			void pop_back()
			{
				if (_c_size == 0)
					return ;
				this->_c_size--;
			}
			
			//*** Element access ***//
			//reference operator[]( size_type pos );
			Type& operator[](size_t i) {
				return this->_c_data[i];
			}

			//const_reference operator[]( size_type pos ) const;
  			const Type& operator[](size_t i) const {
				return _c_data[i];
			}

		private:
			size_t	_c_size;
			Type *	_c_data;
        	std::allocator< Type > alloc;
			//size_t	_max_place;//capacity

	};
} // end of namespace


#endif
