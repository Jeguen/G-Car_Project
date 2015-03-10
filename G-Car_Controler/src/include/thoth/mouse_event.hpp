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


#ifndef THOTH_MOUSE_EVENT_HPP
#define THOTH_MOUSE_EVENT_HPP

#include <functional>

#include <hnc/geometry/is_in_rectangle.hpp>

#include "event.hpp"
#include "mouse.hpp"


namespace thoth
{
	// Forward declaration of thoth::mouse_event function
	template <class T>
	bool mouse_event(thoth::window const & window, T & t, thoth::event const & event);
	
	/**
	 * @brief Mouse events
	 * 
	 * @code
	   #include <thoth/mouse_event.hpp>
	   @endcode
	 */
	class mouse_event_t
	{
	public:
		
		using function_t = std::function<void ()>;
		
	protected:
		
		// Functions
		
		/// On mouse button pressed left function
		function_t m_on_mouse_button_pressed_left;
		
		/// On mouse button released left function
		function_t m_on_mouse_button_released_left;
		
		/// On mouse button clicked left function
		function_t m_on_mouse_button_clicked_left;
		
		/// On mouse button pressed right function
		function_t m_on_mouse_button_pressed_right;
		
		/// On mouse button released right function
		function_t m_on_mouse_button_released_right;
		
		/// On mouse button pressed middle function
		function_t m_on_mouse_button_pressed_middle;
		
		/// On mouse button released middle function
		function_t m_on_mouse_button_released_middle;
		
		/// On mouse button pressed extra 0 function
		function_t m_on_mouse_button_pressed_extra_0;
		
		/// On mouse button released extra 0 function
		function_t m_on_mouse_button_released_extra_0;
		
		/// On mouse button pressed extra 1 function
		function_t m_on_mouse_button_pressed_extra_1;
		
		/// On mouse button released extra 1 function
		function_t m_on_mouse_button_released_extra_1;
		
		/// On mouse wheel moved function
		function_t m_on_mouse_wheel_moved;
		
		/// On mouse moved function
		function_t m_on_mouse_moved;
		
		/// On mouse entered function
		function_t m_on_mouse_entered;
		
		/// On mouse left function
		function_t m_on_mouse_left;
		
		// Last event
		
		/// Last event is mouse button pressed left
		bool m_last_event_is_mouse_button_pressed_left = false;
		
		/// Last event is mouse button released left
		bool m_last_event_is_mouse_button_released_left = false;
		
		/// Last event is mouse button clicked left
		bool m_last_event_is_mouse_button_clicked_left = false;
		
		/// Last event is mouse button pressed right
		bool m_last_event_is_mouse_button_pressed_right = false;
		
		/// Last event is mouse button released right
		bool m_last_event_is_mouse_button_released_right = false;
		
		/// Last event is mouse button pressed middle
		bool m_last_event_is_mouse_button_pressed_middle = false;
		
		/// Last event is mouse button released middle
		bool m_last_event_is_mouse_button_released_middle = false;
		
		/// Last event is mouse button pressed extra 0
		bool m_last_event_is_mouse_button_pressed_extra_0 = false;
		
		/// Last event is mouse button released extra 0
		bool m_last_event_is_mouse_button_released_extra_0 = false;
		
		/// Last event is mouse button pressed extra 1
		bool m_last_event_is_mouse_button_pressed_extra_1 = false;
		
		/// Last event is mouse button released extra 1
		bool m_last_event_is_mouse_button_released_extra_1 = false;
		
		/// Last event is mouse wheel moved function
		bool m_last_event_is_mouse_wheel_moved = false;
		
		/// Last event is mouse moved function
		bool m_last_event_is_mouse_moved = false;
		
		/// Last event is mouse entered function
		bool m_last_event_is_mouse_entered = false;
		
		/// Last event is mouse left function
		bool m_last_event_is_mouse_left = false;
		
	public:
		
		/// @brief Destructor
		virtual ~mouse_event_t() { }
		
		// Stock functions
		
		/// @brief On mouse button pressed left
		/// @param[in] function Function to be called
		void on_mouse_button_pressed_left(function_t const & function) { m_on_mouse_button_pressed_left = function; }
		
		/// @brief On mouse button released left
		/// @param[in] function Function to be called
		void on_mouse_button_released_left(function_t const & function) { m_on_mouse_button_released_left = function; }
		
		/// @brief On mouse button clicked left
		/// @param[in] function Function to be called
		void on_mouse_button_clicked_left(function_t const & function) { m_on_mouse_button_clicked_left = function; }
		
		/// @brief On mouse button pressed right
		/// @param[in] function Function to be called
		void on_mouse_button_pressed_right(function_t const & function) { m_on_mouse_button_pressed_right = function; }
		
		/// @brief On mouse button released right
		/// @param[in] function Function to be called
		void on_mouse_button_released_right(function_t const & function) { m_on_mouse_button_released_right = function; }
		
		/// @brief On mouse button pressed middle
		/// @param[in] function Function to be called
		void on_mouse_button_pressed_middle(function_t const & function) { m_on_mouse_button_pressed_middle = function; }
		
		/// @brief On mouse button released middle
		/// @param[in] function Function to be called
		void on_mouse_button_released_middle(function_t const & function) { m_on_mouse_button_released_middle = function; }
		
		/// @brief On mouse button pressed extra 0
		/// @param[in] function Function to be called
		void on_mouse_button_pressed_extra_0(function_t const & function) { m_on_mouse_button_pressed_extra_0 = function; }
		
		/// @brief On mouse button released extra 0
		/// @param[in] function Function to be called
		void on_mouse_button_released_extra_0(function_t const & function) { m_on_mouse_button_released_extra_0 = function; }
		
		/// @brief On mouse button pressed extra 1
		/// @param[in] function Function to be called
		void on_mouse_button_pressed_extra_1(function_t const & function) { m_on_mouse_button_pressed_extra_1 = function; }
		
		/// @brief On mouse button released extra 1
		/// @param[in] function Function to be called
		void on_mouse_button_released_extra_1(function_t const & function) { m_on_mouse_button_released_extra_1 = function; }
		
		/// @brief On mouse wheel moved
		/// @param[in] function Function to be called
		void on_mouse_wheel_moved(function_t const & function) { m_on_mouse_wheel_moved = function; }
		
		/// @brief On mouse moved
		/// @param[in] function Function to be called
		void on_mouse_moved(function_t const & function) { m_on_mouse_moved = function; }
		
		/// @brief On mouse entered
		/// @param[in] function Function to be called
		void on_mouse_entered(function_t const & function) { m_on_mouse_entered = function; }
		
		/// @brief On mouse left
		/// @param[in] function Function to be called
		void on_mouse_left(function_t const & function) { m_on_mouse_left = function; }
		
		/// Call functions
		
		/// @brief Call mouse button pressed left
		virtual void call_mouse_button_pressed_left()
		{
			call_function(m_on_mouse_button_pressed_left);
			reset_all_last_event();
			m_last_event_is_mouse_button_pressed_left = true;
		}
		
		/// @brief Call mouse button released left
		virtual void call_mouse_button_released_left()
		{
			call_function(m_on_mouse_button_released_left);
			reset_all_last_event();
			m_last_event_is_mouse_button_released_left = true;
		}
		
		/// @brief Call mouse button clicked left
		virtual void call_mouse_button_clicked_left()
		{
			call_function(m_on_mouse_button_clicked_left);
			reset_all_last_event();
			m_last_event_is_mouse_button_clicked_left = true;
		}
		
		/// @brief Call mouse button pressed right
		virtual void call_mouse_button_pressed_right()
		{
			call_function(m_on_mouse_button_pressed_right);
			reset_all_last_event();
			m_last_event_is_mouse_button_pressed_right = true;
		}
		
		/// @brief Call mouse button released right
		virtual void call_mouse_button_released_right()
		{
			call_function(m_on_mouse_button_released_right);
			reset_all_last_event();
			m_last_event_is_mouse_button_released_right = true;
		}
		
		/// @brief Call mouse button pressed middle
		virtual void call_mouse_button_pressed_middle()
		{
			call_function(m_on_mouse_button_pressed_middle);
			reset_all_last_event();
			m_last_event_is_mouse_button_pressed_middle = true;
		}
		
		/// @brief Call mouse button released middle
		virtual void call_mouse_button_released_middle()
		{
			call_function(m_on_mouse_button_released_middle);
			reset_all_last_event();
			m_last_event_is_mouse_button_released_middle = true;
		}
		
		/// @brief Call mouse button pressed extra 0
		virtual void call_mouse_button_pressed_extra_0()
		{
			call_function(m_on_mouse_button_pressed_extra_0);
			reset_all_last_event();
			m_last_event_is_mouse_button_pressed_extra_0 = true;
		}
		
		/// @brief Call mouse button released extra 0
		virtual void call_mouse_button_released_extra_0()
		{
			call_function(m_on_mouse_button_released_extra_0);
			reset_all_last_event();
			m_last_event_is_mouse_button_released_extra_0 = true;
		}
		
		/// @brief Call mouse button pressed extra 1
		virtual void call_mouse_button_pressed_extra_1()
		{
			call_function(m_on_mouse_button_pressed_extra_1);
			reset_all_last_event();
			m_last_event_is_mouse_button_pressed_extra_1 = true;
		}
		
		/// @brief Call mouse button released extra 1
		virtual void call_mouse_button_released_extra_1()
		{
			call_function(m_on_mouse_button_released_extra_1);
			reset_all_last_event();
			m_last_event_is_mouse_button_released_extra_1 = true;
		}
		
		/// @brief Call mouse wheel moved
		virtual void call_mouse_wheel_moved()
		{
			call_function(m_on_mouse_wheel_moved);
			reset_all_last_event();
			m_last_event_is_mouse_wheel_moved = true;
		}
		
		/// @brief Call mouse moved
		virtual void call_mouse_moved()
		{
			call_function(m_on_mouse_moved);
			reset_all_last_event();
			m_last_event_is_mouse_moved = true;
		}
		
		/// @brief Call mouse entered
		virtual void call_mouse_entered()
		{
			call_function(m_on_mouse_entered);
			reset_all_last_event();
			m_last_event_is_mouse_entered = true;
		}
		
		/// @brief Call mouse left
		virtual void call_mouse_left()
		{
			call_function(m_on_mouse_left);
			reset_all_last_event();
			m_last_event_is_mouse_left = true;
		}
		
		// Last event
		
		/// @brief Last event is mouse button pressed left?
		/// @return true if last event is mouse button pressed left, false otherwise
		bool last_event_is_mouse_button_pressed_left() const { return m_last_event_is_mouse_button_pressed_left; }
		
		/// @brief Last event is mouse button released left?
		/// @return true if last event is mouse button released left, false otherwise
		bool last_event_is_mouse_button_released_left() const { return m_last_event_is_mouse_button_released_left; }
		
		/// @brief Last event is mouse button clicked left?
		/// @return true if last event is mouse button clicked left, false otherwise
		bool last_event_is_mouse_button_clicked_left() const { return m_last_event_is_mouse_button_clicked_left; }
		
		/// @brief Last event is mouse button pressed right?
		/// @return true if last event is mouse button pressed right, false otherwise
		bool last_event_is_mouse_button_pressed_right() const { return m_last_event_is_mouse_button_pressed_right; }
		
		/// @brief Last event is mouse button released right?
		/// @return true if last event is mouse button released right, false otherwise
		bool last_event_is_mouse_button_released_right() const { return m_last_event_is_mouse_button_released_right; }
		
		/// @brief Last event is mouse button pressed middle?
		/// @return true if last event is mouse button pressed middle, false otherwise
		bool last_event_is_mouse_button_pressed_middle() const { return m_last_event_is_mouse_button_pressed_middle; }
		
		/// @brief Last event is mouse button released middle?
		/// @return true if last event is mouse button released middle, false otherwise
		bool last_event_is_mouse_button_released_middle() const { return m_last_event_is_mouse_button_released_middle; }
		
		/// @brief Last event is mouse button pressed extra 0?
		/// @return true if last event is mouse button pressed extra 0, false otherwise
		bool last_event_is_mouse_button_pressed_extra_0() const { return m_last_event_is_mouse_button_pressed_extra_0; }
		
		/// @brief Last event is mouse button released extra 0?
		/// @return true if last event is mouse button released extra 0, false otherwise
		bool last_event_is_mouse_button_released_extra_0() const { return m_last_event_is_mouse_button_released_extra_0; }
		
		/// @brief Last event is mouse button pressed extra 1?
		/// @return true if last event is mouse button pressed extra 1, false otherwise
		bool last_event_is_mouse_button_pressed_extra_1() const { return m_last_event_is_mouse_button_pressed_extra_1; }
		
		/// @brief Last event is mouse button released extra 1?
		/// @return true if last event is mouse button released extra 1, false otherwise
		bool last_event_is_mouse_button_released_extra_1() const { return m_last_event_is_mouse_button_released_extra_1; }
		
		/// @brief Last event is mouse wheel moved function
		/// @return true if last event is mouse wheel moved function
		bool last_event_is_mouse_wheel_moved() const { return m_last_event_is_mouse_wheel_moved; }
		
		/// @brief Last event is mouse moved function
		/// @return true if last event is mouse moved function
		bool last_event_is_mouse_moved() const { return m_last_event_is_mouse_moved; }
		
		/// @brief Last event is mouse entered function
		/// @return true if last event is mouse entered function
		bool last_event_is_mouse_entered() const { return m_last_event_is_mouse_entered; }
		
		/// @brief Last event is mouse left function
		/// @return true if last event is mouse left function
		bool last_event_is_mouse_left() const { return m_last_event_is_mouse_left; }
		
	protected:
		
		/// @brief Rest all last event
		void reset_all_last_event()
		{
			m_last_event_is_mouse_button_pressed_left = false;
			m_last_event_is_mouse_button_released_left = false;
			m_last_event_is_mouse_button_clicked_left = false;
			m_last_event_is_mouse_button_pressed_right = false;
			m_last_event_is_mouse_button_released_right = false;
			m_last_event_is_mouse_button_pressed_middle = false;
			m_last_event_is_mouse_button_released_middle = false;
			m_last_event_is_mouse_button_pressed_extra_0 = false;
			m_last_event_is_mouse_button_released_extra_0 = false;
			m_last_event_is_mouse_button_pressed_extra_1 = false;
			m_last_event_is_mouse_button_released_extra_1 = false;
			m_last_event_is_mouse_wheel_moved = false;
			m_last_event_is_mouse_moved = false;
			m_last_event_is_mouse_entered = false;
			m_last_event_is_mouse_left = false;
		}
		
	protected:
		
		/// @brief Call function if valid
		/// @param[in] function Function to be called
		static void call_function(function_t const & function) { if (function) { function(); } }
		
	public:
		
		template <class T>
		friend bool thoth::mouse_event(thoth::window const & window, T & t, thoth::event const & event);
	};
	
	/**
	 * @brief Apply event to the object
	 * 
	 * @code
	   #include <thoth/mouse_event.hpp>
	   @endcode
	 *
	 * @param[in] window A thoth::window
	 * @param[in] t      A object with .position() and thoth::mouse_event_t methods
	 * @param[in] event  A thoth::event
	 *
	 * @return true if the event is used, false otherwise
	 */
	template <class T>
	bool mouse_event(thoth::window const & window, T & t, thoth::event const & event)
	{
		bool r = false;
		
		using hnc::geometry::is_in_rectangle;
		
		// On mouse button pressed left
		if (event.mouse_button_pressed_left())
		{
			auto const mouse_position = thoth::mouse::position(window);
			
			if (is_in_rectangle(float(mouse_position.x), float(mouse_position.y), t.bounds_global()))
			{
				t.call_mouse_button_pressed_left();
				r = true;
			}
		}
		
		// On mouse button released left
		else if (event.mouse_button_released_left())
		{
			if (t.last_event_is_mouse_button_pressed_left())
			{
				// Released
				t.call_mouse_button_released_left();
				
				// Clicked
				auto const mouse_position = thoth::mouse::position(window);
				
				if (is_in_rectangle(float(mouse_position.x), float(mouse_position.y), t.bounds_global()))
				{
					t.call_mouse_button_clicked_left();
				}
				
				r = true;
			}
			
		}
		
		// On mouse button pressed right
		
		// On mouse button released right
		
		// On mouse button pressed middle
		
		// On mouse button released middle
		
		// On mouse button pressed extra 0
		
		// On mouse button released extra 0
		
		// On mouse button pressed extra 1
		
		// On mouse button released extra 1
		
		// On mouse wheel moved
		
		// On mouse moved
		
		// On mouse entered
		
		// On mouse left
		
		return r;
	}
}

#endif