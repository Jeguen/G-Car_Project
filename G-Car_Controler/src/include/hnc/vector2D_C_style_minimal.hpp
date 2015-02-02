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


#ifndef HNC_VECTOR2D_C_STYLE_MINIMAL_HPP
#define HNC_VECTOR2D_C_STYLE_MINIMAL_HPP


namespace hnc
{
	/**
	 * @brief Minimal encapsulation for a C style 2D array with dynamic allocation
	 *
	 * @code
	   #include <hnc/vector2D_C_style_minimal.hpp>
	   @endcode
	 *
	 * @note For other use, have a look to:
	 * - hnc::vector2D
	 * - hnc::vector2D_C_style
	 * - hnc::vector2D_minimal
	 */
	template <class T>
	class vector2D_C_style_minimal
	{
	private:

		/// T[][] data
		T * * p_data;

		/// Number of rows
		std::size_t m_nb_row;

		/// Number of columns
		std::size_t m_nb_col;

	public:

		/// @brief Constructor
		/// @param[in] nb_row        Number of rows
		/// @param[in] nb_col        Number of columns
		/// @param[in] default_value Default value (T() by default)
		vector2D_C_style_minimal(std::size_t const nb_row = 0, std::size_t const nb_col = 0, T const & default_value = T()) :
			p_data(nullptr),
			m_nb_row(nb_row),
			m_nb_col(nb_col)
		{
			p_data = new T *[m_nb_row];

			for (std::size_t i = 0; i < m_nb_row; ++i)
			{
				p_data[i] = new T[m_nb_col];
				
				for (std::size_t j = 0; j < m_nb_col; ++j)
				{
					p_data[i][j] = default_value;
				}
			}
		}

		/// @brief Copy constructor
		/// @param[in] v2D A vector2D
		vector2D_C_style_minimal(vector2D_C_style_minimal<T> const & v2D) :
			vector2D_C_style_minimal(v2D.nb_row(), v2D.nb_col())
		{
			for (std::size_t i = 0; i < m_nb_row; ++i)
			{
				for (std::size_t j = 0; j < m_nb_col; ++j)
				{
					p_data[i][j] = v2D[i][j];
				}
			}
		}

		/// @brief Constructor by RValues reference
		/// @param[in] v2D A vector2D (will be destroyed)
		vector2D_C_style_minimal(vector2D_C_style_minimal<T> && v2D) :
			p_data(v2D.p_data), m_nb_row(v2D.m_nb_row), m_nb_col(v2D.m_nb_col)
		{
			v2D.m_nb_col = 0;
			v2D.m_nb_row = 0;
			v2D.p_data = nullptr;
		}

		/// @brief Destructor
		~vector2D_C_style_minimal()
		{
			destructor();
		}

		/// @brief Return the number of rows
		/// @return the number of rows
		std::size_t nb_row() const { return m_nb_row; }

		/// @brief Return the number of columns
		/// @return the number of columns
		std::size_t nb_col() const { return m_nb_col; }

		/// @brief Move assignment operator between two vector2D 
		/// @param[in] v2D A vector2D
		/// @return the vector2D_C_style_minimal
		vector2D_C_style_minimal<T> operator =(vector2D_C_style_minimal<T> && v2D)
		{
			// If it is a different vector2D
			if (this != &v2D)
			{
				// Delete actual object
				destructor();
				// Move
				p_data = v2D.p_data;
				m_nb_row = v2D.m_nb_row;
				m_nb_col = v2D.m_nb_col;
				// Remove original object
				v2D.m_nb_col = 0;
				v2D.m_nb_row = 0;
				v2D.p_data = nullptr;
			}
			// Return
			return *this;
		}

		/// @brief Affectation operator between two vector2D
		/// @param[in] v2D A vector2D
		/// @return the vector2D_C_style_minimal
		vector2D_C_style_minimal<T> operator =(vector2D_C_style_minimal<T> const & v2D)
		{
			// If it is a different vector2D
			if (this != &v2D)
			{
				// Copy the vector2D
				vector2D_C_style_minimal<T> tmp(v2D);
				// Move the new vector2D in this
				*this = std::move(tmp);
			}
			// Return
			return *this;
		}

		/// @brief Const access by [i][j]
		/// @param i Row index
		/// @return a T const * to have [j]
		T const * operator[](size_t const i) const { return p_data[i]; }

		/// @brief Access by [i][j]
		/// @param i Row index
		/// @return a T * to have [j]
		T * operator[](size_t const i) { return p_data[i]; }

	private:

		/// @brief Fake destructor
		void destructor()
		{
				std::size_t nb_row_for_delete = m_nb_row;

				m_nb_col = 0;
				m_nb_row = 0;

				for (std::size_t i = 0; i < nb_row_for_delete; ++i)
				{
					delete[] p_data[i];
					p_data[i] = nullptr;
				}

				delete[] p_data;
				p_data = nullptr;
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::vector2D_C_style_minimal<T>
	/// @param[in,out] o Output stream
	/// @param[in]     v A hnc::vector2D_C_style_minimal<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::vector2D_C_style_minimal<T> const & v)
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
