#ifndef MESSAGEBOX_HH_
# define MESSAGEBOX_HH_

# include "GUI/Layer.hh"
# include "GUI/String.hh"
# include "GUI/StringArea.hh"

// MessageBox - Layer since it should surpass all Drawables

class MessageBox : public Layer
{
  private:
    const static int		MESSAGEBOX_WIDTH = 200;
    const static int		MESSAGEBOX_HEIGHT = 150;
    const static int		TITLE_HEIGHT = 50;
    const static int		STATUS_BAR_HEIGHT = 60;

    Theme			*_theme;
    sf::RectangleShape		_background;
    // String			*_title;
    // StringArea			*_desc;

  public:
    MessageBox(const sf::String &title, const sf::String &desc);
    ~MessageBox();

    void			draw(sf::RenderWindow &window);
};

#endif


