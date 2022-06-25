#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <cstddef>
# include "iterator_base.hpp"

namespace ft
{
	template<class Iter>
	class reverse_iterator: public ft::iterator<
								std::random_access_iterator_tag,
								typename iterator_traits<Iter>::value_type>
	{
		private:
			Iter	m_current;
		public:
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer       		pointer;
			typedef typename ft::iterator_traits<Iter>::reference     		reference;

            reverse_iterator(void)
			: m_current()
			{}

			reverse_iterator(Iter it)
			: m_current(it)
			{}

			reverse_iterator(const reverse_iterator& vector_it)
			: m_current(vector_it.m_current)
			{}
			
			template<typename _Iter>
	        reverse_iterator(const reverse_iterator<_Iter>& x)
		    : m_current(x.base())
			{}

			virtual ~reverse_iterator() {}

			reverse_iterator
			&operator=(const reverse_iterator& vector_it)
			{
				if (this == &vector_it)
					return (*this);
				this->m_current = vector_it.m_current;
				return (*this);
			}

			const Iter
			base() const
			{ return (m_current); }

			reference
			operator*() const
			{
				Iter tmp = m_current;
				return (*--tmp);
			}

			pointer
			operator->() const
			{ return (&(operator*())); }

			reverse_iterator&
			operator++()
			{
				--m_current;
				return (*this);
			}

			reverse_iterator
			operator++(int)
			{ 
				reverse_iterator tmp = *this;
				--m_current;
				return (tmp);	
			}

			reverse_iterator&
			operator--()
			{
				++m_current;
				return (*this);
			}

			reverse_iterator
			operator--(int)
			{
				reverse_iterator tmp = *this;
				++m_current;
				return (tmp);
			}


			reverse_iterator&
			operator+=(const difference_type n)
			{
				m_current -= n;
				return (*this);
			}

			reverse_iterator
			operator+(difference_type n) const
			{ return (reverse_iterator(m_current - n)); }

			reverse_iterator&
			operator-=(const difference_type n)
			{
				m_current += n;
				return (*this);
			}

			reverse_iterator
			operator-(const difference_type n) const
			{ return (reverse_iterator(m_current + n)); }

			reference
			operator[](const difference_type n) const
			{ return (*(*this + n)); }
	};

	template<typename _Iterator>
		inline bool
		operator==(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{ return x.base() == y.base(); }

	template<typename _Iterator>
		inline bool
		operator<(const reverse_iterator<_Iterator>& x,
			const reverse_iterator<_Iterator>& y)
		{ return y.base() < x.base(); }

	template<typename _Iterator>
		inline bool
		operator!=(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{ return !(x == y); }

	template<typename _Iterator>
		inline bool
		operator>(const reverse_iterator<_Iterator>& x,
			const reverse_iterator<_Iterator>& y)
		{ return y < x; }

	template<typename _Iterator>
		inline bool
		operator<=(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{ return !(y < x); }

	template<typename _Iterator>
		inline bool
		operator>=(const reverse_iterator<_Iterator>& x,
				const reverse_iterator<_Iterator>& y)
		{ return !(x < y); }

	template<typename _Iterator>
		inline typename reverse_iterator<_Iterator>::difference_type
		operator-(const reverse_iterator<_Iterator>& x,
			const reverse_iterator<_Iterator>& y)
		{ return y.base() - x.base(); }

	template<typename _Iterator>
		inline reverse_iterator<_Iterator>
		operator+(typename reverse_iterator<_Iterator>::difference_type n,
			const reverse_iterator<_Iterator>& x)
		{ return reverse_iterator<_Iterator>(x.base() - n); }

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator==(const reverse_iterator<_IteratorL>& x,
				const reverse_iterator<_IteratorR>& y)
		{ return x.base() == y.base(); }

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator<(const reverse_iterator<_IteratorL>& x,
			const reverse_iterator<_IteratorR>& y)
		{ return y.base() < x.base(); }

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator!=(const reverse_iterator<_IteratorL>& x,
				const reverse_iterator<_IteratorR>& y)
		{ return !(x == y); }

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator>(const reverse_iterator<_IteratorL>& x,
			const reverse_iterator<_IteratorR>& y)
		{ return y < x; }

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator<=(const reverse_iterator<_IteratorL>& x,
				const reverse_iterator<_IteratorR>& y)
		{ return !(y < x); }

	template<typename _IteratorL, typename _IteratorR>
		inline bool
		operator>=(const reverse_iterator<_IteratorL>& x,
				const reverse_iterator<_IteratorR>& y)
		{ return !(x < y); }

	template<typename _IteratorL, typename _IteratorR>
    	inline typename reverse_iterator<_IteratorL>::difference_type
		operator-(const reverse_iterator<_IteratorL>& x,
				const reverse_iterator<_IteratorR>& y)
		{ return y.base() - x.base(); }
}

#endif
