#ifndef REVIEWDATA_H
#define REVIEWDATA_H

#include <QObject>
#include <QString>
#include <QDate>

class ReviewData : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(bool recommend READ recommend WRITE setRecommend)

public:
    explicit ReviewData(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QDate date() const;
    void setDate(const QDate &date);

    bool recommend() const;
    void setRecommend(bool recommend);

private:
    QString m_name;
    QDate m_date;
    bool m_recommend;
};

#endif // REVIEWDATA_H
