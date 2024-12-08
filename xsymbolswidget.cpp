/* Copyright (c) 2023-2024 hors<horsicq@gmail.com>
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
        // XBinary::MODE modeAddress = XBinary::getModeOS();

        if (g_mode == MODE_ALL) {
            QList<XInfoDB::SYMBOL> listSymbols = g_pXInfoDB->getAllSymbols();

            qint32 nNumberOfRecords = 0;

            if (bLoadSymbols) {
                nNumberOfRecords = listSymbols.count();
            }

            g_pModel = new QStandardItemModel(nNumberOfRecords, 2);

            // TODO Check if address virtual
            g_pModel->setHeaderData(0, Qt::Horizontal, tr("Address"));
            g_pModel->setHeaderData(1, Qt::Horizontal, tr("Symbol"));

            for (qint32 i = 0; i < nNumberOfRecords; i++) {
                QStandardItem *pItemAddress = new QStandardItem;
                pItemAddress->setText(XBinary::valueToHexEx(listSymbols.at(i).nAddress));
                pItemAddress->setData(listSymbols.at(i).nAddress, Qt::UserRole + (qint32)(USERROLE_ADDRESS));
                pItemAddress->setData(0, Qt::UserRole + (qint32)(USERROLE_SIZE));
                g_pModel->setItem(i, 0, pItemAddress);

                QStandardItem *pItemSymbol = new QStandardItem;
                pItemSymbol->setText(listSymbols.at(i).sSymbol);
                g_pModel->setItem(i, 1, pItemSymbol);
            }

            XOptions::setModelTextAlignment(g_pModel, 0, Qt::AlignRight | Qt::AlignVCenter);
            XOptions::setModelTextAlignment(g_pModel, 1, Qt::AlignLeft | Qt::AlignVCenter);
        } else if (g_mode == MODE_FUNCTIONS) {
            QList<XInfoDB::FUNCTION> listFunctions = g_pXInfoDB->getAllFunctions();

            qint32 nNumberOfFunctions = listFunctions.count();

            g_pModel = new QStandardItemModel(nNumberOfFunctions, 3);

            // TODO Check if address virtual
            g_pModel->setHeaderData(0, Qt::Horizontal, tr("Address"));
            g_pModel->setHeaderData(1, Qt::Horizontal, tr("Size"));
            g_pModel->setHeaderData(2, Qt::Horizontal, tr("Name"));

            for (qint32 i = 0; i < nNumberOfFunctions; i++) {
                QStandardItem *pItemAddress = new QStandardItem;
                pItemAddress->setText(XBinary::valueToHexEx(listFunctions.at(i).nAddress));
                pItemAddress->setData(listFunctions.at(i).nAddress, Qt::UserRole + (qint32)(USERROLE_ADDRESS));
                pItemAddress->setData(listFunctions.at(i).nSize, Qt::UserRole + (qint32)(USERROLE_SIZE));
                g_pModel->setItem(i, 0, pItemAddress);

                QStandardItem *pItemSize = new QStandardItem;
                pItemSize->setText(XBinary::valueToHexEx(listFunctions.at(i).nSize));
                g_pModel->setItem(i, 1, pItemSize);

                QStandardItem *pItemSymbol = new QStandardItem;
                pItemSymbol->setText(listFunctions.at(i).sName);
                g_pModel->setItem(i, 2, pItemSymbol);
            }

            XOptions::setModelTextAlignment(g_pModel, 0, Qt::AlignRight | Qt::AlignVCenter);
            XOptions::setModelTextAlignment(g_pModel, 1, Qt::AlignRight | Qt::AlignVCenter);
            XOptions::setModelTextAlignment(g_pModel, 2, Qt::AlignLeft | Qt::AlignVCenter);
        } else if (g_mode == MODE_REFERENCES) {
            QList<XInfoDB::REFERENCE> listReferences = g_pXInfoDB->getReferencesForAddress(g_varValue.toULongLong());

            qint32 nNumberOfRecords = listReferences.count();

            g_pModel = new QStandardItemModel(nNumberOfRecords, 2);

            g_pModel->setHeaderData(0, Qt::Horizontal, tr("Address"));
            g_pModel->setHeaderData(1, Qt::Horizontal, tr("Code"));

            for (qint32 i = 0; i < nNumberOfRecords; i++) {
                QStandardItem *pItemAddress = new QStandardItem;
                pItemAddress->setText(XBinary::valueToHexEx(listReferences.at(i).nAddress));
                pItemAddress->setData(listReferences.at(i).nAddress, Qt::UserRole + (qint32)(USERROLE_ADDRESS));
                g_pModel->setItem(i, 0, pItemAddress);

                QStandardItem *pItemCode = new QStandardItem;
                pItemCode->setText(listReferences.at(i).sCode);
                g_pModel->setItem(i, 1, pItemCode);
            }

            XOptions::setModelTextAlignment(g_pModel, 0, Qt::AlignRight | Qt::AlignVCenter);
            XOptions::setModelTextAlignment(g_pModel, 1, Qt::AlignLeft | Qt::AlignVCenter);
        }

        ui->tableViewSymbols->setCustomModel(g_pModel, true);
        ui->tableViewSymbols->setColumnWidth(0, 120);  // TODO

        connect(ui->tableViewSymbols->selectionModel(), SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
                SLOT(onTableView_currentRowChanged(QModelIndex, QModelIndex)));
    }
}

void XSymbolsWidget::adjustView()
{
    // TODO
}

void XSymbolsWidget::reloadData(bool bSaveSelection)
{
    Q_UNUSED(bSaveSelection)
    reload(true);
}

void XSymbolsWidget::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}

void XSymbolsWidget::on_pushButtonSaveSymbols_clicked()
{
    XShortcutsWidget::saveTableModel(ui->tableViewSymbols->getProxyModel(), XBinary::getResultFileName(g_pXInfoDB->getDevice(), QString("%1.txt").arg(tr("Symbols"))));
}

void XSymbolsWidget::onTableView_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)

    QModelIndex index = ui->tableViewSymbols->model()->index(current.row(), 0);

    XADDR nAddress = ui->tableViewSymbols->model()->data(index, Qt::UserRole + (qint32)(USERROLE_ADDRESS)).toULongLong();
    qint64 nSize = ui->tableViewSymbols->model()->data(index, Qt::UserRole + (qint32)(USERROLE_SIZE)).toLongLong();

    emit currentSymbolChanged(nAddress, nSize);
}

void XSymbolsWidget::on_tableViewSymbols_clicked(const QModelIndex &index)
{
    QModelIndex _index = ui->tableViewSymbols->model()->index(index.row(), 0);

    XADDR nAddress = ui->tableViewSymbols->model()->data(_index, Qt::UserRole + (qint32)(USERROLE_ADDRESS)).toULongLong();
    qint64 nSize = ui->tableViewSymbols->model()->data(_index, Qt::UserRole + (qint32)(USERROLE_SIZE)).toLongLong();

    emit currentSymbolChanged(nAddress, nSize);
}
