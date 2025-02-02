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


#ifndef TGUI_CANVAS_HPP
#define TGUI_CANVAS_HPP


#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Canvas : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<Canvas> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Canvas> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Canvas();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        ///
        /// @param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Canvas(const Canvas& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~Canvas() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        ///
        /// @param right  Instance to assign
        ///
        /// @return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Canvas& operator= (const Canvas& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the Canvas
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Canvas::Ptr create(const sf::Vector2f& size = {100, 100});


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another canvas
        ///
        /// @param canvas  The other canvas
        ///
        /// @return The new canvas
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Canvas::Ptr copy(Canvas::ConstPtr canvas);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the position of the widget
        ///
        /// This function completely overwrites the previous position.
        /// See the move function to apply an offset based on the previous position instead.
        /// The default position of a transformable widget is (0, 0).
        ///
        /// @param position  New position
        ///
        /// @see move, getPosition
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPosition(const Layout& position) override;
        using Transformable::setPosition;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the widget.
        ///
        /// @param size  The new size of the widget
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Clear the entire canvas with a single color
        ///
        /// This function is usually called once every frame, to clear the previous contents of the canvas.
        ///
        /// @param color Fill color to use to clear the canvas
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void clear(const sf::Color& color = sf::Color(0, 0, 0, 255));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw a drawable object to the canvas
        ///
        /// @param drawable Object to draw
        /// @param states   Render states to use for drawing
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw primitives defined by an array of vertices
        ///
        /// @param vertices    Pointer to the vertices
        /// @param vertexCount Number of vertices in the array
        /// @param type        Type of primitives to draw
        /// @param states      Render states to use for drawing
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(const sf::Vertex* vertices, unsigned int vertexCount,
                  sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Update the contents of the canvas
        ///
        /// This function updates the canvas with what has been drawn so far. Like for windows, calling this
        /// function is mandatory at the end of rendering. Not calling
        /// it may leave the texture in an undefined state.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void display();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<Canvas>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        sf::RenderTexture m_renderTexture;
        sf::Sprite        m_sprite;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CANVAS_HPP
