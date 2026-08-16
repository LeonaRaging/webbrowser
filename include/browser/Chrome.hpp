#include <QTabWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "browser/Tab.hpp"

struct Chrome : public QWidget {
    QTabWidget* tabs;
    QPushButton* new_tab_button;
    QPushButton* back_button;
    QLineEdit* url_bar;

    void new_tab(std::string);
    void tab_change(int);
    void url_change(const QString&);
    void go_back();
    void navigate();

    Chrome(QWidget* parent = nullptr);
};