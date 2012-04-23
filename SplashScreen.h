#pragma once

#include <SFML/Graphics.hpp>

class SplashScreen : public sf::Shape
{
	public:
		SplashScreen(int scrw, int scrh, const char* text);
		void resize(int scrw, int scrh);
		void setText(const char* text);
		
	protected:
		virtual void Render(sf::RenderTarget& target) const;
		
	private:
		sf::String m_str;
		int m_w;
		int m_h;
};


		
