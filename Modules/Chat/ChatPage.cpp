#include "Include/Chat/ChatPage.h"

#include "List/Ui/ChatListWidget.h"
#include "List/Core/Models/ChatListModel.h"

#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QSplitter>
#include <QVBoxLayout>

ChatPage::ChatPage(QWidget* parent) : QWidget(parent)
{
    auto* pMainLayout = new QVBoxLayout(this);
    setMinimumSize(1060, 650);

    auto* pSearchLineEdit = new QLineEdit;
    pSearchLineEdit->setPlaceholderText("Search");
    pSearchLineEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    auto* pListView = new ChatListWidget;
    auto* pModel    = new ChatListModel;
    pListView->setModel(pModel);

    pModel->addItem({"Nastya", "Voice message", QPixmap(":/icons/not_found.png"), 1});
    pModel->addItem({"Me", "Nice", QPixmap(":/icons/not_found.png"), 1});

    QWidget*     placeholderWidget = new QWidget;
    QVBoxLayout* layout            = new QVBoxLayout(placeholderWidget);

    QLabel* label = new QLabel(kChatPlaceholderText);
    label->setAlignment(Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(label);
    layout->addStretch();

    // pSplitter->addWidget(pListView);
    // pSplitter->addWidget(pChatNotSelected);

    auto* pSearchAndChatListLayout = new QVBoxLayout;
    pSearchAndChatListLayout->addWidget(pSearchLineEdit);
    pSearchAndChatListLayout->addWidget(pListView);
    pSearchAndChatListLayout->setContentsMargins(0, 0, 0, 0);
    auto* pCombinedWidget = new QWidget;
    pCombinedWidget->setLayout(pSearchAndChatListLayout);
    pCombinedWidget->setMinimumWidth(200);

    auto* pSplitter = new QSplitter;
    pSplitter->addWidget(pCombinedWidget);
    pSplitter->addWidget(placeholderWidget);
    pSplitter->setCollapsible(0, false);
    pSplitter->setCollapsible(1, false);
    pSplitter->setSizes({300, 700});

    pMainLayout->addWidget(pSplitter);
    pMainLayout->setContentsMargins(5, 5, 5, 5);
    pMainLayout->setAlignment(Qt::AlignHCenter);
    pMainLayout->setSpacing(5);

    this->setMouseTracking(true);
}
