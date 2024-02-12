#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "unit.h"
#include "unitdatamanager.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define HP_LABEL "HP"
#define MD_LABEL "MD"
#define RD_LABEL "RD"
#define ST_LABEL "ST"
#define CB_LABEL "CB"
#define SH_LABEL "SH"
#define AR_LABEL "AR"
#define AP_LABEL "AP"

struct UnitAttributes {
    double hp = 0.0;
    double meleeDamage = 0.0;
    double rangeDamage = 0.0;
    double stamina = 0.0;
    double chargeBonus = 0.0;
    double shield = 0.0;
    double armor = 0.0;
    double armorPiercing = 0.0;

    // Konstruktor pozwalający na szybką inicjalizację
    UnitAttributes(double hp, double meleeDamage, double rangeDamage, double stamina,
                   double chargeBonus, double shield, double armor, double armorPiercing)
        : hp(hp), meleeDamage(meleeDamage), rangeDamage(rangeDamage), stamina(stamina),
        chargeBonus(chargeBonus), shield(shield), armor(armor), armorPiercing(armorPiercing) {}
};

UnitAttributes getUnitAttributes(const Unit& unit) {
    return UnitAttributes(unit.getHp(), unit.getMeleeDamage(), unit.getRangeDamage(), unit.getStamina(),
                          unit.getCharge(), unit.getShield(), unit.getArmor(), unit.getArmorPiercing());
}


void MainWindow::updateUnitStatsFromLeftUI(Unit &unit) {
    // Pobranie wartości z SpinBoxów i ustawienie statystyk jednostki
    unit.setHp(ui->Left_HP_doubleSpinBox->value());
    unit.setArmor(ui->Left_Armor_doubleSpinBox->value());
    unit.setShield(ui->Left_Shield_doubleSpinBox->value());
    unit.setStamina(ui->Left_Stamina_doubleSpinBox->value());
    unit.setMeleeDamage(ui->Left_MeeleDamge_doubleSpinBox->value());
    unit.setRangeDamage(ui->Left_RangeDamage_doubleSpinBox->value());
    unit.setCharge(ui->Left_ChargeBonus_doubleSpinBox->value());
    unit.setArmorPiercing(ui->Left_ArmorPirecing_doubleSpinBox->value());
}
void MainWindow::updateUnitStatsFromRightUI(Unit &unit) {
    // Pobranie wartości z SpinBoxów i ustawienie statystyk jednostki
    unit.setHp(ui->Right_HP_doubleSpinBox->value());
    unit.setArmor(ui->Right_Armor_doubleSpinBox->value());
    unit.setShield(ui->Right_Shield_doubleSpinBox->value());
    unit.setStamina(ui->Right_Stamina_doubleSpinBox->value());
    unit.setMeleeDamage(ui->Right_MeeleDamge_doubleSpinBox->value());
    unit.setRangeDamage(ui->Right_RangeDamage_doubleSpinBox->value());
    unit.setCharge(ui->Right_ChargeBonus_doubleSpinBox->value());
    unit.setArmorPiercing(ui->Right_ArmorPirecing_doubleSpinBox->value());
}


// Modify the doesCounter function to return the matching AntiTag
AntiTag doesCounter(const Unit& unit1, const Unit& unit2) {
    auto unit1AntiTags = unit1.getAntiTags();
    auto unit2Tags = unit2.getTags();

    // Sprawdzamy, czy jakikolwiek z antytagów unit1 pasuje do tagów unit2
    for (const AntiTag& antiTag : unit1AntiTags) {
        // Tutaj nie musimy już usuwać "Anti ", ponieważ zakładamy, że tagi są już odpowiednio nazwane
        QString counteredTagName = antiTag.name.mid(5); // Usuń "Anti " z początku, jeśli jest potrzebne

        // Zamiast porównywać stringi, musimy teraz sprawdzić, czy nazwa antytagu (bez "Anti ") znajduje się w tagach unit2
        if (unit2Tags.contains(counteredTagName)) {
            return antiTag; // Return the matching AntiTag when found
        }
    }

    // Return an empty AntiTag if no match is found
    return AntiTag{"", 0.0};
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    UnitDataManager.loadUnitsFromJson("Unit_DT.json");
    Units = UnitDataManager.getUnits();

    for(const Unit& unit : Units) {
        QString unitName = unit.getUnitName();
        ui->Left_Name_comboBox->addItem(unitName);
        ui->Right_Name_comboBox->addItem(unitName);
    }

    ui->Left_HP_label->setText(HP_LABEL);
    ui->Left_MeeleDamge_label->setText(MD_LABEL);
    ui->Left_RangeDamge_label->setText(RD_LABEL);
    ui->Left_Stamina_label->setText(ST_LABEL);
    ui->Left_ChargeBonus_label->setText(CB_LABEL);
    ui->Left_Shield_label->setText(SH_LABEL);
    ui->Left_Armor_label->setText(AR_LABEL);
    ui->Left_ArmorPirecing_label->setText(AP_LABEL);

    ui->Right_HP_label->setText(HP_LABEL);
    ui->Right_MeeleDamge_label->setText(MD_LABEL);
    ui->Right_RangeDamge_label->setText(RD_LABEL);
    ui->Right_Stamina_label->setText(ST_LABEL);
    ui->Right_ChargeBonus_label->setText(CB_LABEL);
    ui->Right_Shield_label->setText(SH_LABEL);
    ui->Right_Armor_label->setText(AR_LABEL);
    ui->Right_ArmorPirecing_label->setText(AP_LABEL);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Left_Name_comboBox_currentTextChanged(const QString &arg1)
{
    for (const Unit& unit : Units) {
        if (unit.getUnitName() == arg1) {
            ui->Left_HP_doubleSpinBox->setValue(unit.getHp());
            ui->Left_MeeleDamge_doubleSpinBox->setValue(unit.getMeleeDamage());
            ui->Left_RangeDamage_doubleSpinBox->setValue(unit.getRangeDamage());
            ui->Left_Stamina_doubleSpinBox->setValue(unit.getStamina());
            ui->Left_ChargeBonus_doubleSpinBox->setValue(unit.getCharge());
            ui->Left_Shield_doubleSpinBox->setValue(unit.getShield());
            ui->Left_Armor_doubleSpinBox->setValue(unit.getArmor());
            ui->Left_ArmorPirecing_doubleSpinBox->setValue(unit.getArmorPiercing());

            break;
        }
    }
}


void MainWindow::on_Right_Name_comboBox_currentTextChanged(const QString &arg1)
{
    for (const Unit& unit : Units) {
        if (unit.getUnitName() == arg1) {
            ui->Right_HP_doubleSpinBox->setValue(unit.getHp());
            ui->Right_MeeleDamge_doubleSpinBox->setValue(unit.getMeleeDamage());
            ui->Right_RangeDamage_doubleSpinBox->setValue(unit.getRangeDamage());
            ui->Right_Stamina_doubleSpinBox->setValue(unit.getStamina());
            ui->Right_ChargeBonus_doubleSpinBox->setValue(unit.getCharge());
            ui->Right_Shield_doubleSpinBox->setValue(unit.getShield());
            ui->Right_Armor_doubleSpinBox->setValue(unit.getArmor());
            ui->Right_ArmorPirecing_doubleSpinBox->setValue(unit.getArmorPiercing());
            break;
        }
    }
}


void MainWindow::on_Attack_pushButton_clicked()
{
    double result = 0.0;
    double counteredValue = 0.0;
    // Pobierz nazwy jednostek z obu comboBoxów
    QString leftUnitName = ui->Left_Name_comboBox->currentText();
    QString rightUnitName = ui->Right_Name_comboBox->currentText();

    // Znajdź jednostki na podstawie nazw
    Unit leftUnit, rightUnit;
    bool leftFound = false, rightFound = false;

    for (const Unit& unit : Units) {
        if (unit.getUnitName() == leftUnitName) {
            leftUnit = unit;
            leftFound = true;
        }
        if (unit.getUnitName() == rightUnitName) {
            rightUnit = unit;
            rightFound = true;
        }
        if (leftFound && rightFound) break; // Zakończ pętlę, jeśli znaleziono obie jednostki
    }

    // Sprawdź, czy jednostki zostały znalezione
    if (!leftFound || !rightFound) {
        qDebug() << "Nie można znaleźć jednej lub obu jednostek";
        return;
    }

    // Użyj funkcji doesCounter() do sprawdzenia, czy lewa jednostka kontruje prawą
    AntiTag counteredAntiTag = doesCounter(leftUnit, rightUnit);
    if (!counteredAntiTag.name.isEmpty()) {
        // Access the value of the countered AntiTag
        counteredValue = counteredAntiTag.value;

    }


    updateUnitStatsFromLeftUI(leftUnit);
    updateUnitStatsFromRightUI(rightUnit);
    // Pobierz atrybuty jednostek przy użyciu getUnitAttributes
    UnitAttributes leftAttributes = getUnitAttributes(leftUnit);
    UnitAttributes rightAttributes = getUnitAttributes(rightUnit);

  //leftAttributes.meleeDamage =69;


    double armorResultant =  leftAttributes.armorPiercing-rightAttributes.armor;
    if(armorResultant > 0) armorResultant = 0.0;

    result = leftAttributes.meleeDamage + leftAttributes.stamina*leftAttributes.chargeBonus +  counteredValue  + armorResultant;


    if(result <= 0) result =1;
    ui->Result_label->setNum(result);
}



void MainWindow::on_AttackRange_pushButton_clicked()
{
    double result = 0.0;
    double counteredValue = 0.0;
    // Pobierz nazwy jednostek z obu comboBoxów
    QString leftUnitName = ui->Left_Name_comboBox->currentText();
    QString rightUnitName = ui->Right_Name_comboBox->currentText();

    // Znajdź jednostki na podstawie nazw
    Unit leftUnit, rightUnit;
    bool leftFound = false, rightFound = false;

    for (const Unit& unit : Units) {
        if (unit.getUnitName() == leftUnitName) {
            leftUnit = unit;
            leftFound = true;
        }
        if (unit.getUnitName() == rightUnitName) {
            rightUnit = unit;
            rightFound = true;
        }
        if (leftFound && rightFound) break; // Zakończ pętlę, jeśli znaleziono obie jednostki
    }

    // Sprawdź, czy jednostki zostały znalezione
    if (!leftFound || !rightFound) {
        qDebug() << "Nie można znaleźć jednej lub obu jednostek";
        return;
    }

    // Użyj funkcji doesCounter() do sprawdzenia, czy lewa jednostka kontruje prawą
    AntiTag counteredAntiTag = doesCounter(leftUnit, rightUnit);
    if (!counteredAntiTag.name.isEmpty()) {
        // Access the value of the countered AntiTag
        counteredValue = counteredAntiTag.value;

    }

    updateUnitStatsFromLeftUI(leftUnit);
    updateUnitStatsFromRightUI(rightUnit);

    // Pobierz atrybuty jednostek przy użyciu getUnitAttributes
    UnitAttributes leftAttributes = getUnitAttributes(leftUnit);
    UnitAttributes rightAttributes = getUnitAttributes(rightUnit);

    double armorResultant =  leftAttributes.armorPiercing - rightAttributes.shield -  rightAttributes.armor;
    if(armorResultant > 0) armorResultant = 0.0;

    result = leftAttributes.rangeDamage  +leftAttributes.stamina*leftAttributes.chargeBonus +  counteredValue + armorResultant;

    // double armorResultant =  leftAttributes.armorPiercing-rightAttributes.armor;
    // if(armorResultant > 0) armorResultant = 0.0;

    // result = leftAttributes.meleeDamage + leftAttributes.stamina*leftAttributes.chargeBonus +  counteredValue  + armorResultant;


    if(result <= 0) result =1;
    ui->Result_label->setNum(result);
}

