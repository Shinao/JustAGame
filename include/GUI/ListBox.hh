#ifndef TEXT_HH_
# define TEXT_HH_

# include "GUI/Menu.hh"

// ListBox : hide/show a menu

class ListBox : public Item
{
  private:
    Menu			*_menu;

  public:
    ListBox(Menu *menu, Theme *theme = jag::getCurrentTheme(), Alignment align = Left, float scale = 1.0f);
    ~ListBox();

    void			draw(sf::RenderWindow &win);
    void			update();
    Rect			getRectRessource() const;
    void			designChanged();
};

#endif
