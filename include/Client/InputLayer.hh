#ifndef INPUT_LAYER_HH_
# define INPUT_LAYER_HH_

# include "GUI/Layer.hh"
# include "Client/MainMenuItem.hh"
# include "GUI/ModalMessageBox.hh"
# include "GUI/Table.hh"
# include "GUI/Scroller.hh"

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

    void			mouseReleased(int x, int y);
    void			draw(sf::RenderWindow &window);
    void			mouseCaught(int x, int y);
    void			mouseLeft();
    void			settingChanged();

    void			keyPressed(Context context);
    void			mousePressed(Context context);
};

#endif
