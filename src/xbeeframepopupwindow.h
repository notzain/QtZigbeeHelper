#ifndef XBEEFRAMEPOPUPWINDOW_H
#define XBEEFRAMEPOPUPWINDOW_H

#include <QDialog>
#include <QFormLayout>
#include <QObject>
#include <QTextEdit>
#include <QWidget>

namespace Ui {
class XbeeFramePopupWindow;
}

class XbeeFrame;

class XbeeFramePopupWindow : public QDialog {
    Q_OBJECT
public:
    explicit XbeeFramePopupWindow( XbeeFrame* frame, QWidget* parent = nullptr );

private:
    Ui::XbeeFramePopupWindow* ui;

    QFormLayout* mFrameForm;
    QTextEdit* mHexField;
    QTextEdit* mAsciiField;

    void initForm( XbeeFrame* frame );
    void initFormAsRx( XbeeFrame* frame );
};

#endif // XBEEFRAMEPOPUPWINDOW_H
