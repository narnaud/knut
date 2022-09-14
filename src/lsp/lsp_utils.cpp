#include "lsp_utils.h"

namespace Lsp {
namespace Utils {

    QString removeTypeAliasInformation(const QString &typeInfo)
    {

        auto result = typeInfo;
        qsizetype index;
        while ((index = result.indexOf("(aka ")) != -1) {
            qsizetype start = index;
            int braceCount = 0;
            // find the correct matching ")"
            for (; index < result.size() && braceCount >= 0; index++) {
                if (result[index] == '(') {
                    braceCount++;
                } else if (result[index] == ')') {
                    braceCount--;
                }
            }
            qsizetype end = index;
            result.erase(result.begin() + start, result.begin() + end);
        }
        return result.trimmed();
    }

}
}
