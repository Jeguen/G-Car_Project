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


#ifndef HNC_VECTOR3D_C_STYLE_MINIMAL_HPP
#define HNC_VECTOR3D_C_STYLE_MINIMAL_HPP


namespace hnc
{
	/**
	 * @brief Minimal encapsulation for a C style 3D array with dynamic allocation
	 *
	 * @code
	   #include <hnc/vector3D_C_style_minimal.hpp>
	   @endcode
	 *
	 * @note For other use, have a look to:
	 * - hnc::vector3D
	 * - hnc::vector3D_C_style
	 * - hnc::vector3D_minimal
	 */
	template <class T>
	class vector3D_C_style_minimal
	{
	private:

		/// T[][][] data
		T * * * p_data;

		/// Size of the dimension x
		std::size_t m_size_x;

		/// Size of the dimension y
		std::size_t m_size_y;

		/// Size of the dimension z
		std::size_t m_size_z;

	public:

		/// @brief Constructor
		/// @param[in] size_x        Size of the dimension x
		/// @param[in] size_y        Size of the dimension y
		/// @param[in] size_z        Size of the dimension z
		/// @param[in] default_value Default value (T() by default)
		vector3D_C_style_minimal
		(
			std::size_t const size_x = 0, std::size_t const size_y = 0, std::size_t const size_z = 0,
			T const & default_value = T()
		) :
			p_data(nullptr),
			m_size_x(size_x),
			m_size_y(size_y),
			m_size_z(size_z)
		{
			p_data = new T * *[m_size_x];

			for (std::size_t x = 0; x < m_size_x; ++x)
			{
				p_data[x] = new T *[m_size_y];
				
				for (std::size_t y = 0; y < m_size_y; ++y)
				{
					p_data[x][y] = new T[m_size_z];

					for (std::size_t z = 0; z < m_size_z; ++z)
					{
						p_data[x][y][z] = default_value;
					}
				}
			}
		}

		/// @brief Constructor by copy
		/// @param[in] v3D A vector3D
		vector3D_C_style_minimal(vector3D_C_style_minimal<T> const & v3D) :
			vector3D_C_style_minimal(v3D.size_x(), v3D.size_y(), v3D.size_z())
		{
			for (std::size_t x = 0; x < m_size_x; ++x)
			{
				for (std::size_t y = 0; y < m_size_y; ++y)
				{
					for (std::size_t z = 0; z < m_size_z; ++z)
					{
						p_data[x][y][z] = v3D[x][y][z];
					}
				}
			}
		}

		/// @brief Constructor by RValues reference
		/// @param[in] v3D A vector3D (will be destroyed)
		vector3D_C_style_minimal(vector3D_C_style_minimal<T> && v3D) :
			p_data(v3D.p_data),
			m_size_x(v3D.m_size_x),
			m_size_y(v3D.m_size_y),
			m_size_z(v3D.m_size_z)
		{
			v3D.m_size_z = 0;
			v3D.m_size_y = 0;
			v3D.m_size_x = 0;
			v3D.p_data = nullptr;
		}

		/// @brief Destructor
		~vector3D_C_style_minimal()
		{
			destructor();
		}

		/// @brief Return the size of the dimension x
		/// @return the size of the dimension x
		std::size_t size_x() const { return m_size_x; }

		/// @brief Return the size of the dimension y
		/// @return the size of the dimension y
		std::size_t size_y() const { return m_size_y; }

		/// @brief Return the size of the dimension z
		/// @return the size of the dimension z
		std::size_t size_z() const { return m_size_z; }

		/// @brief Move assignment operator between two vector3D
		/// @param[in] v3D A vector3D
		/// @return the vector3D_C_style_minimal
		vector3D_C_style_minimal<T> operator =(vector3D_C_style_minimal<T> && v3D)
		{
			// If it is a different vector3D
			if (this != &v3D)
			{
				// Delete actual object
				destructor();
				// Move
				p_data = v3D.p_data;
				m_size_x = v3D.m_size_x;
				m_size_y = v3D.m_size_y;
				m_size_z = v3D.m_size_z;
				// Remove original object
				v3D.m_size_z = 0;
				v3D.m_size_y = 0;
				v3D.m_size_x = 0;
				v3D.p_data = nullptr;
			}
			// Return
			return *this;
		}

		/// @brief Affectation operator between two vector3D
		/// @param[in] v3D A vector3D
		/// @return the vector3D_C_style_minimal
		vector3D_C_style_minimal<T> operator =(vector3D_C_style_minimal<T> const & v3D)
		{
			// If it is a different vector3D
			if (this != &v3D)
			{
				// Copy the vector3D
				vector3D_C_style_minimal<T> tmp(v3D);
				// Move the new vector3D in this
				*this = std::move(tmp);
			}
			// Return
			return *this;
		}

		/// @brief Const access by [x][y][z]
		/// @param x Dimension x
		/// @return a T const * * to have [y][z]
		T const * const * operator[](size_t const x) const { return p_data[x]; }

		/// @brief Access by [x][y][z]
		/// @param x Dimension x
		/// @return a T const * * to have [y][z]
		T * * operator[](size_t const x) { return p_data[x]; }

	private:

		/// @brief Fake destructor
		void destructor()
		{
				std::size_t size_x_for_delete = m_size_x;
				std::size_t size_y_for_delete = m_size_y;

				m_size_x = 0;
				m_size_y = 0;
				m_size_z = 0;

				for (std::size_t x = 0; x < size_x_for_delete; ++x)
				{
					for (std::size_t y = 0; y < size_y_for_delete; ++y)
					{
						delete[] p_data[x][y];
						p_data[x][y] = nullptr;
					}
					
					delete[] p_data[x];
					p_data[x] = nullptr;
				}

				delete[] p_data;
				p_data = nullptr;
		}
	};
	
	/// @brief Operator << between a std::ostream and a hnc::vector3D_C_style_minimal<T>
	/// @param[in,out] o Output stream
	/// @param[in]     v A hnc::vector3D_C_style_minimal<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::vector3D_C_style_minimal<T> const & v)
	{
		// Display data
		o << "{";
		for (std::size_t x = 0; x < v.size_x(); ++x)
		{
			if (x == 0) { o << "\n"; }
			for (std::size_t y = 0; y < v.size_y(); ++y)
			{
				o << ((y == 0) ? ("  {") : ("   "));
				o << " {";
				for (std::size_t z = 0; z < v.size_z(); ++z)
				{
					if (z != 0) { o << ", "; }
					o << v[x][y][z];
				}
				o << ((y == v.size_y() - 1) ? ("} }") : ("},\n"));
			}
			o << ((x == v.size_x() - 1) ? ("\n") : (",\n"));
		}
		o << "}";

		// Return stream
		return o;
	}
}


#endif
