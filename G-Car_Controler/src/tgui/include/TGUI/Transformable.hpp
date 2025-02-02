/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2015 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TGUI_TRANSFORMABLE_HPP
#define TGUI_TRANSFORMABLE_HPP


#include <TGUI/Global.hpp>
#include <TGUI/Layout.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class TGUI_API Transformable
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Transformable() = default;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Transformable(const Transformable& copy);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Transformable& operator=(const Transformable& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Transformable() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position New position
        ///
        /// @see move, getPosition
        ///
        /// Usage examples:
        /// @code
        /// // Place the widget on an exact position
        /// widget->setPosition({40, 30});
        ///
        /// // Place the widget 50 pixels below another widget
        /// widget->setPosition(otherWidget->getPosition() + sf::Vector2f{0, otherWidget->getSize().y + 50});
        ///
        /// // Place the widget 50 pixels below another widget and automatically move it when the other widget moves
        /// widget->setPosition({tgui::bindLeft(otherWidget), tgui::bindBottom(otherWidget) + 50});
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param x  New x coordinate
        /// @param y  New y coordinate
        ///
        /// @see move, getPosition
        ///
        /// Usage examples:
        /// @code
        /// // Place the widget on an exact position
        /// widget->setPosition(40, 30);
        ///
        /// // Place the widget 50 pixels below another widget
        /// widget->setPosition(otherWidget->getPosition().x, otherWidget->getPosition().y + otherWidget->getSize().y + 50);
        ///
        /// // Place the widget 50 pixels below another widget and automatically move it when the other widget moves
        /// widget->setPosition(tgui::bindLeft(otherWidget), tgui::bindBottom(otherWidget) + 50);
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPosition(const Layout1d& x, const Layout1d& y)
        {
            setPosition({x, y});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief get the position of the widget
        ///
        /// @return Current position
        ///
        /// @see setPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2f getPosition() const
        {
            return m_position.getValue();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Move the widget by a given offset
        ///
        /// This function adds to the current position of the widget, unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// @code
        /// widget.setPosition(widget.getPosition() + offset);
        /// @endcode
        ///
        /// @param offset Offset
        ///
        /// @see setPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void move(const Layout& offset);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Move the widget by a given offset
        ///
        /// This function adds to the current position of the widget, unlike setPosition which overwrites it.
        /// Thus, it is equivalent to the following code:
        /// @code
        /// widget.setPosition(widget.getPosition().x + x, widget.getPosition().y + y);
        /// @endcode
        ///
        /// @param x  Horizontal offset
        /// @param y  Vertical offset
        ///
        /// @see setPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void move(const Layout1d& x, const Layout1d& y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the widget.
        ///
        /// @param size  Size of the widget
        ///
        /// Usage examples:
        /// @code
        /// // Give the widget an exact size
        /// widget->setSize({40, 30});
        ///
        /// // Make the widget 50 pixels higher than some other widget
        /// widget->setSize(otherWidget->getSize() + sf::Vector2f{0, 50});
        ///
        /// // Make the widget 50 pixels higher than some other widget and automatically resize it when the other widget resizes
        /// widget->setSize(tgui::bindSize(otherWidget) + sf::Vector2f{0, 50});
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the widget.
        ///
        /// @param width   Width of the widget
        /// @param height  Height of the widget
        ///
        /// Usage examples:
        /// @code
        /// // Give the widget an exact size
        /// widget->setSize(40, 30);
        ///
        /// // Make the widget 50 pixels higher than some other widget
        /// widget->setSize(otherWidget->getSize().x, otherWidget->getSize().y + 50);
        ///
        /// // Make the widget 50 pixels higher than some other widget and automatically resize it when the other widget resizes
        /// widget->setSize(tgui::bindWidth(otherWidget), tgui::bindHeight(otherWidget) + 50);
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout1d& width, const Layout1d& height)
        {
            setSize({width, height});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the widget.
        ///
        /// @return Size of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getSize() const
        {
            return m_size.getValue();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the entire size that the widget is using.
        ///
        /// This function will return a value equal or greater than what getSize returns.
        /// If the widget would e.g. have borders around it then this function will return the size, including these borders.
        ///
        /// @return Full size of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const
        {
            return getSize();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Scale the widget
        ///
        /// @param factors  Scale factors
        ///
        /// This function multiplies the current size of the widget with the given scale factors.
        /// Thus, it is equivalent to the following code:
        /// @code
        /// widget.setSize({getSize().x * factors.x, getSize().y * factors.y});
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void scale(const Layout& factors);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Scale the widget
        ///
        /// @param x  horizontal scale factor
        /// @param y  vertical scale factor
        ///
        /// This function multiplies the current size of the widget with the given scale factors.
        /// Thus, it is equivalent to the following code:
        /// @code
        /// widget.setSize(getSize().x * factors.x, getSize().y * factors.y);
        /// @endcode
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void scale(const Layout1d& x, const Layout1d& y);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the position
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updatePosition(bool forceUpdate = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Updates the size
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSize(bool forceUpdate = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Layout m_position;
        Layout m_size;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TRANSFORMABLE_HPP
