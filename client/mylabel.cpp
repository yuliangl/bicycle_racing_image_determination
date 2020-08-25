#include <QPainter>
#include <QDebug>
#include <regex>
#include "mylabel.h"

extern QByteArray readData;
//int position[32] = {0, 301, 126, 387,
//                    1235, 299, 1413, 387,
//                    1090, 459, 1261, 531,
//                    758, 393, 935, 467,
//                    952, 373, 1127, 457,
//                    912, 424, 1079, 501,
//                    1178, 365, 1354, 437,
//                    1066, 330, 1240, 417};
//double predict[72] = {2.4286945787821423e-08, 0.00043630460277199745, 3.096556247328408e-05, 2.9688592348975362e-06, 2.0910714937372177e-08, 6.054940403232845e-12, 2.6512188000538117e-08, 0.0007437102030962706, 0.9987860321998596,
//                      0.0008503447170369327, 3.963769268011674e-05, 0.8847669363021851, 0.00034068553941324353, 0.0025727995671331882, 7.793524900989723e-07, 0.07150353491306305, 0.03988709673285484, 3.8224658055696636e-05,
//                      0.9995197057723999, 5.5553805999863926e-09, 2.019516109896813e-08, 1.1694172741272268e-08, 2.174502151319757e-05, 0.0004585629503708333, 1.115034366921952e-11, 8.332151293791515e-14, 7.417804214702442e-16,
//                      8.712292037671432e-05, 6.51948255381285e-07, 1.592630205493606e-08, 3.336684358146158e-06, 6.049590979273489e-07, 0.9999082088470459, 4.851836909124628e-14, 1.5080182840177458e-16, 7.711434935661943e-17,
//                      3.919083013670388e-08, 5.4747744115957175e-08, 0.01380077376961708, 8.968334554992907e-07, 3.4762354061967926e-07, 1.4876428810605552e-13, 2.1068764510800975e-08, 0.9816593527793884, 0.004538492765277624,
//                      0.022230980917811394, 6.31536920536746e-08, 3.460727882043102e-08, 1.8764562126349915e-10, 0.9768903255462646, 0.0007587895961478353, 0.00011986243043793365, 9.90021328806101e-11, 4.426707210427455e-13,
//                      0.016225092113018036, 0.9826184511184692, 5.0802995247067884e-05, 0.0004371815884951502, 6.268668221309781e-05, 2.3670793325436534e-06, 7.84218912031065e-09, 1.7615408864912752e-07, 0.0006031233351677656,
//                      1.0597911170862062e-07, 1.5330394939616632e-11, 3.508697773213498e-05, 5.11870548117882e-13, 0.0006887024501338601, 5.041259076854487e-10, 0.9992758631706238, 2.1068663613732497e-07, 1.7305090466070844e-13};

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{
//    for(int i=0; i<8; i++){
//        for(int j=0; j<4; j++){
//            pos[i][j] = position[i*4+(j+1)];
//        }
//    }
//    for(int i=0; i<8; i++){
//        for(int j=0; j<9; j++){
//            pre[i][j] = predict[i*9+(j+1)];
//        }
//    }
}
void myLabel::paintEvent(QPaintEvent *event){
    QLabel::paintEvent(event);

//    QPoint startPoint(0,0);
//    QPoint endPoint(0,0);
    QColor lineColor(Qt::red);
//    int lineSize = 2;


    QPainter painter(this);
    QPen pen;
    pen.setColor(lineColor);
//    pen.setWidth(lineSize);
    painter.setPen(pen);
    getPositionPredict();
//    painter.drawRect(QRect(startPoint.x(), startPoint.y(),
//                           endPoint.x()-startPoint.x(), endPoint.y()-startPoint.y()));
    painter.drawRect(QRectF(pos[0][0], pos[0][1], pos[0][2], pos[0][3]));
    painter.drawRect(QRectF(pos[1][0], pos[1][1], pos[1][2], pos[1][3]));
    painter.drawRect(QRectF(pos[2][0], pos[2][1], pos[2][2], pos[3][3]));
    painter.drawRect(QRectF(pos[3][0], pos[3][1], pos[3][2], pos[3][3]));
    painter.drawRect(QRectF(pos[4][0], pos[4][1], pos[4][2], pos[4][3]));
    painter.drawRect(QRectF(pos[5][0], pos[5][1], pos[5][2], pos[5][3]));
    painter.drawRect(QRectF(pos[6][0], pos[6][1], pos[6][2], pos[6][3]));
    painter.drawRect(QRectF(pos[7][0], pos[7][1], pos[7][2], pos[7][3]));

}
void myLabel::getPositionPredict(){
    QString data(readData);
    data.remove(QChar('<'), Qt::CaseSensitive);
    data.remove(QChar('>'), Qt::CaseSensitive);
    data.remove(QChar('['), Qt::CaseSensitive);
    data.remove(QChar(']'), Qt::CaseSensitive);
    data.remove(QChar(' '), Qt::CaseSensitive);
    data = std::string(data);
    qDebug()<< "data: "<< data;
    std::string dataStr = std::string(data);
    std::regex reg(",");
    std::sregex_token_iterator pos(mail.begin(), mail.end(), reg, -1);
    decltype(pos) end;
    for (; pos != end; ++pos)
    {
        std::cout << pos->str() << std::endl;
    }

}
