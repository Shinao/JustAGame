#ifndef SERVER_MENU_HH_
# define SERVER_MENU_HH_

# include "Network.hh"
# include "Layer.hh"
# include "Menu.hh"
# include "MainMenuItem.hh"
# include "Table.hh"
# include "ModalMessageBox.hh"
# include "LibraryLoader.hh"

class ServerMenu : public Layer
{
  private:
    Menu			*_menu;
    bool			_internet;
    Table			*_table;

    //
    // Connecting progress
    //
    enum
    {
      Connected,
      Connecting,
      Aborting,
      Unconnected
    }				_state;
    ModalMessageBox		*_msg;
    sf::Thread			*_thread;
    Client			*_server;
    LibraryLoader		*_lib;
    std::string			_game_mode;

    bool			tryingToEscape();
    void			serverSelected();
    void			launchGame();
    void			getGame(ProtocoledPacket &packet);
    void			couldNotConnect(ProtocoledPacket &packet);
    void			connectedToServer(ProtocoledPacket &packet);
    void			connectionError(const std::string &desc);
    //

  public:
    ServerMenu();
    ~ServerMenu();

    void			refreshServers();
    void			serverDiscovered(ProtocoledPacket &packet);

    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
};

#endif
