#ifndef WORDPROXYMODELTOPWORDS_H
#define WORDPROXYMODELTOPWORDS_H
#include <QAbstractProxyModel>

class WordProxyModelTopWords : public QAbstractProxyModel
{
    Q_OBJECT

    Q_PROPERTY(int limit READ maxLimit WRITE setLimit NOTIFY limitChanged)
    Q_PROPERTY(int maxWordCount READ maxWordCount WRITE setMaxWordCount NOTIFY maxWordCountChanged)
public:
    WordProxyModelTopWords(QObject *parent = nullptr);

    void setSourceModel(QAbstractItemModel *sourceModel) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const override;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const override;
    QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const override;

    int maxWordCount() const;
    void setMaxWordCount(int newMaxWordCount);
    int maxLimit() const;
    void setLimit(int newLimit);
signals:
    void maxWordCountChanged();
    void limitChanged();
private:
    void rebuildIndexMap();

    QVector<int> m_rowIndexMap;
    int m_limit = 30;
    int minMaxWordCount = 0;
    int m_maxWordCount;
};

#endif // WORDPROXYMODELTOPWORDS_H
