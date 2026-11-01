#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
using namespace std;

class clsDate
{
private:
		short _Day = 1;
		short _Month = 1;
		short _Year = 1900;
public:
	clsDate()
	{
		time_t t = time(0);

		tm now;
		localtime_s(&now, &t);

		_Day = now.tm_mday;
		_Month = now.tm_mon + 1;
		_Year = now.tm_year + 1900;
	}

	clsDate(string sDate)
	{
		vector <string> vDate;
		vDate = clsString::Split(sDate, "/");

		_Day = stoi(vDate[0]);
	    _Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DateOrderInYear, short year)
	{
		clsDate Date = GetDateFromDayOrderInYear(DateOrderInYear, Year);

		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;


	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day ;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << DateToString() << endl;
	}

	bool static LeapYear(int Year)
	{
		if (Year % 400 == 0)
		{
			return true;
		}
		else if (Year % 100 != 0)
		{
			return false;
		}

		else if (Year % 4 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	static string GetSystemDateTimeString()
	{
		//system datetime string
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now.tm_year + 1900;
		Month = now.tm_mon + 1;
		Day = now.tm_mday;
		Hour = now.tm_hour;
		Minute = now.tm_min;
		Second = now.tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	bool LeapYear()
	{
		return LeapYear(_Year);
		
	}

	short static NumberOfDayesInMonth(short month, short year)
	{
		if (month < 1 || month > 12)
		{
			return 0;
		}

		int Days[12] = { 31, 28, 31,30,31,30,31,31,30,31,30,31 };

		return ((month == 2) ? (LeapYear(year) ? 29 : 28) : Days[month - 1]);
	}

	short NumberOfDayesInMonth()
	{
		return NumberOfDayesInMonth(_Month, _Year);
		
	}

	static bool ValidateDate(clsDate Date)
	{
		short MonthDays = NumberOfDayesInMonth(Date.Month, Date.Year);

		if ((Date.Day > MonthDays && Date.Day < 1) || (Date.Month > 12 && Date.Month < 1) || (Date.Year < 0))
		{
			return false;
		}
		else
			return true;
	}

	bool ValidateDate()
	{
		return ValidateDate(*this);
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{

		if (Month < 1 || Month>12)
			return  0;

		int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (LeapYear(Year) ? 29 : 28) : days[Month - 1];

	}


	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Month, _Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year)
	{

		clsDate Date;
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}

		return Date;
	}

	static clsDate GetSystemDate()
	{
		clsDate Date;
		time_t t = time(0);
		tm now;
		localtime_s(&now, &t);

		short Day, Month, Year;

		Year = now.tm_year + 1900;
		Month = now.tm_mon + 1;
		Day = now.tm_mday;
		return clsDate(Day, Month, Year);
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);

	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static short DayOrder(short Day, short Month, short Year)
	{
		short a = ((14 - Month) / 12);
		short y = Year - a;
		short m = Month + 12 * a - 2;
		short d = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

		return d;
	}

	short DayOrder()
	{
		return DayOrder(_Day, _Month, _Year);
	}

	static string DayName(short DayOrder)
	{
		string arr7Days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return arr7Days[DayOrder];
	}

	string DayName()
	{
		return DayName(DayOrder());
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? Date1.Day == Date2.Day : false) : false;
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1EqualDate2(Date1, Date2) && !IsDate1BeforeDate2(Date1, Date2));
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return (NumberOfDayesInMonth(Date.Month, Date.Year) == Date.Day);
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDays(clsDate& Date, short Days)
	{
		for (int i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	void IncreaseDateByXDays(short Days)
	{
		 IncreaseDateByXDays(*this, Days);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;

			if (Date.Day > NumberOfDayesInMonth(Date.Month, Date.Year))
			{
				Date.Day = NumberOfDayesInMonth(Date.Month, Date.Year);
			}
		}

		return Date;
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;

		if (Date.Day > NumberOfDayesInMonth(Date.Month, Date.Year))
		{
			Date.Day = NumberOfDayesInMonth(Date.Month, Date.Year);
		}

		return Date;
	}

	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
			}

			Date.Day = NumberOfDayesInMonth(Date.Month, Date.Year);
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days : Days;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static bool IsWeekend(clsDate Date)
	{
		short DayIndex = DayOrder(Date.Day, Date.Month, Date.Year);

		return (DayIndex == 5 || DayIndex == 6);
	}

	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekend(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate Date)
	{
		return 6 - DayOrder(Date.Day, Date.Month, Date.Year);
	}

	short DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;

		EndOfMonthDate.Day = NumberOfDayesInMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}

	short DaysUntilEndOfMonth()
	{
		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate Date)
	{
		clsDate EndOfYearDate;

		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}

	short DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}

	enum enCompareDates
	{
		Before = -1,
		Equal = 0,
		After = 1
	};

	static enCompareDates CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
		{
			return enCompareDates::Before;
		}

		if (IsDate1EqualDate2(Date1, Date2))
		{
			return enCompareDates::Equal;
		}

		return enCompareDates::After;
	}

	enCompareDates CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}


	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
	{
		short Days = 0;

		while (IsDate1BeforeDate2(
			DateFrom,
			DateTo))
		{
			if (IsBusinessDay(DateFrom))
			{
				Days++;
			}

			DateFrom =
				IncreaseDateByOneDay(DateFrom);
		}

		return Days;
	}

	static short CalculateVacationDays2(clsDate DateFrom, clsDate DateTo)
	{
		return CalculateBusinessDays(DateFrom, DateTo);
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short VacationDays = 0;

		while (!IsDate1EqualDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
			{
				VacationDays++;
			}

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return VacationDays;
	}

	static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		short WeekEndCounter = 0;

		while (IsWeekend(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{
			if (IsWeekend(DateFrom))
			{
				WeekEndCounter++;
			}

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (IsWeekend(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}

	static string MonthName(short Month)
	{
		string arr12Months[12] =
		{
			"Jan", "Feb", "Mar", "Apr",
			"May", "Jun", "Jul", "Aug",
			"Sep", "Oct", "Nov", "Dec"
		};

		return arr12Months[Month - 1];
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		int Current = DayOrder(1, Month, Year);

		int NumberOfDays = NumberOfDayesInMonth(Month, Year);

		short i;

		printf("_________________%s_________________\\n\\n", MonthName(Month).c_str());

		printf(" Sun  Mon  Tue  Wed  Thu  Fri  Sat\\n");

			for (i = 0; i < Current; i++)
			{
				printf("     ");
			}

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

				if (++i == 7)
				{
					i = 0;
					printf("\\n");
				}
		}

		printf("\\n\\n_____________________________________\\n");
	}

	static void PrintYearCalendar(short Year)
	{
		printf("_____________________________________\\n\\n");

		printf("\\t\\tCalendar - %d", Year);

		printf("\\n\\n_____________________________________\\n\\n");

					for (short i = 1; i <= 12; i++)
					{
						PrintMonthCalendar(i, Year);

						cout << endl;
					}
	}


};

