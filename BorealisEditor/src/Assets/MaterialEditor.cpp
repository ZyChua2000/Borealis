#include <imgui.h>
#include "Assets/MaterialEditor.hpp"

#include <string>

#include "Graphics/Material.hpp"

namespace Borealis
{
	bool MaterialEditor::mRender = false;

	void MaterialEditor::RenderEditor()
	{
		if (!mRender) return;

		static char materialName[128] = "New Material";
		ImGui::InputText("Material Name", materialName, IM_ARRAYSIZE(materialName));

		// Texture Maps
        ImGui::Text("Texture Maps:");
        for (int i = Material::Albedo; i <= Material::Emission; ++i)
        {
            Material::TextureMaps textureMap = static_cast<Material::TextureMaps>(i);

            std::string textureName;
            switch (textureMap)
            {
            case Material::Albedo: textureName = "Albedo"; break;
            case Material::Specular: textureName = "Specular"; break;
            case Material::Metallic: textureName = "Metallic"; break;
            case Material::NormalMap: textureName = "Normal Map"; break;
            case Material::HeightMap: textureName = "Height Map"; break;
            case Material::Occlusion: textureName = "Occlusion"; break;
            case Material::DetailMask: textureName = "Detail Mask"; break;
            case Material::Emission: textureName = "Emission"; break;
            }

            ImGui::Button((textureName).c_str());
            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragDropImageItem"))
                {
                    
                }
                ImGui::EndDragDropTarget();
            }
        }

        ImGui::Separator();

		if (ImGui::Button("Save Material"))
		{
			
		}
	}

}