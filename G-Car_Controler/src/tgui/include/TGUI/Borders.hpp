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


#ifndef TGUI_BORDERS_HPP
#define TGUI_BORDERS_HPP

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Borders
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders() :
            left  (0),
            top   (0),
            right (0),
            bottom(0)
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor that initializes the borders
        ///
        /// @param leftBorderWidth    Width of the left border
        /// @param topBorderHeight    Height of the top border
        /// @param rightBorderWidth   Width of the right border
        /// @param bottomBorderHeight Height of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders(float leftBorderWidth, float topBorderHeight, float rightBorderWidth, float bottomBorderHeight) :
            left  (leftBorderWidth),
            top   (topBorderHeight),
            right (rightBorderWidth),
            bottom(bottomBorderHeight)
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor that initializes the borders
        ///
        /// @param width   Width of the left and right borders
        /// @param height  Height of the top and bottom borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders(float width, float height) :
            left  (width),
            top   (height),
            right (width),
            bottom(height)
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor that initializes the borders
        ///
        /// @param size  Size of the borders on each side
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Borders(float size) :
            left  (size),
            top   (size),
            right (size),
            bottom(size)
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Compare two borders
        ///
        /// @param borders  The borders to compare with this instance
        ///
        /// @return Whether the borders are equal or not.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(const Borders& borders) const
        {
            return (left == borders.left) && (top == borders.top) && (right == borders.right) && (bottom == borders.bottom);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Compare two borders
        ///
        /// @param borders  The borders to compare with this instance
        ///
        /// @return Whether the borders are equal or not.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool operator!=(const Borders& borders) const
        {
            return !(*this == borders);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Width of the left border
        float left;

        /// Height of the top border
        float top;

        /// Width of the right border
        float right;

        /// Height of the bottom border
        float bottom;
    };

    using Padding = Borders;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Parent class for every widget that has borders.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API WidgetBorders
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~WidgetBorders() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the borders.
        ///
        /// @param borders  Size of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(const Borders& borders)
        {
            m_borders = borders;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the borders.
        ///
        /// @param leftBorder    Width of the left border
        /// @param topBorder     Height of the top border
        /// @param rightBorder   Width of the right border
        /// @param bottomBorder  Height of the bottom border
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(float leftBorder,  float topBorder, float rightBorder, float bottomBorder)
        {
            setBorders({leftBorder, topBorder, rightBorder, bottomBorder});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the borders.
        ///
        /// @param width   Width of the left and right borders
        /// @param height  Height of the top and bottom borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(float width,  float height)
        {
            setBorders({width, height});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the borders as a tgui::Borders.
        ///
        /// @return border sizes
        ///
        /// The first element will be the size of the left border, the seconds is the size of the top border,
        /// the third is the size of the right border and the the last constains the size of the bottom border.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Borders getBorders() const
        {
            return m_borders;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        Borders m_borders;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Parent class for every widget that has padding.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API WidgetPadding
    {
      public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~WidgetPadding() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the padding.
        ///
        /// @param padding  Size of the padding
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPadding(const Padding& padding)
        {
            m_padding = padding;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the padding.
        ///
        /// @param leftPadding    Width of the left padding
        /// @param topPadding     Height of the top padding
        /// @param rightPadding   Width of the right padding
        /// @param bottomPadding  Height of the bottom padding
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPadding(float leftPadding,  float topPadding, float rightPadding, float bottomPadding)
        {
            setPadding({leftPadding, topPadding, rightPadding, bottomPadding});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the padding.
        ///
        /// @param width   Width of the left and right padding
        /// @param height  Height of the top and bottom padding
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPadding(float width,  float height)
        {
            setPadding({width, height});
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the padding.
        ///
        /// @return padding sizes
        ///
        /// The first element will be the size of the left padding, the seconds is the size of the top padding,
        /// the third is the size of the right padding and the the last constains the size of the bottom padding.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Padding getPadding() const
        {
            return m_padding;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      protected:

        Padding m_padding;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_BORDERS_HPP
