#ifndef MANAGER_H
#define MANAGER_H

#include <QtGui>
#include <QtCore>
#include <QTranslator>
#include <jm/system/app.h>
#include "scanner.h"
#include "scannerpresenter.h"
#include "messagebox.h"
#include "messageboxpresenter.h"
#include "menu.h"
#include "menupresenter.h"
#include "troublecode.h"
#include "troublecodepresenter.h"
#include "livedataprepare.h"
#include "livedatapreparepresenter.h"
#include "livedata.h"
#include "livedatapresenter.h"
#include "setting.h"

class Manager : public QApplication
{
    Q_OBJECT
public:
    explicit Manager(int &argc, char **argv);
    ~Manager();
    void addWindow(const QString &key, QWidget *widget);
    QWidget *window();

    ScannerPresenter* scannerPresenter() const;
    MessageBoxPresenter* messageBoxPresenter() const;
    MenuPresenter* menuPresenter() const;
    TroubleCodePresenter* troubleCodePresenter() const;
    LiveDataPreparePresenter* liveDataPreparePresenter() const;
    LiveDataPresenter* liveDataPresenter() const;
private:
    void loadTranslateFiles();
    void scannerInit();
    void msgBoxInit();
    void menuInit();
    void troubleCodeInit();
    void liveDataPrepareInit();
    void liveDataInit();
    void dealMsg(JM::UI::Message::Msg *msg);
public slots:
    void switchWindow();
    int exec();
private slots:
    void uiUpdate();
private:
    QWidget *_currentWindow;
    QHash<QString, QWidget*> _windowHash;
    QWidget _window;
    QVBoxLayout _layout;

    QTranslator _ts;

    Scanner *_scannerWindow;
    ScannerPresenter *_scannerPresenter;
    MsgBox *_msgBox;
    MessageBoxPresenter *_msgBoxPresenter;
    Menu *_menu;
    MenuPresenter *_menuPresenter;
    TroubleCode *_troubleCode;
    TroubleCodePresenter *_troubleCodePresenter;
    LiveDataPrepare *_liveDataPrepare;
    LiveDataPreparePresenter *_liveDataPreparePresenter;
    LiveData *_liveData;
    LiveDataPresenter *_liveDataPresenter;

    QTimer *_uiTimer;
};

#endif