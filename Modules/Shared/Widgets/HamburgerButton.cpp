#include "HamburgerButton.h"

#include <QGraphicsDropShadowEffect>
#include <QMenu>

HamburgerButton::HamburgerButton(QWidget* parent) : QPushButton(parent)
{
    setStyleSheet(R"(
        QPushButton {
            border: none;
            background: transparent;
            font-size: 20px;
        }
        QPushButton:hover {
            background: #3d3d3d;
            border-radius: 4px;
        }
    )");
    setIcon(QIcon(":/icons/hamburger-1.png"));

    QMenu* menu = new QMenu(this);
    menu->setStyleSheet(R"(
        QMenu {
            background-color: #3d3d3d;
            border: 1px solid #4a4a4a;
            border-radius: 8px;
            padding: 6px 0;
            margin: 4px 0;
            color: #e0e0e0;
            font-family: "Segoe UI", sans-serif;
        }
        QMenu::item {
            font-weight: bold;
            padding: 8px 24px 8px 16px;
            margin: 0 6px;
            border-radius: 6px;
            background-color: transparent;
            min-width: 160px;
        }
        QMenu::item:selected {
            background-color: #505050;
        }
        QMenu::item:disabled {
            color: #707579;
        }
        QMenu::separator {
            height: 1px;
            background: #4a4a4a;
            margin: 6px 8px;
        }
        QMenu::icon {
            padding-left: 8px;
        }
    )");

    auto* shadow = new QGraphicsDropShadowEffect(menu);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 30));
    shadow->setOffset(0, 1);

    auto addAction = [menu](const QString& iconName, const QString& text) {
        QAction* action = new QAction(QIcon(iconName), text);
        menu->addAction(action);
        return action;
    };

    addAction(":/icons/user.png", "My Profile");
    addAction(":/icons/group.png", "New Group");
    addAction(":/icons/channel.png", "New Channel");
    menu->addSeparator();
    addAction(":/icons/contacts.png", "Contacts");
    addAction(":/icons/calls.png", "Calls");
    addAction(":/icons/bookmark.png", "Saved Messages");
    menu->addSeparator();
    addAction(":/icons/settings.png", "Settings");
    addAction(":/icons/moon.png", "Night Mode");
    menu->addSeparator();

    connect(this, &QPushButton::clicked, [=]() { menu->popup(mapToGlobal(QPoint(0, height()))); });
}
