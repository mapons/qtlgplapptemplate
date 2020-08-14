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
#ifndef LEGAL_H
#define LEGAL_H

#include<QQmlEngine>

class QtLegal: public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString licenses MEMBER m_licenses NOTIFY  dataChanged)
  Q_PROPERTY(QString version MEMBER m_version NOTIFY dataChanged)
  Q_PROPERTY(QString extendedversion MEMBER m_extendedversion NOTIFY  dataChanged)
  Q_PROPERTY(QString release MEMBER m_release NOTIFY  dataChanged)
public:
  static QtLegal * instance();
  static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine); //esto hace falta para la singleton ...
  Q_INVOKABLE QString const aboutQT();
  Q_INVOKABLE QString const saveReleaseLocaly();
  void setVersionData(const QString &version,const QString &buildDate="",const QString &changeLogFile="" );
signals:
  void dataChanged();
private:
  QString  const os();
  QtLegal ();
  QString m_licenses,m_version,m_extendedversion,m_release;
};

#endif // QtLEGAL_H
