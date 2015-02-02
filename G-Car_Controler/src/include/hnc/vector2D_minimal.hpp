// Copyright © 2013, 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

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


#ifndef HNC_VECTOR2D_C_MINIMAL_HPP
#define HNC_VECTOR2D_C_MINIMAL_HPP

#include <vector>

#include "index2D.hpp"


namespace hnc
{
	/**
	 * @brief Minimal encapsulation of std::vector<T> with 2D access
	 *
	 * @code
	   #include <hnc/vector2D_minimal.hpp>
	   @endcode
	 *
	 * @note For other use, have a look to:
	 * - hnc::vector2D
	 * - hnc::vector2D_C_style
	 * - hnc::vector2D_C_style_minimal
	 */
	template <class T>
	class vector2D_minimal
	{
	public:

		/**
		 * @brief Proxy class for a line of const hnc::vector2D_minimal
		 * 
		 * @code
		   #include <hnc/vector2D_minimal.hpp>
		   @endcode
		 */
		template <class U>
		class line_const
		{
		private:

			/// Associated vector2D_minimal
			hnc::vector2D_minimal<U> const & m_data;

			/// Row index
			std::size_t const m_i;

		public:

			/// @brief Constructor
			/// @param[in,out] c A hnc::vector2D_minimal
			/// @param[in]     i Row index
			line_const(hnc::vector2D_minimal<U> const & c, std::size_t const i) : m_data(c), m_i(i)
			{ }

			/// @brief Const access by [i][j]
			/// @param j Column index
			/// @return the value at [i][j]
			U const & operator[](std::size_t const j) const
			{
				return m_data(m_i, j);
			}
		};
		
		/**
		 * @brief Proxy class for a line of hnc::vector2D_minimal
		 * 
		 * @code
		   #include <hnc/vector2D_minimal.hpp>
		   @endcode
		 */
		template <class U>
		class line
		{
		private:

			/// Associated vector2D_minimal
			hnc::vector2D_minimal<U> & m_data;

			/// Row index
			std::size_t const m_i;

		public:

			/// @brief Constructor
			/// @param[in,out] c A hnc::vector2D_minimal
			/// @param[in]     i Row index
			line(hnc::vector2D_minimal<U> & c, std::size_t const i) : m_data(c), m_i(i)
			{ }
			
			/// @brief Const access by [i][j]
			/// @param j Column index
			/// @return the value at [i][j]
			U const & operator[](std::size_t const j) const
			{
				return m_data(m_i, j);
			}
			
			/// @brief Acces by [i][j]
			/// @param j Column index
			/// @return the value at [i][j]
			U & operator[](std::size_t const j)
			{
				return m_data(m_i, j);
			}
		};
		
	private:

		/// vector<T> data
		std::vector<T> m_data;

		/// Number of rows
		std::size_t m_nb_row;

		/// Number of columns
		std::size_t m_nb_col;

	public:

		/// @brief Constructor
		/// @param[in] nb_row        Number of rows
		/// @param[in] nb_col        Number of columns
		/// @param[in] default_value Default value (T() by default)
		vector2D_minimal(std::size_t const nb_row = 0, std::size_t const nb_col = 0, T const & default_value = T()) :
			m_data(nb_row * nb_col, default_value),
			m_nb_row(nb_row),
			m_nb_col(nb_col)
		{ }

		/// @brief Constructor by copy
		/// @param[in] v2D A vector2D
		vector2D_minimal(vector2D_minimal<T> const & v2D) :
			m_data(v2D.m_data),
			m_nb_row(v2D.nb_row()),
			m_nb_col(v2D.nb_col())
		{ }

		/// @brief Constructor by RValues reference
		/// @param[in] v2D A vector2D (will be destroyed)
		vector2D_minimal(vector2D_minimal<T> && v2D) :
			m_data(v2D.m_data), m_nb_row(v2D.m_nb_row), m_nb_col(v2D.m_nb_col)
		{
			v2D.m_nb_col = 0;
			v2D.m_nb_row = 0;
		}

		/// @brief Return the number of rows
		/// @return the number of rows
		std::size_t nb_row() const { return m_nb_row; }


		/// @brief Return the number of columns
		/// @return the number of columns
		std::size_t nb_col() const { return m_nb_col; }

		/// @brief Move assignment operator between two vector2D 
		/// @param[in] v2D A vector2D
		vector2D_minimal<T> operator =(vector2D_minimal<T> && v2D)
		{
			// If it is a different vector2D
			if (this != &v2D)
			{
				// Move
				m_data = std::move(v2D.m_data);
				m_nb_row = v2D.m_nb_row;
				m_nb_col = v2D.m_nb_col;
				// Remove original object
				v2D.m_nb_col = 0;
				v2D.m_nb_row = 0;
			}
			// Return
			return *this;
		}

		/// @brief Affectation operator between two vector2D
		/// @param[in] v2D A vector2D
		vector2D_minimal<T> operator =(vector2D_minimal<T> const & v2D)
		{
			// If it is a different vector2D
			if (this != &v2D)
			{
				m_data = v2D.m_data;
				m_nb_row = v2D.nb_row();
				m_nb_col = v2D.nb_col();
			}
			// Return
			return *this;
		}

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
		hnc::vector2D_minimal<T>::line_const<T> operator[](std::size_t const i) const
		{
			return hnc::vector2D_minimal<T>::line_const<T>(*this, i);
		}
		
		/// @brief Acces by [i][j]
		/// @param i Row index
		/// @return a proxy to have [j]
		hnc::vector2D_minimal<T>::line<T> operator[](std::size_t const i)
		{
			return hnc::vector2D_minimal<T>::line<T>(*this, i);
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::vector2D_C_style_minimal<T>
	/// @param[in,out] o Output stream
	/// @param[in]     v A hnc::vector2D_C_style_minimal<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::vector2D_minimal<T> const & v)
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

		// Return stream
		return o;
	}
}

#endif
