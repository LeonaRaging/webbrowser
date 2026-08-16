#include "browser/Chrome.hpp"

void Chrome::new_tab(std::string url) {
    Tab* new_tab = new Tab(tabs);
    new_tab->load(url);
    connect(new_tab, &Tab::urlChanged, this, &Chrome::url_change);

    tabs->addTab(new_tab, "Tab " + QString::number(tabs->count()));
    tabs->setCurrentWidget(new_tab);
}

void Chrome::tab_change(int index) {
    Tab* tab = dynamic_cast<Tab*>(tabs->widget(index));

    url_bar->setText(QString::fromStdString(tab->url));
}

void Chrome::url_change(const QString& url)
{
    url_bar->setText(url);
}

void Chrome::go_back() {
    Tab* tab = dynamic_cast<Tab*>(tabs->currentWidget());

    tab->go_back();
}

void Chrome::navigate() {
    QString text = url_bar->text();

    Tab* tab = dynamic_cast<Tab*>(tabs->currentWidget());

    tab->load(text.toStdString());
}

Chrome::Chrome(QWidget* parent): QWidget(parent) {
    tabs = new QTabWidget(this);
    tabs->setFixedSize(WIDTH, HEIGHT);

    back_button = new QPushButton("<", this);
    new_tab_button = new QPushButton("+", this);
    url_bar = new QLineEdit(this);

    QHBoxLayout* navigation = new QHBoxLayout;
    navigation->addWidget(back_button);
    navigation->addWidget(new_tab_button);
    navigation->addWidget(url_bar);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addLayout(navigation);
    mainLayout->addWidget(tabs);

    connect(new_tab_button, &QPushButton::clicked, this, [this]() {
            new_tab("https://example.org");
        }
    );

    connect(tabs, &QTabWidget::currentChanged, this, &Chrome::tab_change);

    connect(back_button, &QPushButton::clicked, this, &Chrome::go_back);

    connect(url_bar, &QLineEdit::returnPressed, this, &Chrome::navigate);

    setLayout(mainLayout);
}