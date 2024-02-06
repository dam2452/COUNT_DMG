#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>

#include "unit.h"
#include "unitdatamanager.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"



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
            ui->Left_DMGMeele_doubleSpinBox->setValue(unit.getMeleeDamage());
            ui->Left_DMGRange_doubleSpinBox->setValue(unit.getRangeDamage());
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
            ui->Right_DMGMeele_doubleSpinBox->setValue(unit.getMeleeDamage());
            ui->Right_DMGRange_doubleSpinBox->setValue(unit.getRangeDamage());
            ui->Right_Stamina_doubleSpinBox->setValue(unit.getStamina());
            ui->Right_ChargeBonus_doubleSpinBox->setValue(unit.getCharge());
            ui->Right_Shield_doubleSpinBox->setValue(unit.getShield());
            ui->Right_Armor_doubleSpinBox->setValue(unit.getArmor());
            ui->Right_ArmorPirecing_doubleSpinBox->setValue(unit.getArmorPiercing());

            break;
        }
    }
}

