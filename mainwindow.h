#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QList>
#include <QVariant>
#include <QMetaProperty>
#include <QMessageBox>
#include "reviewdata.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addReview();
    void displayReviews();
    void displayReviewsInConsole();

private:
    QLabel *instructionLabel;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QLabel *dateLabel;
    QDateEdit *dateEdit;
    QCheckBox *recommendCheckBox;
    QPushButton *addButton;
    QPushButton *displayButton;
    QPushButton *consoleButton;
    QLabel *outputLabel;
    QVBoxLayout *mainLayout;
    QWidget *centralWidget;
    QList<QVariant> reviewList;

    void createAndSaveReviewData(const QString &name, const QDate &date, bool recommend);
    QVariant getReviewData(ReviewData *rd);
    void readGUI();
};

#endif // MAINWINDOW_H
