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

UnitAttributes getUnitAttributes(const QString& unitName, const QVector<Unit>& units) {
    for (const Unit& unitItem : units) {
        if (unitItem.getUnitName() == unitName) {
            return UnitAttributes(unitItem.getHp(), unitItem.getMeleeDamage(), unitItem.getRangeDamage(), unitItem.getStamina(),
                                  unitItem.getCharge(), unitItem.getShield(), unitItem.getArmor(), unitItem.getArmorPiercing());
        }
    }
    return UnitAttributes(0, 0, 0, 0, 0, 0, 0, 0); // Return empty attributes if unit not found
}




bool doesCounter(const Unit& unit1, const Unit& unit2) {
    auto unit1AntiTags = unit1.getAntiTags();
    auto unit2Tags = unit2.getTags();

    // Sprawdzamy, czy jakikolwiek z antytagów unit1 pasuje do tagów unit2
    for (const AntiTag& antiTag : unit1AntiTags) {
        // Tutaj nie musimy już usuwać "Anti ", ponieważ zakładamy, że tagi są już odpowiednio nazwane
        QString counteredTagName = antiTag.name.mid(5); // Usuń "Anti " z początku, jeśli jest potrzebne

        // Zamiast porównywać stringi, musimy teraz sprawdzić, czy nazwa antytagu (bez "Anti ") znajduje się w tagach unit2
        if (unit2Tags.contains(counteredTagName)) {
            return true; // Unit1 kontruje unit2, jeśli jeden z jego antytagów pasuje do tagu unit2
        }
    }

    return false; // Nie znaleziono pasujących antytagów, więc unit1 nie kontruje unit2
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
    int counterValue = 0;
    double result = 0.0;

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
    if (doesCounter(leftUnit, rightUnit)) {
        qDebug() << leftUnitName << "kontruje" << rightUnitName;
        counterValue = 1;
    } else {
        qDebug() << leftUnitName << "nie kontruje" << rightUnitName;
        counterValue = 0;
    }

    // Pobierz atrybuty jednostek przy użyciu getUnitAttributes
    UnitAttributes leftAttributes = getUnitAttributes(leftUnitName, Units);
    UnitAttributes rightAttributes = getUnitAttributes(rightUnitName, Units);


    result = leftAttributes.hp - rightAttributes.hp;

    ui->Result_label->setNum(result);
}



void MainWindow::on_AttackRange_pushButton_clicked()
{
    //ui->Result_label->setText("test1");
}

