#ifndef _FANSCHEDULEITEMDATA_H_
#define _FANSCHEDULEITEMDATA_H_

#include <QDateTime>

class FanScheduleItemData {
public:
	inline FanScheduleItemData() {}
	inline FanScheduleItemData(const QDateTime &start, const QDateTime &end, int temperature)
	: d_start(start), d_end(end), d_temperature(temperature) {}
    inline FanScheduleItemData(const FanScheduleItemData &other)
	: d_start(other.d_start), d_end(other.d_end), d_temperature(other.d_temperature) {}

	inline ~FanScheduleItemData() {}

    inline FanScheduleItemData &operator=(const FanScheduleItemData &other)
	{
		d_start = other.d_start;
		d_end = other.d_end;
		d_temperature = other.d_temperature;
		return *this;
	}

    inline bool operator==(const FanScheduleItemData &other) const
	{
		return (d_start == other.d_start) && (d_end == other.d_end) && (d_temperature == other.d_temperature);
	}

    inline bool operator!=(const FanScheduleItemData &other) const { return !(*this == other); }



	inline void setStart(const QDateTime &start) { d_start = start; }
	inline QDateTime start() const { return d_start; }

	inline void setEnd(const QDateTime &end) { d_end = end; }
	inline QDateTime end() const { return d_end; }

	inline void setTemperature(int temperature) { d_temperature = temperature; }
	inline int temperature() const { return d_temperature; }

private:
	QDateTime d_start;
	QDateTime d_end;
	int d_temperature;
};

#endif // _FANSCHEDULEITEMDATA_H_
