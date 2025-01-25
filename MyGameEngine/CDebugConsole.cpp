#include "CDebugConsole.h"

CDebugConsole* g_pDebugConsole;

void CDebugConsole::AddEntry(const std::string& szText, const ImU32& startColor) {
	Entry newMessage;
	newMessage.fragments = ParseColoredText(szText, ImGui::ColorConvertU32ToFloat4(startColor));
	this->m_vMessageVector.push_back(newMessage);
}

void CDebugConsole::Draw()
{
	ImGui::Begin("Debug Console");
	for (int i = 0; i < this->m_vMessageVector.size(); i++) {
		const Entry& message = this->m_vMessageVector[i];
		ImVec2 pos(10.f, 20.f + (i * 19.f));


		for (const auto& fragment : message.fragments) {
			ImGui::SetCursorPos(pos);
			ImGui::TextColored(fragment.color, fragment.text.c_str());

			pos.x += ImGui::CalcTextSize(fragment.text.c_str()).x;
		}

		pos.x = 10.f;
	}
	ImGui::End();
}