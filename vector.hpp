#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>
#include "vector.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"

// A template is a simple yet very powerful tool in C++. The simple idea is to pass
// data type as a parameter so that we don’t need to write the same code for different
// data types. For example, a software company may need to sort() for different data types. 
// Rather than writing and maintaining multiple codes, we can write one sort() and pass 
// data type as a parameter. 
// C++ adds two new keywords to support templates: ‘template’ and ‘typename’.
// The second keyword can always be replaced by the keyword ‘class’.

// Class template
namespace ft
{
	template< class Type, class Allocator = std::allocator< Type > >
		class vector
		{
			public:

				typedef Type 				value_type;
				typedef value_type *	 	pointer;
				typedef std::size_t 		size_type;//typedef = using
				typedef Allocator 			allocator_type;	
				typedef Allocator & 		allocator_reference;	
				typedef const Allocator & 	const_allocator_reference;	
				typedef value_type & 		reference;
				typedef const Type & 		const_reference;
				typedef std::ptrdiff_t			difference_type;

				//--------------------------------//
				// ***	  MEMBER FUNCTIONS 	***   //
				//--------------------------------//

				explicit vector( const Allocator& alloc = Allocator() ) : _c_size(0), _c_data(0), _alloc(alloc), _capacity(0) {
				}

				explicit vector( size_type count, const_reference value = value_type(), const Allocator& alloc = Allocator()) : _c_size(count), _alloc(alloc), _capacity(count){
					if (count > this->max_size()) // equal .max_size()
					{
						throw std::length_error("cannot create std::vector larger than max_size()");
					}
					this->_c_data =  this->_alloc.allocate(count);
					for (size_t i = 0; i < count; i++)
						this->_alloc.construct(this->_c_data + i, value);	
				}

				//	range(3) from first to last
				//	creates a vector from a range of elements defined by two iterators
				template< class InputIt > vector( InputIt first, InputIt last, const_allocator_reference alloc = allocator_type(),
						typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) : _c_size(0), _c_data(0), _alloc(alloc), _capacity(0)
			{
				insert(begin(), first, last);
			}

				vector( const vector& other ) : _c_size(other.size()), _c_data(0),_alloc(other.get_allocator()), _capacity(other.size())
			{
				this->_c_data = this->_alloc.allocate(other.capacity());
				for (size_t i = 0; i < this->_c_size; i++)
					this->_alloc.construct(this->_c_data + i, other[i]);	
			}

				~vector(void)
				{
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

				void assign( size_type count, const_reference value )
				{
					if (count > this->max_size()) // equal .max_size()
					{
						throw std::invalid_argument("cannot create std::vector larger than max_size()");
					}
					clear();
					resize(count, value);
				}
				// assign_2 with iterator
				template< class InputIt > void assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
				{
					size_t diff = ft::distance(first, last);;

					if (diff > this->max_size())
					{
						throw std::invalid_argument("cannot create std::vector larger than max_size()");
					}
					clear();
					insert(begin(), first, last);
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

				reference operator[](size_t i) { return (_c_data[i]); }//return (const_cast<reference>(static_cast < const typename ft::vector< Type, Allocator > &>(*this)[i])); }

				const_reference operator[](size_t i) const { return (this->_c_data[i]); }

				const_reference front() const { return (this->_c_data[0]); }

				reference front(){ return (const_cast<reference>(static_cast < const typename ft::vector< Type, Allocator > &>(*this).front())); }

				const_reference back() const{ return (this->_c_data[this->_c_size - 1]); }

				reference back(){ return (const_cast<reference>( static_cast < const typename ft::vector< Type, Allocator > &>(*this).back()));}

				pointer data()
				{
					if (this->_c_size == 0 || !(this->_c_data))
						return (NULL);
					return (this->_c_data);
				}

				const pointer data() const
				{
					if (this->_c_size == 0 || !(this->_c_data))
						return (NULL);
					return (this->_c_data);
				}

				//--------------------------------//
				//	 *** 	 ITERATORS  	***   //
				//--------------------------------//
				// begin, end, rbegin, rend	

				//template <class T>
				class const_iterator;
				class iterator 
				{
					template< class ItType, class ItAllocator >
						friend class vector ;
					friend class const_iterator ;
					public:
					typedef std::random_access_iterator_tag	iterator_category;
					typedef Type							value_type;
					typedef size_t							size_type;
					typedef value_type&						reference;
					typedef value_type*						pointer;
					typedef std::ptrdiff_t					difference_type;

					// Constructor
					iterator(void) : _ptr(NULL){}
					iterator(pointer p) : _ptr(p){}
					iterator(const iterator& other) : _ptr(other._ptr) {}
					~iterator(){}

//					//User-defined conversion function/
//					operator	iterator<value_type const>() const
//					{return (iterator<value_type const>(_ptr));}

					iterator& operator=(const iterator &other){
						this->_ptr = other._ptr;
						return (*this);
					}

					bool operator==(const iterator &other) const{ return (_ptr == other._ptr); }
					bool operator!=(const iterator &other) const{ return (_ptr != other._ptr); }
					bool operator> (const iterator &other) const{ return (_ptr >  other._ptr); }
					bool operator<=(const iterator &other) const{ return (_ptr <= other._ptr); }
					bool operator>=(const iterator &other) const{ return (_ptr >= other._ptr); }
					bool operator< (const iterator &other) const{ return (_ptr  < other._ptr); }

					bool operator==(const const_iterator &other) const{ return (_ptr == other._ptr); }
					bool operator!=(const const_iterator &other) const{ return (_ptr != other._ptr); }
					bool operator> (const const_iterator &other) const{ return (_ptr >  other._ptr); }
					bool operator<=(const const_iterator &other) const{ return (_ptr <= other._ptr); }
					bool operator>=(const const_iterator &other) const{ return (_ptr >= other._ptr); }
					bool operator< (const const_iterator &other) const{ return (_ptr <  other._ptr); }

					//access
					// Overload the * operator to return a reference to the element at the current iterator position
					reference operator*() const { return (* _ptr); }

					pointer operator->() const{ return (_ptr); }

					reference operator[](size_type n) const { return (_ptr[n]); }

					//assignment
					iterator& operator+=(size_type n){
						_ptr += n;
						return(* this); }		

					iterator& operator-=(size_type n){
						_ptr -= n;
						return(* this); }

					// arithmetic
					iterator operator+(size_type n) const {
						iterator it(_ptr);
						it += n;
						return (it);
					}		

					friend iterator operator+(size_t i, const iterator& it) { return it + i;}
//					friend iterator operator+(size_t i, const const_iterator& it) { return it + i;}

					difference_type operator+(iterator const &other) const {  return (this->_ptr + other._ptr); }		
					difference_type operator+(const_iterator const &other) const {  return (this->_ptr + other._ptr); }		

					iterator operator-(size_type n) const { return (iterator(_ptr - n)); }		
					iterator operator-(size_type n) { return (iterator(_ptr - n)); }		

					difference_type operator-(iterator const &other) { return (this->_ptr - other._ptr); }		
					difference_type operator-(const_iterator const &other) const { return (this->_ptr - other._ptr); }		


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

				//--------------------------------//
				//	 ***  CONST_ITERATORS  	***   //
				//--------------------------------//
				//template <class T>
				class const_iterator 
				{
					template< class ItType, class ItAllocator >
						friend class vector ;
					friend class iterator ;
					public:
					typedef std::random_access_iterator_tag	iterator_category;
					typedef const Type						value_type;
					typedef size_t							size_type;
					typedef value_type&						reference;
					typedef const value_type&				const_reference;
					typedef value_type*						pointer;
					typedef const value_type*				const_pointer;
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
					bool operator==(const const_iterator &other) const {return (this->_ptr == other._ptr);}
					bool operator!=(const const_iterator &other) const {return (this->_ptr != other._ptr);}
					bool operator>(const const_iterator &other) const {return (this->_ptr > other._ptr);}
					bool operator<(const const_iterator &other) const {return (this->_ptr < other._ptr);}
					bool operator<=(const const_iterator &other) const {return (this->_ptr <= other._ptr);}
					bool operator>=(const const_iterator &other) const {return (this->_ptr >= other._ptr);}

					//access
					// Overload the * operator to return a reference to the element at the current iterator position
					const_reference operator*() const { return (* _ptr); }

					const_pointer operator->() const{ return (_ptr); }

					const_reference operator[](size_type n) const { return (_ptr[n]); }

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
					const_iterator operator+(size_type n) const { return (const_iterator(_ptr + n)); }		

					friend const_iterator operator+(size_type i, const const_iterator& it) { return it + i;}

					const_iterator operator-(size_type n) { return (const_iterator(_ptr - n)); }
					const_iterator operator-(size_type n) const { return (const_iterator(_ptr - n)); }		

					difference_type operator+(const_iterator const &other) const { return (_ptr + other._ptr); }

					difference_type operator-(const_iterator const &other) const { return (_ptr - other._ptr); }

					//pre-increment (++a)
					const_iterator& operator++(){
						++_ptr;
						return (*this);
					}
					//post-decrement (--a)
					const_iterator& operator--(){
						--_ptr;
						return (*this);
					}
					// post-increment (a++)
					const_iterator operator++(int){
						const_iterator tmp(*this);
						++(*this);
						return (tmp);
					}
					//pret-decrement (a--)
					const_iterator operator--(int){
						const_iterator tmp(*this);
						--(*this);
						return (tmp);
					}

					private:
						pointer  	_ptr;
				};

				typedef ft::reverse_iterator<iterator>					reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

				iterator begin() { return (iterator(this->_c_data)); }
				const_iterator begin() const { return (const_iterator(this->_c_data)); }

				iterator end() { return (iterator(this->_c_data + this->_c_size )); }
				const_iterator end() const{ return (const_iterator(this->_c_data + this->_c_size )); }

				reverse_iterator	rbegin() { return (reverse_iterator(_c_data + _c_size)); }
				const_reverse_iterator	rbegin() const { return (const_reverse_iterator(_c_data + _c_size)); }

				reverse_iterator	rend() { return (reverse_iterator(_c_data)); }
				const_reverse_iterator	rend() const { return (const_reverse_iterator(_c_data)); }


				//--------------------------------//
				//	 *** 	 CAPACITY		 ***  //
				//--------------------------------//

				size_type size() const {
					return (this->_c_size); }

				size_type capacity(void) const {
					return (this->_capacity);
				}

				void reserve( size_type new_cap ){
					if (new_cap >= max_size())
						throw std::length_error("vector::reserve");
					else if (new_cap > _capacity)
					{
						pointer new_data = _alloc.allocate(new_cap);
						for (size_t i = 0; i < _c_size; i++)
						{
							_alloc.construct((new_data + i), _c_data[i]);
							_alloc.destroy(_c_data + i);
						}
						if (_c_data)
							_alloc.deallocate(_c_data, _capacity);
						_capacity = new_cap;
						_c_data = new_data;
					}
				}

				bool empty() const{
					if (this->_c_size == 0)
						return (1);
					return (0);
				}

				size_type max_size() const{
//#ifdef __APPLE__
//					if (sizeof(Type) == 1)
//					map<Key, T, Compare, Alloc>::_max_size =
				//return (std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2 ?: 1);
			//			return (std::numeric_limits< size_t >::max() / (2 * sizeof (Type)));
			 		return(_alloc.max_size());
//#endif
//return (this->_alloc.max_size());
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

				iterator insert( const_iterator pos, const_reference value )
				{
					size_type	index = pos - begin();
					if (_c_size == _capacity)
						reserve(_capacity ? 2 * _capacity : 1);
					for (size_type i = _c_size; i > index; --i)
					{
						_alloc.construct(_c_data + i, _c_data[i - 1]);
						_alloc.destroy(_c_data + i - 1);
					}
					_alloc.construct(_c_data + index, value);
					++_c_size;

					return (iterator(_c_data + index));
				}

				void	insert(const_iterator pos, size_t count, const_reference value)
				{
					size_t index = pos - begin();

					if (count == 0)
						return ;
					else
					{
						if (size() + count > _capacity)
							reserve(capacity() ? capacity() + count : count);
						for (size_t i = _c_size; i > index; --i)
						{
							_alloc.construct(_c_data + i + count - 1, _c_data[i - 1]);
							_alloc.destroy(_c_data + i);
						}
						for (size_t i = index; i < index + count; ++i)
							_alloc.construct(_c_data + i, value);
						_c_size += count;
					}
				}				

				template< class InputIt >
					void insert( iterator pos, InputIt first, InputIt last,
							typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
						difference_type const	i = pos - begin();
						difference_type const	old_end_i = end() - begin();
						iterator				old_end, end;
						size_type				dif;

						dif = ft::distance(first, last);
						if (_capacity < _c_size + dif)
							resize(_c_size + dif); 
						else
							_c_size += dif;
						end = this->end();
						pos = begin() + i;
						old_end = begin() + old_end_i;
						while (old_end != pos)
							*--end = *--old_end;
						while (first != last)
							*(pos++) = *(first++);
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
					if(_c_size == _capacity)
						reserve(capacity() ? _capacity * 2 : 1);
					_alloc.construct(_c_data + _c_size, value);
					_c_size++;
					return ;
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
						std::abort();
					}
					if (count > _c_size)
					{
						reserve(count);
						for (iterator it (this->_c_data + count - 1); it != end() - 1;  --it)
							this->_alloc.construct(it._ptr, value);
					}
					else if (count < _c_size)
					{
						for (iterator it (this->_c_data + count); it != end(); ++it)
							this->_alloc.destroy(it._ptr);
					}
					_c_size = count;
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

				// Non-member functionn
				friend bool operator==( const ft::vector<Type, Allocator>& lhs, const ft::vector<Type, Allocator>& rhs )
				{
					if (lhs.size() != rhs.size())
						return (0);
					return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
				}
				friend bool operator!=( const ft::vector<Type, Allocator>& lhs, const ft::vector<Type, Allocator>& rhs ) { return (!(lhs == rhs)); }
				friend bool operator<( const ft::vector<Type, Allocator>& lhs, const ft::vector<Type, Allocator>& rhs ) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())) ; }
				friend bool operator>( const ft::vector<Type, Allocator>& lhs, const ft::vector<Type, Allocator>& rhs ) { return (rhs < lhs); }
				friend bool operator>=( const ft::vector<Type, Allocator>& lhs, const ft::vector<Type, Allocator>& rhs ) { return (!(lhs < rhs)); }
				friend bool operator<=( const ft::vector<Type, Allocator>& lhs, const ft::vector<Type, Allocator>& rhs ) { return (!(lhs > rhs)); }

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
