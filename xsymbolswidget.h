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
#ifndef XSYMBOLSWIDGET_H
#define XSYMBOLSWIDGET_H

#include <QFuture>
#include <QStandardItemModel>
#include <QWidget>

#include "xinfodb.h"
#include "xshortcutswidget.h"
#include "xmodel_xsymbol.h"

namespace Ui {
class XSymbolsWidget;
}

class XSymbolsWidget : public XShortcutsWidget {
    Q_OBJECT

public:
    explicit XSymbolsWidget(QWidget *pParent = nullptr);
    ~XSymbolsWidget();

    void setData(XInfoDB *pXInfoDB, XInfoDB::PROFILE profile, XInfoDB::SYMBOL_MODE mode, bool bReload);

    void reload();
    virtual void adjustView();
    virtual void reloadData(bool bSaveSelection);

signals:
    void currentSymbolChanged(XADDR nAddress, qint64 nSize);

protected:
    virtual void registerShortcuts(bool bState);

private slots:
    void on_pushButtonSaveSymbols_clicked();
    void on_pushButtonSymbolsAnalyze_clicked();
    void on_tableViewSelection(const QItemSelection &itemSelected, const QItemSelection &itemDeselected);
    void on_tableViewSymbols_clicked(const QModelIndex &index);
    void viewSelection();

private:
    Ui::XSymbolsWidget *ui;
    XInfoDB *g_pXInfoDB;
    XInfoDB::PROFILE g_profile;
    XInfoDB::SYMBOL_MODE g_mode;
    QVariant g_varValue;
};

#endif  // XSYMBOLSWIDGET_H
