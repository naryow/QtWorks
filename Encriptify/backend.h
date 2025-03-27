#pragma once
#include <QObject>
#include <QString>

class Backend {
public:
    QString encrypt(const QString &text, const QString &key);
    QString decrypt(const QString &hexText, const QString &key);
    QString hash(const QString &input); // Объявление метода hash
};

/*
#pragma once
#include <QObject>
#include <QString>
#include <vector>

class Backend : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE QString hash(const QString& data);
    Q_INVOKABLE QString encrypt(const QString& data, const QString& key);
    Q_INVOKABLE QString decrypt(const QString& data, const QString& key);
};
*/
