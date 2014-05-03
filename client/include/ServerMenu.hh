#ifndef SERVER_MENU_HH_
# define SERVER_MENU_HH_

# include "Network.hh"
# include "Layer.hh"
# include "Menu.hh"
# include "MainMenuItem.hh"

class ServerMenu : public Layer
{
  private:
    Menu			*_menu;
    bool			_internet;

  public:
    ServerMenu();
    ~ServerMenu();

    void			refreshServers();
    void			serverDiscovered(ProtocoledPacket &packet);

    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
};

#endif