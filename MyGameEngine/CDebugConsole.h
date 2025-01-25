#pragma once
#include "CRender.h"
#include "CAlgorithms.h"
#include <regex>

class CDebugConsole
{
    struct TextFragment {
        std::string text;
        ImVec4 color;
    };

    struct Entry {
        std::vector<TextFragment> fragments;
    };

    std::vector<Entry> m_vMessageVector;

    ImVec4 HexToImVec4(const std::string& hex) {
        float r = (std::stoi(hex.substr(0, 2), nullptr, 16) / 255.0f);
        float g = (std::stoi(hex.substr(2, 2), nullptr, 16) / 255.0f);
        float b = (std::stoi(hex.substr(4, 2), nullptr, 16) / 255.0f);
        return ImVec4(r, g, b, 1.0f);
    }

    std::vector<TextFragment> ParseColoredText(const std::string& text, const ImVec4& startColor) {
        std::vector<TextFragment> fragments;
        std::regex regex(R"(\{([A-Fa-f0-9]{6})\})");
        std::sregex_token_iterator iter(text.begin(), text.end(), regex, { -1, 1 });
        ImVec4 currentColor = startColor;

        bool isColor = false;
        for (; iter != std::sregex_token_iterator(); ++iter) {
            std::string part = iter->str();
            if (isColor) {
                currentColor = HexToImVec4(part);
            }
            else if (!part.empty()) {
                fragments.push_back({ part, currentColor });
            }
            isColor = !isColor;
        }
        return fragments;
    }
public:
	void Draw();
    void AddEntry(const std::string& szText, const ImU32& startColor);
    template <typename ... Args>
    void AddDebugMessage(const std::string& szFormat, Args... args) {
        std::string debugString = CAlgorithms::string_format(szFormat, args...);
        this->AddEntry("[Debug]: {FFFFFF}" + debugString, 0xFF99B080);
    }

    template <typename ... Args>
    void AddErrorMessage(const std::string& szFormat, Args... args) {
        std::string errorString = CAlgorithms::string_format(szFormat, args...);
        this->AddEntry("[Error]: {FFFFFF}" + errorString, 0xFF3C15D6);
    }
};

extern CDebugConsole* g_pDebugConsole;