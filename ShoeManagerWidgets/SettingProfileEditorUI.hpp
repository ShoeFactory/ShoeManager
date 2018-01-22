#ifndef PROFILEEDITORUI_HPP
#define PROFILEEDITORUI_HPP

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

class SettingProfileEditorUI : public QWidget
{
    Q_OBJECT
public:
    explicit SettingProfileEditorUI(QWidget *parent = nullptr);

    void initLayout();
    void initConnection();

signals:

public slots:
    void updatePasswdClicked();
    void updateNameClicked();

private:
    QLabel *pLabelNewPasswd;
    QLabel *pLabelNewPasswdConfirm;
    QLineEdit *pLineNewPasswd;
    QLineEdit *pLineNewPasswdConfirm;
    QPushButton *pButtonUpdatePasswd;

    QLabel *pLabelNewName;
    QLineEdit *pLineNewName;
    QPushButton *pButtonUpdateName;
};

#endif // PROFILEEDITORUI_HPP
