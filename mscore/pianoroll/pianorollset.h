#ifndef PIANOROLLSET_H
#define PIANOROLLSET_H

#include <QDialog>

#include "ui_pianorollset.h"

#include "libmscore/staff.h"

namespace Ui {
class PianoRollSet;
}

namespace Ms {

class PianoRollSet : public QDialog, public Ui::PianoRollSet
{
    Q_OBJECT

    int _levelsIndex;
    Staff* _staff;

public:
    explicit PianoRollSet(QWidget *parent = 0);
    ~PianoRollSet();

public:
      Staff* staff() { return _staff; }
      void setStaff(Staff* staff) { _staff = staff; }

      void setLevelsIndex(int index) {_levelsIndex = index; }

private slots:
      void on_buttonBox_accepted();

      void on_buttonBox_rejected();

private:
    Ui::PianoRollSet *ui;
};

}

#endif // PIANOROLLSET_H
