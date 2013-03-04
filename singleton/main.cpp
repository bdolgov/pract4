#include <cstdlib>
class Singleton1
{
	public:
		static Singleton1& instance()
		{
			static Singleton1 m_instance;
			return m_instance;
		}
	private:
		Singleton1() {}
		~Singleton1() {}
		Singleton1 &operator=(const Singleton1&);
		Signleton1(const Singleton1&);
};

class Singleton2
{
	public:
		static Singleton2& instance()
		{
			if (m_instance == 0)
			{
				m_instance = new Singleton2;
				atexit(destroy);
			}
			return *m_instance;
		}
	private:
		Singleton2() {}
		static Singleton2 *m_instance;
		static void destroy()
		{
			delete m_instance;
			m_instance = NULL;
		}
		
};

Singleton2* Singleton2::m_instance = NULL;
