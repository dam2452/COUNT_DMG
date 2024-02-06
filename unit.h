#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QVector>


// Definicja struktury dla umiejętności (Skill)
struct Skill {
    QString skillName;
    int skillValue;
};

// Definicja struktury dla opcji wyposażenia (WargearOption)
struct WargearOption {
    QString name;
    QVector<Skill> skills;
};


class Unit
{
public:
    Unit();

    // Gettery
    QString getUnitName() const { return unitName; }
    double getHp() const { return hp; }
    double getArmor() const { return armor; }
    double getShield() const { return shield; }
    double getSpeed() const { return speed; }
    double getStamina() const { return stamina; }
    double getCost() const { return cost; }
    double getMeleeDamage() const { return meleeDamage; }
    double getRangeDamage() const { return rangeDamage; }
    double getCharge() const { return charge; }
    double getArmorPiercing() const { return ArmorPiercing; }

    QVector<WargearOption> getWargearOptions() const { return wargearOptions; }
    QVector<QString> getAbilities() const { return abilities; }
    QVector<QString> getTags() const { return Tags; }
    QString getDescription() const { return description; }


    // Settery
    void setUnitName(const QString &name) { unitName = name; }
    void setHp(double value) { hp = value; }
    void setArmor(double value) { armor = value; }
    void setShield(double value) { shield = value; }
    void setSpeed(double value) { speed = value; }
    void setStamina(double value) { stamina = value; }
    void setCost(double value) { cost = value; }
    void setMeleeDamage(double value) { meleeDamage = value; }
    void setRangeDamage(double value) { rangeDamage = value; }
    void setCharge(double value) { charge = value; }
    void setArmorPiercing(double value) { ArmorPiercing = value; }

    void setWargearOptions(const QVector<WargearOption> &options) { wargearOptions = options; }
    void addWargearOption(const WargearOption &option) { wargearOptions.append(option); } // Dodatkowa metoda do dodawania pojedynczej opcji wyposażenia
    void setAbilities(const QVector<QString> &abilitiesList) { abilities = abilitiesList; }
    void addAbility(const QString &ability) { abilities.append(ability); } // Dodatkowa metoda do dodawania pojedynczej zdolności
    void setTags(const QVector<QString> &TagsList) { Tags = TagsList; }
    void addTag(const QString &Tag) { Tags.append(Tag); } // Dodatkowa metoda do dodawania pojedynczego słowa kluczowego

    void setAntiTags(const QVector<QString> &AntiTagsList) { AntiTags = AntiTagsList; }
    void addAntiTag(const QString &AntiTag) { AntiTags.append(AntiTag); }

    void setDescription(const QString &desc) { description = desc; }


private:

    QString unitName;
    double hp;
    double armor;
    double shield;
    double speed;
    double stamina;
    double cost;
    double meleeDamage;
    double rangeDamage;
    double charge;
    double ArmorPiercing;
    QVector<WargearOption> wargearOptions;
    QVector<QString> abilities;
    QVector<QString> Tags;
    QVector<QString> AntiTags;
    QString description;


};

#endif // UNIT_H
