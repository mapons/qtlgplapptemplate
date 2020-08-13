/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtScxml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "statemachine.h"

#include "main.h" //ADD THIS INCLUDE
#include "QtLegal.h" //optional Qt legal widget

//test external library
#include <JlCompress.h>
int _main(int argc, char *argv[]) //rename main to _main
{
    // https://doc.qt.io/qt-5/qdir.html#Q_INIT_RESOURCE
    //If the file name contains characters that cannot be part of a valid C++ function name (such as '-'), they have to be replaced by the underscore character ('_').

    Q_INIT_RESOURCE(calculator_qml);//FORCE LINK RESOURCES IN STATIC LIBRARY ..."calculator-qml.qrc"
    
    QGuiApplication app(argc, argv);

    //set software data for legal widget
    //app.setApplicationName("My custom app name");
    app.setOrganizationName("My organization");
    app.setOrganizationDomain("myorganization.com");

    qmlRegisterType<CalculatorStateMachine>("CalculatorStateMachine", 1, 0,
                                            "CalculatorStateMachine");
    //register QML legal component
    QtLegal::instance()->setVersionData("v0.1",BUILD_DATE,":/CHANGELOG.txt");
    
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/calculator-qml.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QuaZip zip("zipFile.zip");
    zip.open(QuaZip::mdUnzip);

 JlCompress::compressFile("text.zip","main.o");
    return app.exec();
}

