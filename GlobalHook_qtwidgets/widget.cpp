#include "widget.h"
#include "ui_widget.h"

#include <QScrollBar>

#ifdef Q_OS_WIN
#include <Windows.h>
#include <QLibrary>

typedef int(*FUN1)(HWND);
typedef int(*FUN2)();
#endif

#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << (setGlobalHook(true) ? "set ok" : "set failed");

    connect(this, &Widget::mousekeyboardAction,
            [this](){
        static int i = 0;
        QString debug = QString::number(i++) + "\tmouse_keyboard_action\n";
        qDebug() << debug;
        //ui->textBrowser->insertPlainText(debug);
    });
    connect(ui->textBrowser->verticalScrollBar(), &QScrollBar::rangeChanged,
            [this](int min, int max) {
        ui->textBrowser->verticalScrollBar()->setValue(max);
    });
}

Widget::~Widget()
{
    qDebug() << (setGlobalHook(false) ? "unset ok" : "unset failed");

    delete ui;
}

bool Widget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#ifdef Q_OS_WIN
    if (eventType == "windows_generic_MSG") {
        MSG *msg = static_cast<MSG *>(message);
        switch (msg->message) {

        case WM_USER + 100:
            emit mousekeyboardAction();
            //qDebug() << "mouse_keyboard_action";
            break;
        default:
            break;
        }
    }
#endif
    return false;
}

bool Widget::setGlobalHook(bool b)
{
#ifdef Q_OS_WIN
    static FUN1 SetHook = NULL;
    static FUN2 UnSetHook = NULL;
    if (b) {
        QLibrary lib("HOOK.dll");
        if (lib.load()) {
            qDebug() << "load ok!";

            SetHook = (FUN1)lib.resolve("SetHook");
            UnSetHook = (FUN2)lib.resolve("UnSetHook");
            if (SetHook) {
                qDebug() << "load SetHook ok!";
                SetHook((HWND)this->winId());
            }
            if (UnSetHook) {
                qDebug() << "load UnSetHook ok!";
            }
            return true;
        } else {
            qDebug() << "load error!";
            return false;
        }
    } else {
        if (UnSetHook)
            return UnSetHook();
        else
            return false;
    }
#endif
}
