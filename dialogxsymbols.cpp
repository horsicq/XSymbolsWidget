/* Copyright (c) 2022-2025 hors<horsicq@gmail.com>
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
#include "dialogxsymbols.h"

#include "ui_dialogxsymbols.h"

DialogXSymbols::DialogXSymbols(QWidget *pParent) : XShortcutsDialog(pParent, true), ui(new Ui::DialogXSymbols)
{
    ui->setupUi(this);

    connect(ui->widgetSymbols, SIGNAL(currentSymbolChanged(XADDR, qint64)), this, SIGNAL(currentSymbolChanged(XADDR, qint64)));
}

DialogXSymbols::~DialogXSymbols()
{
    delete ui;
}

void DialogXSymbols::adjustView()
{
}

void DialogXSymbols::setData(XInfoDB *pXInfoDB, XInfoDB::PROFILE profile, XInfoDB::SYMBOL_MODE mode, bool bReload)
{
    ui->widgetSymbols->setData(pXInfoDB, profile, mode, bReload);

    // TODO function
    // QString sTitle;

    // if (mode == XInfoDB::SYMBOL_MODE_ALL) {
    //     sTitle = tr("Symbols");
    // } else if (mode == XSymbolsWidget::MODE_FUNCTIONS) {
    //     sTitle = tr("Functions");
    // } else if (mode == XSymbolsWidget::MODE_REFERENCES) {
    //     sTitle = tr("References");
    // }

    // setWindowTitle(sTitle);
}

void DialogXSymbols::on_pushButtonClose_clicked()
{
    this->close();
}

void DialogXSymbols::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}
