#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "BaseObject.h"
#include "Texture.h"

/**
 * @class Text
 * @brief Represents a text object that can be rendered in the game.
 *
 * This class handles the representation and management of a text object, including setting its text, font, size, color, and filter mode.
 */
class Text : public BaseObject
{
public:
    /**
     * @brief Constructs a Text object with the specified text, font path, font size, color, and filter mode.
     * @param text The text to be displayed.
     * @param fontPath The path to the font file.
     * @param fontSize The size of the font.
     * @param color The color of the text. Defaults to black (0, 0, 0, 255).
     * @param filtermode The filter mode for the text texture. Defaults to GL_LINEAR.
     */
    Text(const std::string& text, const std::string& fontPath, int fontSize, const SDL_Color& color = { 0, 0, 0, 255 }, int filtermode = GL_LINEAR);

    /**
     * @brief Constructs a Text object with the specified text, font, font size, color, and filter mode.
     * @param text The text to be displayed.
     * @param font The font object to be used.
     * @param fontSize The size of the font.
     * @param color The color of the text. Defaults to black (0, 0, 0, 255).
     * @param filtermode The filter mode for the text texture. Defaults to GL_LINEAR.
     */
    Text(const std::string& text, TTF_Font* font, int fontSize, const SDL_Color& color = { 0, 0, 0, 255 }, int filtermode = GL_LINEAR);

    /**
     * @brief Deleted default constructor to prevent creating an uninitialized Text object.
     */
    Text() = delete;

    /**
     * @brief Destructor for the Text object.
     */
    ~Text();

    /**
     * @brief Sets the text to be displayed.
     * @param newText The new text to be displayed.
     */
    void SetText(const std::string& newText);

    /**
     * @brief Sets the font size of the text.
     * @param fontSize The new font size.
     */
    void SetFontSize(int fontSize);

    /**
     * @brief Sets the color of the text.
     * @param color The new color of the text.
     */
    void SetColor(const SDL_Color& color);

    /**
     * @brief Sets the filter mode for the text texture.
     * @param filtermode The new filter mode.
     */
    void SetFilterMode(int filtermode);

    /**
     * @brief Sets the font object to be used.
     * @param font The new font object.
     */
    void SetFont(TTF_Font* font);

    /**
     * @brief Gets the current text being displayed.
     * @return The current text.
     */
    const std::string& GetText() const;

    /**
     * @brief Updates the text texture. Automatically be called after setting new text or changing font attributes.
     */
    void UpdateText();

public:
    bool m_textNeedUpdate;

private:
    std::string m_text;         ///< The text to be displayed.
    std::string m_fontPath;     ///< The path to the font file.
    int m_fontSize;             ///< The size of the font.
    SDL_Color m_color;          ///< The color of the text.
    int m_filterMode;           ///< The filter mode for the text texture.

    TTF_Font* m_font = nullptr; ///< The font object.
};