// Copyright (c) 2017 hors<horsicq@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 
#include "PluginMainWindow.h"
#include "ui_PluginMainWindow.h"

#include "pluginmain.h"

PluginMainWindow::PluginMainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::PluginMainWindow)
{
    ui->setupUi(this);

    ui->treeWidgetResult->setColumnWidth(0,500);
}

PluginMainWindow::~PluginMainWindow()
{
    delete ui;
}

void PluginMainWindow::on_pushButtonScan_clicked()
{
    QString sFileName=Plugin::sCurrentFileName;

    if(sFileName!="")
    {
        SpecAbstract::SCAN_OPTIONS options={0};
        QList<SpecAbstract::SCAN_STRUCT> listResult;
        DialogStaticScan ds(this);
        ds.setData(sFileName,&options,&listResult);

        ds.exec();

        ui->treeWidgetResult->clear();

        QMap<QString,QTreeWidgetItem *> mapParents;
        QSet<SpecAbstract::RECORD_FILETYPES> stFileTypes;

        for(int i=0;i<listResult.count();i++)
        {
            if(!stFileTypes.contains(listResult.at(i).id.filetype))
            {
                QStringList listParent;
                listParent.append(SpecAbstract::recordFiletypeIdToString(listResult.at(i).id.filetype));
                QTreeWidgetItem *itemParent=0;
                if(listResult.at(i).parentId.nOffset==-1)
                {
                    itemParent=new QTreeWidgetItem(ui->treeWidgetResult,listParent);
                }
                else
                {
                    itemParent=new QTreeWidgetItem(mapParents.value(QString("%1_%2").arg(listResult.at(i).parentId.filetype).arg(listResult.at(i).parentId.nOffset)),listParent);
                }
                mapParents.insert(QString("%1_%2").arg(listResult.at(i).id.filetype).arg(listResult.at(i).id.nOffset),itemParent);

                stFileTypes.insert(listResult.at(i).id.filetype);
            }

            QTreeWidgetItem *itemParent=mapParents.value(QString("%1_%2").arg(listResult.at(i).id.filetype).arg(listResult.at(i).id.nOffset));

            QStringList list;
            list.append(SpecAbstract::createResultString2(&listResult.at(i)));
            QTreeWidgetItem *item=new QTreeWidgetItem(itemParent,list);

            item->setForeground(0,QBrush(Qt::red));
            ui->treeWidgetResult->expandItem(itemParent);
        }
    }
}

void PluginMainWindow::on_pushButtonInfo_clicked()
{
    DialogInfo di(this);

    di.exec();
}
