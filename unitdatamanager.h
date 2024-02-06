#ifndef UNITDATAMANAGER_H
#define UNITDATAMANAGER_H

#include <QString>
#include "unit.h"

class UnitDataManager
{
public:
    UnitDataManager();
    void loadUnitsFromJson(const QString &filePath);
    QVector<Unit> getUnits() const;


private:
    QVector<Unit> units;
};

#endif // UNITDATAMANAGER_H
