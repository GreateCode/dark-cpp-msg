#pragma once
namespace dk
{
	namespace net
	{
		class DARKCPPMSG_API error_t
		{
		public:
			int value;
			std::string emsg;

			error_t();
			error_t(const error_t& copy);
			error_t& operator=(const error_t& copy);

			inline operator bool()
			{
				return value !=0;
			}
		};
	};

};