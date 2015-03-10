// Copyright © 2012-2014 Lénaïc Bagnères, hnc@singularity.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef HNC_VECTOR2D_HPP
#define HNC_VECTOR2D_HPP

#include <vector>

#include "index2D.hpp"
#include "assert.hpp"
#include "to_string.hpp"
#include "iterator.hpp"
#include "serialization.hpp"


namespace hnc
{
	/**
	 * @brief 2D container (use like std::vector<std::vector<T>>, a matrix) implemented with a std::vector<T> with 2D access
	 *
	 * @code
	   #include <hnc/vector2D.hpp>
	   @endcode
	 *
	 * @note For other use, have a look to:
	 * - hnc::vector2D_minimal
	 * - hnc::vector2D_C_style_minimal
	 */
	template <class T>
	class vector2D
	{
	public:

		/**
		 * @brief Proxy class for a line of const hnc::vector2D
		 * 
		 * @code
		   #include <hnc/vector2D.hpp>
		   @endcode
		 */
		template <class U>
		class line_const_ptr
		{
		private:

			/// Associated vector2D
			hnc::vector2D<U> const * p_data;

			/// Row index
			std::size_t m_i;

		public:

			/// Const iterator
			using const_iterator = hnc::const_iterator<U, line_const_ptr<U>>;

			/// Const reverse iterator
			using const_reverse_iterator = hnc::const_reverse_iterator<U, line_const_ptr<U>>;

			/// @brief Constructor
			/// @param[in] p A hnc::vector2D
			/// @param[in] i Row index
			line_const_ptr(hnc::vector2D<U> const * p = nullptr, std::size_t const i = 0) : p_data(p), m_i(i)
			{ }

			/// @brief Return the number of columns
			/// @return the number of columns
			std::size_t size() const
			{
				return p_data->nb_col();
			}

			/// @brief Const access by [i][j]
			/// @param j Column index
			/// @return the value at [i][j]
			U const & operator[](std::size_t const j) const
			{
				return (*p_data)(m_i, j);
			}
			
			/// @brief Const access to the first value of the line
			/// @pre Line has at least one value
			/// @return a proxy to have the first value of the line
			U const & front() const
			{
				return (*p_data)(m_i, 0);
			}

			/// @brief Const access to the last value of the line
			/// @pre Line has at least one value
			/// @return a proxy to have the last value of the line
			U const & back() const
			{
				return (*p_data)(m_i, p_data->nb_col() - 1);
			}
			
			/// @brief Return a const iterator to the beginning
			/// @return a const iterator to the beginning
			const_iterator begin() const
			{
				return const_iterator(*this, 0);
			}

			/// @brief Return a const iterator to the end
			/// @return a const iterator to the end
			const_iterator end() const
			{
				return const_iterator(*this, size());
			}

			/// @brief Return a const iterator to the beginning
			/// @return a const iterator to the beginning
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(*this, size() - 1);
			}

			/// @brief Return a const iterator to the end
			/// @return a const iterator to the end
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(*this, 0);
			}
		};

		/**
		 * @brief Proxy class for a line of hnc::vector2D
		 * 
		 * @code
		   #include <hnc/vector2D.hpp>
		   @endcode
		 */
		template <class U>
		class line_ptr
		{
		private:

			/// Associated vector2D
			hnc::vector2D<U> * p_data;

			/// Row index
			std::size_t m_i;

		public:

			/// Iterator
			using iterator = hnc::iterator<U, line_ptr<U>>;

			/// Const iterator
			using const_iterator = hnc::const_iterator<U, line_ptr<U>>;

			/// Reverse iterator
			using reverse_iterator = hnc::reverse_iterator<U, line_ptr<U>>;

			/// Const reverse iterator
			using const_reverse_iterator = hnc::const_reverse_iterator<U, line_ptr<U>>;

			/// @brief Constructor
			/// @param[in,out] p A hnc::vector2D
			/// @param[in]     i Row index
			line_ptr(hnc::vector2D<U> * p = nullptr, std::size_t const i = 0) : p_data(p), m_i(i)
			{ }

			/// @brief Return the number of columns
			/// @return the number of columns
			std::size_t size() const
			{
				return p_data->nb_col();
			}

			/// @brief Const access by [i][j]
			/// @param j Column index
			/// @return the value at [i][j]
			U const & operator[](std::size_t const j) const
			{
				return (*p_data)(m_i, j);
			}

			/// @brief Acces by [i][j]
			/// @param j Column index
			/// @return the value at [i][j]
			U & operator[](std::size_t const j)
			{
				return (*p_data)(m_i, j);
			}

			/// @brief Const access to the first value of the line
			/// @pre Line has at least one value
			/// @return a proxy to have the first value of the line
			U const & front() const
			{
				return (*p_data)(m_i, 0);
			}
			
			/// @brief Access to the first value of the line
			/// @pre Line has at least one value
			/// @return a proxy to have the first value of the line
			U & front()
			{
				return (*p_data)(m_i, 0);
			}

			/// @brief Const access to the last value of the line
			/// @pre Line has at least one value
			/// @return a proxy to have the last value of the line
			U const & back() const
			{
				return (*p_data)(m_i, p_data->nb_col() - 1);
			}
			
			/// @brief Const access to the last value of the line
			/// @pre Line has at least one value
			/// @return a proxy to have the last value of the line
			U & back()
			{
				return (*p_data)(m_i, p_data->nb_col() - 1);
			}

			/// @brief Return a iterator to the beginning
			/// @return a iterator to the beginning
			iterator begin()
			{
				return iterator(*this, 0);
			}

			/// @brief Return a iterator to the end
			/// @return a iterator the to end
			iterator end()
			{
				return iterator(*this, size());
			}

			/// @brief Return a const iterator to the beginning
			/// @return a const iterator to the beginning
			const_iterator begin() const
			{
				return const_iterator(*this, 0);
			}

			/// @brief Return a const iterator to the end
			/// @return a const iterator to the end
			const_iterator end() const
			{
				return const_iterator(*this, size());
			}

			/// @brief Return a reverse iterator to the beginning
			/// @return a reverse iterator to the beginning
			reverse_iterator rbegin()
			{
				return reverse_iterator(*this, size() - 1);
			}

			/// @brief Return a reverse iterator to the end
			/// @return a reverse iterator the to end
			reverse_iterator rend()
			{
				return reverse_iterator(*this, 0);
			}

			/// @brief Return a const reverse iterator to the beginning
			/// @return a const reverse iterator to the beginning
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(*this, size() - 1);
			}

			/// @brief Return a const reverse iterator to the end
			/// @return a const reverse iterator to the end
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(*this, 0);
			}
		};

		/// Iterator
		using iterator = hnc::iterator<line_ptr<T>, std::vector<line_ptr<T>>>;

		/// Const iterator
		using const_iterator = hnc::const_iterator<line_const_ptr<T>, std::vector<line_const_ptr<T>>>;

		/// Reverse iterator
		using reverse_iterator = hnc::reverse_iterator<line_ptr<T>, std::vector<line_ptr<T>>>;

		/// Const reverse iterator
		using const_reverse_iterator = hnc::const_reverse_iterator<line_const_ptr<T>, std::vector<line_const_ptr<T>>>;

	private:

		/// Data
		std::vector<T> m_data;

		/// Number of rows
		std::size_t m_nb_row;

		/// Number of columns
		std::size_t m_nb_col;

		/// Const lignes
		std::vector<line_const_ptr<T>> m_lines_const_ptr;

		/// Lignes
		std::vector<line_ptr<T>> m_lines_ptr;

	public:

		/// @brief Constructor
		/// @param[in] nb_row        Number of rows
		/// @param[in] nb_col        Number of columns
		/// @param[in] default_value Default value (T() by default)
		vector2D(std::size_t const nb_row = 0, std::size_t const nb_col = 0, T const & default_value = T()) :
			m_data(nb_row * nb_col, default_value),
			m_nb_row(nb_row),
			m_nb_col(nb_col)
		{
			update_lines_ptr();
		}

		/// @brief Constructor by copy
		/// @param[in] v2D A vector2D
		vector2D(vector2D<T> const & v2D) :
			m_data(v2D.m_data),
			m_nb_row(v2D.nb_row()),
			m_nb_col(v2D.nb_col())
		{
			update_lines_ptr();
		}

		/// @brief Constructor by RValues reference
		/// @param[in] v2D A vector2D (will be destroyed)
		vector2D(vector2D<T> && v2D) :
			m_data(v2D.m_data), m_nb_row(v2D.m_nb_row), m_nb_col(v2D.m_nb_col)
		{
			v2D.m_nb_col = 0;
			v2D.m_nb_row = 0;
			update_lines_ptr();
		}

		/**
		 * @brief Constructor with a vector of vector
		 *
		 * @param[in] values a std::vector of std::vector of T
		 *
		 * @warning The number of column is the size of the first vector @n
		 * If another size is smaller we use T() for initialisation
		 */
		vector2D(std::vector<std::vector<T>> const & values)
			: vector2D(values.size(), (values.size() >= 1) ? values[0].size() : 0)
		{
			// Copy the values
			for (std::size_t row = 0; row < m_nb_row; ++row)
			{
				for (std::size_t col = 0; col < std::min(m_nb_col, values[row].size()); ++col)
				{
					(*this)(row, col) = values[row][col];
				}
			}
		}

		/**
		 * @brief Constructor with initializer list os initializer list
		 *
		 * @param[in] values Values in { {10, 11, 12}, {20, 21, 22} }
		 *
		 * @warning The number of column is the size of the first initializer_list @n
		 * If another size is smaller we use T() for initialisation
		 */
		vector2D(std::initializer_list<std::initializer_list<T>> const & values)
			: vector2D(values.size(), (values.size() >= 1) ? values.begin()->size() : 0)
		{
			// Copy the values
			std::size_t row = 0;
			for (std::initializer_list<T> const & rows : values)
			{
				std::size_t col = 0;
				for (T const & e : rows)
				{
					(*this)(row, col) = e;
					++col;
				}
				++row;
			}
		}

		/// @brief Return the number of rows
		/// @return the number of rows
		std::size_t nb_row() const { return m_nb_row; }
		
		/// @brief Return the number of rows
		/// @return the number of rows
		std::size_t size() const { return nb_row(); }


		/// @brief Return the number of columns
		/// @return the number of columns
		std::size_t nb_col() const { return m_nb_col; }

		/// @brief Move assignment operator between two vector2D
		/// @param[in] v2D A vector2D
		vector2D<T> operator =(vector2D<T> && v2D)
		{
			// If it is a different vector2D
			if (this != &v2D)
			{
				// Move
				m_data = std::move(v2D.m_data);
				m_nb_row = v2D.m_nb_row;
				m_nb_col = v2D.m_nb_col;
				update_lines_ptr();
				// Remove original object
				v2D.m_nb_col = 0;
				v2D.m_nb_row = 0;
			}
			// Return
			return *this;
		}

		/// @brief Affectation operator between two vector2D
		/// @param[in] v2D A vector2D
		vector2D<T> operator =(vector2D<T> const & v2D)
		{
			// If it is a different vector2D
			if (this != &v2D)
			{
				m_data = v2D.m_data;
				m_nb_row = v2D.nb_row();
				m_nb_col = v2D.nb_col();
				update_lines_ptr();
			}
			// Return
			return *this;
		}
		
		hnc_generate_serialize_member_function(m_data, m_nb_row, m_nb_col)
		
		/// @brief After load serialization
		void after_load_serialization() { update_lines_ptr(); }

		// operator () acces

		/// @brief Const access by fonctor
		/// @param i Row index
		/// @param j Column index
		/// @return the value at (i, j)
		T const & operator()(std::size_t const i, std::size_t const j) const
		{
			return m_data[index2D::index1D(i, j, m_nb_col)];
		}
		
		/// @brief Acces by fonctor
		/// @param i Row index
		/// @param j Column index
		/// @return the value at (i, j)
		T & operator()(std::size_t const i, std::size_t const j)
		{
			return m_data[index2D::index1D(i, j, m_nb_col)];
		}

		// .at acces

		/// @brief Safe const acces
		/// @param i Row index
		/// @param j Column index
		/// @exception std::out_of_range if out of range access (check by std::vector)
		/// @return the value at .at(i, j)
		T const & at(std::size_t const i, std::size_t const j) const
		{
			return m_data.at(index2D::index1D(i, j, m_nb_col));
		}
		
		/// @brief Safe acces
		/// @param i Row index
		/// @param j Column index
		/// @exception std::out_of_range if out of range access (check by std::vector)
		/// @return the value at .at(i, j)
		T & at(std::size_t const i, std::size_t const j)
		{
			return m_data.at(index2D::index1D(i, j, m_nb_col));
		}

		// operator [] access

		/// @brief Const access by [i][j]
		/// @param i Row index
		/// @return a proxy to have [j]
		hnc::vector2D<T>::line_const_ptr<T> const & operator[](std::size_t const i) const
		{
			return m_lines_const_ptr[i];
		}
		
		/// @brief Acces by [i][j]
		/// @param i Row index
		/// @return a proxy to have [j]
		hnc::vector2D<T>::line_ptr<T> & operator[](std::size_t const i)
		{
			return m_lines_ptr[i];
		}
		
		// front, back

		/// @brief Const access to the first line
		/// @pre vector2D has at least one line
		/// @return a proxy to have the first line
		hnc::vector2D<T>::line_const_ptr<T> const & front() const
		{
			return m_lines_const_ptr[0];
		}
		
		/// @brief Access to the first line
		/// @pre vector2D has at least one line
		/// @return a proxy to have the first line
		hnc::vector2D<T>::line_ptr<T> & front()
		{
			return m_lines_ptr[0];
		}

		/// @brief Const access to the last line
		/// @pre vector2D has at least one line
		/// @return a proxy to have the last line
		hnc::vector2D<T>::line_const_ptr<T> const & back() const
		{
			return m_lines_const_ptr[m_nb_row - 1];
		}
		
		/// @brief Access to the last line
		/// @pre vector2D has at least one line
		/// @return a proxy to have the last line
		hnc::vector2D<T>::line_ptr<T> & back()
		{
			return m_lines_ptr[m_nb_row - 1];
		}
		
		// Iterator

		/// @brief Return a iterator to the beginning
		/// @return a iterator to the beginning
		iterator begin()
		{
			return iterator(m_lines_ptr, 0);
		}

		/// @brief Return a iterator to the end
		/// @return a iterator to the end
		iterator end()
		{
			return iterator(m_lines_ptr, nb_row());
		}
		
		/// @brief Return a const iterator to the beginning
		/// @return a const iterator to the beginning
		const_iterator begin() const
		{
			return const_iterator(m_lines_const_ptr, 0);
		}

		/// @brief Return a const iterator to the end
		/// @return a const iterator to the end
		const_iterator end() const
		{
			return const_iterator(m_lines_const_ptr, nb_row());
		}
		
		/// @brief Return a const iterator to the beginning
		/// @return a const iterator to the beginning
		const_iterator cbegin() const
		{
			return const_iterator(m_lines_const_ptr, 0);
		}

		/// @brief Return a const iterator to the end
		/// @return a const iterator to the end
		const_iterator cend() const
		{
			return const_iterator(m_lines_const_ptr, nb_row());
		}
		
		// Reverse iterator

		/// @brief Return a reverse iterator to the beginning
		/// @return a reverse iterator to the beginning
		reverse_iterator rbegin()
		{
			return reverse_iterator(m_lines_ptr, nb_row() - 1);
		}

		/// @brief Return a reverse iterator to the end
		/// @return a reverse iterator to the end
		reverse_iterator rend()
		{
			return reverse_iterator(m_lines_ptr, 0);
		}

		/// @brief Return a const reverse iterator to the beginning
		/// @return a const reverse iterator to the beginning
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(m_lines_const_ptr, nb_row() - 1);
		}

		/// @brief Return a const reverse iterator to the end
		/// @return a const reverse iterator to the end
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(m_lines_const_ptr, 0);
		}

		/// @brief Return a const reverse iterator to the beginning
		/// @return a const reverse iterator to the beginning
		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(m_lines_const_ptr, nb_row() - 1);
		}

		/// @brief Return a const reverse iterator to the end
		/// @return a const reverse iterator to the end
		const_reverse_iterator crend() const
		{
			return const_reverse_iterator(m_lines_const_ptr, 0);
		}

		// Operator
		
		/// @brief Equality operator
		/// @param[in] v A hnc::vector2D<T> for the comparaison
		/// @return true if hnc::vector2D<T> are equals, false otherwise
		bool operator ==(hnc::vector2D<T> const & v) const
		{
			// Different size
			if (this->nb_row() != v.nb_row() || this->nb_col() != v.nb_col())
			{
				return false;
			}
			else
			{
				return (m_data == v.m_data);
			}
		}

		/// @brief Inequality operator
		/// @param[in] v A hnc::vector2D<T> for the comparaison
		/// @return true if hnc::vector2D<T> are not equals, false otherwise
		bool operator !=(hnc::vector2D<T> const & v) const
		{
			return ! (*this == v);
		}

		// Add / remove
		
		/// @brief Add a row before
		/// @param[in] i             Row is inserted before this one
		/// @param[in] default_value Default value
		/// @exception std::out_of_range hnc::hassert i <= number of rows if NDEBUG is not defined
		void add_row_before(std::size_t const i, T const & default_value = T())
		{
			// Check i
			#ifndef NDEBUG
				hnc::hassert(i <= m_nb_row, std::out_of_range("hnc::vector2D::add_row_before could not insert before row " + hnc::to_string(i) + ", number of rows = " + hnc::to_string(m_nb_row)));
			#endif
			// New vector2D
			hnc::vector2D<T> new_vector2D(m_nb_row + 1, m_nb_col);
			// Copy rows before new row
			for (std::size_t row = 0; row < i; ++row)
			{
				for (std::size_t col = 0; col < m_nb_col; ++col)
				{ new_vector2D(row, col) = (*this)(row, col); }
			}
			// Insert line
			for (std::size_t col = 0; col < new_vector2D.nb_col(); ++col)
			{ new_vector2D(i, col) = default_value; }
			// Copy rows after new row
			for (std::size_t row = i; row < m_nb_row; ++row)
			{
				for (std::size_t col = 0; col < m_nb_col; ++col)
				{ new_vector2D(row + 1, col) = (*this)(row, col); }
			}
			// Copy
			*this = std::move(new_vector2D);
		}
		
		/// @brief Add a row after
		/// @param[in] i             Row is inserted after this one
		/// @param[in] default_value Default value
		void add_row_after(std::size_t const i, T const & default_value = T())
		{ add_row_before(i + 1, default_value); }

		/// @brief Add a column before
		/// @param[in] j             Column is inserted before this one
		/// @param[in] default_value Default value
		/// @exception std::out_of_range hnc::hassert j <= number of columns if NDEBUG is not defined
		void add_col_before(std::size_t const j, T const & default_value = T())
		{
			// Check j
			#ifndef NDEBUG
				hnc::hassert(j <= m_nb_col, std::out_of_range("hnc::vector2D::add_col_before could not insert before column " + hnc::to_string(j) + ", number of columns = " + hnc::to_string(m_nb_col)));
			#endif
			// New vector2D
			hnc::vector2D<T> new_vector2D(m_nb_row, m_nb_col + 1);
			// Copy rows before new row
			for (std::size_t row = 0; row < m_nb_row; ++row)
			{
				// Copy all col before new col
				for (std::size_t col = 0; col < j; ++col)
				{ new_vector2D(row, col) = (*this)(row, col); }
				// Insert value
				new_vector2D(row, j) = default_value;
				// Copy all col after new col
				for (std::size_t col = j; col < m_nb_col; ++col)
				{ new_vector2D(row, col + 1) = (*this)(row, col); }
			}
			// Copy
			*this = std::move(new_vector2D);
		}
		
		/// @brief Add a column after
		/// @param[in] j             Column is inserted after this one
		/// @param[in] default_value Default value
		void add_col_after(std::size_t const j, T const & default_value = T())
		{ add_col_before(j + 1, default_value); }

		// Remove a line/column

		/// @brief Remove a line
		/// @param[in] i Row removed
		/// @exception std::out_of_range hnc::hassert i <= number of rows if NDEBUG is not defined
		void remove_line(std::size_t const i)
		{
			// Check i
			#ifndef NDEBUG
				hnc::hassert(i < m_nb_row, std::out_of_range("hnc::vector2D::remove_line could not remove the line " + hnc::to_string(i) + ", number of rows = " + hnc::to_string(m_nb_row)));
			#endif
			// New vector2D
			hnc::vector2D<T> new_vector2D(m_nb_row - 1, m_nb_col);
			// Copy lines before i
			for (std::size_t row = 0; row < i; ++row)
			{
				for (std::size_t col = 0; col < m_nb_col; ++col)
				{ new_vector2D(row, col) = (*this)(row, col); }
			}
			// Copy lines after i
			for (std::size_t row = i + 1; row < m_nb_row; ++row)
			{
				for (std::size_t col = 0; col < m_nb_col; ++col)
				{ new_vector2D(row - 1, col) = (*this)(row, col); }
			}
			// Copy
			*this = std::move(new_vector2D);
		}

		/// @brief Remove a column
		/// @param[in] j Column removed
		/// @exception std::out_of_range hnc::hassert j <= number of columns if NDEBUG is not defined
		void remove_column(std::size_t const j)
		{
			// Check i
			#ifndef NDEBUG
				hnc::hassert(j < m_nb_col, std::out_of_range("hnc::vector2D::remove_column could not remove the column " + hnc::to_string(j) + ", number of columns = " + hnc::to_string(m_nb_col)));
			#endif
			// New vector2D
			hnc::vector2D<T> new_vector2D(m_nb_row, m_nb_col - 1);
			// Copy lines
			for (std::size_t row = 0; row < m_nb_row; ++row)
			{
				// Copy columns bejore j
				for (std::size_t col = 0; col < j; ++col)
				{
					new_vector2D(row, col) = (*this)(row, col);
				}
				// Copy columns after j
				for (std::size_t col = j + 1; col < m_nb_col; ++col)
				{
					new_vector2D(row, col - 1) = (*this)(row, col);
				}
			}
			// Copy
			*this = std::move(new_vector2D);
		}

	private:

		#ifndef NDEBUG
			/**
			 * @brief Check if acces is out of range with hnc::hassert if NDEBUG is not defined
			 *
			 * (Empty function if NDEBUG)
			 *
			 * @param i Row index
			 * @param j Column index
			 *
			 * @exception std::out_of_range hnc::hassert i < number of rows and j < number of columns if NDEBUG is not defined
			 */
			void check_range_assert(std::size_t const i, std::size_t const j) const
			{
					hnc::hassert(i < m_nb_row, std::out_of_range("hnc::vector2D, id row = " + hnc::to_string(i) + ", number of rows = " + hnc::to_string(m_nb_row)));
					hnc::hassert(j < m_nb_col, std::out_of_range("hnc::vector2D, id column = " + hnc::to_string(j) + ", number of columns = " + hnc::to_string(m_nb_col)));
			}
		#else
			void check_range_assert(std::size_t const /*i*/, std::size_t const /*j*/) const { }
		#endif

		/// @brief Check if acces is out of range
		/// @param i Row index
		/// @param j Column index
		void check_range(std::size_t const i, std::size_t const j) const
		{
			if (i >= m_nb_row)
			{
				throw std::out_of_range("hnc::vector2D, id row = " + hnc::to_string(i) + ", number of rows = " + hnc::to_string(m_nb_row));
			}
			if (j >= m_nb_col)
			{
				throw std::out_of_range("hnc::vector2D, id column = " + hnc::to_string(j) + ", number of columns = " + hnc::to_string(m_nb_col));
			}
		}

		/// @brief Udapte lines const and lines after each modifications of the vector2D (constructors, operator =, add/remove line/column)
		void update_lines_ptr()
		{
			m_lines_const_ptr.resize(nb_row());
			m_lines_ptr.resize(nb_row());
			for (std::size_t row = 0; row < m_nb_row; ++row)
			{
				m_lines_const_ptr[row] = line_const_ptr<T>(this, row);
				m_lines_ptr[row] = line_ptr<T>(this, row);
			}
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::vector2D<T>
	/// @param[in,out] o Output stream
	/// @param[in]     v A hnc::vector2D<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::vector2D<T> const & v)
	{
		// Display data
		for (std::size_t row = 0; row < v.nb_row(); ++row)
		{
			o << ((row == 0) ? ("{") : (" "));
			o << " {";
			// Display data
			for (std::size_t col = 0; col < v.nb_col(); ++col)
			{
				if (col != 0) { o << ", "; }
				o << v[row][col];
			}
			o << ((row == v.nb_row() - 1) ? ("} }") : ("},\n"));
		}

		return o;
	}
}

#endif
