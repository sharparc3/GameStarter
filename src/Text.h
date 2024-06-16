#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "BaseObject.h"
#include "Texture.h"

class Text : public BaseObject
{
public:
    Text(const std::string& text, const std::string& fontPath, int fontSize, const SDL_Color& color = { 0, 0, 0, 255 }, int filtermode = GL_LINEAR);
    Text(const std::string& text, TTF_Font* font, int fontSize, const SDL_Color& color = { 0, 0, 0, 255 }, int filtermode = GL_LINEAR);
    Text() = delete;
    ~Text();

    void SetText(const std::string& newText);
    void SetFontSize(int fontSize);
    void SetColor(const SDL_Color& color);
    void SetFilterMode(int filtermode);
    void SetFont(TTF_Font* font);
    const std::string& GetText() const;
    void UpdateText();

public:
    bool m_textNeedUpdate;

private:
    std::string m_text;
    std::string m_fontPath;
    int m_fontSize;
    SDL_Color m_color;
    int m_filterMode;

    TTF_Font* m_font = nullptr;
};