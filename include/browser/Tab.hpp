#include <QFile>
#include <QWidget>
#include "layout/DocumentLayout.hpp"
#include "network/URL.hpp"
#include "html/Text.hpp"
#include "html/Element.hpp"
#include "html/HTMLParser.hpp"
#include "css/Style.hpp"

struct Canvas;

struct Tab : public QWidget {
    Q_OBJECT

    public:
        URL url;
        std::unique_ptr<Token> node;
        std::unique_ptr<DocumentLayout> document;
        std::vector<URL> history;
        Canvas* canvas;

        void load(URL);
        void go_back();

        Tab(QWidget* parent = nullptr);
    signals:
        void urlChanged(const QString& url);
    
};