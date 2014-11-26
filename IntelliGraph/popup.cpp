#include "popup.h"


Popup::Popup(QWidget *parent, Node *_caller) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
    this->setCaller(_caller);
    //this->setFixedSize(382, 350);
    this->fillColours();
    this->setSliders( caller->getColour() );
    this->setWindowFlags(Qt::Tool);
}

Popup::~Popup()
{
    delete ui;
}

void Popup::setLabel(string label) {
    ui->labelTextbox->setPlainText( QString::fromStdString(label) );
}

void Popup::fillColours() {
    ui->colorComboBox->addItem("");
    foreach (QString clr, QColor::colorNames()) {
        colors.append(clr);
        ui->colorComboBox->addItem(clr);
    }
}

void Popup::setSliders( QColor currentColor ) {
    updateColour(currentColor.red(), currentColor.green(), currentColor.blue());

    ui->redSlider->setMinimum(0);
    ui->redSlider->setMaximum(255);
    ui->redSlider->setValue(currentColor.red());

    ui->greenSlider->setMinimum(0);
    ui->greenSlider->setMaximum(255);
    ui->greenSlider->setValue(currentColor.green());

    ui->blueSlider->setMinimum(0);
    ui->blueSlider->setMaximum(255);
    ui->blueSlider->setValue(currentColor.blue());
}

void Popup::on_buttonBox_accepted() {
    if (ui->labelTextbox->toPlainText().size() != 0) {
        this->caller->setLabel(ui->labelTextbox->toPlainText().toStdString());
    }

    if (ui->colorComboBox->currentIndex() != 0) {
        QColor selected = colors[ui->colorComboBox->currentIndex() - 1];
        this->caller->setColour(selected);
    }
    else
        this->caller->setColour(newColor);

}

void Popup::updateColour(int r, int g, int b) {
    ui->colourPreview->setStyleSheet("QLabel { background-color : rgb(" +
                                     QString::number(r) + ", " +
                                     QString::number(g) + ", " +
                                     QString::number(b) + ");}");
    newColor = QColor(r, g, b);
}

void Popup::setCaller(Node *_caller) {
    caller = _caller;
}

void Popup::on_redSlider_sliderMoved(int position) {
    updateColour(position, newColor.green(), newColor.blue());
}

void Popup::on_greenSlider_sliderMoved(int position) {
    updateColour(newColor.red(), position, newColor.blue());
}

void Popup::on_blueSlider_sliderMoved(int position) {
    updateColour(newColor.red(), newColor.green(), position);
}

void Popup::on_colorComboBox_currentIndexChanged(int index) {
    if (index != 0) {
        QColor selected = (colors[ui->colorComboBox->currentIndex() - 1]);
        setSliders( selected );
    }
}
