// Copyright © 2014 Lénaïc Bagnères, hnc@singularity.fr

// This file is part of Thōth.

// Thōth is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// Thōth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with Thōth. If not, see <http://www.gnu.org/licenses/>


#ifndef THOTH_TRANSFORMABLE_HPP
#define THOTH_TRANSFORMABLE_HPP

#include <hnc/vector2.hpp>
#include <hnc/system_of_measurement/degree.hpp>
#include <hnc/system_of_measurement/radian.hpp>
#include <hnc/geometry/rectangle.hpp>

#include "to_hnc.hpp"


namespace thoth
{
	/**
	 * @brief Transformable
	 * 
	 * @code
	   #include <thoth/transformable.hpp>
	   @endcode
	 */
	class transformable
	{
	public:
		
		/// @brief Destructor
		virtual ~transformable() = 0;
		
		/// @brief Get position
		/// @return the position
		virtual hnc::vector2<float> position() const = 0;
		
		/// @brief Set position
		/// @param[in] x New x position
		/// @param[in] y New y position
		virtual void set_position(float const x, float const y) = 0;
		
		/// @brief Set position
		/// @param[in] position New position
		virtual void set_position(hnc::vector2<float> const & position) { set_position(position.x, position.y); }
		
		/// @brief Move
		/// @param[in] d_x Move on X axis
		/// @param[in] d_y Move on Y axis
		virtual void move(float const d_x, float const d_y) = 0;
		
		/// @brief Get rotation
		/// @return the rotation
		virtual hnc::degree<float> rotation() const = 0;
		
		/// @brief Set rotation
		/// @param[in] angle Angle in degree
		virtual void set_rotation(hnc::degree<float> const & angle) = 0;
		
		/// @brief Set rotation
		/// @param[in] angle Angle in radian
		virtual void set_rotation(hnc::radian<float> const & angle) { set_rotation(angle.to_degree()); }
		
		/// @brief Rotate
		/// @param[in] angle Angle in degree
		virtual void rotate(hnc::degree<float> const & angle) = 0;
		
		/// @brief Rotate
		/// @param[in] angle Angle in radian
		virtual void rotate(hnc::radian<float> const & angle) { rotate(angle.to_degree()); }
		
		/// @brief Get origin
		/// @return the origin
		virtual hnc::vector2<float> origin() const = 0;
		
		/// @brief Set origin
		/// @param[in] x New x position of the center
		/// @param[in] y New y position of the center
		virtual void set_origin(float const x, float const y) = 0;
		
		/// @brief Set origin
		/// @param[in] origin New origin
		virtual void set_origin(hnc::vector2<float> const & origin) { set_origin(origin.x, origin.y); }
		
		/// @brief Return the global bounds of the sprite
		/// @return the global bounds of the sprite
		virtual hnc::geometry::rectangle<float> bounds_global() const = 0;
		
	protected:
		
		// SFML
		
		/// @brief Get position
		/// @param[in] sfml_object SFML object
		/// @return the position
		template <class sfml_t>
		static hnc::vector2<float> position_sfml(sfml_t const & sfml_object)
		{
			return thoth::to_hnc(sfml_object.getPosition());
		}
		
		/// @brief Set position
		/// @param[in,out] sfml_object SFML object
		/// @param[in]     x           New x position
		/// @param[in]     y           New y position
		template <class sfml_t>
		static void set_position_sfml(sfml_t & sfml_object, float const x, float const y)
		{
			sfml_object.setPosition(x, y);
		}
		
		/// @brief Move
		/// @param[in,out] sfml_object SFML object
		/// @param[in]     d_x         Move on X axis
		/// @param[in]     d_y         Move on Y axis
		template <class sfml_t>
		static void move_sfml(sfml_t & sfml_object, float const d_x, float const d_y)
		{
			sfml_object.move(d_x, d_y);
		}
		
		/// @brief Get rotation
		/// @param[in] sfml_object SFML object
		/// @return the rotation
		template <class sfml_t>
		static hnc::degree<float> rotation_sfml(sfml_t const & sfml_object)
		{
			return hnc::degree<float>(sfml_object.getRotation());
		}
		
		/// @brief Set rotation
		/// @param[in,out] sfml_object SFML object
		/// @param[in]     angle       Angle in degree
		template <class sfml_t>
		static void set_rotation_sfml(sfml_t & sfml_object, hnc::degree<float> const & angle)
		{
			sfml_object.setRotation(angle.degree_value());
		}
		
		/// @brief Rotate
		/// @param[in,out] sfml_object SFML object
		/// @param[in]     angle       Angle in degree
		template <class sfml_t>
		static void rotate_sfml(sfml_t & sfml_object, hnc::degree<float> const & angle)
		{
			sfml_object.rotate(angle.degree_value());
		}
		
		/// @brief Get origin
		/// @param[in] sfml_object SFML object
		/// @return the origin
		template <class sfml_t>
		static hnc::vector2<float> origin_sfml(sfml_t const & sfml_object)
		{
			return thoth::to_hnc(sfml_object.getOrigin());
		}
		
		/// @brief Set origin
		/// @param[in,out] sfml_object SFML object
		/// @param[in]     x           New x position of the center
		/// @param[in]     y           New y position of the center
		template <class sfml_t>
		static void set_origin_sfml(sfml_t & sfml_object, float const x, float const y)
		{
			sfml_object.setOrigin(x, y);
		}
		
		/// @brief Return the global bounds of the sprite
		/// @param[in] sfml_object SFML object
		/// @return the global bounds of the sprite
		template <class sfml_t>
		static hnc::geometry::rectangle<float> bounds_global_sfml(sfml_t const & sfml_object)
		{
			return thoth::to_hnc(sfml_object.getGlobalBounds());
		}
		
		// Thōth
		
		/// @brief Get position
		/// @param[in] thoth_object Thōth object
		/// @return the position
		template <class thoth_t>
		static hnc::vector2<float> position_thoth(thoth_t const & thoth_object)
		{
			return thoth_object.position();
		}
		
		/// @brief Set position
		/// @param[in,out] thoth_object Thōth object
		/// @param[in]     x            New x position
		/// @param[in]     y            New y position
		template <class thoth_t>
		static void set_position_thoth(thoth_t & thoth_object, float const x, float const y)
		{
			thoth_object.set_position(x, y);
		}
		
		/// @brief Get rotation
		/// @param[in] thoth_object Thōth object
		/// @return the rotation
		template <class thoth_t>
		static hnc::degree<float> rotation_thoth(thoth_t const & thoth_object)
		{
			return thoth_object.rotation();
		}
		
		/// @brief Set rotation
		/// @param[in,out] thoth_object Thōth object
		/// @param[in]     angle        Angle in degree
		template <class thoth_t>
		static void set_rotation_thoth(thoth_t & thoth_object, hnc::degree<float> const & angle)
		{
			thoth_object.set_rotation(angle);
		}
		
		/// @brief Rotate
		/// @param[in,out] thoth_object Thōth object
		/// @param[in]     angle        Angle in degree
		template <class thoth_t>
		static void rotate_thoth(thoth_t & thoth_object, hnc::degree<float> const & angle)
		{
			thoth_object.rotate(angle);
		}
		
		/// @brief Get origin
		/// @param[in] thoth_object Thōth object
		/// @return the origin
		template <class thoth_t>
		static hnc::vector2<float> origin_thoth(thoth_t const & thoth_object)
		{
			return thoth_object.origin();
		}
		
		/// @brief Set origin
		/// @param[in,out] thoth_object Thōth object
		/// @param[in]     x            New x position of the center
		/// @param[in]     y            New y position of the center
		template <class thoth_t>
		static void set_origin_thoth(thoth_t & thoth_object, float const x, float const y)
		{
			thoth_object.set_origin(x, y);
		}
		
		/// @brief Return the global bounds of the sprite
		/// @param[in] thoth_object Thōth object
		/// @return the global bounds of the sprite
		template <class thoth_t>
		static hnc::geometry::rectangle<float> bounds_global_thoth(thoth_t const & thoth_object)
		{
			return thoth_object.bounds_global();
		}
		
		// Common
		
		/// @brief Move
		/// @param[in,out] T   Object with .move() method
		/// @param[in]     d_x Move on X axis
		/// @param[in]     d_y Move on Y axis
		template <class T>
		static void move(T & t, float const d_x, float const d_y)
		{
			t.move(d_x, d_y);
		}
	};
	
	transformable::~transformable() { }
}

#endif
