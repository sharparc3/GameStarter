#include "Text.h"
#include <string>
#include <glad/glad.h>
#include "Config.h"
#include "ResourceManager.h"
#include "Logger.h"
#include "IDGenerator.h"

Text::Text(const std::string& text, const std::string& fontPath, int fontSize, const SDL_Color& color, int filtermode) :
	BaseObject(nullptr, nullptr), m_text(text), m_fontPath(fontPath), m_fontSize(fontSize), m_color(color), m_filterMode(filtermode)
{
	m_objectId = getUniqueID();
	std::string path_to_font = ResourcesPath::FONT + fontPath;
	m_font = TTF_OpenFont(path_to_font.c_str(), m_fontSize);
	if (!m_font)
	{
		LogError("Error loading font: %s", m_font);
		return;
	}
	m_mesh = ResourceManager::GetInstance()->GetMesh("quad_center.nfg");
	if (!m_mesh)
	{
		ResourceManager::GetInstance()->LoadMesh("quad_center.nfg");
		m_mesh = ResourceManager::GetInstance()->GetMesh("quad_center.nfg");
	}

	m_needCalculateWorldMatrix = true;
	m_textNeedUpdate = true;
	m_objectType = "text";

	UpdateText();
}

Text::Text(const std::string& text, TTF_Font* font, int fontSize, const SDL_Color& color, int filtermode) :
	BaseObject(nullptr, nullptr), m_text(text), m_fontSize(fontSize), m_color(color), m_filterMode(filtermode), m_font(font)
{
	m_objectId = getUniqueID();
	m_mesh = ResourceManager::GetInstance()->GetMesh("quad_center.nfg");
	if (!m_mesh)
	{
		ResourceManager::GetInstance()->LoadMesh("quad_center.nfg");
		m_mesh = ResourceManager::GetInstance()->GetMesh("quad_center.nfg");
	}

	m_needCalculateWorldMatrix = true;
	m_textNeedUpdate = true;
	m_objectType = "text";

	UpdateText();
}

Text::~Text()
{
	m_texture = nullptr;
	m_mesh = nullptr;
}

void Text::SetText(const std::string& newText)
{
	m_text = newText;
	m_textNeedUpdate = true;
	UpdateText();
}

void Text::SetFontSize(int fontSize)
{
	m_fontSize = fontSize;
	m_textNeedUpdate = true;
	UpdateText();
}

void Text::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_textNeedUpdate = true;
	UpdateText();
}

void Text::SetFilterMode(int filtermode)
{
	if (filtermode == GL_LINEAR || filtermode == GL_NEAREST)
	{
		m_filterMode = filtermode;
		m_textNeedUpdate = true;
	}
	UpdateText();
}

void Text::SetFont(TTF_Font* font)
{
	m_font = font;
	m_textNeedUpdate = true;
	UpdateText();
}

const std::string& Text::GetText() const
{
	return m_text;
}

void Text::UpdateText()
{
	if (m_needCalculateWorldMatrix)
	{
		RecalculateWorldMatrix();
	}

	if (!m_textNeedUpdate)
	{
		return;
	}

	if (m_font == nullptr || m_mesh == nullptr)
	{
		LogError("Error create text texture: font or mesh is null");
		return;
	}

	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(m_font, m_text.c_str(), m_color, 0);
	if (textSurface == nullptr) 
	{
		LogError("Rendering font error: %s", TTF_GetError());
		return;
	}

	if (m_texture == nullptr)
	{
		// Create a new texture
		GLuint texture_id;
		m_texture = std::make_shared<Texture>();
		glGenTextures(1, &texture_id);
		m_texture->m_iTextureID = texture_id;
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else 
	{
		// Update existing texture
		glBindTexture(GL_TEXTURE_2D, m_texture->m_iTextureID);
	}

	// temporary fix
	Uint32 len = textSurface->w * textSurface->format->BytesPerPixel;
	Uint8* src = static_cast<Uint8*>(textSurface->pixels);
	Uint8* dst = static_cast<Uint8*>(textSurface->pixels);
	for (int i = 0; i < textSurface->h; i++) 
	{
		SDL_memmove(dst, src, len);
		dst += len;
		src += textSurface->pitch;
	}
	textSurface->pitch = len;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textSurface->w, textSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, textSurface->pixels);
	SetPosition(0.f, 0.f);
	SetSize((float)textSurface->w, (float)textSurface->h);
	SetRotation(0.f);

	if (m_needCalculateWorldMatrix)
	{
		RecalculateWorldMatrix();
	}

	SDL_FreeSurface(textSurface);

	m_textNeedUpdate = false;
}
