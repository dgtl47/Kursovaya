#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"
#include "patients_printout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(socketReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(socketDisconnect()));

    ui->statusbar->addPermanentWidget(ui->connectButton);

    //Disable MenuBar and other..
    MainWindow::ui->actionLogin->setEnabled(false);
    MainWindow::ui->actionAdd_Patient->setEnabled(false);
    MainWindow::ui->actionEdit_Patient->setEnabled(false);
    MainWindow::ui->actionDelete_Patient->setEnabled(false);
    MainWindow::ui->actionPatient_Info->setEnabled(false);
    MainWindow::ui->actionLogout->setEnabled(false);
    MainWindow::ui->actionChange_password->setEnabled(false);
    MainWindow::ui->actionQuit->setEnabled(false);
    MainWindow::ui->actionPrint_out->setEnabled(false);
    MainWindow::ui->scrollArea->setEnabled(false);
    MainWindow::ui->pushButton_2->setEnabled(false);

    disableButtons();

    toolbar.setStyleSheet("QToolBar{spacing:3px;}");
    toolbar.movableChanged(false);  
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::socketDisconnect()
{
    socket->deleteLater();
}

void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::socketReady()
{
    if (socket->waitForConnected(1000))
    {
        socket->waitForReadyRead(1000);
        data = socket->readAll();

        QString list = data.mid(7,12);
        QString patientinfo = data.mid(2,11);

        int buttonCounter = 3;
        int patientCounter = 0;

        document = QJsonDocument::fromJson(data,&documentError);

        if ((documentError.errorString()=="no error occurred"))
        {
            if ((document.object().value("type").toString() == "connect") && (document.object().value("value").toString() == "correct"))
            {
                ui->statusbar->showMessage("Connected");
            }
            else if ((document.object().value("type").toString() == "user") && (document.object().value("value").toString() == "success"))
            {
                ui->statusbar->showMessage("Connected");
                QMessageBox message;
                message.setWindowTitle("Success");
                message.setText("Your're logged in!");
                message.exec();

                QPixmap pixmap("C:\\Users\\79788\\Documents\\EndocrinHelper\\icon\\userlogin.png");
                ui->label->setPixmap(pixmap);

                QPixmap pixmap1("C:\\Users\\79788\\Documents\\EndocrinHelper\\icon\\userlogin.png");
                ui->label_4->setPixmap(pixmap1);
            }
            else if ((document.object().value("type").toString() == "user") && (document.object().value("value").toString() == "failed"))
            {
                ui->statusbar->showMessage("Connected");
                QMessageBox message;
                message.setWindowTitle("Warning");
                message.setText("Wrong password!");
                message.exec();
            }
            else if (document.object().value("type").toString() == "save")
            {
                QJsonObject object = document.object();

                QString complaints;
                if (object.value("complaint1").toString() == "ON") complaints += "слабость, ";
                if (object.value("complaint2").toString() == "ON") complaints += "утомляемость, ";
                if (object.value("complaint3").toString() == "ON") complaints += "снижение работоспособности, ";
                if (object.value("complaint4").toString() == "ON") complaints += "сухость кожи, ";
                if (object.value("complaint5").toString() == "ON") complaints += "потливость, ";
                if (object.value("complaint6").toString() == "ON") complaints += "сердцебиение, ";
                if (object.value("complaint7").toString() == "ON") complaints += "понос, ";
                if (object.value("complaint8").toString() == "ON") complaints += "чувство кома в горле, ";
                if (object.value("complaint9").toString() == "ON") complaints += "поперхивание пищей, ";
                if (object.value("complaint10").toString() == "ON") complaints += "дискомфорт в обл. шеи, ";
                if (object.value("complaint11").toString() == "ON") complaints += "раздражительность, ";
                if (object.value("complaint12").toString() == "ON") complaints += "плаксивость, ";
                if (object.value("complaint13").toString() == "ON") complaints += "снижение памяти, ";
                if (object.value("complaint14").toString() == "ON") complaints += "сонливость, ";
                if (object.value("complaint15").toString() == "ON") complaints += "бессоницу, ";
                if (object.value("complaint16").toString() == "ON") complaints += "дрожь в теле, ";
                if (object.value("complaint17").toString() == "ON") complaints += "дискомфорт в глаз. яблоках, ";
                if (object.value("complaint18").toString() == "ON") complaints += "склонность к запорам, ";
                if (object.value("complaint19").toString() == "ON") complaints += "чувство перебоев в сердце.";

                QString conditions;
                if (object.value("condition1").toString() == "ON") conditions += "удовлетворительное, ";
                if (object.value("condition2").toString() == "ON") conditions += "средней тяжести.";

                QString skins;
                if (object.value("skin1").toString() == "ON") skins += "N окраски, ";
                if (object.value("skin2").toString() == "ON") skins += "влажности, ";
                if (object.value("skin3").toString() == "ON") skins += "чистая, ";
                if (object.value("skin4").toString() == "ON") skins += "сухая, ";
                if (object.value("skin5").toString() == "ON") skins += "бледная, ";
                if (object.value("skin6").toString() == "ON") skins += "субиктеричная. ";
                skins + object.value("skins7").toString() + ".";

                QString thyroids;
                if (object.value("thyroid1").toString() == "ON") thyroids += "увеличена, ";
                if (object.value("thyroid2").toString() == "ON") thyroids += "не увеличена, ";
                if (object.value("thyroid3").toString() == "ON") thyroids += "мягкая, ";
                if (object.value("thyroid4").toString() == "ON") thyroids += "плотная, ";
                if (object.value("thyroid5").toString() == "ON") thyroids += "подвижная, ";
                if (object.value("thyroid6").toString() == "ON") thyroids += "эластичная. ";
                thyroids + object.value("thyroid7").toString() + ".";

                QString lungs;
                if (object.value("lungs1").toString() == "ON") lungs += "везикулярное, ";
                if (object.value("lungs2").toString() == "ON") lungs += "хрипов (нет), ";
                if (object.value("lungs3").toString() == "ON") lungs += "хрипы (есть). ";
                lungs + object.value("lungs4").toString() + ".";

                QString hearts;
                if (object.value("heart1").toString() == "ON") hearts += "звучные, ";
                if (object.value("heart2").toString() == "ON") hearts += "приглушены, ";
                if (object.value("heart3").toString() == "ON") hearts += "глухие. ";
                hearts + object.value("heart4").toString() + ".";

                QString stomachs;
                if (object.value("stomach1").toString() == "ON") stomachs += "мягкий, ";
                if (object.value("stomach2").toString() == "ON") stomachs += "безболезненный, ";
                if (object.value("stomach3").toString() == "ON") stomachs += "болезненный. ";
                stomachs + object.value("stomach4").toString() + ".";

                QString tremors;
                if (object.value("tremor1").toString() == "ON") tremors += "выраженный, ";
                if (object.value("tremor2").toString() == "ON") tremors += "умеренный, ";
                if (object.value("tremor3").toString() == "ON") tremors += "нет. ";

                QString summarypatientData = "\t\t\t\t\t\tОсмотр эндокринолога\n\nФамилия: " + object.value("surname").toString() + "\nИмя: " + object.value("name").toString() + "\nОтчество: " + object.value("patronymic").toString() + "\n\nЖалобы: " + complaints + "\n\nАнамнез жизни: " + object.value("anamnesis_life").toString() + "\nАнамнез болезни: " + object.value("anamnesis_disease").toString() + "\n\nОбъективно:\nОбщее состояние " + conditions + "\nКожа - " + skins + "\nЛицо: " + object.value("face").toString() + "\nЯзык: " + object.value("tongue").toString() + "\nЩитовидная железа - " + thyroids + "\nВ легких дыхание " + lungs + "\nТоны сердца " + hearts + "\nAD: " + object.value("AD").toString() + "\nЖивот " + stomachs + "\nПечень у края реб.дуги + " + object.value("liver").toString() + " см" + "\nВ позе Ромберга тремор + " + tremors + "\nГлазные симптомы " + object.value("eyes").toString() + "\nОтеки " + object.value("edema").toString() + "\nСтул N, запоры, поносы " + object.value("diarrhea").toString() + "\n\nDs:\n\nРекомендовано:\t\t\t\t\t\t\t\tТТГ, св. Т4, а/т к ТГ, ТПО\n\t\t\t\t\t\t\t\t\tРец. ТТГ\n\t\t\t\t\t\t\t\t\tФГ, о/о,\n\t\t\t\t\t\t\t\t\tОАК, сах.крови\n\t\t\t\t\t\t\t\t\tБиохим.,\n\t\t\t\t\t\t\t\t\tУЗИ щит.ж-зы ТАПБ\n\n\n\t\t\t\t\t\t\t\t\tВрач \n\t\t\t\t\t\t\t\t\tФ.И.О. \n\t\t\t\t\t\t\t\t\tподпись ";
                patients_printout pPrintout;
                pPrintout.setModal(true);
                pPrintout.setText(summarypatientData);
                pPrintout.exec();
            }
        }
        else
        {
            QMessageBox::information(this,"Info", "Error with the transfer format"+documentError.errorString());
        }

        if (list == "patientArray")
        {
            QJsonObject object = document.object();

            QJsonValue JSONArrayValue = object.value("patientArray");
            QJsonArray JSONArray = JSONArrayValue.toArray();
            QJsonObject object_JSONArray_first = JSONArray[0].toObject();
            QString emptyString = "";

            foreach (const QJsonValue & v, JSONArray)
            {
                if (((v.toObject().value("surname").toString() != emptyString)) && ((v.toObject().value("name").toString() != emptyString)) && ((v.toObject().value("patronymic").toString() != emptyString)))
                {
                    QString patientName = v.toObject().value("surname").toString() + " " + v.toObject().value("name").toString() + " " + v.toObject().value("patronymic").toString();

                    QPushButton *button = findChild<QPushButton *>("pushButton_" + QString::number(buttonCounter));
                    if (button == nullptr) continue;

                    button->setEnabled(true);
                    button->setText(patientName);
                }

                buttonCounter++;
                patientCounter++;
            }
        }
    }
}

void MainWindow::on_connectButton_clicked()
{
    socket->connectToHost("127.0.0.1",5555);
    ui->statusbar->removeWidget(ui->connectButton);

    MainWindow::ui->actionLogin->setEnabled(true);
    MainWindow::ui->actionAdd_Patient->setEnabled(true);
    MainWindow::ui->actionEdit_Patient->setEnabled(true);
    MainWindow::ui->actionDelete_Patient->setEnabled(true);
    MainWindow::ui->actionPatient_Info->setEnabled(true);
    MainWindow::ui->actionChange_password->setEnabled(true);
    MainWindow::ui->actionQuit->setEnabled(true);
}

void MainWindow::on_actionLogin_triggered()
{
    authdialog aDialog;
    aDialog.setModal(true);
    aDialog.exec();

    QString login = aDialog.login;
    QString password = aDialog.password;

    qDebug() << login << password;

    if (socket->isOpen())
    {
        QByteArray login_ = login.toUtf8();
        QByteArray password_ = password.toUtf8();
        QByteArray summary = "{\"type\":\"login\""+login_+",\"value\":\"password\""+password_+"}";
        socket->write(summary);
    }

    delay();

    if (ui->label->pixmap() !=0)
    {
        ui->label->setText("Добро пожаловать,\n"+login+"!");
        MainWindow::ui->pushButton_2->setEnabled(true);
    }

}

void MainWindow::on_actionAdd_Patient_triggered()
{
    if (ui->label_4->pixmap() != 0)
    {
        MainWindow::ui->scrollArea->setEnabled(true);
    }
    else
    {
        MainWindow::ui->scrollArea->setEnabled(false);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString surname = ui->textEdit_2->toPlainText();
    QString name = ui->textEdit_3->toPlainText();
    QString patronymic = ui->textEdit_4->toPlainText();
    QString anamnesis_life = ui->textEdit_5->toPlainText();
    QString anamnesis_disease = ui->textEdit_6->toPlainText();
    QString skin7 = ui->textEdit_7->toPlainText();
    QString face = ui->textEdit_8->toPlainText();
    QString tongue = ui->textEdit_9->toPlainText();
    QString thyroid7 = ui->textEdit_10->toPlainText();
    QString lungs4 = ui->textEdit_11->toPlainText();
    QString heart4 = ui->spinBox->text();
    QString AD = ui->textEdit_12->toPlainText();
    QString stomach4 = ui->textEdit_13->toPlainText();
    QString liver = ui->doubleSpinBox->text();
    QString eyes = ui->textEdit_14->toPlainText();
    QString edema = ui->textEdit_15->toPlainText();
    QString diarrhea = ui->textEdit_16->toPlainText();

    if (socket->isOpen())
    {
        QByteArray surname_ = surname.toLocal8Bit();
        QByteArray name_ = name.toLocal8Bit();
        QByteArray patronymic_ = patronymic.toLocal8Bit();
        QByteArray anamnesis_life_ = anamnesis_life.toLocal8Bit();
        QByteArray anamnesis_disease_ = anamnesis_disease.toLocal8Bit();
        QByteArray skin7_ = skin7.toLocal8Bit();
        QByteArray face_ = face.toLocal8Bit();
        QByteArray tongue_ = tongue.toLocal8Bit();
        QByteArray thyroid7_ = thyroid7.toLocal8Bit();
        QByteArray lungs4_ = lungs4.toLocal8Bit();
        QByteArray heart4_ = heart4.toLocal8Bit();
        QByteArray AD_ = AD.toLocal8Bit();
        QByteArray stomach4_ = stomach4.toLocal8Bit();
        QByteArray liver_ = liver.toLocal8Bit();
        QByteArray eyes_ = eyes.toLocal8Bit();
        QByteArray edema_ = edema.toLocal8Bit();
        QByteArray diarrhea_ = diarrhea.toLocal8Bit();

        QString label = ui->label->text();
        QString username = label.mid(18,5);

        QByteArray username_ = username.toUtf8();

        grabcheckboxstate();

        QByteArray summary = "{\n\t\"login\":\""+username_+"\",\n\t\"type\":\"save\",\n\t\"surname\":\""+surname_+"\",\n\t\"name\":\""+name_+"\",\n\t\"patronymic\":\""+patronymic_+"\",\n\t\"complaint1\":\""+complaint1_+"\",\n\t\"complaint2\":\""+complaint2_+"\",\n\t\"complaint3\":\""+complaint3_+"\",\n\t\"complaint4\":\""+complaint4_+"\",\n\t\"complaint5\":\""+complaint5_+"\",\n\t\"complaint6\":\""+complaint6_+"\",\n\t\"complaint7\":\""+complaint7_+"\",\n\t\"complaint8\":\""+complaint8_+"\",\n\t\"complaint9\":\""+complaint9_+"\",\n\t\"complaint10\":\""+complaint10_+"\",\n\t\"complaint11\":\""+complaint11_+"\",\n\t\"complaint12\":\""+complaint12_+"\",\n\t\"complaint13\":\""+complaint13_+"\",\n\t\"complaint14\":\""+complaint14_+"\",\n\t\"complaint15\":\""+complaint15_+"\",\n\t\"complaint16\":\""+complaint16_+"\",\n\t\"complaint17\":\""+complaint17_+"\",\n\t\"complaint18\":\""+complaint18_+"\",\n\t\"complaint19\":\""+complaint19_+"\",\n\t\"anamnesis_life\":\""+anamnesis_life_+"\",\n\t\"anamnesis_disease\":\""+anamnesis_disease_+"\",\n\t\"condition1\":\""+condition1_+"\",\n\t\"condition2\":\""+condition2_+"\",\n\t\"skin1\":\""+skin1_+"\",\n\t\"skin2\":\""+skin2_+"\",\n\t\"skin3\":\""+skin3_+"\",\n\t\"skin4\":\""+skin4_+"\",\n\t\"skin5\":\""+skin5_+"\",\n\t\"skin6\":\""+skin6_+"\",\n\t\"skin7\":\""+skin7_+"\",\n\t\"face\":\""+face_+"\",\n\t\"tongue\":\""+tongue_+"\",\n\t\"thyroid1\":\""+thyroid1_+"\",\n\t\"thyroid2\":\""+thyroid2_+"\",\n\t\"thyroid3\":\""+thyroid3_+"\",\n\t\"thyroid4\":\""+thyroid4_+"\",\n\t\"thyroid5\":\""+thyroid5_+"\",\n\t\"thyroid6\":\""+thyroid6_+"\",\n\t\"thyroid7\":\""+thyroid7_+"\",\n\t\"lungs1\":\""+lungs1_+"\",\n\t\"lungs2\":\""+lungs2_+"\",\n\t\"lungs3\":\""+lungs3_+"\",\n\t\"lungs4\":\""+lungs4_+"\",\n\t\"heart1\":\""+heart1_+"\",\n\t\"heart2\":\""+heart2_+"\",\n\t\"heart3\":\""+heart3_+"\",\n\t\"heart4\":\""+heart4_+"\",\n\t\"AD\":\""+AD_+"\",\n\t\"stomach1\":\""+stomach1_+"\",\n\t\"stomach2\":\""+stomach2_+"\",\n\t\"stomach3\":\""+stomach3_+"\",\n\t\"stomach4\":\""+stomach4_+"\",\n\t\"liver\":\""+liver_+"\",\n\t\"tremor1\":\""+tremor1_+"\",\n\t\"tremor2\":\""+tremor2_+"\",\n\t\"tremor3\":\""+tremor3_+"\",\n\t\"eyes\":\""+eyes_+"\",\n\t\"edema\":\""+edema_+"\",\n\t\"diarrhea\":\""+diarrhea_+"\"\n\t}";
        socket->write(summary);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString label = ui->label->text();
    QString username = label.mid(18,5);

    QByteArray username_ = username.toUtf8();

    if (socket->isOpen())
    {
        socket->write("{\n\t\"login\":\""+username_+"\",\"patient\":\"list\"}");
    }
}

void MainWindow::disableButtons()
{
    for (int i = 3; i <= 22; i++)
    {
        QPushButton *button = findChild<QPushButton *>("pushButton_" + QString::number(i));
        if (button == nullptr) continue;
        button->setEnabled(false);
    }
}

void MainWindow::grabcheckboxstate()
{
    if (ui->checkBox_1->isChecked()) complaint1_ = "ON";
    else complaint1_ = "OFF";

    if (ui->checkBox_2->isChecked()) complaint2_ = "ON";
    else complaint2_ = "OFF";

    if (ui->checkBox_3->isChecked()) complaint3_ = "ON";
    else complaint3_ = "OFF";

    if (ui->checkBox_4->isChecked()) complaint4_ = "ON";
    else complaint4_ = "OFF";

    if (ui->checkBox_5->isChecked()) complaint5_ = "ON";
    else complaint5_ = "OFF";

    if (ui->checkBox_6->isChecked()) complaint6_ = "ON";
    else complaint6_ = "OFF";

    if (ui->checkBox_7->isChecked()) complaint7_ = "ON";
    else complaint7_ = "OFF";

    if (ui->checkBox_8->isChecked()) complaint8_ = "ON";
    else complaint8_ = "OFF";

    if (ui->checkBox_9->isChecked()) complaint9_ = "ON";
    else complaint9_ = "OFF";

    if (ui->checkBox_10->isChecked()) complaint10_ = "ON";
    else complaint10_ = "OFF";

    if (ui->checkBox_11->isChecked()) complaint11_ = "ON";
    else complaint11_ = "OFF";

    if (ui->checkBox_12->isChecked()) complaint12_ = "ON";
    else complaint12_ = "OFF";

    if (ui->checkBox_13->isChecked()) complaint13_ = "ON";
    else complaint13_ = "OFF";

    if (ui->checkBox_14->isChecked()) complaint14_ = "ON";
    else complaint14_ = "OFF";

    if (ui->checkBox_15->isChecked()) complaint15_ = "ON";
    else complaint15_ = "OFF";

    if (ui->checkBox_16->isChecked()) complaint16_ = "ON";
    else complaint16_ = "OFF";

    if (ui->checkBox_17->isChecked()) complaint17_ = "ON";
    else complaint17_ = "OFF";

    if (ui->checkBox_18->isChecked()) complaint18_ = "ON";
    else complaint18_ = "OFF";

    if (ui->checkBox_19->isChecked()) complaint19_ = "ON";
    else complaint19_ = "OFF";

    if (ui->checkBox_20->isChecked()) condition1_ = "ON";
    else condition1_ = "OFF";

    if (ui->checkBox_63->isChecked()) condition2_ = "ON";
    else condition2_ = "OFF";

    if (ui->checkBox->isChecked()) skin1_ = "ON";
    else skin1_ = "OFF";

    if (ui->checkBox_58->isChecked()) skin2_ = "ON";
    else skin2_ = "OFF";

    if (ui->checkBox_62->isChecked()) skin3_ = "ON";
    else skin3_ = "OFF";

    if (ui->checkBox_59->isChecked()) skin4_ = "ON";
    else skin4_ = "OFF";

    if (ui->checkBox_61->isChecked()) skin5_ = "ON";
    else skin5_ = "OFF";

    if (ui->checkBox_60->isChecked()) skin6_ = "ON";
    else skin6_ = "OFF";

    if (ui->checkBox_69->isChecked()) thyroid1_ = "ON";
    else thyroid1_ = "OFF";

    if (ui->checkBox_70->isChecked()) thyroid2_ = "ON";
    else thyroid2_ = "OFF";

    if (ui->checkBox_71->isChecked()) thyroid3_ = "ON";
    else thyroid3_ = "OFF";

    if (ui->checkBox_72->isChecked()) thyroid4_ = "ON";
    else thyroid4_ = "OFF";

    if (ui->checkBox_73->isChecked()) thyroid5_ = "ON";
    else thyroid5_ = "OFF";

    if (ui->checkBox_74->isChecked()) thyroid6_ = "ON";
    else thyroid6_ = "OFF";

    if (ui->checkBox_75->isChecked()) lungs1_ = "ON";
    else lungs1_ = "OFF";

    if (ui->checkBox_76->isChecked()) lungs2_ = "ON";
    else lungs2_ = "OFF";

    if (ui->checkBox_77->isChecked()) lungs3_ = "ON";
    else lungs3_ = "OFF";

    if (ui->checkBox_78->isChecked()) heart1_ = "ON";
    else heart1_ = "OFF";

    if (ui->checkBox_79->isChecked()) heart2_ = "ON";
    else heart2_ = "OFF";

    if (ui->checkBox_80->isChecked()) heart3_ = "ON";
    else heart3_ = "OFF";

    if (ui->checkBox_81->isChecked()) stomach1_ = "ON";
    else stomach1_ = "OFF";

    if (ui->checkBox_82->isChecked()) stomach2_ = "ON";
    else stomach2_ = "OFF";

    if (ui->checkBox_83->isChecked()) stomach3_ = "ON";
    else stomach3_ = "OFF";

    if (ui->checkBox_84->isChecked()) tremor1_ = "ON";
    else tremor1_ = "OFF";

    if (ui->checkBox_85->isChecked()) tremor2_ = "ON";
    else tremor2_ = "OFF";

    if (ui->checkBox_86->isChecked()) tremor3_ = "ON";
    else tremor3_ = "OFF";
}

void MainWindow::on_pushButton_3_clicked()
{
    QString patientName = ui->pushButton_3->text();
    QByteArray patientName_ = patientName.toUtf8();
    QString label = ui->label->text();
    QString username = label.mid(18,5);

    QByteArray username_ = username.toUtf8();

    if (socket->isOpen())
    {
        socket->write("{\"patientname\":\"YES\",\"username\":\""+username_+"\",\"value\":\""+patientName_+"\"}");
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString patientName = ui->pushButton_4->text();
    QByteArray patientName_ = patientName.toUtf8();
    QString label = ui->label->text();
    QString username = label.mid(18,5);

    QByteArray username_ = username.toUtf8();

    if (socket->isOpen())
    {
        socket->write("{\"patientname\":\"YES\",\"username\":\""+username_+"\",\"value\":\""+patientName_+"\"}");
    }
}
