#ifndef AUTOFOLDER_H
#define AUTOFOLDER_H

#include <QDialog>
#include <QDir>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDesktopServices>
#include <QIcon>



QT_BEGIN_NAMESPACE
namespace Ui { class autoFolder; }
QT_END_NAMESPACE

class autoFolder : public QDialog
{
    Q_OBJECT

public:
    autoFolder(QWidget *parent = nullptr);
    ~autoFolder();

private slots:
    void on_buttonBox_rejected();
    void sltCreate();
    void sltOpen();

    void on_btnTargetFolder_clicked();

    void on_btnTemplate_clicked();

    void on_txtProjectName_textChanged(const QString &arg1);

private:
    Ui::autoFolder *ui;
    QPushButton *btnCreate;
    QPushButton *btnOpen;
    QString m_targetFolder;
    QString m_templateFile;
    QIcon *m_icon;

};
#endif // AUTOFOLDER_H
