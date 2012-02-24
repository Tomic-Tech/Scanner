#ifndef MANAGER_H
#define MANAGER_H

#include <QtGui>
#include <QTranslator>
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

class UIThread;

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
public slots:
    void switchWindow();
    int exec();
private:
    QWidget *_currentWindow;
    QHash<QString, QWidget*> _windowHash;
    QWidget _window;
    QVBoxLayout _layout;

    QTranslator _ts;

    Scanner *_scannerWindow;
    ScannerPresenter *_scannerPresenter;
    MessageBox *_msgBox;
    MessageBoxPresenter *_msgBoxPresenter;
    Menu *_menu;
    MenuPresenter *_menuPresenter;
    TroubleCode *_troubleCode;
    TroubleCodePresenter *_troubleCodePresenter;
    LiveDataPrepare *_liveDataPrepare;
    LiveDataPreparePresenter *_liveDataPreparePresenter;
    LiveData *_liveData;
    LiveDataPresenter *_liveDataPresenter;

    UIThread *_thread;
};

#endif