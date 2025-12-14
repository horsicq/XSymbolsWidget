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

    explicit XModel_XSymbol(XInfoDB *pXInfoDB, XBinary::FT fileType, XInfoDB::SYMBOL_MODE symbolMode, QObject *pParent = nullptr);

    virtual QVariant data(const QModelIndex &index, int nRole = Qt::DisplayRole) const;
    virtual QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
    virtual SORT_METHOD getSortMethod(qint32 nColumn);

private:
    XInfoDB *m_pXInfoDB;
    XBinary::FT m_fileType;
    XInfoDB::SYMBOL_MODE m_symbolMode;
    XInfoDB::STATE *m_pState;
    XBinary::MODE m_modeAddress;
    XBinary::MODE m_modeOffset;
};

#endif  // XMODEL_XSYMBOL_H
