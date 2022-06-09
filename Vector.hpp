#ifndef VECTOR
# define VECTOR

#include <memory>
#include <limits>

namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class vector
	{
		private:
			Allocator					m_allocator;
			std::size_t					m_element_number;
			std::size_t					m_alloc_size;
			T							*m_ptr;

		public:
			typedef typename Allocator::reference 		reference;
			typedef typename Allocator::const_reference	const_reference;
			typedef typename Allocator::pointer 		pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;			
			typedef T 									value_type;
			typedef Allocator 							allocator_type;
		

		/*
		**		__CONSTRUCTOR__
		*/

		vector(const Allocator& allocator = Allocator())
		: m_allocator(allocator), m_element_number(0), m_alloc_size(0), m_ptr(NULL) {}
		
		explicit vector(size_type n, const value_type& value = value_type(),
			const allocator_type& allocator = allocator_type())
		: m_allocator(allocator), m_element_number(n), m_alloc_size(n), m_ptr(0)
		{
			m_ptr = m_allocator.allocate(n);
			for(size_type i = 0; i < n; i++)
				m_allocator.construct( m_ptr + i, value );
		}
			/*
			** A faire ?
			*/
				//template <class InputIterator>
				//vector(InputIterator first, InputIterator last, const Allocator& = Allocator());
		
		// vector(const vector<T,Allocator>& x); Faire quand operateur = sera fait


		/*
		**		__DESTRUCTOR__
		*/

		~vector()
		{
			if (m_ptr)
				m_allocator.deallocate(m_ptr, m_element_number);
		}
		/*
		**		__MEMBER FUNCTIONS__
		*/

		// _ITERATORS_

		// _CAPACITY_

		inline std::size_t	size( void ) const 		{return (m_element_number);}
		inline std::size_t	max_size( void ) const	{return (m_allocator.max_size());}
		//resize
		inline std::size_t	capacity( void ) const	{return (m_alloc_size);}
		inline bool			empty( void ) const		{return (m_element_number == 0 ? true : false);}
	};
}

#endif