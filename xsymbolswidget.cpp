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

    g_pXInfoDB = nullptr;
    g_pModel = nullptr;
    g_mode = XInfoDB::SYMBOL_MODE_ALL;
}

XSymbolsWidget::~XSymbolsWidget()
{
    delete ui;
}

void XSymbolsWidget::setXInfoDB(XInfoDB *pXInfoDB, QString sXInfoProfile)
{
    g_pXInfoDB = pXInfoDB;
    g_sXInfoProfile = sXInfoProfile;
}

void XSymbolsWidget::setData(XInfoDB::SYMBOL_MODE mode, bool bReload)
{
    g_mode = mode;

    if (bReload) {
        reload(true);
    }
}

void XSymbolsWidget::reload(bool bLoadSymbols)
{
    if (g_pXInfoDB) {
        // XBinary::MODE modeAddress = XBinary::getModeOS();
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
    // XShortcutsWidget::saveTableModel(ui->tableViewSymbols->getProxyModel(), XBinary::getResultFileName(g_pXInfoDB->getDevice(), QString("%1.txt").arg(tr("Symbols"))));
}

void XSymbolsWidget::on_pushButtonSymbolsAnalyze_clicked()
{
    // TODO
}
