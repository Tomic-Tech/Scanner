#include "manager.h"
#include <jm/jmlib.h>
#include "register.h"
#include "utils.h"

Manager::Manager(int &argc, char **argv)
    : QApplication(argc, argv)
    , _currentWindow(0)
    , _windowHash()
    , _uiTimer(new QTimer(this))
{
    QString dir = qApp->applicationDirPath().append(G_DIR_SEPARATOR_S);
    jm_lib_init(dir.toUtf8().data());

    _window.setWindowTitle(trUtf8("JMScanner"));
    _window.setLayout(&_layout);
    _layout.setContentsMargins(0, 0, 0, 0);

    qApp->setQuitOnLastWindowClosed(true);
    connect(&_window, SIGNAL(destroyed()), qApp, SLOT(quit()));

    loadTranslateFiles();

    scannerInit();
    msgBoxInit();
    menuInit();
    troubleCodeInit();
    liveDataPrepareInit();
    liveDataInit();

    //_thread->start();
    connect(_uiTimer, SIGNAL(timeout()), this, SLOT(uiUpdate()));
    _uiTimer->start(1);
}

Manager::~Manager()
{
    //_thread->stop();
    //delete _thread;
    delete _uiTimer;
    delete _liveDataPresenter;
    delete _liveData;
    delete _liveDataPreparePresenter;
    delete _liveDataPrepare;
    delete _troubleCodePresenter;
    delete _troubleCode;
    delete _menuPresenter;
    delete _menu;
    delete _msgBoxPresenter;
    delete _msgBox;
    delete _scannerPresenter;
    delete _scannerWindow;
    jm_lib_destroy();
}

void Manager::loadTranslateFiles()
{
    QString fileName = QString::fromUtf8("%1"G_DIR_SEPARATOR_S"%2")
        .arg(qApp->applicationDirPath())
        .arg(UtilsInst().getTheSystemLang());
    if (_ts.load(fileName))
        qApp->installTranslator(&_ts);
}

void Manager::scannerInit()
{
    _scannerPresenter = new ScannerPresenter(this);
    _scannerWindow = new Scanner();

    _scannerPresenter->setObjectName("ScannerPresenter");
    addWindow(_scannerPresenter->objectName(), _scannerWindow);

    connect(_scannerWindow->thread(), SIGNAL(finished()), 
        _scannerPresenter, SLOT(show()));
    connect(_scannerPresenter, SIGNAL(switchWindow()), this, 
        SLOT(switchWindow()));
}

void Manager::msgBoxInit()
{
    _msgBoxPresenter = new MessageBoxPresenter(this);
    _msgBox = new MessageBox();

    connect(_msgBoxPresenter, SIGNAL(sendShow()), _msgBox, SLOT(show()));
    connect(_msgBoxPresenter, SIGNAL(sendHide()), _msgBox, SLOT(hide()));
    connect(_msgBoxPresenter, SIGNAL(sendAddBtn(QString)), 
        _msgBox->dynamicButtons(), SLOT(addBtn(QString)));
    connect(_msgBoxPresenter, SIGNAL(sendBtnClr()), 
        _msgBox->dynamicButtons(), SLOT(btnClr()));
    connect(_msgBoxPresenter, SIGNAL(sendSetMsg(QString)), _msgBox, 
        SLOT(setMsg(QString)));
    connect(_msgBoxPresenter, SIGNAL(sendSetTitle(QString)), _msgBox, 
        SLOT(setTitle(QString)));
    connect(_msgBox->dynamicButtons(), SIGNAL(sendBtnClk(QString)), 
        _msgBox->dynamicButtons(), SLOT(defaultBtnClked(QString)));
}

void Manager::menuInit()
{
    _menuPresenter = new MenuPresenter(this);
    _menu = new Menu();

    _menuPresenter->setObjectName("MenuPresenter");
    addWindow(_menuPresenter->objectName(), _menu);

    connect(_menuPresenter, SIGNAL(sendAddItem(QString)), _menu, 
        SLOT(addItem(QString)));
    connect(_menuPresenter, SIGNAL(sendItemClr()), _menu, 
        SLOT(itemClr()));
    connect(_menuPresenter, SIGNAL(switchWindow()), this, 
        SLOT(switchWindow()));
}

void Manager::troubleCodeInit()
{

    _troubleCodePresenter = new TroubleCodePresenter(this);
    _troubleCode = new TroubleCode();

    _troubleCodePresenter->setObjectName("TroubleCodePresenter");
    addWindow(_troubleCodePresenter->objectName(), _troubleCode);

    connect(_troubleCodePresenter, SIGNAL(sendAddBtn(QString)),
        _troubleCode->dynamicButtons(), SLOT(addBtn(QString)),
        Qt::QueuedConnection);
    connect(_troubleCodePresenter, SIGNAL(sendAddItem(QString,QString)),
        _troubleCode, SLOT(addItem(QString,QString)),
        Qt::QueuedConnection);
    connect(_troubleCodePresenter, SIGNAL(sendBtnClr()),
        _troubleCode->dynamicButtons(), SLOT(btnClr()),
        Qt::QueuedConnection);
    connect(_troubleCodePresenter, SIGNAL(sendItemClr()),
        _troubleCode, SLOT(itemClr()),
        Qt::QueuedConnection);
    connect(_troubleCode->dynamicButtons(), SIGNAL(sendBtnClk(QString)),
        _troubleCode->dynamicButtons(), SLOT(defaultBtnClked(QString)),
        Qt::QueuedConnection);
    connect(_troubleCodePresenter, SIGNAL(switchWindow()),
        this, SLOT(switchWindow()));
}

void Manager::liveDataPrepareInit()
{
    _liveDataPreparePresenter = new LiveDataPreparePresenter(this);
    _liveDataPrepare = new LiveDataPrepare();

    _liveDataPreparePresenter->setObjectName("LiveDataPreparePresenter");
    addWindow(_liveDataPreparePresenter->objectName(), _liveDataPrepare);

    //connect(_liveDataPreparePresenter, SIGNAL(sendShow()), _liveDataPrepare, SLOT(show()));
    connect(_liveDataPreparePresenter, SIGNAL(switchWindow()), this, 
        SLOT(switchWindow()));
}

void Manager::liveDataInit()
{
    _liveDataPresenter = new LiveDataPresenter(this);
    _liveData = new LiveData();

    _liveDataPresenter->setObjectName("LiveDataPresenter");
    addWindow(_liveDataPresenter->objectName(), _liveData);

    connect(_liveDataPresenter, SIGNAL(sendSetValue(int, QString)), 
        _liveData, SLOT(setValue(int, QString)));
    connect(_liveDataPresenter, SIGNAL(switchWindow()), this, 
        SLOT(switchWindow()));
    connect(_liveDataPresenter, SIGNAL(sendAddBtn(QString)), 
        _liveData->dynamicButtons(), SLOT(addBtn(QString)));
    connect(_liveDataPresenter, SIGNAL(sendBtnClr()), 
        _liveData->dynamicButtons(), SLOT(btnClr()));
    connect(_liveData->dynamicButtons(), SIGNAL(sendBtnClk(QString)), 
        _liveData->dynamicButtons(), SLOT(defaultBtnClked(QString)));
}

void Manager::addWindow(const QString &key, QWidget *widget)
{
    widget->hide();
    widget->setParent(&_window);
    _layout.addWidget(widget);
    _windowHash.insert(key, widget);
}

int Manager::exec()
{
    if (!jm_auth_check_reg())
    {
        Register r;
        if (r.exec() != QDialog::Accepted)
        {
            return 0;
        }
    }
    _scannerPresenter->show();
    _window.showMaximized();
    return QApplication::exec();
}

QWidget* Manager::window()
{
    return &_window;
}

void Manager::switchWindow()
{
    if (_currentWindow != _windowHash.value(sender()->objectName()))
    {
        QWidget *oldWindow = _currentWindow;
        _currentWindow = _windowHash.value(sender()->objectName());
        _currentWindow->show();
        if (0 != oldWindow)
            oldWindow->hide();
    }
}

ScannerPresenter* Manager::scannerPresenter() const
{
    return _scannerPresenter;
}

MessageBoxPresenter* Manager::messageBoxPresenter() const
{
    return _msgBoxPresenter;
}

MenuPresenter* Manager::menuPresenter() const
{
    return _menuPresenter;
}

TroubleCodePresenter* Manager::troubleCodePresenter() const
{
    return _troubleCodePresenter;
}

LiveDataPreparePresenter* Manager::liveDataPreparePresenter() const
{
    return _liveDataPreparePresenter;
}

LiveDataPresenter* Manager::liveDataPresenter() const
{
    return _liveDataPresenter;
}

void Manager::dealMsg(JMUIMessage *msg)
{
    if (msg != NULL)
    {
        switch(msg->type)
        {
        case JM_UI_MSG_BOX_BTN_CLR:
            messageBoxPresenter()->btnClr();
            break;
        case JM_UI_MSG_BOX_ADD_BTN:
            messageBoxPresenter()->addBtn(QString::fromUtf8(msg->message));
            break;
        case JM_UI_MSG_BOX_SET_MSG:
            messageBoxPresenter()->setMsg(QString::fromUtf8(msg->message));
            break;
        case JM_UI_MSG_BOX_SET_TITLE:
            messageBoxPresenter()->setTitle(QString::fromUtf8(msg->message));
            break;
        case JM_UI_MSG_BOX_SHOW:
            messageBoxPresenter()->show();
            break;
        case JM_UI_MSG_BOX_HIDE:
            messageBoxPresenter()->hide();
            break;
        case JM_UI_MENU_ITEM_CLR:
            menuPresenter()->itemClr();
            break;
        case JM_UI_MENU_ADD_ITEM:
            menuPresenter()->addItem(QString::fromUtf8(msg->message));
            break;
        case JM_UI_MENU_SHOW:
            menuPresenter()->show();
            break;
        case JM_UI_TC_ITEM_CLR:
            troubleCodePresenter()->itemClr();
            break;
        case JM_UI_TC_ADD_ITEM:
            {
                QString str = QString::fromUtf8(msg->message);
                QStringList strl = str.split(QChar('|'));
                troubleCodePresenter()->addItem(strl[0], strl[1]);
            }
            break;
        case JM_UI_TC_ADD_BTN:
            troubleCodePresenter()->addBtn(QString::fromUtf8(msg->message));
            break;
        case JM_UI_TC_BTN_CLR:
            troubleCodePresenter()->btnClr();
            break;
        case JM_UI_TC_SHOW:
            troubleCodePresenter()->show();
            break;
        case JM_UI_LD_PREPARE_SHOW:
            liveDataPreparePresenter()->show();
            break;
        case JM_UI_LD_SHOW:
            liveDataPresenter()->show();
            break;
        case JM_UI_LD_BTN_CLR:
            liveDataPresenter()->btnClr();
            break;
        case JM_UI_LD_ADD_BTN:
            liveDataPresenter()->addBtn(QString::fromUtf8(msg->message));
            break;
        case JM_UI_LD_SET_VALUE:
            {
                QStringList strl = 
                    QString::fromUtf8(msg->message).split(QChar('|'));
                int index = strl[0].toInt();
                QString value = strl[1];
                liveDataPresenter()->setValue(index, value);
            }
            break;
        default:
            break;
        }
        jm_ui_msg_free(msg);
    }
}

void Manager::uiUpdate()
{
    size_t msg_count = jm_ui_msg_count();
    while(msg_count)
    {
        JMUIMessage *msg = jm_ui_pop_msg();
        dealMsg(msg);
        msg_count--;
    }

}