#include "qtwswebpage.h"
#include "qtws.h"

#include <QDesktopServices>
#include <QUrl>
#include <QWebEnginePage>

QtWSWebPage::QtWSWebPage(QtWS *config) {
    configHandler = config;
}

QWebEnginePage *QtWSWebPage::createWindow(QWebEnginePage::WebWindowType type) {
    QWebEnginePage *fakePage = new QWebEnginePage(this);

    connect(fakePage, &QWebEnginePage::urlChanged, this, [this, fakePage](QUrl url) {
        if (!this->configHandler->isInScope(url)) {
            if (url.scheme() != "about" && url.scheme() != "") {
                QDesktopServices::openUrl(url);
                fakePage->triggerAction(QWebEnginePage::Stop);
                fakePage->triggerAction(QWebEnginePage::RequestClose);
            }
        } else {
            this->setUrl(url);
        }
    });

    connect(fakePage, &QWebEnginePage::windowCloseRequested, this, []() {
        qWarning() << tr("CLOSED!");
    });

    return fakePage;
}

bool QtWSWebPage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame) {
    if (type == QWebEnginePage::NavigationTypeLinkClicked &&
            !this->configHandler->isInScope(url) &&
            isMainFrame) {
        QDesktopServices::openUrl(url);
        return false;
    }

    return true;
}
