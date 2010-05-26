#ifndef _LIGHTINGSCHEDULEITEMDATA_H_
#define _LIGHTINGSCHEDULEITEMDATA_H_

#include <QDateTime>

class LightingScheduleItemData {
public:
	inline LightingScheduleItemData() {}
	inline LightingScheduleItemData(const QDateTime &start, const QDateTime &end, int lighting)
	: d_start(start), d_end(end), d_lighting(lighting) {}
    inline LightingScheduleItemData(const LightingScheduleItemData &other)
	: d_start(other.d_start), d_end(other.d_end), d_lighting(other.d_lighting) {}

	inline ~LightingScheduleItemData() {}

    inline LightingScheduleItemData &operator=(const LightingScheduleItemData &other)
	{
		d_start = other.d_start;
		d_end = other.d_end;
		d_lighting = other.d_lighting;
		return *this;
	}

    inline bool operator==(const LightingScheduleItemData &other) const
	{
		return (d_start == other.d_start) && (d_end == other.d_end) && (d_lighting == other.d_lighting);
	}

    inline bool operator!=(const LightingScheduleItemData &other) const { return !(*this == other); }



	inline void setStart(const QDateTime &start) { d_start = start; }
	inline QDateTime start() const { return d_start; }

	inline void setEnd(const QDateTime &end) { d_end = end; }
	inline QDateTime end() const { return d_end; }

	inline void setLighting(int lighting) { d_lighting = lighting; }
	inline int lighting() const { return d_lighting; }

private:
	QDateTime d_start;
	QDateTime d_end;
	int d_lighting;
};

#endif // _LIGHTINGSCHEDULEITEMDATA_H_
