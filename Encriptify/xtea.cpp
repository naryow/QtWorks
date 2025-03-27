#include "xtea.h"
#include <QDebug>

// Реализация методов XTea
XTea::XTea(const QByteArray &key, uint n_rounds)
    : m_key(key), m_n_rounds(n_rounds) {
    if (key.size() != 16) {
        qWarning("Key size must be exactly 16 bytes!");
    }
}

void XTea::Encrypt(QByteArray &data, const QByteArray &key, uint n_rounds) {
    if (key.size() != 16) {
        qWarning("Key size must be exactly 16 bytes!");
        return;
    }

    // Добавляем padding, если размер данных не кратен BLOCK_SIZE
    addPadding(data);

    // Преобразуем ключ в массив uint32_t
    const uint32_t *keyPtr = reinterpret_cast<const uint32_t *>(key.constData());

    // Шифруем данные блоками по 8 байт
    for (int i = 0; i < data.size(); i += BLOCK_SIZE) {
        encipher(n_rounds, reinterpret_cast<uint32_t *>(data.data() + i), keyPtr);
    }
}

void XTea::Decrypt(QByteArray &data, const QByteArray &key, uint n_rounds) {
    if (key.size() != 16) {
        qWarning("Key size must be exactly 16 bytes!");
        return;
    }

    // Преобразуем ключ в массив uint32_t
    const uint32_t *keyPtr = reinterpret_cast<const uint32_t *>(key.constData());

    // Расшифровываем данные блоками по 8 байт
    for (int i = 0; i < data.size(); i += BLOCK_SIZE) {
        decipher(n_rounds, reinterpret_cast<uint32_t *>(data.data() + i), keyPtr);
    }

    // Удаляем padding
    removePadding(data);
}

void XTea::Encrypt(QByteArray &data) {
    Encrypt(data, m_key, m_n_rounds);
}

void XTea::Decrypt(QByteArray &data) {
    Decrypt(data, m_key, m_n_rounds);
}

void XTea::encipher(uint n_rounds, uint32_t v[2], const uint32_t key[4]) {
    uint32_t sum = 0;
    for (uint i = 0; i < n_rounds; i++) {
        v[0] += ((v[1] << 4 ^ v[1] >> 5) + v[1]) ^ (sum + key[sum & 3]);
        sum += DELTA;
        v[1] += ((v[0] << 4 ^ v[0] >> 5) + v[0]) ^ (sum + key[(sum >> 11) & 3]);
    }
}

void XTea::decipher(uint n_rounds, uint32_t v[2], const uint32_t key[4]) {
    uint32_t sum = DELTA * n_rounds;
    for (uint i = 0; i < n_rounds; i++) {
        v[1] -= ((v[0] << 4 ^ v[0] >> 5) + v[0]) ^ (sum + key[(sum >> 11) & 3]);
        sum -= DELTA;
        v[0] -= ((v[1] << 4 ^ v[1] >> 5) + v[1]) ^ (sum + key[sum & 3]);
    }
}

void XTea::addPadding(QByteArray &data) {
    uint padding = BLOCK_SIZE - (data.size() % BLOCK_SIZE);
    data.append(padding, static_cast<char>(padding));
}

void XTea::removePadding(QByteArray &data) {
    if (data.isEmpty()) return;

    uint padding = static_cast<uint>(static_cast<uchar>(data.at(data.size() - 1)));
    if (padding > BLOCK_SIZE) {
        qWarning("Invalid padding!");
        return;
    }

    data.chop(padding);
}
