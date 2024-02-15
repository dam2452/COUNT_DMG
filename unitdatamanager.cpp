#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "unit.h"
#include "unitdatamanager.h"


UnitDataManager::UnitDataManager() {}

void UnitDataManager::loadUnitsFromJson(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Nie można otworzyć pliku.");
        return;
    }

    QString jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData.toUtf8());

    if (document.isArray()) {
        QJsonArray jsonArray = document.array();
        for (const QJsonValue &unitValue : jsonArray) {
            QJsonObject unitObject = unitValue.toObject();

            Unit unit;
            unit.setUnitName(unitObject["UnitName"].toString());
            unit.setHp(static_cast<float>(unitObject["HP"].toDouble()));
            unit.setArmor(static_cast<float>(unitObject["Armor"].toDouble()));
            unit.setShield(static_cast<float>(unitObject["Shield"].toDouble()));
            unit.setSpeed(static_cast<float>(unitObject["Speed"].toDouble()));
            unit.setStamina(static_cast<float>(unitObject["Stamina"].toDouble()));
            unit.setCost(static_cast<float>(unitObject["Cost"].toDouble()));
            unit.setDescription(unitObject["Description"].toString());

            // Ustaw wartości Melee Damage, Range Damage, Charge i Armor Piercing bezpośrednio z JSON
            unit.setMeleeDamage(static_cast<float>(unitObject["Meele Damage"].toDouble()));
            unit.setRangeDamage(static_cast<float>(unitObject["Ranged Damage"].toDouble()));
            unit.setCharge(static_cast<float>(unitObject["Charge Bonus"].toDouble()));
            unit.setArmorPiercing(static_cast<float>(unitObject["Meele Armor Piercing"].toDouble())); // Przykład dla Meele Armor Piercing

            // Tagi
            QJsonArray tagArray = unitObject["Tag"].toArray();
            for (const QJsonValue &tagValue : tagArray) {
                QJsonObject tagObject = tagValue.toObject(); // Jeżeli Tagi są obiektami
                unit.addTag(tagObject["Tag"].toString());
            }

            // AntiTagi
            QJsonArray antiTagArray = unitObject["AntiTag"].toArray();
            for (const QJsonValue &antiTagValue : antiTagArray) {
                QJsonObject antiTagObject = antiTagValue.toObject();
                AntiTag antiTag;
                antiTag.name = antiTagObject["Tag"].toString();
                antiTag.value = antiTagObject["Value"].toDouble();
                unit.addAntiTag(antiTag);
            }

            units.append(unit);
        }
    }
}


QVector<Unit> UnitDataManager::getUnits() const
{
 return units;
}

