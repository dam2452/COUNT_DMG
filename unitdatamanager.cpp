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

            double meleeDamageValue = 0.0f;
            double rangeDamageValue = 0.0f;
            double ChargeValue = 0.0f;
            double ArmorPiercingValue = 0.0f;
            QJsonArray wargearArray = unitObject["Wargear Options"].toArray();
            for (const QJsonValue &wargearValue : wargearArray) {
                QJsonObject wargearObject = wargearValue.toObject();
                WargearOption option;
                option.name = wargearObject["Name"].toString();

                QJsonArray skillsArray = wargearObject["Skills"].toArray();
                for (const QJsonValue &skillValue : skillsArray) {
                    QJsonObject skillObject = skillValue.toObject();
                    Skill skill;
                    skill.skillName = skillObject["SkillName"].toString();
                    skill.skillValue = static_cast<double>(skillObject["SkillValue"].toDouble());
                    option.skills.append(skill);

                    // Przechwytywanie wartości dla Melee Damage i Range Damage
                    if (skill.skillName == "Melee Damage") {
                        meleeDamageValue = skill.skillValue;
                    } else if (skill.skillName == "Range Damage") {
                        rangeDamageValue = skill.skillValue;
                    }
                    else if (skill.skillName == "Charge") {
                        ChargeValue = skill.skillValue;
                    }
                    else if (skill.skillName == "Armor Piercing") {
                        ArmorPiercingValue = skill.skillValue;
                    }

                }

                unit.addWargearOption(option);
            }

            // Ustaw wartości Melee Damage i Range Damage
            unit.setMeleeDamage(meleeDamageValue);
            unit.setRangeDamage(rangeDamageValue);
            unit.setCharge(ChargeValue);
            unit.setArmorPiercing(ArmorPiercingValue);

            // Tagi
            QJsonArray tagArray = unitObject["Tags"].toArray();
            for (const QJsonValue &tagValue : tagArray) {
                unit.addTag(tagValue.toString());
            }

            // AntiTagi
            QJsonArray antiTagArray = unitObject["AntiTags"].toArray();
            for (const QJsonValue &antiTagValue : antiTagArray) {
                QJsonObject antiTagObject = antiTagValue.toObject();
                AntiTag antiTag;
                antiTag.name = antiTagObject["Name"].toString();
                antiTag.value = antiTagObject["Value"].toDouble(); // Zakładamy, że "Value" to int
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

