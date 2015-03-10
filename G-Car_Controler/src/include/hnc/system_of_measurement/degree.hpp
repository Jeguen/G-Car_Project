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


#ifndef HNC_SYSTEM_OF_MEASUREMENT_DEGREE_HPP
#define HNC_SYSTEM_OF_MEASUREMENT_DEGREE_HPP

#include <type_traits>

#include "../math/pi.hpp"
#include "radian.hpp"
#include "../serialization.hpp"


namespace hnc
{
	// Forward declaration of class radian
	template <class T>
	class radian;
	
	/**
	 * @brief Degree (angle)
	 *
	 * @code
	   #include <hnc/system_of_measurement.hpp>
	   @endcode
	 *
	 * @b From http://en.wikipedia.org/wiki/Degree_%28angle%29 @n
	 * A degree (in full, a degree of arc, arc degree, or arcdegree), usually denoted by ° (the degree symbol), is a measurement of plane angle, representing @f$ \frac{1}{360} @f$ of a full rotation; one degree is equivalent to @f$ \frac{\Pi}{180} @f$ radians. It is not an SI unit, as the SI unit for angles is radian, but it is mentioned in the SI brochure as an accepted unit.
	 */
	template <class T>
	class degree
	{
	static_assert(std::is_arithmetic<T>::value, "hnc::degree works for arithmetic types only");
		
	private:

		/// Value of the angle in degree
		T m_value;

	public:

		/// @brief Construtor
		/// @param[in] degree_value Degree value (T(0) by default)
		explicit degree(T const degree_value = T(0)) : m_value(degree_value) { }
		
		/// @brief Constructor with hnc::radian
		/// @param[in] radian A hnc::radian
		degree(hnc::radian<T> const radian) : m_value(radian.degree_value()) { }
		
		/// @brief Operator= between hnc::degree and hnc::radian
		/// @param[in] radian A hnc::radian
		/// @return the hnc::degree
		hnc::degree<T> & operator =(hnc::radian<T> const radian)
		{
			m_value = radian.degree_value();
			return *this;
		}
		
		hnc_generate_serialize_member_function(m_value)
		
		/// @brief Operator== between two hnc::degree
		/// @param[in] degree A hnc::degree
		/// @return true if the hnc::degree are equals, false otherwise
		bool operator ==(hnc::degree<T> const degree)
		{
			return (m_value == degree.value());
		}
		
		/// @brief Operator!= between two hnc::degree
		/// @param[in] degree A hnc::degree
		/// @return true if the hnc::degree are not equals, false otherwise
		bool operator !=(hnc::degree<T> const degree)
		{
			return (! (*this == degree));
		}
		
		/// @brief Operator== between hnc::degree and hnc::radian
		/// @param[in] radian A hnc::radian
		/// @return true if the hnc::degree and the hnc::radian are equals, false otherwise
		bool operator ==(hnc::radian<T> const radian)
		{
			return (m_value == radian.degree_value());
		}
		
		/// @brief Operator!= between hnc::degree and hnc::radian
		/// @param[in] radian A hnc::radian
		/// @return true if the hnc::degree and the hnc::radian are not equals, false otherwise
		bool operator !=(hnc::radian<T> const radian)
		{
			return (! (*this == radian));
		}

		/// @brief Return the degree value
		/// @return the degree value
		T value() const { return m_value; }

		/// @copydoc hnc::degree::value
		T degree_value() const { return value(); }
		
		/// @copydoc hnc::radian::value
		T radian_value() const { return ((value() * math::pi<T>()) / T(180)); }
		
		/// @brief Return a hnc::radian with converted value
		/// @return the a hnc::radian with converted value
		radian<T> to_radian() const { return hnc::radian<T>(radian_value()); }
	};
	
	/// @brief Operator << between a std::ostream and a hnc::degree<T>
	/// @param[in,out] o            Output stream
	/// @param[in]     angle_degree A hnc::degree<T>
	/// @return the output stream
	template <class T>
	std::ostream & operator <<(std::ostream & o, hnc::degree<T> const & angle_degree)
	{
		o << angle_degree.value() << "°";
		return o;
	}
}

#endif
