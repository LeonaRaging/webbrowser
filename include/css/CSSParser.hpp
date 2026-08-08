#include <QString>
#include <QHash>
#include "util/Util.hpp"
#include "css/TagSelector.hpp"
#include "css/DescendantSelector.hpp"

struct CSSParser {
    QString s;
    int i;

    void whitespace();
    void literal(QChar ch);
    QString word();
    std::pair<QString, QString> pair();
    QChar ignore_until(std::vector<QChar> chars);
    QHash<QString, QString> body();
    std::unique_ptr<Selector> selector();
    std::vector<std::pair<std::unique_ptr<Selector>, QHash<QString, QString>>> parse();

    CSSParser(QString s);
};