#pragma once

#include "core/querymatch.h"
#include <QSortFilterProxyModel>

namespace Core {
class LspDocument;
}

namespace Gui {

class ScriptSuggestions : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ScriptSuggestions(Core::LspDocument &document, QObject *parent = nullptr);

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

public slots:
    void run(const QModelIndex &index);

signals:
    void suggestionsUpdated();

private:
    std::optional<Core::QueryMatch> contextQuery(const QStringList &queries) const;

    Core::LspDocument &m_document;
};

} // namespace Gui
