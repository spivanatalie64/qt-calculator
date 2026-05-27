#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator() override = default;

private slots:
    void onDigitPressed();
    void onOpPressed();
    void onEquals();
    void onClear();

private:
    QLineEdit   *m_display;
    QPushButton *createButton(const QString &text, const char *slot);

    double  m_currentValue = 0;
    QString m_pendingOp;
    bool    m_clearOnInput = true;
};

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QGridLayout(this);
    layout->setSpacing(4);

    m_display = new QLineEdit("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);
    m_display->setMinimumHeight(48);
    m_display->setStyleSheet("font-size: 24px; padding: 4px;");
    layout->addWidget(m_display, 0, 0, 1, 5);

    const QStringList buttons = {
        "7", "8", "9", "/", "C",
        "4", "5", "6", "*", "",
        "1", "2", "3", "-", "",
        "0", ".", "=", "+", ""
    };

    for (int i = 0; i < buttons.size(); ++i) {
        const QString &text = buttons[i];
        if (text.isEmpty()) continue;

        int row = 1 + i / 5;
        int col = i % 5;
        int colspan = (text == "0") ? 1 : 1;

        const char *slot = nullptr;
        if (text == "=")
            slot = SLOT(onEquals());
        else if (text == "C")
            slot = SLOT(onClear());
        else if (text == "+" || text == "-" || text == "*" || text == "/")
            slot = SLOT(onOpPressed());
        else
            slot = SLOT(onDigitPressed());

        auto *btn = createButton(text, slot);
        layout->addWidget(btn, row, col, 1, colspan);
    }

    setWindowTitle("Calculator");
    resize(280, 360);
}

QPushButton *Calculator::createButton(const QString &text, const char *slot)
{
    auto *btn = new QPushButton(text);
    btn->setMinimumSize(56, 48);
    btn->setStyleSheet(
        "QPushButton { font-size: 18px; border: 1px solid #888; border-radius: 4px; "
        "background: #f0f0f0; } "
        "QPushButton:pressed { background: #d0d0d0; }");
    connect(btn, SIGNAL(clicked()), this, slot);
    return btn;
}

void Calculator::onDigitPressed()
{
    auto *btn = qobject_cast<QPushButton *>(sender());
    const QString digit = btn->text();

    if (m_clearOnInput) {
        m_display->clear();
        m_clearOnInput = false;
    }

    if (digit == ".") {
        if (m_display->text().contains('.'))
            return;
        if (m_display->text().isEmpty())
            m_display->setText("0");
    }

    m_display->setText(m_display->text() + digit);
}

void Calculator::onOpPressed()
{
    auto *btn = qobject_cast<QPushButton *>(sender());
    const QString op = btn->text();

    double value = m_display->text().toDouble();

    if (!m_pendingOp.isEmpty()) {
        if (m_pendingOp == "+") m_currentValue += value;
        else if (m_pendingOp == "-") m_currentValue -= value;
        else if (m_pendingOp == "*") m_currentValue *= value;
        else if (m_pendingOp == "/") {
            if (value == 0.0) {
                m_display->setText("Error");
                m_currentValue = 0;
                m_pendingOp.clear();
                m_clearOnInput = true;
                return;
            }
            m_currentValue /= value;
        }
    } else {
        m_currentValue = value;
    }

    m_display->setText(QString::number(m_currentValue, 'g', 15));
    m_pendingOp = op;
    m_clearOnInput = true;
}

void Calculator::onEquals()
{
    double value = m_display->text().toDouble();

    if (!m_pendingOp.isEmpty()) {
        if (m_pendingOp == "+") m_currentValue += value;
        else if (m_pendingOp == "-") m_currentValue -= value;
        else if (m_pendingOp == "*") m_currentValue *= value;
        else if (m_pendingOp == "/") {
            if (value == 0.0) {
                m_display->setText("Error");
                m_currentValue = 0;
                m_pendingOp.clear();
                m_clearOnInput = true;
                return;
            }
            m_currentValue /= value;
        }
        m_pendingOp.clear();
    } else {
        m_currentValue = value;
    }

    m_display->setText(QString::number(m_currentValue, 'g', 15));
    m_clearOnInput = true;
}

void Calculator::onClear()
{
    m_currentValue = 0;
    m_pendingOp.clear();
    m_display->setText("0");
    m_clearOnInput = true;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calculator calc;
    calc.show();
    return app.exec();
}

#include "main.moc"
