#include <QLabel>

class Tile : public QLabel
{
    Q_OBJECT

public:
    int x;
    int y;
    int state;
    bool mouseOn;
    Tile(QWidget *parent, int x, int y);
};
