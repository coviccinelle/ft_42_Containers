/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:59:18 by thi-phng          #+#    #+#             */
/*   Updated: 2022/12/15 18:20:49 by thi-phng         ###   ########.fr       */
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

	template< class Type, class Allocator = std::allocator< Type > >
	class vector {
		public:

			typedef Type value_type;
			typedef value_type * pointer;
			typedef std::size_t size_type;//typedef = using
 			typedef Allocator allocator_type;	
			typedef value_type& reference;

		// *** TEST ONLY *** //

			allocator_type & getAlloc(void){
				return (this->alloc);
			}

			pointer getElements(void) const {
				return (this->_c_data);
			}

			size_type getCapacity(void) const {
				return (this->_capacity);
			}

						//--------------------------------//
						// ***	  MEMBER FUNCTIONS 	***   //
						//--------------------------------//

			vector(void) : _c_size(0), _capacity(2) {
				this->_c_data = this->alloc.allocate(this->_capacity);//void deallocate( T* p, std::size_t n ); //pointer allocate( size_type n, const void * hint = 0 );
				//std::memset(this->_c_data, 0, this->_capacity + 1);
				//std::cout << "Constructor called" << std::endl;
			};

			~vector(void){
				//reallocate
				//std::cout << "Destructor called" << std::endl;
				for (size_t i = 0; i < this->_c_size; i++)
					this->alloc.destroy((this->_c_data + i));//address of this->_c_data[i] == (*this).(_c_data + i) // 
				this->alloc.deallocate(this->_c_data, this->_capacity);
			};

			//vector& operator=( const vector& other );
			vector< Type, Allocator >& operator=(const vector<Type, Allocator>& other)
    		{
				(void)other;
					/*
    		    if (this != &other)
    		    {
    		        //delete[] this->_c_data;
					alloc.deallocate(_c_data, this->_capacity);
    		        this->_c_size = other._c_size;
					if (this->_c_size >= this->_capacity)
						this->_capacity *= 2;
    		        this->_capacity = other._capacity;
					this->_c_data = this->alloc.allocate(this->_capacity);
					std::memset(this->_c_data, 0, this->_capacity);
    		        //this->_c_data = new Type[this->_capacity];
    		        for (size_t i = 0; i < this->_c_size; i++)
    		            this->_c_data[i] = other._c_data[i];
    		    }
				*/
				std::cout << "helllllo i'm over here operator = " << std::endl;
    		    return *this;
    		}


						//--------------------------------//
						//	 *** 	ELEMENT ACCESS 	 ***  //
						//--------------------------------//
						// at, operator[], front, back, data

			//reference operator[]( size_type pos );
			Type& operator[](size_t i) {
				//std::cout << "operator []" << std::endl;
				if (i > this->_c_size)
				{
					std::cout << "Error: Can't access further, sorry" << std::endl;
					return (this->_c_data[0]);
				 }
				return this->_c_data[i];
			}

			//const_reference operator[]( size_type pos ) const;
  			const Type& operator[](size_t i) const {
				return _c_data[i];
			}

			// front : acess the first element
			reference front(void){
				return (this->_c_data[0]);
			}

						//--------------------------------//
						//	 *** 	 CAPACITY		 ***  //
						//--------------------------------//

			size_type size() const { return (_c_size); }


						//--------------------------------//
						//	 *** 	 MODIFIERS		 ***  //
						//--------------------------------//

			void push_back( const Type& value ) {
				if (this->_c_size == this->_capacity)
				{

					this->_capacity *= 2;
					value_type	*new_data = this->alloc.allocate((this->_capacity));
					//std::memset(new_data, 0, (this->_capacity * 2) + 1);
					for (size_t i = 0; i < this->_c_size; i++)
					{
						this->alloc.construct((new_data + i), *((*this)._c_data + i));
						this->alloc.destroy((*this)._c_data + i);
					}
					this->alloc.deallocate((*this)._c_data, this->_capacity);
					this->_c_data = new_data;
				}
				this->alloc.construct(((*this)._c_data + (*this)._c_size), value);
				this->_c_size++;
			}

			void pop_back()
			{
				if (this->_c_size <= 0)
					return ;
				else {
					//std::cout << "what are we destroying? => " << this->_c_data[this->_c_size - 1] << std::endl;
					this->alloc.destroy((*this)._c_data + this->_c_size);
					this->_c_size--;
					//std::cout << "last_element now? => " << this->_c_data[this->_c_size - 1] << std::endl;
				}
			}
			


		private:
			size_t			_c_size;
			value_type *	_c_data;
        	allocator_type	alloc;
			size_t			_capacity;
	};
} // end of namespace
#endif
