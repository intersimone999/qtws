#ifndef QTWS_H
#define QTWS_H

#include <QString>
#include <QList>
#include "menuaction.h"

class QtWS {
public:
    QtWS(QString filename);

    QString getName();

    QList<QString> getWScope();
    bool isInScope(QUrl);

    QList<QString> getPlugins();
    QString getHome();
    QString getIconPath();

    QList<MenuAction> getMenu();

    QString getConfigName();

    bool isSaveSession();
    bool isMenuDisabled();
    bool hasMultimedia();

private:
    QString name;
    QList<QString> scope;
    QList<QString> plugins;
    QString home;
    QString iconPath;
    bool saveSession;
    bool menuDisabled;
    bool multimedia;

    QList<MenuAction> menu;

    void loadData(QString filename);
};

#endif // QTWS_H
