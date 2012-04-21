#pragma once

#include <SFML/Graphics.hpp>

class SplashScreen : public sf::Shape
{
	public:
		SplashScreen(int scrw, int scrh, const char* text);
		
	protected:
		virtual void Render(sf::RenderTarget& target) const;
		
	private:
		sf::String m_str;
};


		
