/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-phng <thi-phng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:59:18 by thi-phng          #+#    #+#             */
/*   Updated: 2023/01/24 15:52:11 by thi-phng         ###   ########.fr       */
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

			pointer getElements(void) const {
				return (this->_c_data);
			}

						//--------------------------------//
						// ***	  MEMBER FUNCTIONS 	***   //
						//--------------------------------//

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
			vector( const vector& other ) : _c_size(other.size()), _c_data(0),_alloc(other.get_allocator()), _capacity(other.size()) {//constructeur de recopie
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
				for (size_t i = 0; i < this->_c_size; i++)
					this->_alloc.destroy((this->_c_data + i));
				this->_alloc.deallocate(this->_c_data, this->_capacity);
			};

			vector< Type, Allocator >& operator=(const vector<Type, Allocator>& other)
    		{
    		    if (this != &other)
    		    {
					for (size_t i = 0; i < this->_c_size; i++)
						this->_alloc.destroy((this->_c_data + i));
    		        this->_c_size = other._c_size;
					if (this->_capacity != other.capacity()){
						this->_alloc.deallocate(_c_data, this->_capacity);
    		        	this->_capacity = other.size();
						this->_c_data = this->_alloc.allocate(this->_c_size);
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
				if (count > this->max_size()) // equal .max_size()
				{
					throw std::invalid_argument("cannot create std::vector larger than max_size()");
					std::abort();
				}
				clear();
				if (count > this->_capacity)
				{
					this->_alloc.deallocate(_c_data, this->_capacity);
					this->_c_data = this->_alloc.allocate(count);
					this->_capacity = count;
				}
				//for (size_type k = 0; k < count; k++)
				//	this->_alloc.construct(this->_c_data + k, value);
				//this->_c_size = count;
				while (_c_size < count)
					this->_alloc.construct(&this->_c_data[_c_size++], value);
			}
			
	// *** //
			// assign_2 with iterator
			template< class InputIt > void assign( InputIt first, InputIt last ){
				size_type diff = std::distance(first, last);

				if (diff > this->max_size())
				{
					throw std::invalid_argument("cannot create std::vector larger than max_size()");
					std::abort();
				}
				clear();
				if (diff > this->_capacity)
				{
					this->_alloc.deallocate(_c_data, this->_capacity);
					this->_c_data = this->_alloc.allocate(diff);
					this->_capacity = diff;
				}
				while (first != last)
					this->_alloc.construct(&this->_c_data[_c_size++], *first++);
			}

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
				return (this->_c_data[pos]); }

			reference at( size_type pos ){
				return (const_cast<reference>(static_cast < const typename ft::vector< Type, Allocator >& >(*this).at(pos))); }

			//reference operator[]( size_type pos );
			Type& operator[](size_t i) {
			/*	if (i > this->_c_size)
				{
					throw std::invalid_argument( "Error: Can't acess further, sorry\n" );
				 }*/
				return (const_cast<reference>(static_cast < const typename ft::vector< Type, Allocator > &>(*this)[i])); }

			//const_reference operator[]( size_type pos ) const;
  			const Type& operator[](size_t i) const {
				return (this->_c_data[i]); }

			const_reference front() const {
				return (this->_c_data[0]); }

			reference front(){
				return (const_cast<reference>(
					static_cast < const typename ft::vector< Type, Allocator > &>(*this).front())); }

			const_reference back() const{
				return (this->_c_data[this->_c_size - 1]); }

			reference back(){
					return (const_cast<reference>(
						static_cast < const typename ft::vector< Type, Allocator > &>(*this).back()));}

			pointer data(){
				if (this->_c_size == 0 || !(this->_c_data))
					return (NULL);
				return (this->_c_data);
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
				template< class ItType, class ItAllocator >
				friend class vector ;
				public:
					typedef std::random_access_iterator_tag	iterator_category;
					typedef Type							value_type;
					typedef size_t							size_type;
					typedef value_type						&reference;
					typedef value_type						*pointer;
					typedef std::ptrdiff_t					difference_type;

					// Constructor
			 		iterator(void) : _ptr(NULL){}
			 		iterator(pointer p) : _ptr(p){}
			 		iterator(const iterator& other) : _ptr(other._ptr) {}
		     		~iterator(){}

			 		iterator& operator=(const iterator &other){
			 			this->_ptr = other._ptr;
			 		   return (*this);
			 		}

			 		bool operator==(const iterator &other) const{
			 		    return (this->_ptr == other._ptr); }
			 		bool operator!=(const iterator &other) const{
			 		    return (this->_ptr != other._ptr); }
			 		bool operator>(const iterator &other) const{
			 		    return (this->_ptr > other._ptr); }
			 		bool operator<=(const iterator &other) const{
			 		    return (this->_ptr <= other._ptr); }
			 		bool operator>=(const iterator &other) const{
			 		    return (this->_ptr <= other._ptr); }
			 		bool operator<(const iterator &other) const{
			 		    return (this->_ptr < other._ptr); }

					//access
			 		// Overload the * operator to return a reference to the element at the current iterator position
			 		reference operator*() const {
			 		  return (* _ptr);;
			 		}

			 		pointer operator->() const{ return (this->_ptr); }

			 		reference operator[](size_type n) const { return (_ptr[n]); }

					//assignment
		    		iterator& operator+=(size_type n){
			 		   _ptr += n;
			 		   return(* this); }		

		    		iterator& operator-=(size_type n){
			 		   _ptr -= n;
			 		   return(* this); }

					// arithmetic
					iterator operator+(size_type n) const{
						iterator it(_ptr);
						it += n;
						return (it);
					}		

					friend iterator operator+(size_t i, const iterator& it) { return it + i;}

					iterator operator-(size_type n) const { return (iterator(_ptr - n)); }		

					difference_type operator+(iterator const &other) const {  return (this->_ptr + other._ptr); }		

					difference_type operator-(iterator const &other) const { return (this->_ptr - other._ptr); }		


			//pre-increment (++a)
    		 		iterator& operator++(){
			 		    ++_ptr;
			 		    return (*this); }
			//post-decrement (--a)
    		 		iterator& operator--(){
			 		    --_ptr;
			 		    return (*this); }
			// post-increment (a++)
    		 		iterator operator++(int){
			 		    iterator tmp(*this);
			 		    ++(*this);
			 		    return (tmp); }
			//pret-decrement (a--)
    		 		iterator operator--(int){
			 		    iterator tmp(*this);
			 		    --(*this);
			 		    return (tmp); }

			private:
			 	pointer  	_ptr;
			};

			//template <class T>
			class const_iterator {
				template< class ItType, class ItAllocator >
				friend class vector ;
				public:
					typedef std::random_access_iterator_tag	iterator_category;
					typedef const Type						value_type;
					typedef size_t							size_type;
					typedef value_type						&reference;
					typedef value_type						*pointer;
					typedef std::ptrdiff_t					difference_type;

					// Constructor
			 		const_iterator(void) : _ptr(NULL){}
			 		const_iterator(pointer p) : _ptr(p){}
			 		const_iterator(const const_iterator& other){ this->_ptr = other._ptr;}
			 		const_iterator(const iterator& other){ this->_ptr = other._ptr;}
		     		~const_iterator(){}

			 		const_iterator& operator=(const const_iterator &other){
			 			this->_ptr = other._ptr;
			 		   return (*this);
			 		}
			 		bool operator==(const const_iterator &other) const{
			 		    return (this->_ptr == other._ptr);
			 		}
			 		bool operator!=(const const_iterator &other) const{
			 		    return (this->_ptr != other._ptr);
			 		}
			 		bool operator>(const const_iterator &other) const{
			 		    return (this->_ptr > other._ptr);
			 		}
			 		bool operator<=(const const_iterator &other) const{
			 		    return (this->_ptr <= other._ptr);
			 		}
			 		bool operator>=(const const_iterator &other) const{
			 		    return (this->_ptr <= other._ptr);
			 		}
			 		bool operator<(const const_iterator &other) const{
			 		    return (this->_ptr < other._ptr);
			 		}

			//access
			 		// Overload the * operator to return a reference to the element at the current iterator position
			 		reference operator*() const { return (* _ptr); }

			 		pointer operator->() const{ return (this->_ptr); }

			 		reference operator[](size_type n) const { return (_ptr[n]); }

			//assignment
		    		const_iterator& operator+=(size_type n){
			 		   _ptr += n;
			 		   return(* this);
					}		

		    		const_iterator& operator-=(size_type n){
			 		   _ptr -= n;
			 		   return(* this);
					}		
			// arithmetic
					const_iterator operator+(size_type n) const{ return (const_iterator(_ptr + n)); }		

					friend const_iterator operator+(size_type i, const const_iterator& it) { return it + i;}

					const_iterator operator-(size_type n) const{ return (const_iterator(_ptr - n)); }		

					difference_type operator+(const_iterator const &other) const{ return (this->_ptr + other._ptr); }

					difference_type operator-(const_iterator const &other) const{ return (this->_ptr - other._ptr); }


		//pre		-increment (++a)
    		 		const_iterator& operator++(){
			 		    ++_ptr;
			 		    return (*this);
			 		}
		//pos		t-decrement (--a)
    		 		const_iterator& operator--(){
			 		    --_ptr;
			 		    return (*this);
			 		}
		// po		st-increment (a++)
    		 		const_iterator operator++(int){
			 		    const_iterator tmp(*this);
			 		    ++(*this);
			 		    return (tmp);
			 		}
		//pre		t-decrement (a--)
    		 		const_iterator operator--(int){
			 		    const_iterator tmp(*this);
			 		    --(*this);
			 		    return (tmp);
			 		}

			private:
			 	pointer  	_ptr;
			};

			iterator begin() { return (iterator(this->_c_data)); }

			const_iterator begin() const { return (const_iterator(this->_c_data)); }

			iterator end() { return (iterator(this->_c_data + this->_c_size )); }
			const_iterator end() const{ return (const_iterator(this->_c_data + this->_c_size )); }

		/*	
			//Iterator to the element following the last element.

			//Reverse iterator to the first element.
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;


			//Reverse iterator to the element following the last element.
			reverse_iterator rend();
			const_reverse_iterator rend() const;


			*/

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
					pointer new_data = this->_alloc.allocate(new_cap);
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
				//	( clear, insert, erease, push_back, pop_back, resize, swap )

			void clear(){
				for (size_t i = 0; i < this->_c_size; ++i)
					this->_alloc.destroy((*this)._c_data + i );
				this->_c_size = 0;
			}

			iterator erase( iterator pos ){
				if (pos == end())
					return (end());
				std::copy(pos + 1, end(), pos);
				resize(_c_size - 1);
				return (pos);
			}

			iterator erase( iterator first, iterator last ){
				if (first == last)
					return (last);
				size_t dif = std::distance( first, last);
				if (last != end()){
					std::copy(last, end(), first);
				}
				resize(_c_size - dif);
				return (first);
			}


			void push_back( const Type& value ) {
				if (this->_capacity == 0)
				{
					this->_c_data = this->_alloc.allocate(1);
					this->_capacity = 1;
				}
				else if(this->_c_size == this->_capacity)
				{

					this->_capacity *= 2;
					value_type	*new_data = this->_alloc.allocate((this->_capacity));
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
			void resize( size_type count, value_type value= value_type() ){
				if (count > this->max_size())
				{
					throw std::length_error("vector::resize");
					//std::abort();
				}
				if (this->_c_size < count)
				{
					reserve(count);
					for (iterator it (this->_c_data + count - 1); it != end() - 1;  --it)
						this->_alloc.construct(it._ptr, value);
				}
				else if (this->_c_size > count)
				{
					for (iterator it (this->_c_data + count); it != end(); ++it)
						this->_alloc.destroy(it._ptr);
				}
				this->_c_size = count;
			}

			void swap( vector& other ){

				size_type tmp_size = this->_c_size;
				pointer tmp_data = this->_c_data;
				size_type tmp_capacity = this->_capacity;
				allocator_type tmp_alloc = this->_alloc;
				
				this->_c_size = other._c_size;
				this->_c_data = other._c_data;
				this->_capacity = other._capacity;
				this->_alloc = other._alloc;

				other._c_size = tmp_size;
				other._c_data = tmp_data;
				other._capacity = tmp_capacity;
				other._alloc = tmp_alloc;
			}

		private:
			size_t			_c_size;
			value_type *	_c_data;
        	allocator_type	_alloc;
			size_t			_capacity;
	};
			//template< class T, class Alloc >
template< class Type, class Allocator >
void swap( ft::vector < Type, Allocator >& x, ft::vector < Type, Allocator > & other ) {
	x.swap(other);
}

template< class Iterator >
void swap(Iterator& x, Iterator& other ) {
	Iterator	tmp(x);

	x = other;
	other = tmp;
}

} // end of namespace
#endif
