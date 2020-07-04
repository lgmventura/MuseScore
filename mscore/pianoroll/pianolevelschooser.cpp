#include "pianolevelschooser.h"
#include "pianolevelsfilter.h"
#include "pianoroll.h"

#include "pianorollset.h"

#include "libmscore/score.h"

namespace Ms {

//---------------------------------------------------------
//   PianoLevelsChooser
//---------------------------------------------------------

PianoLevelsChooser::PianoLevelsChooser(QWidget *parent)
      : QWidget(parent)
{
      setupUi(this);

      _levelsIndex = 0;

      for (int i = 0; PianoLevelsFilter::FILTER_LIST[i]; ++i) {
            QString name = PianoLevelsFilter::FILTER_LIST[i]->name();
            levelsCombo->addItem(name, i);
            levelsCombo->setItemData(i, PianoLevelsFilter::FILTER_LIST[i]->tooltip(), Qt::ToolTipRole);
            }

      connect(levelsCombo, SIGNAL(activated(int)), SLOT(setLevelsIndex(int)));
      connect(setEventsBn, SIGNAL(clicked(bool)), SLOT(setEventDataPressed()));
}


//---------------------------------------------------------
//   PianoLevelsChooser
//---------------------------------------------------------

void PianoLevelsChooser::setLevelsIndex(int index)
{
      if (_levelsIndex != index) {
            _levelsIndex = index;
            emit levelsIndexChanged(index);
            }
}


//---------------------------------------------------------
//   PianoLevelsChooser
//---------------------------------------------------------

void PianoLevelsChooser::setEventDataPressed()
      {
            PianoRollSet* pianoRollSet = new PianoRollSet;
            pianoRollSet->setStaff(_staff);
            pianoRollSet->setWindowTitle("Set");
            pianoRollSet->show();
            emit notesChanged();
      }

}
