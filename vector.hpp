#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include <cmath>
# include <vector>
# include <exception>
# include <cstddef>
# include <stdexcept>
# include <sstream>
# include "integral.hpp"
# include "lexicographical_compare.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		protected:
			Allocator	m_allocator;
			std::size_t	m_element_number;
			std::size_t	m_alloc_size;
			T			*m_ptr;

		public:
			typedef typename Allocator::reference 			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer 			pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;			
			typedef T 										value_type;
			typedef Allocator 								allocator_type;
			typedef ft::vector_iterator<value_type>			iterator;
			typedef ft::vector_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator> 			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 	const_reverse_iterator;
		

		/*
		**		__CONSTRUCTOR__
		*/

		vector(const Allocator& allocator = Allocator())
		: m_allocator(allocator), m_element_number(0), m_alloc_size(0), m_ptr(0) {}
		
		explicit vector(size_type n, const value_type& value = value_type(),
			const allocator_type& allocator = allocator_type())
		: m_allocator(allocator), m_element_number(n), m_alloc_size(n), m_ptr(0)
		{
			m_ptr = m_allocator.allocate(n);
			for(size_type i = 0; i < n; i++)
				m_allocator.construct( m_ptr + i, value );
		}

		template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& allocator = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: m_allocator(allocator), m_ptr(NULL) {
				size_type		range_len = 0;

				for (InputIterator it = first; it  != last; it++)
					range_len++;
				if (range_len > this->max_size())
					throw std::length_error("Error: allocation over max size\n");
				m_element_number = range_len;
				m_alloc_size = range_len;
				m_ptr = m_allocator.allocate(m_alloc_size);
				for (size_type i = 0; first != last; first++)
				{
					m_allocator.construct( m_ptr + i, *first );
					i++;
				}
			}

		vector(const vector<T,Allocator>& x)
		{
			size_type	size_x = x.size();
			if (this == &x)
				return ;
			m_ptr = m_allocator.allocate(size_x);
			for (size_type i = 0; i < size_x; i++)
				m_allocator.construct( m_ptr + i, x[i] );
			m_element_number = size_x;
			m_allocator = x.m_allocator;
			m_alloc_size = size_x;
		}

		vector<T>
		&operator=( vector<T> &a )// maybe cont le vector
		{
			size_type	size_a = a.size();

			if (this == &a)
				return (*this);
			if (size_a > m_alloc_size)
				this->reserve(size_a);
			for (size_type i = 0; i < size_a; i++)
				m_ptr[i] = a[i];
			m_element_number = size_a;
			return (*this);
		}

		/*
		**		__DESTRUCTOR__
		*/

		~vector()
		{
			if (m_ptr)
			{
				this->clear();
				m_allocator.deallocate(m_ptr, m_alloc_size);
			}
		}

		/*
		**		__MEMBER FUNCTIONS__
		*/

		// _ITERATORS_
		iterator
		begin()
		{ return (iterator(m_ptr)); }

		const_iterator
		begin() const
		{ return (const_iterator(m_ptr)); }

		iterator
		end()
		{ return (iterator(m_ptr + m_element_number)); }

		const_iterator
		end() const
		{ return (const_iterator(m_ptr + m_element_number)); }

		reverse_iterator
		rbegin()
		{ return (reverse_iterator(end())); }

		const_reverse_iterator
		rbegin() const
		{ return (const_reverse_iterator(end())); }

		reverse_iterator
		rend()
		{ return (reverse_iterator(begin())); }

		const_reverse_iterator
		rend() const
		{ return (const_reverse_iterator(begin())); }

		// _CAPACITY_
		inline size_type
		size( void ) const
		{ return (m_element_number); }

		inline size_type
		max_size( void ) const
		{ return (m_allocator.max_size()); }
		
		void
		resize (size_type n, value_type val = value_type())
		{
			// check negative n
			// exception quand max size atteint
			if (n > this->max_size())
				throw std::length_error("Error: allocation over max size\n");
			if (n > m_alloc_size)
			{
				int	new_allocate_size = (m_alloc_size != 0) ? m_alloc_size * std::ceil((double)n / m_alloc_size) : n;
				T	*new_ptr = m_allocator.allocate(new_allocate_size);

				for(size_type i = 0; i < n; i++)
				{
					if (i < m_element_number)
						m_allocator.construct(new_ptr + i, *(m_ptr + i));
					else
						m_allocator.construct(new_ptr + i, val);
				}
				this->clear();
				m_allocator.deallocate(m_ptr, m_element_number);
				m_alloc_size = new_allocate_size;
				m_element_number = n;
				m_ptr = new_ptr;
			}
			else if (n > m_element_number)
			{
				for (size_t i = m_element_number; i < n; i++)
					m_allocator.construct(m_ptr + i, val);
				m_element_number = n;
			}
			else
			{
				for (size_t i = n; i < m_element_number; i++)
					m_allocator.destroy(m_ptr + i);
				m_element_number = n;
			}
		}

		inline size_type
		capacity( void ) const
		{ return (m_alloc_size); }
		
		inline bool
		empty( void ) const
		{ return (m_element_number == 0 ? true : false); }
		
		void
		reserve( size_type n )
		{
			if (n > this->max_size())
				throw std::length_error("Error: allocation over max size\n");
			if (n <= m_alloc_size)
				return ;
			int	new_allocate_size = (m_alloc_size != 0) ? m_alloc_size * std::ceil((double)n / m_alloc_size) : n;
			T	*new_ptr = m_allocator.allocate(new_allocate_size);
			
			for(size_type i = 0; i < m_element_number; i++)
			{
				if (i < m_element_number)
					m_allocator.construct(new_ptr + i, *(m_ptr + i));
			}
			m_allocator.deallocate(m_ptr, m_element_number);
			m_alloc_size = new_allocate_size;
			m_ptr = new_ptr;
		}

		// _ELEMENT ACCESS_
		reference
		operator[] (size_type n)
		{ return (*(m_ptr + n)); }

		const_reference
		operator[] (size_type n) const
		{ return (*(m_ptr + n)); }

		reference
		at (size_type n)
		{
			if (n > m_element_number)
			{
				std::ostringstream error_msg;
				error_msg << "vector::range_check: n (which is " << n << ") >= this->size() (which is " << m_element_number << ")";
				throw std::out_of_range(error_msg.str());//exceptions out of range a modif
			}
			return ((*this)[n]);
		}

		const_reference
		at (size_type n) const
		{
			if (n > m_element_number)
			{
				std::ostringstream error_msg;
				error_msg << "vector::range_check: n (which is " << n << ") >= this->size() (which is " << m_element_number << ")";
				throw std::out_of_range(error_msg.str());//exceptions out of range a modif
			}
			return ((*this)[n]);
		}

		reference
		front()
		{ return ((*this)[0]); }
		
		const_reference
		front() const
		{ return ((*this)[0]); }
		
		reference
		back()
		{ return ((*this)[m_element_number - 1]); }
		
		const_reference
		back() const
		{ return ((*this)[m_element_number - 1]); }

		// _MODIFIERS_
		template <class InputIterator>
			void
			assign (InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				size_type		range_len = 0;

				for (InputIterator it = first; it  != last; it++)
					range_len++;
				this->clear();
				if (m_alloc_size < range_len)
					this->resize(range_len);
				else
					m_element_number = range_len;
				for (size_type i = 0; first != last; first++)
				{
					m_ptr[i] = *first;
					i++;
				}
			}

		void
		assign (size_type n, const value_type& val)
		{
			this->clear();
			if (n > m_alloc_size)
				this->resize(n, val);
			else
				m_element_number = n;
			for (size_type i = 0; i < n; i++)
				m_ptr[i] = val;
		}

		iterator
		insert (iterator position, const value_type& val)
		{
			vector<T>	tmp(position, this->end());
			size_type	index = position - this->begin();

			if (m_alloc_size == m_element_number)
				resize(m_element_number + 1);
			else
				m_element_number++;
			m_ptr[index] = val;
			for (size_type i = 0; ++index < m_element_number; i++)
				m_ptr[index] = tmp[i];
			return (position);
		}

		void
		insert (iterator position, size_type n, const value_type& val)
		{
			vector<T>	tmp(position, this->end());
			size_type	index = position - this->begin();

			if (m_alloc_size < m_element_number + n)
				resize(m_element_number + n);
			else
				m_element_number += n;
			for (size_type i = 0; i < n; i++)
			{
				m_ptr[index] = val;
				index++;
			}
			for (size_type i = 0; index < m_element_number; i++)
			{
				m_ptr[index] = tmp[i];
				index++;
			}
		}

		template <class InputIterator>
			void
			insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				size_type	el_nbr_to_insert = 0;
				vector<T>	tmp(position, this->end());
				size_type	index = position - this->begin();

				for (InputIterator it = first; it  != last; it++)
					el_nbr_to_insert++;
				if (m_alloc_size < m_element_number + el_nbr_to_insert)
					resize(m_element_number + el_nbr_to_insert);
				else
					m_element_number += el_nbr_to_insert;
				for (InputIterator it = first; it  != last; it++)
				{
					m_ptr[index] = *it;
					index++;
				}
				for (size_type i = 0; index < m_element_number; i++)
				{
					m_ptr[index] = tmp[i];
					index++;
				}
			}

		iterator
		erase (iterator position)
		{
			size_type	index = position - this->begin();

			m_allocator.destroy(&m_ptr[index]);
			while (index < m_element_number - 1)
			{
				m_ptr[index] = m_ptr[index + 1];
				index++;
			}
			m_element_number--;
			return (position);
		}

		iterator
		erase (iterator first, iterator last)
		{
			size_type	index_first = first - this->begin();
			size_type	index_last = last - this->begin();

			for (size_t i = 0; index_last + i < m_element_number; i++)
				m_ptr[index_first + i] = m_ptr[index_last + i];
			for (size_type i = last - first; i < m_element_number; i++)
				m_allocator.destroy(&m_ptr[index_first + i]);
			m_element_number -= last - first;
			return (first);
		}

		void
		swap (vector& x)
		{
			Allocator	tmp_allocator 		= x.m_allocator;
			std::size_t	tmp_element_number	= x.m_element_number;
			std::size_t	tmp_alloc_size		= x.m_alloc_size;
			T			*tmp_ptr 			= x.m_ptr;

			x.m_alloc_size					= m_alloc_size;
			x.m_allocator					= m_allocator;
			x.m_element_number				= m_element_number;
			x.m_ptr							= m_ptr;

			m_alloc_size					= tmp_alloc_size;
			m_allocator						= tmp_allocator;
			m_element_number				= tmp_element_number;
			m_ptr 							= tmp_ptr;
		}

		void
		push_back ( const value_type& val )
		{
			if (m_element_number >= m_alloc_size)
				this->resize(m_element_number + 1, val);
			else
			{
				m_allocator.construct( m_ptr + m_element_number, val );
				m_element_number++;
			}
		}

		void
		pop_back( void )
		{
			m_allocator.destroy(&(*this)[m_element_number - 1]);
			m_element_number--;
		}

		void
		clear( void )
		{
			while (m_element_number > 0)
			{
				m_allocator.destroy(&(*this)[m_element_number - 1]);
				m_element_number--;
			}
		}

		// _ALLOCATOR_
		allocator_type
		get_allocator( void ) const
		{ return (m_allocator); };
	};

	template <class T, class Alloc>
		void
		swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
		{ x.swap(y); }

	template <class T, class Alloc>
		bool
		operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			for (size_t i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i])
					return (false);
			return (true);
		}

	template <class T, class Alloc>
		bool
		operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (!(lhs == rhs)); }
	
	template <class T, class Alloc>
		bool
		operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
	
	template <class T, class Alloc>
		bool
		operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (!ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }
	
	template <class T, class Alloc>
		bool
		operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); }

	template <class T, class Alloc>
		bool
		operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
		{ return (!ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
}

#endif