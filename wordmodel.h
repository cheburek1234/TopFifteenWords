#ifndef WORDMODEL_H
#define WORDMODEL_H
#include "qdebug.h"
#include <QAbstractTableModel>

class WordModel : public QAbstractTableModel{
    Q_OBJECT
public:
    WordModel(QObject * parent = nullptr);;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    bool replaceValue(const QString & word, int count);
    bool addRow(const QString & word, int count);
    bool resetModel();
protected:
    QHash<int, QByteArray> roleNames() const  override;

private:
    QVector<QPair<QString, int>> _data;
    QMap<QString, int> indexWord;

    enum Roles {
        WORD  = Qt::UserRole + 1,
        COUNT
    };

};

#endif // WORDMODEL_H
