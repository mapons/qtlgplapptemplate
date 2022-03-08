/****************************************************************************
**
** Copyright (C) 2020 Dianiux Innova S.L.
** Contact: http://www.dianiuxinnova.com
**
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#include "QtLegal.h"
#include<QMutex>
#include<QMutexLocker>
#include<QFile>
#include<QDir>
#include <QQmlContext>
#include <QDirIterator>
#include <QSysInfo>
#include <QStandardPaths>
#include <QDebug>
#include <QGuiApplication>
#if defined(Q_OS_ANDROID)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QtAndroid>
#endif
#endif
static QtLegal * pinstance  =nullptr;
static QMutex m_mutex;

QtLegal *QtLegal::instance(){
  QMutexLocker lock(&m_mutex);
  if(pinstance==nullptr)pinstance=new QtLegal();
  return pinstance;
}

QObject * QtLegal::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
  Q_UNUSED(engine)
  Q_UNUSED(scriptEngine)
  return instance();
}
QString  const QtLegal::os(){
#if defined(Q_OS_ANDROID)
  return "ANDROID";
#endif
#if defined(Q_OS_IOS)
  return "IOS";
#endif
#if defined(Q_OS_WIN)
  return "WINDOWS";
#endif
#if defined(Q_OS_LINUX)
  return "LINUX";
#endif
  return "UNKNOW";
}

QString  const QtLegal::aboutQT()
{
  QString translatedTextAboutQtCaption;
  QString myos=os();
  if(myos=="ANDROID" ||myos=="IOS"||myos=="WINDOWS" || QSysInfo::currentCpuArchitecture().toUpper()=="X86_64")
    { //QT PRECOMPILADO
      translatedTextAboutQtCaption = QString(
            "<h3>Qt libraries</h3>"
            "<p>This software uses the Qt libraries, version %1</p>"
            "<p>We have used a precompiled version of Qt (LGPLv3), which has been downloaded from the official website <a href=\"http://%2\">%2</a></p>"
            ).arg(
            QLatin1String(QT_VERSION_STR),
            QLatin1String("qt.io/download")
            );
    }else { //QT COMPILADO
      translatedTextAboutQtCaption = QString(
            "<h3>Qt libraries</h3>"
            "<p>This software uses the Qt libraries, version %1</p>"
            "<p>We have build  Qt (LGPLv3) from original sources, which  has been downloaded from the official website/git repositories <a href=\"http://%2\">%2</a></p>"
            ).arg(
            QLatin1String(QT_VERSION_STR),
            QLatin1String("qt.io/download")
            );
    }
  //: Leave this text untranslated or include a verbatim copy of it below
  //: and note that it is the authoritative version in case of doubt.
  const QString translatedTextAboutQtText = QString(
        "<p>Qt is a C++ toolkit for cross-platform application "
        "development.</p>"
        "<p>Qt provides single-source portability across all major desktop "
        "operating systems. It is also available for embedded Linux and other "
        "embedded and mobile operating systems.</p>"
        "<p>Qt is available under multiple licensing options designed "
        "to accommodate the needs of our various users.</p>"
        "<p>Qt licensed under our commercial license agreement is appropriate "
        "for development of proprietary/commercial software where you do not "
        "want to share any source code with third parties or otherwise cannot "
        "comply with the terms of GNU (L)GPL.</p>"
        "<p>Qt licensed under GNU (L)GPL is appropriate for the "
        "development of Qt&nbsp;applications provided you can comply with the terms "
        "and conditions of the respective licenses.</p>"
        "<p>Please see <a href=\"http://%2/\">%2</a> "
        "for an overview of Qt licensing.</p>"
        "<p>Copyright (C) %1 The Qt Company Ltd and other "
        "contributors.</p>"
        "<p>Qt and the Qt logo are trademarks of The Qt Company Ltd.</p>"
        "<p>Qt is The Qt Company Ltd product developed as an open source "
        "project. See <a href=\"http://%3/\">%3</a> for more information.</p>"
        ).arg(QStringLiteral("2020"),
              QStringLiteral("qt.io/licensing"),
              QStringLiteral("qt.io"));
  return translatedTextAboutQtCaption+ translatedTextAboutQtText;
}
/*
 * SAVE release.zip in DOWNLOAD FOLDER
 * In android you need android.permission.WRITE_EXTERNAL_STORAGE for that
 * */
QString const QtLegal::saveReleaseLocaly(){
  QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

  if (path.isEmpty())
    return tr("IMPOSSIBLE TO SAVE. NO DOWNLOAD LOCATION");

  path.append("/release.zip");
  QFile destination (path);
  if(destination.exists())return tr("IMPOSSIBLE TO SAVE")+"\n"+tr("FIRST DELETE  FILE") +" "+path;
  QFile release(":/release.zip");
  if(release.open(QFile::ReadOnly) && destination.open(QFile::WriteOnly))
    {
      destination.write(release.readAll());
      return  tr("FILE SAVED") +path;
    }else{
#if defined(Q_OS_ANDROID)
      //EXAMPLE TO SAVE EMBEDDED RELEASE.ZIP INTO ANDROID DEVICE
    /*  QtAndroid::requestPermissions({"android.permission.WRITE_EXTERNAL_STORAGE"},
                                    [this](const QtAndroid::PermissionResultMap & map) {
          if(map.find("android.permission.WRITE_EXTERNAL_STORAGE")!=map.end()){
              qDebug()<<"SE HA CONCEDIDO EL PERMISO  DE ESCRITURA";
              //   saveReleaseLocaly(); //retry
            }
        });*/
      return tr("IMPOSSIBLE TO SAVE TO")+"\n"+path +"\n"+tr("CHECK") +"\n"+ "android.permission.WRITE_EXTERNAL_STORAGE";
#endif
      return tr("IMPOSSIBLE TO SAVE TO")+"\n"+path ;
    }

}


QtLegal::QtLegal()
{
  Q_INIT_RESOURCE(QtLegal); //init local resources

  //Seach all license files in :/qtlegal/SoftwareLicenses/ folder
  QDirIterator dirFon(":/qtlegal/SoftwareLicenses/",QDirIterator::Subdirectories);
  m_licenses+="<p>*********************</p>";
  while (dirFon.hasNext())
    {
      dirFon.next();
      if (QFileInfo(dirFon.filePath()).isFile())
        {
          if(QFileInfo(dirFon.filePath()).suffix() == "html" ||QFileInfo(dirFon.filePath()).suffix() == "txt" )
            {
              QFile license(dirFon.filePath());
              if(license.open(QFile::ReadOnly)){
                  m_licenses+=  license.readAll();
                  m_licenses+="<p>*********************</p>";
                  m_licenses+="<p>*********************</p>";
                }
            }
        }
    }


emit dataChanged();


  //REGISTER C++ CLASS IN QML
  qmlRegisterSingletonType<QtLegal>("QtLegal", 1, 0, "QtLegal",QtLegal::singletontype_provider);//registrar clase C++ como tipo QML SINGLETON
}
void QtLegal::setVersionData(const QString &version,const QString &buildDate,const QString &changeLogFile ){

    //Generar datos de version
    // QString version=BUILDVERSION;
    // QString builddate=BUILD_DATE;
    QString Versioninfo="<p>" + QGuiApplication::applicationName().toUpper()+"</p>" ;
    Versioninfo+="<p><a style=\"font-size: 18px; text-decoration: none\" href=\"https://"+QGuiApplication::organizationDomain()+"\">"  + QGuiApplication::organizationDomain()  + "</a></p>";

    if(version.size()>0) Versioninfo+="<p>V "+version+" ";
    if(buildDate.size()>0) Versioninfo+=QObject::tr("BUILD DATE") +" "+buildDate+"</p>";

    Versioninfo+="<p>"+QObject::tr("SYSTEM")+" "+QSysInfo::prettyProductName()+ " " +QSysInfo::buildAbi()+" "+QSysInfo::currentCpuArchitecture()+"</p>";
    Versioninfo+="<p>"+QObject::tr("QT")+" V"+ QLatin1String(QT_VERSION_STR)+ "</p>";

    m_extendedversion=Versioninfo;//otrher options
    m_version=version;
    m_release=  Versioninfo;

    //fichero de changelog, si existe, añadirlo
    QFile release(changeLogFile);
    if(release.open(QFile::ReadOnly)){
        m_release+= "<br>";
        QByteArray line;
        while((line=release.readLine()).size()>0)
            m_release+=  line+"<br>";
    }else{
        qDebug()<<"QtLegal::Error oppening changelog file "<<changeLogFile;
    }

    emit dataChanged();

}
