#pragma once
#include <IchiNoIchi/Game/Object.hpp>
#include <IchiNoIchi/Game/ShareData.hpp>

namespace IchiNoIchi
{
	/// @brief オブジェクトを操作する
	class Controller
	{
	public:

		using Ptr = std::shared_ptr<Controller>;

		using Stack = std::stack<Ptr>;

		/// @brief push後の処理
		/// @param objectMap オブジェクトのマップ
		/// @param shareData オブジェクトの共有データ
		virtual void onAfterPush(Object::Map& objectMap, ShareData& shareData) = 0;

		/// @brief オブジェクトと共有データの更新
		/// @param objectMap オブジェクトのマップ
		/// @param shareData オブジェクトの共有データ
		virtual void control(Object::Map& objectMap, ShareData& shareData) = 0;

		/// @brief pop前の処理
		/// @param objectMap オブジェクトのマップ
		/// @param shareData オブジェクトの共有データ
		virtual void onBeforePop(Object::Map& objectMap, ShareData& shareData) = 0;

	};

	/// @brief 「Controller::Stack から1つだけ pop する」操作
	inline ControllerOperation popCtrlr()
	{
		static ControllerOperation rtn =
			[](Controller::Stack& stack, Object::Map& objectMap, ShareData& shareData)
			{
				stack.top()->onBeforePop(objectMap, shareData);
				stack.pop();
			};
		return rtn;
	}

	/// @brief 「Controller::Stack から全て pop する」操作
	inline ControllerOperation popAllCtrlr()
	{
		static ControllerOperation rtn =
			[](Controller::Stack& stack, Object::Map& objectMap, ShareData& shareData)
			{
				while (!stack.empty())
				{
					stack.top()->onBeforePop(objectMap, shareData);
					stack.pop();
				}
			};
		return rtn;
	}

	/// @brief 「Controller::Stack に指定した Controller を push する」操作
	/// @tparam ControllerType  Controllerの派生クラス
	template<typename ControllerType>
	inline ControllerOperation pushCtrlr()
	{
		static ControllerOperation rtn =
			[](Controller::Stack& stack, Object::Map& objectMap, ShareData& shareData)
			{
				stack.push(std::make_shared<ControllerType>());
				stack.top()->onAfterPush(objectMap, shareData);
			};
		return rtn;
	}
}
