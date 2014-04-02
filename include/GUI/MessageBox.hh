#ifndef MESSAGEBOX_HH_
# define MESSAGEBOX_HH_

# include "GUI/Layer.hh"
# include "GUI/String.hh"

// MessageBox - Layer since it should surpass all Drawables

class MessageBox : public Layer
{
  private:

  public:
    MessageBox(const sf::String &text);
    ~MessageBox();

    void			draw(sf::RenderWindow &window);
};

#endif


