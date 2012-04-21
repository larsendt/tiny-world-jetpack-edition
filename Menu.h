#pragma once

#include <GL/gl.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

enum MenuAction {
	Nothing,
	Yes,
	No,
	Quit
};

class Button;

class Menu : public sf::Drawable
{
	public:
		Menu();
		void mouseClick(int x, int y);
		void mouseHover(int x, int y);
		void keyPress(sf::Key::Code);
		
		void setActive(bool active);
		bool isActive() { return m_active; }
		bool hasAction();
		MenuAction getAction();
		
		
	protected:
		virtual void Render(sf::RenderTarget& target) const;

	private:
		bool m_active;	
		bool m_confirmingAction;
		MenuAction m_actionWaitingForConfirm;
		MenuAction m_lastAction;	
		Button* m_resumeButton;
		Button* m_yesButton;
		Button* m_noButton;
		std::vector<Button*> m_buttons;
};


class Button : public sf::Shape
{
	public:
		Button(int x, int y, int width, int height, const char* text, MenuAction action, bool confirmation = false);
		
		void setText(const char* text);
		const char* text() { return m_text; }
		
		MenuAction action() { return m_action; }
		bool wantsConfirmation() { return m_confirm; }
		
		void setHover(bool hover);
		
		int left() { return m_x; }
		int right() { return m_x+m_width; }
		int top() { return m_y; }
		int bottom() { return m_y+m_height; }
		
		void setPos(int x, int y);
		void setX(int x);
		void setY(int y);
		
	protected:
		virtual void Render(sf::RenderTarget& target) const;
	
	private:
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		sf::String m_str;
		const char* m_text;
		MenuAction m_action;
		bool m_confirm;
};

	
