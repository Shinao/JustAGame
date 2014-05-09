#ifndef TABLE_HH_
# define TABLE_HH_

# include "Item.hh"
# include "Menu.hh"
# include "DrawableManager.hh"
# include <vector>

// Table : multi menu

class Table : public Drawable, public DrawableManager
{
  private:
    std::vector<Menu *>		_menus;

    void			init(int nb_column);

  public:
    Table(int nb_row, Theme *theme = jag::getCurrentTheme());
    ~Table();

    void			addRow(const std::vector<Item *> &items);

    void			draw(sf::RenderWindow &win);
    void			update();
    void			designChanged();
    Rect			getRect() const;
    void			setRect(const Rect &rec);

    Item			*getSelectedItem(int row);
    int				getSelectedIndex() const;
    void			unselect();

    // Event
    virtual void		mouseCaught(int x, int y);
    virtual void		mouseLeft();
    virtual void		mouseReleased(int x, int y);
};

#endif
