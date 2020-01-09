#pragma once
#include <Crusty.h>
namespace Crusty
{
	namespace Engine
	{
		class __declspec(dllexport) Camera
		{
		public:
			Camera();
			explicit Camera(const int& width, const int& height);
			~Camera();

			void Set_Position(const float& x, const float& y, const float& z);
			void Set_Position_X(const float & x);
			void Set_Position_Y(const float & y);
			void Set_Position_Z(const float & z);
			void Set_Position(const glm::vec3& pos);
			void Update(const float & dt);
			const float Get_Near();
			const float Get_Far();
			void Set_Near(const float& zNear);
			void Set_Far(const float& zFar);
			void Set_Projection(const float & left, const float & right, const float & bottom, const float & top);
			glm::vec3& Get_Position();
			void Render();
			glm::mat4 Get_ProjectionViewMatrix();
			float zNear;
			float zFar;
		private:


			glm::mat4 projection;
			glm::vec3 position;
			glm::mat4 projView;
		};
	}
}

