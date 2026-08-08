#include "html/HTMLParser.hpp"

std::vector<QString> SELF_CLOSING_TAGS = {
    "area", "base", "br", "col", "embed", "hr", "img", "input",
    "link", "meta", "param", "source", "track", "wbr",
};

std::vector<QString> HEAD_TAGS = {
    "base", "basefont", "bgsound", "noscript",
    "link", "meta", "title", "style", "script",
};

std::pair<QString, QHash<QString, QString>> get_attributes(const QString &text) {
    QStringList parts = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    QString tag = parts[0].toLower();
    QHash<QString, QString> attributes;
    for (int i = 1; i < parts.size(); i++) {
        QString attrpair = parts[i];
        int pos = attrpair.indexOf('=');

        if (pos != -1) {
            QString key = attrpair.left(pos).toLower();
            QString value = attrpair.mid(pos + 1);

            if (value.length() > 2 &&
                (value[0] == '\'' || value[0] == '"')) {
                    value = value.mid(1, value.length() - 2);
                }

            attributes[key] = value;
        }
        else attributes[attrpair.toLower()] = "";
    }
    return {tag, attributes};
}

void HTMLParser::implicit_tags(QString tag) {
    while (true) {
        std::vector<QString> open_tags;
        for (auto& node : unfinished)
            open_tags.push_back(node->value);
        if (open_tags.empty() && tag != "html")
            add_tag("html");
        else if (open_tags == std::vector<QString>{"html"} 
            && !QStringList{"head", "body", "/html"}.contains(tag)) {
                if (contains(HEAD_TAGS, tag)) {
                    add_tag("head");
                } else {
                    add_tag("body");
                }
        }
        else if (open_tags == std::vector<QString>{"html", "head"}
            && tag != "/head" && !contains(HEAD_TAGS, tag)) {
                add_tag("/head");
            }
        else break;
    }
}

void HTMLParser::add_text(const QString& text) {
    if (text.trimmed().isEmpty()) return;
    implicit_tags("");
    Token* parent = unfinished.back().get();
    auto node = std::unique_ptr<Token>(new Text(text, parent));
    parent->children.push_back(std::move(node));
}

void HTMLParser::add_tag(QString tag) {
    QHash<QString, QString> attributes;
    qDebug() << tag;
    std::tie(tag, attributes) = get_attributes(tag);
    if (tag.startsWith("!")) return;
    implicit_tags(tag);
    if (tag.startsWith('/'))  {
        if (unfinished.size() == 1) return;
        auto node = std::move(unfinished.back());
        unfinished.pop_back();
        Token* parent = unfinished.back().get();
        parent->children.push_back(std::move(node));
    } else if (contains(SELF_CLOSING_TAGS, tag)) {
        Token* parent = unfinished.back().get();
        auto node = std::unique_ptr<Token>(new Element(tag, attributes, parent));
        parent->children.push_back(std::move(node));
    } 
    else {
        Token* parent = (unfinished.empty() ? nullptr : unfinished.back().get());
        auto node = std::unique_ptr<Token>(new Element(tag, attributes, parent));
        unfinished.push_back(std::move(node));
    }
}

std::unique_ptr<Token> HTMLParser::finish() {
    if (unfinished.empty()) implicit_tags("");
    while (unfinished.size() > 1) {
        auto node = std::move(unfinished.back());
        unfinished.pop_back();
        Token* parent = unfinished.back().get();
        parent->children.push_back(std::move(node));
    }
    auto node = std::move(unfinished.back());
    unfinished.pop_back();
    return node;
}

std::unique_ptr<Token> HTMLParser::parse() {
    QString text = "";
    bool in_tag = false;
    for (QChar c : body) {
        if (c == '<') {
            in_tag = true;
            if (!text.isEmpty()) add_text(text);
            text = "";
        } else if (c == '>') {
            in_tag = false;
            add_tag(text);
            text = "";
        } else text += c;
    }
    if (!in_tag && !text.isEmpty())
        add_text(text);
    return std::move(finish());
}

void HTMLParser::print_tree(std::unique_ptr<Token> &node, int indent) {
    qDebug().noquote() << QString(indent, ' ') << *node;
    for (auto &child : node->children)
        print_tree(child, indent + 2);
}