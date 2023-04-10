#include "wordproxymodeltopwords.h"

WordProxyModelTopWords::WordProxyModelTopWords(QObject *parent) : QAbstractProxyModel(parent) {
    setLimit(15);
    setMaxWordCount(0);
    m_rowIndexMap.reserve(1000000);

}

void WordProxyModelTopWords::setSourceModel(QAbstractItemModel *sourceModel) {
    disconnect( sourceModel, nullptr, this, nullptr );
    QAbstractProxyModel::setSourceModel( sourceModel );

    connect( sourceModel, &QAbstractItemModel::dataChanged,
             this, [this] (const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        if(this->sourceModel()->data(topLeft, Qt::UserRole + 2).toInt() >= minMaxWordCount)
            rebuildIndexMap();
    } );

    connect( sourceModel, &QAbstractItemModel::rowsInserted,
             this, [this] (const QModelIndex &parent, int first, int last) {
        Q_UNUSED(parent);
        if(this->sourceModel()->index(first, 0 ).data(Qt::UserRole + 2).toInt() >= minMaxWordCount)
            rebuildIndexMap();

    } );
}



int WordProxyModelTopWords::rowCount(const QModelIndex &parent) const {
    return m_rowIndexMap.size();
}

int WordProxyModelTopWords::columnCount(const QModelIndex &parent) const {
    return sourceModel()->columnCount();
}

QModelIndex WordProxyModelTopWords::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() || row < 0 || row >= m_rowIndexMap.size() || column < 0 || column >= columnCount()) {
        return QModelIndex();
    }

    return createIndex(row, column, m_rowIndexMap.at(row));
}

QModelIndex WordProxyModelTopWords::parent(const QModelIndex &child) const {
    return QModelIndex();
}

QModelIndex WordProxyModelTopWords::mapFromSource(const QModelIndex &sourceIndex) const {
    return QModelIndex();
//    if (!sourceIndex.isValid()) {
//        return QModelIndex();
//    }

//    int row = m_indexMap.value(sourceIndex.row(), -1);
//    if (row == -1) {
//        return QModelIndex();
//    }

//    return createIndex(row, sourceIndex.column(), sourceIndex.row());
}

QModelIndex WordProxyModelTopWords::mapToSource(const QModelIndex &proxyIndex) const {
    if (!proxyIndex.isValid() || proxyIndex.row() >= m_rowIndexMap.size() || proxyIndex.column() >= columnCount()) {
        return QModelIndex();
    }

    int sourceRow = m_rowIndexMap.at(proxyIndex.row());
    return sourceModel()->index(sourceRow, proxyIndex.column());
}

QVariant WordProxyModelTopWords::data(const QModelIndex &proxyIndex, int role) const {
    if (!proxyIndex.isValid()) {
        return QVariant();
    }

    QModelIndex sourceIndex = mapToSource(proxyIndex);
    if (!sourceIndex.isValid()) {
        return QVariant();
    }

    return sourceModel()->data(sourceIndex, role);
}

int WordProxyModelTopWords::maxWordCount() const
{
    return m_maxWordCount;
}

void WordProxyModelTopWords::setMaxWordCount(int newMaxWordCount)
{
    if (m_maxWordCount == newMaxWordCount)
        return;
    m_maxWordCount = newMaxWordCount;
    emit maxWordCountChanged();
}

int WordProxyModelTopWords::maxLimit() const
{
    return m_limit;
}

void WordProxyModelTopWords::setLimit(int newLimit)
{
    if (m_limit == newLimit)
        return;
    m_limit = newLimit;
    emit limitChanged();
}

void WordProxyModelTopWords::rebuildIndexMap() {
    beginResetModel();
    m_rowIndexMap.clear();

    m_rowIndexMap.resize(sourceModel()->rowCount());
    std::iota(m_rowIndexMap.begin(), m_rowIndexMap.end(), 0);

    // Последовательно:

    // сортируем по количеству элементов
    std::partial_sort(m_rowIndexMap.begin(),m_rowIndexMap.begin() + qMin(m_limit, m_rowIndexMap.size()),m_rowIndexMap.end(), [&](int a, int b){
        return sourceModel()->index(a, 0).data(Qt::UserRole + 2).toInt() > sourceModel()->index(b, 0).data(Qt::UserRole + 2).toInt();
    });

    // обрезаем до лимита (15 топовых элементов )
    m_rowIndexMap.resize(qMin(m_limit, m_rowIndexMap.size()));

    int localMinMaxElement = mapToSource(index(m_rowIndexMap.size()-1,0)).data(Qt::UserRole + 2).toInt();
    minMaxWordCount = qMax(minMaxWordCount, localMinMaxElement);

    int localMaxElement = mapToSource(index(0,0)).data(Qt::UserRole + 2).toInt();
    setMaxWordCount(qMax(maxWordCount(), localMaxElement));

    //         сортируем оставшиеся по имени
    std::sort(m_rowIndexMap.begin(), m_rowIndexMap.end(), [&](int a, int b) {
        return sourceModel()->index(a, 0).data(Qt::UserRole + 1).toString() < sourceModel()->index(b, 0).data(Qt::UserRole + 1).toString();
    });
    endResetModel();
}
