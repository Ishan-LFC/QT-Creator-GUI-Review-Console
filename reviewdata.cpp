#include "reviewdata.h"

ReviewData::ReviewData(QObject *parent)
    : QObject(parent), m_recommend(false) {}

QString ReviewData::name() const {
    return m_name;
}

void ReviewData::setName(const QString &name) {
    m_name = name;
}

QDate ReviewData::date() const {
    return m_date;
}

void ReviewData::setDate(const QDate &date) {
    m_date = date;
}

bool ReviewData::recommend() const {
    return m_recommend;
}

void ReviewData::setRecommend(bool recommend) {
    m_recommend = recommend;
}
