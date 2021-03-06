#ifndef QQTSHOWDOWEFFECTWIDGET_H
#define QQTSHOWDOWEFFECTWIDGET_H

/**
 * T.D.R (QQ:2657635903) 2017年10月22日17:47:18
 * MOD
**/

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include "qqt-local.h"

/**
 * @brief The QQtShadowEffectWidget class 阴影widget基类
 */
class QQTSHARED_EXPORT QQtShadowEffectWidget : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief QQtShadowEffectWidget 构造函数
     * @param parent
     */
    explicit QQtShadowEffectWidget(QWidget* parent = 0);

protected:
    /**
     * @brief paintEvent 绘制事件处理函数
     * @param e
     */
    void paintEvent(QPaintEvent* e);

private:
    /**
     * @brief drawShadowPlanA 阴影绘制方案A
     */
    void drawShadowPlanA();

    /**
     * @brief drawShadowPlanB 阴影绘制方案B
     */
    void drawShadowPlanB();

private:
};

#endif // QQTSHOWDOWEFFECTWIDGET_H
