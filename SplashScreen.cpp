#include "SplashScreen.h"

SplashScreen::SplashScreen(int scrw, int scrh, const char* text) 
{
	m_w = 200;
	m_h = 50;
	
	AddPoint((scrw/2)-(m_w/2), (scrh/2)-(m_h/2));
	AddPoint((scrw/2)+(m_w/2), (scrh/2)-(m_h/2));
	AddPoint((scrw/2)+(m_w/2), (scrh/2)+(m_h/2));
	AddPoint((scrw/2)-(m_w/2), (scrh/2)+(m_h/2));
	EnableFill(true);
	
	SetColor(sf::Color(255, 255, 255));
	
	m_str = sf::String(text, sf::Font::GetDefaultFont(), 15.0);
	m_str.SetColor(sf::Color(50, 50, 50));
	m_str.SetX((scrw/2)-(m_w/2) + 10);
	m_str.SetY((scrh/2)-(m_h/2) + 10);
}

void SplashScreen::setText(const char* text)
{
	m_str.SetText(text);
}

void SplashScreen::resize(int scrw, int scrh)
{
	SetX(-(m_w/2));
	SetY(-(m_h/2));
}

void SplashScreen::Render(sf::RenderTarget& target) const 
{
	sf::Shape::Render(target);
	target.Draw(m_str);
}
