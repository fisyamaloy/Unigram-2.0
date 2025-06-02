#include "Include/Chat/ChatPage.h"

#include <Shared/Widgets/HamburgerButton.h>

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QSplitter>
#include <QTimer>
#include <QVBoxLayout>

#include "List/Core/Models/ChatListModel.h"
#include "List/Ui/ChatListWidget.h"
#include "Messages/Ui/MessageListWidget.h"
#include "Chat/ChatConversationArea.h"

ChatPage::ChatPage(QWidget* parent) : QWidget(parent)
{
    auto* pConversationArea = new ChatConversationArea(this);

    auto* pSplitter = new QSplitter;

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

    /*
    connect(pListView, &QListView::clicked, this, [=](const QModelIndex& index) {
        int row = index.row();
        if (!chatViews.contains(row))
        {
            auto* view = new MessageListWidget(this);

            for (int i = 0; i < 10; ++i)
                view->addMessage({pModel->data(index, ChatListModel::TitleRole).toString(),
                                  "Привет! Это тестовое сообщение. аывапывап ывап ывап ывап ывап ывапыавпржы валюпрд ывардп ывдарп ыдва "
                                  "поыывапывапывапывапывапывапдырвадпыварпдывапдывапдыважррфывж фыжва рфыжва рфыва фжыва 2345 346 345 "
                                  "634563456цуа ывап ывапывап уке234534е уапуапуарпарвапрпар",
                                  "14:55", pModel->data(index, ChatListModel::AvatarRole).value<QPixmap>()});

            chatViews[row] = view;
        }

        auto* newView = chatViews[row];
        newView->setMouseTracking(true);
        newView->installEventFilter(this);
        newView->viewport()->setMouseTracking(true);
        newView->viewport()->installEventFilter(this);

        pSplitter->replaceWidget(1, newView);
    });
    */

    connect(pListView, &QListView::clicked, this, [=](const QModelIndex& index) {
        int row = index.row();
        QString chatTitle = pModel->data(index, ChatListModel::TitleRole).toString();
        pConversationArea->showChatForRow(row, chatTitle);
        pSplitter->replaceWidget(1, pConversationArea);
    });

    QWidget*     placeholderWidget = new QWidget;
    QVBoxLayout* placeholderLayout = new QVBoxLayout(placeholderWidget);

    QLabel* label = new QLabel(kChatPlaceholderText);
    label->setAlignment(Qt::AlignCenter);
    placeholderLayout->addStretch();
    placeholderLayout->addWidget(label);
    placeholderLayout->addStretch();

    auto* pHamburgerButton = new HamburgerButton(this);
    pHamburgerButton->setFixedSize(36, 36);

    auto* pHamburgerAndSearchLayout = new QHBoxLayout;
    pHamburgerAndSearchLayout->addWidget(pHamburgerButton);
    pHamburgerAndSearchLayout->addWidget(pSearchLineEdit);

    auto* pHamburgerSearchAndChatListLayout = new QVBoxLayout;
    pHamburgerSearchAndChatListLayout->addLayout(pHamburgerAndSearchLayout);
    pHamburgerSearchAndChatListLayout->addWidget(pListView);
    pHamburgerSearchAndChatListLayout->setContentsMargins(0, 0, 0, 0);
    auto* pCombinedWidget = new QWidget;
    pCombinedWidget->setLayout(pHamburgerSearchAndChatListLayout);
    pCombinedWidget->setMinimumWidth(200);

    pSplitter->addWidget(pCombinedWidget);
    pSplitter->addWidget(placeholderWidget);
    
    pSplitter->setCollapsible(0, false);
    pSplitter->setCollapsible(1, false);
    pSplitter->setSizes({300, 700});

    pMainLayout->addWidget(pSplitter);
    pMainLayout->setContentsMargins(5, 5, 5, 5);
    pMainLayout->setAlignment(Qt::AlignHCenter);
    pMainLayout->setSpacing(5);

    setMouseTracking(true);
}
