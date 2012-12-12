#include "hash.h"

#include <QString>
#include <QCryptographicHash>
#include <QFile>

QString fileHash( const QString & filename )
{
    QCryptographicHash crypto(QCryptographicHash::Md5);
    QFile file(filename);
    file.open(QFile::ReadOnly);
    while(!file.atEnd()){
        crypto.addData(file.read(8192));
    }
    return QString( crypto.result().toHex() );
}
