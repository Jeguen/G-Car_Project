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


#ifndef TGUI_ANIMATED_PICTURE_HPP
#define TGUI_ANIMATED_PICTURE_HPP

#include <TGUI/ClickableWidget.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
namespace ext
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Animated picture widget
    ///
    /// Load multiple images and add then behind each other to create a simple animation or even a short movie.
    ///
    /// Signals:
    ///     - AnimationFinished
    ///     - Inherited signals from ClickableWidget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API AnimatedPicture : public ClickableWidget
    {
    public:

        typedef std::shared_ptr<AnimatedPicture> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const AnimatedPicture> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        AnimatedPicture();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~AnimatedPicture() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the AnimatedPicture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static AnimatedPicture::Ptr create()
        {
            return std::make_shared<AnimatedPicture>();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another animated picture
        ///
        /// @param picture  The other animated picture
        ///
        /// @return The new animated picture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static AnimatedPicture::Ptr copy(AnimatedPicture::ConstPtr picture);


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
        /// @brief Changes the size of the animated picture.
        ///
        /// @param size  The new size of the animated picture
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Load another image/frame from a file.
        ///
        /// @param filename       The filename of the image that you want to use as next frame.
        /// @param frameDuration  The amount of time that the frame will be displayed on the screen.
        ///                       When the duration is 0 (default) then the animation will be blocked at that frame.
        ///
        /// @throw Exception when the image could not be loaded.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addFrame(const std::string& filename, sf::Time frameDuration = sf::Time());


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Starts or resumes playing the animation.
        ///
        /// @see pause
        /// @see stop
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void play();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Pauses the animation.
        ///
        /// You can continue the animation with the start() function.
        ///
        /// @see play
        /// @see stop
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void pause();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Stops the animation.
        ///
        /// When calling start() after calling this function, the animation will restart from the first frame.
        ///
        /// @see play
        /// @see pause
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void stop();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the animation at a specific frame.
        ///
        /// @param frame  The frame that should be displayed
        ///
        /// The number is the index of the frame, so the first frame is number 0.
        ///
        /// @return True when the frame was selected.
        ///         False when the index was too high.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setFrame(unsigned int frame);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current displayed frame.
        ///
        /// @return Number of the frame that is currently displayed.
        ///
        /// The number is the index of the frame, so the first frame is number 0.
        /// If no frames were loaded then this function will return -1.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getCurrentFrame() const
        {
            return m_currentFrame;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the duration of the currently displayed frame.
        ///
        /// @return Duration of the frame that is currently displayed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::Time getCurrentFrameDuration() const
        {
            return m_frameDuration.empty() ? sf::Time{} : m_frameDuration[m_currentFrame];
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of frames in the animation.
        ///
        /// @return Number of frames
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getFrames() const
        {
            return m_textures.size();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a frame from the animation.
        ///
        /// @param frame  The number of the frame to remove
        ///
        /// The number is the index of the frame, so the first frame is number 0.
        ///
        /// @return True when the frame was removed.
        ///         False if the index was too high.
        ///
        /// @see removeAllFrames
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeFrame(unsigned int frame);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Remove all frames from the animation.
        ///
        /// @see removeFrame
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllFrames();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Turn the looping of the animation on or off.
        ///
        /// By default, when this function isn't called, the animation will not loop.
        ///
        /// @param loop  Should the animation start over from the beginning when it finishes?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setLooping(bool loop = true)
        {
            m_looping = loop;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the looping of the animation is on or off.
        ///
        /// By default, the animation will not loop.
        ///
        /// @return Will the animation start over from the beginning when it finishes?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getLooping() const
        {
            return m_looping;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the animation is still playing.
        ///
        /// @return Is the animation still playing?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool isPlaying() const
        {
            return m_playing;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the transparency of the widget.
        ///
        /// @param transparency  The transparency of the widget.
        ///                      0 is completely transparent, while 255 (default) means fully opaque.
        ///
        /// Note that this will only change the transparency of the images. The parts of the widgets that use a color will not
        /// be changed. You must change them yourself by setting the alpha channel of the color.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setTransparency(unsigned char transparency) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When the elapsed time changes then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void update() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<AnimatedPicture>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::vector<Texture>  m_textures;
        std::vector<sf::Time> m_frameDuration;

        int m_currentFrame = -1;

        bool m_playing = false;
        bool m_looping = false;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // ext
} // tgui

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_ANIMATED_PICTURE_HPP

