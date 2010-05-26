#ifndef _SWITCHSCHEDULEITEMDATA_H_
#define _SWITCHSCHEDULEITEMDATA_H_

#include <QDateTime>

class SwitchScheduleItemData {
public:
	inline SwitchScheduleItemData() {}
	inline SwitchScheduleItemData(const QDateTime &start, const QDateTime &end, bool status)
	: d_start(start), d_end(end), d_status(status) {}
    inline SwitchScheduleItemData(const SwitchScheduleItemData &other)
	: d_start(other.d_start), d_end(other.d_end), d_status(other.d_status) {}

	inline ~SwitchScheduleItemData() {}

    inline SwitchScheduleItemData &operator=(const SwitchScheduleItemData &other)
	{
		d_start = other.d_start;
		d_end = other.d_end;
		d_status = other.d_status;
		return *this;
	}

    inline bool operator==(const SwitchScheduleItemData &other) const
	{
		return (d_start == other.d_start) && (d_end == other.d_end) && (d_status == other.d_status);
	}

    inline bool operator!=(const SwitchScheduleItemData &other) const { return !(*this == other); }



	inline void setStart(const QDateTime &start) { d_start = start; }
	inline QDateTime start() const { return d_start; }

	inline void setEnd(const QDateTime &end) { d_end = end; }
	inline QDateTime end() const { return d_end; }

	inline void setStatus(bool status) { d_status = status; }
	inline bool status() const { return d_status; }

private:
	QDateTime d_start;
	QDateTime d_end;
	bool d_status;
};

class SwitchScheduleDelayData {
public:
	inline SwitchScheduleDelayData() {}
	inline SwitchScheduleDelayData(const QDateTime &duration, bool status)
	: d_duration(duration), d_status(status) {}
    inline SwitchScheduleDelayData(const SwitchScheduleDelayData &other)
	: d_duration(other.d_duration), d_status(other.d_status) {}

	inline ~SwitchScheduleDelayData() {}

    inline SwitchScheduleDelayData &operator=(const SwitchScheduleDelayData &other)
	{
		d_duration = other.d_duration;
		d_status = other.d_status;
		return *this;
	}

    inline bool operator==(const SwitchScheduleDelayData &other) const
	{
		return (d_duration == other.d_duration) && (d_status == other.d_status);
	}

    inline bool operator!=(const SwitchScheduleDelayData &other) const { return !(*this == other); }



	inline void setDuration(const QDateTime &duration) { d_duration = duration; }
	inline QDateTime duration() const { return d_duration; }

	inline void setStatus(bool status) { d_status = status; }
	inline bool status() const { return d_status; }

private:
	QDateTime d_duration;
	bool d_status;
};


#endif // _SWITCHSCHEDULEITEMDATA_H_
