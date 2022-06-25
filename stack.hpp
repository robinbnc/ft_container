#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef typename Container::value_type			value_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;
			typedef typename Container::size_type			size_type;
			typedef          Container						container_type;

		protected:
			Container c;

		public:

			explicit
			stack (const container_type& ctnr = container_type())
			: c(ctnr)
			{ }

			bool
			empty() const
			{ return (c.empty()); }

			size_type
			size() const
			{ return (c.size()); }

			value_type&
			top()
			{
				return (c.back());
			}

			const value_type&
			top() const
			{ return (c.back()); }

			void
			push (const value_type& val)
			{ c.push_back(val); }

			void
			pop()
			{ c.pop_back(); }

			template <class Tp, class Ctnr>
				friend bool
				operator== (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);

			template <class Tp, class Ctnr>
				friend bool
				operator!= (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);

			template <class Tp, class Ctnr>
				friend bool
				operator<  (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);

			template <class Tp, class Ctnr>
				friend bool
				operator<= (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);

			template <class Tp, class Ctnr>
				friend bool
				operator>  (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);

			template <class Tp, class Ctnr>
				friend bool
				operator>= (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);
	};

	template <class T, class Container>
	  bool
	  operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	  { return (lhs.c == rhs.c); }

	template <class T, class Container>
	  bool
	  operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	  { return !(lhs == rhs); }

	template <class T, class Container>
	  bool
	  operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	  { return (lhs.c < rhs.c); }

	template <class T, class Container>
	  bool
	  operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	  { return (lhs.c <= rhs.c); }

	template <class T, class Container>
	  bool
	  operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	  { return (lhs.c > rhs.c); }

	template <class T, class Container>
	  bool
	  operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	  { return (lhs.c >= rhs.c); }
}

#endif