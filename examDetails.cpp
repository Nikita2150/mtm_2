#include "examDetails.h"

#include <cmath>
namespace mtm
{
	using std::string;
	using std::ostream;
	using std::endl;
	using std::modf;

	const double ExamDetails::MATAM_TIME = 13.0;
	const std::string ExamDetails::MATAM_ZOOM_LINK = "https://tinyurl.com/59hzps6m";
	const double EPSILON = 1E6;

	ExamDetails::ExamDetails(int course_number, int month_number, int day_number, double exam_time, int exam_length,
							string zoom_link) : zoom_link(zoom_link)
	{
                                if(course_number < 0)
		{
			throw InvalidArgsException();
		}
		this->course_number = course_number;
		if(month_number <= 0 || month_number > MONTH_NUM)
		{
			throw InvalidDateException();
		}
		this->month_number = month_number;
                                if(day_number <= 0 || day_number > DAYS_IN_MONTH)
                                {
			throw InvalidDateException();
		}
		this->day_number = day_number;


		double exam_time_full_hours;
		double exam_time_without_full_hours = modf(exam_time, &exam_time_full_hours);
		if(exam_time < -EPSILON || exam_length < 0 || (fabs(exam_time_without_full_hours) > EPSILON &&
		fabs(exam_time_full_hours - ExamDetails::HALF_HOUR)) > EPSILON)
		{
			throw InvalidTimeException();
		}
                                if(exam_time < 0 || exam_time >= HOURS_IN_DAY)
                                {
			throw InvalidTimeException();
		}
		this->exam_time = exam_time;
		this->exam_length = exam_length;
	}

	ExamDetails::~ExamDetails() = default;

	ExamDetails::ExamDetails(const ExamDetails &to_copy) : course_number(to_copy.course_number),
							month_number(to_copy.month_number), day_number(to_copy.day_number),
							exam_time(to_copy.exam_time), exam_length(to_copy.exam_length),
							zoom_link(to_copy.zoom_link)
	{ }
	ExamDetails& ExamDetails::operator=(const ExamDetails &details)
	{
		if(this->zoom_link != details.zoom_link)
		{
			this->zoom_link = details.zoom_link;
		}
		//alloc error?
		this->course_number = details.course_number;
		this->month_number = details.month_number;
		this->day_number = details.day_number;
		this->exam_time = details.exam_time;
		this->exam_length = details.exam_length;

		return *this;
	}

	string ExamDetails::getLink() const
	{
		return this->zoom_link;
	}

	void ExamDetails::setLink(string new_zoom_link)
	{
		this->zoom_link = new_zoom_link;
	}

	int ExamDetails::operator-(const ExamDetails &details) const
	{

		return (this->month_number - details.month_number) * ExamDetails::DAYS_IN_MONTH + 
			   (this->day_number - details.day_number);
	}
	bool ExamDetails::operator<(const ExamDetails &details) const
	{
		if(this->month_number < details.month_number)
		{
			return true;
		}
		if(this->month_number == details.month_number)
		{
			return ((*this) - details) < 0; // if operator- is set right
		}
		return false;
	}
	ostream& operator<<(std::ostream& os, const ExamDetails& details)
	{
		double exam_time_local = details.exam_time;
		int exam_time_full_hours = (int) exam_time_local;
		int minutes = 0;
		if((((int)(exam_time_local / 0.5))) % 2 != 0)
		{
			minutes = ExamDetails::HALF_HOUR;
		}
		return os << "Course Number: " << details.course_number << endl << "Time: " << details.day_number << "." <<
			details.month_number << " at " << exam_time_full_hours << ":" << minutes << ((minutes == 0) ? "0" : "") <<
				endl << "Duration: " << details.exam_length << ":00" << endl << "Zoom Link: " << details.zoom_link << endl;
	}

	ExamDetails ExamDetails::makeMatamExam()
	{
		ExamDetails matam(MATAM_COURSE_NUMBER, MATAM_MONTH, MATAM_DAY, MATAM_TIME, MATAM_LENGTH, MATAM_ZOOM_LINK);
		return matam;
	}

}
