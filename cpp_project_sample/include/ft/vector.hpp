/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:59:18 by thi-phng          #+#    #+#             */
/*   Updated: 2023/01/03 20:51:04 by thi-phng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstring>
#include <sstream>

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

			typedef Type 			value_type;
			typedef value_type * 	pointer;
			typedef std::size_t 	size_type;//typedef = using
 			typedef Allocator 		allocator_type;	
 			typedef Allocator & 	allocator_reference;	
			typedef value_type & 	reference;
			typedef const Type & 	const_reference;

		// *** TEST ONLY *** //

			allocator_type & getAlloc(void){
				return (this->_alloc);
			}
/*
			allocator_type & getAlloc(void){
				//return (this->_alloc);
				return (const_cast<allocator_reference>(
					static_cast < const typename ft::vector< Type, Allocator > &>(*this).front()));
			}*/

			pointer getElements(void) const {
				return (this->_c_data);
			}

						//--------------------------------//
						// ***	  MEMBER FUNCTIONS 	***   //
						//--------------------------------//

		//	vector(void) : _c_size(0), _c_data(0), _capacity(0) {
				//this->_c_data = this->_alloc.allocate(this->_capacity);
				//void deallocate( T* p, std::size_t n );
				//pointer allocate( size_type n, const void * hint = 0 );
		//	};

// A coder ^^
			explicit vector( const Allocator& alloc = Allocator() ) : _c_size(0), _c_data(0), _alloc(alloc), _capacity(0) {
			}

			explicit vector( size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator()) : _c_size(count), _alloc(alloc), _capacity(count){
				if (count > this->max_size()) // equal .max_size()
				{
					throw std::length_error("cannot create std::vector larger than max_size()");
					std::abort();
				}
				this->_c_data =  this->_alloc.allocate(count);
				for (size_t i = 0; i < count; i++)
					this->_alloc.construct(this->_c_data + i, value);	
			}

			//template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
		/*	vector( value_type Type, std::allocator< Type > allocator){
				std::cout << "Now what? :) " << std::endl;
				(void) Type;
				(void) allocator;
			}
		*/
			// A TESTSER
			vector( const vector& other ) : _c_size(other.size()),/* _c_data(this->_alloc.allocate(other.capacity())),*/ _alloc(other.get_allocator()), _capacity(other.capacity()) {//constructeur de recopie
				//this->_alloc = other.get_allocator();
				//try {
					this->_c_data = this->_alloc.allocate(other.capacity());
				//}
				//catch
				for (size_t i = 0; i < this->_c_size; i++)
					this->_alloc.construct(this->_c_data + i, other[i]);	
			}
/*
*/

			~vector(void){
				if (this->_capacity > 0)
				//std::cout << "Destructor called" << std::endl;
				for (size_t i = 0; i < this->_c_size; i++)
					this->_alloc.destroy((this->_c_data + i));
				//address of this->_c_data[i] == (*this).(_c_data + i) // 
				this->_alloc.deallocate(this->_c_data, this->_capacity);
			};

			//vector& operator=( const vector& other );
			vector< Type, Allocator >& operator=(const vector<Type, Allocator>& other)
    		{
    		    if (this != &other)
    		    {
					for (size_t i = 0; i < this->_c_size; i++)
						this->_alloc.destroy((this->_c_data + i));
    		        //delete[] this->_c_data;
    		        this->_c_size = other._c_size;
					if (this->_capacity != other.capacity()){
						this->_alloc.deallocate(_c_data, this->_capacity);
    		        	this->_capacity = other.capacity();
						this->_c_data = this->_alloc.allocate(this->_capacity);
					}
					for (size_t k = 0; k < this->_c_size; k++)
						this->_alloc.construct(this->_c_data + k, other._c_data[k]);
    		    }
    		    return *this;
    		}

			allocator_type get_allocator() const{
				return (this->_alloc);
			}

	//		void assign( size_type count, const T& value ){
			void assign( size_type count, const_reference value ){
				//std::cout << "count = " << count << " value = " << value << " size = " << this->_c_size << " capacity = "<< this->_capacity << std::endl;
				if (count > this->max_size()) // equal .max_size()
				{
					throw std::invalid_argument("cannot create std::vector larger than max_size()");
					std::abort();
				}

				if (this->_c_size > 0)
				{
					for (size_type i = 0; i < this->_c_size; i++)
						this->_alloc.destroy((this->_c_data + i));
				}

				else if (this->_capacity == 0){
					this->_c_data = this->_alloc.allocate(1);
					this->_capacity = 1;
					this->_c_size = 1;
				}
				//std::cout << "Updated -> count = " << count << " value = " << value << " size = " << this->_c_size << " capacity = "<< this->_capacity << std::endl;
				if (count > this->_capacity)
				{
					this->_alloc.deallocate(_c_data, this->_capacity);
					while (this->_capacity < count)
						this->_capacity *= 2;
					this->_c_data = this->_alloc.allocate(this->_capacity);
				}
				else if (this->_capacity == count && (this->_c_size != 1))
				{
					std::cout << "I'm the problem is me" << std::endl;
					this->_alloc.deallocate(this->_c_data, this->_capacity);
				}
				//else
				{
					for (size_type k = 0; k < count; k++)
						this->_alloc.construct(this->_c_data + k, value);
					this->_c_size = count;
				}
			}
			
			// assign_2 with iterator
			//template< class InputIt > void assign( InputIt first, InputIt last );

						//--------------------------------//
						//	 *** 	ELEMENT ACCESS 	 ***  //
						//--------------------------------//
						// at, operator[], front, back, data


			const_reference at( size_type pos ) const
			{
				if ((pos >= this->size()))
				{
					std::ostringstream out;
					out << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
					throw std::out_of_range(out.str());
				}
				return (this->_c_data[pos]);
			}

			reference at( size_type pos ){
				return (const_cast<reference>(
					static_cast < const typename ft::vector< Type, Allocator >& >(*this).at(pos)
							));
			}

			//reference operator[]( size_type pos );
			Type& operator[](size_t i) {
				//std::cout << "operator []" << std::endl;
			/*	if (i > this->_c_size)
				{
					throw std::invalid_argument( "Error: Can't acess further, sorry\n" );
				 }*/
				return (const_cast<reference>(
					static_cast < const typename ft::vector< Type, Allocator > &>(*this)[i]
							));
			}

			//const_reference operator[]( size_type pos ) const;
  			const Type& operator[](size_t i) const {
				return (this->_c_data[i]);
			}

			// front : acess the first element
			const_reference front() const
			{
				return (this->_c_data[0]); // ==return ((*this)[0]);
			}

			reference front()
			{
				return (const_cast<reference>(
					static_cast < const typename ft::vector< Type, Allocator > &>(*this).front()));
			}

			const_reference back() const{
				return (this->_c_data[this->_c_size - 1]);
			}

			reference back(){
					return (const_cast<reference>(
						static_cast < const typename ft::vector< Type, Allocator > &>(*this).back()));
			}

			
			pointer data()
			{
				if (this->_c_size == 0 || !(this->_c_data))
					return (NULL);
				return (this->_c_data);
				/*
				return (const_cast<pointer>(
					static_cast < const pointer > (*this).data()
							));
				*/
			}

			const pointer data() const{
				if (this->_c_size == 0 || !(this->_c_data))
					return (NULL);
				return (this->_c_data);
			}

						//--------------------------------//
						//	 *** 	 ITERATORS  	***   //
						//--------------------------------//
						// begin, end, rbegin, rend	

			//template <class T>
			class iterator {
				public:
					typedef std::random_access_iterator_tag	iterator_category;
					typedef Type							value_type;
					typedef value_type						&reference;
					typedef value_type						*pointer;
					typedef std::ptrdiff_t					difference_type;

			 // Constructor
			 iterator(void) : _ptr(NULL){}
			 iterator(pointer p) : _ptr(p){}
			 iterator(const iterator&){}
		     ~iterator(){}
    		/* iterator& operator=(const iterator&);
    		 iterator& operator++(); //prefix increment
    		 reference operator*() const;
			 iterator(void) : _ptr(NULL){}
			 iterator(value_type){}
			*/
			 // Overload the * operator to return a reference to the element at the current iterator position
			 reference operator*() {
			   return (* _ptr);;
			 }

			private:
			 	pointer  	_ptr;
			};

/*
			template<typename value_type, typename Alloc>
			typename vector<Type, Alloc>::iterator vector<Type, Alloc>::begin(void) {
				std::cout << "Hello\n" << std::endl;
				return (iterator(this->_c_data));
			}
*/
		/*	
		 // Iterator to the first element.
		 	iterator begin();

			const_iterator begin() const;

			//Iterator to the element following the last element.
			iterator end();
			const_iterator end() const;

			//Reverse iterator to the first element.
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;


			//Reverse iterator to the element following the last element.
			reverse_iterator rend();
			const_reverse_iterator rend() const;


			*/

			 iterator begin(){
				 return (iterator(this->_c_data));
			 }

						//--------------------------------//
						//	 *** 	 CAPACITY		 ***  //
						//--------------------------------//

			size_type size() const {
				return (this->_c_size); }

			size_type capacity(void) const {
				return (this->_capacity);
			}

			void reserve( size_type new_cap ){
				if (new_cap > this->max_size())
					throw std::length_error("vector::reserve");
				else if (new_cap > this->_capacity/* && (*this)._c_data*/)
				{
					value_type	*new_data = this->_alloc.allocate((new_cap));
					///*
					for (size_t i = 0; i < this->_c_size; i++)
					{
						this->_alloc.construct((new_data + i), this->_c_data[i]);
						this->_alloc.destroy(this->_c_data + i);
					}
				//	*/
					this->_alloc.deallocate(this->_c_data, this->_capacity);
					this->_capacity = new_cap;
					this->_c_data = new_data;
				}
			}

			bool empty() const{
				if (this->_c_size == 0)
					return (1);
				return (0);
			}

			size_type max_size() const{
			#ifdef __APPLE__
				if (sizeof(Type) == 1)
					return (std::numeric_limits< size_t >::max() / (2 * sizeof (Type)));
			#endif
				return (this->_alloc.max_size());
			//#else
			}


						//--------------------------------//
						//	 *** 	 MODIFIERS		 ***  //
						//--------------------------------//

			void push_back( const Type& value ) {
				if (this->_capacity == 0)
				{
					this->_c_data = this->_alloc.allocate(1);
					//this->_alloc.construct(this->_c_data, value);
					this->_capacity = 1;
				}
				else if(this->_c_size == this->_capacity)
				{

					this->_capacity *= 2;
					value_type	*new_data = this->_alloc.allocate((this->_capacity));
					//std::memset(new_data, 0, (this->_capacity * 2) + 1);
					for (size_t i = 0; i < this->_c_size; i++)
					{
						this->_alloc.construct((new_data + i), *((*this)._c_data + i));
						this->_alloc.destroy((*this)._c_data + i);
					}
					this->_alloc.deallocate((*this)._c_data, this->_capacity);
					this->_c_data = new_data;
				}
				this->_alloc.construct(((*this)._c_data + (*this)._c_size), value);
				this->_c_size++;
			}

			void pop_back()
			{
				if (this->_c_size <= 0)
					return ;
				else {
					this->_alloc.destroy((*this)._c_data + this->_c_size - 1);
					this->_c_size--;
				}
			}

		private:
			size_t			_c_size;
			value_type *	_c_data;
        	allocator_type	_alloc;
			size_t			_capacity;
	};
} // end of namespace
#endif
