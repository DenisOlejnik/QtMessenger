#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scrollLayout = new QVBoxLayout();
    ui->scrollAreaWidgetContents->setLayout(m_scrollLayout);
    m_scrollLayout->addStretch();

    connect(ui->actionNetworkManage, &QAction::triggered, this, &MainWindow::onNetManagerOpenRequested);
    connect(ui->btnSend, &QToolButton::clicked, this, &MainWindow::onBtnSendClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNetManagerOpenRequested()
{
    m_netManagerDialog = new NetManagerDialog();

    if (m_netManagerDialog->exec() != QDialog::Accepted) {
        return;
    }

    if (m_netManagerDialog->isServer()) {
        m_server = new Server(this);
        if (m_server->startServer(m_netManagerDialog->port())) {
            connect(m_server, &Server::messageReceived, this, &MainWindow::updateChatMessages);
            connect(m_server, &Server::messageSent, this, &MainWindow::updateChatMessages);
            connect(m_server, &Server::serviceMessageRequested, this, &MainWindow::updateChatMessages);

            QString message = QString("Server started at port %1").arg(m_netManagerDialog->port());
            setWindowTitle(QString("Server | Port: %1").arg(m_netManagerDialog->port()));
            MessageInfo startMessage(true, message, this);
            updateChatMessages(startMessage);
        }
        else {
            qDebug() << "(onNetManagerOpenRequested) Failed to start server.";
        }
    }
    else {
        m_client = new Client(m_netManagerDialog->username(), this);
        connect(m_client, &Client::messageReceived, this, &MainWindow::updateChatMessages);
        connect(m_client, &Client::messageSent, this, &MainWindow::updateChatMessages);
        m_client->connectToServer(m_netManagerDialog->host(), m_netManagerDialog->port());

        setWindowTitle(QString("Client | %1").arg(m_client->getUsername()));

        MessageInfo startMessage(true, QString("%1 joined").arg(m_client->getUsername()));
        ui->usersListWidget->addItem(m_client->getUsername());
        updateChatMessages(startMessage);
    }
}

void MainWindow::onBtnSendClicked()
{
    QString text = ui->messageTextEdit->toPlainText().trimmed();

    if (text.isEmpty()) {
        return;
    }

    if (m_server) {
        MessageInfo message(m_netManagerDialog->username(), text);
        m_server->sendMessage(message);

        ui->messageTextEdit->clear();
    }

    if (m_client) {
        m_client->sendMessage(text);

        ui->messageTextEdit->clear();
    }

}

void MainWindow::updateChatMessages(const MessageInfo &newMessage)
{
    QLayoutItem *stretch = m_scrollLayout->takeAt(m_scrollLayout->count() - 1);

    if (newMessage.isServiceMsg()) {
        QLabel *serviceLabel = new QLabel(newMessage.text());
        serviceLabel->setAlignment(Qt::AlignCenter);
        m_scrollLayout->addWidget(serviceLabel);
        m_scrollLayout->addItem(stretch);
        return;
    }

    QString username = m_netManagerDialog->username();
    bool isOwner = newMessage.sender() == username;

    Message *messageWidget = new Message(newMessage, isOwner, this);

    m_scrollLayout->addWidget(messageWidget);

    m_scrollLayout->addItem(stretch);


    qDebug() << QString("[new] %1 | %2 | %3").arg(newMessage.dateTime().toString("hh:mm:ss")).arg(newMessage.text()).arg(newMessage.sender());
}

