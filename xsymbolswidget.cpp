/* Copyright (c) 2023-2025 hors<horsicq@gmail.com>
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

    g_pDevice = nullptr;
    g_pXInfoDB = nullptr;
}

XSymbolsWidget::~XSymbolsWidget()
{
    delete ui;
}

void XSymbolsWidget::setData(QIODevice *pDevice, const OPTIONS &options, XInfoDB *pXInfoDB, bool bReload)
{
    g_pDevice = pDevice;
    g_pXInfoDB = pXInfoDB;
    g_options = options;

    XFormats::setFileTypeComboBox(options.fileType, g_pDevice, ui->comboBoxType);

    if (bReload) {
        reload();
    }
}

void XSymbolsWidget::reload()
{
    if (g_pXInfoDB) {
        XModel_XSymbol *pModel = new XModel_XSymbol(g_pXInfoDB, g_options.fileType, g_options.symbolMode, this);

        ui->tableViewSymbols->setCustomModel(pModel, true);
        // XBinary::MODE modeAddress = XBinary::getModeOS();
        connect(ui->tableViewSymbols->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                SLOT(on_tableViewSelection(QItemSelection, QItemSelection)));
    }
}

void XSymbolsWidget::adjustView()
{
    getGlobalOptions()->adjustWidget(this, XOptions::ID_VIEW_FONT_CONTROLS);
    getGlobalOptions()->adjustTableView(ui->tableViewSymbols, XOptions::ID_VIEW_FONT_TABLEVIEWS);
    ui->tableViewSymbols->adjust();
}

void XSymbolsWidget::reloadData(bool bSaveSelection)
{
    Q_UNUSED(bSaveSelection)
    reload();
}

void XSymbolsWidget::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}

void XSymbolsWidget::on_pushButtonSaveSymbols_clicked()
{
    // XShortcutsWidget::saveTableModel(ui->tableViewSymbols->getProxyModel(), XBinary::getResultFileName(g_pXInfoDB->getDevice(), QString("%1.txt").arg(tr("Symbols"))));
}

void XSymbolsWidget::on_tableViewSelection(const QItemSelection &itemSelected, const QItemSelection &itemDeselected)
{
    Q_UNUSED(itemSelected)
    Q_UNUSED(itemDeselected)

    viewSelection();
}

void XSymbolsWidget::on_tableViewSymbols_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)

    viewSelection();
}

void XSymbolsWidget::viewSelection()
{
    QItemSelectionModel *pSelectionModel = ui->tableViewSymbols->selectionModel();

    if (pSelectionModel) {
        QModelIndexList listIndexes = pSelectionModel->selectedIndexes();

        if (listIndexes.count()) {
            QModelIndex indexNumber = listIndexes.at(XModel_XSymbol::COLUMN_NUMBER);
            XADDR nVirtualAddress = ui->tableViewSymbols->model()->data(indexNumber, Qt::UserRole + XModel_XSymbol::USERROLE_ADDRESS).toULongLong();
            qint64 nOffset = ui->tableViewSymbols->model()->data(indexNumber, Qt::UserRole + XModel_XSymbol::USERROLE_OFFSET).toULongLong();
            qint64 nSize = ui->tableViewSymbols->model()->data(indexNumber, Qt::UserRole + XModel_XSymbol::USERROLE_SIZE).toLongLong();

            if (nOffset != -1) {
                emit currentLocationChanged(nOffset, XBinary::LT_OFFSET, nSize);
            } else if (nVirtualAddress != (XADDR)-1) {
                emit currentLocationChanged(nVirtualAddress, XBinary::LT_ADDRESS, nSize);
            }
        }
    }
}
