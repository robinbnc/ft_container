#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "iterator_base.hpp"

namespace ft
{
	template <typename T>
		class vector_iterator: public ft::iterator<std::random_access_iterator_tag, T>
		{
			protected:
				T	*m_it;

			public:
				typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
				typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
				typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
				typedef T*																				pointer;
				typedef T&																				reference;
				
				vector_iterator( void )
				: m_it(0)
				{}

				vector_iterator( pointer it )
				: m_it(it)
				{}

				vector_iterator( const vector_iterator& vector_it )
				: m_it(vector_it.m_it)
				{}

				virtual
				~vector_iterator() {}

				vector_iterator
				&operator=(const vector_iterator& vector_it)
				{
					if (this == &vector_it)
						return (*this);
					this->m_it = vector_it.m_it;
					return (*this);
				}

				reference
				operator*() const
				{ return (*m_it); }

				pointer
				operator->() const
				{ return (m_it); }

				vector_iterator&
				operator++()
				{
					++m_it;
					return (*this);
				}

				vector_iterator
				operator++(int)
				{ return (vector_iterator(m_it++)); }

				vector_iterator&
				operator--()
				{
					--m_it;
					return (*this);
				}

				vector_iterator
				operator--(int)
				{ return (vector_iterator(m_it--)); }

				reference
				operator[](const difference_type n) const
				{ return (m_it[n]); }

				vector_iterator&
				operator+=(const difference_type n)
				{
					m_it += n;
					return (*this);
				}

				vector_iterator
				operator+(difference_type n) const
				{ return (vector_iterator(m_it + n)); }

				vector_iterator&
				operator-=(const difference_type n)
				{
					m_it -= n;
					return (*this);
				}

				vector_iterator
				operator-(const difference_type n) const
				{ return (vector_iterator(m_it - n)); }

				const pointer&
				base() const
				{ return (this->m_it); }

				operator vector_iterator<const T> () const
				{ return (vector_iterator<const T>(this->m_it)); }
		};
	
	// Note: In what follows, the left- and right-hand-side iterators are
	// allowed to vary in types (conceptually in cv-qualification) so that
	// comparison between cv-qualified and non-cv-qualified iterators be
	// valid.
	
	template<typename IteratorL, typename IteratorR>
    inline bool
    operator==(const vector_iterator<IteratorL>& lhs,
           const vector_iterator<IteratorR>& rhs)
    { return (lhs.base() == rhs.base()); }

	template<typename iterator>
    inline bool
    operator==(const vector_iterator<iterator>& lhs,
           const vector_iterator<iterator>& rhs)
    { return (lhs.base() == rhs.base()); }

	template<typename IteratorL, typename IteratorR>
    inline bool
    operator!=(const vector_iterator<IteratorL>& lhs,
           const vector_iterator<IteratorR>& rhs)
    { return (lhs.base() != rhs.base()); }

	template<typename iterator>
    inline bool
    operator!=(const vector_iterator<iterator>& lhs,
           const vector_iterator<iterator>& rhs)
    { return (lhs.base() != rhs.base()); }

	template<typename IteratorL, typename IteratorR>
    inline bool
    operator<(const vector_iterator<IteratorL>& lhs,
           const vector_iterator<IteratorR>& rhs)
    { return (lhs.base() < rhs.base()); }

	template<typename iterator>
    inline bool
    operator<(const vector_iterator<iterator>& lhs,
           const vector_iterator<iterator>& rhs)
    { return (lhs.base() < rhs.base()); }

	template<typename IteratorL, typename IteratorR>
    inline bool
    operator>(const vector_iterator<IteratorL>& lhs,
           const vector_iterator<IteratorR>& rhs)
    { return (lhs.base() > rhs.base()); }

	template<typename iterator>
    inline bool
    operator>(const vector_iterator<iterator>& lhs,
           const vector_iterator<iterator>& rhs)
    { return (lhs.base() > rhs.base()); }

	template<typename IteratorL, typename IteratorR>
    inline bool
    operator<=(const vector_iterator<IteratorL>& lhs,
           const vector_iterator<IteratorR>& rhs)
    { return (lhs.base() <= rhs.base()); }

	template<typename iterator>
    inline bool
    operator<=(const vector_iterator<iterator>& lhs,
           const vector_iterator<iterator>& rhs)
    { return (lhs.base() <= rhs.base()); }

	template<typename IteratorL, typename IteratorR>
    inline bool
    operator>=(const vector_iterator<IteratorL>& lhs,
           const vector_iterator<IteratorR>& rhs)
    { return (lhs.base() >= rhs.base()); }

	template<typename iterator>
    inline bool
    operator>=(const vector_iterator<iterator>& lhs,
           const vector_iterator<iterator>& rhs)
    { return (lhs.base() >= rhs.base()); }

    template<typename T>
    ft::vector_iterator<T>
	operator+(typename ft::vector_iterator<T>::difference_type n,
        	typename ft::vector_iterator<T>& rai)
	{ return (rai + n); }

    template <typename T>
    typename ft::vector_iterator<T>::difference_type
    operator-(const ft::vector_iterator<T> lhs,
              const ft::vector_iterator<T> rhs)
    { return (lhs.base() - rhs.base()); }

    template<typename T_L, typename T_R>
    typename ft::vector_iterator<T_L>::difference_type
    operator-(const ft::vector_iterator<T_L> lhs,
              const ft::vector_iterator<T_R> rhs)
    { return (lhs.base() - rhs.base()); }
}

#endif
