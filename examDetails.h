#ifndef MTM_2_PART1_EXAMDETAILS_H
#define MTM_2_PART1_EXAMDETAILS_H

#include <iostream>

namespace mtm
{
	class ExamDetails
	{
		int course_number;
		int month_number;
		int day_number;
		double exam_time;
		int exam_length;
		std::string zoom_link;

	public:
		explicit ExamDetails(int course_number, int month_number, int day_number, double exam_time, int exam_length,
					std::string zoom_link = "");
		~ExamDetails();
		ExamDetails(const ExamDetails& to_copy);
		ExamDetails& operator=(const ExamDetails& details);
		std::string getLink() const;
		void setLink(std::string new_zoom_link);
		int operator-(const ExamDetails& details) const;
		bool operator<(const ExamDetails& details) const;
		friend std::ostream& operator<<(std::ostream& os, const ExamDetails& details);

		static ExamDetails makeMatamExam();

		class InvalidDateException{};
		class InvalidTimeException{};
		class InvalidArgsException{};

		static const int MATAM_COURSE_NUMBER = 234124;
		static const int HALF_HOUR = 30;
		static const int MATAM_DAY = 28;
		static const int MATAM_MONTH = 7;
		static const double MATAM_TIME;
		static const int MATAM_LENGTH = 3;
		static const std::string MATAM_ZOOM_LINK;
		static const int DAYS_IN_MONTH = 30;
		static const int MONTH_NUM = 12;
		static const int HOURS_IN_DAY = 24;
	};
}




#endif //MTM_2_PART1_EXAMDETAILS_H
