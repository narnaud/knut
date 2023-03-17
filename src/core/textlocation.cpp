#include "textlocation.h"

#include "lspdocument.h"
#include "project.h"

namespace Core {

/*!
 * \qmltype TextLocation
 * \brief Defines a range of text in a file.
 * \inqmlmodule Script
 * \ingroup TextDocument
 * \since 1.1
 * \sa LspDocument
 *
 * A mark is always created by a [LspDocument](lspdocument.md).
 */

/*!
 * \qmlproperty LspDocument TextLocation::document
 * This read-only property contains the source document for this text location.
 */
/*!
 * \qmlproperty TextRange TextLocation::range
 * This read-only property contains the range of text in the document.
 */

QString TextLocation::toString() const
{
    return QString("{'%1', %2}").arg(document->fileName(), range.toString());
}

QVector<TextLocation> TextLocation::fromLsp(const std::vector<Lsp::Location> &locations)
{
    QVector<Core::TextLocation> textLocations;

    for (const auto &location : locations) {
        const auto url = QUrl::fromEncoded(QByteArray::fromStdString(location.uri));
        if (!url.isLocalFile()) {
            continue;
        }
        const auto filepath = url.toLocalFile();

        if (auto *document = qobject_cast<LspDocument *>(Project::instance()->get(filepath))) {
            const auto range = document->toRange(location.range);

            textLocations.emplace_back(TextLocation {.document = document, .range = range});
        }
    }

    return textLocations;
}

} // namespace Core
