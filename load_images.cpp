#include "load_images.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>

QMap<QString, QString> createImageToProductMap() {
    QMap<QString, QString> map;
    map.insert("korm-dlya-kotiv", "Корм для котів");
    map.insert("korm-dlya-papug", "Корм для папуг");
    map.insert("korm-dlya-gruzyniv", "Корм для гризунів");
    map.insert("shampun-dlya-kotiv", "Шампунь для котів");
    map.insert("korm-dlya-reptuliy", "Корм для рептилій");
    map.insert("korm-akvariumnux-rub", "Корм для акваріумних риб");
    map.insert("kosmetuka-dlya-sobak", "Косметика для собак");
    map.insert("zasib-proty-blix-dlya-kotiv", "Засіб проти бліх для котів");
    map.insert("klitka-dlya-xomakiv", "Клітка для хом'яків");
    map.insert("lazerna-ukazka-dlya-kotiv", "Іграшка для котів \"Лазерна указка\"");
    map.insert("pidstulka-dlya-klitok", "Підстилка для кліток");
    map.insert("lakomstvo-dlya-sobak", "Лакомство для собак");
    map.insert("pazl-dlya-sobak", "Іграшка-пазл для собак");
    map.insert("lakomstvo-dlya-kotiv", "Лакомства для котів");
    map.insert("tonel-dlya-xomyakiv", "Тунель для хом'яків");
    map.insert("klitka-dlya-ptaxiv", "Клітка для птахів");
    map.insert("tonel-dlya-kotiv", "Тунель для котів");
    map.insert("lishko-dlya-kotiv", "Ліжко для котів");
    map.insert("leshak-dlya-sobak", "Лежак для собак");
    map.insert("vitaminu-dlya-papug", "Вітаміни для папуг");
    map.insert("vitaminu-dlya-gruzyniv", "Вітаміни для гризунів");
    map.insert("kombinezon-dlya-sobak", "Комбінезон для собак");
    map.insert("shleyka-dlya-xomakiv", "Шлейка для хом’яків");
    map.insert("kombinezon-dlya-sobak-na-zumy", "Комбінезон для собак на зиму");
    map.insert("igrashka-dlya-sobak", "Іграшка для собак");
    map.insert("exotuchnuy-korm-dlya-papug", "Екзотичний корм для папуг");
    map.insert("akvarium", "Акваріум");
    map.insert("filtr-dlya-akvariuma", "Фільтр для акваріума");
    map.insert("akvariumna-pompa", "Акваріумна помпа");
    map.insert("interaktuvna-igrashka-dlya-sobak", "Інтерактивна іграшка для собак");
    map.insert("povidec", "Повідець");
    map.insert("muska-dlya-kotiv", "Миска для котів");
    map.insert("skrebok-dlya-kotiv", "Скребок для котів");
    map.insert("vidlakuvach-kotiv", "Ультразвуковий відлякувач котів");
    map.insert("osheynuk-z-gps", "Ошейник з GPS");
    map.insert("muska-z-automatuchnum-goduvannyam", "Миска з автоматичним годуванням");
    return map;
}


void loadImages() {
    QDir dir("/home/beand/documents/dz/databases/coursework/zoo-shop/productsImages");
    dir.setFilter(QDir::Files); // Указываем, что нас интересуют только файлы
    QMap<QString, QString> imageMap = createImageToProductMap();

    foreach (QString fileName, dir.entryList()) {
        QString filePath = dir.absoluteFilePath(fileName);
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) continue;

        QByteArray imageData = file.readAll();
        QString baseName = QFileInfo(fileName).baseName(); // Получаем имя файла без расширения

        if (imageMap.contains(baseName)) {
            QString productName = imageMap.value(baseName);

            qDebug() << "Updating image for product:" << productName;
            qDebug() << "Image data size:" << imageData.size();

            QSqlQuery query;
            query.prepare("UPDATE products SET image = :image WHERE name = :name");
            query.bindValue(":image", imageData);
            query.bindValue(":name", productName);
            if (!query.exec()) {
                qDebug() << "Error updating image:" << query.lastError().text();
            }
        }
    }
}
