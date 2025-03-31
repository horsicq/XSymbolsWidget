/* Copyright (c) 2025 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef XMODEL_XSYMBOL_H
#define XMODEL_XSYMBOL_H

#include "xmodel.h"
#include "xinfodb.h"

class XModel_XSymbol : public XModel {
    Q_OBJECT

public:
    enum COLUMN {
        COLUMN_NUMBER,
        COLUMN_OFFSET,
        COLUMN_ADDRESS,
        COLUMN_REGION,
        COLUMN_SIZE,
        COLUMN_SYMBOL,
        __COLUMN_SIZE
    };

    enum USERROLE {
        USERROLE_SIZE = 0,
        USERROLE_OFFSET,
        USERROLE_ADDRESS,
        USERROLE_TYPE
    };

    explicit XModel_XSymbol(XInfoDB *pXInfoDB, XBinary::FT fileType, XInfoDB::SYMBOL_MODE symbolMode, QObject *parent = nullptr);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int nRole = Qt::DisplayRole) const;
    virtual QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
    virtual qint32 getColumnSymbolSize(qint32 nColumn);
    virtual SORT_METHOD getSortMethod(qint32 nColumn);

private:
    XInfoDB *g_pXInfoDB;
    XBinary::FT g_fileType;
    XInfoDB::SYMBOL_MODE g_symbolMode;
    XInfoDB::STATE *g_pState;
    qint32 g_nRowCount;
    qint32 g_nColumnCount;
    qint32 g_nColumnWidths[__COLUMN_SIZE];
    XBinary::MODE g_modeAddress;
    XBinary::MODE g_modeOffset;
};

#endif  // XMODEL_XSYMBOL_H
