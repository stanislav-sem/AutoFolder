#include "autofolder.h"
#include "ui_autofolder.h"

autoFolder::autoFolder(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::autoFolder)
    , m_targetFolder{}
    , m_templateFile{}

{
    ui->setupUi(this);
    m_icon = new QIcon(":/new/prefix1/folders.png");
    //QWindow::setIcon(m_icon);
    setWindowIcon(*m_icon);

    btnCreate = new QPushButton("Создать");
    ui->buttonBox->addButton(btnCreate, QDialogButtonBox::ButtonRole::ActionRole);
    btnOpen = new QPushButton("Открыть папку");
    ui->buttonBox->addButton(btnOpen, QDialogButtonBox::ButtonRole::ActionRole);

    connect(btnCreate, &QPushButton::clicked, this, &autoFolder::sltCreate);
    connect(btnOpen, &QPushButton::clicked, this, &autoFolder::sltOpen);

    btnCreate->setEnabled(false);
    btnOpen->setEnabled(false);
}

autoFolder::~autoFolder()
{
    delete ui;
}

void autoFolder::on_buttonBox_rejected()
{
    reject();
}

//select target folder
void autoFolder::on_btnTargetFolder_clicked()
{
    m_targetFolder = QFileDialog::getExistingDirectory(this, "Where to put project folder?");
    if (m_targetFolder.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "You must select target folder");
        return;
    }
    ui->btnTemplate->setEnabled(true);
}

//select template file
void autoFolder::on_btnTemplate_clicked()
{
    m_templateFile = QFileDialog::getOpenFileName(this, "Select template file", QDir::currentPath(), "Text files (*.txt)");
    if (m_templateFile.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "You must select template file");
        return;
    }
    ui->label->setEnabled(true);
    ui->txtProjectName->setEnabled(true);

}

//button "Create" clicked
void autoFolder::sltCreate()
{
    QString projectName = ui->txtProjectName->text();
    if (projectName == " " or projectName.isEmpty()) {
        QMessageBox::critical(this, "Error!", "Folder name couldn't be empty.");
        ui->label->setEnabled(false);
        ui->txtProjectName->setEnabled(false);
        return;
    }

    QDir dir(m_targetFolder);

    //check if projectName folder already exist
    if (dir.exists(projectName)) {
        QMessageBox::information(this, "OOPS!", "Folder " + projectName + " alredy exist.");
        return;
    } else {
        dir.mkdir(projectName);
        dir.setPath(m_targetFolder + "/" + projectName);
    }


    //open template file
    QFile tmpFile(m_templateFile, this);
    if (!tmpFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error!", "Couldn't open template file.");
        return;
    }

    //read template file and create subdir
    QTextStream input(&tmpFile);
    QString line{};
    while (!input.atEnd()) {
        line = input.readLine();
        dir.mkpath(line);
    }

    dir.setPath(m_targetFolder + "/" + projectName + "/" + line);
    if (dir.exists()) {
        QMessageBox::information(this, "Information", "Project folder and subfolder successfully created.\n" + m_targetFolder + "/" + projectName);
    }

    //closing file to prevent memoty leak
    tmpFile.close();
}

//button "Open" clicked
void autoFolder::sltOpen()
{
    QString projectPath =m_targetFolder + "/" + ui->txtProjectName->text();
    if (!QDir(projectPath).exists()) {
        QMessageBox::critical(this, "Error!", "Folder doesn't exist.");
        return;
    }
    QDesktopServices::openUrl(QUrl::fromLocalFile(projectPath));
}

void autoFolder::on_txtProjectName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    btnCreate->setEnabled(true);
    btnOpen->setEnabled(true);
}

