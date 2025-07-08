#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), reviewList() {
    instructionLabel = new QLabel("Fill in the data and click Add", this);
    nameLabel = new QLabel("Name", this);
    nameEdit = new QLineEdit(this);
    dateLabel = new QLabel("Date", this);
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    recommendCheckBox = new QCheckBox("Recommend", this);
    addButton = new QPushButton("Add", this);
    displayButton = new QPushButton("Display", this);
    consoleButton = new QPushButton("Display in Console", this);
    outputLabel = new QLabel(this);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(instructionLabel);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameEdit);
    mainLayout->addWidget(dateLabel);
    mainLayout->addWidget(dateEdit);
    mainLayout->addWidget(recommendCheckBox);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(displayButton);
    mainLayout->addWidget(consoleButton);
    mainLayout->addWidget(outputLabel);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addReview);
    connect(displayButton, &QPushButton::clicked, this, &MainWindow::displayReviews);
    connect(consoleButton, &QPushButton::clicked, this, &MainWindow::displayReviewsInConsole);

    nameEdit->setFocus();
}

MainWindow::~MainWindow() {}

void MainWindow::createAndSaveReviewData(const QString &name, const QDate &date, bool recommend) {
    ReviewData *rd = new ReviewData();
    rd->setName(name);
    rd->setDate(date);
    rd->setRecommend(recommend);

    QVariant reviewDataState = getReviewData(rd);
    reviewList.append(reviewDataState);

    delete rd;
}

QVariant MainWindow::getReviewData(ReviewData *rd) {
    QVariantMap dataMap;
    const QMetaObject *metaObj = rd->metaObject();

    for (int i = 0; i < metaObj->propertyCount(); ++i) {
        QMetaProperty property = metaObj->property(i);
        const char *propName = property.name();
        QVariant propValue = rd->property(propName);
        dataMap[propName] = propValue;
    }

    return dataMap;
}

void MainWindow::readGUI() {
    QString name = nameEdit->text().trimmed();
    QDate date = dateEdit->date();
    bool recommend = recommendCheckBox->isChecked();

    if (!name.isEmpty()) {
        createAndSaveReviewData(name, date, recommend);
        nameEdit->clear();
        recommendCheckBox->setChecked(false);
        dateEdit->setDate(QDate::currentDate());
        nameEdit->setFocus();
    } else {
        QMessageBox::warning(this, "Input Error", "Name cannot be empty.");
    }
}

void MainWindow::addReview() {
    readGUI();
}

void MainWindow::displayReviews() {
    if (reviewList.isEmpty()) {
        outputLabel->setText("No data entered.");
    } else {
        QString output;
        for (const QVariant &reviewData : reviewList) {
            QVariantMap dataMap = reviewData.toMap();
            QString name = dataMap["name"].toString();
            QDate date = dataMap["date"].toDate();
            bool recommend = dataMap["recommend"].toBool();

            output += QString("Name: %1\nDate: %2\nRecommend: %3\n\n")
                            .arg(name)
                            .arg(date.toString())
                            .arg(recommend ? "Yes" : "No");
        }
        outputLabel->setText(output);
    }
}

void MainWindow::displayReviewsInConsole() {
    if (reviewList.isEmpty()) {
        qDebug() << "No data entered.";
    } else {
        for (const QVariant &reviewData : reviewList) {
            QVariantMap dataMap = reviewData.toMap();
            QString name = dataMap["name"].toString();
            QDate date = dataMap["date"].toDate();
            bool recommend = dataMap["recommend"].toBool();

            qDebug() << "Name:" << name;
            qDebug() << "Date:" << date.toString();
            qDebug() << "Recommend:" << (recommend ? "Yes" : "No");
            qDebug() << "-------------------";
        }
    }
}
