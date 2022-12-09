/* Copyright (c) 2022 hors<horsicq@gmail.com>
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
#include "xsymbolswidget.h"

#include "ui_xsymbolswidget.h"

XSymbolsWidget::XSymbolsWidget(QWidget *pParent) : XShortcutsWidget(pParent), ui(new Ui::XSymbolsWidget)
{
    ui->setupUi(this);

    g_pXInfoDB = nullptr;
    g_pModel = nullptr;
    g_pOldModel = nullptr;
}

XSymbolsWidget::~XSymbolsWidget()
{
    delete ui;
}

void XSymbolsWidget::setXInfoDB(XInfoDB *pXInfoDB, bool bReload)
{
    g_pXInfoDB = pXInfoDB;

    if (bReload) {
        reload(true);
    }
}

void XSymbolsWidget::reload(bool bLoadSymbols)
{
    if (g_pXInfoDB) {
        g_pOldModel = g_pModel;

        XBinary::MODE modeAddress = XBinary::getModeOS();

        QList<XInfoDB::SYMBOL> *pListSymbols = g_pXInfoDB->getSymbols();

        qint32 nNumberOfRecords = 0;

        if (bLoadSymbols) {
            nNumberOfRecords = pListSymbols->count();
        }

        g_pModel = new QStandardItemModel(nNumberOfRecords, __HEADER_COLUMN_size);

        // TODO Check if address virtual
        g_pModel->setHeaderData(HEADER_COLUMN_ADDRESS, Qt::Horizontal, tr("Address"));
        g_pModel->setHeaderData(HEADER_COLUMN_SIZE, Qt::Horizontal, tr("Size"));
        g_pModel->setHeaderData(HEADER_COLUMN_SOURCE, Qt::Horizontal, tr("Source"));
        g_pModel->setHeaderData(HEADER_COLUMN_TYPE, Qt::Horizontal, tr("Type"));
        g_pModel->setHeaderData(HEADER_COLUMN_SYMBOL, Qt::Horizontal, tr("Symbol"));

        for (qint32 i = 0; i < nNumberOfRecords; i++) {
            QStandardItem *pItemAddress = new QStandardItem;
            pItemAddress->setText(XBinary::valueToHex(modeAddress, pListSymbols->at(i).nAddress));
            pItemAddress->setData(pListSymbols->at(i).nAddress, Qt::UserRole + USERROLE_ADDRESS);
            pItemAddress->setData(pListSymbols->at(i).nSize, Qt::UserRole + USERROLE_SIZE);
            pItemAddress->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            g_pModel->setItem(i, HEADER_COLUMN_ADDRESS, pItemAddress);

            QStandardItem *pItemSize = new QStandardItem;
            pItemSize->setText(XBinary::valueToHex(modeAddress, pListSymbols->at(i).nSize));
            pItemSize->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            g_pModel->setItem(i, HEADER_COLUMN_SIZE, pItemSize);

            QStandardItem *pItemSource = new QStandardItem;
            pItemSource->setText(XInfoDB::symbolSourceIdToString(pListSymbols->at(i).symbolSource));
            pItemSource->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            g_pModel->setItem(i, HEADER_COLUMN_SOURCE, pItemSource);

            QStandardItem *pItemType = new QStandardItem;
            pItemType->setText(XInfoDB::symbolTypeIdToString(pListSymbols->at(i).symbolType));
            pItemType->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            g_pModel->setItem(i, HEADER_COLUMN_TYPE, pItemType);

            QStandardItem *pItemSymbol = new QStandardItem;
            pItemSymbol->setText(pListSymbols->at(i).sSymbol);
            pItemSymbol->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            g_pModel->setItem(i, HEADER_COLUMN_SYMBOL, pItemSymbol);
        }

        ui->tableViewSymbols->setModel(g_pModel);

        deleteOldStandardModel(&g_pOldModel);
    }
}

void XSymbolsWidget::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}

void XSymbolsWidget::on_pushButtonSaveSymbols_clicked()
{
    if (g_pModel) {
        XShortcutsWidget::saveTableModel(g_pModel, XBinary::getResultFileName(g_pXInfoDB->getDevice(), QString("%1.txt").arg(tr("Symbols"))));
    }
}

void XSymbolsWidget::on_pushButtonReloadSymbols_clicked()
{
    reload(true);
}

void XSymbolsWidget::on_pushButtonClearSymbols_clicked()
{
    reload(false);
}
