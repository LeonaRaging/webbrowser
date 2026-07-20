#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>

const int WIDTH = 800;
const int HEIGHT = 600;

struct Canvas : public QWidget {
    public:
        void layout(const std::string &text);
        Canvas(QWidget *parent = nullptr);
    protected:
        void paintEvent(QPaintEvent *) override;
        void keyPressEvent(QKeyEvent *event) override;
        void wheelEvent(QWheelEvent* event) override;
        void scrollpage(int step);
    private:
        int scroll = 0;
        std::vector<std::tuple<int, int, QChar>> display_list;
};
