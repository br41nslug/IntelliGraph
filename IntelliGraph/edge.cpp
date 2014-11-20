#include "edge.h"
#include "node.h"
#include "workspace.h"

using namespace std;

// initializes the edge class
Edge::Edge(int id, Node *start, Node *end, Workspace *context): QGraphicsItem()
{
    _id = id;
    _start = start;
    _end = end;
    _label = "1";
    _flip = false;
    _margin = 50;
    _weight = 1.0;
    _context = context;
    this->setZValue(1);
}

// Deconstructs the edge class instance
Edge::~Edge()
{

}

// Gets the Id
int Edge::getID()
{
    return _id;
}

// Gets the Label
string Edge::getLabel()
{
    return _label;
}

// Gets the path weight
double Edge::getWeight()
{
    return _weight;
}

// Checks if this edge is connected to target
bool Edge::hasNode(Node *target)
{
    return (_start == target || _end == target);
}

// Sets the Label
void Edge::setLabel(string label)
{
    _label = label;
    this->update();
}

// Sets the Weight
void Edge::setWeight(double weight)
{
    // if label set to weight change it
    if (dtos(_weight) == _label)
    {
        _label = dtos(weight);
    }
    _weight = weight;
    this->update();
}

// Return bounding rectangle
QRectF Edge::boundingRect() const
{
    QPointF s = _start->getCenter();
    QPointF e = _end->getCenter();
    QPointF topleft = QPointF(min(s.x(), e.x())-_margin, min(s.y(), e.y())-_margin);
    QPointF bottomright = QPointF(max(s.x(), e.x())+_margin, max(s.y(), e.y())+_margin);

    return QRectF(topleft, bottomright);//_start->getCenter(), _end->getCenter());
}

// Paint the object
void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawLine(_start->getCenter(), _end->getCenter());

    QFont font = painter->font();
    font.setPointSize(FONTSIZE);
    painter->setFont(font);

    QLineF line(_end->getCenter(),_start->getCenter());

    if(!_flip)
        painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*50,qCos(line.angle()*M_PI/180)*50,0,0), Qt::AlignCenter, QString(_label.c_str()));
    else
        painter->drawText(boundingRect().adjusted(qSin(line.angle()*M_PI/180)*-50,qCos(line.angle()*M_PI/180)*-50,0,0), Qt::AlignCenter, QString(_label.c_str()));

}


// convert an double to a string
string Edge::dtos(double number)
{
    ostringstream temp;
    temp << number;
    return temp.str();
}

// Custom update routine
void Edge::update()
{
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::update(boundingRect());
}

void Edge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->update();
}
