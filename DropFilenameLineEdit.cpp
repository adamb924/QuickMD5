/*
 * DropFilenameLineEdit.cpp
 *
 *  Created on: Aug 1, 2012
 *      Author: Adam
 */

#include <QtGui>

#include "DropFilenameLineEdit.h"
#include "hash.h"

DropFilenameLineEdit::DropFilenameLineEdit( QWidget * parent ) : QLineEdit(parent)
{
    setAcceptDrops(true);
}

DropFilenameLineEdit::DropFilenameLineEdit()
{
    setAcceptDrops(true);
}

DropFilenameLineEdit::~DropFilenameLineEdit()
{
}

void DropFilenameLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void DropFilenameLineEdit::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        QString filename = event->mimeData()->urls().at(0).toLocalFile();

        QDir d(filename);
        if( d.exists() )
        {
            emit directoryChanged(filename);
            setText(tr("<Folder>"));
        }
        else
        {
            setText( fileHash(filename) );
        }
        emit filenameChanged(filename);
    }
}
