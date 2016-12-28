#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool setGlobalHook(bool b);

signals:
    void mousekeyboardAction();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
