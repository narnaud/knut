#pragma once

#include "core/mark.h"
#include <QWidget>

class QRubberBand;
class QToolButton;

namespace Core {
class TextDocument;
}
namespace Gui {

class ScriptSuggestions;

class TextView : public QWidget
{
    Q_OBJECT
public:
    explicit TextView(QWidget *parent = nullptr);

    void setTextDocument(Core::TextDocument *document);

    void toggleMark();
    void gotoMark();
    void selectToMark();
    bool hasMark() const;

    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void updateMarkRect();
    void updateQuickActionRect();
    void showQuickActionMenu();

    Core::TextDocument *m_document;
    std::optional<Core::Mark> m_mark = {};
    QWidget *m_markRect = nullptr;
    ScriptSuggestions *m_scriptSuggestions = nullptr;
    QToolButton *m_quickActionButton = nullptr;
};

} // namespace Gui
