#include "wordmodel.h"


WordModel::WordModel(QObject *parent) : QAbstractTableModel(parent){}

int WordModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return _data.size();
}

int WordModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    return 1;
}

QVariant WordModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    switch (role){
    case WORD:  return _data[index.row()].first;  break;
    case COUNT: return _data[index.row()].second;  break;
    }
    return QVariant();
}

bool WordModel::replaceValue(const QString &word, int count){

    // добавить проверки на выход за границы и существование слова

    _data[indexWord[word]].second = count;
    emit dataChanged(this->index(indexWord[word],0), this->index(indexWord[word],0), {WORD, COUNT});
    return true;
}

bool WordModel::addRow(const QString &word, int count){

    beginInsertRows(QModelIndex(), _data.count(), _data.count());

    _data.append(qMakePair(word, count));
    indexWord.insert(word, _data.count()-1);

    endInsertRows();
    return true;
}

bool WordModel::resetModel(){
    beginResetModel();
    _data.clear();
    indexWord.clear();
    endResetModel();

    return true;
}

QHash<int, QByteArray> WordModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[WORD]     = "word";
    roles[COUNT]    = "count";
    return roles;
}
