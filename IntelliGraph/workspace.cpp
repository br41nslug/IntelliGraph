#include "workspace.h"

Workspace::Workspace( QWidget *widget, QGraphicsView *elem )
{
    this->drawingArea = elem;
    this->parent = widget;

    // We need a Scene on the GraphicsView to draw shapes
    scene = new QGraphicsScene( parent );
    drawingArea->setScene(scene);

    //We can only add elements *inside* the bounding box of the scene, but by default this bounding box has
    //no width or height, so we can't add anything...
    //We set this bounding box to be a fixed value here so we can add something.
    scene->setSceneRect(drawingArea->x(), drawingArea->y(), drawingArea->width()-10, drawingArea->height()-10);

    //When using a dynamic scene rect, the scene rect is the bounding box of the elements.
    //These invisible elements force the bounding box to be the size of the initial workspace
    //allowing us to dynamically add elements in it.
    scene->addRect(0,0,0,0,QPen(),QBrush());
    scene->addRect(scene->width(),scene->height(),0,0,QPen(),QBrush());

    //Scene rect back to automatic. Since we now have items in it, the bounding box will be at least the size
    //that contains these elements. Mission accomplished.
    scene->setSceneRect(QRectF());
}

Workspace::~Workspace()
{
    delete scene;
}

void Workspace::handleClick( QMouseEvent *event ) {
    int x, y;
    x = event->x() - drawingArea->x() - drawingArea->horizontalScrollBar()->minimum() + drawingArea->horizontalScrollBar()->value();
    y = event->y() - drawingArea->y() - drawingArea->verticalScrollBar()->minimum() + drawingArea->verticalScrollBar()->value();

    if( event->type() == QEvent::MouseButtonDblClick ) {
        addNode( x - (NODESIZE/2), y - (NODESIZE/2) );
    }
}

void Workspace::addNode(int x, int y)
{
    Node* node = new Node(nodes.count(),x,y);
    nodes.append( node );

    //FIXME Delete me at some point
    node->changeName( "something" );

    scene->addItem( node );
    scene->addItem( node->getLabel() );
}
