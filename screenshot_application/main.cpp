#include <QByteArray>
#include <QScreen>
#include <QApplication>
#include <QPixmap>
#include <QBuffer>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>

QByteArray GetScreenshot(int screen,const char* format,int quality = -1){
    QByteArray screenshot_data;

    QScreen* sc = qApp->screens().at(screen);
    QPixmap px = sc->grabWindow(0);

    QBuffer buffer(&screenshot_data);
    buffer.open(QIODevice::WriteOnly);
    px.save(&buffer,format,quality);

    return screenshot_data;
}


bool WriteToFile(const char* path,const char* name , const QByteArray& data){

    if(!QFileInfo(path).exists()){
        return false;
    }else {
    QString file_path(path);
        if(!file_path.endsWith("/")){
        file_path += "/";
        }

        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz");
        QString fileName = QString("%1_%2.png").arg(name).arg(timestamp);

        file_path.append(fileName);

        QFile file(file_path);
        file.open(QIODevice::WriteOnly);
        file.write(data);

        return file.waitForBytesWritten(10000);

    }

}

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    QByteArray screenshot_data =  GetScreenshot(0,"PNG");
    WriteToFile("C:\\Users\\user\\Desktop\\lessonsQt\\screenshot_application\\arrayPhoto","screenshot", screenshot_data)  ;
    return 0;

}
