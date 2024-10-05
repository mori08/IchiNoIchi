#include <IchiNoIchi/Record.hpp>

namespace IchiNoIchi
{
	Record::Record(int32 digit, int32 defaultValue)
		: m_digit(digit)
		, m_maxValue((1 << m_digit) - 1)
		, m_defaultValue(Clamp(defaultValue, 0, m_maxValue))
		, m_value(m_defaultValue)
	{
	}

	void Record::init()
	{
		m_value = m_defaultValue;
	}

	void Record::set(int32 value)
	{
		m_value = Clamp(value, 0, m_maxValue);
	}

	int32 Record::get() const
	{
		return m_value;
	}

	void Record::addRecordToEncryptionList(std::list<int32>& dataList) const
	{
		for (int32 i = 0; i < m_digit; ++i)
		{
			// i桁目を追加
			dataList.emplace_back((m_value >> i) & 1);
		}
	}

	void Record::setValueFromDecryption(std::list<int32>& dataList)
	{
		m_value = 0;

		for (int32 i = 0; i < m_digit; ++i)
		{
			if (dataList.empty()) { return; }

			// i桁目に追加
			m_value |= dataList.front() << i;
			dataList.pop_front();
		}
	}

}
