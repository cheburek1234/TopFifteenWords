#ifndef APPCORE_H
#define APPCORE_H

#include "qqmlcontext.h"
#include "wordmodel.h"
#include "wordproxymodeltopwords.h"
#include "wordreader.h"
#include <QObject>

class AppCore : public QObject{
    Q_OBJECT
public:
    AppCore(QObject * parent = nullptr);
    void setupQmlContextProperty(QQmlContext *context);
private:
    WordModel * model;
    WordProxyModelTopWords * proxy;
    WordReader * reader;
};

#endif // APPCORE_H
