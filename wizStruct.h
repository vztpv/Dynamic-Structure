
#include <map>
#include <string>

#include <wiz/global.h>
#include <wiz/wizVar.h>


namespace wiz {

	class wizStructError { };

	class wizStruct : public wizObject // dynamic struct!!
	{
	private:
		std::map<std::string, Var> data;
	public:
		wizStruct() { }
		virtual ~wizStruct() { }
	public:
		wizStruct(const wizStruct& ws)
		{
			data = ws.data;
		}
		virtual wizStruct& operator=(const wizStruct& object)
		{
			data = object.data;
			return *this;
		}
		virtual wizObject& operator=(const wizObject& object)
		{
			const wizStruct& temp = static_cast< const wizStruct&>(object);
			(*this) = temp;
			return *static_cast< wizObject* >(this);
		}
		virtual wizObject* clone()const { return new wizStruct(*this); }

		virtual std::string toString()const { return "wizStruct"; }
		virtual void initial(const wizObject& object)
		{
			const wizStruct temp = static_cast< const wizStruct&>(object);

			(*this) = temp;
		}
	public:
		/// add, remove // string varName, wizObject* data
		bool add(const std::string& varName, const Var& var)
		{
			bool bSuccess = true;

			if (isExistVar(varName))
			{
				bSuccess = false;
			}
			else {
				data.insert(std::pair<std::string, Var>(varName, var));
			}
			return bSuccess;
		}
		bool remove(const std::string& varName)
		{
			bool bSuccess = true;

			if (isExistVar(varName))
			{
				data.erase(varName);
			}
			else {
				bSuccess = false;
			}
			return bSuccess;
		}
		bool isExistVar(const std::string& varName)
		{
			std::map<std::string, Var>::iterator pos;

			pos = data.find(varName); // find by key..

			return pos != data.end();
		}
		/// get, set, 없는 경우, 예외를 던진다..
		// std::pair<bool, Var>?
		Var get(const std::string& varName)
		{
			std::map<std::string, Var>::iterator pos = data.find(varName);
			if (pos != data.end()) // exist
			{
				return pos->second;
			}
			else
			{
				throw wizStructError();
			}
		}
		// return bool?
		void set(const std::string& varName, const Var var)
		{
			std::map<std::string, Var>::iterator pos = data.find(varName);
			if (pos != data.end()) // exist
			{
				pos->second = var;
			}
			else
			{
				throw wizStructError();
			}
		}
	};
}
