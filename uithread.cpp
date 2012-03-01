#include "uithread.h"
#include "jm/jmui.h"

UIThread::UIThread(Manager *manager, QObject *parent /* = 0 */)
    : QThread(parent)
    , _isStop(false)
    , _manager(manager)
{

}

void UIThread::run()
{
    while (!_isStop)
    {
        JMUIMessage *msg = jm_ui_pop_msg();
        if (msg != NULL)
        {
            switch(msg->type)
            {
            case JM_UI_MSG_BOX_BTN_CLR:
                _manager->messageBoxPresenter()->btnClr();
                break;
            case JM_UI_MSG_BOX_ADD_BTN:
                _manager->messageBoxPresenter()->addBtn(QString::fromUtf8(msg->message));
                break;
            case JM_UI_MSG_BOX_SET_MSG:
                _manager->messageBoxPresenter()->setMsg(QString::fromUtf8(msg->message));
                break;
            case JM_UI_MSG_BOX_SET_TITLE:
                _manager->messageBoxPresenter()->setTitle(QString::fromUtf8(msg->message));
                break;
            case JM_UI_MSG_BOX_SHOW:
                _manager->messageBoxPresenter()->show();
                break;
            case JM_UI_MSG_BOX_HIDE:
                _manager->messageBoxPresenter()->hide();
                break;
            case JM_UI_MENU_ITEM_CLR:
                _manager->menuPresenter()->itemClr();
                break;
            case JM_UI_MENU_ADD_ITEM:
                _manager->menuPresenter()->addItem(QString::fromUtf8(msg->message));
                break;
            case JM_UI_MENU_SHOW:
                _manager->menuPresenter()->show();
                break;
            case JM_UI_TC_ITEM_CLR:
                _manager->troubleCodePresenter()->itemClr();
                break;
            case JM_UI_TC_ADD_ITEM:
                {
                    QString str = QString::fromUtf8(msg->message);
                    QStringList strl = str.split(QChar('|'));
                    _manager->troubleCodePresenter()->addItem(strl[0], strl[1]);
                }
                break;
            case JM_UI_TC_ADD_BTN:
                _manager->troubleCodePresenter()->addBtn(QString::fromUtf8(msg->message));
                break;
            case JM_UI_TC_BTN_CLR:
                _manager->troubleCodePresenter()->btnClr();
                break;
            case JM_UI_TC_SHOW:
                _manager->troubleCodePresenter()->show();
                break;
            case JM_UI_LD_PREPARE_SHOW:
                _manager->liveDataPreparePresenter()->show();
                break;
            case JM_UI_LD_SHOW:
                _manager->liveDataPresenter()->show();
                break;
            case JM_UI_LD_BTN_CLR:
                _manager->liveDataPresenter()->btnClr();
                break;
            case JM_UI_LD_ADD_BTN:
                _manager->liveDataPresenter()->addBtn(QString::fromUtf8(msg->message));
                break;
            case JM_UI_LD_SET_VALUE:
                {
                    QStringList strl = QString::fromUtf8(msg->message).split(QChar('|'));
                    int index = strl[0].toInt();
                    QString value = strl[1];
                    _manager->liveDataPresenter()->setValue(index, value);
                }
                break;
            default:
                break;
            }
            jm_ui_msg_free(msg);
        }
        QThread::yieldCurrentThread();
    }
}

void UIThread::stop()
{
    _isStop = true;
    while (isRunning());
}


