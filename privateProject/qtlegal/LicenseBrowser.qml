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

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtLegal 1.0


Page {
    padding: 0
    id:about
    signal back()
    property string extraLicenseText
    property string urlBinaries
    Component.onCompleted: Qt.callLater(about.forceActiveFocus)
    onFocusChanged: refocus.restart()
    Timer{
        id:refocus
        interval: 200
        onTriggered: if(about.visible)Qt.callLater(about.forceActiveFocus)
    }
    Keys.onPressed:  {
        if (event.key === Qt.Key_Back  || event.key === Qt.Key_Left  ) {
            event.accepted=true;
            about.back()
            console.log("KEY BACK")
        }
    }
header:
    ToolBar {
        id:toolbar
        //width: parent.width
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "<"
                 font.pixelSize: parent.height*.8
                //font.pointSize: 20
                onClicked:{
                    about.back()
                }
                Layout.fillHeight: true
            }
        }
        Label {
            id: titleLabel
            text: qsTr("LEGAL")
            // font.family: "Arial"
          //  font.pixelSize: parent.height*.8
           // font.pixelSize: 20
            elide: Label.ElideRight
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            anchors.centerIn:parent
        }
    }
    Item {
       /* anchors.margins: parent.width*.03
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: toolbar.bottom
        anchors.bottom: bar.top*/
anchors.fill: parent
anchors.margins: parent.width*.03
        StackLayout {
            id:stly
            /*       width: parent.width
            anchors.bottom: bar.top
            anchors.top:parent.top
            anchors.topMargin: parent.height*.1*/
            anchors.fill: parent
            currentIndex: bar.currentIndex
            Flickable {
                width: parent.width
                height: parent.height
                contentWidth: tc.width;
                contentHeight: tc.height
                ScrollBar.vertical: ScrollBar {
                    orientation : Qt.Vertical}
                ScrollBar.horizontal:  ScrollBar { orientation : Qt.Horizontal}
                clip: true
                Label{
                    id:tc
                    width: stly.width
                    wrapMode :Text.WordWrap
                    // font.family: "Arial"
                    text:QtLegal.release+extraLicenseText
                    textFormat : TextEdit.RichText
                    onLinkActivated: {

                        console.log("activated link " + link)
                        Qt.openUrlExternally(link)
                    }
                }
            }
            Flickable {
                width: parent.width
                height: parent.height
                contentWidth: tb.width;
                contentHeight: tb.height
                ScrollBar.vertical: ScrollBar {
                    orientation : Qt.Vertical}
                ScrollBar.horizontal:  ScrollBar { orientation : Qt.Horizontal}
                clip: true
                Label{
                    id:tb
                    width: stly.width
                    wrapMode :Text.WordWrap
                    //font.family: "Arial"
                    property string text1:QtLegal.aboutQT()
                    property string text2:"<p></p><p>USED LICENSES:</p>"+QtLegal.licenses
                    property string text3: "<p></p><p></p><p>*********************</p><p>Your LGPLv3 rights:</p><p></p><p>This Qt project file  contains all necessary files and source code to rebuild the app using your own Qt version.</p>
<p>You must use Qt Creator and a comple Andoid or iOS development environtment.</p>
<p>Then you can install rebuilded app in your onw device</p>
<p><a href=\""+urlBinaries+"\">"+urlBinaries+"</a></p>"
                    property string finalText:{
                        return text1+text2+text3
                        /*
                        var os=Qt.platform.os.toUpperCase() //nuevo lectura de sistema operativo nativo
                        if(os==="ANDROID" || os==="IOS") return text1+text2+text3
                        else return text1+text2  +text3//sin fichero release.zip
                        */
                    }
                    text:finalText+"<p></p>"+"<p></p>"+"<p>*********************</p>"
                    textFormat : TextEdit.RichText
                    onLinkActivated: {
                        if(link=="qrc:/release.zip")
                        {
                            dialogLegal.text=QtLegal.saveReleaseLocaly()
                            dialogLegal.open()
                            // console.log("download internal file")
                        }
                        else Qt.openUrlExternally(link)
                    }
                }
            }


        }
    }
    footer:TabBar {
        id: bar
        width: parent.width
        anchors.bottom: parent.bottom
        TabButton {
            text: qsTr("Release")
            // font.family: "Arial"
        }
        TabButton {
            text: qsTr("Open source licenses")
            //   font.family: "Arial"
        }
    }
    Dialog {
        id: dialogLegal
        modal: true
        title: qsTr("ATTENTION")
        //  font.family: "Arial"
        property alias text:dlabel.text
        Label {
            id:dlabel
            //  font.family: "Arial"
            width: dialogLegal.width
            wrapMode:Text.WrapAnywhere
        }
        standardButtons: Dialog.Ok
        //anchors.centerIn: parent
        y:(parent.height-height)/2
        height: parent.height/2
        width: about.width
    }
}
