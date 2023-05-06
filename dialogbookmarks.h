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
#ifndef DIALOGBOOKMARKS_H
#define DIALOGBOOKMARKS_H

#include <QDialog>
#include <QLineEdit>
#include <QColorDialog>
#include <QTableWidgetItem>
#include "xinfodb.h"

namespace Ui {
class DialogBookmarks;
}

class DialogBookmarks : public QDialog {
    Q_OBJECT

public:
    explicit DialogBookmarks(QWidget *pParent = nullptr);
    ~DialogBookmarks();

    void setData(XInfoDB *pXInfoDB, quint64 nLocation, qint64 nSize);

private slots:
    void reload();
    void on_pushButtonOK_clicked();
    void pushButtonColorSlot();
    void pushButtonRemoveSlot();
    void lineEditTextChangedSlot(const QString &sText);
    void on_tableWidgetBookmarks_currentCellChanged(int nCurrentRow, int nCurrentColumn, int nPreviousRow, int nPreviousColumn);

signals:
    void currentBookmarkChanged(XADDR nLocation, qint64 nSize);

private:
    Ui::DialogBookmarks *ui;
    XInfoDB *g_pXInfoDB;
    quint64 g_nLocation;
    qint64 g_nSize;
};

#endif  // DIALOGBOOKMARKS_H
