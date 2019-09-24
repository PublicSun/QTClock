#include <QWidget>
#include <QTimerEvent>

//每一次Qt刷新，指针改变的的度数
#define Needle_Step 6
class ClockWidget : public QWidget
{

public:
    explicit ClockWidget(QWidget *parent = nullptr);

public slots:
    void showSS(void);
private:
    int StepNum=0;
    int StepMM=0;
    int StepHH=0;
private:
    void DrawMM(QPainter *painter);
    void DrawHH(QPainter *painter);
protected:
    void paintEvent(QPaintEvent *);
};


