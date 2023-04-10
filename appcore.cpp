#include "appcore.h"


AppCore::AppCore(QObject *parent) : QObject(parent){
    reader = new WordReader(this);
    model = new WordModel(this);

    connect(reader, &WordReader::newWord, model, &WordModel::addRow);
    connect(reader, &WordReader::wordCountChanged, model, &WordModel::replaceValue);
    connect(reader, &WordReader::hasReset, model, &WordModel::resetModel);

    proxy = new WordProxyModelTopWords(this);
    proxy->setSourceModel(model);

}

void AppCore::setupQmlContextProperty(QQmlContext *context){
    context->setContextProperty("WordReader", reader);
    context->setContextProperty("WordModel", proxy);
    context->setContextProperty("AppCore", this);
}
