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
#ifndef DIALOGXSYMBOLS_H
#define DIALOGXSYMBOLS_H

#include "xinfodb.h"
#include "xshortcutsdialog.h"
#include "xsymbolswidget.h"

namespace Ui {
class DialogXSymbols;
}

class DialogXSymbols : public XShortcutsDialog {
    Q_OBJECT

public:
    explicit DialogXSymbols(QWidget *pParent = nullptr);
    ~DialogXSymbols();

    virtual void adjustView();

    void setData(QIODevice *pDevice, const XSymbolsWidget::OPTIONS &options, XInfoDB *pXInfoDB, bool bReload = true);

private slots:
    void on_pushButtonClose_clicked();

signals:
    void currentSymbolChanged(XADDR nAddress, qint64 nSize);

protected:
    virtual void registerShortcuts(bool bState);

private:
    Ui::DialogXSymbols *ui;
};

#endif  // DIALOGXSYMBOLS_H
