#include <memory>
#include <QString>
#include "Text.hpp"
#include "Element.hpp"

class HTMLParser {
    public:
        QString body;
        std::vector<std::unique_ptr<Token>> unfinished;
        void implicit_tags(QString);
        void add_text(const QString& text);
        void add_tag(QString tag);
        std::unique_ptr<Token> finish();
        std::unique_ptr<Token> parse();
        void print_tree(std::unique_ptr<Token>& node, int indent = 0);
        HTMLParser(QString body): body(body) {}
};