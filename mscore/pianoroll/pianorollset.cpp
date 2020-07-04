#include "pianorollset.h"
//#include "ui_pianorollset.h"
#include "pianolevelsfilter.h"

#include "pianolevelschooser.h"

#include "libmscore/score.h"

namespace Ms {

PianoRollSet::PianoRollSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PianoRollSet)
{
    ui->setupUi(this);
}

PianoRollSet::~PianoRollSet()
{
    delete ui;
}

void PianoRollSet::on_buttonBox_accepted()
{
    PianoLevelsFilter* filter = PianoLevelsFilter::FILTER_LIST[_levelsIndex]; // filter selected properties (e.g. velocity relative)

    bool offset = offsetRb->isChecked(); // GUI radio button
    int val = eventValSpinBox->value(); // GUI value
    int currVal = 0; // initializing current value as 0
    int randVal = 0; // initializing randVal as 0
    QList<Note*> noteList = _staff->getNotes();

    Score* score = _staff->score();

    score->startCmd();

    // initialize random seed:
    std::srand(eventSeedSpinBox->value());

    for (Note* note: noteList) {
          if (!note->selected())
                continue;

          // Generating a random integer from 0 to eventRandSpinBox->value()
          if (eventRandSpinBox->value() > 0) { // else it remains 0, as initialized
              randVal = std::rand()/((RAND_MAX + 1u)/eventRandSpinBox->value());
          }

          // applying set to selected notes:
          if (filter->isPerEvent()) {
                for (NoteEvent& e : note->playEvents()) {
                    // Getting current value assigned if using offset
                    if (offset == true) { // if user chose offset (radio button on the GUI)
                        currVal = filter->value(_staff, note, &e); // getting current value
                    }

                    filter->setValue(_staff, note, &e, currVal + val + randVal); // set new value
                 }
          }
          else
                    filter->setValue(_staff, note, nullptr, val + randVal);

          }

    score->endCmd();

//    emit notesChanged();
}

void PianoRollSet::on_buttonBox_rejected()
{
    delete ui;
}


} // namespace Ms

