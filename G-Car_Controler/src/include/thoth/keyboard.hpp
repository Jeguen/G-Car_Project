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


#ifndef THOTH_KEYBOARD_HPP
#define THOTH_KEYBOARD_HPP

#include <iostream>

#include <SFML/Window/Keyboard.hpp>


namespace thoth
{
	/**
	 * @brief Keyboard keys
	 * 
	 * @code
	   #include <thoth/keyboard.hpp>
	   @endcode
	 */
	enum class keyboard : int
	{
		unknown = sf::Keyboard::Unknown,
		a = sf::Keyboard::A,
		b = sf::Keyboard::B,
		c = sf::Keyboard::C,
		d = sf::Keyboard::D,
		e = sf::Keyboard::E,
		f = sf::Keyboard::F,
		g = sf::Keyboard::G,
		h = sf::Keyboard::H,
		i = sf::Keyboard::I,
		j = sf::Keyboard::J,
		k = sf::Keyboard::K,
		l = sf::Keyboard::L,
		m = sf::Keyboard::M,
		n = sf::Keyboard::N,
		o = sf::Keyboard::O,
		p = sf::Keyboard::P,
		q = sf::Keyboard::Q,
		r = sf::Keyboard::R,
		s = sf::Keyboard::S,
		t = sf::Keyboard::T,
		u = sf::Keyboard::U,
		v = sf::Keyboard::V,
		w = sf::Keyboard::W,
		x = sf::Keyboard::X,
		y = sf::Keyboard::Y,
		z = sf::Keyboard::Z,
		num_0 = sf::Keyboard::Num0,
		num_1 = sf::Keyboard::Num1,
		num_2 = sf::Keyboard::Num2,
		num_3 = sf::Keyboard::Num3,
		num_4 = sf::Keyboard::Num4,
		num_5 = sf::Keyboard::Num5,
		num_6 = sf::Keyboard::Num6,
		num_7 = sf::Keyboard::Num7,
		num_8 = sf::Keyboard::Num8,
		num_9 = sf::Keyboard::Num9,
		escape = sf::Keyboard::Escape,
		control_left = sf::Keyboard::LControl,
		shift_left = sf::Keyboard::LShift,
		alt_left = sf::Keyboard::LAlt,
		system_left = sf::Keyboard::LSystem,
		control_right = sf::Keyboard::RControl,
		shift_right = sf::Keyboard::RShift,
		alt_right = sf::Keyboard::RAlt,
		system_alt = sf::Keyboard::RSystem,
		menu = sf::Keyboard::Menu,
		bracket_left = sf::Keyboard::LBracket,
		bracket_right = sf::Keyboard::RBracket,
		semicolon = sf::Keyboard::SemiColon,
		comma = sf::Keyboard::Comma,
		period = sf::Keyboard::Period,
		quote = sf::Keyboard::Quote,
		slash = sf::Keyboard::Slash,
		backslash = sf::Keyboard::BackSlash,
		tilde = sf::Keyboard::Tilde,
		equal = sf::Keyboard::Equal,
		dash = sf::Keyboard::Dash,
		space = sf::Keyboard::Space,
		enter = sf::Keyboard::Return,
		backspace = sf::Keyboard::BackSpace,
		tab = sf::Keyboard::Tab,
		page_up = sf::Keyboard::PageUp,
		page_down = sf::Keyboard::PageDown,
		end = sf::Keyboard::End,
		home = sf::Keyboard::Home,
		insert = sf::Keyboard::Insert,
		del = sf::Keyboard::Delete,
		add = sf::Keyboard::Add,
		subtract = sf::Keyboard::Subtract,
		multiply = sf::Keyboard::Multiply,
		divide = sf::Keyboard::Divide,
		left = sf::Keyboard::Left,
		right = sf::Keyboard::Right,
		up = sf::Keyboard::Up,
		down = sf::Keyboard::Down,
		numpad_0 = sf::Keyboard::Numpad0,
		numpad_1 = sf::Keyboard::Numpad1,
		numpad_2 = sf::Keyboard::Numpad2,
		numpad_3 = sf::Keyboard::Numpad3,
		numpad_4 = sf::Keyboard::Numpad4,
		numpad_5 = sf::Keyboard::Numpad5,
		numpad_6 = sf::Keyboard::Numpad6,
		numpad_7 = sf::Keyboard::Numpad7,
		numpad_8 = sf::Keyboard::Numpad8,
		numpad_9 = sf::Keyboard::Numpad9,
		f1 = sf::Keyboard::F1,
		f2 = sf::Keyboard::F2,
		f3 = sf::Keyboard::F3,
		f4 = sf::Keyboard::F4,
		f5 = sf::Keyboard::F5,
		f6 = sf::Keyboard::F6,
		f7 = sf::Keyboard::F7,
		f8 = sf::Keyboard::F8,
		f9 = sf::Keyboard::F9,
		f10 = sf::Keyboard::F10,
		f11 = sf::Keyboard::F11,
		f12 = sf::Keyboard::F12,
		f13 = sf::Keyboard::F13,
		f14 = sf::Keyboard::F14,
		f15 = sf::Keyboard::F15,
		pause = sf::Keyboard::Pause,
		key_count = sf::Keyboard::KeyCount
	};
	
	/**
	 * @brief Test if key is pressed
	 * 
	 * @code
	   #include <thoth/keyboard.hpp>
	   @endcode
	 *
	 * @param[in] key A thoth::keyboard key
	 *
	 * @return true if the key is pressed, false otherwise
	 */
	inline bool key_pressed(thoth::keyboard const key)
	{
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
	}
	
	/// @brief Operator << between a std::ostream and a thoth::keyboard
	/// @param[in,out] o   Output stream
	/// @param[in]     key A thoth::keyboard
	/// @return the output stream
	inline std::ostream & operator <<(std::ostream & o, thoth::keyboard const key)
	{
		if (key == thoth::keyboard::unknown) { o << "thoth::keyboard::unknown"; }
		else if (key == thoth::keyboard::a) { o << "key == thoth::keyboard::a"; }
		else if (key == thoth::keyboard::b) { o << "thoth::keyboard::b"; }
		else if (key == thoth::keyboard::c) { o << "thoth::keyboard::c"; }
		else if (key == thoth::keyboard::d) { o << "thoth::keyboard::d"; }
		else if (key == thoth::keyboard::e) { o << "thoth::keyboard::e"; }
		else if (key == thoth::keyboard::f) { o << "thoth::keyboard::f"; }
		else if (key == thoth::keyboard::g) { o << "thoth::keyboard::g"; }
		else if (key == thoth::keyboard::h) { o << "thoth::keyboard::h"; }
		else if (key == thoth::keyboard::i) { o << "thoth::keyboard::i"; }
		else if (key == thoth::keyboard::j) { o << "thoth::keyboard::j"; }
		else if (key == thoth::keyboard::k) { o << "thoth::keyboard::k"; }
		else if (key == thoth::keyboard::l) { o << "thoth::keyboard::l"; }
		else if (key == thoth::keyboard::m) { o << "thoth::keyboard::m"; }
		else if (key == thoth::keyboard::n) { o << "thoth::keyboard::n"; }
		else if (key == thoth::keyboard::o) { o << "thoth::keyboard::o"; }
		else if (key == thoth::keyboard::p) { o << "thoth::keyboard::p"; }
		else if (key == thoth::keyboard::q) { o << "thoth::keyboard::q"; }
		else if (key == thoth::keyboard::r) { o << "thoth::keyboard::r"; }
		else if (key == thoth::keyboard::s) { o << "thoth::keyboard::s"; }
		else if (key == thoth::keyboard::t) { o << "thoth::keyboard::t"; }
		else if (key == thoth::keyboard::u) { o << "thoth::keyboard::u"; }
		else if (key == thoth::keyboard::v) { o << "thoth::keyboard::v"; }
		else if (key == thoth::keyboard::w) { o << "thoth::keyboard::w"; }
		else if (key == thoth::keyboard::x) { o << "thoth::keyboard::x"; }
		else if (key == thoth::keyboard::y) { o << "thoth::keyboard::y"; }
		else if (key == thoth::keyboard::z) { o << "thoth::keyboard::z"; }
		else if (key == thoth::keyboard::num_0) { o << "thoth::keyboard::num_0"; }
		else if (key == thoth::keyboard::num_1) { o << "thoth::keyboard::num_1"; }
		else if (key == thoth::keyboard::num_2) { o << "thoth::keyboard::num_2"; }
		else if (key == thoth::keyboard::num_3) { o << "thoth::keyboard::num_3"; }
		else if (key == thoth::keyboard::num_4) { o << "thoth::keyboard::num_4"; }
		else if (key == thoth::keyboard::num_5) { o << "thoth::keyboard::num_5"; }
		else if (key == thoth::keyboard::num_6) { o << "thoth::keyboard::num_6"; }
		else if (key == thoth::keyboard::num_7) { o << "thoth::keyboard::num_7"; }
		else if (key == thoth::keyboard::num_8) { o << "thoth::keyboard::num_8"; }
		else if (key == thoth::keyboard::num_9) { o << "thoth::keyboard::num_9"; }
		else if (key == thoth::keyboard::escape) { o << "thoth::keyboard::escape"; }
		else if (key == thoth::keyboard::control_left) { o << "thoth::keyboard::control_left"; }
		else if (key == thoth::keyboard::shift_left) { o << "thoth::keyboard::shift_left"; }
		else if (key == thoth::keyboard::alt_left) { o << "thoth::keyboard::alt_left"; }
		else if (key == thoth::keyboard::system_left) { o << "thoth::keyboard::system_left"; }
		else if (key == thoth::keyboard::control_right) { o << "thoth::keyboard::control_right"; }
		else if (key == thoth::keyboard::shift_right) { o << "thoth::keyboard::shift_right"; }
		else if (key == thoth::keyboard::alt_right) { o << "thoth::keyboard::alt_right"; }
		else if (key == thoth::keyboard::system_alt) { o << "thoth::keyboard::system_alt"; }
		else if (key == thoth::keyboard::menu) { o << "thoth::keyboard::menu"; }
		else if (key == thoth::keyboard::bracket_left) { o << "thoth::keyboard::bracket_left"; }
		else if (key == thoth::keyboard::bracket_right) { o << "thoth::keyboard::bracket_right"; }
		else if (key == thoth::keyboard::semicolon) { o << "thoth::keyboard::semicolon"; }
		else if (key == thoth::keyboard::comma) { o << "thoth::keyboard::comma"; }
		else if (key == thoth::keyboard::period) { o << "thoth::keyboard::period"; }
		else if (key == thoth::keyboard::quote) { o << "thoth::keyboard::quote"; }
		else if (key == thoth::keyboard::slash) { o << "thoth::keyboard::slash"; }
		else if (key == thoth::keyboard::backslash) { o << "thoth::keyboard::backslash"; }
		else if (key == thoth::keyboard::tilde) { o << "thoth::keyboard::tilde"; }
		else if (key == thoth::keyboard::equal) { o << "thoth::keyboard::equal"; }
		else if (key == thoth::keyboard::dash) { o << "thoth::keyboard::dash"; }
		else if (key == thoth::keyboard::space) { o << "thoth::keyboard::space"; }
		else if (key == thoth::keyboard::enter) { o << "thoth::keyboard::enter"; }
		else if (key == thoth::keyboard::backspace) { o << "thoth::keyboard::backspace"; }
		else if (key == thoth::keyboard::tab) { o << "thoth::keyboard::tab"; }
		else if (key == thoth::keyboard::page_up) { o << "thoth::keyboard::page_up"; }
		else if (key == thoth::keyboard::page_down) { o << "thoth::keyboard::page_down"; }
		else if (key == thoth::keyboard::end) { o << "thoth::keyboard::end"; }
		else if (key == thoth::keyboard::home) { o << "thoth::keyboard::home"; }
		else if (key == thoth::keyboard::insert) { o << "thoth::keyboard::insert"; }
		else if (key == thoth::keyboard::del) { o << "thoth::keyboard::del"; }
		else if (key == thoth::keyboard::add) { o << "thoth::keyboard::add"; }
		else if (key == thoth::keyboard::subtract) { o << "thoth::keyboard::subtract"; }
		else if (key == thoth::keyboard::multiply) { o << "thoth::keyboard::multiply"; }
		else if (key == thoth::keyboard::divide) { o << "thoth::keyboard::divide"; }
		else if (key == thoth::keyboard::left) { o << "thoth::keyboard::left"; }
		else if (key == thoth::keyboard::right) { o << "thoth::keyboard::right"; }
		else if (key == thoth::keyboard::up) { o << "thoth::keyboard::up"; }
		else if (key == thoth::keyboard::down) { o << "thoth::keyboard::down"; }
		else if (key == thoth::keyboard::numpad_0) { o << "thoth::keyboard::numpad_0"; }
		else if (key == thoth::keyboard::numpad_1) { o << "thoth::keyboard::numpad_1"; }
		else if (key == thoth::keyboard::numpad_2) { o << "thoth::keyboard::numpad_2"; }
		else if (key == thoth::keyboard::numpad_3) { o << "thoth::keyboard::numpad_3"; }
		else if (key == thoth::keyboard::numpad_4) { o << "thoth::keyboard::numpad_4"; }
		else if (key == thoth::keyboard::numpad_5) { o << "thoth::keyboard::numpad_5"; }
		else if (key == thoth::keyboard::numpad_6) { o << "thoth::keyboard::numpad_6"; }
		else if (key == thoth::keyboard::numpad_7) { o << "thoth::keyboard::numpad_7"; }
		else if (key == thoth::keyboard::numpad_8) { o << "thoth::keyboard::numpad_8"; }
		else if (key == thoth::keyboard::numpad_9) { o << "thoth::keyboard::numpad_9"; }
		else if (key == thoth::keyboard::f1) { o << "thoth::keyboard::f1"; }
		else if (key == thoth::keyboard::f2) { o << "thoth::keyboard::f2"; }
		else if (key == thoth::keyboard::f3) { o << "thoth::keyboard::f3"; }
		else if (key == thoth::keyboard::f4) { o << "thoth::keyboard::f4"; }
		else if (key == thoth::keyboard::f5) { o << "thoth::keyboard::f5"; }
		else if (key == thoth::keyboard::f6) { o << "thoth::keyboard::f6"; }
		else if (key == thoth::keyboard::f7) { o << "thoth::keyboard::f7"; }
		else if (key == thoth::keyboard::f8) { o << "thoth::keyboard::f8"; }
		else if (key == thoth::keyboard::f9) { o << "thoth::keyboard::f9"; }
		else if (key == thoth::keyboard::f10) { o << "thoth::keyboard::f10"; }
		else if (key == thoth::keyboard::f11) { o << "thoth::keyboard::f11"; }
		else if (key == thoth::keyboard::f12) { o << "thoth::keyboard::f12"; }
		else if (key == thoth::keyboard::f13) { o << "thoth::keyboard::f13"; }
		else if (key == thoth::keyboard::f14) { o << "thoth::keyboard::f14"; }
		else if (key == thoth::keyboard::f15) { o << "thoth::keyboard::f15"; }
		else if (key == thoth::keyboard::pause) { o << "thoth::keyboard::pause"; }
		else if (key == thoth::keyboard::key_count) { o << "thoth::keyboard::key_count"; }
		else { o << "thoth::keyboard::???"; }
		
		o << " (" << int(key) << ")";
		
		return o;
	}
}

#endif
