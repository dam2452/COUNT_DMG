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
            ui->Result_label->setText(unit.getKeywords()[0]);
            break;
        }
    }
}


void MainWindow::on_Attack_pushButton_clicked()
{
    double result=0.0;
    double MeeleDamage=0.0;

    //result =




   // ui->Result_label->setText("test");
}


void MainWindow::on_AttackRange_pushButton_clicked()
{
    //ui->Result_label->setText("test1");
}

