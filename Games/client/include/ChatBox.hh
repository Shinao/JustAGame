#ifndef CHATBOX_HH_
# define CHATBOX_HH_

# include "Input.hh"

class ChatBox : public Layer
{
  private:
    const int		MARGIN = 64;
    const int		MESSAGES_HEIGHT = 128;
    const int		INPUT_HEIGHT = 34;
    const int		WIDTH = 256;

    Input		*_input;

  public:
    ChatBox();
    ~ChatBox();

    void			settingChanged();
};

#endif
