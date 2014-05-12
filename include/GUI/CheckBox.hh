#ifndef CHECKBOX_HH_
# define CHECKBOX_HH_

# include "Menu.hh"
# include "Item.hh"
# include "String.hh"

// CheckBox
// The check box use the border color theme

class CheckBox : public Item
{
  private:
    String			*_string;
    bool			_is_checked;
    sf::RectangleShape		_border;
    sf::RectangleShape		_check;

    static const int		SIZE = 10;
    static const int		SPACE = 2;
    static const int		PADDING = 8;

  public:
    CheckBox(String *item, Theme *theme = jag::getTheme("CheckBoxTransparent"), float scale = 1.0f);
    ~CheckBox();

    // CheckBox
    bool			isChecked() const;
    void			setChecked(bool checked);

    void			setRect(const Rect &rec);
    void			draw(sf::RenderWindow &win);
    Rect			getRectRessource() const;
    void			designChanged();
    void			update();

    // Event
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif


