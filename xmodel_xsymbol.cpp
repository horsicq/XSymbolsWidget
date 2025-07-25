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

#include "xmodel_xsymbol.h"

XModel_XSymbol::XModel_XSymbol(XInfoDB *pXInfoDB, XBinary::FT fileType, XInfoDB::SYMBOL_MODE symbolMode, QObject *pParent) : XModel(pParent)
{
    g_pXInfoDB = pXInfoDB;
    g_symbolMode = symbolMode;

    g_pState = g_pXInfoDB->getState(fileType);

    _setRowCount(g_pState->listSymbols.count());
    _setColumnCount(__COLUMN_SIZE);

    g_modeAddress = XBinary::getWidthModeFromSize(g_pState->memoryMap.nModuleAddress + g_pState->memoryMap.nImageSize);
    g_modeOffset = XBinary::getWidthModeFromSize(g_pState->memoryMap.nBinarySize);

    setColumnSymbolSize(COLUMN_NUMBER, QString::number(rowCount()).length());
    setColumnSymbolSize(COLUMN_OFFSET, XBinary::getByteSizeFromWidthMode(g_modeOffset) * 2);
    setColumnSymbolSize(COLUMN_ADDRESS, XBinary::getByteSizeFromWidthMode(g_modeAddress) * 2);
    setColumnSymbolSize(COLUMN_REGION, 1);
    setColumnSymbolSize(COLUMN_SIZE, 4);
    setColumnSymbolSize(COLUMN_SYMBOL, 100);

    qint32 nNumberOfRegions = g_pState->memoryMap.listRecords.count();
    qint32 nMaxRegionNameLength = 4;

    for (qint32 i = 0; i < nNumberOfRegions; i++) {
        nMaxRegionNameLength = qMax(nMaxRegionNameLength, g_pState->memoryMap.listRecords.at(i).sName.length());
        nMaxRegionNameLength = qMin(50, nMaxRegionNameLength);
    }

    setColumnSymbolSize(COLUMN_REGION, nMaxRegionNameLength);
}

QVariant XModel_XSymbol::data(const QModelIndex &index, int nRole) const
{
    QVariant result;

    if (index.isValid()) {
        qint32 nRow = index.row();

        if (nRow >= 0) {
            qint32 nColumn = index.column();

            if (nRole == Qt::DisplayRole) {
                if (nColumn == COLUMN_NUMBER) {
                    result = nRow;
                } else if (nColumn == COLUMN_OFFSET) {
                    qint16 nRegionIndex = g_pState->listSymbols.at(nRow).nRegionIndex;
                    if (nRegionIndex != -1) {
                        if (g_pState->memoryMap.listRecords.at(nRegionIndex).nOffset != -1) {
                            result =
                                XBinary::valueToHex(g_modeOffset, g_pState->memoryMap.listRecords.at(nRegionIndex).nOffset + g_pState->listSymbols.at(nRow).nRelOffset);
                        }
                    } else {
                        result = XBinary::valueToHex(g_modeOffset, g_pState->listSymbols.at(nRow).nRelOffset);
                    }
                } else if (nColumn == COLUMN_ADDRESS) {
                    qint16 nRegionIndex = g_pState->listSymbols.at(nRow).nRegionIndex;
                    if (nRegionIndex != -1) {
                        if (g_pState->memoryMap.listRecords.at(nRegionIndex).nAddress != (XADDR)-1) {
                            result =
                                XBinary::valueToHex(g_modeAddress, g_pState->memoryMap.listRecords.at(nRegionIndex).nAddress + g_pState->listSymbols.at(nRow).nRelOffset);
                        }
                    }
                } else if (nColumn == COLUMN_REGION) {
                    if (g_pState->listSymbols.at(nRow).nRegionIndex != (quint16)-1) {
                        result = g_pState->memoryMap.listRecords.at(g_pState->listSymbols.at(nRow).nRegionIndex).sName;
                    }
                } else if (nColumn == COLUMN_SIZE) {
                    result = QString::number(g_pState->listSymbols.at(nRow).nSize, 16);
                } else if (nColumn == COLUMN_SYMBOL) {
                    result =
                        g_pXInfoDB->_getSymbolStringBySegmentRelOffset(g_pState, g_pState->listSymbols.at(nRow).nRegionIndex, g_pState->listSymbols.at(nRow).nRelOffset);
                }
            } else if (nRole == Qt::UserRole + USERROLE_ORIGINDEX) {
                result = nRow;
            } else if (nRole == Qt::UserRole + USERROLE_ADDRESS) {
                qint16 nRegionIndex = g_pState->listSymbols.at(nRow).nRegionIndex;
                if (nRegionIndex != -1) {
                    if (g_pState->memoryMap.listRecords.at(nRegionIndex).nAddress != (XADDR)-1) {
                        result = g_pState->memoryMap.listRecords.at(nRegionIndex).nAddress + g_pState->listSymbols.at(nRow).nRelOffset;
                    }
                }
            } else if (nRole == Qt::UserRole + USERROLE_OFFSET) {
                qint16 nRegionIndex = g_pState->listSymbols.at(nRow).nRegionIndex;
                if (nRegionIndex != -1) {
                    if (g_pState->memoryMap.listRecords.at(nRegionIndex).nOffset != -1) {
                        result = g_pState->memoryMap.listRecords.at(nRegionIndex).nOffset + g_pState->listSymbols.at(nRow).nRelOffset;
                    }
                } else {
                    result = g_pState->listSymbols.at(nRow).nRelOffset;
                }
            } else if (nRole == Qt::UserRole + USERROLE_SIZE) {
                result = g_pState->listSymbols.at(nRow).nSize;
            }
        }
    }

    return result;
}

QVariant XModel_XSymbol::headerData(int nSection, Qt::Orientation orientation, int nRole) const
{
    QVariant result;

    if (orientation == Qt::Horizontal) {
        if (nRole == Qt::DisplayRole) {
            if (nSection == COLUMN_NUMBER) {
                result = "#";
            } else if (nSection == COLUMN_OFFSET) {
                result = tr("Offset");
            } else if (nSection == COLUMN_ADDRESS) {
                result = tr("Address");
            } else if (nSection == COLUMN_REGION) {
                result = tr("Region");
            } else if (nSection == COLUMN_SIZE) {
                result = tr("Size");
            } else if (nSection == COLUMN_SYMBOL) {
                result = tr("Symbol");
            }
        } else if (nRole == Qt::TextAlignmentRole) {
            if ((nSection == COLUMN_NUMBER) || (nSection == COLUMN_OFFSET) || (nSection == COLUMN_ADDRESS) || (nSection == COLUMN_SIZE)) {
                result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignRight;
            } else {
                result = (qint32)Qt::AlignVCenter + (qint32)Qt::AlignLeft;
            }
        }
    }

    return result;
}

XModel::SORT_METHOD XModel_XSymbol::getSortMethod(qint32 nColumn)
{
    SORT_METHOD result = SORT_METHOD_DEFAULT;

    if ((nColumn == COLUMN_OFFSET) || (nColumn == COLUMN_OFFSET) || (nColumn == COLUMN_SIZE)) {
        result = SORT_METHOD_HEX;
    }

    return result;
}
