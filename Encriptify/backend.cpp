#include "backend.h"
#include <QCryptographicHash>
#include "xtea.h"

QString Backend::encrypt(const QString &text, const QString &key) {
    QByteArray data = text.toUtf8();
    QByteArray keyBytes = key.toUtf8();

    if (keyBytes.size() != 16) {
        return "Error: Key must be exactly 16 bytes!";
    }

    XTea xtea(keyBytes, 32); // Указываем количество раундов
    xtea.Encrypt(data);

    return data.toHex();
}

QString Backend::decrypt(const QString &hexText, const QString &key) {
    QByteArray data = QByteArray::fromHex(hexText.toUtf8());
    QByteArray keyBytes = key.toUtf8();

    if (keyBytes.size() != 16) {
        return "Error: Key must be exactly 16 bytes!";
    }

    XTea xtea(keyBytes, 32); // Указываем количество раундов
    xtea.Decrypt(data);

    return QString::fromUtf8(data);
}

QString Backend::hash(const QString &input) {
    QByteArray hashBytes = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Sha256);
    return hashBytes.toHex();
}

/*
#include "backend.h"
#include <QCryptographicHash>
#include "xtea.h"

QString Backend::hash(const QString &data)
{
    return QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Md5).toBase64();
}

QString Backend::encrypt(const QString &data, const QString &key)
{
    std::vector<unsigned char> out(data.toUtf8().begin(), data.toUtf8().end());
    std::vector<unsigned char> keyVec = std::vector<unsigned char>(key.toUtf8().begin(), key.toUtf8().end());
    XTea xtea(32);
    xtea.Encrypt(out.data(), out.size(), keyVec.data());

    return QByteArray(reinterpret_cast<char*>(out.data()), out.size()).toBase64();
}

QString Backend::decrypt(const QString &data, const QString &key)
{
    std::vector<unsigned char> out = std::vector<unsigned char>(QByteArray::fromBase64(data.toUtf8()).begin(), QByteArray::fromBase64(data.toUtf8()).end());
    std::vector<unsigned char> keyVec = std::vector<unsigned char>(key.toUtf8().begin(), key.toUtf8().end());
    XTea xtea(32);
    xtea.Decrypt(out.data(), out.size(), keyVec.data());

    return QString::fromUtf8(reinterpret_cast<char*>(out.data()), out.size());
}
*/
