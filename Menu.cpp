#include "Menu.h"
#include <stdio.h>

Menu::Menu() : sf::Drawable()
{
	Button* button = new Button(0, 0, 100, 30, "RESTART LEVEL", Retry, true, true);
	m_buttons.push_back(button);
	
	m_nextButton = new Button(0, 35, 100, 30, "NEXT LEVEL", Next, false);
	m_buttons.push_back(m_nextButton);
	
	button = new Button(0, 70, 100, 30, "EXIT GAME", Quit, true, true);
	m_buttons.push_back(button);
	
	m_yesButton = new Button(105, 0, 100, 30, "YES", Yes, true);
	m_noButton = new Button(210, 0, 100, 30, "NO", No, true);

	m_resumeButton = new Button(0, 105, 100, 30, "RESUME GAME", Resume, true);
	
	m_confirmingAction = false;
	m_active = false;
}

void Menu::resize(int width, int height)
{

}

void Menu::setNextLevelButtonEnabled(bool enabled)
{
	m_nextButton->setEnabled(enabled);
}

void Menu::setActive(bool active)
{
	if(!m_confirmingAction)
	{
		m_active = active;
	}
	else
	{
		m_confirmingAction = false;
	}
}

bool Menu::hasAction()
{
	return (m_lastAction != Nothing);
}

MenuAction Menu::getAction()
{
	MenuAction tmp = m_lastAction;
	m_lastAction = Nothing;
	return tmp;
}	

void Menu::keyPress(sf::Key::Code key)
{
	
}

void Menu::mouseHover(int x, int y)
{
	if(m_active)
	{
		
		if(m_confirmingAction)
		{
			if(x > m_yesButton->left() && x < m_yesButton->right() && y > m_yesButton->top() && y < m_yesButton->bottom())
			{
				m_yesButton->setHover(true);
				return;
			}
			else
			{	
				m_yesButton->setHover(false);
			}
		
			if(x > m_noButton->left() && x < m_noButton->right() && y > m_noButton->top() && y < m_noButton->bottom())
			{
				m_noButton->setHover(true);
				return;
			}
			else
			{	
				m_noButton->setHover(false);
			}
		}
		else
		{
			if(x > m_resumeButton->left() && x < m_resumeButton->right() && y > m_resumeButton->top() && y < m_resumeButton->bottom())
			{
				m_resumeButton->setHover(true);
				return;
			}
			else
			{	
				m_resumeButton->setHover(false);
			}
		
			for(int i = 0; i < m_buttons.size(); i++)
			{
				if(x > m_buttons[i]->left() && x < m_buttons[i]->right() && y > m_buttons[i]->top() && y < m_buttons[i]->bottom())
				{
					m_buttons[i]->setHover(true);
					return;
				}
				else
				{
					m_buttons[i]->setHover(false);
				}
			}
		}
	}
}	

void Menu::mouseClick(int x, int y)
{
	if(m_confirmingAction)
	{
		if(x > m_yesButton->left() && x < m_yesButton->right() && y > m_yesButton->top() && y < m_yesButton->bottom())
		{
			m_lastAction = m_actionWaitingForConfirm;
			m_confirmingAction = false;
		}
		else if(x > m_noButton->left() && x < m_noButton->right() && y > m_noButton->top() && y < m_noButton->bottom())
		{
			m_actionWaitingForConfirm = Nothing;
			m_confirmingAction = false;
		}
	}
	else
	{
		for(int i = 0; i < m_buttons.size(); i++)
		{
			if(m_buttons[i]->enabled() && x > m_buttons[i]->left() && x < m_buttons[i]->right() && y > m_buttons[i]->top() && y < m_buttons[i]->bottom())
			{
				if(m_buttons[i]->wantsConfirmation())
				{
					m_actionWaitingForConfirm = m_buttons[i]->action();
					m_yesButton->setY(m_buttons[i]->top());
					m_noButton->setY(m_buttons[i]->top());
					m_confirmingAction = true;
				}
				else
				{
					m_lastAction = m_buttons[i]->action();
				}
				
				return;
			}
		}
	
		if(x > m_resumeButton->left() && x < m_resumeButton->right() && y > m_resumeButton->top() && y < m_resumeButton->bottom())
		{
			m_lastAction = m_resumeButton->action();
			return;
		}
	}
}

void Menu::Render(sf::RenderTarget& target) const
{
	if(m_confirmingAction)
	{
		target.Draw(*m_yesButton);
		target.Draw(*m_noButton);
	}
	
	for(int i = 0; i < m_buttons.size(); i++)
	{
		target.Draw(*m_buttons[i]);
	}

	target.Draw(*m_resumeButton);
}

///////////////////////////////////
///          Button
///////////////////////////////////

Button::Button(int x, int y, int width, int height, const char* text, MenuAction action, bool enabled, bool confirmation) : sf::Shape()
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	
	m_text = text;
	m_confirm = confirmation;
	
	m_enabled = enabled;
	
	if(m_enabled)
		SetColor(sf::Color(200, 200, 200));
	else
		SetColor(sf::Color(100, 100, 100));
	
	m_str = sf::String(text, sf::Font::GetDefaultFont(), 12.0);
	m_str.SetColor(sf::Color(50, 50, 50));
	m_str.SetX(m_x);
	m_str.SetY(m_y);
	
	m_action = action;
	
	EnableFill(true);
	AddPoint(x, y);
	AddPoint(x+width, y);
	AddPoint(x+width, y+height);
	AddPoint(x, y+height);
}

void Button::setEnabled(bool enabled)
{
	m_enabled = enabled;
	
	if(m_enabled)
		SetColor(sf::Color(200, 200, 200));
	else
		SetColor(sf::Color(100, 100, 100));
}

void Button::setText(const char* text)
{
	m_str.SetText(text);
	m_text = text;
}

void Button::setHover(bool hover)
{
	if(m_enabled)
	{
		if(hover)
		{
			SetColor(sf::Color(255, 255, 255));
		}
		else
		{
			SetColor(sf::Color(200, 200, 200));
		}
	}
	else
	{
		SetColor(sf::Color(100, 100, 100));
	}
}

void Button::Render(sf::RenderTarget& target) const
{
	sf::Shape::Render(target);
	target.Draw(m_str);
}

void Button::setPos(int x, int y)
{
	m_x = x;
	m_y = y;
	
	m_str.SetX(m_x);
	m_str.SetY(m_y);
	
	SetX(m_x);
	SetY(m_y);
}

void Button::setX(int x)
{
	m_x = x;
	SetX(x);
}

void Button::setY(int y)
{
	m_y = y;
	SetY(y);
}





