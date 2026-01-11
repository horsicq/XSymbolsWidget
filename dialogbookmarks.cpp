/* Copyright (c) 2023-2026 hors<horsicq@gmail.com>
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

DialogBookmarks::DialogBookmarks(QWidget *pParent) : XShortcutsDialog(pParent, false), ui(new Ui::DialogBookmarks)
{
    ui->setupUi(this);

    m_pXInfoDB = nullptr;
    m_nOffset = 0;
    m_nAddress = 0;
    m_nSize = 0;
}

DialogBookmarks::~DialogBookmarks()
{
    delete ui;
}

void DialogBookmarks::setData(XInfoDB *pXInfoDB, qint64 nOffset, XADDR nAddress, qint64 nSize)
{
    m_pXInfoDB = pXInfoDB;
    m_nOffset = nOffset;
    m_nAddress = nAddress;
    m_nSize = nSize;

    connect(m_pXInfoDB, SIGNAL(reloadViewSignal()), this, SLOT(reload()));

    reload();
}

void DialogBookmarks::adjustView()
{
}

void DialogBookmarks::reload()
{
    const bool bBlock1 = ui->tableWidgetBookmarks->blockSignals(true);

    QList<QString> listHeaders;

    listHeaders.append(tr("Location"));
    listHeaders.append(tr("Size"));
    listHeaders.append(tr("Color"));
    listHeaders.append(tr("Comment"));
    listHeaders.append("");

    QVector<XInfoDB::BOOKMARKRECORD> listRecord;

    if (m_nOffset != -1) {
        listRecord.append(m_pXInfoDB->getBookmarkRecords(m_nOffset, XBinary::LT_OFFSET, m_nSize));
    }

    if (m_nAddress != (XADDR)-1) {
        listRecord.append(m_pXInfoDB->getBookmarkRecords(m_nAddress, XBinary::LT_ADDRESS, m_nSize));
    }

    qint32 nNumberOfRecords = listRecord.count();

    ui->tableWidgetBookmarks->setRowCount(nNumberOfRecords);
    ui->tableWidgetBookmarks->setColumnCount(listHeaders.count());

    ui->tableWidgetBookmarks->setHorizontalHeaderLabels(listHeaders);

    for (qint32 i = 0; i < nNumberOfRecords; i++) {
        {
            QTableWidgetItem *pItem = new QTableWidgetItem;
            QString sLocation = XBinary::valueToHexEx(listRecord.at(i).nLocation);
            if (listRecord.at(i).locationType == XBinary::LT_ADDRESS) {
                sLocation = QString("%1: %2").arg(tr("Address"), sLocation);
            } else if (listRecord.at(i).locationType == XBinary::LT_OFFSET) {
                sLocation = QString("%1: %2").arg(tr("Offset"), sLocation);
            }

            pItem->setText(sLocation);
            pItem->setData(Qt::UserRole + 0, listRecord.at(i).nLocation);
            pItem->setData(Qt::UserRole + 1, listRecord.at(i).nSize);
            pItem->setData(Qt::UserRole + 2, listRecord.at(i).locationType);

            ui->tableWidgetBookmarks->setItem(i, 0, pItem);
        }
        {
            QTableWidgetItem *pItem = new QTableWidgetItem;
            pItem->setText(XBinary::valueToHexEx(listRecord.at(i).nSize));

            ui->tableWidgetBookmarks->setItem(i, 1, pItem);
        }
        {
            QString sColor = listRecord.at(i).sColorBackground;
            QPushButton *pPushButtonBackgroundColor = new QPushButton;
            pPushButtonBackgroundColor->setText("");
            pPushButtonBackgroundColor->setStyleSheet(QString("background-color: %1").arg(sColor));
            pPushButtonBackgroundColor->setProperty("UUID", listRecord.at(i).sUUID);
            pPushButtonBackgroundColor->setProperty("COLOR", sColor);

            connect(pPushButtonBackgroundColor, SIGNAL(clicked(bool)), this, SLOT(pushButtonColorSlot()));
            ui->tableWidgetBookmarks->setCellWidget(i, 2, pPushButtonBackgroundColor);
        }
        {
            QLineEdit *pLineEdit = new QLineEdit;
            pLineEdit->setText(listRecord.at(i).sComment);
            pLineEdit->setProperty("UUID", listRecord.at(i).sUUID);

            connect(pLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(lineEditTextChangedSlot(const QString &)));
            ui->tableWidgetBookmarks->setCellWidget(i, 3, pLineEdit);
        }
        {
            QPushButton *pPushButtonRemove = new QPushButton;
            pPushButtonRemove->setText("X");
            pPushButtonRemove->setProperty("UUID", listRecord.at(i).sUUID);

            connect(pPushButtonRemove, SIGNAL(clicked(bool)), this, SLOT(pushButtonRemoveSlot()));
            ui->tableWidgetBookmarks->setCellWidget(i, 4, pPushButtonRemove);
        }
    }

    ui->tableWidgetBookmarks->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->tableWidgetBookmarks->setColumnWidth(0, 120);
    ui->tableWidgetBookmarks->setColumnWidth(4, 30);

    ui->tableWidgetBookmarks->blockSignals(bBlock1);
}

void DialogBookmarks::on_pushButtonOK_clicked()
{
    this->close();
}

void DialogBookmarks::pushButtonColorSlot()
{
    QPushButton *pPushButton = qobject_cast<QPushButton *>(sender());

    if (pPushButton) {
        QString sUUID = pPushButton->property("UUID").toString();
        QString sColor = pPushButton->property("COLOR").toString();

        QColor color = XOptions::stringToColor(sColor);

        color = XOptions::getColorDialog(this, tr("Background"), color);

        if (color.isValid()) {
            sColor = XOptions::colorToString(color);

            pPushButton->setStyleSheet(QString("background-color: %1").arg(sColor));

            m_pXInfoDB->updateBookmarkRecordColorBackground(sUUID, sColor);
            m_pXInfoDB->reloadView();
        }
    }
}

void DialogBookmarks::pushButtonRemoveSlot()
{
    QPushButton *pPushButton = qobject_cast<QPushButton *>(sender());

    if (pPushButton) {
        QString sUUID = pPushButton->property("UUID").toString();

        m_pXInfoDB->removeBookmarkRecord(sUUID);
        m_pXInfoDB->reloadView();

        reload();
    }
}

void DialogBookmarks::lineEditTextChangedSlot(const QString &sText)
{
    const bool bBlocked1 = m_pXInfoDB->blockSignals(true);

    QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(sender());

    if (pLineEdit) {
        QString sUUID = pLineEdit->property("UUID").toString();
        m_pXInfoDB->updateBookmarkRecordComment(sUUID, sText);
        m_pXInfoDB->reloadView();
    }

    m_pXInfoDB->blockSignals(bBlocked1);
}

void DialogBookmarks::on_tableWidgetBookmarks_currentCellChanged(int nCurrentRow, int nCurrentColumn, int nPreviousRow, int nPreviousColumn)
{
    Q_UNUSED(nCurrentColumn)
    Q_UNUSED(nPreviousColumn)

    if (nPreviousRow != -1) {
        QTableWidgetItem *pItem = ui->tableWidgetBookmarks->item(nCurrentRow, 0);

        if (pItem) {
            quint64 nLocation = pItem->data(Qt::UserRole + 0).toULongLong();
            quint64 nSize = pItem->data(Qt::UserRole + 1).toLongLong();
            quint32 nLocType = pItem->data(Qt::UserRole + 2).toLongLong();

            emit currentLocationChanged(nLocation, nLocType, nSize);
        }
    }
}

void DialogBookmarks::on_tableWidgetBookmarks_itemClicked(QTableWidgetItem *pItem)
{
    if (pItem) {
        QTableWidgetItem *_pItem = ui->tableWidgetBookmarks->item(pItem->row(), 0);

        if (_pItem) {
            quint64 nLocation = _pItem->data(Qt::UserRole + 0).toULongLong();
            quint64 nSize = _pItem->data(Qt::UserRole + 1).toLongLong();
            quint32 nLocType = pItem->data(Qt::UserRole + 2).toLongLong();

            emit currentLocationChanged(nLocation, nLocType, nSize);
        }
    }
}

void DialogBookmarks::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}
