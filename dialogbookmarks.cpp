/* Copyright (c) 2023 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "dialogbookmarks.h"
#include "ui_dialogbookmarks.h"

DialogBookmarks::DialogBookmarks(QWidget *parent) : QDialog(parent), ui(new Ui::DialogBookmarks)
{
    ui->setupUi(this);
}

DialogBookmarks::~DialogBookmarks()
{
    delete ui;
}

void DialogBookmarks::setData(XInfoDB *pXInfoDB, quint64 nLocation, qint64 nSize)
{
    QList<QString> listHeaders;

    listHeaders.append(tr("Location"));
    listHeaders.append(tr("Size"));
    listHeaders.append(tr("Color"));
    listHeaders.append(tr("Name"));
    listHeaders.append("");

    QList<XInfoDB::BOOKMARKRECORD> listRecord = pXInfoDB->getBookmarkRecords(nLocation, nSize);
    int nNumberOfRecords = listRecord.count();

    ui->tableWidgetBookmarks->setRowCount(nNumberOfRecords);
    ui->tableWidgetBookmarks->setColumnCount(listHeaders.count());

    ui->tableWidgetBookmarks->setHorizontalHeaderLabels(listHeaders);

    for (int i = 0; i < nNumberOfRecords; i++) {
        {
            QTableWidgetItem *pItem = new QTableWidgetItem;
            pItem->setText(XBinary::valueToHexEx(listRecord.at(i).nLocation));

            ui->tableWidgetBookmarks->setItem(i, 0, pItem);
        }
        {
            QTableWidgetItem *pItem = new QTableWidgetItem;
            pItem->setText(XBinary::valueToHexEx(listRecord.at(i).nSize));

            ui->tableWidgetBookmarks->setItem(i, 1, pItem);
        }
        {
            // TODO QButton
        }
        {
            // TODO QLineEdit
            QTableWidgetItem *pItem = new QTableWidgetItem;
            pItem->setText(listRecord.at(i).sName);

            ui->tableWidgetBookmarks->setItem(i, 3, pItem);
        }
        {
           // TODO QButton delete
        }
    }

    ui->tableWidgetBookmarks->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableWidgetBookmarks->setColumnWidth(4, 30);
}

void DialogBookmarks::on_pushButtonOK_clicked()
{
    this->close();
}
