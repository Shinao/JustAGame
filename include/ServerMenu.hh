#ifndef SERVER_MENU_HH_
# define SERVER_MENU_HH_

# include "Network/Network.hh"
# include "GUI/Layer.hh"
# include "GUI/Menu.hh"

class ServerMenu : public Layer
{
  public:
    static const int		WIDTH = 600;
    static const int		HEIGHT = 32;
    static const int		PADDING = 128;
    static const int		MARGIN = 32;

  private:
    Menu			*_menu;
    bool			_internet;

  public:
    ServerMenu();
    ~ServerMenu();

    void			refreshServers();
    void			serverDiscovered(Client *client, sf::Packet &packet);

    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
};

#endif
