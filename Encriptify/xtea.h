#ifndef XTEA_H
#define XTEA_H

#include <QByteArray>
#include <cstdint>
#include <QDebug>

class XTea {
public:
    // Конструктор для работы с экземпляром класса
    explicit XTea(const QByteArray &key, uint n_rounds = 32);

    // Статические методы для работы без создания экземпляра
    static void Encrypt(QByteArray &data, const QByteArray &key, uint n_rounds = 32);
    static void Decrypt(QByteArray &data, const QByteArray &key, uint n_rounds = 32);

    // Нестатические методы для работы через объект
    void Encrypt(QByteArray &data);
    void Decrypt(QByteArray &data);

private:
    QByteArray m_key;
    uint m_n_rounds;
    static constexpr uint BLOCK_SIZE = 8; // Размер блока в байтах
    static constexpr uint32_t DELTA = 0x9E3779B9; // Константа для алгоритма

    // Внутренние методы для шифрования и расшифрования
    static void encipher(uint n_rounds, uint32_t v[2], const uint32_t key[4]);
    static void decipher(uint n_rounds, uint32_t v[2], const uint32_t key[4]);

    // Метод для добавления padding
    static void addPadding(QByteArray &data);
    // Метод для удаления padding
    static void removePadding(QByteArray &data);
};

#endif // XTEA_H
