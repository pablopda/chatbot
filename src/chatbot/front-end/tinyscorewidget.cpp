#include "tinyscorewidget.h"
#include "ui_tinyscorewidget.h"


//--------------------------------------------------------------------------------------------------
// TinyScoreWidget
//--------------------------------------------------------------------------------------------------

Lvk::FE::TinyScoreWidget::TinyScoreWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::TinyScoreWidget)
{
    ui->setupUi(this);

    clear();
}

//--------------------------------------------------------------------------------------------------

Lvk::FE::TinyScoreWidget::~TinyScoreWidget()
{
    delete ui;
}

//--------------------------------------------------------------------------------------------------

void Lvk::FE::TinyScoreWidget::clear()
{
    ui->scoreLabel->clear();
    ui->timeLabel->clear();
}

//--------------------------------------------------------------------------------------------------

void Lvk::FE::TinyScoreWidget::setScore(const BE::Score &current, const BE::Score &best)
{
    QString text = QString(tr("%1 / %2")).arg(QString::number(current.total),
                                                                    QString::number(best.total));

    ui->scoreLabel->setText(text);
}

//--------------------------------------------------------------------------------------------------

void Lvk::FE::TinyScoreWidget::setRemainingTime(const QTime &time)
{
    QString text = QString(tr("%1")).arg(time.toString("hh:mm:ss"));

    ui->timeLabel->setText(text);
}
