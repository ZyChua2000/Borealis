/******************************************************************************/
/*!
\file		OrthographicCameraController.cpp
\author 	Chua Zheng Yang
\par    	email: c.zhengyang\@digipen.edu
\date   	July 9, 2024
\brief		Implements the class for Orthographic Camera Controller for 
	 		Level Editor's internal camera

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/


#include "BorealisPCH.hpp"
#include <Scene/OrthographicCameraController.hpp>
#include <Core/InputSystem.hpp>
#include <Core/KeyCodes.hpp>
#include <Core/Core.hpp>

namespace Borealis
{
    OrthographicCameraController::OrthographicCameraController(float width, float height, bool rotation) : 
		mRotation(rotation), mAspectRatio(width/height), mZoom(1.f), mBounds({ -mAspectRatio * mZoom, mAspectRatio * mZoom, -mZoom, mZoom }), 
		mCamera(mBounds.Left, mBounds.Right, mBounds.Bottom, mBounds.Top),
		mCameraPosition(0.f,0.f,0.f), mCameraRotation(0.f), mCameraMoveSpeed(2.f), mCameraRotSpeed(90.f)
    {
    }

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : 
		mRotation(rotation), mAspectRatio(aspectRatio), mZoom(1.f), mBounds({ -mAspectRatio * mZoom, mAspectRatio * mZoom, -mZoom, mZoom }),
		mCamera(mBounds.Left, mBounds.Right, mBounds.Bottom, mBounds.Top),
		mCameraPosition(0.f, 0.f, 0.f), mCameraRotation(0.f), mCameraMoveSpeed(1.f), mCameraRotSpeed(90.f)
	{
	}


    void OrthographicCameraController::UpdateFn(float dt)
    {
		PROFILE_FUNCTION();
		if (InputSystem::IsKeyPressed(Borealis::Key::W))
		{
			mCameraPosition.y += mCameraMoveSpeed * dt;
		}

		else if (InputSystem::IsKeyPressed(Borealis::Key::S))
		{
			mCameraPosition.y -= mCameraMoveSpeed * dt;
		}

		if (InputSystem::IsKeyPressed(Borealis::Key::A))
		{
			mCameraPosition.x -= mCameraMoveSpeed * dt;
		}

		else if (InputSystem::IsKeyPressed(Borealis::Key::D))
		{
			mCameraPosition.x += mCameraMoveSpeed * dt;
		}

		if (mRotation)
		{
			if (InputSystem::IsKeyPressed(Borealis::Key::R))
			{
				mCameraRotation += mCameraRotSpeed * dt;
			}

			else if (InputSystem::IsKeyPressed(Borealis::Key::Q))
			{
				mCameraRotation -= mCameraRotSpeed * dt;
			}
			mCamera.SetRotation(mCameraRotation);
		}

		mCamera.SetPosition(mCameraPosition);
		
    }

    void OrthographicCameraController::EventFn(Borealis::Event& e)
    {
		PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<EventMouseScrolled>(BIND_EVENT(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<EventWindowResize>(BIND_EVENT(OrthographicCameraController::OnWindowResized));
    }

	void OrthographicCameraController::Resize(float width, float height)
	{
		mAspectRatio = width / height;
		mBounds = { -mAspectRatio * mZoom, mAspectRatio * mZoom, -mZoom, mZoom };
		mCamera.SetProjection(mBounds.Left, mBounds.Right, mBounds.Bottom, mBounds.Top);
	}

    bool OrthographicCameraController::OnMouseScrolled(EventMouseScrolled& e)
    {
		PROFILE_FUNCTION();
		mZoom -= static_cast<float>(e.GetYOffset()) * 0.7f;
		mZoom = std::max(mZoom, 0.25f);
		mBounds = { -mAspectRatio * mZoom, mAspectRatio * mZoom, -mZoom, mZoom };
		mCamera.SetProjection(mBounds.Left, mBounds.Right, mBounds.Bottom, mBounds.Top);
		mCameraMoveSpeed = mZoom;
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(EventWindowResize& e)
    {
		PROFILE_FUNCTION();
		Resize(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
        return false;
    }
}
