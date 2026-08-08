#include "css/CSSParser.hpp"

void CSSParser::whitespace() {
    while (i < s.size() && s[i].isSpace())
        i++;
}

void CSSParser::literal(QChar ch) {
    if (!(i < s.size() && s[i] == ch))
        throw std::runtime_error("Parsing error");
    i++;
}

QString CSSParser::word() {
    int start = i;
    while (i < s.size()) {
        QChar ch = s[i];
        if (ch.isLetterOrNumber() || 
            ch == '#' ||
            ch == '-' ||
            ch == '.' ||
            ch == '%') {
                i++;
            }
        else break;
    }
    if (i <= start) {
        throw std::runtime_error("Parsing error");
    }
    return s.mid(start, i - start);
}

std::pair<QString, QString> CSSParser::pair() {
    QString prop = word();
    whitespace();
    literal(':');
    whitespace();
    QString val = word();
    return {prop.toLower(), val};
}

QChar CSSParser::ignore_until(std::vector<QChar> chars) {
    while (i < s.size()) {
        if (contains(chars, s[i]))
            return s[i];
        else i++;
    }
    return QChar();
}

#include <QDebug>

QHash<QString, QString> CSSParser::body() {
    QHash<QString, QString> pairs;
    while (i < s.size()) {
        try {
            QString prop;
            QString val;
            std::tie(prop, val) = pair();
            pairs[prop] = val;
            whitespace();
            literal(';');
            whitespace();
        }
        catch (const std::exception& e) {
            QChar why = ignore_until({';', '}'});
            if (why == ';') {
                literal(';');
                whitespace();
            } else break;
        }
    }
    return pairs;
}

std::unique_ptr<Selector> CSSParser::selector() {
    std::unique_ptr<Selector> out(new TagSelector(word().toLower()));
    whitespace();
    while (i < s.size() && s[i] != '{') {
        QString tag = word();
        std::unique_ptr<Selector> descendant(new TagSelector(tag.toLower()));
        out = std::unique_ptr<Selector>(new DescendantSelector(std::move(out), std::move(descendant)));
        whitespace();
    }
    return std::move(out);
}

std::vector<std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>> CSSParser::parse() {
    std::vector<std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>> rules;
    while (i < s.size()) {
        try {
            whitespace();
            std::unique_ptr<Selector> s = std::move(selector());
            literal('{');
            whitespace();
            QHash<QString, QString> b = body();
            literal('}');
            rules.emplace_back(std::move(s), b);
        } catch (const std::exception& e) {
            QChar why = ignore_until({'}'});
            if (why == '}') {
                literal('}');
                whitespace();
            } else break;
        }
    }
    return rules;
}

CSSParser::CSSParser(QString s): s(s), i(0) {}