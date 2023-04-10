#ifndef WORDREADER_H
#define WORDREADER_H
#include "qobjectdefs.h"
#include <QFile>
#include <QTextStream>
#include <QtConcurrent>
#include <QThread>


class WordReader : public QObject{
    Q_OBJECT

    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(float pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(float total READ total WRITE setTotal NOTIFY totalChanged)
    Q_PROPERTY(bool isRuning READ isRuning WRITE setIsRuning NOTIFY isRuningChanged)
public:
    WordReader(QObject * parent = nullptr);
    ~WordReader();

    Q_INVOKABLE void runReading(const QString& fileName);

    const QString &filePath() const;
    void setFilePath(const QString &newFilePath);

    float pos() const;
    void setPos(float newPos);

    float total() const;
    void setTotal(float newTotal);

    bool isRuning() const;
    void setIsRuning(bool newIsRuning);

signals:
    void newWord(const QString & word, int count);
    void wordCountChanged(const QString & word, int count);

    void filePathChanged();
    void posChanged();
    void totalChanged();
    void isRuningChanged();

    void hasReset();

private:
    void readFile(const QString& fileName);

    QHash<QString, int> wordsCount;
    QSet<QString> notWords = {"-", "а", "бы", "но" , "и", "в", "к", "на", "за", "не", "с", "у", "что"};
    QFuture<void> future ;

    QString m_filePath;
    float m_progress;
    float m_pos;
    float m_total;
    bool m_isRuning;
};

#endif // WORDREADER_H
