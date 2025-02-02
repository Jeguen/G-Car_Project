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


#ifndef TGUI_COMBO_BOX_HPP
#define TGUI_COMBO_BOX_HPP


#include <TGUI/ListBox.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    class ComboBoxRenderer;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Combo box widget
    ///
    /// Signals:
    ///     - ItemSelected (a new item was selected)
    ///         * Optional parameter sf::String: Name of the item (the text that is visible)
    ///         * Optional parameters sf::String and sf::String: Name and id of the item
    ///         * Uses Callback member 'text' and 'itemId'
    ///
    ///     - Inherited signals from Widget
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ComboBox : public Widget
    {
    public:

        typedef std::shared_ptr<ComboBox> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const ComboBox> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Copy constructor
        ///
        /// @param copy  Instance to copy
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBox(const ComboBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~ComboBox() {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Overload of assignment operator
        ///
        /// @param right  Instance to assign
        ///
        /// @return Reference to itself
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBox& operator= (const ComboBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Create the combo box
        ///
        /// @param themeFileFilename  Filename of the theme file.
        /// @param section            The section in the theme file to read.
        ///
        /// @throw Exception when the theme file could not be opened.
        /// @throw Exception when the theme file did not contain the requested section with the needed information.
        /// @throw Exception when one of the images, described in the theme file, could not be loaded.
        ///
        /// When an empty string is passed as filename, the built-in white theme will be used.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ComboBox::Ptr create(const std::string& themeFileFilename = "", const std::string& section = "ComboBox");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another combo box
        ///
        /// @param comboBox  The other combo box
        ///
        /// @return The new combo box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ComboBox::Ptr copy(ComboBox::ConstPtr comboBox);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Reference to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<ComboBoxRenderer> getRenderer() const
        {
            return std::static_pointer_cast<ComboBoxRenderer>(m_renderer);
        }


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
        /// @brief Changes the size of the combo box.
        ///
        /// This size does not include the borders.
        ///
        /// @param size   The new size of the combo box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the full size of the combo box.
        ///
        /// The size returned by this function includes the borders.
        ///
        /// @return The full size of the combo box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual sf::Vector2f getFullSize() const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the number of items that are displayed in the list.
        ///
        /// @param nrOfItemsInListToDisplay  The maximum number of items to display when the list of items is shown.
        ///
        /// When there is no scrollbar then this is the maximum number of items.
        /// If there is one, then it will only become visible when there are more items than this number.
        ///
        /// When set to zero then all items are shown (then there will never be a scrollbar).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemsToDisplay(unsigned int nrOfItemsInListToDisplay);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the number of items that are displayed in the list.
        ///
        /// @return The maximum number of items to display when the list of items is shown.
        ///
        /// When there is no scrollbar then this is the maximum number of items.
        /// If there is one, then it will only become visible when there are more items than this number.
        ///
        /// When set to zero then all items are shown (then there will never be a scrollbar).
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemsToDisplay() const
        {
            return m_nrOfItemsToDisplay;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds an item to the list, so that it can be selected later.
        ///
        /// @param itemName  The name of the item you want to add (this is the text that will be displayed inside the combo box)
        /// @param id        Optional unique id given to this item for the purpose to later identifying this item.
        ///
        /// @return
        ///         - true when the item when it was successfully added
        ///         - false when the combo box wasn't loaded correctly
        ///         - false when the list is full (you have set a maximum item limit and you are trying to add more items)
        ///         - false when there is no scrollbar and you try to have more items than the number of items to display
        ///
        /// @see setMaximumItems
        /// @see setItemsToDisplay
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool addItem(const sf::String& itemName, const sf::String& id = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects an item from the list.
        ///
        /// When adding items to the combo box with the addItem function, none of them will be selected.
        /// If you don't want the combo box to stay empty until the user selects something, but you want a default item instead,
        /// then you can use this function to select an item.
        ///
        /// @param itemName  The item you want to select
        ///
        /// In case the names are not unique, the first item with that name will be selected.
        ///
        /// @return
        ///         - true on success
        ///         - false when none of the items matches the name
        ///
        /// @see setSelectedItemById
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects an item from the list.
        ///
        /// When adding items to the combo box with the addItem function, none of them will be selected.
        /// If you don't want the combo box to stay empty until the user selects something, but you want a default item instead,
        /// then you can use this function to select an item.
        ///
        /// @param id  Unique id passed to addItem
        ///
        /// In case the id would not be unique, the first item with that id will be selected.
        ///
        /// @return
        ///         - true on success
        ///         - false when none of the items has the given id
        ///
        /// @see setSelectedItem
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItemById(const sf::String& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Deselects the selected item.
        ///
        /// The combo box will be empty after this function is called.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselectItem();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the item from the list with the given name.
        ///
        /// @param itemName  The item to remove
        ///
        /// In case the names are not unique, only the first item with that name will be removed.
        ///
        /// @return
        ///        - true when the item was removed
        ///        - false when the name did not match any item
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItem(const sf::String& itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the item that were added with the given id.
        ///
        /// @param id  Id that was given to the addItem function.
        ///
        /// In case the id is not unique, only the first item with that id will be removed.
        ///
        /// @return
        ///        - true when the item was removed
        ///        - false when there was no item with the given id
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItemById(const sf::String& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all items from the list.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the item name of the item with the given id.
        ///
        /// @param id  The id of the item that was given to it when it was added
        ///
        /// In case the id is not unique, the first item with that id will be returned.
        ///
        /// @return The requested item, or an empty string when no item matches the id
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getItemById(const sf::String& id) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the currently selected item.
        ///
        /// @return The selected item.
        ///         When no item was selected then this function will return an empty string.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelectedItem() const
        {
            return m_listBox->getSelectedItem();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Get the id of the selected item.
        ///
        /// @return The id of the selected item, which was the optional id passed to the addItem function.
        ///         When no item was selected then this function returns 0.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelectedItemId() const
        {
            return m_listBox->getSelectedItemId();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes an item with name originalValue to newValue.
        ///
        /// @param originalValue The name of the item which you want to change
        /// @param newValue      The new name for that item
        ///
        /// In case the names are not unique, only the first item with that name will be changed.
        ///
        /// @return
        ///        - true when the item was changed
        ///        - false when none of the items had the given name
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeItem(const sf::String& originalValue, const sf::String& newValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the name of an item with the given id to newValue.
        ///
        /// @param id       The unique id of the item which you want to change
        /// @param newValue The new name for that item
        ///
        /// In case the id is not unique, only the first item with that id will be changed.
        ///
        /// @return
        ///        - true when the item was changed
        ///        - false when none of the items had the given id
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeItemById(const sf::String& id, const sf::String& newValue);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of items in the list box
        ///
        /// @return Number of items inside the list box
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemCount()
        {
            return m_listBox->getItemCount();
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the scrollbar.
        ///
        /// When there are too many items to fit in the list then the items will be removed.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum items that the combo box can contain.
        ///
        /// @param maximumItems  The maximum items inside the combo box.
        ///                      When the maximum is set to 0 then the limit will be disabled.
        ///
        /// If no scrollbar was loaded then there is always a limitation because there will be a limited space for the items.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumItems(unsigned int maximumItems = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum items that the combo box can contain.
        ///
        /// @return The maximum items inside the list.
        ///         If the function returns 0 then there is no limit.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumItems() const;


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
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMouseReleased(float x, float y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseWheelMoved(int delta, int x, int y) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called when the widget is added to a container.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void initialize(Container *const container) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() override
        {
            return std::make_shared<ComboBox>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Shows the list of items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void showListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Hides the list of items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void hideListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Initialize the internal list box
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void initListBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Called by the internal ListBox when a different item is selected.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void newItemSelectedCallbackFunction();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Called by the internal ListBox when it gets unfocused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void listBoxUnfocusedCallbackFunction();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        // The number of items to display. If there is a scrollbar then you can scroll to see the other.
        // If there is no scrollbar then this will be the maximum amount of items.
        unsigned int m_nrOfItemsToDisplay = 0;

        // Internally a list box is used to store all items
        ListBox::Ptr m_listBox = ListBox::create();

        Label m_text;

        friend class ComboBoxRenderer;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API ComboBoxRenderer : public WidgetRenderer, public WidgetBorders, public WidgetPadding
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructor
        ///
        /// @param comboBox  The combo box that is connected to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBoxRenderer(ComboBox* comboBox) : m_comboBox{comboBox} {}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Dynamically change a property of the renderer, without even knowing the type of the widget.
        ///
        /// This function should only be used when you don't know the type of the widget.
        /// Otherwise you can make a direct function call to make the wanted change.
        ///
        /// @param property  The property that you would like to change
        /// @param value     The new value that you like to assign to the property
        /// @param rootPath  Path that should be placed in front of any resource filename
        ///
        /// @throw Exception when the property doesn't exist for this widget.
        /// @throw Exception when the value is invalid for this property.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setProperty(std::string property, const std::string& value, const std::string& rootPath = getResourcePath()) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background image
        ///
        /// When this image is set, the background color property will be ignored.
        ///
        /// Pass an empty string to unset the image, in this case the background color property will be used again.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundImage(const std::string& filename,
                                const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the arrow up image
        ///
        /// When this image and the down image are set, the arrow color properties will be ignored.
        ///
        /// Pass an empty string to unset the image.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowUpNormalImage(const std::string& filename,
                                   const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                   const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                   bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the arrow down image
        ///
        /// When this image and the up image are set, the arrow color properties will be ignored.
        ///
        /// Pass an empty string to unset the image.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowDownNormalImage(const std::string& filename,
                                     const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                     const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                     bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the arrow up image for when the mouse is on top of the combo box
        ///
        /// This image is ignored when the up and down normal images are not set.
        ///
        /// Pass an empty string to unset the image.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowUpHoverImage(const std::string& filename,
                                  const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                  const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                  bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the arrow down image for when the mouse is on top of the combo box
        ///
        /// This image is ignored when the up and down normal images are not set.
        ///
        /// Pass an empty string to unset the image.
        ///
        /// @param filename   Filename of the image to load.
        /// @param partRect   Load only part of the image. Don't pass this parameter if you want to load the full image.
        /// @param middlePart Choose the middle part of the image for 9-slice scaling (relative to the part defined by partRect)
        /// @param repeated   Should the image be repeated or stretched when the size is bigger than the image?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowDownHoverImage(const std::string& filename,
                                    const sf::IntRect& partRect = sf::IntRect(0, 0, 0, 0),
                                    const sf::IntRect& middlePart = sf::IntRect(0, 0, 0, 0),
                                    bool repeated = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color that will be used inside the combo box.
        ///
        /// @param backgroundColor  The color of the background of the combo box
        ///
        /// This color will be ignored when a background image was set.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBackgroundColor(const sf::Color& backgroundColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the arrow that will be used inside the combo box.
        ///
        /// @param color  The color of the arrow background of the combo box
        ///
        /// This will overwrite the color in both normal and hover states.
        ///
        /// This color will be ignored when a up and down image were loaded for the normal state.
        ///
        /// @see setArrowBackgroundColorNormal
        /// @see setArrowBackgroundColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowBackgroundColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the arrow when the mouse is not on top of the combo box
        ///
        /// @param color  The color of the arrow background in normal state
        ///
        /// This color will be ignored when a up and down image were loaded for the normal state.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowBackgroundColorNormal(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the background color of the arrow when the mouse is standing on top of the combo box
        ///
        /// @param color  The color of the arrow background in hover state
        ///
        /// This color will be ignored when a up and down image were loaded for the normal state.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowBackgroundColorHover(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color of the arrow that will be used inside the combo box.
        ///
        /// @param color  The color of the arrow of the combo box
        ///
        /// This will overwrite the color in both normal and hover states.
        ///
        /// This color will be ignored when a up and down image were loaded for the normal state.
        ///
        /// @see setArrowColorNormal
        /// @see setArrowColorHover
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowColor(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color of the arrow when the mouse is not on top of the combo box
        ///
        /// @param color  The color of the arrow in normal state
        ///
        /// This color will be ignored when a up and down image were loaded for the normal state.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowColorNormal(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the color of the arrow when the mouse is standing on top of the combo box
        ///
        /// @param color  The color of the arrow in hover state
        ///
        /// This color will be ignored when a up and down image were loaded for the normal state.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setArrowColorHover(const sf::Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the text color that will be used inside the combo box.
        ///
        /// @param textColor  The color of the text
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextColor(const sf::Color& textColor);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Set the border color text that will be used inside the combo box.
        ///
        /// @param borderColor  The color of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorderColor(const sf::Color& borderColor);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the font of the items.
        ///
        /// When you don't call this function then the global font will be use.
        /// This global font can be changed with the setGlobalFont function from the parent.
        ///
        /// @param font  The new font.
        ///
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(std::shared_ptr<sf::Font> font);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the borders.
        ///
        /// @param borders  The size of the borders
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setBorders(const Borders& borders) override;
        using WidgetBorders::setBorders;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the padding of the list box.
        ///
        /// This padding will be scaled together with the background image.
        /// If there is no background image, or when 9-slice scaling is used, the padding will be exactly what you pass here.
        ///
        /// @param padding  The padding width and height
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setPadding(const Padding& padding) override;
        using WidgetPadding::setPadding;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer of the list box
        ///
        /// @return The list box used to display all the items
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<ListBoxRenderer> getListBox() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draws the widget on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the padding, which is possibly scaled with the background image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Padding getScaledPadding() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual std::shared_ptr<WidgetRenderer> clone(Widget* widget) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ComboBoxRenderer(const ComboBoxRenderer&) = default;
        ComboBoxRenderer& operator=(const ComboBoxRenderer&) = delete;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        ComboBox* m_comboBox;

        Texture   m_backgroundTexture;

        Texture   m_textureArrowUpNormal;
        Texture   m_textureArrowUpHover;
        Texture   m_textureArrowDownNormal;
        Texture   m_textureArrowDownHover;

        sf::Color m_arrowBackgroundColorNormal = {245, 245, 245};
        sf::Color m_arrowBackgroundColorHover  = {255, 255, 255};
        sf::Color m_arrowColorNormal           = { 60,  60,  60};
        sf::Color m_arrowColorHover            = {  0,   0,   0};

        friend class ComboBox;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_COMBO_BOX_HPP

