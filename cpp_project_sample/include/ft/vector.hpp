/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:59:18 by thi-phng          #+#    #+#             */
/*   Updated: 2022/12/10 13:36:22 by thi-phng         ###   ########.fr       */
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
			vector(void) : _c_size(0), _capacity(2) {
				this->_c_data = this->alloc.allocate(this->_capacity + 1);//void deallocate( T* p, std::size_t n ); //pointer allocate( size_type n, const void * hint = 0 );
				std::memset(this->_c_data, 0, this->_capacity + 1);
			};
			~vector(void){};

			typedef std::size_t size_type;//typedef = using

			size_type size() const { return (_c_size); }

			void push_back( const Type& value ){
				size_t old_capacity = this->_capacity;
				for (size_t i = 0; i < this->_c_size; i++)
					std::cout << this->_c_data[i] << " : " << this->_c_size << std::endl;
				std::cout << std::endl;
				if (this->_c_size == this->_capacity){
					this->_capacity *= 2;
					Type *new_data = this->alloc.allocate(this->_capacity + 1);
					std::memset(this->_c_data, 0, this->_capacity + 1);
					size_t i = 0;
					for (; i < _c_size; i++){
						new_data[i] = _c_data[i];
					}
					new_data[i] = value;
					alloc.deallocate(_c_data, old_capacity + 1);
					_c_data = new_data;
					//this->_capacity = new_capacity;
				}
				else
				{
					_c_data[this->_c_size] = value;
				}
				this->_c_size++;
			}
//			 Modifiers
  			//void push_back(const T& value) {
  			//  if (m_size >= m_capacity) {
  			//    // Need to allocate more memory
  			//    size_t new_capacity = (m_capacity > 0) ? m_capacity * 2 : 1;
  			//    T* new_data = new T[new_capacity];
  			//    for (size_t i = 0; i < m_size; i++) {
  			//      new_data[i] = m_data[i];
  			//    }
  			//    delete[] m_data;
  			//    m_data = new_data;
  			//    m_capacity = new_capacity;
  			//  }
  			//  m_data[m_size] = value;
  			//  m_size++;
  			//}
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
			size_t	_capacity;
	};
} // end of namespace
#endif
