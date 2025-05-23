#ifndef CHAT_LIST_WIDGET_H
#include <QListView>

class ChatListWidget : public QListView
{
    Q_OBJECT
public:
    explicit ChatListWidget(QWidget* parent = nullptr);
};

#endif  //! CHAT_LIST_WIDGET_H
