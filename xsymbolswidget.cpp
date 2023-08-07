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
#include "xsymbolswidget.h"

#include "ui_xsymbolswidget.h"

XSymbolsWidget::XSymbolsWidget(QWidget *pParent) : XShortcutsWidget(pParent), ui(new Ui::XSymbolsWidget)
{
    ui->setupUi(this);

    g_pXInfoDB = nullptr;
    g_pModel = nullptr;
    g_pOldModel = nullptr;
    g_mode = MODE_ALL;
}

XSymbolsWidget::~XSymbolsWidget()
{
    delete ui;
}

void XSymbolsWidget::setData(XInfoDB *pXInfoDB, MODE mode, QVariant varValue, bool bReload)
{
    g_pXInfoDB = pXInfoDB;
    g_mode = mode;
    g_varValue = varValue;

    if (bReload) {
        reload(true);
    }
}

void XSymbolsWidget::reload(bool bLoadSymbols)
{
    if (g_pXInfoDB) {
        g_pOldModel = g_pModel;

        // XBinary::MODE modeAddress = XBinary::getModeOS();

        QList<XInfoDB::SYMBOL> listSymbols;

        if (g_mode == MODE_ALL) {
            listSymbols = g_pXInfoDB->getAllSymbols();
        }

        qint32 nNumberOfRecords = 0;

        if (bLoadSymbols) {
            nNumberOfRecords = listSymbols.count();
        }

        g_pModel = new QStandardItemModel(nNumberOfRecords, __HEADER_COLUMN_size);

        // TODO Check if address virtual
        g_pModel->setHeaderData(HEADER_COLUMN_ADDRESS, Qt::Horizontal, tr("Address"));
        g_pModel->setHeaderData(HEADER_COLUMN_MODULE, Qt::Horizontal, tr("Module"));
        g_pModel->setHeaderData(HEADER_COLUMN_SYMBOL, Qt::Horizontal, tr("Symbol"));

        for (qint32 i = 0; i < nNumberOfRecords; i++) {
            QStandardItem *pItemAddress = new QStandardItem;
            pItemAddress->setText(XBinary::valueToHexEx(listSymbols.at(i).nAddress));
            pItemAddress->setData(listSymbols.at(i).nAddress, Qt::UserRole + USERROLE_ADDRESS);
            //            pItemAddress->setData(listSymbols.at(i).nSize, Qt::UserRole + USERROLE_SIZE);
            g_pModel->setItem(i, HEADER_COLUMN_ADDRESS, pItemAddress);

            // TODO
            //            QStandardItem *pItemModule = new QStandardItem;
            //            pItemModule->setText(XInfoDB::symbolTypeIdToString(listSymbols.at(i).symbolType));
            //            g_pModel->setItem(i, HEADER_COLUMN_MODULE, pItemModule);

            QStandardItem *pItemSymbol = new QStandardItem;
            pItemSymbol->setText(listSymbols.at(i).sSymbol);
            g_pModel->setItem(i, HEADER_COLUMN_SYMBOL, pItemSymbol);
        }

        XOptions::setModelTextAlignment(g_pModel, HEADER_COLUMN_ADDRESS, Qt::AlignRight | Qt::AlignVCenter);
        XOptions::setModelTextAlignment(g_pModel, HEADER_COLUMN_MODULE, Qt::AlignLeft | Qt::AlignVCenter);
        //        XOptions::setModelTextAlignment(g_pModel, HEADER_COLUMN_SOURCE, Qt::AlignLeft | Qt::AlignVCenter);
        //        XOptions::setModelTextAlignment(g_pModel, HEADER_COLUMN_TYPE, Qt::AlignLeft | Qt::AlignVCenter);
        XOptions::setModelTextAlignment(g_pModel, HEADER_COLUMN_SYMBOL, Qt::AlignLeft | Qt::AlignVCenter);

        ui->tableViewSymbols->setModel(g_pModel);

        ui->tableViewSymbols->setColumnWidth(0, 120);  // TODO

        connect(ui->tableViewSymbols->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
                SLOT(onTableView_currentRowChanged(QModelIndex, QModelIndex)));

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

void XSymbolsWidget::onTableView_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)

    QModelIndex index = ui->tableViewSymbols->model()->index(current.row(), 0);

    XADDR nAddress = ui->tableViewSymbols->model()->data(index, Qt::UserRole + USERROLE_ADDRESS).toULongLong();
    qint64 nSize = ui->tableViewSymbols->model()->data(index, Qt::UserRole + USERROLE_SIZE).toULongLong();

    emit currentSymbolChanged(nAddress, nSize);
}
