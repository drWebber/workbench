#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <qsettings.h>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    QString browseFile();
    QString browseDir();
private slots:
    void on_pbnBrowseMysqlDump_clicked();
    void on_pbhBrowseBupDir_clicked();
    void on_pbnSaveSettings_accepted();

    void on_pbnSaveSettings_rejected();

private:
    Ui::Settings *ui;
    QSettings settings;
};

#endif // SETTINGS_H
