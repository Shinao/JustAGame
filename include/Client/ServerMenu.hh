#ifndef SERVER_MENU_HH_
# define SERVER_MENU_HH_

# include "Network.hh"
# include "Layer.hh"
# include "Menu.hh"
# include "MainMenuItem.hh"
# include "Table.hh"
# include "ModalMessageBox.hh"
# include "LibraryLoader.hh"
# include "AGameClient.hh"

class ServerMenu : public MainMenuItem
{
  private:
    // Connecting progress
    enum
    {
      Disconnecting,
      Connected,
      Connecting,
      Aborting,
      Unconnected
    }				_state;

    bool			_internet;
    Table			*_table;

    // Connexion Progress
    ModalMessageBox		*_msg;
    sf::Thread			*_thread;
    Client			*_server;
    LibraryLoader		*_lib;
    std::string			_game_mode;
    Version			_version;
    AGameClient			*_game;

    void			initGame(ProtocoledPacket &packet);
    bool			tryingToEscape();
    void			connectToServer();
    void			serverSelected();
    void			launchGame();
    void			getGame(ProtocoledPacket &packet);
    void			getInfo(ProtocoledPacket &packet);
    void			incorrectVersion();
    void			couldNotConnect(ProtocoledPacket &packet);
    void			connectedToServer(ProtocoledPacket &packet);
    void			connectionError(const std::string &desc);
    void			disconnectedFromGame(ProtocoledPacket &packet);
    void			abortConnexion(ProtocoledPacket &packet);
    void			abortCouldNotConnect(ProtocoledPacket &packet);
    void			abortDisconnexion(ProtocoledPacket &packet);
    //

  public:
    ServerMenu();
    ~ServerMenu();

    void			refreshServers();
    void			serverDiscovered(ProtocoledPacket &packet);

    void			mousePressed(int x, int y);
    void			mouseReleased(int x, int y);
    void			settingChanged();
};

#endif
