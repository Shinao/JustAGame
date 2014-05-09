#ifndef INPUT_LAYER_HH_
# define INPUT_LAYER_HH_

# include "Layer.hh"
# include "MainMenuItem.hh"
# include "ModalMessageBox.hh"
# include "Table.hh"
# include "Scroller.hh"

class InputLayer : public MainMenuItem, public EventCallback
{
  private:
    static const int		NB_INPUT = 14;

    static struct Keys
    {
      std::string		ini_name;
      std::string		label;
      std::string		sf_key;
    }				_keys[NB_INPUT];

    Scroller			*_scroller;
    ModalMessageBox		*_msg_box;
    bool			_event_catched;
    Table			*_table;

    void			applyChanges();
    void			cbItemPressed();
    int				eventCatched();
    void			setEventByIndex(int index, const std::string &sf_key);

  public:
    InputLayer();
    ~InputLayer();

    bool			update(sf::RenderWindow &window);
    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();

    void			keyPressed(Context context);
    void			mousePressed(Context context);
};

#endif
