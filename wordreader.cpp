#include "wordreader.h"

WordReader::WordReader(QObject *parent) : QObject(parent){
    setPos(0);
    setTotal(0);
    setIsRuning(false);
}

void WordReader::runReading(const QString &fileName){
    setFilePath(fileName);
    setIsRuning(true);
    wordsCount.clear();
    emit hasReset();
    auto future = QtConcurrent::run([this]{
        readFile(filePath());
    });

}

void WordReader::readFile(const QString &fileName) {
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file" << fileName;
        return;
    }
    setTotal(file.size());

    QTextStream in(&file);

    while (!in.atEnd()) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            return;
        }

        QString word;
        in >> word;
        word = word.toLower().remove(QRegExp("[^а-яa-z-]"));
        if (!word.isEmpty() && !notWords.contains(word)) {
            if(wordsCount.contains(word)){
                wordsCount[word]++;
                emit wordCountChanged(word, wordsCount[word]);
            }else{
                wordsCount.insert(word, 1);
                emit newWord(word, 1);
            }
            setPos(in.pos());
        }
    }
    setIsRuning(false);
    file.close();
}



const QString &WordReader::filePath() const
{
    return m_filePath;
}

void WordReader::setFilePath(const QString &newFilePath)
{
    if (m_filePath == newFilePath)
        return;
    m_filePath = newFilePath;
    emit filePathChanged();
}

WordReader::~WordReader(){
    if(future.isRunning())
        future.cancel();
}



float WordReader::pos() const
{
    return m_pos;
}

void WordReader::setPos(float newPos)
{
    if (qFuzzyCompare(m_pos, newPos))
        return;
    m_pos = newPos;
    emit posChanged();
}

float WordReader::total() const
{
    return m_total;
}

void WordReader::setTotal(float newTotal)
{
    if (qFuzzyCompare(m_total, newTotal))
        return;
    m_total = newTotal;
    emit totalChanged();
}

bool WordReader::isRuning() const
{
    return m_isRuning;
}

void WordReader::setIsRuning(bool newIsRuning)
{
    if (m_isRuning == newIsRuning)
        return;
    m_isRuning = newIsRuning;
    emit isRuningChanged();
}
